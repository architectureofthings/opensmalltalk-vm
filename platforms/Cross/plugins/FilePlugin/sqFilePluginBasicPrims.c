/****************************************************************************
*   PROJECT: File Interface
*   FILE:    sqFilePluginBasicPrims.c
*   CONTENT: 
*
*   AUTHOR:  
*   ADDRESS: 
*   EMAIL:   ]
*   RCSID:   $Id: sqFilePluginBasicPrims.c 1283 2005-12-31 00:51:12Z rowledge $
*
*   NOTES: See change log below.
*	2005-03-26 IKP fix unaligned accesses to file[Size] members
* 	2004-06-10 IKP 64-bit cleanliness
* 	1/28/02    Tim remove non-ansi stuff
*				unistd.h
				ftello
				fseeko
				ftruncate & fileno
				macro-ise use of sqFTruncate to avoid non-ansi
*	1/22/2002  JMM Use squeakFileOffsetType versus off_t
*
*****************************************************************************/

/* The basic prim code for file operations. See also the platform specific
* files typically named 'sq{blah}Directory.c' for details of the directory
* handling code. Note that the win32 platform #defines NO_STD_FILE_SUPPORT
* and thus bypasses this file
*/
                                                      
#include "sq.h"
#ifndef NO_STD_FILE_SUPPORT
#include "FilePlugin.h"

/***
	The state of a file is kept in the following structure,
	which is stored directly in a Squeak bytes object.
	NOTE: The Squeak side is responsible for creating an
	object with enough room to store sizeof(SQFile) bytes.

	The session ID is used to detect stale file objects--
	files that were still open when an image was written.
	The file pointer of such files is meaningless.

	Files are always opened in binary mode; Smalltalk code
	does (or someday will do) line-end conversion if needed.

	Writeable files are opened read/write. The stdio spec
	requires that a positioning operation be done when
	switching between reading and writing of a read/write
	filestream. The lastOp field records whether the last
	operation was a read or write operation, allowing this
	positioning operation to be done automatically if needed.

	typedef struct {
		File	*file;
		int		sessionID;
		int		writable;
		squeakFileOffsetType		fileSize;  //JMM Nov 8th 2001 64bits we hope
		int		lastOp;  // 0 = uncommitted, 1 = read, 2 = write //
	} SQFile;

***/

/*** Constants ***/
#define UNCOMMITTED	0
#define READ_OP		1
#define WRITE_OP	2

#ifndef SEEK_SET
#define SEEK_SET	0
#define SEEK_CUR	1
#define SEEK_END	2
#endif

/*** Variables ***/
int thisSession = 0;
extern struct VirtualMachine * interpreterProxy;

/* Since SQFile instaces are held on the heap in 32-bit-aligned byte arrays we
 * may need to use memcpy to avoid alignment faults.
 */
#if DOUBLE_WORD_ALIGNMENT
static void setFile(SQFile *f, FILE *file)
{
  void *in= (void *)&file;
  void *out= (void *)&f->file;
  memcpy(out, in, sizeof(FILE *));
}
#else
# define setFile(f,fileptr) ((f)->file = (fileptr))
#endif

#if DOUBLE_WORD_ALIGNMENT
static void setSize(SQFile *f, squeakFileOffsetType size)
{
  void *in= (void *)&size;
  void *out= (void *)&f->fileSize;
  memcpy(out, in, sizeof(squeakFileOffsetType));
}
#else
# define setSize(f,size) ((f)->fileSize = (size))
#endif

#if DOUBLE_WORD_ALIGNMENT
static FILE *getFile(SQFile *f)
{
  FILE *file;
  void *in= (void *)&f->file;
  void *out= (void *)&file;
  memcpy(out, in, sizeof(FILE *));
  return file;
}
#else
# define getFile(f) ((f)->file)
#endif

#if DOUBLE_WORD_ALIGNMENT
static squeakFileOffsetType getSize(SQFile *f)
{
  squeakFileOffsetType size;
  void *in= (void *)&f->fileSize;
  void *out= (void *)&size;
  memcpy(out, in, sizeof(squeakFileOffsetType));
  return size;
}
#else
# define getSize(f) ((f)->fileSize)
#endif

sqInt sqFileAtEnd(SQFile *f) {
	/* Return true if the file's read/write head is at the end of the file. */

	if (!sqFileValid(f))
		return interpreterProxy->success(false);
	if (f->isStdioStream)
		return feof(getFile(f));
	return ftell(getFile(f)) == getSize(f);
}

sqInt sqFileClose(SQFile *f) {
	/* Close the given file. */

	if (!sqFileValid(f))
		return interpreterProxy->success(false);
	fclose(getFile(f));
	setFile(f, 0);
	f->sessionID = 0;
	f->writable = false;
	setSize(f, 0);
	f->lastOp = UNCOMMITTED;
	return 1;
}

sqInt sqFileDeleteNameSize(char* sqFileName, sqInt sqFileNameSize) {
	char cFileName[1000];
	int err;

	if (sqFileNameSize >= 1000) {
		return interpreterProxy->success(false);
	}

	/* copy the file name into a null-terminated C string */
	interpreterProxy->ioFilenamefromStringofLengthresolveAliases(cFileName, sqFileName, sqFileNameSize, false);

	err = remove(cFileName);
	if (err) {
		return interpreterProxy->success(false);
	}
	return 1;
}

squeakFileOffsetType sqFileGetPosition(SQFile *f) {
	/* Return the current position of the file's read/write head. */

	squeakFileOffsetType position;

	if (!sqFileValid(f))
		return interpreterProxy->success(false);
	position = ftell(getFile(f));
	if (position == -1)
		return interpreterProxy->success(false);
	return position;
}

sqInt sqFileInit(void) {
	/* Create a session ID that is unlikely to be repeated.
	   Zero is never used for a valid session number.
	   Should be called once at startup time.
	*/
#if VM_PROXY_MINOR > 6
	thisSession = interpreterProxy->getThisSessionID();
#else
	thisSession = ioLowResMSecs() + time(NULL);
	if (thisSession == 0) thisSession = 1;	/* don't use 0 */
#endif
	return 1;
}

sqInt sqFileShutdown(void) {
	return 1;
}

sqInt sqFileOpen(SQFile *f, char* sqFileName, sqInt sqFileNameSize, sqInt writeFlag) {
	/* Opens the given file using the supplied sqFile structure
	   to record its state. Fails with no side effects if f is
	   already open. Files are always opened in binary mode;
	   Squeak must take care of any line-end character mapping.
	*/

	char cFileName[1001];

	/* don't open an already open file */
	if (sqFileValid(f))
		return interpreterProxy->success(false);

	/* copy the file name into a null-terminated C string */
	if (sqFileNameSize > 1000) {
		return interpreterProxy->success(false);
	}
	interpreterProxy->ioFilenamefromStringofLengthresolveAliases(cFileName, sqFileName, sqFileNameSize, true);

	if (writeFlag) {
		/* First try to open an existing file read/write: */
		setFile(f, fopen(cFileName, "r+b"));
		if (getFile(f) == NULL) {
			/* Previous call fails if file does not exist. In that case,
			   try opening it in write mode to create a new, empty file.
			*/
			setFile(f, fopen(cFileName, "w+b"));
			if (getFile(f) != NULL) {
			    char type[4],creator[4];
				dir_GetMacFileTypeAndCreator(sqFileName, sqFileNameSize, type, creator);
				if (strncmp(type,"BINA",4) == 0 || strncmp(type,"????",4) == 0 || *(int *)type == 0 ) 
				    dir_SetMacFileTypeAndCreator(sqFileName, sqFileNameSize,"TEXT","R*ch");	
			}
		}
		f->writable = true;
	} else {
		setFile(f, fopen(cFileName, "rb"));
		f->writable = false;
	}

	if (getFile(f) == NULL) {
		f->sessionID = 0;
		setSize(f, 0);
		return interpreterProxy->success(false);
	} else {
		FILE *file= getFile(f);
		f->sessionID = thisSession;
		/* compute and cache file size */
		fseek(file, 0, SEEK_END);
		setSize(f, ftell(file));
		fseek(file, 0, SEEK_SET);
	}
	f->lastOp = UNCOMMITTED;
	return 1;
}

/*
 * Fill-in files with handles for stdin, stdout and stderr as available and
 * answer a bit-mask of the availability, 1 corresponding to stdin, 2 to stdout
 * and 4 to stderr, with 0 on error or unavailablity.
 */
sqInt
sqFileStdioHandlesInto(SQFile files[3])
{
#if defined(_IONBF)
	if (isatty(fileno(stdin)))
		setvbuf(stdin,0,_IONBF,0);
#endif
	files[0].sessionID = thisSession;
	files[0].file = stdin;
	files[0].fileSize = 0;
	files[0].writable = false;
	files[0].lastOp = READ_OP;
	files[0].isStdioStream = true;
	files[0].lastChar = EOF;

	files[1].sessionID = thisSession;
	files[1].file = stdout;
	files[1].fileSize = 0;
	files[1].writable = true;
	files[1].isStdioStream = true;
	files[1].lastChar = EOF;
	files[1].lastOp = WRITE_OP;

	files[2].sessionID = thisSession;
	files[2].file = stderr;
	files[2].fileSize = 0;
	files[2].writable = true;
	files[2].isStdioStream = true;
	files[2].lastChar = EOF;
	files[2].lastOp = WRITE_OP;

	return 7;
}

size_t sqFileReadIntoAt(SQFile *f, size_t count, char* byteArrayIndex, size_t startIndex) {
	/* Read count bytes from the given file into byteArray starting at
	   startIndex. byteArray is the address of the first byte of a
	   Squeak bytes object (e.g. String or ByteArray). startIndex
	   is a zero-based index; that is a startIndex of 0 starts writing
	   at the first byte of byteArray.
	*/

	char *dst;
	size_t bytesRead;
	FILE *file;
#if COGMTVM
	sqInt myThreadIndex;
#endif

	if (!sqFileValid(f))
		return interpreterProxy->success(false);
	file = getFile(f);
	if (f->writable) {
		if (f->isStdioStream)
			return interpreterProxy->success(false);
		if (f->lastOp == WRITE_OP)
			fseek(file, 0, SEEK_CUR);  /* seek between writing and reading */
	}
	dst = byteArrayIndex + startIndex;
#if COGMTVM
	if (f->isStdioStream)
		myThreadIndex = interpreterProxy->disownVM();
#endif
	bytesRead = fread(dst, 1, count, file);
#if COGMTVM
	if (f->isStdioStream)
		interpreterProxy->ownVM(myThreadIndex);
#endif
	/* support for skippng back 1 chacater for stdio streams */
	f->lastChar = bytesRead > 0 ? dst[bytesRead-1] : EOF;
	f->lastOp = READ_OP;
	return bytesRead;
}

sqInt sqFileRenameOldSizeNewSize(char* oldNameIndex, sqInt oldNameSize, char* newNameIndex, sqInt newNameSize) {
	char cOldName[1000], cNewName[1000];
	int err;

	if ((oldNameSize >= 1000) || (newNameSize >= 1000)) {
		return interpreterProxy->success(false);
	}

	/* copy the file names into null-terminated C strings */
	interpreterProxy->ioFilenamefromStringofLengthresolveAliases(cOldName, oldNameIndex, oldNameSize, false);

	interpreterProxy->ioFilenamefromStringofLengthresolveAliases(cNewName, newNameIndex, newNameSize, false);

	err = rename(cOldName, cNewName);
	if (err) {
		return interpreterProxy->success(false);
	}
	return 1;
}

sqInt sqFileSetPosition(SQFile *f, squeakFileOffsetType position) {
	/* Set the file's read/write head to the given position. */

	if (!sqFileValid(f))
		return interpreterProxy->success(false);
	if (f->isStdioStream) {
		/* support one character of pushback for stdio streams. */
		if (!f->writable
		 && f->lastChar != EOF) {
			squeakFileOffsetType currentPos = ftell(getFile(f));
			if (currentPos == position)
				return 1;
			if (currentPos - 1 == position) {
				ungetc(f->lastChar, getFile(f));
				f->lastChar = EOF;
				return 1;
			}
		}
		return interpreterProxy->success(false);
	}
	fseek(getFile(f), position, SEEK_SET);
	f->lastOp = UNCOMMITTED;
	return 1;
}

squeakFileOffsetType sqFileSize(SQFile *f) {
	/* Return the length of the given file. */

	if (!sqFileValid(f))
		return interpreterProxy->success(false);
	if (f->isStdioStream)
		return interpreterProxy->success(false);
	return getSize(f);
}

sqInt sqFileFlush(SQFile *f) {
	/* Return the length of the given file. */

	if (!sqFileValid(f))
		return interpreterProxy->success(false);
	fflush(getFile(f));
	return 1;
}

sqInt sqFileTruncate(SQFile *f,squeakFileOffsetType offset) {
	/* Truncate the file*/

	if (!sqFileValid(f))
		return interpreterProxy->success(false);
 	if (sqFTruncate(getFile(f), offset))
		return interpreterProxy->success(false);
	setSize(f, ftell(getFile(f)));
	return 1;
}


sqInt sqFileValid(SQFile *f) {
	return (
		(f != NULL) &&
		(getFile(f) != NULL) &&
		(f->sessionID == thisSession));
}

size_t sqFileWriteFromAt(SQFile *f, size_t count, char* byteArrayIndex, size_t startIndex) {
	/* Write count bytes to the given writable file starting at startIndex
	   in the given byteArray. (See comment in sqFileReadIntoAt for interpretation
	   of byteArray and startIndex).
	*/

	char *src;
	size_t bytesWritten;
	squeakFileOffsetType position;
	FILE *file;

	if (!(sqFileValid(f) && f->writable))
		return interpreterProxy->success(false);
	file= getFile(f);
	if (f->lastOp == READ_OP) fseek(file, 0, SEEK_CUR);  /* seek between reading and writing */
	src = byteArrayIndex + startIndex;
	bytesWritten = fwrite(src, 1, count, file);

	position = ftell(file);
	if (position > getSize(f)) {
		setSize(f, position);  /* update file size */
	}

	if (bytesWritten != count) {
		interpreterProxy->success(false);
	}
	f->lastOp = WRITE_OP;
	return bytesWritten;
}

sqInt sqFileThisSession() {
	return thisSession;
}

#endif /* NO_STD_FILE_SUPPORT */
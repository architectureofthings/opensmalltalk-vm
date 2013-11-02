/* Automatically generated by
	SmartSyntaxPluginCodeGenerator VMMaker.oscog-eem.496 uuid: f0401045-f2f7-470e-9940-3535be9c0334
   from
	UUIDPlugin VMMaker.oscog-eem.496 uuid: f0401045-f2f7-470e-9940-3535be9c0334
 */
static char __buildInfo[] = "UUIDPlugin VMMaker.oscog-eem.496 uuid: f0401045-f2f7-470e-9940-3535be9c0334 " __DATE__ ;



#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Default EXPORT macro that does nothing (see comment in sq.h): */
#define EXPORT(returnType) returnType

/* Do not include the entire sq.h file but just those parts needed. */
/*  The virtual machine proxy definition */
#include "sqVirtualMachine.h"
/* Configuration options */
#include "sqConfig.h"
/* Platform specific definitions */
#include "sqPlatformSpecific.h"

#define true 1
#define false 0
#define null 0  /* using 'null' because nil is predefined in Think C */
#ifdef SQUEAK_BUILTIN_PLUGIN
#undef EXPORT
// was #undef EXPORT(returnType) but screws NorCroft cc
#define EXPORT(returnType) static returnType
#endif

#include "UUIDPlugin.h"
#include "sqMemoryAccess.h"


/*** Constants ***/
#define BytesPerWord 4


/*** Function Prototypes ***/
static VirtualMachine * getInterpreter(void);
EXPORT(const char*) getModuleName(void);
static sqInt halt(void);
EXPORT(sqInt) initialiseModule(void);
static sqInt msg(char *s);
EXPORT(sqInt) primitiveMakeUUID(void);
EXPORT(sqInt) setInterpreter(struct VirtualMachine*anInterpreter);
EXPORT(sqInt) shutdownModule(void);
static sqInt sqAssert(sqInt aBool);


/*** Variables ***/

#if !defined(SQUEAK_BUILTIN_PLUGIN)
static sqInt (*byteSizeOf)(sqInt oop);
static sqInt (*failed)(void);
static void * (*firstIndexableField)(sqInt oop);
static sqInt (*isBytes)(sqInt oop);
static sqInt (*methodArgumentCount)(void);
static sqInt (*primitiveFail)(void);
static sqInt (*stackObjectValue)(sqInt offset);
#else /* !defined(SQUEAK_BUILTIN_PLUGIN) */
extern sqInt byteSizeOf(sqInt oop);
extern sqInt failed(void);
extern void * firstIndexableField(sqInt oop);
extern sqInt isBytes(sqInt oop);
extern sqInt methodArgumentCount(void);
extern sqInt primitiveFail(void);
extern sqInt stackObjectValue(sqInt offset);
extern
#endif
struct VirtualMachine* interpreterProxy;
static const char *moduleName =
#ifdef SQUEAK_BUILTIN_PLUGIN
	"UUIDPlugin VMMaker.oscog-eem.496 (i)"
#else
	"UUIDPlugin VMMaker.oscog-eem.496 (e)"
#endif
;



/*	Note: This is coded so that plugins can be run from Squeak. */

static VirtualMachine *
getInterpreter(void)
{
	return interpreterProxy;
}


/*	Note: This is hardcoded so it can be run from Squeak.
	The module name is used for validating a module *after*
	it is loaded to check if it does really contain the module
	we're thinking it contains. This is important! */

EXPORT(const char*)
getModuleName(void)
{
	return moduleName;
}

static sqInt
halt(void)
{
	;
	return 0;
}

EXPORT(sqInt)
initialiseModule(void)
{
	return sqUUIDInit();
}

static sqInt
msg(char *s)
{
	fprintf(stderr, "\n%s: %s", moduleName, s);
	return 0;
}

EXPORT(sqInt)
primitiveMakeUUID(void)
{
	char*location;
	sqInt oop;

	oop = stackObjectValue(0);
	if ((failed())
	 || (((methodArgumentCount()) != 0)
	 || ((!(isBytes(oop)))
	 || ((byteSizeOf(oop)) != 16)))) {
		return primitiveFail();
	}
	location = firstIndexableField(oop);
	MakeUUID(location);
	return oop;
}


/*	Note: This is coded so that it can be run in Squeak. */

EXPORT(sqInt)
setInterpreter(struct VirtualMachine*anInterpreter)
{
	sqInt ok;

	interpreterProxy = anInterpreter;
	ok = ((interpreterProxy->majorVersion()) == (VM_PROXY_MAJOR))
	 && ((interpreterProxy->minorVersion()) >= (VM_PROXY_MINOR));
	if (ok) {
		
#if !defined(SQUEAK_BUILTIN_PLUGIN)
		byteSizeOf = interpreterProxy->byteSizeOf;
		failed = interpreterProxy->failed;
		firstIndexableField = interpreterProxy->firstIndexableField;
		isBytes = interpreterProxy->isBytes;
		methodArgumentCount = interpreterProxy->methodArgumentCount;
		primitiveFail = interpreterProxy->primitiveFail;
		stackObjectValue = interpreterProxy->stackObjectValue;
#endif /* !defined(SQUEAK_BUILTIN_PLUGIN) */
	}
	return ok;
}

EXPORT(sqInt)
shutdownModule(void)
{
	return sqUUIDShutdown();
}

static sqInt
sqAssert(sqInt aBool)
{
	/* missing DebugCode */;
}


#ifdef SQUEAK_BUILTIN_PLUGIN

void* UUIDPlugin_exports[][3] = {
	{"UUIDPlugin", "getModuleName", (void*)getModuleName},
	{"UUIDPlugin", "initialiseModule", (void*)initialiseModule},
	{"UUIDPlugin", "primitiveMakeUUID", (void*)primitiveMakeUUID},
	{"UUIDPlugin", "setInterpreter", (void*)setInterpreter},
	{"UUIDPlugin", "shutdownModule", (void*)shutdownModule},
	{NULL, NULL, NULL}
};

#endif /* ifdef SQ_BUILTIN_PLUGIN */

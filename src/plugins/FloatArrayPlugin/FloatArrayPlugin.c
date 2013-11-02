/* Automatically generated by
	VMPluginCodeGenerator VMMaker.oscog-eem.496 uuid: f0401045-f2f7-470e-9940-3535be9c0334
   from
	FloatArrayPlugin VMMaker.oscog-eem.496 uuid: f0401045-f2f7-470e-9940-3535be9c0334
 */
static char __buildInfo[] = "FloatArrayPlugin VMMaker.oscog-eem.496 uuid: f0401045-f2f7-470e-9940-3535be9c0334 " __DATE__ ;



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

#include "sqMemoryAccess.h"


/*** Constants ***/
#define BytesPerWord 4


/*** Function Prototypes ***/
static VirtualMachine * getInterpreter(void);
EXPORT(const char*) getModuleName(void);
static sqInt halt(void);
static sqInt msg(char *s);
EXPORT(sqInt) primitiveAddFloatArray(void);
EXPORT(sqInt) primitiveAddScalar(void);
EXPORT(sqInt) primitiveAt(void);
EXPORT(sqInt) primitiveAtPut(void);
EXPORT(sqInt) primitiveDivFloatArray(void);
EXPORT(sqInt) primitiveDivScalar(void);
EXPORT(sqInt) primitiveDotProduct(void);
EXPORT(sqInt) primitiveEqual(void);
EXPORT(sqInt) primitiveHashArray(void);
EXPORT(sqInt) primitiveLength(void);
EXPORT(sqInt) primitiveMulFloatArray(void);
EXPORT(sqInt) primitiveMulScalar(void);
EXPORT(sqInt) primitiveNormalize(void);
EXPORT(sqInt) primitiveSubFloatArray(void);
EXPORT(sqInt) primitiveSubScalar(void);
EXPORT(sqInt) primitiveSum(void);
EXPORT(sqInt) setInterpreter(struct VirtualMachine*anInterpreter);


/*** Variables ***/

#if !defined(SQUEAK_BUILTIN_PLUGIN)
static sqInt (*failed)(void);
static void * (*firstIndexableField)(sqInt oop);
static double (*floatObjectOf)(double  aFloat);
static double (*floatValueOf)(sqInt oop);
static sqInt (*integerValueOf)(sqInt oop);
static sqInt (*isIntegerObject)(sqInt objectPointer);
static sqInt (*isWords)(sqInt oop);
static sqInt (*pop)(sqInt nItems);
static sqInt (*popthenPush)(sqInt nItems, sqInt oop);
static sqInt (*primitiveFail)(void);
static sqInt (*pushBool)(sqInt trueOrFalse);
static sqInt (*pushFloat)(double  f);
static sqInt (*pushInteger)(sqInt integerValue);
static sqInt (*slotSizeOf)(sqInt oop);
static sqInt (*stSizeOf)(sqInt oop);
static double (*stackFloatValue)(sqInt offset);
static sqInt (*stackIntegerValue)(sqInt offset);
static sqInt (*stackObjectValue)(sqInt offset);
static sqInt (*stackValue)(sqInt offset);
static sqInt (*success)(sqInt aBoolean);
#else /* !defined(SQUEAK_BUILTIN_PLUGIN) */
extern sqInt failed(void);
extern void * firstIndexableField(sqInt oop);
extern double floatObjectOf(double  aFloat);
extern double floatValueOf(sqInt oop);
extern sqInt integerValueOf(sqInt oop);
extern sqInt isIntegerObject(sqInt objectPointer);
extern sqInt isWords(sqInt oop);
extern sqInt pop(sqInt nItems);
extern sqInt popthenPush(sqInt nItems, sqInt oop);
extern sqInt primitiveFail(void);
extern sqInt pushBool(sqInt trueOrFalse);
extern sqInt pushFloat(double  f);
extern sqInt pushInteger(sqInt integerValue);
extern sqInt slotSizeOf(sqInt oop);
extern sqInt stSizeOf(sqInt oop);
extern double stackFloatValue(sqInt offset);
extern sqInt stackIntegerValue(sqInt offset);
extern sqInt stackObjectValue(sqInt offset);
extern sqInt stackValue(sqInt offset);
extern sqInt success(sqInt aBoolean);
extern
#endif
struct VirtualMachine* interpreterProxy;
static const char *moduleName =
#ifdef SQUEAK_BUILTIN_PLUGIN
	"FloatArrayPlugin VMMaker.oscog-eem.496 (i)"
#else
	"FloatArrayPlugin VMMaker.oscog-eem.496 (e)"
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

static sqInt
msg(char *s)
{
	fprintf(stderr, "\n%s: %s", moduleName, s);
	return 0;
}


/*	Primitive. Add the receiver and the argument, both FloatArrays and store
	the result into the receiver.
 */

EXPORT(sqInt)
primitiveAddFloatArray(void)
{
    sqInt arg;
    float *argPtr;
    sqInt i;
    sqInt length;
    sqInt rcvr;
    float *rcvrPtr;

	arg = stackObjectValue(0);
	rcvr = stackObjectValue(1);
	if (failed()) {
		return null;
	}
	success(isWords(arg));
	success(isWords(rcvr));
	if (failed()) {
		return null;
	}
	length = stSizeOf(arg);
	success(length == (stSizeOf(rcvr)));
	if (failed()) {
		return null;
	}
	rcvrPtr = ((float *) (firstIndexableField(rcvr)));
	argPtr = ((float *) (firstIndexableField(arg)));
	for (i = 0; i <= (length - 1); i += 1) {
		rcvrPtr[i] = ((((double) (rcvrPtr[i]))) + (((double) (argPtr[i]))));
	}
	pop(1);
}


/*	Primitive. Add the argument, a scalar value to the receiver, a FloatArray */

EXPORT(sqInt)
primitiveAddScalar(void)
{
    sqInt i;
    sqInt length;
    sqInt rcvr;
    float *rcvrPtr;
    double  value;

	value = stackFloatValue(0);
	rcvr = stackObjectValue(1);
	if (failed()) {
		return null;
	}
	success(isWords(rcvr));
	if (failed()) {
		return null;
	}
	length = stSizeOf(rcvr);
	rcvrPtr = ((float *) (firstIndexableField(rcvr)));
	for (i = 0; i <= (length - 1); i += 1) {
		rcvrPtr[i] = ((((double) (rcvrPtr[i]))) + value);
	}
	pop(1);
}

EXPORT(sqInt)
primitiveAt(void)
{
    float *floatPtr;
    double  floatValue;
    sqInt index;
    sqInt rcvr;

	index = stackIntegerValue(0);
	rcvr = stackObjectValue(1);
	if (failed()) {
		return null;
	}
	success(isWords(rcvr));
	success((index > 0)
	 && (index <= (slotSizeOf(rcvr))));
	if (failed()) {
		return null;
	}
	floatPtr = firstIndexableField(rcvr);
	floatValue = ((double) (floatPtr[index - 1]) );
	pop(2);
	pushFloat(floatValue);
}

EXPORT(sqInt)
primitiveAtPut(void)
{
    float *floatPtr;
    double  floatValue;
    sqInt index;
    sqInt rcvr;
    sqInt value;

	value = stackValue(0);
	if (isIntegerObject(value)) {
		floatValue = ((double) (integerValueOf(value)) );
	}
	else {
		floatValue = floatValueOf(value);
	}
	index = stackIntegerValue(1);
	rcvr = stackObjectValue(2);
	if (failed()) {
		return null;
	}
	success(isWords(rcvr));
	success((index > 0)
	 && (index <= (slotSizeOf(rcvr))));
	if (failed()) {
		return null;
	}
	floatPtr = firstIndexableField(rcvr);
	floatPtr[index - 1] = (((float) floatValue));
	if (!(failed())) {
		popthenPush(3, value);
	}
}


/*	Primitive. Add the receiver and the argument, both FloatArrays and store
	the result into the receiver.
 */

EXPORT(sqInt)
primitiveDivFloatArray(void)
{
    sqInt arg;
    float *argPtr;
    sqInt i;
    sqInt length;
    sqInt rcvr;
    float *rcvrPtr;

	arg = stackObjectValue(0);
	rcvr = stackObjectValue(1);
	if (failed()) {
		return null;
	}
	success(isWords(arg));
	success(isWords(rcvr));
	if (failed()) {
		return null;
	}
	length = stSizeOf(arg);
	success(length == (stSizeOf(rcvr)));
	if (failed()) {
		return null;
	}
	rcvrPtr = ((float *) (firstIndexableField(rcvr)));

	/* Check if any of the argument's values is zero */

	argPtr = ((float *) (firstIndexableField(arg)));
	for (i = 0; i <= (length - 1); i += 1) {
		if ((intAtPointer(((char*) (argPtr + i)))) == 0) {
			return primitiveFail();
		}
	}
	for (i = 0; i <= (length - 1); i += 1) {
		rcvrPtr[i] = ((((double) (rcvrPtr[i]))) / (((double) (argPtr[i]))));
	}
	pop(1);
}


/*	Primitive. Add the argument, a scalar value to the receiver, a FloatArray */

EXPORT(sqInt)
primitiveDivScalar(void)
{
    sqInt i;
    double  inverse;
    sqInt length;
    sqInt rcvr;
    float *rcvrPtr;
    double  value;

	value = stackFloatValue(0);
	rcvr = stackObjectValue(1);
	if (failed()) {
		return null;
	}
	if (value == 0.0) {
		return primitiveFail();
	}
	success(isWords(rcvr));
	if (failed()) {
		return null;
	}
	length = stSizeOf(rcvr);
	rcvrPtr = ((float *) (firstIndexableField(rcvr)));
	inverse = 1.0 / value;
	for (i = 0; i <= (length - 1); i += 1) {
		rcvrPtr[i] = ((((double) (rcvrPtr[i]))) * inverse);
	}
	pop(1);
}


/*	Primitive. Compute the dot product of the receiver and the argument.
	The dot product is defined as the sum of the products of the individual
	elements. 
 */

EXPORT(sqInt)
primitiveDotProduct(void)
{
    sqInt arg;
    float *argPtr;
    sqInt i;
    sqInt length;
    sqInt rcvr;
    float *rcvrPtr;
    double  result;

	arg = stackObjectValue(0);
	rcvr = stackObjectValue(1);
	if (failed()) {
		return null;
	}
	success(isWords(arg));
	success(isWords(rcvr));
	if (failed()) {
		return null;
	}
	length = stSizeOf(arg);
	success(length == (stSizeOf(rcvr)));
	if (failed()) {
		return null;
	}
	rcvrPtr = ((float *) (firstIndexableField(rcvr)));
	argPtr = ((float *) (firstIndexableField(arg)));
	result = 0.0;
	for (i = 0; i <= (length - 1); i += 1) {
		result += (((double) (rcvrPtr[i]))) * (((double) (argPtr[i])));
	}
	pop(2);
	pushFloat(result);
}

EXPORT(sqInt)
primitiveEqual(void)
{
    sqInt arg;
    float *argPtr;
    sqInt i;
    sqInt length;
    sqInt rcvr;
    float *rcvrPtr;

	arg = stackObjectValue(0);
	rcvr = stackObjectValue(1);
	if (failed()) {
		return null;
	}
	success(isWords(arg));
	success(isWords(rcvr));
	if (failed()) {
		return null;
	}
	pop(2);
	length = stSizeOf(arg);
	if (!(length == (stSizeOf(rcvr)))) {
		return pushBool(0);
	}
	rcvrPtr = ((float *) (firstIndexableField(rcvr)));
	argPtr = ((float *) (firstIndexableField(arg)));
	for (i = 0; i <= (length - 1); i += 1) {
		if (!((rcvrPtr[i]) == (argPtr[i]))) {
			return pushBool(0);
		}
	}
	return pushBool(1);
}

EXPORT(sqInt)
primitiveHashArray(void)
{
    sqInt i;
    sqInt length;
    sqInt rcvr;
    int *rcvrPtr;
    sqInt result;

	rcvr = stackObjectValue(0);
	if (failed()) {
		return null;
	}
	success(isWords(rcvr));
	if (failed()) {
		return null;
	}
	length = stSizeOf(rcvr);
	rcvrPtr = ((int *) (firstIndexableField(rcvr)));
	result = 0;
	for (i = 0; i <= (length - 1); i += 1) {
		result += rcvrPtr[i];
	}
	pop(1);
	return pushInteger(result & 0x1FFFFFFF);
}


/*	Primitive. Compute the length of the argument (sqrt of sum of component
	squares). 
 */

EXPORT(sqInt)
primitiveLength(void)
{
    sqInt i;
    sqInt length;
    sqInt rcvr;
    float *rcvrPtr;
    double  result;

	rcvr = stackObjectValue(0);
	if (failed()) {
		return null;
	}
	success(isWords(rcvr));
	if (failed()) {
		return null;
	}
	length = stSizeOf(rcvr);
	success(1);
	rcvrPtr = ((float *) (firstIndexableField(rcvr)));
	result = 0.0;
	for (i = 0; i <= (length - 1); i += 1) {
		result += (((double) (rcvrPtr[i]))) * (((double) (rcvrPtr[i])));
	}
	result = sqrt(result);
	popthenPush(1, floatObjectOf(result));
}


/*	Primitive. Add the receiver and the argument, both FloatArrays and store
	the result into the receiver.
 */

EXPORT(sqInt)
primitiveMulFloatArray(void)
{
    sqInt arg;
    float *argPtr;
    sqInt i;
    sqInt length;
    sqInt rcvr;
    float *rcvrPtr;

	arg = stackObjectValue(0);
	rcvr = stackObjectValue(1);
	if (failed()) {
		return null;
	}
	success(isWords(arg));
	success(isWords(rcvr));
	if (failed()) {
		return null;
	}
	length = stSizeOf(arg);
	success(length == (stSizeOf(rcvr)));
	if (failed()) {
		return null;
	}
	rcvrPtr = ((float *) (firstIndexableField(rcvr)));
	argPtr = ((float *) (firstIndexableField(arg)));
	for (i = 0; i <= (length - 1); i += 1) {
		rcvrPtr[i] = ((((double) (rcvrPtr[i]))) * (((double) (argPtr[i]))));
	}
	pop(1);
}


/*	Primitive. Add the argument, a scalar value to the receiver, a FloatArray */

EXPORT(sqInt)
primitiveMulScalar(void)
{
    sqInt i;
    sqInt length;
    sqInt rcvr;
    float *rcvrPtr;
    double  value;

	value = stackFloatValue(0);
	rcvr = stackObjectValue(1);
	if (failed()) {
		return null;
	}
	success(isWords(rcvr));
	if (failed()) {
		return null;
	}
	length = stSizeOf(rcvr);
	rcvrPtr = ((float *) (firstIndexableField(rcvr)));
	for (i = 0; i <= (length - 1); i += 1) {
		rcvrPtr[i] = ((((double) (rcvrPtr[i]))) * value);
	}
	pop(1);
}


/*	Primitive. Normalize the argument (A FloatArray) in place. */

EXPORT(sqInt)
primitiveNormalize(void)
{
    sqInt i;
    double  len;
    sqInt length;
    sqInt rcvr;
    float *rcvrPtr;

	rcvr = stackObjectValue(0);
	if (failed()) {
		return null;
	}
	success(isWords(rcvr));
	if (failed()) {
		return null;
	}
	length = stSizeOf(rcvr);
	success(1);
	rcvrPtr = ((float *) (firstIndexableField(rcvr)));
	len = 0.0;
	for (i = 0; i <= (length - 1); i += 1) {
		len += (((double) (rcvrPtr[i]))) * (((double) (rcvrPtr[i])));
	}
	success(len > 0.0);
	if (failed()) {
		return null;
	}
	len = sqrt(len);
	for (i = 0; i <= (length - 1); i += 1) {
		rcvrPtr[i] = ((((double) (rcvrPtr[i]))) / len);
	}
}


/*	Primitive. Add the receiver and the argument, both FloatArrays and store
	the result into the receiver.
 */

EXPORT(sqInt)
primitiveSubFloatArray(void)
{
    sqInt arg;
    float *argPtr;
    sqInt i;
    sqInt length;
    sqInt rcvr;
    float *rcvrPtr;

	arg = stackObjectValue(0);
	rcvr = stackObjectValue(1);
	if (failed()) {
		return null;
	}
	success(isWords(arg));
	success(isWords(rcvr));
	if (failed()) {
		return null;
	}
	length = stSizeOf(arg);
	success(length == (stSizeOf(rcvr)));
	if (failed()) {
		return null;
	}
	rcvrPtr = ((float *) (firstIndexableField(rcvr)));
	argPtr = ((float *) (firstIndexableField(arg)));
	for (i = 0; i <= (length - 1); i += 1) {
		rcvrPtr[i] = ((((double) (rcvrPtr[i]))) - (((double) (argPtr[i]))));
	}
	pop(1);
}


/*	Primitive. Add the argument, a scalar value to the receiver, a FloatArray */

EXPORT(sqInt)
primitiveSubScalar(void)
{
    sqInt i;
    sqInt length;
    sqInt rcvr;
    float *rcvrPtr;
    double  value;

	value = stackFloatValue(0);
	rcvr = stackObjectValue(1);
	if (failed()) {
		return null;
	}
	success(isWords(rcvr));
	if (failed()) {
		return null;
	}
	length = stSizeOf(rcvr);
	rcvrPtr = ((float *) (firstIndexableField(rcvr)));
	for (i = 0; i <= (length - 1); i += 1) {
		rcvrPtr[i] = ((((double) (rcvrPtr[i]))) - value);
	}
	pop(1);
}


/*	Primitive. Find the sum of each float in the receiver, a FloatArray, and
	stash the result into the argument Float.
 */

EXPORT(sqInt)
primitiveSum(void)
{
    sqInt i;
    sqInt length;
    sqInt rcvr;
    float *rcvrPtr;
    double  sum;

	rcvr = stackObjectValue(0);
	if (failed()) {
		return null;
	}
	success(isWords(rcvr));
	if (failed()) {
		return null;
	}
	length = stSizeOf(rcvr);
	rcvrPtr = ((float *) (firstIndexableField(rcvr)));
	sum = 0.0;
	for (i = 0; i <= (length - 1); i += 1) {
		sum += ((double) (rcvrPtr[i]));
	}
	popthenPush(1, floatObjectOf(sum));
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
		failed = interpreterProxy->failed;
		firstIndexableField = interpreterProxy->firstIndexableField;
		floatObjectOf = interpreterProxy->floatObjectOf;
		floatValueOf = interpreterProxy->floatValueOf;
		integerValueOf = interpreterProxy->integerValueOf;
		isIntegerObject = interpreterProxy->isIntegerObject;
		isWords = interpreterProxy->isWords;
		pop = interpreterProxy->pop;
		popthenPush = interpreterProxy->popthenPush;
		primitiveFail = interpreterProxy->primitiveFail;
		pushBool = interpreterProxy->pushBool;
		pushFloat = interpreterProxy->pushFloat;
		pushInteger = interpreterProxy->pushInteger;
		slotSizeOf = interpreterProxy->slotSizeOf;
		stSizeOf = interpreterProxy->stSizeOf;
		stackFloatValue = interpreterProxy->stackFloatValue;
		stackIntegerValue = interpreterProxy->stackIntegerValue;
		stackObjectValue = interpreterProxy->stackObjectValue;
		stackValue = interpreterProxy->stackValue;
		success = interpreterProxy->success;
#endif /* !defined(SQUEAK_BUILTIN_PLUGIN) */
	}
	return ok;
}


#ifdef SQUEAK_BUILTIN_PLUGIN

void* FloatArrayPlugin_exports[][3] = {
	{"FloatArrayPlugin", "getModuleName", (void*)getModuleName},
	{"FloatArrayPlugin", "primitiveAddFloatArray", (void*)primitiveAddFloatArray},
	{"FloatArrayPlugin", "primitiveAddScalar", (void*)primitiveAddScalar},
	{"FloatArrayPlugin", "primitiveAt", (void*)primitiveAt},
	{"FloatArrayPlugin", "primitiveAtPut", (void*)primitiveAtPut},
	{"FloatArrayPlugin", "primitiveDivFloatArray", (void*)primitiveDivFloatArray},
	{"FloatArrayPlugin", "primitiveDivScalar", (void*)primitiveDivScalar},
	{"FloatArrayPlugin", "primitiveDotProduct", (void*)primitiveDotProduct},
	{"FloatArrayPlugin", "primitiveEqual", (void*)primitiveEqual},
	{"FloatArrayPlugin", "primitiveHashArray", (void*)primitiveHashArray},
	{"FloatArrayPlugin", "primitiveLength", (void*)primitiveLength},
	{"FloatArrayPlugin", "primitiveMulFloatArray", (void*)primitiveMulFloatArray},
	{"FloatArrayPlugin", "primitiveMulScalar", (void*)primitiveMulScalar},
	{"FloatArrayPlugin", "primitiveNormalize", (void*)primitiveNormalize},
	{"FloatArrayPlugin", "primitiveSubFloatArray", (void*)primitiveSubFloatArray},
	{"FloatArrayPlugin", "primitiveSubScalar", (void*)primitiveSubScalar},
	{"FloatArrayPlugin", "primitiveSum", (void*)primitiveSum},
	{"FloatArrayPlugin", "setInterpreter", (void*)setInterpreter},
	{NULL, NULL, NULL}
};

#endif /* ifdef SQ_BUILTIN_PLUGIN */

#ifndef clox_object_h
#define clox_object_h

#include "common.h"
#include "chunk.h"
#include "value.h"

#define OBJ_TYPE(value)        (AS_OBJ(value)->type)

#define IS_CLOSURE(value)      isObjType(value, OBJ_CLOSURE)
#define IS_FUNCTION(value)     isObjType(value, OBJ_FUNCTION)
#define IS_NATIVE(value)       isObjType(value, OBJ_NATIVE)
#define IS_STRING(value)       isObjType(value, OBJ_STRING)

#define AS_CLOSURE(value)      ((ObjClosure*)AS_OBJ(value))
#define AS_FUNCTION(value)     ((ObjFunction*)AS_OBJ(value))
#define AS_NATIVE(value)       (AS_NATIVE_OBJ(value)->function)
#define AS_NATIVE_OBJ(value)   ((ObjNative*)AS_OBJ(value))
#define AS_STRING(value)       ((ObjString*)AS_OBJ(value))
#define AS_CSTRING(value)      (((ObjString*)AS_OBJ(value))->chars)

typedef struct ObjClosure ObjClosure;
typedef struct ObjFunction ObjFunction;
typedef struct ObjNative ObjNative;
typedef struct ObjUpvalue ObjUpvalue;
typedef enum {
  OBJ_CLOSURE,
  OBJ_FUNCTION,
  OBJ_NATIVE,
  OBJ_STRING,
  OBJ_UPVALUE,
} ObjType;

typedef bool (*NativeFn)(int argCount, Value* args,
                         Value* result);

struct Obj {
  ObjType type;
  bool isMarked;
  int refCount;
  struct Obj* next;
};

struct ObjFunction {
  Obj obj;
  int arity;
  int upvalueCount;
  Chunk chunk;
  ObjString* name;
};

struct ObjNative {
  Obj obj;
  int arity;
  NativeFn function;
};

struct ObjString {
  Obj obj;
  int length;
  char* chars;
  uint32_t hash;
};

struct ObjUpvalue {
  Obj obj;
  Value* location;
  Value closed;
  ObjUpvalue* next;
};

struct ObjClosure {
  Obj obj;
  ObjFunction* function;
  ObjUpvalue** upvalues;
  int upvalueCount;
};

ObjClosure* newClosure(ObjFunction* function);
ObjFunction* newFunction();
ObjNative* newNative(int arity, NativeFn function);
ObjUpvalue* newUpvalue(Value* slot);
ObjString* takeString(char* chars, int length);
ObjString* copyString(const char* chars, int length);
void printObject(Value value);
void retainObject(Obj* obj);
void releaseObject(Obj* obj);

static inline bool isObjType(Value value, ObjType type) {
  return IS_OBJ(value) && AS_OBJ(value)->type == type;
}

#endif

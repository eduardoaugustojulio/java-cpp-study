#include  "foo.h"

#include "FooClass_jni.h"

static jfieldID _get_self_id(JNIEnv *env, jobject thisObj)
{
    static int init = 0;
    static jfieldID fidSelfPtr;
    if(!init)
    {
        jclass thisClass = env->GetObjectClass(thisObj);
        fidSelfPtr = env->GetFieldID(thisClass, "self_ptr", "J");
    }
    return fidSelfPtr;
}
static Foo *_get_self(JNIEnv *env, jobject thisObj)
{
    jlong selfPtr = env->GetLongField(thisObj, _get_self_id(env, thisObj));
	return *(Foo**)&selfPtr;
}

static void _set_self(JNIEnv *env, jobject thisObj, Foo *self)
{
    jlong selfPtr = *(jlong*)&self;
    env->SetLongField(thisObj, _get_self_id(env, thisObj), selfPtr);
}


JNIEXPORT void JNICALL Java_arm_test_lib_Foo_init(JNIEnv *env, jobject thisObj, jint nb)
{
	Foo *self = new Foo(nb);
    _set_self(env, thisObj, self);
}

JNIEXPORT jint JNICALL Java_arm_test_lib_Foo_getValue(JNIEnv *env, jobject thisObj)
{
	Foo *self = _get_self(env, thisObj);
    return self->getValue();
}

JNIEXPORT void JNICALL Java_arm_test_lib_Foo_increment(JNIEnv *env, jobject thisObj)
{
	Foo *self = _get_self(env, thisObj);
    self->increment();
}

JNIEXPORT void JNICALL Java_arm_test_lib_Foo_finalize(JNIEnv *env, jobject thisObj)
{
	Foo *self = _get_self(env, thisObj);
    if(self != NULL)
    {
        delete self;
        _set_self(env, thisObj, NULL);
    }
}

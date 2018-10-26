#include <jni.h>
#include <string>

extern "C"
JNIEXPORT jstring JNICALL
Java_com_mtcle_jni_MNativeUtil_getStringFromJNI(JNIEnv *env, jobject instance) {
    std::string strInC = "C++中的字符串";//无参数，直接返回个c中的字符串给java使用
    return env->NewStringUTF(strInC.c_str());
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_mtcle_jni_MNativeUtil_getStringFromJNIWithParam(JNIEnv *env, jobject instance,
                                                         jstring key_) {
    const char *key = env->GetStringUTFChars(key_, 0);

    std::string strFull = "C++中字符串拼接java参数(";
    strFull.append(key);
    strFull.append(")");
    env->ReleaseStringUTFChars(key_, key);

    return env->NewStringUTF(strFull.c_str());
}
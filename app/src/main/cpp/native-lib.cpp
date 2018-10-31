#include <jni.h>
#include <string>

#include "utils.h"


extern "C"
JNIEXPORT jstring JNICALL
Java_com_mtcle_jni_MNativeUtil_getStringFromJNI(JNIEnv *env, jobject instance) {
    std::string strInC = "C++中的字符串";//无参数，直接返回个c中的字符串给java使用；
    // std:: 代表使用模板，就是类？ 调用了string这个类，new了个strInC的对象
            //基本类型的话 还是 int a=1； 这种方式定义
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

extern "C"
JNIEXPORT jstring JNICALL
Java_com_mtcle_jni_MNativeUtil_getStringFromJNIWithJavaMeth(JNIEnv *env, jobject instance) {
    std::string strNull = "[null]";
    //1 . 找到java代码的 class文件
    jclass mNativeUtil = env->FindClass("com/mtcle/jni/MNativeUtil");// 参数就是java类的路径加上名字
    if (mNativeUtil == 0) {
        // 找不到类，写错了？？注意包名，类名
        return env->NewStringUTF(strNull.c_str());
    }


    //2 寻找class里面的方法。。参数①：类名的引用，②准备调用Java类里面方法的名字，
    //③括号里面表示方法的要传入的参数类型，现在是空的
    // 括号外面  V   表示这个方法的返回值是  void  类型的
    //Z boolean
    //B byte
    //C char
    //S short
    //I int
    //J long
    //F float
    //D double
    //Ljava/lang/String  String String是对象类型，都需要这样搞
    jmethodID method1 = env->GetMethodID(mNativeUtil, "javaM", "()Ljava/lang/String;");
    if (method1 == 0) {
        // 找不到类，写错了？？注意方法的名字
        return env->NewStringUTF(strNull.c_str());
    }
    // 就这样  jmethodID method1 = env->GetMethodID(test,"helloFromJava","(I)V");

    //3 .调用这个方法（返回值是对象的用这个，是基本类型和void的有对应方法），
    // 参数说明  ②为方法的名字，如果有参数记得在后面填上，env->CallVoidMethod(obj,method1,10); // 10就是要传到Java方法里面的参数
    jobject result = env->CallObjectMethod(instance, method1);
    // 调用CallStaticObjectMethod方法会返回一个jobject对象，在前面弄个(jstring)就可以转换成jstring
    jstring resultStr = (jstring) result;
    return resultStr;
}


extern "C"
JNIEXPORT jstring JNICALL
Java_com_mtcle_jni_MNativeUtil_getStringFromJNIWithJavaMethWithCParma(JNIEnv *env,
                                                                      jobject instance) {

    LOGD("c中打印的日志");
    LOGE("c中打印的日志error");
    // TODO
    std::string strNull = "[null]";
    //1 . 找到java代码的 class文件
    jclass mNativeUtil = env->FindClass("com/mtcle/jni/MNativeUtil");// 参数就是java类的路径加上名字
    if (mNativeUtil == 0) {
        // 找不到类，写错了？？注意包名，类名
        return env->NewStringUTF(strNull.c_str());
    }
    jmethodID method1 = env->GetMethodID(mNativeUtil, "javaMWithP", "(ILjava/lang/String;)Ljava/lang/String;");//java方法签名，括号内挨着写，第一个参数是int、第二个参数是object（String），括号外是返回值，object类型（String）
    if (method1 == 0) {
        // 找不到类，写错了？？注意方法的名字
        return env->NewStringUTF(strNull.c_str());
    }
    std::string strP2 = "c中String参数";
    jobject result = env->CallObjectMethod(instance, method1, 110, env->NewStringUTF(strP2.c_str()));
    // 调用CallStaticObjectMethod方法会返回一个jobject对象，在前面弄个(jstring)就可以转换成jstring
    jstring resultStr = (jstring) result;

    // jstring 转 char*
    char *chardata = jstringToChar(env, resultStr);
    return env->NewStringUTF(chardata);
}
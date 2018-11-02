//
// Created by Lenovo on 2018/10/31.
//该工具类打造为好用的jni工具类
//

#include <jni.h>
#include <android/log.h>
#include <string>

using namespace std;
#ifndef JNILEARNING_UTILS_H
#define JNILEARNING_UTILS_H
const bool Jni_Debug = true;//native 中 是否打印日志
#define LOGD(...) if(Jni_Debug) __android_log_print(ANDROID_LOG_DEBUG, "mtcle_from_native", __VA_ARGS__)
#define LOGE(...) if(Jni_Debug) __android_log_print(ANDROID_LOG_ERROR, "mtcle_from_native", __VA_ARGS__)

//通用方法，javaString to c string
char *jstringToChar(JNIEnv *env, jstring jstr);



const char HexCode[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E',
                        'F'};

string getDefaultKey(JNIEnv *env, jobject arg, jobject mContext);

bool getSha1(JNIEnv *env, jobject clz, jobject context_object, const char *localSha14App);

#endif //JNILEARNING_UTILS_H

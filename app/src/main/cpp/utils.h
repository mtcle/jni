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
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, "mtcle_c", __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, "mtcle_c", __VA_ARGS__)
//通用方法，javaString to c string
char *jstringToChar(JNIEnv *env, jstring jstr);

string getDefaultKey(JNIEnv *env,jobject arg, jobject mContext);

#endif //JNILEARNING_UTILS_H

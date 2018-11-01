#include <jni.h>
#include <string>
#include "utils.h"


//
// Created by Lenovo on 2018/10/31.
//
int getVersionCode() {
    return 1;
}

char *jstringToChar(JNIEnv *env, jstring jstr) {
    char *rtn = NULL;
    jclass clsstring = env->FindClass("java/lang/String");
    jstring strencode = env->NewStringUTF("UTF-8");
    jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr = (jbyteArray) env->CallObjectMethod(jstr, mid, strencode);
    jsize alen = env->GetArrayLength(barr);
    jbyte *ba = env->GetByteArrayElements(barr, JNI_FALSE);
    if (alen > 0) {
        rtn = (char *) malloc(alen + 1);
        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }
    env->ReleaseByteArrayElements(barr, ba, 0);
    return rtn;
}

string getDefaultKey(JNIEnv *env, jobject arg, jobject mContext) {
    const char *sha1 = "209E11B09CA684B4A05E9531D6A49102A77A3B65";//调用者的签名，防止被第三方使用
    string eCs="MIICopIBADBCDgkqhkiG9w0BAQEFAASCAmAweeJcAgEAAoOIEWnLrNU4uFPSOkI9";//错误秘钥
    string sCs="123456";//正确的加密秘钥
    if (mContext == 0) {
        return eCs;//"[+] Error: Context is 0"
    }
    jclass clsContext = env->FindClass("android/content/Context");
    if (clsContext == 0) {
        return eCs;//"[+] Error: FindClass <android/content/Context> Error"
    }

//验证签名//com.mtcle.jni.utils
    jclass cerFingerprintsClass = env->FindClass("com/mtcle/jni/utils/CerFingerprintsUtil");
    jmethodID getCerSHA1 = (env)->GetStaticMethodID(cerFingerprintsClass, "getCerSHA1",
                                                    "(Landroid/content/Context;)Ljava/lang/String;");
    if (getCerSHA1 == 0) {
        LOGE("!cer");
        return eCs;
    }
    jobject cerSha1 = (env)->CallStaticObjectMethod(cerFingerprintsClass, getCerSHA1,
                                                    mContext);
    char *cerSha1Char = jstringToChar(env, (jstring) cerSha1);
    if (strcmp(sha1, cerSha1Char) != 0) {
        LOGE("签名有误");
        return eCs;//"[+] Error: sha1 not success"
    }
    //验证调用者身份是否合法
    jfieldID fVerId = (env)->GetStaticFieldID(cerFingerprintsClass, "serialVersionUID", "J");
    jlong iver = 119;//调用类的serialVersionUID，做了个判断，不知道有什么用
    jlong iversion = (env)->GetStaticLongField(cerFingerprintsClass, fVerId);
    if (iversion != iver) {
        LOGE("!iver");
        return eCs;
    }
    //正确
    LOGD("验证成功！");
    return sCs;
}

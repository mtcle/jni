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
    string eCs = "MIICopIBADBCDgkqhkiG9w0BAQEFAASCAmAweeJcAgEAAoOIEWnLrNU4uFPSOkI9";//错误秘钥
    string sCs = "12341234123412341234123412341234";//正确的加密秘钥,必须为32/48位等
    if (mContext == 0) {
        return eCs;//"[+] Error: Context is 0"
    }
    jclass clsContext = env->FindClass("android/content/Context");
    if (clsContext == 0) {
        return eCs;//"[+] Error: FindClass <android/content/Context> Error"
    }

    if (getSha1(env, arg, mContext, sha1)) {
        //LOGE("签名校验成功");
    } else {
        //LOGE("签名校验失败");
        return eCs;
    }
    return sCs;
}


bool getSha1(JNIEnv *env, jobject clz, jobject context_object, const char *localSha14App) {
    //const char *sha14app = "209E11B09CA684B4A05E9531D6A49102A77A3B65";//调用者的签名，防止被第三方使用
    char *mTAG = "SHA1";
    jclass context_class = env->GetObjectClass(context_object);

    //context.getPackageManager()
    jmethodID methodId = env->GetMethodID(context_class, "getPackageManager",
                                          "()Landroid/content/pm/PackageManager;");
    jobject package_manager_object = env->CallObjectMethod(context_object, methodId);
    if (package_manager_object == NULL) {
        LOGE("%s_%s", mTAG, "getPackageManager() Failed!");
        return false;
    }

    //context.getPackageName()
    methodId = env->GetMethodID(context_class, "getPackageName", "()Ljava/lang/String;");
    jstring package_name_string = (jstring) env->CallObjectMethod(context_object, methodId);
    if (package_name_string == NULL) {
        LOGE("%s_%s", mTAG, "getPackageName() Failed!");
        return false;
    }
    env->DeleteLocalRef(context_class);

    //PackageManager.getPackageInfo(Sting, int)
    //public static final int GET_SIGNATURES= 0x00000040;
    jclass pack_manager_class = env->GetObjectClass(package_manager_object);
    methodId = env->GetMethodID(pack_manager_class, "getPackageInfo",
                                "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");
    env->DeleteLocalRef(pack_manager_class);
    jobject package_info_object = env->CallObjectMethod(package_manager_object, methodId,
                                                        package_name_string, 0x40);
    if (package_info_object == NULL) {
        LOGE("%s_%s", mTAG, "getPackageInfo() Failed!");
        return false;
    }
    env->DeleteLocalRef(package_manager_object);

    //PackageInfo.signatures[0]
    jclass package_info_class = env->GetObjectClass(package_info_object);
    jfieldID fieldId = env->GetFieldID(package_info_class, "signatures",
                                       "[Landroid/content/pm/Signature;");
    env->DeleteLocalRef(package_info_class);
    jobjectArray signature_object_array = (jobjectArray) env->GetObjectField(package_info_object,
                                                                             fieldId);
    if (signature_object_array == NULL) {
        LOGE("%s_%s", mTAG, "PackageInfo.signatures[] is null");
        return false;
    }
    jobject signature_object = env->GetObjectArrayElement(signature_object_array, 0);
    env->DeleteLocalRef(package_info_object);

    //Signature.toByteArray()
    jclass signature_class = env->GetObjectClass(signature_object);
    methodId = env->GetMethodID(signature_class, "toByteArray", "()[B");
    env->DeleteLocalRef(signature_class);
    jbyteArray signature_byte = (jbyteArray) env->CallObjectMethod(signature_object, methodId);


    //new ByteArrayInputStream
    jclass byte_array_input_class = env->FindClass("java/io/ByteArrayInputStream");
    methodId = env->GetMethodID(byte_array_input_class, "<init>", "([B)V");
    jobject byte_array_input = env->NewObject(byte_array_input_class, methodId, signature_byte);
    env->DeleteLocalRef(byte_array_input_class);
    //CertificateFactory.getInstance("X.509")
    jclass certificate_factory_class = env->FindClass("java/security/cert/CertificateFactory");
    methodId = env->GetStaticMethodID(certificate_factory_class, "getInstance",
                                      "(Ljava/lang/String;)Ljava/security/cert/CertificateFactory;");
    jstring x_509_jstring = env->NewStringUTF("X.509");
    jobject cert_factory = env->CallStaticObjectMethod(certificate_factory_class, methodId,
                                                       x_509_jstring);

    //certFactory.generateCertificate(byteIn);
    methodId = env->GetMethodID(certificate_factory_class, "generateCertificate",
                                ("(Ljava/io/InputStream;)Ljava/security/cert/Certificate;"));
    jobject x509_cert = env->CallObjectMethod(cert_factory, methodId, byte_array_input);
    env->DeleteLocalRef(certificate_factory_class);
    //cert.getEncoded()
    jclass x509_cert_class = env->GetObjectClass(x509_cert);
    methodId = env->GetMethodID(x509_cert_class, "getEncoded", "()[B");
    jbyteArray cert_byte = (jbyteArray) env->CallObjectMethod(x509_cert, methodId);
    env->DeleteLocalRef(x509_cert_class);
    //MessageDigest.getInstance("SHA1")
    jclass message_digest_class = env->FindClass("java/security/MessageDigest");
    methodId = env->GetStaticMethodID(message_digest_class, "getInstance",
                                      "(Ljava/lang/String;)Ljava/security/MessageDigest;");
    jstring sha1_jstring = env->NewStringUTF("SHA1");
    jobject sha1_digest = env->CallStaticObjectMethod(message_digest_class, methodId, sha1_jstring);

    //sha1.digest (certByte)
    methodId = env->GetMethodID(message_digest_class, "digest", "([B)[B");
    jbyteArray sha1_byte = (jbyteArray) env->CallObjectMethod(sha1_digest, methodId, cert_byte);
    env->DeleteLocalRef(message_digest_class);

    //toHexString
    jsize array_size = env->GetArrayLength(sha1_byte);
    jbyte *sha1 = env->GetByteArrayElements(sha1_byte, NULL);

    char *hex_sha = (char *) malloc((sizeof(char) * (array_size * 2)) + 1);
    int i;
    for (i = 0; i < array_size; ++i) {
        hex_sha[2 * i] = HexCode[((unsigned char) sha1[i]) / 16];
        hex_sha[2 * i + 1] = HexCode[((unsigned char) sha1[i]) % 16];
    }
    hex_sha[array_size * 2] = '\0';
    //比较签名
    if (strcmp(hex_sha, localSha14App) == 0) {
        //LOGE("%s_%s", mTAG, "验证通过");
        return true;
    } else {
        LOGE("%s_app_%s", mTAG, hex_sha);
        LOGE("%s_loc_%s", mTAG, localSha14App);
        return false;
    }
}

string desEncode(JNIEnv *env, jstring javastr, string key) {
    // jstring 转 char*
    char *chardata = jstringToChar(env, javastr);
    // char* 转 string
    string origin = chardata;
    auto my3Des = new Des(key);
    string result = my3Des->desEncrypt(origin);
    if (result.length() == 0) {
        LOGE("加密出错");
        return "";
    }
    return result;
}

string desDecode(JNIEnv *env,jstring javastr,string key){
    // jstring 转 char*
    char* chardata = jstringToChar(env, javastr);
    // char* 转 string
    string origin = chardata;
    auto my3Des = new Des(key);
    string result=my3Des->desDecrypt(origin);
    if (result.length() == 0) {
        LOGE("解密出错");
        return "";
    }
    return result;
}
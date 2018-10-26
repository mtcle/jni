package com.mtcle.jni;

/**
 * 作者：Lenovo on 2018/10/26 14:12
 * <p>
 * 邮箱：mtcle@126.com
 * <p>
 * 描述：
 */
public class MNativeUtil {
    /**获取c中的字符串*/
    public native String getStringFromJNI();

    /**获取c中的字符串，简单传参数拼接*/
    public native String getStringFromJNIWithParam(String key);
}

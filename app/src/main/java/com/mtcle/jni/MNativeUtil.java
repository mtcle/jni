package com.mtcle.jni;

import android.util.Log;

/**
 * 作者：Lenovo on 2018/10/26 14:12
 * <p>
 * 邮箱：mtcle@126.com
 * <p>
 * 描述：
 */
public class MNativeUtil {
    /**
     * 获取c中的字符串
     */
    public native String getStringFromJNI();

    /**
     * 获取c中的字符串，简单传参数拼接
     */
    public native String getStringFromJNIWithParam(String key);

    /**
     * c中调用java方法获得参数，进行处理后返回给java
     *
     * @return
     */
    public native String getStringFromJNIWithJavaMeth();

    public String javaM() {
        Log.e("mtcle", "java方法javaM被调用！");
        return "java中文";
    }
}

package com.mtcle.jni;

import android.content.Context;
import android.widget.Toast;

/**
 * 作者：Lenovo on 2018/10/26 15:10
 * <p>
 * 邮箱：mtcle@126.com
 * <p>
 * 描述：
 */
public class ViewUtils {
    public static void showToast(Context context, String content) {
        Toast.makeText(context, content, Toast.LENGTH_LONG).show();
    }
}

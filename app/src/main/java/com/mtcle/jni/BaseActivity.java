package com.mtcle.jni;

import android.content.Context;
import android.os.Bundle;
import android.os.PersistableBundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;

/**
 * 作者：Lenovo on 2018/10/26 15:07
 * <p>
 * 邮箱：mtcle@126.com
 * <p>
 * 描述：
 */
public class BaseActivity extends AppCompatActivity {

    protected Context mContext;
    protected MNativeUtil mNativeUtil = new MNativeUtil();

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mContext = this;
    }
}

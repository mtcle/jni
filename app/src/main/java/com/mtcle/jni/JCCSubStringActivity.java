package com.mtcle.jni;

import android.os.Bundle;
import android.view.View;

public class JCCSubStringActivity extends BaseActivity implements View.OnClickListener {


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_javacallc_sub_string);
        findViewById(R.id.btn_string).setOnClickListener(this);
        findViewById(R.id.btn_string_p).setOnClickListener(this);

    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.btn_string:
                ViewUtils.showToast(mContext, mNativeUtil.getStringFromJNI());
                break;
            case R.id.btn_string_p:
                ViewUtils.showToast(mContext, mNativeUtil.getStringFromJNIWithParam("java参数"));
                break;
        }
    }
}

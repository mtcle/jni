package com.mtcle.jni;

import android.os.Bundle;
import android.util.Log;
import android.view.View;

import com.mtcle.jni.utils.MNativeUtil;

public class JCCSubEncrypteActivity extends BaseActivity implements View.OnClickListener {


    private MNativeUtil mNativeUtil = new MNativeUtil();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_javacallc_sub_encrypted);
        findViewById(R.id.btn_md5).setOnClickListener(this);
        findViewById(R.id.btn_hash).setOnClickListener(this);
        findViewById(R.id.btn_aes).setOnClickListener(this);
        findViewById(R.id.btn_3des).setOnClickListener(this);
        findViewById(R.id.btn_rsa).setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.btn_md5:
                //ViewUtils.showToast(mContext, mNativeUtil.getStringFromJNI());
                break;
            case R.id.btn_hash:
                String strKey = mNativeUtil.getDefaultKeyFromC(JCCSubEncrypteActivity.this);
                Log.d("mtcle", "返回的key：" + strKey);
                ViewUtils.showToast(mContext, "秘钥：" + strKey);
                break;
            case R.id.btn_aes:
                // ViewUtils.showToast(mContext, mNativeUtil.getStringFromJNIWithParam("java参数"));
                break;
            case R.id.btn_3des:
                // ViewUtils.showToast(mContext, mNativeUtil.getStringFromJNIWithParam("java参数"));
                break;
            case R.id.btn_rsa:
                // ViewUtils.showToast(mContext, mNativeUtil.getStringFromJNIWithParam("java参数"));
                break;
        }
    }
}

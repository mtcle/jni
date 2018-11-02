package com.mtcle.jni;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.EditText;

import com.mtcle.jni.utils.MNativeUtil;

public class JCCSubEncrypteActivity extends BaseActivity implements View.OnClickListener {


    private MNativeUtil mNativeUtil = new MNativeUtil();

    private EditText et_inputText;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_javacallc_sub_encrypted);
        findViewById(R.id.btn_md5).setOnClickListener(this);
        findViewById(R.id.btn_hash).setOnClickListener(this);
        findViewById(R.id.btn_aes).setOnClickListener(this);
        findViewById(R.id.btn_3des).setOnClickListener(this);
        findViewById(R.id.btn_3des_jiemi).setOnClickListener(this);
        findViewById(R.id.btn_rsa).setOnClickListener(this);
        et_inputText = findViewById(R.id.et_inputText);
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
                String strMingwen = et_inputText.getText().toString();
                if (strMingwen.isEmpty()) {
                    ViewUtils.showToast(mContext, "请输入要加密的内容");
                    return;
                }
                String str = mNativeUtil.desEncrypt(JCCSubEncrypteActivity.this, strMingwen);
                Log.d("mtcle", "加密后：" + str);
                et_inputText.setText(str);
                ViewUtils.showToast(mContext, "3des加密后：" + str);
                break;
            case R.id.btn_3des_jiemi:
                String strMiwen = et_inputText.getText().toString();
                if (strMiwen.isEmpty()) {
                    ViewUtils.showToast(mContext, "请先加密");
                    return;
                }
                String str2 = mNativeUtil.desDeEncrypt(JCCSubEncrypteActivity.this, strMiwen);
                Log.d("mtcle", "解密后：" + str2);
                et_inputText.setText(str2);
                ViewUtils.showToast(mContext, "3des解密后：" + str2);
                break;
            case R.id.btn_rsa:
                // ViewUtils.showToast(mContext, mNativeUtil.getStringFromJNIWithParam("java参数"));
                break;
        }
    }
}

package com.mtcle.jni;

import android.content.Intent;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

/**
 * 作者：Lenovo on 2018/10/26 14:39
 * <p>
 * 邮箱：mtcle@126.com
 * <p>
 * 描述：
 */
public class JavaCallNativeFragment extends Fragment implements View.OnClickListener {
    /**
     * The fragment argument representing the section number for this
     * fragment.
     */
    private static final String ARG_SECTION_NUMBER = "section_number";

    public JavaCallNativeFragment() {
    }

    /**
     * Returns a new instance of this fragment for the given section
     * number.
     */
    public static JavaCallNativeFragment newInstance(int sectionNumber) {
        JavaCallNativeFragment fragment = new JavaCallNativeFragment();
        Bundle args = new Bundle();
        args.putInt(ARG_SECTION_NUMBER, sectionNumber);
        fragment.setArguments(args);
        return fragment;
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View rootView = inflater.inflate(R.layout.fragment_javacallc, container, false);
        //TextView textView = (TextView) rootView.findViewById(R.id.section_label);
        //textView.setText(getString(R.string.section_format, getArguments().getInt(ARG_SECTION_NUMBER)));
        initUi(rootView);
        return rootView;
    }

    private void initUi(View rootView) {
        rootView.findViewById(R.id.btn_string).setOnClickListener(this);
        rootView.findViewById(R.id.btn_encryption).setOnClickListener(this);
    }


    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.btn_string:
                startActivity(new Intent(getContext(), JCCSubStringActivity.class));
                break;
            case R.id.btn_encryption:
                startActivity(new Intent(getContext(), JCCSubEncrypteActivity.class));
                break;
        }
    }
}

package com.androidyuan.aesjniencrypt;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.Toast;
import com.androidyuan.aesjni.AESEncrypt;
import com.androidyuan.aesjni.SignatureTool;

import android.util.Log;

public class MainActivity extends AppCompatActivity {

    private final String str = "123abcABC*%!~#+_/中文测试";
    private final String ecode = "SkiDk/JC5F/BXKf/np7rWNub7ibxzYMjKwkQ7A6AqPw=";

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //下面的密文对应的原文：123abcABC&*(@#@#@)+_/中文测试
        //String code = AESEncrypt.encode(this, str);
        String code = AESEncrypt.decode(this, ecode);

        Log.i("code", code + "");

    }


    private void toast(String str)
    {
        Toast.makeText(this,str, Toast.LENGTH_LONG).show();
    }
}

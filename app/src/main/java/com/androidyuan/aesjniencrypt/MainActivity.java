package com.androidyuan.aesjniencrypt;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.widget.Toast;

import com.androidyuan.aesjni.AESEncrypt;

public class MainActivity extends AppCompatActivity {

    private final String str = "123abcABC*%!~#+_/中文测试";
    private final String encodeStr = "1cad994119e4f3038fe29e34a4a12ce8a4b28f06db7682ab9d4f775c0e25659b01da27db09368eb3778ccea063";

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //下面的密文对应的原文：123abcABC&*(@#@#@)+_/中文测试
        final String code = AESEncrypt.encode(this, str);
        Log.i("code", code + "");
        final String decode = AESEncrypt.decode(this, encodeStr);
        Log.i("decode", decode + "");


    }


    private void toast(String str)
    {
        Toast.makeText(this,str, Toast.LENGTH_LONG).show();
    }
}

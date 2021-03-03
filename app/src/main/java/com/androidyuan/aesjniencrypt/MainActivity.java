package com.androidyuan.aesjniencrypt;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.widget.Toast;

import com.androidyuan.aesjni.EncryptEntry;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = "CHACHA20-Test";

    private final static String str = "123abcABC*%!~#+_/中文测试";
    private final static String strNewline = "1MTIzYWJjQUJDKiUhfiMrXy/kuK3mlofmtYvor5UK";//base64("23abcABC*%!~#+_/中文测试\n")
    private final static String strBlank = "MTIzYWJjQUJDKiUhfiMrXy/kuK3mlofmtYvor5Ug";//base64("123abcABC*%!~#+_/中文测试 ")
    private final static String encodeStr = "1cad994119e4f3038fe29e34a4a12ce8a4b28f06db7682ab9d4f775c0e25659b01da27db09368eb3778ccea063";
    private final static String encodeStrNewline = "1cd2fe6901dee50ba699ee5f9ec96ee2e3305ee64fb87c6243b1d4c0f64476b6f9cf13b2343d88a58bf38caa3b7c92290eda1591a6b9a671cd";
    private final static String encodeStrBlank = "60cbe35a22d0f82b9d9df15191eb52dfed3f7ad965992a265d8fac9ef7477fbde0e23cab297ae8979acfe597a7e0b68e91a7da98b71aa4d3";

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        String code = EncryptEntry.encode(MainActivity.this.getApplicationContext(), str);
        Log.i(TAG, "code " + code + "");
        code = EncryptEntry.encode(MainActivity.this.getApplicationContext(), strNewline);
        Log.i(TAG, "code " + code + "");
        code = EncryptEntry.encode(MainActivity.this.getApplicationContext(), strBlank);
        Log.i(TAG, "code " + code + "");


        String decode = EncryptEntry.decode(MainActivity.this.getApplicationContext(), encodeStr);
        Log.i(TAG, "decode \"" + decode + "\"");
        decode = EncryptEntry.decode(MainActivity.this.getApplicationContext(), encodeStrNewline);
        Log.i(TAG, "decode \"" + decode + "\"");
        decode = EncryptEntry.decode(MainActivity.this.getApplicationContext(), encodeStrBlank);
        Log.i(TAG, "decode \"" + decode + "\"");

    }


    private void toast(String str) {
        Toast.makeText(this, str, Toast.LENGTH_LONG).show();
    }
}

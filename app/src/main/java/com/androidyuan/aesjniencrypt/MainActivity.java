package com.androidyuan.aesjniencrypt;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.widget.Toast;

import com.androidyuan.aesjni.EncryptEntry;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = "CHACHA20-Test";

    private final static String str = "123abcABC*%!~#+_/中文测试";
    private final static String encodeStr = "1cad994119e4f3038fe29e34a4a12ce8a4b28f06db7682ab9d4f775c0e25659b01da27db09368eb3778ccea063";

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        final String code = EncryptEntry.encode(MainActivity.this.getApplicationContext(), str);
        Log.i(TAG, "code" + code + "");
        final String decode = EncryptEntry.decode(MainActivity.this.getApplicationContext(), encodeStr);
        Log.i(TAG, "decode " + decode + "");

    }


    private void toast(String str) {
        Toast.makeText(this, str, Toast.LENGTH_LONG).show();
    }
}

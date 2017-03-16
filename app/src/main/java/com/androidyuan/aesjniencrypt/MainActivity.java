package com.androidyuan.aesjniencrypt;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.Toast;
import com.androidyuan.aesjni.AESEncrypt;
import com.androidyuan.aesjni.SignatureTool;

import android.util.Log;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

//        toast(AESEncrypt.encode(this, "1") + "");

        //toast(SignatureTool.getSignature(this)+"");

        Log.d("thisHascode", SignatureTool.getSignature(this) + "");

        toast(AESEncrypt.checkSignature(this)+"");
    }


    void toast(String str)
    {
        Toast.makeText(this,str, Toast.LENGTH_LONG).show();
    }
}

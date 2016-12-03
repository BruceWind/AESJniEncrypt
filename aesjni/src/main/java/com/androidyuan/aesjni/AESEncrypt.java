package com.androidyuan.aesjni;

/**
 * Created by wei on 16-12-2.
 */

public class AESEncrypt {

    static {
        System.loadLibrary("JNIEncrypt");
    }

    public static native  String  encode(String str);

    public static native String decode(String str);

}

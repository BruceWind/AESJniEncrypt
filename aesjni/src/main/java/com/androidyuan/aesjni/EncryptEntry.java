package com.androidyuan.aesjni;

/**
 * Created by wei on 16-12-2.
 * key is stored in JNIEncrypt.c, you may need to change it.
 *
 * @Date: 21-02-22:
 * AES algorithm has been instead with chacha20.
 * And algorithm is written by libsodium.
 */
public class EncryptEntry {

    static {
        System.loadLibrary("JNIEncrypt");
    }

    /**
     * AES加密
     *
     * @param context
     * @param str
     * @return
     */
    public static native String encode(Object context, String str);


    /**
     * chacha20 decrypt
     *
     * @param context
     * @return WRONG_SIGNATURE ： sign not pass .
     */
    public static native String decode(Object context, String str);


    /**
     * 检查 打包签名是否 是正确的 防止被二次打包
     *
     * @param context
     * @return 1 : pass ， -1 or  -2 : error.
     */
    public static native int checkSignature(Object context);

}

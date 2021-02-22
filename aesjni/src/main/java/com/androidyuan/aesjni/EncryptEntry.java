package com.androidyuan.aesjni;

/**
 * Created by wei on 16-12-2.
 *
 * 秘文的key 在 C 的代码，如需修改请先修改JNIEncrypt.c
 * 另外native做了签名校验
 *
 * @Date: 21-02-22:
 * AES algorithm has been instead with chacha20.
 * And algorithm is written by libsodium.
 *
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
     * AES 解密
     *
     * @param context
     * @param str
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

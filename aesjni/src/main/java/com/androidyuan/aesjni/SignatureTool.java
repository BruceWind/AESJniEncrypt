package com.androidyuan.aesjni;

import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.Signature;

/**
 * Created by wei on 16-12-4.
 * Please use this class to read hash of the current apk signature file, and then copy the hash to check_signature.h;
 * 请您使用这个类读取当前apk签名文件的hash值，然后拷贝hash写入到check_signature.h;
 */

public class SignatureTool {

    private static final String PKGNAME = "com.androidyuan.aesjniencrypt";


    /* 1.如果包名不存在 就会报错  return -1
    System.err:     android.content.pm.PackageManager$NameNotFoundException: [配置包名]
    System.err:     at android.app.ApplicationPackageManager.getPackageInfo(ApplicationPackageManager.java:137)

     2.如果配置包名不是当前进程的包名 那么，也不会报错。
        这点我觉得奇怪 居然可以取得别人的包的keystore的hash
    */
    public static int getSignature(Context context) {

        try {
            PackageInfo packageInfo =
                    context.
                            getPackageManager().
                            getPackageInfo(PKGNAME, PackageManager.GET_SIGNATURES);

            Signature[] signs = packageInfo.signatures;
            Signature sign = signs[0];
            return sign.hashCode();
        }
        catch (Exception e) {
            e.printStackTrace();
        }
        return -1;
    }

}

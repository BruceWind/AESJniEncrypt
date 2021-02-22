package com.androidyuan.aesjni;

import android.support.test.runner.AndroidJUnit4;

import org.junit.Test;
import org.junit.runner.RunWith;

import static org.junit.Assert.assertEquals;

/**
 * Instrumentation test, which will execute on an Android device.
 *
 * @see <a href="http://d.android.com/tools/testing">Testing documentation</a>
 */
@RunWith(AndroidJUnit4.class)
public class JNITest {

    private final String plain = "123abcABC*%!~#+_/中文测试";
    private final String encodeStr = "1cad994119e4f3038fe29e34a4a12ce8a4b28f06db7682ab9d4f775c0e25659b01da27db09368eb3778ccea063";
    @Test
    public void useAppContext() throws Exception {

        //plain：123abcABC&*(@#@#@)+_/中文测试
        final String code = AESEncrypt.encode(this, plain);
        assertEquals(code,encodeStr);
        final String decode = AESEncrypt.decode(this, encodeStr);
        assertEquals(plain,decode);
    }
}

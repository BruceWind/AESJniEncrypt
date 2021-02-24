package com.androidyuan.aesjni;

import android.content.Context;
import android.support.test.InstrumentationRegistry;
import android.support.test.runner.AndroidJUnit4;

import org.junit.Test;
import org.junit.runner.RunWith;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.atomic.AtomicBoolean;

import static org.junit.Assert.assertEquals;

/**
 * Instrumentation test, which will execute on an Android device.
 *
 * @see <a href="http://d.android.com/tools/testing">Testing documentation</a>
 */
@RunWith(AndroidJUnit4.class)
public class JNITest {

    private static final String PLAIN = "123abcABC*%!~#+_/中文测试";
    private static final String ENCODE_STR = "1cad994119e4f3038fe29e34a4a12ce8a4b28f06db7682ab9d4f775c0e25659b01da27db09368eb3778ccea063";
    private Context appContext;

    //it is used avoid running useless test code.
    private final AtomicBoolean atomicBoolean = new AtomicBoolean();
    //test in a thread pool.
    private final ExecutorService executor = Executors.newFixedThreadPool(3);

    private final Runnable pressureTestRun = new Runnable() {
        @Override
        public void run() {

            for (int i = 0; i < 1000 * 100; i++) {
                final String code = EncryptEntry.encode(appContext.getApplicationContext(), PLAIN);
                assertEquals(ENCODE_STR, code);
                final String decode = EncryptEntry.decode(appContext.getApplicationContext(), ENCODE_STR);
                assertEquals(PLAIN, decode);

            }
            atomicBoolean.set(false);
        }
    };

    @Test
    public void useAppContext() throws Exception {

        // Context of the app under test.
        appContext = InstrumentationRegistry.getTargetContext();
        assertEquals(EncryptEntry.checkSignature(appContext), 1);

        atomicBoolean.set(true);

        executor.submit(pressureTestRun);
        executor.submit(pressureTestRun);
        executor.submit(pressureTestRun);

        while (atomicBoolean.get()) {

        }
    }
}

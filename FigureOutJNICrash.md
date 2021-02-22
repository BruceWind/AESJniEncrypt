How to locate where native crash at?
------------
1.ensure you ndk is set into environment.

2.run **ndk-stack** to analyze logcat which code crash printed.
``` 
adb logcat | ndk-stack -sym ../obj/local/armeabi-v7a/
//or 
adb logcat | ndk-stack -sym ../obj/local/x86/
```
> **../obj/local/x86/** and **../obj/local/armeabi-v7a/** is symbol file directory.
### Example:

I got crash logs:

```logs
$ ./rebuild.sh test
2021-02-19 17:05:04.569 29543-29543/? A/libc: Fatal signal 11 (SIGSEGV), code 1 (SEGV_MAPERR), fault addr 0x1 in tid 29543 (test), pid 29543 (test)
2021-02-19 17:05:04.621 29547-29547/? A/DEBUG: *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** ***
2021-02-19 17:05:04.621 29547-29547/? A/DEBUG: Build fingerprint: 'samsung/d1qzc/d1q:11/RP1A.200720.012/N9700ZCU3EUA6:user/release-keys'
2021-02-19 17:05:04.622 29547-29547/? A/DEBUG: Revision: '9'
2021-02-19 17:05:04.622 29547-29547/? A/DEBUG: ABI: 'arm'
2021-02-19 17:05:04.623 29547-29547/? A/DEBUG: Timestamp: 2021-02-19 17:05:04+0800
2021-02-19 17:05:04.623 29547-29547/? A/DEBUG: pid: 29543, tid: 29543, name: test  >>> /data/local/tmp/test <<<
2021-02-19 17:05:04.623 29547-29547/? A/DEBUG: uid: 2000
2021-02-19 17:05:04.623 29547-29547/? A/DEBUG: signal 11 (SIGSEGV), code 1 (SEGV_MAPERR), fault addr 0x1
2021-02-19 17:05:04.625 29547-29547/? A/DEBUG: Cause: null pointer dereference
2021-02-19 17:05:04.626 29547-29547/? A/DEBUG:     r0  00000001  r1  ffdb37f3  r2  00000001  r3  0024c80e
2021-02-19 17:05:04.626 29547-29547/? A/DEBUG:     r4  7fffffff  r5  00000001  r6  00000001  r7  ffdb3800
2021-02-19 17:05:04.626 29547-29547/? A/DEBUG:     r8  ffdb3698  r9  ffdb3cac  r10 ffdb37f3  r11 00000000
2021-02-19 17:05:04.626 29547-29547/? A/DEBUG:     ip  00000030  sp  ffdb35e0  lr  f65f212d  pc  f65b7ef0
2021-02-19 17:05:04.646 29547-29547/? A/DEBUG: backtrace:
2021-02-19 17:05:04.647 29547-29547/? A/DEBUG:     NOTE: Function names and BuildId information is missing for some frames due
2021-02-19 17:05:04.647 29547-29547/? A/DEBUG:     NOTE: to unreadable libraries. For unwinds of apps, only shared libraries
2021-02-19 17:05:04.647 29547-29547/? A/DEBUG:     NOTE: found under the lib/ directory are readable.
2021-02-19 17:05:04.647 29547-29547/? A/DEBUG:       #00 pc 00036ef0  /apex/com.android.runtime/lib/bionic/libc.so (__memcpy_base_a55+488) (BuildId: 940ec10aefab667cc40b263303abf96e)
2021-02-19 17:05:04.647 29547-29547/? A/DEBUG:       #01 pc 00071129  /apex/com.android.runtime/lib/bionic/libc.so (__sfvwrite+166) (BuildId: 940ec10aefab667cc40b263303abf96e)
2021-02-19 17:05:04.647 29547-29547/? A/DEBUG:       #02 pc 0006af97  /apex/com.android.runtime/lib/bionic/libc.so (__vfprintf+6306) (BuildId: 940ec10aefab667cc40b263303abf96e)
2021-02-19 17:05:04.647 29547-29547/? A/DEBUG:       #03 pc 0007fae1  /apex/com.android.runtime/lib/bionic/libc.so (sprintf+128) (BuildId: 940ec10aefab667cc40b263303abf96e)
2021-02-19 17:05:04.647 29547-29547/? A/DEBUG:       #04 pc 00001045  /data/local/tmp/test
2021-02-19 17:05:04.648 29547-29547/? A/DEBUG:       #05 pc 0000113d  /data/local/tmp/test
2021-02-19 17:05:04.648 29547-29547/? A/DEBUG:       #06 pc 0003382d  /apex/com.android.runtime/lib/bionic/libc.so (__libc_init+68) (BuildId: 940ec10aefab667cc40b263303abf96e)

```

 
```log
$ adb logcat | ndk-stack -sym ./obj/local/armeabi-v7a/
Crash dump is completed

********** Crash dump: **********
Build fingerprint: 'samsung/d1qzc/d1q:11/RP1A.200720.012/N9700ZCU3EUA6:user/release-keys'
pid: 29543, tid: 29543, name: test  >>> /data/local/tmp/test <<<
signal 11 (SIGSEGV), code 1 (SEGV_MAPERR), fault addr 0x1
Stack frame #00 pc 00036ef0  /apex/com.android.runtime/lib/bionic/libc.so (__memcpy_base_a55+488) (BuildId: 940ec10aefab667cc40b263303abf96e)
Stack frame #01 pc 00071129  /apex/com.android.runtime/lib/bionic/libc.so (__sfvwrite+166) (BuildId: 940ec10aefab667cc40b263303abf96e)
Stack frame #02 pc 0006af97  /apex/com.android.runtime/lib/bionic/libc.so (__vfprintf+6306) (BuildId: 940ec10aefab667cc40b263303abf96e)
Stack frame #03 pc 0007fae1  /apex/com.android.runtime/lib/bionic/libc.so (sprintf+128) (BuildId: 940ec10aefab667cc40b263303abf96e)
Stack frame #04 pc 00001045  /data/local/tmp/test: Routine test_chacha20 at /Users/bruce/Documents/git/AESJniEncrypt/aesjni/src/main/jni/main_unit_test.c:146
Stack frame #05 pc 0000113d  /data/local/tmp/test: Routine main at /Users/bruce/Documents/git/AESJniEncrypt/aesjni/src/main/jni/main_unit_test.c:170

```

My conclusion: `/Users/******/git/AESJniEncrypt/aesjni/src/main/jni/main_unit_test.c:146` is where the executable file crash at.

## Remind
*ndk-stack* of NDK-R13 **only supports** symbol file of armeabi-v7a.


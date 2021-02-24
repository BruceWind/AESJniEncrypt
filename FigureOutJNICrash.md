How to locate where native crash at?
------------
1.ensure you ndk is set into environment.

2.run **ndk-stack** to analyze logcat and **symbol file** to find where crash printed.
``` 
//gradlew build with ndkBuild:
adb logcat | ndk-stack -sym ./aesjni/build/intermediates/ndkBuild/debug/obj/local/arm64-v8a/objs-debug/
//gradlew build with CMake:
adb logcat | ndk-stack -sym ./aesjni/build/intermediates/cmake/debug/obj/arm64-v8a
//if you run ndk-build command:
adb logcat | ndk-stack -sym ./aesjni/src/main/obj/local/x86/
```
> **../obj/local/x86/** and **../obj/local/armeabi-v7a/** is symbol file directory.


### Example:

I got crash logs:

```logs
$ ./test_in_executing.sh
2021-02-24 17:03:48.242 12059-12059/? A/libc: Fatal signal 11 (SIGSEGV), code 1 (SEGV_MAPERR), fault addr 0x0 in tid 12059 (test), pid 12059 (test)
2021-02-24 17:03:48.251 12063-12063/? A/DEBUG: *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** ***
2021-02-24 17:03:48.251 12063-12063/? A/DEBUG: Build fingerprint: 'google/sdk_gphone_x86_arm/generic_x86_arm:11/RSR1.201013.001/6903271:userdebug/dev-keys'
2021-02-24 17:03:48.252 12063-12063/? A/DEBUG: Revision: '0'
2021-02-24 17:03:48.252 12063-12063/? A/DEBUG: ABI: 'x86'
2021-02-24 17:03:48.252 12063-12063/? A/DEBUG: Timestamp: 2021-02-24 17:03:48+0800
2021-02-24 17:03:48.252 12063-12063/? A/DEBUG: pid: 12059, tid: 12059, name: test  >>> /data/local/tmp/test <<<
2021-02-24 17:03:48.252 12063-12063/? A/DEBUG: uid: 2000
2021-02-24 17:03:48.252 12063-12063/? A/DEBUG: signal 11 (SIGSEGV), code 1 (SEGV_MAPERR), fault addr 0x0
2021-02-24 17:03:48.252 12063-12063/? A/DEBUG: Cause: null pointer dereference
2021-02-24 17:03:48.252 12063-12063/? A/DEBUG:     eax 00000000  ebx 60915ef0  ecx f482efe0  edx f482efe0
2021-02-24 17:03:48.252 12063-12063/? A/DEBUG:     edi fff9e924  esi 608f0c20
2021-02-24 17:03:48.252 12063-12063/? A/DEBUG:     ebp fff9e848  esp fff9e78c  eip 60857ef3
2021-02-24 17:03:48.252 12063-12063/? A/DEBUG: backtrace:
2021-02-24 17:03:48.252 12063-12063/? A/DEBUG:     NOTE: Function names and BuildId information is missing for some frames due
2021-02-24 17:03:48.252 12063-12063/? A/DEBUG:     NOTE: to unreadable libraries. For unwinds of apps, only shared libraries
2021-02-24 17:03:48.252 12063-12063/? A/DEBUG:     NOTE: found under the lib/ directory are readable.
2021-02-24 17:03:48.252 12063-12063/? A/DEBUG:     NOTE: On this device, run setenforce 0 to make the libraries readable.
2021-02-24 17:03:48.252 12063-12063/? A/DEBUG:       #00 pc 0000bef3  /data/local/tmp/test
2021-02-24 17:03:48.252 12063-12063/? A/DEBUG:       #01 pc 0000532e  /data/local/tmp/test
2021-02-24 17:03:48.252 12063-12063/? A/DEBUG:       #02 pc 000058f7  /data/local/tmp/test
2021-02-24 17:03:48.252 12063-12063/? A/DEBUG:       #03 pc 000522e3  /apex/com.android.runtime/lib/bionic/libc.so (__libc_init+115) (BuildId: 6e3a0180fa6637b68c0d181c343e6806)
```

I run ndk-stack: 
```log
$ adb logcat | ndk-stack -sym ./aesjni/src/main/obj/local/x86                                     
 ********** Crash dump: **********
 Build fingerprint: 'google/sdk_gphone_x86_arm/generic_x86_arm:11/RSR1.201013.001/6903271:userdebug/dev-keys'
 pid: 12059, tid: 12059, name: test  >>> /data/local/tmp/test <<<
 signal 11 (SIGSEGV), code 1 (SEGV_MAPERR), fault addr 0x0
 Stack frame #00 pc 0000bef3  /data/local/tmp/test: Routine crypto_aead_aes256gcm_beforenm at ??:?
 Stack frame #01 pc 0000532e  /data/local/tmp/test: Routine test_aead_aes256gcm at ~/Documents/git/AESJniEncrypt/aesjni/src/main/jni/main_unit_test.c:48
 Stack frame #02 pc 000058f7  /data/local/tmp/test: Routine main at ~/Documents/git/AESJniEncrypt/aesjni/src/main/jni/main_unit_test.c:142
 Stack frame #03 pc 000522e3  /apex/com.android.runtime/lib/bionic/libc.so (__libc_init+115) (BuildId: 6e3a0180fa6637b68c0d181c343e6806)
 
```

`at ~/Documents/git/AESJniEncrypt/aesjni/src/main/jni/main_unit_test.c:48` show me that 
executable file crash at `line 48 from main_unit_test.c`.



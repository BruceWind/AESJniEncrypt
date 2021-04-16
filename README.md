[English](https://github.com/BruceWind/AESJniEncrypt/blob/master/README.md)

[中文](https://github.com/BruceWind/AESJniEncrypt/blob/master/README_zh.md)


# Reach high security with libsodium in Android
- [x] I have no longer supported ~~AES algorithms~~. If you still need it, check out tag: [v2.2](https://github.com/BruceWind/AESJniEncrypt/releases/tag/v2.2).
- [x] Use **CHACHA20** instead of **AES**. TLS1.3 has been used **CHACHA20** on mobile device too. It is high-performance for ARM architecture.
- [x] Hide native function in JniOnload
- [x] Use signature verification to avoid being packaged again (It is prevents that hacker call your jni method directly.)
- [x] ~~key exists in the symbol table, and hides the character table~~. This method has been deprecated due to [discard reason issues5](https://github.com/weizongwei5/AESJniEncrypt/issues/5)
- [x] Get the key from a complex function, to hide the key, current function is a simple solution. (Complex solution: divide the Key into several pieces, store them in different C files, and finally splicing them together. This function should be complicated to write and increase the decompiling difficulty.)

- [x] Use "obfuscator" to confuse C code, [how to  deobfuscate it?](https://blog.quarkslab.com/deobfuscation-recovering-an-ollvm-protected-program.html)
- [x] Supporting x86 of obfucation. A link at the bottom is tutorial for configuring obfucator.
- [x] Anti-debugging, the current code is a relatively simple solution, there are more complicated and more sophisticated solutions, such as: each time you perform encryption and decryption sign to determine whether it is traced, you want to write more complicated after your fork
- [x] Detect device is emulator in runtime : The code comes from my another repo [Check_Emulator_In_NDK](https://github.com/Scavenges/Check_Emulator_In_NDK)
- [ ] TODO: Prevent SO file being code injected

## build & run it.

1. preparation：

run the shell : `aesjni/src/main/jni/build_libsodium_for_all_android_abi.sh`

2. click run app from Android Studio to look at logcat.

## how integrate it into your project?
a. generating a chacha20 key: 
    
run `test_in_exexutaing.sh`, and look at logcat. It will generate key and nonce. You can paste it into **JNIEntry.c**.

b. Set **ndk.dir** in local.properties. Some versions of NDK I have not tested. Maybe you will encounter build errors from that.

c. As you integrate into the project, please modify class name and method name, don't expose the name of encryption algorithm, modify the method of key storage from my code.

d. Generate and modify signatures.

d.1. Generate keystore

```shell script
# my generate record:
mkdir keystore
cd keystore/
keytool -genkey -alias client1 -keypass 123456 -keyalg RSA -keysize 1024 -validity 365 -storetype PKCS12 -keystore ./androidyuan.keystore
```

d.2. Modify keystore hash and package name form [check_signature.h](https://github.com/BruceWind/AESJniEncrypt/blob/master/aesjni/src/main/jni/check_signature.h#L9).

This medthod: [getSignature()](https://github.com/BruceWind/AESJniEncrypt/blob/519a4f16ee0a61b05f8dd41419e3fe61836ee5c7/aesjni/src/main/java/com/androidyuan/aesjni/SignatureTool.java#L26), 
is used to get hash value of keystore file.
    
Please integrate the keystore hashcode and package name into `check_signature.h`.
## Thanks

libsodium Algorithm from: https://github.com/jedisct1/libsodium

Native code obfuscator: [obfuscation-o-llvm-ndk](https://fuzion24.github.io/android/obfuscation/ndk/llvm/o-llvm/2014/07/27/android-obfuscation-o-llvm-ndk)


### Remind: SO file will become bigger

![unconfused so](https://github.com/weizongwei5/AESJniEncrypt/raw/master/img/unobfscator_debugapk.png)
![confused so](https://github.com/weizongwei5/AESJniEncrypt/raw/master/img/obfscator_screen.png)

Confused SO file is three times the size of original SO file.
If the size of SO file bother you, you can disable obfscator-lvvm. It is unnecessary.

### In addition, what I have to tell you:
Because you need to do signature verification, I can't provide **jcenter** dependencies, pls forgive me! 

Even though these code is very safe, I still against storing key in code.


To compile a SO confused native code, you need to modify the `externalNativeBuild` in the aesjni/build.gradle and configure the Obfuscator-LLVM under the NDK.

This is my NDK configuration obfuscator tutorial: [Obfuscator-LLVM-4.0-BUILD-NDK](https://github.com/weizongwei5/Obfuscator-LLVM-4.0-BUILD-NDK)

[How do other languages ​​work together with encryption and decryption?](https://github.com/weizongwei5/AESJniEncrypt/issues/8)

If you want to ask me,please click [![Gitter chat](https://badges.gitter.im/gitterHQ/gitter.png)](https://gitter.im/askbruce/community).

If you encounter crash, you can look into **FigureOutJNICrash.md** to find where code crash at.

-------------------
## Legal
If you live in China, you should take care about [checking apk signature](https://github.com/BruceWind/AESJniEncrypt/blob/master/aesjni/src/main/cpp/check_emulator.h#L15).
I have called PackageManger that may be misunderstood to collect list of installed apps. 
You should look at [工信部整治八项违规](http://www.miit.gov.cn/n1146295/n7281315/c7507241/part/7507297.docx).

## Contributing

In case you would like to add information to this repository or suggest some ideas, please use one of the following options:

- [Create an Issue](https://github.com/weizongwei5/AESJniEncrypt/issues/new).
- Send me Pull Requests

### Contributor

[https://github.com/larry19840909](https://github.com/larry19840909)

[https://github.com/zxp0505](https://github.com/zxp0505)

[https://github.com/baoyongzhang](https://github.com/baoyongzhang)

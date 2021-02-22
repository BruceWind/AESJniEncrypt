[English](https://github.com/BruceWind/AESJniEncrypt/blob/master/README.md)

[中文](https://github.com/BruceWind/AESJniEncrypt/blob/master/README_zh.md)


# Reach high security in Android
- [x] ~~AES algorithms~~,it is low-performance,so it has been deprecated.
- [x] use chacha20 instead of AES. TLS1.3 used chacha20 on mobile device too,it is high-performance for arm.
- [x] Hide native function in JniOnload
- [x] Use signature verification to avoid being packaged again (It is prevents that hacker call your jni method directly.)
- [x] ~~key exists in the symbol table, and hides the character table~~ This scheme has been deprecated, [discard reason issues5](https://github.com/weizongwei5/AESJniEncrypt/issues/5), please see the next
- [x] Get the key from a complex function, to hide the key, current function is a simple solution. (Complex solution: divide the Key into several pieces, store them in different C files, and finally splicing them together. This function should be complicated to write and increase the decompiling difficulty.)

- [x] Use "obfuscator" to confuse C code, [how to  deobfuscation?](https://blog.quarkslab.com/deobfuscation-recovering-an-ollvm-protected-program.html)
- [x] Added support for x86 for obfucator. There is a link at the bottom of the tutorial for configuring obfucator.
- [x] Anti-debugging the so, the current code is a relatively simple solution, there are more complicated and more sophisticated solutions, such as: each time you perform encryption and decryption sign to determine whether it is traced, you want to write more complicated after your fork
- [x] Masking the simulator when the code is run: The code comes from my another repository [Check_Emulator_In_NDK](https://github.com/Scavenges/Check_Emulator_In_NDK)
- [ ] TODO: Prevent SO file being code inject


## Before you clone
install GIT-LFS: https://git-lfs.github.com/

## Build & Integration

a. Set ndk.dir in local.properties Requires that the ndk version must be 11-13b. High version ndk has not been tested, and may doesn't compiled.

b. Integrate into the project, please modify the class name and method name, dont expose the encryption algorithm, modify the key storage program into the code.

c. Generate and modify signatures.

c.1.Generate keystore
```
/ / Then the current directory
$ mkdir keystore
$ cd keystore/
$ keytool -genkey -alias client1 -keypass 123456 -keyalg RSA -keysize 1024 -validity 365 -storetype PKCS12 -keystore ./androidyuan.keystore

...


```

c.2. Get the hash value of the current keystore and modify the package name and hash in the native code

    At present, there seems to be no good way. I can only use java, **getSignature(Context context)** to log out, then write to the C file and rebuild the project.
    
  Please integrate the keystore hashcode and package name into your own project to prevent the de-compilation from getting the SO file and use it for secondary packaging.
## Thanks

Base64 algorithm from: https://github.com/willemt/pearldb

AES128 Algorithm From: https://github.com/kokke/tiny-AES128-C

Native code obfuscator: [obfuscation-o-llvm-ndk](https://fuzion24.github.io/android/obfuscation/ndk/llvm/o-llvm/2014/07/27/android-obfuscation-o-llvm-ndk)


### Remind: SO file will become bigger

![unconfused so](https://github.com/weizongwei5/AESJniEncrypt/raw/master/img/unobfscator_debugapk.png)
![confused so](https://github.com/weizongwei5/AESJniEncrypt/raw/master/img/obfscator_screen.png)

Contrast: So confused is three times the size before confusion.

### PS:
Because you need to do signature verification, i cann't provide jcenter dependencies, pls forgive me! 

Regardless of how secure the code, I still against that the key being stored in the code.


To compile a SO confused native code, you need to modify the externalNativeBuild in the aesjni/build.gradle file and configure the Obfuscator-LLVM under the NDK.

This is my NDK configuration obfuscator tutorial: [Obfuscator-LLVM-4.0-BUILD-NDK](https://github.com/weizongwei5/Obfuscator-LLVM-4.0-BUILD-NDK)

[How do other languages ​​work together with encryption and decryption?](https://github.com/weizongwei5/AESJniEncrypt/issues/8)

If you want to ask me,please click [![Gitter chat](https://badges.gitter.im/gitterHQ/gitter.png)](https://gitter.im/askbruce/community).

-------------------

## Contributing

In case you would like to add information to this repository or suggest some ideas, please use one of the following options:

- [Create an Issue](https://github.com/weizongwei5/AESJniEncrypt/issues/new).
- Send me Pull Requests

### Contributor

[https://github.com/larry19840909](https://github.com/larry19840909)

[https://github.com/zxp0505](https://github.com/zxp0505)

[https://github.com/baoyongzhang](https://github.com/baoyongzhang)


## Legal
If you live in China, you should take care about [checking apk signature](https://github.com/BruceWind/AESJniEncrypt/blob/master/aesjni/src/main/cpp/check_emulator.c#L43).
I have called PackageManger ,it might be considered to read installed apps list,look at [工信部整治八项违规](http://www.miit.gov.cn/n1146295/n7281315/c7507241/part/7507297.docx).

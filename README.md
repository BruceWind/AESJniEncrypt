[English](https://github.com/BruceWind/AESJniEncrypt/blob/master/README.md)

[中文](https://github.com/BruceWind/AESJniEncrypt/blob/master/README_zh.md)


# Reach high security with libsodium in Android

> I have no longer supported ~~AES algorithms~~. Still needing it, you can check out tag: [v2.2](https://github.com/BruceWind/AESJniEncrypt/releases/tag/v2.2).

- [x] Use **CHACHA20** instead of **AES**. I have to mention that TLS1.3 use **CHACHA20** on mobile device too. It is high-performance for ARM architecture.
- [x] Hide native function in JniOnload
- [x] Use signature verification to avoid second-packaged. (It is prevents that hacker call your jni method directly.)
- [x] ~~key exists in the symbol table, and hides the character table~~. This approach has been deprecated due to [discard reason issues5](https://github.com/weizongwei5/AESJniEncrypt/issues/5)
- [x] Obtain the key from a complex function, to hide the key, currently the function is a simple solution. (Complex solution: divide the Key into several pieces, store them in different C files, and finally splicing them together. This function should be complicated to write and increase the decompiling difficulty.)

- [x] Use "obfuscator" to confuse C code, [how to  deobfuscate it?](https://blog.quarkslab.com/deobfuscation-recovering-an-ollvm-protected-program.html)
- [x] Supporting x86 of obfucation. A link at the bottom is tutorial for configuring obfucator.
- [x] Anti-debugging. Currently, I put a simple solution into code but there are complicated and sophisticated solutions.
      I recommand determining whether it is traced in every encryption and decryption. You can add other complicated algorithm in your fork.
- [x] Detecting device is emulator during runtime. This feature comes from my another repo [Check_Emulator_In_NDK](https://github.com/Scavenges/Check_Emulator_In_NDK)
- [ ] TODO: Prevent SO file injecting from hacker.



## build & run it.
<details>
<summary>click to expand.</summary>


1. preparation：

run the shell : `./build_libsodium_for_all_android_abi.sh`
When you run the shell, some error you may got some error like this:
`env: python: No such file or directory` , `See "config.log" for more details` or others.

Pls, take time to solve them.

If the shell run well, a lots of files, such as  `.a` & `.so`, will be copy into `aesjni/src/main/jni/sodium_include/`.
Also you would saw `All of static libs has been moved into ......` at terminal.

1. click run app from adb to look at logcat，some result of execution will be there

</details>


## how to integrate it into my project?
<details>
<summary>click to expand.</summary>
a. generating a chacha20 key: 
    
run `test_in_exexutaing.sh`, and look at logcat. It will generate ***key*** and ***nonce***. You can paste it into **JNIEntry.c**.



b. Set **ndk.dir** in local.properties. Some versions of NDK I have not tested. Maybe you will encounter build errors from that.

c. As you integrating it into the project, please modify class names and method names, don't expose the name of encryption algorithm, modify the [C function](https://github.com/BruceWind/AESJniEncrypt/blob/master/aesjni/src/main/jni/JNIEncrypt.c#L56-L70) of key storage from my code.

d. Generate and modify signatures.

d.1. Generate keystore file(You shoul jump this step in case you already have keysotre.)

```shell script
# my generate record:
mkdir keystore
cd keystore/
keytool -genkey -alias client1 -keypass 123456 -keyalg RSA -keysize 1024 -validity 365 -storetype PKCS12 -keystore ./androidyuan.keystore
```

d.2. Modify `hash` of your keystore and `pkg-name` in [check_signature.h](https://github.com/BruceWind/AESJniEncrypt/blob/master/aesjni/src/main/jni/check_signature.h#L9_L11).

As you obtaining the hash,  you should use this medthod: [getSignature()](https://github.com/BruceWind/AESJniEncrypt/blob/519a4f16ee0a61b05f8dd41419e3fe61836ee5c7/aesjni/src/main/java/com/androidyuan/aesjni/SignatureTool.java#L26), 
to get.
    
Please copy the **keystore hashcode** and **package name** into `check_signature.h`.
      
</details>

### Remind: SO file will become bigger

![unconfused so](https://github.com/weizongwei5/AESJniEncrypt/raw/master/img/unobfscator_debugapk.png)
![confused so](https://github.com/weizongwei5/AESJniEncrypt/raw/master/img/obfscator_screen.png)

Size of confused SO file may be three times the size of original SO file.
If the size bother you, you can disable obfscator-lvvm. It is unnecessary.

### In addition, what I have to tell you:
Because you need to do signature verification, I can't provide **jcenter** dependencies, pls forgive me! 

Even though these code is very safe, I still against storing key in code. The key that shouldn't be constant shuold be termporary and generated. If you know how SSL works, you may think that asymmetric entription transfering the key is safest in the world.
If you dont know how SSL works, I recommend a blog from Cloudflare: [what-is-asymmetric-encryption](https://www.cloudflare.com/zh-cn/learning/ssl/what-is-asymmetric-encryption/)


To confuse native code, you need to modify the `externalNativeBuild` in the `aesjni/build.gradle` and configure the **Obfuscator-LLVM** under the NDK.

This is my NDK configuration obfuscator tutorial: [Obfuscator-LLVM-4.0-BUILD-NDK](https://github.com/weizongwei5/Obfuscator-LLVM-4.0-BUILD-NDK).

In another way, you can build it on docker.
Maybe you think configurating Obfuscator-LLVM is really difficult. I recommend using docker : [github.com/nickdiego/docker-ollvm](https://github.com/nickdiego/docker-ollvm).


[How do other languages ​​work together with encryption and decryption?](https://github.com/weizongwei5/AESJniEncrypt/issues/8)

If you got a crash, you can look into **FigureOutJNICrash.md** to find where code crash at.

-------------------
## Legal
If you live in China, you should take care of [checking apk signature](https://github.com/BruceWind/AESJniEncrypt/blob/master/aesjni/src/main/cpp/check_emulator.h#L15).
In this code, I use PackageManger that may be misunderstood to collect list of installed apps. 
You should look at [工信部整治八项违规](http://www.miit.gov.cn/n1146295/n7281315/c7507241/part/7507297.docx).

## Contributing

In case you would like to add information to this repository or suggest some ideas, please use one of the following options:

- [Create an Issue](https://github.com/weizongwei5/AESJniEncrypt/issues/new).
- Send me Pull Requests

### Contributor

[https://github.com/larry19840909](https://github.com/larry19840909)

[https://github.com/zxp0505](https://github.com/zxp0505)

[https://github.com/baoyongzhang](https://github.com/baoyongzhang)



## Thanks

Libsodium Algorithm from: https://github.com/jedisct1/libsodium

Native code obfuscator: [obfuscation-o-llvm-ndk](https://fuzion24.github.io/android/obfuscation/ndk/llvm/o-llvm/2014/07/27/android-obfuscation-o-llvm-ndk)



[English](https://github.com/BruceWind/AESJniEncrypt/blob/master/README.md)

[中文](https://github.com/BruceWind/AESJniEncrypt/blob/master/README_zh.md)

# 追求极致的代码安全性保障 
- [x] ~~ndk实现AES加密~~,性能不佳,已废弃此方式
- [x] 使用**CHACHA20**加密,TLS1.3也在移动端用了**CHACHA20**了,性能对ARM架构CPU更好。
- [x] 使用JniOnload 隐藏C函数
- [x] 使用签名校验避免被再次打包（这是绕过破解加密算法直接调用你的jni函数）
- [x] ~~key存在符号表中,同时隐藏字符表~~ 该方案已经废弃,[废弃原因issues5](https://github.com/weizongwei5/AESJniEncrypt/issues/5)
- [x] 手工处理隐藏key,最复杂的方案：将密钥分成不同的几段,存储在不同的代码中,最后将他们拼接起来,可以将整个操作写的很复杂,增加逆向难度。（目前代码里用的是稍微简单的方案）
- [x] 使用obfuscator混淆C的代码,[关于破解obfuscator](https://blog.quarkslab.com/deobfuscation-recovering-an-ollvm-protected-program.html)
- [x]  增加obfucator对x86的支持,具体配置obfucator的教程底部有链接。
- [x] 反动态调试 , 目前代码里是比较简单的方案, 有更复杂更高明的方案,比如：每次执行加密解密签先去判断是否被trace,想要更复杂的自己fork之后去写
- [x] 代码运行时屏蔽模拟器 :代码来自我的另外一个仓库[Check_Emulator_In_NDK](https://github.com/Scavenges/Check_Emulator_In_NDK)
- [ ] TODO：防止so代码被code inject

## 尝试编译，并跑起来
1.准备：
运行这个shell ： aesjni/src/main/jni/build_libsodium_for_all_android_abi.sh
2.打开AS运行app，并查看日志。 
## 集成

a.先配置local.properties中ndk.dir 要求使用ndk版本必须11-13b,新版本ndk没有测试过,或许不能编译通过。

b.集成到项目中请修改类名方法名,不要暴露加密算法,自行修改key存储到代码里的方案.

b.1. 生成 chacha20 key: 
    
run `test_in_exexutaing.sh`,然后请看logcat. 随机生成的key & nonce会显示出来. 你需要粘贴到 **JNIEntry.c**.

c.生成和修改签名.

**c.1.生成keystore**

```shell script
# my generate record:
mkdir keystore
cd keystore/
keytool -genkey -alias client1 -keypass 123456 -keyalg RSA -keysize 1024 -validity 365 -storetype PKCS12 -keystore ./androidyuan.keystore
```

**c.2.用java取得当前keystore的hash值,并修改native代码中的包名和hash**

    用[getSignature()](https://github.com/BruceWind/AESJniEncrypt/blob/519a4f16ee0a61b05f8dd41419e3fe61836ee5c7/aesjni/src/main/java/com/androidyuan/aesjni/SignatureTool.java#L26)打log取出之后,然后写入到C文件中,重新build项目。
    
  集成到自己项目中请先修改`check_signature.h`中的keystore hashcode和包名。
  
  
## 鸣谢

Libsodium 算法 来自：https://github.com/jedisct1/libsodium
Native代码混淆器：[obfuscation-o-llvm-ndk](https://fuzion24.github.io/android/obfuscation/ndk/llvm/o-llvm/2014/07/27/android-obfuscation-o-llvm-ndk)





### 注意 : SO会变大的问题

![未混淆的so](https://github.com/weizongwei5/AESJniEncrypt/raw/master/img/unobfscator_debugapk.png)
![已混淆的so](https://github.com/weizongwei5/AESJniEncrypt/raw/master/img/obfscator_screen.png)

对比： 混淆后的so是混淆前的三倍大小。

如果SO文件大小对您的项目有影响，你可以选择停用SO扰乱的，因为还有其他安全检查。

### 补充:
因为需要做签名校验,所以无法提供jcenter依赖了,望见谅！！

不管代码安全性多高,我依旧反对key存到代码里。

有问题及时提:[new issues](https://github.com/weizongwei5/AESJniEncrypt/issues/new)

想要编译出混淆过native代码的so需要修改aesjni/build.gradle文件中的externalNativeBuild,并配置NDK下的Obfuscator-LLVM。

这是我的NDK配置混淆器教程：[Obfuscator-LLVM-4.0-BUILD-NDK](https://github.com/weizongwei5/Obfuscator-LLVM-4.0-BUILD-NDK)

[其他语言怎么配合加解密？](https://github.com/weizongwei5/AESJniEncrypt/issues/8)

如果你遇到了崩溃，请看**FigureOutJNICrash.md**，这个是个so崩溃定位的教程。

-------------------

## 合规
如果你生活在中国，请注意[工信部整治八项违规](http://www.miit.gov.cn/n1146295/n7281315/c7507241/part/7507297.docx).
我调用了PackageManger[检查签名](https://github.com/BruceWind/AESJniEncrypt/blob/master/aesjni/src/main/cpp/check_emulator.c#L43)，我只是**读取当前安装的app**, 这可能被认为**收集了安装列表**。从规定上来讲并不违规，只是读取了，并没**收集**，收集是违规的，读取是合规的。
只是目前有可能被误认为**收集**。


### 贡献者

[https://github.com/larry19840909](https://github.com/larry19840909)

[https://github.com/zxp0505](https://github.com/zxp0505)

[https://github.com/baoyongzhang](https://github.com/baoyongzhang)
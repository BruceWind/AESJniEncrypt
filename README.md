# 追求极致的代码安全性保障 
- [x] ndk实现AES加密
- [x] 使用JniOnload 隐藏c函数
- [x] 再做一层防止被二次打包的签名校验
- [x] ~~key存在符号表中，同时隐藏字符表~~ 该方案已经废弃,请看下一条
- [x] 手工处理隐藏key，最复杂的方案：将密钥分成不同的几段，存储在不同的代码中，最后将他们拼接起来，可以将整个操作写的很复杂，增加逆向难度。（目前代码里用的是稍微简单的方案）
- [x] 使用obfuscator混淆C的代码,[关于破解obfuscator](https://blog.quarkslab.com/deobfuscation-recovering-an-ollvm-protected-program.html)
- [x]  增加obfucator对x86的支持,具体配置obfucator的教程底部有链接。
- [ ] TODO：代码run的时候屏蔽模拟器 :demo已经写好，准备接入[Check_Emulator_In_NDK](https://github.com/Scavenges/Check_Emulator_In_NDK)
- [ ] TODO：防止so代码被code inject
- [ ] TODO：反动态调试
```
char * key = "NMTIzNDU2Nzg5MGFiY2RlZg";//这里是key被做过处理存储在这里的，实际上真实的key是："1234567890abcdef"
```
## 集成

a.先配置local.properties中ndk.dir 要求使用ndk版本必须12b以上.

b.集成到项目中请修改类名方法名,不要暴露加密算法，自行修改key存储到代码里的方案.

c.生成和修改签名.

**c.1.生成**
```
//再当前目录下
$ mkdir  keystore
$ cd keystore/
$ keytool -genkey -alias client1 -keypass 123456 -keyalg RSA -keysize 1024 -validity 365 -storetype PKCS12 -keystore ./androidyuan.keystore
输入密钥库口令:weizongwei
再次输入新口令:weizongwei
警告: PKCS12 密钥库不支持其他存储和密钥口令。正在忽略用户指定的-keypass值。
您的名字与姓氏是什么?
  [Unknown]:  weizongwei
您的组织单位名称是什么?
  [Unknown]:  androidyuan.com
您的组织名称是什么?
  [Unknown]:  androidyuan.com
您所在的城市或区域名称是什么?
  [Unknown]:  shanghai
您所在的省/市/自治区名称是什么?
  [Unknown]:  shanghai
该单位的双字母国家/地区代码是什么?
  [Unknown]:  cn
CN=weizongwei, OU=androidyuan.com, O=androidyuan.com, L=shanghai, ST=shanghai, C=cn是否正确?
  [否]:  y

//测试 keystore口令是否正确
$ keytool -exportcert -alias androiddebugkey -keystore   "androidyuan.keystore" | openssl sha1 -binary | openssl base64
  输入密钥库口令:  weizongwei
  8GUZG0hBFvUZ1I4kSq/3vowhE7Y=


```

**c.2.取得当前keystore的hash值,并修改native代码中的包名和hash**

    目前似乎没有好的办法，我只能用java取，**getSignature(Context context)**打log取出之后，然后写入到C文件中，重新build项目。
    
  集成到自己项目中请先修改keystore hashcode和包名，防止反编译时拿到so文件，进行二次打包使用。
## 鸣谢

Base64 算法 来自：https://github.com/willemt/pearldb

AES128 算法 来自：https://github.com/kokke/tiny-AES128-C

Native代码混淆器：[obfuscation-o-llvm-ndk](https://fuzion24.github.io/android/obfuscation/ndk/llvm/o-llvm/2014/07/27/android-obfuscation-o-llvm-ndk)


### 注意 : SO会变大的问题

![未混淆的so](https://github.com/weizongwei5/AESJniEncrypt/raw/master/img/unobfscator_debugapk.png)
![已混淆的so](https://github.com/weizongwei5/AESJniEncrypt/raw/master/img/obfscator_screen.png)

对比： 混淆后的so是混淆前的三倍大小。

### PS:
因为需要做签名校验，所以无法提供jcenter依赖了，望见谅！！

不管代码安全性多高，我依旧反对key存到代码里。


想要编译出混淆过native代码的so需要修改aesjni/build.gradle文件中的externalNativeBuild，并配置NDK下的Obfuscator-LLVM。

这是我的NDK配置混淆器教程：[Obfuscator-LLVM-4.0-BUILD-NDK](https://github.com/weizongwei5/Obfuscator-LLVM-4.0-BUILD-NDK)




-------------------

有问题及时提:[new issues](https://github.com/weizongwei5/AESJniEncrypt/issues/new)

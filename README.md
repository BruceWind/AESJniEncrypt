# 追求破解难度到极致
- [x] ndk实现AES加密
- [x] 使用JniOnload 隐藏c函数
- [x] 再做一层防止被二次打包的签名校验
- [x] key存在符号表中，同时隐藏字符表
- [x] 使用obfuscator混淆C的代码(仅支持ndk-build)
- [ ] 目前ollvm-obfuscator无法混淆出x86平台的so。
- [x] 手工处理隐藏key，最复杂的方案：将密钥分成不同的几段，存储在不同的代码中，最后将他们拼接起来，可以将整个操作写的很复杂，增加逆向难度。（目前代码里用的是稍微简单的方案）
```
char * key = "NMTIzNDU2Nzg5MGFiY2RlZg";//这里是key被做过处理存储在这里的，实际上真实的key是："1234567890abcdef"
```
集成到项目中请修改类名方法名,不要暴露加密算法，自行修改key存储到代码里的方案.

## keystore文件 校验

1.生成
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

## 2.取得当前打包的keystore的hash值

    目前似乎没有好的办法，我只能用java取，**getSignature(Context context)**打log取出之后，然后写入到C文件中，重新build项目。
    
  集成到自己项目中请先修改keystore hashcode和包名，防止反编译时拿到so文件，进行二次打包使用。
## 鸣谢

Base64 算法 来自：https://github.com/willemt/pearldb

AES128 算法 来自：https://github.com/kokke/tiny-AES128-C

Native代码混淆器：[obfuscation-o-llvm-ndk](https://fuzion24.github.io/android/obfuscation/ndk/llvm/o-llvm/2014/07/27/android-obfuscation-o-llvm-ndk)


### PS:
因为需要做签名校验，所以无法提供jcenter依赖了，望见谅！！

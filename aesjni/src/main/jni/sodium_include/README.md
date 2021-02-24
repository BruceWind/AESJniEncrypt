### you need to generate libsodium static library.
libsodium generation of shell script is ***build_libsodium_for_all_android_abi.sh***.

By the time you generated, file tree will like :
```shell script

$ tree -d ./sodium_include/
sodium_include/
├── libsodium-android-armv6
│   ├── include
│   │   └── sodium
│   └── lib
│       └── pkgconfig
├── libsodium-android-armv7-a
│   ├── include
│   │   └── sodium
│   └── lib
│       └── pkgconfig
├── libsodium-android-armv8-a
│   ├── include
│   │   └── sodium
│   └── lib
│       └── pkgconfig
└── libsodium-android-i686
    ├── include
    │   └── sodium
    └── lib
        └── pkgconfig
```


### libsodium version
Other information what I need to remind was that the **libsodium static file** which I built was **v1.0.18**. 
That version is the last stable version up to now.

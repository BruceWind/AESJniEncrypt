cmake_minimum_required(VERSION 3.4.1)           #普通版本的clang


add_library( # Sets the name of the library.
             JNIEncrypt

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             src/main/cpp/JNIEncrypt.c
             src/main/cpp/checksignature.h
             src/main/cpp/checksignature.c
             src/main/cpp/check_emulator.h
             src/main/cpp/check_emulator.c
             src/main/cpp/debugger.h
             src/main/cpp/debugger.c
             src/main/cpp/aes.h
             src/main/cpp/base64.h
             src/main/cpp/aes.c
             src/main/cpp/base64.c
             )

# 搜索指定的预构建库并将路径存储为变量。 因为默认情况下，CMake在搜索路径中包含系统库，
# 所以您只需要指定公共NDK库的名称你想添加。 在完成构建之前，CMake验证库存在。

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# 指定CMake应链接到目标库的库。 您可以链接多个库，例如在此构建脚本中定义的库，预构建的第三方库或系统库。

target_link_libraries( # Specifies the target library.
                       JNIEncrypt

                       # included in the NDK.
                       ${log-lib} )

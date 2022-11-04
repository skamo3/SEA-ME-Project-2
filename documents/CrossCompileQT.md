# Cross Compiling Qt for Rpi and Ubuntu

- Qt is a graphic framework, so it is inefficient to work on code, work on graphics, and compile on Raspberry Pi.
- Work on Ubuntu and make a cross-compiling environment so that compilation results are available on Raspberry Pi

> Follow in Raspberry Pi
## 1. Enable development source  
``` sudo vim /etc/apt/sources.list ```
- uncomment the following line by removing the # character (the line should exist already, if not then add it):  
``` deb-src http://raspbian.raspberrypi.org/raspbian/ buster main contrib non-free rpi ```

## 2. Update system
```bash
sudo apt-get update
sudo apt-get dist-upgrade
sudo reboot
```
- check rsync
```bash
which rsync
# /usr/bin/rsync
```
- If rsync is not available [follow this link](https://snapcraft.io/install/rsync/raspbian)
- Add following structure ``` sudo visudo```
    ```bash
    <username> ALL=NOPASSWD:/usr/bin/rsync
    ```

## 3. Install the required development packages
```bash
sudo apt-get build-dep qt5-qmake
sudo apt-get build-dep libqt5gui5
sudo apt-get build-dep libqt5webengine-data
sudo apt-get build-dep libqt5webkit5
sudo apt-get install libudev-dev libinput-dev libts-dev libxcb-xinerama0-dev libxcb-xinerama0 gdbserver
```

## 4. Create a directory for the Qt install
```bash
sudo mkdir /usr/local/qt5.15
sudo chown -R <username>:<username> /usr/local/qt5.15
```

> Follow next step in Ubuntu 
## 5. Update
```bash
sudo apt-get update
sudo apt-get upgrade
sudo apt-get install gcc git bison gperf pkg-config gdb-multiarch python-is-python3
sudo apt install build-essential
```

## 6. Set up the directory structure
```bash
sudo mkdir ~/rpi
sudo mkdir ~/rpi/build
sudo mkdir ~/rpi/tools
sudo mkdir ~/rpi/sysroot
sudo mkdir ~/rpi/sysroot/usr
sudo mkdir ~/rpi/sysroot/opt
sudo chown -R 1000:1000 ~/rpi
cd ~/rpi
```

## 7. Download Qt sources
```bash
sudo wget http://download.qt.io/archive/qt/5.15/5.15.0/single/qt-everywhere-src-5.15.0.tar.xz
sudo tar xfv qt-everywhere-src-5.15.0.tar.xz
cp -R qt-everywhere-src-5.15.0/qtbase/mkspecs/linux-arm-gnueabi-g++ qt-everywhere-src-5.15.0/qtbase/mkspecs/linux-arm-gnueabihf-g++
sed -i -e 's/arm-linux-gnueabi-/arm-linux-gnueabihf-/g' qt-everywhere-src-5.15.0/qtbase/mkspecs/linux-arm-gnueabihf-g++/qmake.conf
```

## 8. Download cross-compiler
```bash
cd ~/rpi/tools
sudo wget https://releases.linaro.org/components/toolchain/binaries/7.4-2019.02/arm-linux-gnueabihf/gcc-linaro-7.4.1-2019.02-x86_64_arm-linux-gnueabihf.tar.xz
sudo tar xfv gcc-linaro-7.4.1-2019.02-x86_64_arm-linux-gnueabihf.tar.xz
cd ~/rpi
```

## 9. Sync our sysroot
- Fisrt make variable for server name and server ip
```bash
export SERVER_NAME=<server name>
export SERVER_IP=<server ip>
```
- Remote synchronization Pull  
```rsync <options> <user-name>@<remote-host>:<source-file-dir> <destination>```
- Remote synchronization Push  
```rsync <options> <source-file-dir> <user-name>@<romote-host>:<destination>```

- Sync the files with rsync
```bash
rsync -avz --rsync-path="sudo rsync" --delete $SERVER_NAME@$SERVER_IP:/lib sysroot
rsync -avz --rsync-path="sudo rsync" --delete $SERVER_NAME@$SERVER_IP:/usr/include sysroot/usr
rsync -avz --rsync-path="sudo rsync" --delete $SERVER_NAME@$SERVER_IP:/usr/lib sysroot/usr
rsync -avz --rsync-path="sudo rsync" --delete $SERVER_NAME@$SERVER_IP:/opt/vc sysroot/opt
```

## 10. Fix symbolic link
```bash
wget https://raw.githubusercontent.com/riscv/riscv-poky/master/scripts/sysroot-relativelinks.py
sudo chmod +x sysroot-relativelinks.py
./sysroot-relativelinks.py sysroot
```

## 11. Configure Qt build
```bash
cd ~/rpi/build
../qt-everywhere-src-5.15.0/configure -release -opengl es2  -eglfs -device linux-rasp-pi4-v3d-g++ -device-option CROSS_COMPILE=~/rpi/tools/gcc-linaro-7.4.1-2019.02-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf- -sysroot ~/rpi/sysroot -prefix /usr/local/qt5.15 -extprefix ~/rpi/qt5.15 -opensource -confirm-license -skip qtscript -skip qtwayland -skip qtwebengine -nomake tests -make libs -pkg-config -no-use-gold-linker -v -recheck
```

<details>
<summary>Trouble shooting</summary>

## file include error
```bash
(base) seame-three@seamethree-ThinkPad-P14s-Gen-2a:~/rpi/build$ ../qt-everywhere-src-5.15.0/configure -release -opengl es2  -eglfs -device linux-rasp-pi4-v3d-g++ -device-option CROSS_COMPILE=~/rpi/tools/gcc-linaro-7.4.1-2019.02-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf- -sysroot ~/rpi/sysroot -prefix /usr/local/qt5.15 -extprefix ~/rpi/qt5.15 -opensource -confirm-license -skip qtscript -skip qtwayland -skip qtwebengine -nomake tests -make libs -pkg-config -no-use-gold-linker -v -recheck
+ cd qtbase
+ /home/seame-three/rpi/qt-everywhere-src-5.15.0/qtbase/configure -top-level -release -opengl es2 -eglfs -device linux-rasp-pi4-v3d-g++ -device-option CROSS_COMPILE=/home/seame-three/rpi/tools/gcc-linaro-7.4.1-2019.02-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf- -sysroot /home/seame-three/rpi/sysroot -prefix /usr/local/qt5.15 -extprefix /home/seame-three/rpi/qt5.15 -opensource -confirm-license -skip qtscript -skip qtwayland -skip qtwebengine -nomake tests -make libs -pkg-config -no-use-gold-linker -v -recheck
Performing shadow build...
Preparing build tree...
Creating qmake...
g++ -c -o qutfcodec.o   -std=c++11 -ffunction-sections -fdata-sections -g -g  -I/home/seame-three/rpi/qt-everywhere-src-5.15.0/qtbase/qmake -I/home/seame-three/rpi/qt-everywhere-src-5.15.0/qtbase/qmake/library -I/home/seame-three/rpi/qt-everywhere-src-5.15.0/qtbase/qmake/generators -I/home/seame-three/rpi/qt-everywhere-src-5.15.0/qtbase/src/3rdparty/tinycbor/src -I/home/seame-three/rpi/qt-everywhere-src-5.15.0/qtbase/qmake/generators/unix -I/home/seame-three/rpi/qt-everywhere-src-5.15.0/qtbase/qmake/generators/win32 -I/home/seame-three/rpi/qt-everywhere-src-5.15.0/qtbase/qmake/generators/mac -I/home/seame-three/rpi/qt-everywhere-src-5.15.0/qtbase/include -I/home/seame-three/rpi/qt-everywhere-src-5.15.0/qtbase/include/QtCore -I/home/seame-three/rpi/qt-everywhere-src-5.15.0/qtbase/include/QtCore/5.15.0 -I/home/seame-three/rpi/qt-everywhere-src-5.15.0/qtbase/include/QtCore/5.15.0/QtCore -I../src/corelib/global -I/home/seame-three/rpi/qt-everywhere-src-5.15.0/qtbase/mkspecs/linux-g++ -DQT_VERSION_STR=\"5.15.0\" -DQT_VERSION_MAJOR=5 -DQT_VERSION_MINOR=15 -DQT_VERSION_PATCH=0 -DQT_BUILD_QMAKE -DQT_BOOTSTRAPPED -DPROEVALUATOR_FULL -DQT_NO_FOREACH /home/seame-three/rpi/qt-everywhere-src-5.15.0/qtbase/src/corelib/codecs/qutfcodec.cpp
In file included from /home/seame-three/rpi/qt-everywhere-src-5.15.0/qtbase/include/QtCore/qfloat16.h:1,
                 from /home/seame-three/rpi/qt-everywhere-src-5.15.0/qtbase/include/QtCore/../../src/corelib/global/qendian.h:44,
                 from /home/seame-three/rpi/qt-everywhere-src-5.15.0/qtbase/include/QtCore/qendian.h:1,
                 from /home/seame-three/rpi/qt-everywhere-src-5.15.0/qtbase/src/corelib/codecs/qutfcodec.cpp:43:
/home/seame-three/rpi/qt-everywhere-src-5.15.0/qtbase/include/QtCore/../../src/corelib/global/qfloat16.h:300:7: error: ‘numeric_limits’ is not a class template
  300 | class numeric_limits<QT_PREPEND_NAMESPACE(qfloat16)> : public numeric_limits<float>
      |       ^~~~~~~~~~~~~~
/home/seame-three/rpi/qt-everywhere-src-5.15.0/qtbase/include/QtCore/../../src/corelib/global/qfloat16.h:300:77: error: expected template-name before ‘<’ token
  300 | class numeric_limits<QT_PREPEND_NAMESPACE(qfloat16)> : public numeric_limits<float>
      |                                                                             ^
/home/seame-three/rpi/qt-everywhere-src-5.15.0/qtbase/include/QtCore/../../src/corelib/global/qfloat16.h:300:77: error: expected ‘{’ before ‘<’ token
/home/seame-three/rpi/qt-everywhere-src-5.15.0/qtbase/include/QtCore/../../src/corelib/global/qfloat16.h:344:18: error: ‘numeric_limits’ is not a class template
  344 | template<> class numeric_limits<const QT_PREPEND_NAMESPACE(qfloat16)>
      |                  ^~~~~~~~~~~~~~
/home/seame-three/rpi/qt-everywhere-src-5.15.0/qtbase/include/QtCore/../../src/corelib/global/qfloat16.h:344:69: error: ‘std::numeric_limits’ is not a template
  344 | template<> class numeric_limits<const QT_PREPEND_NAMESPACE(qfloat16)>
      |                                                                     ^
/home/seame-three/rpi/qt-everywhere-src-5.15.0/qtbase/include/QtCore/../../src/corelib/global/qfloat16.h:300:7: note: previous declaration here
  300 | class numeric_limits<QT_PREPEND_NAMESPACE(qfloat16)> : public numeric_limits<float>
      |       ^~~~~~~~~~~~~~
/home/seame-three/rpi/qt-everywhere-src-5.15.0/qtbase/include/QtCore/../../src/corelib/global/qfloat16.h:345:28: error: expected template-name before ‘<’ token
  345 |     : public numeric_limits<QT_PREPEND_NAMESPACE(qfloat16)> {};
      |                            ^
/home/seame-three/rpi/qt-everywhere-src-5.15.0/qtbase/include/QtCore/../../src/corelib/global/qfloat16.h:346:18: error: ‘numeric_limits’ is not a class template
  346 | template<> class numeric_limits<volatile QT_PREPEND_NAMESPACE(qfloat16)>
      |                  ^~~~~~~~~~~~~~
/home/seame-three/rpi/qt-everywhere-src-5.15.0/qtbase/include/QtCore/../../src/corelib/global/qfloat16.h:346:72: error: ‘std::numeric_limits’ is not a template
  346 | template<> class numeric_limits<volatile QT_PREPEND_NAMESPACE(qfloat16)>
      |                                                                        ^
/home/seame-three/rpi/qt-everywhere-src-5.15.0/qtbase/include/QtCore/../../src/corelib/global/qfloat16.h:300:7: note: previous declaration here
  300 | class numeric_limits<QT_PREPEND_NAMESPACE(qfloat16)> : public numeric_limits<float>
      |       ^~~~~~~~~~~~~~
/home/seame-three/rpi/qt-everywhere-src-5.15.0/qtbase/include/QtCore/../../src/corelib/global/qfloat16.h:347:28: error: expected template-name before ‘<’ token
  347 |     : public numeric_limits<QT_PREPEND_NAMESPACE(qfloat16)> {};
      |                            ^
/home/seame-three/rpi/qt-everywhere-src-5.15.0/qtbase/include/QtCore/../../src/corelib/global/qfloat16.h:348:18: error: ‘numeric_limits’ is not a class template
  348 | template<> class numeric_limits<const volatile QT_PREPEND_NAMESPACE(qfloat16)>
      |                  ^~~~~~~~~~~~~~
/home/seame-three/rpi/qt-everywhere-src-5.15.0/qtbase/include/QtCore/../../src/corelib/global/qfloat16.h:348:78: error: ‘std::numeric_limits’ is not a template
  348 | template<> class numeric_limits<const volatile QT_PREPEND_NAMESPACE(qfloat16)>
      |                                                                              ^
/home/seame-three/rpi/qt-everywhere-src-5.15.0/qtbase/include/QtCore/../../src/corelib/global/qfloat16.h:300:7: note: previous declaration here
  300 | class numeric_limits<QT_PREPEND_NAMESPACE(qfloat16)> : public numeric_limits<float>
      |       ^~~~~~~~~~~~~~
/home/seame-three/rpi/qt-everywhere-src-5.15.0/qtbase/include/QtCore/../../src/corelib/global/qfloat16.h:349:28: error: expected template-name before ‘<’ token
  349 |     : public numeric_limits<QT_PREPEND_NAMESPACE(qfloat16)> {};
      |                            ^
In file included from /home/seame-three/rpi/qt-everywhere-src-5.15.0/qtbase/include/QtCore/qendian.h:1,
                 from /home/seame-three/rpi/qt-everywhere-src-5.15.0/qtbase/src/corelib/codecs/qutfcodec.cpp:43:
/home/seame-three/rpi/qt-everywhere-src-5.15.0/qtbase/include/QtCore/../../src/corelib/global/qendian.h: In static member function ‘static constexpr QSpecialInteger<S> QSpecialInteger<S>::max()’:
/home/seame-three/rpi/qt-everywhere-src-5.15.0/qtbase/include/QtCore/../../src/corelib/global/qendian.h:331:30: error: ‘std::numeric_limits’ is not a template
  331 |     { return QSpecialInteger(std::numeric_limits<T>::max()); }
      |                              ^~~
/home/seame-three/rpi/qt-everywhere-src-5.15.0/qtbase/include/QtCore/../../src/corelib/global/qendian.h:331:54: error: incomplete type ‘std::numeric_limits’ used in nested name specifier
  331 |     { return QSpecialInteger(std::numeric_limits<T>::max()); }
      |                                                      ^~~
/home/seame-three/rpi/qt-everywhere-src-5.15.0/qtbase/include/QtCore/../../src/corelib/global/qendian.h: In static member function ‘static constexpr QSpecialInteger<S> QSpecialInteger<S>::min()’:
/home/seame-three/rpi/qt-everywhere-src-5.15.0/qtbase/include/QtCore/../../src/corelib/global/qendian.h:333:30: error: ‘std::numeric_limits’ is not a template
  333 |     { return QSpecialInteger(std::numeric_limits<T>::min()); }
      |                              ^~~
/home/seame-three/rpi/qt-everywhere-src-5.15.0/qtbase/include/QtCore/../../src/corelib/global/qendian.h:333:54: error: incomplete type ‘std::numeric_limits’ used in nested name specifier
  333 |     { return QSpecialInteger(std::numeric_limits<T>::min()); }
      |                                                      ^~~
gmake: *** [Makefile:383: qutfcodec.o] Error 1
```
- To prevent error, I add these 3 lines at the top of ```~/rpi/qt-everywhere-src-5.15.0/qtbase/src/corelib/global/qglobal.h``` 
```c++
#ifdef __cplusplus
#include <limits>
#endif
```
</details>

## 12. Build Qt
```bash
make -j4
make install
```

## 13. Deploy Qt to our Raspberry Pi

```bash
cd ~/rpi
rsync -avz --rsync-path="sudo rsync" qt5.15 $SERVER_NAME@$SERVER_IP:/usr/local
```

## 14. Build an example application
```bash
cp -r ~/rpi/qt-everywhere-src-5.15.0/qtbase/examples/opengl/qopenglwidget ~/rpi/
cd ~/rpi/qopenglwidget
../qt5.15/bin/qmake
make
```

- copy file to Raspberry Pi and try to execute it
    ```bash
    scp qopenglwidget $SERVER_NAME@$SERVER_IP:/home/pi
    ```

## 15. Execute and test in Raspberry Pi

- find ```qopenglwidget``` file
- `./qopenglwidget` execute
    - You need to use vnc or screen
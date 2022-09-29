# __ASM ARM__

- If your computer's processor is not `ARM` architecture, you should install some additional tools for running binary code

 <font size="6"> 

### Note

- If you have problems with your linux, have MacBook with M1/M2 or  don't want to starve you can use [GodBolt](https://godbolt.org). Just choose there language _Assembly_ and _ARM gcc_ compiler.

## Install instructions

</font> 

1. Download compilers and dynamic libraries

`wget http://releases.linaro.org/components/toolchain/binaries/7.3-2018.05/arm-linux-gnueabi/gcc-linaro-7.3.1-2018.05-i686_arm-linux-gnueabi.tar.xz`

2. Unpack downloaded file

`tar xvf gcc-linaro-7.3.1-2018.05-i686_arm-linux-gnueabi.tar.xz`

3. Install qemu-arm if haven't got already

`sudo apt-get install qemu-user-static qemu-system-arm qemu-user`

4. In case it doesn't work  

`sudo apt update && sudo apt upgrade`

`sudo apt-get install zlib1g:i386`

`sudo apt-get install libc6:i386 libncurses5:i386 libstdc++6:i386`

`sudo dpkg --add-architecture i386`

1. If you have other problems, just search in google the error message. You will find solution for your problem in *99%* of cases.

## Compile and run

1. Add paths to the compilers

`export PATH=$PATH:<local path to directory with unpacked linaro>/gcc-linaro-7.3.1-2018.05-i686_arm-linux-gnueabi/bin`

2. Add paths to the shared-libs for emulator

`export QEMU_LD_PREFIX=<local path to directory with unpacked linaro>/gcc-linaro-7.3.1-2018.05-i686_arm-linux-gnueabi/arm-linux-gnueabi/libc`

3. Compile and run examples
   
   - arm-linux-gnueabi-gcc -marm main.c -o programm.exe
   - arm-linux-gnueabi-gcc -marm main.S -o programm.exe 
   - arm-linux-gnueabi-gcc -marm main.c lib.S -o programm.exe 
   - arm-linux-gnueabi-gcc -marm -S -O3 lib.c -o lib.S

   - qemu-arm ./program.exe

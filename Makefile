obj-m += packetfilter.o
 
all:
	make -C /lib/modules/`uname -r`/build M=`pwd` modules
 
clean:
	make -C /lib/modules/`uname -r`/build M=`pwd` clean

modules_install:
	make -C /lib/modules/`uname -r`/build M=`pwd` modules_install

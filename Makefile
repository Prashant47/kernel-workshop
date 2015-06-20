obj-m += packetfilter.o
 
all:
	make -C /lib/modules/`uname -r`/build M=`pwd` modules
	#make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
 
clean:
	make -C /lib/modules/`uname -r`/build M=`pwd` clean
	#make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

modules_install:
	make -C /lib/modules/`uname -r`/build M=`pwd` modules_install

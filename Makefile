obj-m += homework2.o
obj-m += homework3.o
obj-m += homework5.o
obj-m += homework6.o
obj-m += homework7.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
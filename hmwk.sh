if (( $1 == 10))
then
    gcc -o test test.c
    gcc -o homework10 homework10.c
    ./homework10 test
    echo "----------------------------------Testing homework10-------------------------------------------------"
    echo "----------------------------------Results are written into file result10.log-------------------------"
    rm -f test homework10
else
    make
    rmmod homework$1
    insmod homework$1.ko
    echo "----------------------------------Testing homework$1--------------------------------------------------"
    dmesg > result$1.log
    echo "----------------------------------Results are written into file result$1.log--------------------------"
 #   make clean
fi
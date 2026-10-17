gcc main.c bitonic.c bitonic_parallel.c -o bitonic_test -pthread
./bitonic_test
rm bitonic_test

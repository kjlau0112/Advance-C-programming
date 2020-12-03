gcc -g -c mld.c -o mld.o
gcc -g -c app.c -o app.o
gcc -g -o app app.o mld.o
rm *.o


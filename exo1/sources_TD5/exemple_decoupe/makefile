all : plim.o plam.o ploum.o
	gcc ploum.o plim.o plam.o -o exe


plim.o : plim.c
	gcc -c plim.c -o plim.o

plam.o : plam.c 
	gcc -c plam.c -o plam.o

ploum.o : ploum.c plam.h plim.h
	gcc -c ploum.c -o ploum.o
 
clean : 
	rm -F *.o
	rm -F exe 

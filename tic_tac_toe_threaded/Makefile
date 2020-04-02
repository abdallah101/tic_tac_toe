all: judgeCPU
 
judgeCPU: judgeCPU.c judge.c firstCPU.c secondCPU.c judge.h firstCPU.h secondCPU.h
	gcc -g judgeCPU.c judge.c firstCPU.c secondCPU.c -o judgeCPU -lpthread -w

clean:
	rm -f *.o a.out judgeCPU core

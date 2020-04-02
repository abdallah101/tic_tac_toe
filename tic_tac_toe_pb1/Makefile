all: judgeCPU firstCPU secondCPU
 
firstCPU: firstCPU.c judge.c judge.h
	gcc -g firstCPU.c judge.c -o firstCPU -w

secondCPU: secondCPU.c judge.c judge.h
	gcc -g secondCPU.c judge.c -o secondCPU -w

judgeCPU: judgeCPU.c judge.c judge.h
	gcc -g judgeCPU.c judge.c -o judgeCPU -w

clean:
	rm -f *.o a.out firstCPU secondCPU judgeCPU core

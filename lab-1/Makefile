all: 1_1.c 1_2.c 1_3.c 1_4.c 1_56.c
	gcc -o step1 1_1.c
	gcc -o step2 1_2.c
	gcc -o step3 1_3.c
	gcc -o step4 1_4.c -lpthread
	gcc -o step56 1_56.c -lm
clean:; rm -f *.out step1 step2 step3 step4 step56
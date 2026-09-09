all:
	gcc -o scheduler main.c escalonador.c
clean:
	rm -f scheduler *.txt *.out
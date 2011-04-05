all: pi

pi: pi_proc.c
	gcc pi_proc.c -o pi -std=c99

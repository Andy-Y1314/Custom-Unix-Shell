customshell : main.c exec.c date.c catch_signal.c change_dir.c redirect.c
	gcc main.c exec.c date.c catch_signal.c change_dir.c redirect.c -o customshell

clean :
	rm customshell
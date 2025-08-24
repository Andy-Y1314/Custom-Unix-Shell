# Custom Command Shell in C

This is a custom Linux shell implemented in C. It supports standard Linux commands (like `ls`, `pwd`, etc.) as well as some custom features I added:

- **exec.c**: contains code for executing Linux commands such as `ls`, `pwd`, etc.
- **date.c**: prints the shell prompt in the format `[dd/mm hh:mm] #`
- **catch_signal.c**: handles `Ctrl + C` (signal) to prevent the shell from exiting (it simply ignores the signal)
- **change_dir.c**: implements changing directory (`cd`), which is not a built-in command in the exec family
- **redirect.c**: provides output redirection to standard output

The `Makefile` builds an executable called `customshell`. To run the shell on Ubuntu, simply type make:

```bash
make
./customshell
```
# Example usage:
```bash
[19/03 11:34] # ls
Makefile  catch_signal.c  change_dir.c  customshell  date.c  exec.c  header.h  main.c  redirect.c
[19/03 11:34] #
```

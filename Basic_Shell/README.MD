# bshell — Basic Shell

A custom Unix shell built from scratch in C as part of learning systems programming and OS internals (OSTEP).



---

## Features

- REPL loop — Read, Evaluate, Print, Loop
- Command execution — runs any external command via `fork()` + `execvp()`
- Pipes — `ls -l | grep foo`
- Redirection — `ls > file.txt`, `echo hi >> file.txt`, `grep foo < file.txt`
- Built-in commands — `cd`, `exit`
- Colored prompt — ANSI escape codes

---

## Demo

### Basic Commands

[screenshot: type these commands one by one → ls | pwd | echo "hello world"]

### Pipes

[screenshot: type → ls -l | grep bshell]

### Redirection

[screenshot: type these in order →
echo "hello from bshell" > out.txt
cat out.txt
echo "second line" >> out.txt
cat out.txt
grep bshell < out.txt
]

### Built-in cd

[screenshot: type these in order →
pwd
cd /tmp
pwd
cd
pwd
]

### Error Handling

[screenshot: type → cd /fakepath    (shows "cd failed: No such file or directory")]

---

## Build

```bash
gcc -Wall -o bshell bshell.c
./bshell
```

---

## How It Works

```
Input line
    ↓
read_line()        getline() reads from stdin safely
    ↓
tokenize()         strtok() splits line into args[]
    ↓
handle_builtins()  checks for cd, exit
    ↓
find_pipe()        checks for | in args
find_redirect()    checks for >, >>, < in args
    ↓
execute()          fork() + execvp() + wait()
execute_pipe()     two forks + pipe() + dup2()
execute_redirect() one fork + open() + dup2()
```

---

## What I Learned

- Process management — `fork()`, `execvp()`, `wait()`
- File descriptors and `dup2()` for piping and redirection
- `getline()` for safe input reading
- `strtok()` for tokenizing strings
- ANSI escape codes for terminal colors
- Memory management — `malloc()`, `free()`, `realloc()`
- Why built-in commands like `cd` cannot use `fork()`
- How pipes connect two processes through a shared buffer
- How redirection replaces stdin/stdout with files

---

## Project Structure

```
bshell/
├── bshell.c    main source file
├── cell.h      colors, macros, includes
└── README.md
```

---

## Built With

- C (C11)
- GCC
- Linux system calls — `fork`, `execvp`, `wait`, `pipe`, `dup2`, `open`, `chdir`

---

## References

- Operating Systems: Three Easy Pieces (OSTEP) — ostep.org
- Linux man pages

---

## Author

Tushar Upadhyay — [github.com/Tushar-Upadhiya](https://github.com/Tushar-Upadhyla)

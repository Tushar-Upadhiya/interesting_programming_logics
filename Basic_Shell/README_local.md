# bshell — Basic Shell

A custom Unix shell built from scratch in C as part of learning systems programming and OS internals.

---

## Features

- **REPL loop** — Read, Evaluate, Print, Loop
- **Command execution** — runs any external command via `fork()` + `execvp()`
- **Pipes** — `ls -l | grep foo`
- **Redirection** — `ls > file.txt`, `echo hi >> file.txt`, `grep foo < file.txt`
- **Built-in commands** — `cd`, `exit`
- **Colored prompt** — ANSI escape codes

---

## Build

```bash
gcc -Wall -o bshell bshell.c
```

## Run

```bash
./bshell
```

---

## Usage

```bash
bshell> ls -l
bshell> cd /tmp
bshell> pwd
bshell> ls | grep bshell
bshell> echo "hello" > out.txt
bshell> cat out.txt
bshell> grep bshell < out.txt
bshell> exit
```

---

## How It Works

```
Input line
    ↓
read_line()        getline() reads from stdin safely
    ↓
tokenize()         strtok() splits into args array
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
- Built-in vs external commands and why `cd` can't use `fork()`

---

## Project Structure

```
bshell/
├── bshell.c    main source file
├── cell.h      colors, macros, includes
└── README.md
```

---

## Author

Tushar Upadhiya — [github.com/Tushar-Upadhiya](https://github.com/Tushar-Upadhiya)

Built while studying Operating Systems: Three Easy Pieces (OSTEP)

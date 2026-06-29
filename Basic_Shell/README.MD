# bshell — Basic Shell

A custom Unix shell built from scratch in C as part of learning systems programming and OS internals (OSTEP).

![Image Alt](https://github.com/Tushar-Upadhiya/interesting_programming_logics/blob/main/Basic_Shell/Screenshot_20260629_084232.png)

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

![Image Alt](https://github.com/Tushar-Upadhiya/interesting_programming_logics/blob/main/Basic_Shell/48e83f67eb2e1c22188bf66cb56b6ea78bbef475)

### Pipes

[screenshot: type → ls -l | grep bshell]

### Redirection

![Image Alt](https://github.com/Tushar-Upadhiya/interesting_programming_logics/blob/main/Basic_Shell/645872d9f9da886a6e3ac5cf434375dc40cd9429)

### Built-in cd

![Image Alt](https://github.com/Tushar-Upadhiya/interesting_programming_logics/blob/main/Basic_Shell/38fe41061bba546f0f4fa154c69c214d5718d822)

### Error Handling

![Image Alt](https://github.com/Tushar-Upadhiya/interesting_programming_logics/blob/main/Basic_Shell/a891bc126a7585f9f74f6d8847aec247bb4c25ca)

---

## Build

```bash
gcc -Wall -Wextra -o bshell.out bshell.c
./bshell.out
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

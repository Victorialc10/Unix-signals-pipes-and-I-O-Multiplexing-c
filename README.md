# UNIX Signals, Pipes and I/O Multiplexing in C

This repository contains several C programs developed as part of an Operating Systems lab focused on:

- Signal handling
- Unnamed pipes
- Named pipes (FIFOs)
- Bidirectional inter-process communication
- I/O multiplexing with `select()`

All programs were developed and tested on Linux (Ubuntu).

### 1️⃣ Signals
Programs demonstrating:
- Blocking signals (`SIGINT`, `SIGTSTP`)
- Installing signal handlers
- Counting received signals
- Using `alarm()` and `sigsuspend()` for timed execution and cancellation

Concepts covered:
- `sigaction`
- `sigprocmask`
- `sigpending`
- `alarm`
- `sigsuspend`

---

### 2️⃣ Unnamed Pipes
Programs implementing:
- Shell-like pipeline execution (`command1 | command2`)
- Bidirectional communication using two pipes
- Stop-and-wait synchronization mechanism

Concepts covered:
- `pipe`
- `fork`
- `dup2`
- `execvp`
- `read` / `write`

---

### 3️⃣ Named Pipes (FIFOs)
Programs demonstrating:
- Creating FIFOs with `mkfifo`
- Reading and writing through named pipes
- Handling blocking behavior
- Reopening FIFOs after EOF

Concepts covered:
- `open`
- `O_NONBLOCK`
- `read`
- `write`
- `unlink`

---

### 4️⃣ I/O Multiplexing
Program that:
- Monitors multiple FIFOs simultaneously
- Uses `select()` to detect available input
- Handles EOF correctly and reopens descriptors

Concepts covered:
- `select`
- `fd_set`
- Non-blocking I/O
- Buffer management

---

## 🛠 Compilation

Each program can be compiled using:

```bash
gcc filename.c -o program_name


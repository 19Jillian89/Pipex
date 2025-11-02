# Pipex

![Language](https://img.shields.io/badge/language-C-blue)  ![Score](https://img.shields.io/badge/score-100%2F100-brightgreen)  ![Status](https://img.shields.io/badge/status-complete-success)  ![Bonus](https://img.shields.io/badge/bonus-in%20progress-yellow)  ![42](https://img.shields.io/badge/42-common%20core-black)

---

## 🔍 Project Overview

The **Pipex** project is part of the 42 curriculum and focuses on:
- understanding **UNIX processes**,
- mastering **file descriptors**,
- using **pipes**, **fork()**, **execve()**, and **dup2()**,
- handling **input/output redirection**.

It’s an introduction to **inter-process communication** and how shell pipelines work internally.

---

📁 Project Structure

```
pipex/
├── libft/
│   ├── ft_strlen.c
│   ├── ft_strdup.c
│   ├── ...
│   └── Makefile
├── child_utils.c
├── find_cmd.c
├── handler_error.c
├── mem_utils.c
├── pipex.c
├── pipex.h
├── Makefile
└── README.md
```
---

## ▶️ Execution

<pre>./pipex infile "cmd1" "cmd2" outfile</pre>


## Equivalent to the shell command:

<pre>< infile cmd1 | cmd2 > outfile</pre>

## Example:

<pre>./pipex input.txt "grep hello" "wc -l" output.txt</pre>

---

## 📄 License

This project is for educational purposes only and is part of the 42 Common Core curriculum. [42 Common Core curriculum](https://www.42network.org/),

---

🔗 If you found this project helpful or interesting, consider supporting it by starring ⭐️ or forking.

---

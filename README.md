# 🐚 minishell

minishell is a simple UNIX shell developed as part of the 42 curriculum.  
The goal of this project is to recreate a basic shell by handling commands, processes, and input/output redirections.

---

## 📖 About the Project

minishell replicates the behavior of a basic shell like bash.

It supports command execution, pipes, and redirections while managing processes and signals.

This project focuses on:

- Process creation and management
- File descriptors and redirections
- Pipes
- Parsing and tokenization
- Environment variables
- Signal handling

---

## ⚙️ Features

- Command execution
- PATH resolution
- Pipes (`|`)
- Input and output redirections (`<`, `>`, `>>`)
- Environment variables (`$VAR`)
- Exit status handling (`$?`)
- Signal handling (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`)
- Built-in commands

---

## 🛠 Built-in Commands

- `echo`
- `cd`
- `pwd`
- `export`
- `unset`
- `env`
- `exit`

---

## 📦 Installation

Clone the repository:

```bash
git clone https://github.com/Mert5558/Minishell.git
cd Minishell
```

Compile the project:

```bash
make
```

---

## 🚀 Usage

Run the shell:

```bash
./minishell
```
---

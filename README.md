*This project has been created as part of the 42 curriculum by nfaronia , nnasered.*

# Minishell

## 📝 Description
Minishell is a simplified shell implementation inspired by **bash**.  
The goal is to understand how a shell works internally: handling processes, signals, environment variables, pipes, and redirections.  
It provides hands-on experience with system calls, memory management, and parsing user input.

---

## 📌 Instructions
- The program must run on **Linux**.
- It should handle errors gracefully (invalid commands, inaccessible files, etc.).
- Behavior should mimic **bash** for fundamental cases.

---

### 🛠️ Compilation
Compile the project using:
```
make
```
This will generate the executable `minishell`.

---

### 💻 Execution
Run the shell with:
```
./minishell
```
Examples of supported commands:
```
ls -la
echo "Hello World"
cat file.txt | grep keyword
```

---

## ✅ Features
- Execute system commands via 'execve'.
- PATH resolution.
- Pipes (`|`) support.
- Redirections (`>`, `<`, `>>`, `<<`).
- Signal handling (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`).
- Built-in commands: `cd`, `echo`, `exit`, `env`.
- Environment variable expansion.

--- 

## 🗃️ Resources

### 📚 References
- SIGNALS

    - [Previous project - Minitalk](https://cdn.intra.42.fr/pdf/pdf/196645/en.subject.pdf)
    - [tutorialspoint - signal() function](https://www.tutorialspoint.com/c_standard_library/c_function_signal.htm)
    - man sigaction
    - man 7 signal
- readline
    - dd
- Lexical and Token
    - [Introduction of Lexical Analysis](https://www.geeksforgeeks.org/compiler-design/introduction-of-lexical-analysis/)
    - [Tokens in C](https://www.geeksforgeeks.org/c/tokens-in-c/)
    - [Lexical Analyser in C](https://www.geeksforgeeks.org/c/c-lexical-analyser-lexer/)

- Parser
    - [Parsing - Introduction to Parsers](https://www.geeksforgeeks.org/compiler-design/introduction-of-parsing-ambiguity-and-parsers-set-1/)
    - 

### 🤖 AI Usage

AI assistance was used to :
- help find study resources
- understand algorithms
- clarify edge cases.
- Organize and structure the README.
- Refine descriptions and instructions.
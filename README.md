# simple_shell

Welcome to **Simple Shell**, a team project aimed at building a custom Unix shell in C. This project provides an opportunity to delve into the intricacies of operating systems and enhance your understanding of how command-line interfaces work.

## Project Description

**Simple Shell** is a minimalist command-line interface inspired by Unix shells like Bash and Zsh. The goal is to implement essential features of a shell, including parsing and executing commands, handling system calls, and managing processes.

### Features

- **Command Parsing:** Parse user input into executable commands and arguments.
- **Command Execution:** Execute commands and display output to the standard output.
- **Built-in Commands:** Implement essential built-in commands like `cd`, `exit`, and `help`.
- **Redirection:** Support input and output redirection for command input and output.
- **Pipelines:** Enable the chaining of multiple commands using pipelines.

## Getting Started

To get started with **Simple Shell**, follow these steps:

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/photonkay/simple_shell.git
   cd simple_shell
   ```

2. **Compile the Code:**
   ```bash
   gcc *.c -o simple_shell
   ```

3. **Run the Shell:**
   ```bash
   ./simple_shell
   ```

## Usage

Once the shell is running, you can enter various Unix commands and see the output. The shell supports standard command-line syntax, including pipes (`|`), input redirection (`<`), and output redirection (`>`). Additionally, it includes built-in commands such as `cd` to change directories, `exit` to exit the shell, and `help` to display usage information.

Example:
```bash
$ ls -l | grep .txt
$ cat < input.txt > output.txt
$ cd /path/to/directory
$ help
$ exit
```

## Authors

- Prince Odoi Asare (princeasa2005@gmail.com)
- Emekowa Deborah Chiwendu (triciachiwen@yahoo.com)

Feel free to contribute and make **Simple Shell** even better! If you encounter any issues or have suggestions, please create an issue or submit a pull request.

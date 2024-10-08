# OS-2023 Terminal

This project is a custom terminal emulator created during the first semester of the second year at the **West University of Timisoara, Faculty of Mathematics and Informatics, Computer Science in English**. It serves as an educational project that demonstrates core principles of operating systems and terminal interfaces.

## Features

- **Command Execution**: Supports execution of basic shell commands like `ls`, `cd`, `mkdir`, and more.
- **Input Parsing**: Parses and executes multiple commands, handles piped commands, and manages input/output redirection.
- **Error Handling**: Implements basic error handling for invalid commands or incorrect input.
- **History Feature**: Keeps track of previously executed commands, allowing users to recall them.
- **Process Management**: Supports foreground and background process execution.

## Getting Started

These instructions will help you run and test the terminal emulator on your local machine.

### Prerequisites

Ensure you have the following installed on your system:

- Linux or Unix-based system (for command execution)
- GCC compiler (for building the project)

### Installation

1. **Clone the repository**:

   \`\`\`bash
   git clone https://github.com/ecinteza/OS-2023-Terminal.git
   cd OS-2023-Terminal
   \`\`\`

2. **Compile the source code**:

   \`\`\`bash
   gcc -o terminal terminal.c
   \`\`\`

### Running the Terminal

To start the terminal emulator, run:

\`\`\`bash
./terminal
\`\`\`

- You can then use the terminal as you would a standard shell by typing commands and pressing `Enter`.

### How It Works

- **Command Parsing**: The terminal reads user input, parses the command, and checks for built-in or external commands.
- **Redirection**: Supports output redirection (`>`), input redirection (`<`), and piped commands (e.g., `ls | grep filename`).
- **Process Management**: Handles process creation using `fork()` and `exec()` for executing commands.
- **Error Handling**: Displays informative error messages for unknown commands or syntax issues.

### Future Improvements

- **Scripting Support**: Add support for shell scripts to allow automation of tasks.
- **Tab Completion**: Implement auto-completion for commands and filenames.
- **Extended Built-in Commands**: Expand the set of built-in commands to make the terminal more powerful.

### Troubleshooting

- **Command not found**: Ensure the command is installed on your system or in the correct path.
- **Permissions error**: Some commands may require elevated privileges (`sudo`).

### Contributing

Feel free to fork the repository and submit pull requests. For major changes, please open an issue first to discuss what you would like to change.

### License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

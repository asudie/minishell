The Minishell project is a simplified version of a Unix shell. It includes the following key features:

    Basic command execution: The shell can execute external commands like /bin/ls, using a similar process to how bash operates.
    Built-in commands: Implements essential built-ins such as echo, cd, exit, and others.
    Input/output redirection: Supports features like pipes (|), input redirection (<), and output redirection (>).
    Environment management: Handles environment variables and path resolution for finding executables.
    Signal handling: Manages interrupts (like Ctrl+C) gracefully, without terminating the shell abruptly.
    Parsing and tokenization: Parses user input to handle command arguments, options, and redirection symbols.

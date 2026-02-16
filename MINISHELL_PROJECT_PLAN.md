# MINISHELL PROJECT - 3-WEEK WORK PLAN (2 PEOPLE)
## Following: LEXER → PARSER → EXPANDER → EXECUTOR Architecture

---

## WEEK 1: LEXER + PARSER

### Person A - Week 1

#### 1. Project Setup & Makefile (Day 1)
- [ ] Create project structure (folders: src, include, libft)
- [ ] Setup Makefile with required rules:
  - [ ] NAME rule (creates minishell executable)
  - [ ] all, clean, fclean, re rules
  - [ ] Compilation flags: -Wall -Wextra -Werror
  - [ ] Ensure no re-linking (use proper dependencies)
  - [ ] Link with readline library (-lreadline)
- [ ] Create header file with all necessary structures
- [ ] Integrate libft if using it

#### 2. LEXER - Tokenization (Days 2-4)
**Purpose: Convert raw input string into tokens**

- [ ] **Define token structure:**
  ```c
  typedef enum e_token_type {
      TOKEN_WORD,          // Regular words/commands
      TOKEN_PIPE,          // |
      TOKEN_REDIR_IN,      // <
      TOKEN_REDIR_OUT,     // >
      TOKEN_REDIR_APPEND,  // >>
      TOKEN_REDIR_HEREDOC, // <<
      TOKEN_EOF            // End of input
  } t_token_type;

  typedef struct s_token {
      t_token_type type;
      char *value;
      struct s_token *next;
  } t_token;
  ```

- [ ] **Implement lexer function:**
  - [ ] Read input character by character
  - [ ] Skip whitespaces (spaces, tabs)
  - [ ] Identify operators: |, <, >, <<, >>
  - [ ] Handle words (everything else)
  
- [ ] **Quote handling in lexer:**
  - [ ] When encountering quote (' or "), enter quote mode
  - [ ] Read until closing quote
  - [ ] Keep quote characters in token value (for expander to handle)
  - [ ] Track quote type (single vs double)
  - [ ] **ERROR: Detect unclosed quotes and return error**
  
- [ ] **Word tokenization:**
  - [ ] Collect characters until: whitespace, operator, or quote
  - [ ] Handle quoted strings as part of word tokens
  - [ ] Example: `echo "hello world"` → [TOKEN_WORD: echo], [TOKEN_WORD: "hello world"]
  
- [ ] **Operator tokenization:**
  - [ ] Recognize single-char operators: |, <, >
  - [ ] Recognize double-char operators: <<, >>
  - [ ] Create separate tokens for each operator
  
- [ ] **Output: Linked list of tokens**

- [ ] **Test lexer:**
  - [ ] Input: `echo hello` → tokens: [WORD:echo] [WORD:hello]
  - [ ] Input: `cat < file` → [WORD:cat] [REDIR_IN:<] [WORD:file]
  - [ ] Input: `ls | grep test` → [WORD:ls] [PIPE:|] [WORD:grep] [WORD:test]
  - [ ] Input: `echo "hello world"` → [WORD:echo] [WORD:"hello world"]
  - [ ] Input: `echo 'test'` → [WORD:echo] [WORD:'test']
  - [ ] Input: `echo "unclosed` → ERROR

#### 3. PARSER - Build Command Structure (Day 5)
**Purpose: Convert tokens into command structure (AST)**

- [ ] **Define command structure:**
  ```c
  typedef struct s_redir {
      t_token_type type;      // Type of redirection
      char *file;             // Filename (still with quotes)
      struct s_redir *next;
  } t_redir;

  typedef struct s_cmd {
      char **args;            // Array of arguments (still with quotes)
      t_redir *redirections;  // List of redirections
      struct s_cmd *next;     // Next command in pipeline
  } t_cmd;
  ```

- [ ] **Parse tokens into commands:**
  - [ ] Split token list by pipes (each pipe = new command)
  - [ ] For each command segment:
    - [ ] Collect WORD tokens into args array
    - [ ] Collect redirection tokens + their files into redir list
  
- [ ] **Syntax validation:**
  - [ ] Check pipe at start or end: `| cat` or `cat |` → ERROR
  - [ ] Check redirection without file: `cat <` → ERROR
  - [ ] Check empty commands between pipes: `cat | | grep` → ERROR
  
- [ ] **Output: Command structure (linked list of commands)**

- [ ] **Test parser:**
  - [ ] `echo hello` → cmd[args: [echo, hello], redir: NULL, next: NULL]
  - [ ] `cat | grep test` → cmd1[args: [cat]] → cmd2[args: [grep, test]]
  - [ ] `cat < in > out` → cmd[args: [cat], redir: [<:in, >:out]]

---

### Person B - Week 1

#### 1. Main Loop & Prompt (Days 1-2)
- [ ] **Implement main function:**
  - [ ] Initialize shell (set up signals, environment)
  - [ ] Enter infinite loop
  - [ ] Display prompt using readline()
  - [ ] Read input line
  - [ ] Add non-empty input to history
  - [ ] Check for NULL (ctrl-D) → exit shell
  - [ ] Handle empty input or whitespace-only input → continue

- [ ] **Prompt display:**
  - [ ] Create prompt string (e.g., "minishell$ ")
  - [ ] Use readline() to display and read
  
- [ ] **Test:**
  - [ ] Empty command → new prompt
  - [ ] Spaces/tabs only → new prompt
  - [ ] ctrl-D on empty prompt → exit

#### 2. Signal Handling (Days 3-4)
**Purpose: Handle ctrl-C, ctrl-D, ctrl-\**

- [ ] **Global variable setup:**
  - [ ] Declare ONLY ONE global variable
  - [ ] Must store ONLY signal number
  - [ ] Example: `volatile sig_atomic_t g_signal = 0;`
  - [ ] NOT a structure, NOT multiple globals
  
- [ ] **Signal handlers:**
  - [ ] Create handler for SIGINT (ctrl-C)
  - [ ] Create handler for SIGQUIT (ctrl-\)
  
- [ ] **Interactive mode signals (waiting for input):**
  - [ ] Setup with sigaction() before readline()
  - [ ] **SIGINT (ctrl-C):**
    - [ ] Write newline
    - [ ] Display new prompt using rl_on_new_line() + rl_redisplay()
    - [ ] Clear current input with rl_replace_line("", 0)
    - [ ] Set global variable to signal number
  - [ ] **SIGQUIT (ctrl-\):**
    - [ ] Ignore (SIG_IGN)
  - [ ] **ctrl-D:**
    - [ ] Handled by readline() returning NULL
    - [ ] Exit shell gracefully
    
- [ ] **Execution mode signals (during command execution):**
  - [ ] Setup different handlers before executing command
  - [ ] **SIGINT (ctrl-C):**
    - [ ] Let child process handle it (default behavior)
    - [ ] Parent ignores signal
  - [ ] **SIGQUIT (ctrl-\):**
    - [ ] Let child process handle it (default behavior)
    - [ ] Should print "Quit (core dumped)"
  - [ ] **After command execution:**
    - [ ] Restore interactive mode signal handlers
    
- [ ] **Test:**
  - [ ] ctrl-C on empty prompt → new line + new prompt
  - [ ] ctrl-C after typing → new line + new prompt, buffer clean
  - [ ] Press Enter after ctrl-C → nothing executes
  - [ ] ctrl-\ on empty prompt → nothing
  - [ ] ctrl-D on empty prompt → exit
  - [ ] ctrl-C during `cat` (no args) → interrupt command
  - [ ] ctrl-\ during `cat` (no args) → quit with message

#### 3. EXECUTOR - Basic Setup (Day 5)
**Purpose: Prepare execution infrastructure**

- [ ] **Define execution context:**
  ```c
  typedef struct s_exec {
      char **envp;        // Environment variables
      int last_exit;      // Exit status of last command
  } t_exec;
  ```

- [ ] **Environment setup:**
  - [ ] Copy environment from main's `char **envp` parameter
  - [ ] Or use external `char **environ`
  - [ ] Store in accessible structure
  
- [ ] **Exit status tracking:**
  - [ ] Variable to store last command exit status
  - [ ] Initialize to 0
  - [ ] Update after each command execution

- [ ] **Basic execution skeleton:**
  - [ ] Function to execute single command (stub for now)
  - [ ] Function to execute pipeline (stub for now)
  - [ ] Will be implemented in Week 2

---

## WEEK 2: EXPANDER + EXECUTOR

### Person A - Week 2

#### 1. EXPANDER - Quote Processing (Days 1-3)
**Purpose: Remove quotes and handle quoted strings**

- [ ] **Create expander module:**
  - [ ] Takes command structure from parser
  - [ ] Processes each argument
  - [ ] Returns processed command ready for execution
  
- [ ] **Quote removal logic:**
  - [ ] Iterate through each character in argument
  - [ ] Track quote state (none, single, double)
  - [ ] Build new string without quote characters
  
- [ ] **Single quote handling ('):**
  - [ ] Everything between single quotes is LITERAL
  - [ ] No interpretation of any character (including $, ", \)
  - [ ] Remove the quote characters themselves
  - [ ] Example: `'$USER'` → `$USER` (literal string)
  - [ ] Example: `'hello   world'` → `hello   world` (spaces preserved)
  
- [ ] **Double quote handling ("):**
  - [ ] Preserve everything EXCEPT $
  - [ ] $ should be expanded (handled by variable expander)
  - [ ] Remove the quote characters themselves
  - [ ] Example: `"hello   world"` → `hello   world` (spaces preserved)
  
- [ ] **Mixed quotes:**
  - [ ] Handle adjacent quotes: `"hello"'world'` → `helloworld`
  - [ ] Handle quotes within quotes: handled by state machine
  - [ ] Example: `echo ""$USER'""` requires careful processing
  
- [ ] **Preserve spaces:**
  - [ ] Quoted spaces should NOT split arguments
  - [ ] `echo "hello world"` → args: ["echo", "hello world"] (2 args, not 3)
  
- [ ] **Apply to all command parts:**
  - [ ] Process each argument in args array
  - [ ] Process redirection filenames
  
- [ ] **Test expander (quote processing):**
  - [ ] Input: `['echo', '"hello"']` → `['echo', 'hello']`
  - [ ] Input: `['echo', "'test'"]` → `['echo', 'test']`
  - [ ] Input: `['echo', '"hello world"']` → `['echo', 'hello world']` (one arg)
  - [ ] Input: `['cat', '<', '"file.txt"']` → `['cat', '<', 'file.txt']`

#### 2. EXPANDER - Variable Expansion (Days 4-5)
**Purpose: Expand $VARIABLES and $?**

- [ ] **Variable expansion logic:**
  - [ ] Scan each argument for $ character
  - [ ] Check context: inside single quotes → skip
  - [ ] Inside double quotes or unquoted → expand
  
- [ ] **Identify variable name:**
  - [ ] $ followed by letters, digits, underscore
  - [ ] Stop at: space, operator, quote, end of string
  - [ ] Examples: `$USER`, `$HOME`, `$PATH`
  
- [ ] **Get variable value:**
  - [ ] Use getenv(variable_name)
  - [ ] If variable doesn't exist → expand to empty string
  - [ ] Replace $VAR with its value in the string
  
- [ ] **Exit status expansion ($?):**
  - [ ] Special case: detect `$?`
  - [ ] Replace with last exit status (as string)
  - [ ] Example: if last exit was 127 → `$?` becomes `127`
  
- [ ] **Expansion in different contexts:**
  - [ ] **Unquoted:** `echo $USER` → expand
  - [ ] **Double quotes:** `echo "$USER"` → expand
  - [ ] **Single quotes:** `echo '$USER'` → DON'T expand (already handled)
  
- [ ] **Multiple variables:**
  - [ ] `echo $USER $HOME` → expand both
  - [ ] `echo $?$?` → expand both (same value)
  
- [ ] **Edge cases:**
  - [ ] `$` alone → keep literal
  - [ ] `$ ` ($ + space) → keep literal
  - [ ] `$$` → implementation choice (PID not required)
  - [ ] Undefined variable: `$NOTEXIST` → empty string
  
- [ ] **Process in correct order:**
  1. First handle quotes (know what's in single/double quotes)
  2. Then expand variables (skip single-quoted parts)
  3. Then remove quotes
  
- [ ] **Apply to:**
  - [ ] Command arguments
  - [ ] Redirection filenames
  - [ ] Heredoc content (expand variables in heredoc input)
  
- [ ] **Test expander (variable expansion):**
  - [ ] Set USER=john
  - [ ] Input: `['echo', '$USER']` → `['echo', 'john']`
  - [ ] Input: `['echo', '"$USER"']` → `['echo', 'john']`
  - [ ] Input: `['echo', "'$USER'"]` → `['echo', '$USER']` (literal)
  - [ ] After failed command (exit 1):
    - [ ] Input: `['echo', '$?']` → `['echo', '1']`

---

### Person B - Week 2

#### 1. EXECUTOR - Simple Command Execution (Days 1-2)
**Purpose: Execute single commands (no pipes yet)**

- [ ] **PATH resolution:**
  - [ ] Get PATH from environment: `getenv("PATH")`
  - [ ] Split by ':' delimiter
  - [ ] For each directory in PATH:
    - [ ] Construct full path: directory + "/" + command
    - [ ] Check if file exists with access(path, F_OK)
    - [ ] Check if executable with access(path, X_OK)
    - [ ] If both true → use this path
  
- [ ] **Handle different path types:**
  - [ ] **Absolute path:** `/bin/ls` → use directly
  - [ ] **Relative path:** `./minishell`, `../bin/cmd` → use directly
  - [ ] **Command name:** `ls` → search in PATH
  - [ ] **No PATH:** If PATH unset, can't find commands
  
- [ ] **Execution with fork/execve:**
  - [ ] Fork process with fork()
  - [ ] **In child process:**
    - [ ] Handle redirections (if any) - stub for now
    - [ ] Execute command with execve(path, args, envp)
    - [ ] If execve fails: print error and exit(127)
  - [ ] **In parent process:**
    - [ ] Wait for child with waitpid()
    - [ ] Get exit status with WIFEXITED and WEXITSTATUS
    - [ ] Update last_exit status
    - [ ] Update $? for next expansion
  
- [ ] **Error handling:**
  - [ ] Command not found: print error, exit status 127
  - [ ] Permission denied: print error, exit status 126
  - [ ] execve failed: print error with perror()
  
- [ ] **Test:**
  - [ ] Absolute path: `/bin/ls`, `/bin/echo hello`
  - [ ] Command from PATH: `ls`, `pwd`, `cat`
  - [ ] Relative path: `./a.out` (if exists)
  - [ ] Non-existent command: `nonexistent` → error 127
  - [ ] Check $?: run command, then `echo $?`

#### 2. EXECUTOR - Pipes (Days 3-4)
**Purpose: Execute pipelines**

- [ ] **Pipeline execution:**
  - [ ] Count number of commands in pipeline
  - [ ] Create array of pipe fds: `int pipes[n-1][2]`
  - [ ] Create all pipes before forking: `pipe(pipes[i])`
  
- [ ] **Fork for each command:**
  - [ ] Loop through commands in pipeline
  - [ ] Fork for each command
  - [ ] **In each child:**
    - [ ] **First command:**
      - [ ] Close read end of first pipe
      - [ ] Redirect stdout to write end: `dup2(pipes[0][1], STDOUT_FILENO)`
      - [ ] Close all other pipe fds
    - [ ] **Middle commands:**
      - [ ] Redirect stdin from previous pipe: `dup2(pipes[i-1][0], STDIN_FILENO)`
      - [ ] Redirect stdout to next pipe: `dup2(pipes[i][1], STDOUT_FILENO)`
      - [ ] Close all pipe fds
    - [ ] **Last command:**
      - [ ] Redirect stdin from previous pipe: `dup2(pipes[n-2][0], STDIN_FILENO)`
      - [ ] Close all pipe fds
    - [ ] Execute command with execve
  - [ ] **In parent:**
    - [ ] Close all pipe fds (important!)
    - [ ] Wait for all children
    - [ ] Return exit status of last command
  
- [ ] **Test:**
  - [ ] Simple pipe: `ls | wc -l`
  - [ ] Multiple pipes: `cat file | grep word | sort | uniq`
  - [ ] Error handling: `ls nofile | grep test` (first fails)
  - [ ] Check exit status is from last command

#### 3. EXECUTOR - Redirections (Day 5)
**Purpose: Handle <, >, <<, >>**

- [ ] **Apply redirections before execve:**
  - [ ] Process redirection list for each command
  - [ ] Apply redirections in order (last one wins for same type)
  
- [ ] **Input redirection (<):**
  - [ ] Open file: `open(filename, O_RDONLY)`
  - [ ] Check file exists and readable
  - [ ] Redirect stdin: `dup2(fd, STDIN_FILENO)`
  - [ ] Close original fd
  
- [ ] **Output redirection (>):**
  - [ ] Open file: `open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644)`
  - [ ] Redirect stdout: `dup2(fd, STDOUT_FILENO)`
  - [ ] Close original fd
  
- [ ] **Append redirection (>>):**
  - [ ] Open file: `open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644)`
  - [ ] Redirect stdout: `dup2(fd, STDOUT_FILENO)`
  - [ ] Close original fd
  
- [ ] **Heredoc (<<):**
  - [ ] Create pipe: `pipe(fd)`
  - [ ] Read input lines until delimiter
  - [ ] **Don't add to history** (no add_history calls)
  - [ ] Expand variables in each line (call expander)
  - [ ] Write lines to pipe write end
  - [ ] Close write end
  - [ ] Redirect stdin from read end: `dup2(fd[0], STDIN_FILENO)`
  
- [ ] **Multiple redirections:**
  - [ ] `< in1 < in2` → use in2 (last one)
  - [ ] `> out1 > out2` → use out2 (last one)
  - [ ] `< in > out cat` → both redirections apply
  
- [ ] **Combine with pipes:**
  - [ ] Apply redirections after pipe setup
  - [ ] Redirections override pipe fds
  - [ ] Example: `cat < file | grep word > output`
  
- [ ] **Test:**
  - [ ] `echo hello > file.txt`
  - [ ] `cat < input.txt`
  - [ ] `cat < in > out`
  - [ ] `cat << EOF` (enter lines, end with EOF)
  - [ ] `ls >> log.txt` (check appends)
  - [ ] Mix with pipes: `cat < file | grep test > out`

---

## WEEK 3: BUILT-INS + FINALIZATION

### Person A - Week 3

#### 1. Built-in: echo (Day 1)
- [ ] **Implementation:**
  - [ ] Check if command is "echo"
  - [ ] Parse -n option (must be first argument)
  - [ ] Handle multiple -n flags: `echo -n -n test` (treat as one -n)
  - [ ] Print arguments separated by single space
  - [ ] Print newline at end (unless -n flag)
  
- [ ] **Test:**
  - [ ] `echo hello world` → "hello world\n"
  - [ ] `echo -n test` → "test" (no newline)
  - [ ] `echo -n -n hello` → "hello" (no newline)
  - [ ] `echo -n` → "" (just no newline)
  - [ ] `echo` → "\n" (empty line)

#### 2. Built-in: pwd (Day 1)
- [ ] **Implementation:**
  - [ ] Use getcwd() to get current directory
  - [ ] Print to stdout with newline
  - [ ] Handle errors (buffer too small, deleted directory)
  
- [ ] **Test:**
  - [ ] `pwd` in different directories
  - [ ] Compare with /bin/pwd output

#### 3. Built-in: cd (Day 2)
- [ ] **Implementation:**
  - [ ] Check if command is "cd"
  - [ ] Handle one argument (directory path)
  - [ ] Use chdir(path) to change directory
  - [ ] Handle errors: directory doesn't exist, no permissions
  - [ ] Print error message on failure
  
- [ ] **Special cases:**
  - [ ] `cd .` → stay in current directory
  - [ ] `cd ..` → go to parent directory
  - [ ] Relative path: `cd dirname`
  - [ ] Absolute path: `cd /tmp`
  - [ ] `cd` with no args → decision (HOME or error)
  
- [ ] **Update environment (optional but good):**
  - [ ] Update PWD variable
  - [ ] Update OLDPWD variable
  
- [ ] **Test:**
  - [ ] Navigate to different directories
  - [ ] Verify with `/bin/ls` or `pwd`
  - [ ] Test `cd ..` multiple times
  - [ ] Test non-existent directory → error

#### 4. Built-in: env (Day 3)
- [ ] **Implementation:**
  - [ ] Check if command is "env"
  - [ ] No arguments or options
  - [ ] Print all environment variables
  - [ ] Format: VAR=value (one per line)
  - [ ] Use stored environment array
  
- [ ] **Test:**
  - [ ] `env` → print all variables
  - [ ] Compare with system env
  - [ ] Verify exported variables appear

#### 5. Built-in: export (Day 4)
- [ ] **Implementation:**
  - [ ] Check if command is "export"
  - [ ] Parse argument format: VAR=value
  - [ ] Split by first '=' to get name and value
  - [ ] Add/update in environment array
  - [ ] Handle multiple exports: `export A=1 B=2`
  - [ ] Handle export without value: `export VAR` (declare only)
  
- [ ] **Environment management:**
  - [ ] Maintain custom environment list
  - [ ] Reallocate array when adding new variables
  - [ ] Update existing variables
  - [ ] Make available to child processes
  
- [ ] **Test:**
  - [ ] `export TEST=value` then `env` → should see TEST=value
  - [ ] `export USER=newname` → update existing
  - [ ] `export A=1 B=2 C=3` → multiple at once
  - [ ] Verify child processes see exported variables

#### 6. Built-in: unset (Day 5)
- [ ] **Implementation:**
  - [ ] Check if command is "unset"
  - [ ] Remove variable from environment
  - [ ] Handle multiple unsets: `unset VAR1 VAR2`
  - [ ] No error if variable doesn't exist
  - [ ] Rebuild environment array without removed variables
  
- [ ] **Test:**
  - [ ] `export TEST=value` then `unset TEST` then `env` → TEST gone
  - [ ] `unset NONEXISTENT` → no error
  - [ ] `unset VAR1 VAR2 VAR3` → remove multiple

---

### Person B - Week 3

#### 1. Built-in: exit (Day 1)
- [ ] **Implementation:**
  - [ ] Check if command is "exit"
  - [ ] Handle different cases:
    - [ ] No arguments: exit with last command status
    - [ ] One numeric argument: exit with that code
    - [ ] Non-numeric argument: print error, exit with error code
    - [ ] Multiple arguments: print error, don't exit
  
- [ ] **Cleanup before exit:**
  - [ ] Free all allocated memory
  - [ ] Close all open file descriptors
  - [ ] Clear history with rl_clear_history()
  
- [ ] **Test:**
  - [ ] `exit` → exit with last status
  - [ ] `exit 0` → exit with 0
  - [ ] `exit 42` → exit with 42
  - [ ] `exit hello` → error message
  - [ ] `exit 1 2` → error, don't exit

#### 2. Built-in Detection & Execution (Day 2)
- [ ] **Identify built-ins:**
  - [ ] Check command name against: echo, cd, pwd, export, unset, env, exit
  - [ ] Case-sensitive comparison
  
- [ ] **Execute built-ins:**
  - [ ] **NOT in pipeline:** Execute in parent process (don't fork)
  - [ ] **In pipeline:** Must fork (to allow pipe redirection)
  
- [ ] **Built-in redirections:**
  - [ ] Built-ins must respect redirections
  - [ ] `echo hello > file` should work
  - [ ] Save original stdin/stdout, restore after
  
- [ ] **Update $?:**
  - [ ] Set exit status to 0 on success
  - [ ] Set to appropriate error code on failure
  
- [ ] **Test:**
  - [ ] `echo hello` → executes in parent
  - [ ] `echo hello | cat` → echo must fork
  - [ ] `pwd > file` → output goes to file
  - [ ] Verify $? after built-in commands

#### 3. PATH Management & Testing (Day 3)
- [ ] **PATH tests:**
  - [ ] Commands work without path: `ls`, `cat`, `grep`
  - [ ] Set PATH to custom value: `export PATH=/bin:/usr/bin`
  - [ ] Verify search order (left to right)
  - [ ] First directory has priority
  
- [ ] **Unset PATH:**
  - [ ] `unset PATH`
  - [ ] Commands should fail: "command not found"
  - [ ] Built-ins should still work
  - [ ] Absolute paths should still work: `/bin/ls`
  
- [ ] **Test:**
  - [ ] Normal PATH → `ls` works
  - [ ] Custom PATH → verify correct executable chosen
  - [ ] No PATH → `ls` fails, `/bin/ls` works
  - [ ] Complex relative paths with `../../../`

#### 4. Error Handling & Edge Cases (Day 4)
- [ ] **Command errors:**
  - [ ] Command not found: proper error message + exit 127
  - [ ] Permission denied: proper error message + exit 126
  - [ ] Use perror() or strerror() for system errors
  
- [ ] **Syntax errors:**
  - [ ] Unclosed quotes: "Error: unclosed quotes"
  - [ ] Invalid operators: `cat |` or `| grep`
  - [ ] Redirection without file: `cat <`
  
- [ ] **File errors:**
  - [ ] Input file doesn't exist: error message
  - [ ] Output file can't be created: error message
  - [ ] Permission denied on files
  
- [ ] **Handle gracefully:**
  - [ ] Invalid commands don't crash shell
  - [ ] Errors print message, shell continues
  - [ ] `dsbksdgbksdghsd` → error, new prompt
  
- [ ] **Test:**
  - [ ] All error cases from evaluation sheet
  - [ ] `cat nonexistent` → error message
  - [ ] `cat < nofile` → error message
  - [ ] Shell keeps running after errors

#### 5. Memory Management (Day 5)
- [ ] **Memory leak checking:**
  - [ ] Run valgrind: `valgrind --leak-check=full --show-leak-kinds=all ./minishell`
  - [ ] Test each feature separately
  - [ ] Test combined features
  
- [ ] **Free allocated memory:**
  - [ ] Free tokens after parsing
  - [ ] Free command structures after execution
  - [ ] Free environment copy
  - [ ] Free expanded strings
  - [ ] Free redirections
  
- [ ] **Close file descriptors:**
  - [ ] Close all opened files
  - [ ] Close pipe fds
  - [ ] Check for fd leaks
  
- [ ] **Note:**
  - [ ] readline() internal leaks are OK
  - [ ] Only YOUR code must not leak
  
- [ ] **Test:**
  - [ ] Run valgrind on simple commands
  - [ ] Run valgrind on complex pipelines
  - [ ] Run valgrind with multiple redirections
  - [ ] Exit cleanly with all memory freed

---

## INTEGRATION & FINAL TESTING (Both - Days 6-7 of Week 3)

### Integration Tasks:

#### 1. Code Integration
- [ ] Merge Person A and Person B code
- [ ] Resolve any conflicts
- [ ] Ensure consistent coding style
- [ ] Review each other's code

#### 2. Module Testing
- [ ] **Test the pipeline:**
  - [ ] Input → LEXER → tokens
  - [ ] Tokens → PARSER → command structure
  - [ ] Command structure → EXPANDER → expanded commands
  - [ ] Expanded commands → EXECUTOR → results
  
- [ ] **Verify each stage:**
  - [ ] Print tokens after lexer (debug mode)
  - [ ] Print parsed commands (debug mode)
  - [ ] Print expanded args (debug mode)
  - [ ] Verify execution results

#### 3. Comprehensive Testing (Evaluation Sheet)

**Compile checks:**
- [ ] `make -n` shows -Wall -Wextra -Werror
- [ ] Compiles without errors
- [ ] No re-linking

**Simple commands:**
- [ ] `/bin/ls` (absolute path)
- [ ] `ls -la` (from PATH)
- [ ] `./program` (relative path)
- [ ] Empty command
- [ ] Spaces/tabs only

**Arguments:**
- [ ] `/bin/ls -la /tmp`
- [ ] Multiple arguments
- [ ] Different commands with args

**echo:**
- [ ] `echo hello world`
- [ ] `echo -n test`
- [ ] `echo -n -n hello`
- [ ] `echo` (alone)

**exit:**
- [ ] `exit`
- [ ] `exit 0`
- [ ] `exit 42`
- [ ] `exit hello` (error)
- [ ] `exit 1 2` (multiple args)

**Return value ($?):**
- [ ] `/bin/ls; echo $?` → 0
- [ ] `ls nofile; echo $?` → non-zero
- [ ] `expr $? + $?`

**Signals:**
- [ ] ctrl-C on empty prompt → new line + prompt
- [ ] ctrl-\ on empty prompt → nothing
- [ ] ctrl-D on empty prompt → exit
- [ ] ctrl-C after typing → new line + clean buffer
- [ ] Press Enter after ctrl-C → nothing executes
- [ ] ctrl-D after typing → nothing
- [ ] ctrl-\ after typing → nothing
- [ ] ctrl-C during `cat` → interrupt
- [ ] ctrl-\ during `cat` → quit message
- [ ] ctrl-D during `cat` → send EOF

**Double quotes:**
- [ ] `echo "hello world"` → preserves spaces
- [ ] `echo "cat file | grep"` → literal
- [ ] `echo "$USER"` → expands variable

**Single quotes:**
- [ ] `echo '$USER'` → prints $USER
- [ ] `echo 'hello   world'` → preserves spaces
- [ ] No interpretation in single quotes

**env:**
- [ ] `env` → shows all variables

**export:**
- [ ] `export TEST=value`
- [ ] `env` → verify TEST appears
- [ ] `export A=1 B=2`

**unset:**
- [ ] `export TEST=value; unset TEST; env` → TEST gone
- [ ] `unset VAR1 VAR2`

**cd:**
- [ ] `cd /tmp; pwd`
- [ ] `cd ..; pwd`
- [ ] `cd .; pwd`
- [ ] `cd nodir` → error

**pwd:**
- [ ] `pwd` in different directories

**Relative path:**
- [ ] `../../bin/ls`
- [ ] Complex paths with ..

**PATH:**
- [ ] Commands work: `ls`, `cat`
- [ ] `unset PATH` → commands fail
- [ ] `export PATH=/bin:/usr/bin` → check order

**Redirections:**
- [ ] `echo hello > file`
- [ ] `cat < file`
- [ ] `cat << EOF`
- [ ] `ls >> log`
- [ ] `< in > out cat`
- [ ] Multiple: `< in1 < in2`

**Pipes:**
- [ ] `cat file | grep test`
- [ ] `ls | wc -l`
- [ ] `cat | grep | more`
- [ ] `ls nofile | grep test`
- [ ] Mix: `cat < in | grep | sort > out`

**History:**
- [ ] Up/Down arrows navigate
- [ ] Retry previous command

**Environment variables:**
- [ ] `echo $USER`
- [ ] `echo "$USER"` → expands
- [ ] `echo '$USER'` → doesn't expand
- [ ] Undefined variable → empty

**Edge cases:**
- [ ] Invalid command → error, shell continues
- [ ] Long command with many arguments
- [ ] `catcat | ls` → normal error handling

**Complex test:**
- [ ] `echo ""$USER'""` → complex quote handling

#### 4. Memory Leak Final Check
- [ ] Run valgrind on ALL test cases
- [ ] Fix any leaks in YOUR code
- [ ] Document readline leaks as acceptable

#### 5. Final Cleanup
- [ ] Remove debug prints
- [ ] Remove commented code
- [ ] Ensure proper indentation
- [ ] Check norm (if applicable)
- [ ] Verify all required files present
- [ ] Test Makefile rules (all, clean, fclean, re)

---

## ARCHITECTURE SUMMARY

```
INPUT (readline)
      ↓
   LEXER (Person A, Week 1)
   - Tokenize input
   - Handle quotes (don't remove yet)
   - Detect operators
      ↓
   TOKENS
      ↓
   PARSER (Person A, Week 1)
   - Build command structure
   - Syntax validation
   - Organize redirections
      ↓
   COMMAND STRUCTURE
      ↓
   EXPANDER (Person A, Week 2)
   - Remove quotes
   - Expand variables ($VAR, $?)
   - Process in correct order
      ↓
   EXPANDED COMMANDS
      ↓
   EXECUTOR (Person B, Week 2)
   - Fork/execve
   - Setup pipes
   - Setup redirections
   - Execute built-ins
      ↓
   RESULT + EXIT STATUS
      ↓
   Update $? and continue
```

---

## CRITICAL REMINDERS

### Global Variable:
- **ONLY ONE** allowed
- Store **ONLY signal number**
- Example: `volatile sig_atomic_t g_signal;`
- **NOT a structure**

### Processing Order:
1. **Lexer:** String → Tokens (keep quotes)
2. **Parser:** Tokens → Command structure (keep quotes)
3. **Expander:** Process quotes → Expand variables → Remove quotes
4. **Executor:** Execute processed commands

### Quote Handling:
- **Lexer:** Identify and preserve quotes
- **Parser:** Keep quotes in arguments
- **Expander:** 
  1. Identify quote regions
  2. Expand variables (skip single quotes)
  3. Remove quote characters
- Single quotes: NO interpretation
- Double quotes: Only $ expands

### Variable Expansion:
- Must happen AFTER quote identification
- Must respect quote context
- Must happen BEFORE quote removal
- $? updates after each command

### Built-ins:
- Execute in parent (unless in pipeline)
- Must work with redirections
- Update $? appropriately

### Heredoc:
- Don't add to history
- DO expand variables
- Read until delimiter

### Memory:
- readline() leaks = OK
- YOUR code leaks = NOT OK
- Test with valgrind regularly

---

## PERSON RESPONSIBILITIES

**Person A:**
- Lexer (tokenization)
- Parser (command structure)
- Expander (quotes + variables)
- Built-ins: echo, pwd, cd, env, export, unset

**Person B:**
- Main loop & prompt
- Signal handling
- Executor (fork/exec, pipes, redirections)
- Built-in: exit
- Built-in integration
- PATH management

**Shared:**
- Integration testing
- Memory leak checking
- Final testing against evaluation sheet

## Installation

### Clone
```bash
git clone https://github.com/octoross-42/minishell.git
cd minishell
```
### Execution
```bash
make
./minishell
```


### Compilation on Linux
**GCC et Make** :
   
   ```bash
   sudo apt update
   sudo apt install build-essential
```



# Project Workflow 

The way minishell works is quite simple, it is just as it follows :

```mermaid
stateDiagram-v2
	direction LR
    state "init" as init
    state "input" as input
    state "parsing" as parsing
    state "exec" as execution

    state "exit" as exit
	
	init --> input
	input --> parsing
	parsing --> execution
	execution --> exit
	execution --> input

```

Obviously, things will get more difficult... Let's dive into it !

## Signals

In minishell, we must handle `Ctrl+d` and `Ctrl+c` (and `Ctrl + \` but it doesn't do anything).
Signals are simple, here is doc for signals handling:
https://www.ibm.com/docs/en/zos/3.1.0?topic=functions-sigaction-examine-change-signal-action
On our part we'll focus on the structure of the program.
In this project, we set different use of signals for user input, execution and for here_docs.

(actually `Ctrl+d` isn't a signal but just an `EOF` (meaning end of file), but since we are considering the program's checkpoints, this will do)
### Input signals:

```mermaid
stateDiagram-v2
	direction LR
 	state "setup
	input signals" as input_sig
	state "user input" as input
	state "Ctrl+d" as eof
	state "Ctrl+c" as interrupt
	state "No signal" as no
	state "execution" as exec

	input_sig --> input
	input --> eof
	input --> interrupt
	input --> no
	eof --> exit
	interrupt --> input
	no --> exec
	exec --> input
```   

### Execution signals  
```mermaid
stateDiagram-v2
	direction LR
    state "setup
	exec signals" as exec_sig
    state "input" as input
    state "exec" as execution
    state "exit" as exit
	state "no signal" as no
	state "Ctrl+c" as interrupt
	state "cmd" as cmd

	[*] --> input
	input -->exec_sig
	exec_sig --> execution
	execution --> no
	no --> cmd
	cmd --> input
	execution --> interrupt
	interrupt --> exit
```
### Execution signals  
```mermaid
stateDiagram-v2
	direction LR
	state "setup
	here_doc signals" as sig
	state "here_doc" as hd 
	state "no signal" as no
	state "exec" as execution
	state "Ctrl+d" as eof
	state "Ctrl+c" as int
	state "warning here_doc" as warning

	[*] --> execution
	execution --> hd
	hd --> sig
	sig --> no
	sig --> eof
	eof --> warning
	sig --> int
	warning --> execution
	no --> execution
	int --> execution
```

Now these are quite simple, but it really helps to have a global structure overview.
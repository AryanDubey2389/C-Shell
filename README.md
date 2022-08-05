
  

## INRUCTIONS TO RUN CODE


- First use make command to compile the program.
- Then write ./a.out in the terminal to execute the program.
- To get exit from the shell use command exit.

 
## Contents OF THE FILE

- I did whole code using files ,i.e, main.c prompt.c,pinfo.c, repeat.c, command_ls.c, command_cd.c, history.c, ini_history.c,listing.c, listing_l.c,headers.h prompt.h and history.txt.

- The main code is in main.c and with the help of this i am calling every other functions to execute the commands.

- In history.txt i am storing 20 previous commands.

## Functionas of my Shell

- Built-in commands: `ls`with a and l flags, `echo`, `pwd`, `cd`, `history`, `pinfo`, `jobs`, `fg`, `bg`, `exit`.

- I have also implemeneted piping and redirection

- I have also handled signals like `SIGINT` and `SIGTSTP`

- I have made a prompt that shows the username, hostname and the current working directory and the working directory is with respect to the directory in which you are running the shell.

- I have also done proper error handling.  
  

## Functions of each file

-  `main.c` : It contains the main code from which I am calling every other functions.

-  `prompt.c` : It calls almost every function as per the requirements and prints the shell.

-  `command_cd.c` : It contains all the functions to execute `cd` command

-  `command_ls.c` : It contains all the functions to implement `ls` command

-  `listing.c` : It prints the values as per the request of `command_ls.c` for ls without flag and with flag -a.

-  `listing_l.c` : It prints the values as per the requirements of `command_ls.c` for the remaining flags.

-  `pinfo.c` : It executes `pinfo` commands as per the given requirements.

-  `history.c` : It adds the new command in `history.txt` and returns everything stored in that file in form of array with the help of which we print from `ini_history.c` .

-  `ini_history.c`: It prints history as per our requirements.

-  `makefile` : It compiles all the files.

-  `README.md` : It has instructions and explaination of my whole shell.

-  `prompt.h`: It contains some globally declared functions.

-  `headers.h`:It contains all the header files which are required to run the shell.

  

### Functioning of my shell

- Initiallly you will see your username and hostname along with the directory you are present in and the relative path with respect to the folder from which you are running you shell.

- Their will be blank where you need to give input and then it will print the respective outputs on your terminal or in your file (in case you redirected).


### Explaining every command i made

`ls`: Here it will print conents of a folder based upon the path given and also given flags. And you just need to write ls `path`  `flags`.

`echo`: It will anything written after echo.

`pwd`:It will give the your current directory information. And it will be a absolute path.

`cd`: It will help you in going to any directory, and you just need to write cd `path`.

`history`: If you will write only history then it will print previous 10 commands otherwise for a particular number you need to write history `number`.

`pinfo`: It will give you information about a process. You can execute it pinfo `process id` of that process.

`jobs`:It will list all the jobs currently running in the background. It also has the flags -r and -s for running and stopped processes.

`fg`:It will convert currently ongoing process to foregrorund. Format is fg `process number`.

`bg`:Changes the state of a stopped background job to running (in the background). Format bg `process number`.
`baywatch`:  I implemented three flags here `interrupt`, `newborn` and `dirty`. In each case as given in the question it prints till we enter 'q'. In `newborn` it print the PID of the process that was most recently created on the system. In `interrupt` print the number of times the CPU(s) has(ve) been interrupted by the keyboardcontroller (i8042 with ​IRQ 1​).In `dirty` it print the size of the part of the memory which is dirty
`exit`:It will help you to get exit from the shell.

### Piping and Redirection

- I have also done redirection with the help of which you can take input from a file, write or append your ouput in a file.

-  `<`, `>` and `>>` These are the three redirections `<` is used to get input from a file, `>` is used to write your output in a file and `>>` is used to append your output to file.

- Piping is also performed here you can use `|` to use piping.

- I have done this through duplicating file descriptors of the standard I/O files and swapping them with others as per the requirements.
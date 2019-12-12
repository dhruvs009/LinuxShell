# LinuxShell
This is a small implementation of a baic Shell that I made during my Computer Architecture and Operating Systems course written in C using forking and wating.

## How to run?
1. Clone the repository using `git clone https://github.com/dhruvs009/LinuxShell.git`. <br>
2. Navigate to the downloaded directory. <br>
3. Run `make`. <br>
4. Run `./main` to run the shell. <br>

## Some Implementations: 
External Commands:
All external commands whose binaries exist at /usr/bin work with all predefined flags as well. <br><br>
For echo commands the flags -n and -e can be used with all possible combinations handled for the input. For the 
cd command the arguments combination have been hadled well (at least one directory is required and not more than one 
directory can be given at once). pwd command doesn't take any flags or any arguments and suitable error is shown if 
any of them are given. history command works using file handling (a file is created at execution at the directory where
the shell executables are located) and this doesn't take any arguments as well. exit works normally (no arguments and 
must exit the shell). <br>

For the external commands execv(), fork(), and wait() have been used to execute the binaries of the required commands
in a child process and show the expected output. In case of any errors, suitable error message is also shown. The external
commands work with any number of arguments (any number of flags that are available). In case of unexpected or incorrect
inputs, the shell shows appropriate error messages as well. <br>

> Dhruv Sahnan <br>
> Computer Architecture and Operating Systems | Monsoon'19 <br>
> B.Tech CSAM | Batch of 2022 <br>
> IIIT Delhi

# MD5 Message Digest Algorithm
Author: Sean Moylan

## Introduction

In 1991 [Ronald Rivest](https://en.wikipedia.org/wiki/Ron_Rivest) created the MD5 message-digest algorithm that generates a unique 128-bit digital signature from a given input message (file) known as the message-digest.

Contained in this repository is my own vesion of the MD5 alogrithm that was an assignment given to me as part of the Theory of Algorithms module completed during 4th year Software Development in GMIT.

You will find MD5.c where I have recreated the MD5 algorithm from the original standard. You will also find MD5.exe which is a executable version of the program that can be run from the terminal. For testing perposes I have added a file named hello.txt that contains the test string "hello world".

The MD5 algorithm was initially designed to be a cryptographic hash function but was later found to have "extensive vulnerablities". That said it is still used to this day to varify document integrity. 

Please find instructions bellow for how to run the code found in this repository along with a thorough breakdown of the algorithm in my own words

## Run

For this project I used the GCC Compiler wich can be installed on Linux, Windows and Mac. Please follow instuctions for the apropriate device you wish to run this repos code on.

- Windows
  - [Here](https://www.codeblocks.org/downloads/binaries) you will find the binaries for an IDE named Codeblocks that contains the compiler you will need
  - [Here](https://www.journaldev.com/25757/c-compiler-windows-gcc) is a useful guide for installing the Codeblocks IDE on you windows device
- Mac and Linux
  - First open your terminal and check if you already have GCC installed by running `gcc --version` 
  - Using [Homebrew](https://brew.sh) follow the steps below
  - `brew update`
  - `brew upgrade`
  - `brew info gcc`
  - `brew install gcc`
  - Finally `brew cleanup`- this removes previous application/dependency revisions saving considerable space
  - Then varify it is intalled correctly by running `gcc --version`

Steps to compile and run the original MD5.c file:

1. Clone this repo to your device.
2. Open terminal and navigate to the dir you saved the repo to.
3. Once inside the dir type `gcc MD5.c -o MD5` this will compile an executable
4. Now you can type `./MD5 -o <filename>` where the filename is the input for the Message Digest
5. Once run you sould see MD5(filename): followed by a 128 bit Message digest of the input file

## Test

To run a test on the MD5.c file:

1. Clone this repo to your device.
2. Open terminal and navigate to the dir you saved the repo to.
3. Once inside the dir type `gcc MD5.c -o MD5` this will compile an executable
4. Now you can type `./MD5 -t` 
5. The program will then generate a message digest on a predefined string `hello world` and output to the terminal

## Algorithm

Simplistically speaking there are just 5 steps to the MD5 algorithm tho each comes with its own complexities. Below i outline the steps and the section they relate to in the specification.

1. Append padding bits - section 3.1
2. Append length - section 3.2
3. Initialise MD buffers - section 3.3
4. Process message in 16-Word blocks - section 3.4
5. Output Message Digest - section 3.5

I feel it is best you first familiarise yourself with the terminology I have laid out below as it is used in the  [MD5 Standard](https://tools.ietf.org/html/rfc1321) and will help you better understand some of the technical aspects of the algorithm.

### Terminology - section 2

Here I have stated the terminology used in the MD5 algorithm which can also be found in the [MD5 Standard](https://tools.ietf.org/html/rfc1321):

|  Term   |                    Meaning                    |
| :-----: | :-------------------------------------------: |
|  word   |      Represents a 32-bit space in memory      |
|  byte   |      Represents a 8-bit space in memory       |
|   x_i   |              Represents x sub i               |
|   x^i   |        Represents x to the i-th power         |
|    +    |   Addition of words (modulo-2^32 addition)    |
| X <<< s | Circularly shifting X left by s bit positions |

### Bitwise Operators - section 2

Bit-wise operators are used in c to operate on eight bit (byte) strings of memory. Click [here](https://en.wikipedia.org/wiki/Bitwise_operations_in_C) to find out more about bit-wise operators. The following are used within the MD5 algorithm:

| Term   | Meaning                  |
| ------ | ------------------------ |
| not(X) | bit-wise complement of X |
| X or Y | bit-wise XOR of X and Y  |
| XY     | bit_wise AND of X and Y  |

### 1. Append padding bits

Padding is performed on





## Complexity

## References

- https://tools.ietf.org/html/rfc1321
- https://www.tutorialspoint.com/cprogramming/index.htm
- https://github.com/ianmcloughlin?tab=repositories&q=&type=&language=c
- https://www.geeksforgeeks.org/union-c/
- https://www.geeksforgeeks.org/command-line-arguments-in-c-cpp/
- http://www.gnu.org/software/libc/manual/html_node/Getopt.html
- https://www.tutorialspoint.com/unix_commands/getopt.htm
- http://courses.cms.caltech.edu/cs11/material/general/usage.html
- https://stackoverflow.com/questions/9642732/parsing-command-line-arguments-in-c
- https://discussions.apple.com/thread/8336714
- https://brew.sh
- https://www.codeblocks.org/downloads/binaries
- https://www.journaldev.com/25757/c-compiler-windows-gcc


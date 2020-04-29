# MD5 Message Digest
Author: Sean Moylan

## Introduction

In 1991 [Ronald Rivest](https://en.wikipedia.org/wiki/Ron_Rivest) created the MD5 message-digest algorithm that generates a unique 128-bit digitial signature from a given input message (file) known as the message-digest.

In this repository you will find MD5.c where I have recreated the MD5 algorithm from the original standard. You will also find MD5 which is a compiled version of the program that can be run from the terminal.

## Terminology 

Here I have stated the terminology used in the MD5 algorithm which can also be found in the [MD5 Standard](https://tools.ietf.org/html/rfc1321) 

|  Term   |                    Meaning                    |
| :-----: | :-------------------------------------------: |
|  word   |      Represents a 32-bit space in memory      |
|  byte   |      Represents a 8-bit space in memory       |
|   x_i   |              Represents x sub i               |
|   x^i   |        Represents x to the i-th power         |
|    +    |   Addition of words (modulo-2^32 addition)    |
| X <<< s | Circularly shifting X left by s bit positions |

### Bitwise Operators

Bit-wise operations are used in c to operate on eight bit (byte) strings of memory. Click [here](https://en.wikipedia.org/wiki/Bitwise_operations_in_C) to find out more about bit-wise operators. The following 

| Term   | Meaning                  |
| ------ | ------------------------ |
| not(X) | bit-wise complement of X |
| X or Y | bit-wise XOR of X and Y  |
| XY     | bit_wise AND of X and Y  |

## Run

Steps to compile and run the orginal MD5.c file:

1. Clone this repo to your device.
2. Open terminal and navigate to the dir you saved the repo to.
3. Once inside the dir type `gcc MD5.c -o MD5` this will compile an executable
4. Now you can type `./MD5 <filename>` where the filename is the input for the Message Digest
5. Once run you sould see MD5<filename> followed by a 128 bit Message digest of the input file

## Test

To run a test on the MD5.c file:

1. Clone this repo to your device.
2. Open terminal and navigate to the dir you saved the repo to.
3. Once inside the dir type `gcc MD5.c -o MD5` this will compile an executable
4. Now you can type `./MD5 -t` 
5. The program will then generate a message digest on a predefined string `hello world` and output to the terminal

## Algorithm

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


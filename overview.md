# MD5 Message-Digest Algorithm
Author: Sean Moylan

## Introduction

In 1991 [Ronald Rivest](https://en.wikipedia.org/wiki/Ron_Rivest) created the MD5 message-digest algorithm that generates a unique 128-bit digital signature from a given input message (file) known as the message-digest.

Contained in this repository is my own version of the MD5 algorithm that was an assignment given to me as part of the Theory of Algorithms module completed during 4th year Software Development in GMIT.

You will find MD5.c where I have recreated the MD5 algorithm from the original standard. You will also find MD5.exe which is a executable version of the program that can be run from the terminal. For testing perposes I have added a file named hello.txt that contains the test string "hello world".

Please find instructions below for how to run the code found in this repository along with a thorough breakdown of the algorithm and its complexities in my own words.

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

Simplistically speaking there are just 5 steps to the MD5 algorithm tho each comes with its own complexities. Below I outline the steps and the section they relate to in the specification.

1. ### Append padding bits - section 3.1

   The blocks that get processed are in multiples of 512-bits, that said not all messages will be multiple of 512 so to compensate for this we use padding to pad the last block in the massage with 0's leaving 64-bits at the end for our message length. To begin the padding we first append a '1' bit followed then by '0' bits until the block is congruent with 448, modulo 512. This means that at very least there is 1 x '0' bit appended or at most 512 bits

   

2. ### Append length - section 3.2

   The 64-bits that is left at the end of the last block is reserved for the 64-bit representation of the length of the message to be processed. This representation is then appended to the end of the padded message. Tho it is very unlikely, if the length of the message is greater then $$ 2^{64} $$ then only the lower order 64-bits are used.

   At this stage we now have a message that is made up of multiple blocks of 512-bits.

   

3. ### Initialise MD buffers - section 3.3

   The MD buffers are the initial digest, they consist of 4 32-bit words that have been pre defined in the [MD5 Standard](https://tools.ietf.org/html/rfc1321):

   ​	

   |  words  | Hexidecimal | Binary                           | Decimal    |
   | :-----: | ----------- | -------------------------------- | ---------- |
   | word A: | 01 23 45 67 | 1001000110100010101100111        | 19088743   |
   | word B: | 89 ab cd ef | 10001001101010111100110111101111 | 2309737967 |
   | word C: | fe dc ba 98 | 11111110110111001011101010011000 | 4275878552 |
   | word D: | 76 54 32 10 | 1110110010101000011001000010000  | 1985229328 |

   

4. ### Process message in 16-Word blocks - section 3.4

   First we define the auxilary functions that take in 3 x 32-bit words, perform bit-wise operations on them and return 1 x 32-bit word. The funtions are as follows:

   ​		  F(X,Y,Z) = XY v not(X) Z
   ​          G(X,Y,Z) = XZ v Y not(Z)
   ​          H(X,Y,Z) = X xor Y xor Z
   ​          I(X,Y,Z)   = Y xor (X v not(Z))

   Next we have the 64 element table that is generated from the Sine where the i-th element is equal to 4294967296 times abs(sin(i)), where i is in radians. This table can be found in the appendix of the standard. For my program I populated a unsigned 32 bit integer array with the 64 values taken from the standard.

   Now you process the message in 16-word blocks by passing them through each of the 4 rounds outlined in the standard. Each round takes advantage of diffrent bit shifting operations:

   Round 1

   ​	FF(a, b, c, d, m, s, t) { a += F(b, c, d) + m + t;  a = b + ROTLEFT(a, s); }

   Round 2

   ​	GG(a, b, c, d, m, s, t) { a += G(b, c, d) + m + t;  a = b + ROTLEFT(a, s); }

   Round 3

   ​	HH(a, b, c, d, m, s, t) { a += H(b, c, d) + m + t;  a = b + ROTLEFT(a, s); }

   Round 4

   ​	II(a, b, c, d, m, s, t) { a += I(b, c, d) + m + t;  a = b + ROTLEFT(a, s); }

   

   ![MD5 Bit shifting](https://kl2217.files.wordpress.com/2011/07/md5.png)

   Figure 1 - Round one of MD5 operation. *Mi* denotes a 32-bit block of the message input, and *Ki* denotes a 32-bit constant, different for each operation. [![left shift](https://i1.wp.com/upload.wikimedia.org/wikipedia/commons/e/e1/Lll.png)](https://kl2217.wordpress.com/2011/07/21/common-hashing-algorithms/Lll.png)*s* denotes a left bit rotation by *s* places; *s* varies for each operation. [![Addition](https://i2.wp.com/upload.wikimedia.org/wikipedia/commons/7/75/Boxplus.png)](https://kl2217.wordpress.com/2011/07/21/common-hashing-algorithms/Boxplus.png) denotes addition modulo 232

   

5. ### Output Message Digest - section 3.5

   What is produced at the end is the initial words A, B, C, D after being operated on through each 512-bit block and each round per block to give us the 128-bit Message Digest as output.



## Complexity

The MD5 algorithm was initially designed to be a cryptographic hash function but was later found to have "extensive vulnerablities". That said it is still used to this day to varify document integrity. 

Cryptanalytic research published in 1996 showed a possible weakness in MD5 through a collision attack. It was not until december of 2004, Dan Kaminsky published his finding that the MD5 Algorithm had a hash collision weakness. What he found was there were more then one possible inputs to obtain the same checksum from the MD5 algorithm. Unfortunatly what this means is hackers can take advantage of this and substitute a innocent message that has been digitaly signed with a malicious one, leaving users of MD5 vulnerable to attacks. The way in which hackers would cause harm using this technique is by using forged data on software that used MD5 to then incorrectly identify themselves as trustworthy 

## References

- https://tools.ietf.org/html/rfc1321 
  - Used to gain a better understanding of the MD5 Algorithm
- https://www.tutorialspoint.com/cprogramming/index.htm 
  - Familiarise myself with c 
- https://github.com/ianmcloughlin?tab=repositories&q=&type=&language=c 
  - Ian's c repos including sha256 which was laid out step by step throughout the semester along with helpful code on hash functions and bit-wise operations
- https://www.geeksforgeeks.org/union-c/ 
  -  Better understanding of unions in c
- https://en.wikipedia.org/wiki/MD5
  - General information on MD5
- https://www.geeksforgeeks.org/command-line-arguments-in-c-cpp/ 
  - Manipulation of commarnd line arguments in c
- http://www.gnu.org/software/libc/manual/html_node/Getopt.html 
  - getopt library for handling command line arguments
- https://www.tutorialspoint.com/unix_commands/getopt.htm 
  - more command line argument information
- http://courses.cms.caltech.edu/cs11/material/general/usage.html 
  - How to correctly write usage statements
- https://stackoverflow.com/questions/9642732/parsing-command-line-arguments-in-c 
  - more command line argument information as I struggled to understand for some time
- https://discussions.apple.com/thread/8336714
  - installing gcc on Mac
- https://brew.sh
  - Link to home-brew which I used to install the GCC Compiler 
- https://www.codeblocks.org/downloads/binaries
  - Link to codeBlock binaries to install GCC compiler on a windows machine
- https://www.journaldev.com/25757/c-compiler-windows-gcc
  - Guide to install GCC on windows
- https://kl2217.wordpress.com/2011/07/21/common-hashing-algorithms/
  - Site used to obtain visual representation of a round in the algorithm
- https://www.securityfocus.com/bid/11849/info
  - Report outlining the hash collision weakness of MD5
- https://www.kb.cert.org/vuls/id/836068/
  - 
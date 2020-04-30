# MD5 Message Digest
Lecturer: **Dr Ian McLoughin**

Author: **Sean Moylan**

## About

This repo contains an assignment given to me as part of Theory of Algorithms module carried out in 4th Year Software Development at GMIT 2020.

In the assignment I was asked to write in the C Programming language a program that could compute the Message Digest 5 (MD5) hash. The file MD5.c contains my implementation of the algorithm, MD5.exe is a compiled version of the program that can be run from the terminal but if you wish to compile and run it yourself please see instructions below. 

For a full breakdown of this repo navigate to the file overview.md where I give a through breakdown of the algorithm, how to run, the complexities and all the references I used in completing this assignment.

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

Steps to compile using gcc and run the original MD5.c file:

1. Clone this repo to your device.
2. Open terminal and navigate to the dir you saved the repo to.
3. Once inside the dir type `gcc MD5.c -o MD5` this will compile an executable
4. Now you can type `./MD5 -o <filename>` where the filename is the input for the Message Digest
5. Once run you should see MD5(filename): followed by a 128 bit Message digest of the input file

## Test

To run a test on the MD5.c file:

1. Clone this repo to your device.
2. Open terminal and navigate to the dir you saved the repo to.
3. Once inside the dir type `gcc MD5.c -o MD5` this will compile an executable
4. Now you can type `./MD5 -t` 
5. The program will then generate a message digest on a predefined string `hello world` and output to the terminal




## 

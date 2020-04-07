/* 
  Author - Sean Moylan 
 
  MD5 Message Digest Algorithm 

  
  Termonology and Notation

    word    - represents a 32bit space in memory
    byte    - represents a 8bit space in memory
    x_i     - represents x sub i
    x^i     - represents x to the i-th power
    +       - Addition of words(modulo-2^32 addition)
    X <<< s - Circularly shifting X left by s bit positions

  Bitwise Operators

    not(X)  - bit-wise complement of X
    X xor Y - bit-wise XOR of X and Y
    XY      - bit-wise AND
    

*/


#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

// Initialize MD buffers that consistes of 4 32bit integers
const uint32_t WORDS[] = {0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476};


// Constants for MD5Transform routine
#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21

static unsigned char PADDING[64] = {
  0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

// Functions (F, G, H, I)
// --- F Function ---
#define F( x,  y,  z) ((x & y) | (~x & z))
// --- G Function ---
#define G( x,  y,  z) ((x & z) | (y & ~z))
// --- H Function ---
#define H( x,  y,  z) (x ^ y ^ z)
// --- I Function ---
#define I( x,  y,  z) (y ^ (x | ~z))



// bit shifting functions for rounds 1, 2, 3, 4
#define FF(a, b, c, d, m, s, t) { a += F(b, c, d) + m + t;  a = b + ROTLEFT(a, s); }
#define GG(a, b, c, d, m, s, t) { a += G(b, c, d) + m + t;  a = b + ROTLEFT(a, s); }
#define HH(a, b, c, d, m, s, t) { a += H(b, c, d) + m + t;  a = b + ROTLEFT(a, s); }
#define II(a, b, c, d, m, s, t) { a += I(b, c, d) + m + t;  a = b + ROTLEFT(a, s); }


// Union allows you to store diffrent data types in the same memory address
// this union is size 512bits that can be accessed as:
// 8 x 64 bits
// 16 x 32 bits
// 64 x 8 bits
union block {
  uint64_t six_four[8];
  uint32_t three_two[16];
  uint8_t eight[64];
};

// Used to help nextblock keep track of the status of nextblock
enum flag {READ, PAD0, FINISH};


// Reads in the next block to be processed
int nextblock(union block *M, FILE *infile, uint64_t *nobits, enum flag *status){

}


// Processes the next hash to be computed
void nexthash(union block *M){

}


int main(int argc, char *argv[ ]) {
  
  // Read in file for message digest

  if(argc != 2){
    printf("Error! Expected single file as argument. \n");
  }

  FILE *infile = fopen(argv[1], "rb");
  if(!infile){
    printf("Error! Could not open file");
  }


  // The current padded message block
  union block M;
  uint64_t nobits = 0;
  enum flag status = READ;


  // Read throughall the padded message blocks.
  while(nextblock(&M, infile, &nobits, &status)){
    // Calculate the next hash value
    nexthash(&M);
  }

  for(int i = 0; i < 8; i++){
    printf("%02" PRIx32, WORDS[i]);
  }



}

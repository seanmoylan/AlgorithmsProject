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
    not(X)  - bit-wise complement of X
    X xor Y - bit-wise XOR of X and Y
    XY      - bit-wise AND
    

*/


#include <stdio.h>
#include <stdint.h>

// Initialize MD buffers that consistes of 4 32bit integers
const uint32_t WORDS[] = {0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476};


int main(int argc, char *argv[ ]) {
  
  // Read in file for message digest

  if(argc != 2){
    printf("Error! Expected single file as argument. \n");
  }

  FILE *infile = fopen(argv[1], "rb");
  if(!infile){
    printf("Error! Could not open file");
  }


  // Functions (F, G, H, I)

  // --- F Function ---
  uint32_t F(uint32_t x, uint32_t y, uint32_t z){
    return (x & y) | (~x & z);
  }


  // --- G Function ---
  uint32_t G(uint32_t x, uint32_t y, uint32_t z){
    return (x & z) | (y & ~z);
  }


  // --- H Function ---
  uint32_t H(uint32_t x, uint32_t y, uint32_t z){
    return (x ^ y ^ z);
  }

  // --- I Function ---
  uint32_t I(uint32_t x, uint32_t y, uint32_t z){
    return (y ^ (x | ~z));
  }


}

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
    

 References:
- https://tools.ietf.org/html/rfc1321
- https://www.geeksforgeeks.org/command-line-arguments-in-c-cpp/
- http://www.gnu.org/software/libc/manual/html_node/Getopt.html
- https://www.tutorialspoint.com/unix_commands/getopt.htm
- http://courses.cms.caltech.edu/cs11/material/general/usage.html
- https://stackoverflow.com/questions/9642732/parsing-command-line-arguments-in-c

*/


#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <unistd.h>
#include <getopt.h>

// Initialize MD buffers that consistes of 4 32bit integers
const uint32_t WORDS[] = {0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476};
const char usage[] = "usage: MD5 - Message Digest Algorithm \n ./md5 <filename> | ./md5 -h \n More again \n and more \n";
const char test_string[] = "hello world";

uint32_t DIGEST[4];


// Constants for MD5Transform routine
#define S4 4
#define S5 5
#define S6 6
#define S7 7
#define S9 9
#define S10 10
#define S11 11
#define S12 12
#define S14 14
#define S15 15
#define S16 16
#define S17 17
#define S20 20
#define S21 21
#define S22 22
#define S23 23


// Rotation left shifts the bits to the left 
// any that fall off are appended to the end (Loop)
#define ROTLEFT(x, c) ((x << c) | (x >> (32 - c)))

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


// Hash constants
const uint32_t K[64] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};


/* 	
	Union allows you to store diffrent data types in the same memory address
	this union is size 512bits that can be accessed as:
	8 x 64 bits
 	16 x 32 bits
 	64 x 8 bits
*/

union block {
	uint64_t six_four[8];
	uint32_t three_two[16];
	uint8_t eight[64];
};

// Used to help nextblock keep track of the status of nextblock
enum flag {READ, PAD0, FINISH};


// Reads in the next block to be processed
// When we reach the end of the file we check
int nextblock(union block *M, FILE *infile, uint64_t *nobits, enum flag *status){

  	// Breaks while loop in the main method when nextblock is finished
	if(*status == FINISH)
		return 0;


	if (*status == PAD0){
		for(int i = 0; i < 56; i++)
			M->eight[i] = 0;

		M->six_four[7] = *nobits;
		status = FINISH;
		return 1;
	}



  	// Reads 64 x 1bits and stores them in M.eight
  	// fread takes in a pointer to a memory address, the size to be read in bytes,
  	// the number of elements of size bytes and the file to be taken as input.
	size_t nobytesread = fread(M->eight, 1, 64, infile);

	if(nobytesread == 64)
		return 1;

  	// run if all padding can be fit into the last block
	if(nobytesread < 56){
		M->eight[nobytesread] = 0x80;
		for(int i = nobytesread + 1; i < 56; i++)
			M->eight[i] = 0;
		M->six_four[7] = *nobits;
		*status = FINISH;
		return 1;

	}
}


// Processes the next hash to be computed
void nexthash(union block *M){

  	// Initial values of a, b, c, d
	uint32_t a, b, c, d;
	a = WORDS[0];
	b = WORDS[1];
	c = WORDS[2];
	d = WORDS[3];

  	// Round 1 - FF function
	FF(a, b, c, d, M -> three_two[0], S7,   K[0]);
	FF(d, a, b, c, M -> three_two[1], S12,  K[1]);
	FF(c, d, a, b, M -> three_two[2], S17,  K[2]);
	FF(b, c, d, a, M -> three_two[3], S22,  K[3]);
	FF(a, b, c, d, M -> three_two[4], S7,   K[4]);
	FF(d, a, b, c, M -> three_two[5], S12,  K[5]);
	FF(c, d, a, b, M -> three_two[6], S17,  K[6]);
	FF(b, c, d, a, M -> three_two[7], S22,  K[7]);
	FF(a, b, c, d, M -> three_two[8], S7,   K[8]);
	FF(d, a, b, c, M -> three_two[9], S12,  K[9]);
	FF(c, d, a, b, M -> three_two[10], S17, K[10]);
	FF(b, c, d, a, M -> three_two[11], S22, K[11]);
	FF(a, b, c, d, M -> three_two[12], S7,  K[12]);
	FF(d, a, b, c, M -> three_two[13], S12, K[13]);
	FF(c, d, a, b, M -> three_two[14], S17, K[14]);
	FF(b, c, d, a, M -> three_two[15], S22, K[15]);

  	// Round 2 - GG function
	GG(a, b, c, d, M -> three_two[1], S5,   K[16]);
	GG(d, a, b, c, M -> three_two[6], S9,   K[17]);
	GG(c, d, a, b, M -> three_two[11], S14, K[18]);
	GG(b, c, d, a, M -> three_two[0], S20,  K[19]);
	GG(a, b, c, d, M -> three_two[5], S5,   K[20]);
	GG(d, a, b, c, M -> three_two[10], S9,  K[21]);
	GG(c, d, a, b, M -> three_two[15], S14, K[22]);
	GG(b, c, d, a, M -> three_two[4], S20,  K[23]);
	GG(a, b, c, d, M -> three_two[9], S5,   K[24]);
	GG(d, a, b, c, M -> three_two[14], S9,  K[25]);
	GG(c, d, a, b, M -> three_two[3], S14,  K[26]);
	GG(b, c, d, a, M -> three_two[8], S20,  K[27]);
	GG(a, b, c, d, M -> three_two[13], S5,  K[28]);
	GG(d, a, b, c, M -> three_two[2], S9,   K[29]);
	GG(c, d, a, b, M -> three_two[7], S14,  K[30]);
	GG(b, c, d, a, M -> three_two[12], S20, K[31]);

  	// Round 3 - HH function
	HH(a, b, c, d, M -> three_two[5], S4,   K[32]);
	HH(d, a, b, c, M -> three_two[8], S11,  K[33]);
	HH(c, d, a, b, M -> three_two[11], S16, K[34]);
	HH(b, c, d, a, M -> three_two[14], S23, K[35]);
	HH(a, b, c, d, M -> three_two[1], S4,   K[36]);
	HH(d, a, b, c, M -> three_two[4], S11,  K[37]);
	HH(c, d, a, b, M -> three_two[7], S16,  K[38]);
	HH(b, c, d, a, M -> three_two[10], S23, K[39]);
	HH(a, b, c, d, M -> three_two[13], S4,  K[40]);
	HH(d, a, b, c, M -> three_two[0], S11,  K[41]);
	HH(c, d, a, b, M -> three_two[3], S16,  K[42]);
	HH(b, c, d, a, M -> three_two[6], S23,  K[43]);
	HH(a, b, c, d, M -> three_two[9], S4,   K[44]);
	HH(d, a, b, c, M -> three_two[12], S11, K[45]);
	HH(c, d, a, b, M -> three_two[15], S16, K[46]);
	HH(b, c, d, a, M -> three_two[2], S23,  K[47]);

  	// Round 4 - II function
	II(a, b, c, d, M -> three_two[0], S6,   K[48]);
	II(d, a, b, c, M -> three_two[7], S10,  K[49]);
	II(c, d, a, b, M -> three_two[14], S15, K[50]);
	II(b, c, d, a, M -> three_two[5], S21,  K[51]);
	II(a, b, c, d, M -> three_two[12], S6,  K[52]);
	II(d, a, b, c, M -> three_two[3], S10,  K[53]);
	II(c, d, a, b, M -> three_two[10], S15, K[54]);
	II(b, c, d, a, M -> three_two[1], S21,  K[55]);
	II(a, b, c, d, M -> three_two[8], S6,   K[56]);
	II(d, a, b, c, M -> three_two[15], S10, K[57]);
	II(c, d, a, b, M -> three_two[6], S15,  K[58]);
	II(b, c, d, a, M -> three_two[13], S21, K[59]);
	II(a, b, c, d, M -> three_two[4], S6,   K[60]);
	II(d, a, b, c, M -> three_two[11], S10, K[61]);
	II(c, d, a, b, M -> three_two[2], S15,  K[62]);
	II(b, c, d, a, M -> three_two[9], S21,  K[63]);


	DIGEST[0] += a;
	DIGEST[1] += b;
	DIGEST[2] += c;
	DIGEST[3] += d;
}

// usage message
void print_usage(){
	//printf("usage: MD5 - Message Digest Algorithm \n");
	printf("%s\n", usage);
	//exit(0);
}


int main(int argc, char *argv[]) {

	int option_index;
	char *input_string;

	FILE *infile = NULL;

	// If argc = 1 then the user has only given the program name
	// A usage message should be given to the user when they either
	// pass incorrect args or incorrect number of args

	if (argc == 1){
		print_usage();
		exit(0);
	}


	// Using getopt to manage command line arguments
	while((option_index = getopt(argc, argv, "hts:")) != -1){
		switch(option_index){
			// used for running MD5 against a pre defined string as a test
			case 't':
				// this code will run when --test is called
				printf("You have chosen t\n");
				print_usage();
				//(0);
				break;
			case 'h':
				printf("You want help\n");
				print_usage();
				//exit(0);
				break;
			case 's':
				input_string = optarg;
				printf("File given as input: %s\n", input_string);
				infile = fopen(input_string, "rb");
				//exit(0);
				break;
				//exit(0);
			default:
				print_usage();
				return 1;
		}
	}
	

	 
	if(!infile){
		printf("Error! Could not open file\n");
		return 1;
	}


  	// The current padded message block
	union block M;
	uint64_t nobits = 0;
	enum flag status = READ;


  	// Read through all the padded message blocks.
	while(nextblock(&M, infile, &nobits, &status)){
    	// Calculate the next hash value
		nexthash(&M);
	}

	// Print Message Digest
	printf("MD5(%s): ", input_string);
	for(int i = 0; i < 4; i++){
		printf("%02" PRIx32, DIGEST[i]);
	}
	printf("\n");
	

	return 0;



}

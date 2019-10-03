//see LICENSE for license
// The following is a RISC-V program to test the functionality of the
// sha3 RoCC accelerator.
// Compile with riscv-gcc sha3-rocc.c
// Run with spike --extension=sha3 pk a.out

#include <stdio.h>
#include <stdint.h>
#include "sha3.h"
#include "encoding.h"

int main() {

  unsigned long start = 0;
  unsigned long end = 0;

  do {
    printf("Start basic test 1.\n");
    // BASIC TEST 1 - 150 zero bytes

    // Setup some test data
    unsigned int ilen = 150;
    unsigned char input[150] = "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000";
    unsigned char output[SHA3_256_DIGEST_SIZE];

    start = rdcycle();

    // Compute hash in SW
    sha3ONE(input, ilen, output);

    end = rdcycle();

    // Check result
    int i = 0;
    unsigned char result[SHA3_256_DIGEST_SIZE] =
    {221,204,157,217,67,211,86,31,54,168,44,245,97,194,193,26,234,42,135,166,66,134,39,174,184,61,3,149,137,42,57,238};
    //sha3ONE(input, ilen, result);
    for(i = 0; i < SHA3_256_DIGEST_SIZE; i++){
      printf("output[%d]:%d ==? results[%d]:%d \n",i,output[i],i,result[i]);
      if(output[i] != result[i]) {
        printf("Failed: Outputs don't match!\n");
        printf("SHA execution took %lu cycles\n", end - start);
        return 1;
      }
    }

  } while(0);

  printf("Success!\n");

  printf("SHA execution took %lu cycles\n", end - start);

  return 0;
}

#include <stdio.h>
#include <stdlib.h>


// This is the Parser for DannyBasic: A compiler for TinyBasic made by Daniel Small






int main(int argc, char *argv[]) {


  // File IO
  printf("Source Code: \n");

  FILE* fp;

  // No File Mentioned
  if (argc < 2){

    printf("No File was Provided");
    exit(1);

  }

  // Open File
  fp = fopen(argv[1], "r");


  // Print the Original Source Code

  char c = getc(fp);
  while (c != EOF) {

    printf("%c", c);
    c = getc(fp);
  }

  printf("\n\n");


  // Reset file pointer and start parsing

  fp = fopen(argv[1], "r");




  return 0;
}

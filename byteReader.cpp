// --- Custom header for this file built by autoClasser --- //
// Alex Holehouse (alex.holehouse@gmail.com)
// Part of the dnacompress project
// Contact me at alex.holehouse@gmail.com for more details
// version 1.0 - December 2011


#include <iostream>
#include "byteReader.h"
#include <math.h>

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// another function would go here
char* byteReader::readByte(char byte) {
  
  char* byte_array = new char[9];
  int total = sqrt(pow(int(byte),2));
  int temp = 0;

  for (int i = 0 ; i < 8 ; i++){

    temp = pow(2,7 - i);
    if (total >= temp){
      byte_array[i] = '1';
      total = total - temp;
    }
    else
      byte_array[i] = '0';
  }

  byte_array[8] = '\0';

  return byte_array;
  
}

// END OF FILE

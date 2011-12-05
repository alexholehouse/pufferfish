// --- Custom header for this file built by autoClasser --- //
// Alex Holehouse (alex.holehouse@gmail.com)
// Part of the dnacompress project
// Contact me at alex.holehouse@gmail.com for more details
// version 1.0 - December 2011


#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "cmp_decode.h"

using std::ifstream;
using std::ofstream;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// default constructor
cmp_decode::cmp_decode() {
  //
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// another function would go here
bool cmp_decode::decode(ifstream *IN, ofstream *OUT){
  
  // variable decs
  int eoftest;
  char byte;
  char tempbyte;
  int num_bases;
  bool finished = false;
  
  // get until EOF
  while(!finished){
    
    //cout << "tellg() = " << IN.tellg() << endl;
    
    num_bases = 4;
    IN->get(byte);
    IN->get(tempbyte);
        
    eoftest = IN->peek();
    
    if (eoftest == EOF)
      finished = true;
    
    else
      IN->putback(tempbyte);
    
    if (finished){
      num_bases = tempbyte;
      // cout << "Final number of bases is " << num_bases << endl;
    }
    
    //cout << char_to_code(byte, num_bases) << endl;
    *OUT << char_to_code(byte, num_bases);
  }
  
  
  return true;
}
char* cmp_decode::char_to_code(char byte, int num_bases){
  
  char* code = new char[5];
  
  // loops four times, once for each base
  // encoding is 00(A) 01(C) 10(G) and 11(T)
  for (int i = 0 ; i < num_bases ; i++){
    
    // if first binary digit is 1
    if (byte & static_cast<char>(128)){
      byte = byte << 1;
      if (byte & static_cast<char>(128))
	code[i] = 'T';
      else
	code[i] = 'G';
    }
    
    // if first binary digit is 0
    else{
      byte = byte << 1;
      if (byte & static_cast<char>(128))
	code[i] = 'C';
      else
	code[i] = 'A';
    }
    
    byte = byte << 1;
  }
  
  code[num_bases] = '\0';
  
  return code;
}
// END OF FILE

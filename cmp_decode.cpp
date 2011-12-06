// --- Custom header for this file built by autoClasser --- //
// Alex Holehouse (alex.holehouse@gmail.com)
// Part of the pufferfish project
// Contact me at alex.holehouse@gmail.com for more details
// version 1.0 - December 2011

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "cmp_decode.h"

using std::ifstream;
using std::ofstream;
using std::endl;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// default constructor
// 
// Set decoding parameters
cmp_decode::cmp_decode(bool _format, bool _numbering) {
  numbering = _numbering;
  format = _format;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// decode
//
// Takes two (open) filestreams and decodes the compressed instream  and
// dumps it into the outstream
bool cmp_decode::decode(ifstream *IN, ofstream *OUT){
  
  // variable decs
  int eoftest;
  char byte;
  char tempbyte;
  int num_bases;
  int counter = 0;
  int basecounter = 1;
  bool finished = false;
  
  // set initial "1" if numbering is being used
  if (numbering)
    *OUT << basecounter << "     ";
  
  // loop until EOF 
  while(!finished){
    
    // set counters
    basecounter +=4;
    counter++;
    num_bases = 4;
    
    // get the byte and the following byte
    IN->get(byte);
    IN->get(tempbyte);
    
    // peak at the byte after that
    eoftest = IN->peek();
    
    // if this byte is the EOF then tempbyte has been encoded to show how many bases
    // were stored in what is currently in byte. i.e. the end of the file is
    // [AGCT]-[AGXX]-[2]-[EOF] (where each [block] is a byte
    
    if (eoftest == EOF){
      finished = true;
      num_bases = tempbyte;
    }
    
    else
      IN->putback(tempbyte);
    
    // write to disk 
    *OUT << char_to_code(byte, num_bases);

    // formatting 
    if (format && counter !=8)
      *OUT << " ";
    
    if (format && counter == 8){
      *OUT << endl;
      
      // note, numbering breaks down after 99999 bases, although seems unlikely you'd
      // be looking at a file by hand which is over 100 0000 bases?
      if (numbering){
	
	if (basecounter < 100)
	  *OUT << basecounter << "    ";

	else if (basecounter < 1000)
	  *OUT << basecounter << "   ";

	else if (basecounter < 10000)
	  *OUT << basecounter << "  ";

	else if (basecounter < 100000)
	  *OUT << basecounter << " ";
      }
      
      // reset counter (NB basecounter continues counting)
      counter = 0;
    }
  }
  return true;
}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// char_to_code
//
// takes a byte (from the compressed input stream) and converts it into a cstring of 
// four characters, returning the string (unless it's the penultimate byte, in which 
// case it retunrs the number of bases in the preceding byte. 
//
char* cmp_decode::char_to_code(char byte, int num_bases){
  
  char* code = new char[5];
  
  // loops four times, once for each base
  // encoding is 00(A) 01(C) 10(G) and 11(T)
  // NB use bitwise operations (& and <)
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

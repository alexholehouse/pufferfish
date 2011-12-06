// --- Custom header for this file built by autoClasser --- //
// Alex Holehouse (alex.holehouse@gmail.com)
// Part of the dnacompress project
// Contact me at alex.holehouse@gmail.com for more details
// version 1.0 - December 2011


#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "cmp_encode.h"
#include "byteReader.h"

using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// default constructor
cmp_encode::cmp_encode(int mem) {
  DEDICATED_MEMORY = mem;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// another function would go here
bool cmp_encode::encode(ifstream *input_file, ofstream *output_file){
  
  // character declarations
  char base; // will be used to grab bases from a FASAT file
  char byte; // the byte we encode four bases into
  char mem_array[DEDICATED_MEMORY]; // an in memory array of the encoded bytes
  bool exit = false; // exit flag when we get to the end of the file
  int counter = 0; // counter through FASTA file - is never reset
  int byte_counter; // counter through the byte, is reset on each byte back to 0;
  int offset = 0; // A
  
  
  // Set A,C,G and T as 2 bit encoding 
  // 0000 0000 = A = 0
  // 0000 0001 = C = 1
  // 0000 0010 = G = 2
  // 0000 0011 = T = 3

  char refbase[4];
  refbase[0] = static_cast<char>(0);
  refbase[1] = static_cast<char>(1);
  refbase[2] = static_cast<char>(2);
  refbase[3] = static_cast<char>(3);
  
  
  // Until we reach EOF (tested by switch statement)
  while(true){
    
    // We loop until DEDICATED_MEMORY-1 because we always add a final
    // byte showing the progress through the penultimate byte. Although
    // unlikely, we could segfault if by chance we had DEDICATED_MEMORY 
    // nucleotides and we looped only to DEDICATED_MEMORY. This is why
    // we loop to DEDICATED_MEMORY - 1 instead.
    
    // multiply by <loops> so we can restart where we left off if the file
    // contains more nucleotides than DEDICATED_MEMORY and we have to dump
    // to disk.
    
    for (counter = 0 ; counter < (DEDICATED_MEMORY - 1) ; counter++){
      
      // reset byte to 0000 0000
      byte = static_cast<char>(0);
      
      // loops four times (four bases per byte)
      for (byte_counter = 0 ; byte_counter < 4 ; byte_counter++){
	
	if (exit)
	  break;
	
	// get the next character in the file
	input_file->get(base);
		
	// switch on that character
	switch(base){
	  
	case 'a':
	case 'A': {
	  byte = (byte | (refbase[0] << ((3 - byte_counter) *2) ));
	  break;
	}
	  
	case 'c':
	case 'C': {
	  byte = (byte | (refbase[1] << ((3 - byte_counter) *2) ));
	  break;
	}
	    
	case 'g':
	case 'G': {
	  byte = (byte | (refbase[2] << ((3 - byte_counter) *2) ));
	  break;
	}
	  
	case 't':
	case 'T': {
	  byte = (byte | (refbase[3] << ((3 - byte_counter) *2) ));
	  break;
	}
	  
	// this makes out input pretty tolerant
	default: {
	  // if we hit the end of the file set exit status to true
	  if (input_file->eof())
	    exit = true;
	  // else ignore this character so decrement the byte counter
	  byte_counter--; }
	}
      }
      
      // DEBUG-WRITE
      //cout << "Writing byte content (" << byteReader::readByte(byte) 
      //     << ") to mem_array pos " << counter << endl;
      
      // writing a byte to the in memory array
      // cout << "Writing byte to memarray " << static_cast<int>(byte) << endl;
      mem_array[counter] = byte;
      
      // if exit flag is raised
      if (exit){
	// shows how far through the final byte we were - this is important, unlikely 
	// we'll have a (n mod 4 = 0) number of nucleotides!
	mem_array[counter + 1] = byte_counter;
	offset = 2;
	break;
      }
    }
    
    // write the current in memory array to disk...
    if (!write_array_to_disk(mem_array, counter+offset, output_file)){
      cout << "Error: Unable to write to file" << endl;
      return false;
    }
    
    if (exit){
      input_file->close();
      return true;
    }
  }
  
  return false;
}


// END OF FILE
bool cmp_encode::write_array_to_disk(char* mem_array, int size, ofstream *output_file){
  
  //cout << "-------- DEBUG(write_array_to_disk)---------------" << endl; 
  //cout << "size is = " << size << endl;
  
  ofstream LOG;
  ofstream OUT;

  // always append - means each read adds to the end of the previously written block
  LOG.open("log.txt", std::ios::app);
  
  if (output_file->fail())
    return false;

  for (int i = 0 ; i < size; i++){
    output_file->put(mem_array[i]);

    LOG.put(static_cast<int>(mem_array[i]));
  }

  LOG.close();
  return true;
}

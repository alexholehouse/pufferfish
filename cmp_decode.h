// --- Custom header for this file built by autoClasser --- //
// Alex Holehouse (alex.holehouse@gmail.com)
// Part of the pufferfish project
// Contact me at alex.holehouse@gmail.com for more details
// version 1.0 - December 2011

#ifndef CMP_DECODE_H
#define CMP_DECODE_H

/*! \brief Class which decodes files encoded using encode

  
 */ 

//------------------------------------
class cmp_decode  {

public:
  
  // constructor
  cmp_decode(bool format, bool number);

  // main funcion, takes an input stream and converts it to a decoded output stream
  bool decode(std::ifstream *inputstream, std::ofstream *outputstream);

private:

  //converts an encoded byte into a cstring of four bases in ASCII
  char* char_to_code(char byte, int num_bases); 
  
  // class variables
  bool format; // set to true in the constructor if the output should be formatted
  bool numbering; // set to true if the base numbering should be added
  
};

#endif

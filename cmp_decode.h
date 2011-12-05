// --- Custom header for this file built by autoClasser --- //
// Alex Holehouse (alex.holehouse@gmail.com)
// Part of the dnacompress project
// Contact me at alex.holehouse@gmail.com for more details
// version 1.0 - December 2011


#ifndef CMP_DECODE_H
#define CMP_DECODE_H

// include any relevant header files here...

/*! \brief Class which decodes files encoded using encode
  
 */ 

//------------------------------------
class cmp_decode  {

public:
  cmp_decode();
  bool decode(std::ifstream *inputstream, std::ofstream *outputstream);

private:
  char* char_to_code(char byte, int num_bases);

    
// Private class methods and class variables go here

};

#endif

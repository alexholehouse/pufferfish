// --- Custom header for this file built by autoClasser --- //
// Alex Holehouse (alex.holehouse@gmail.com)
// Part of the dnacompress project
// Contact me at alex.holehouse@gmail.com for more details
// version 1.0 - December 2011


#ifndef CMP_ENCODE_H
#define CMP_ENCODE_H

/*! \brief Class for encoding FASTA forma into compressed storage

<Longer class description>
*/ 

//------------------------------------
class cmp_encode {
  
 public:
  
  cmp_encode(int mem);
  bool encode(std::ifstream *inputstream, std::ofstream *outputstream);
  // Public class methods go here

 private:
  // Private class methods and class variables go here
  bool write_array_to_disk(char* mem_array, int size, std::ofstream *output_file);
  int DEDICATED_MEMORY;
};

#endif

// --- Custom header for this file built by autoClasser --- //
// Alex Holehouse (alex.holehouse@gmail.com)
// Part of the pufferfish project
// Contact me at alex.holehouse@gmail.com for more details
// version 1.0 - December 2011


#ifndef CMP_ENCODE_H
#define CMP_ENCODE_H

/*! \brief Class for encoding raw text DNA sequences into a compressed file format
  
 */ 

//------------------------------------
class cmp_encode {
  
 public:
  
  // constructor - mem defines the size of dedicated memory
  cmp_encode(int mem);

  // main function for class, takes a raw open inputstream and writes the 
  // compressed file to the outputfile. Note that in terms of file rationalization
  // it will ONLY read A,a,C,c,T,t, G, or G - any other characters or spaces are 
  // ignored, meaning files with weird formatting can be used. The only requirement is
  // that the bases are in file-sequential order
  bool encode(std::ifstream *inputstream, std::ofstream *outputstream);
  
 private:

  // takes an array of size size and writes it to the stream passed by output_file
  bool write_array_to_disk(char* mem_array, int size, std::ofstream *output_file);

  // defines the size of mem_array
  int DEDICATED_MEMORY;
};

#endif

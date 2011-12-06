// --- Custom header for this file built by autoClasser --- //
// Alex Holehouse (alex.holehouse@gmail.com)
// Part of the pufferfish project
// Contact me at alex.holehouse@gmail.com for more details
// version 1.0 - December 2011


#ifndef CMP_FILEHANDLER_H
#define CMP_FILEHANDLER_H

#include <vector>

/*! \brief File handler class - deals with input files

 */ 

// using declarations
using std::vector;
using std::string;

class cmp_filehandler {

 public:
  
  // constructor
  cmp_filehandler();
  
  // check input arguments and return associated flags and values
  int check_args (int argc, char *argv[], vector<string> &io, bool &formatting, int &memory_usage, bool &numbering);
  
  // load a filename and return an open, functioning input filestream
  std::ifstream* load_input_file(std::string filename, int &filesize);

  // load a filename and return an open, functioning output filestream
  std::ofstream* load_output_file(std::string filename);
  
  // get the size of a file (in bytes)
  int get_file_size(string filename);

  // get the number of bases in a (compressed) file
  int get_number_bases(string filename);
  
 private:
  
  // initializer 
  bool init();
  
  // sets all the values in array up to array[size] to zero
  void zeros(int *array, int size);
  
  // prints usage information
  void usage();
  
  // prints help information
  void help();
  
  // number of expected flags (v. important this is correct)
  static const int number_of_flags = 8;
  static vector<string> expected_args;
    
};

#endif

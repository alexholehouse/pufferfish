// --- Custom header for this file built by autoClasser --- //
// Alex Holehouse (alex.holehouse@gmail.com)
// Part of the dnacompress project
// Contact me at alex.holehouse@gmail.com for more details
// version 1.0 - December 2011


#ifndef CMP_FILEHANDLER_H
#define CMP_FILEHANDLER_H

#include <vector>

// include any relevant header files here...

/*! \brief File handler class - deals with input files

 */ 

using std::vector;
using std::string;
//------------------------------------

class cmp_filehandler {

 public:
  cmp_filehandler();
  
  // check input arguments
  int check_args (int argc, char *argv[], vector<string> &io, bool &formatting, int &memory_usage, bool &numbering);
  
  // load a filename and return an open, functioning input filestream
  std::ifstream* load_input_file(std::string filename, int &filesize);

  // load a filename and return an open, functioning output filestream
  std::ofstream* load_output_file(std::string filename);
  
  int get_file_size(string filename);
  int get_number_bases(string filename);
 private:
  
  static const int number_of_flags = 8;
  static vector<string> expected_args;
  //  vector<string> expected_args;

  //
  
  
  bool init();
  void zeros(int *argc, int size);
  void usage();
  void help();
  
  
};

#endif

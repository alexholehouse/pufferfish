// --- Custom header for this file built by autoClasser --- //
// Alex Holehouse (alex.holehouse@gmail.com)
// Part of the pufferfish project
// Contact me at alex.holehouse@gmail.com for more details
// version 1.0 - December 2011


#ifndef CMP_UI_H
#define CMP_UI_H


/*! \brief Interface class that writes to cout


*/ 

class cmp_ui {

 public:
  cmp_ui();
  
  // decompression summary written to cout
  void decompression_summary(std::string input_file, 
			     std::string output_file, 
			     int input_size,
			     int output_size,
			     int number_bases);
  
  // compression summary written to cout
  void compression_summary(std::string input_file, 
			   std::string output_file, 
			   int input_size,
			   int output_size,
			   int number_bases);
  

  // error calls
  std::string ER_compression();
  std::string ER_decompression();
  std::string ER_arguments();

  
 private:


  
};

#endif

// --- Custom header for this file built by autoClasser --- //
// Alex Holehouse (alex.holehouse@gmail.com)
// Part of the pufferfish project
// Contact me at alex.holehouse@gmail.com for more details
// version 1.0 - December 2011


#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "cmp_ui.h"

using std::string;
using std::cout;
using std::endl;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// default constructor
cmp_ui::cmp_ui() {
  // no functionality yet...
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// output summary of decompression
//

void cmp_ui::decompression_summary(string input_file, 
				   string output_file, 
				   int input_size,
				   int output_size,
				   int number_bases){
  
  cout << "o---------------------------------------" << endl;
  cout << "|  DECOMPRESSION COMPLETE" << endl;
  cout << "|  Compressed:        " << input_file  << endl;
  cout << "|  Compressed Size:   " << input_size << " bytes" << endl;
  cout << "|  Decompressed:      " << output_file << endl;
  cout << "|  Decompressed Size: " << output_size << " bytes" << endl;
  cout << "|  Number of bases:   " << number_bases << endl;
  cout << "o---------------------------------------" << endl;

  return;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// output summary of decompression
//

void cmp_ui::compression_summary(string input_file, 
				 string output_file, 
				 int input_size,
				 int output_size,
				 int number_bases){
  
  cout << "o---------------------------------------" << endl;
  cout << "|  COMPRESSION COMPLETE" << endl;
  cout << "|  Original:          " << input_file  << endl;
  cout << "|  Original Size  :   " << input_size << " bytes" << endl;
  cout << "|  Compressed:        " << output_file << endl;
  cout << "|  Compressed Size:   " << output_size << " bytes" << endl;
  cout << "|  Number of bases:   " << number_bases << endl;
  cout << "o---------------------------------------" << endl;

  return;
}


string cmp_ui::ER_compression(){
  return ("Error: Something has gone worng during compression\nExiting...\n");
}

string cmp_ui::ER_decompression(){
  return ("Error: Something has gone worng during decompression\nExiting...\n");
}

string cmp_ui::ER_arguments(){
  return("Error: Something has gone wrong with the input arguments\nExiting...\n");
}

// END OF FILE

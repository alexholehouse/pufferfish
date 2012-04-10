// --- Custom header for this file built by autoClasser --- //
// Alex Holehouse (alex.holehouse@gmail.com)
// Part of the pufferfish project
// Contact me at alex.holehouse@gmail.com for more details
// version 1.0 - December 2011


#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <sys/stat.h>
#include "cmp_filehandler.h"

// using declarations
using std::string;
using std::cout;
using std::cerr;
using std::cerr;
using std::endl;
using std::ifstream;
using std::ofstream;

// static variable declaration
std::vector<string> cmp_filehandler::expected_args(number_of_flags);


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// initializer function for the expected_args vector

bool cmp_filehandler::init(){
  
  expected_args[0] = "-i"; // input file
  expected_args[1] = "-o"; // output file
  expected_args[2] = "-c"; // compress
  expected_args[3] = "-d"; // decompres
  expected_args[4] = "-h"; // help
  expected_args[5] = "-f"; // formatted output
  expected_args[6] = "-m"; // set dedicated memory
  expected_args[7] = "-n"; // output numbering

  return true;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// constructor

cmp_filehandler::cmp_filehandler() {
  
  // initialize that bad boy!
  init();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// function to load a file based purly on the filename (stream

ifstream* cmp_filehandler::load_input_file(string input_filename, int &filesize){
  
  cout << "Attempting to open file: " << input_filename << endl; 
  
  ifstream* input_file_p = new ifstream; // input filestream opened using new_filename
  
  input_file_p->open(input_filename.c_str());

  // check file opened ok
  if (!input_file_p->good()){
    cerr << "Error: Problem reading file "<< input_filename << endl;
    cerr << "Exiting..." << endl;
    exit(1);
  }

  filesize = get_file_size(input_filename);

  return input_file_p;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// function to load the output file as a stream

ofstream* cmp_filehandler::load_output_file(string output_filename){
  
  ofstream* output_file_p = new ofstream; // input filestream opened using new_filename

  // check if a file of the input name exists - if it does delete it
  ifstream teststream(output_filename.c_str());
  
  if (teststream.good()){
    string message = "rm ";
    message.append(output_filename);
    system(message.c_str());
  }
  
  // open the file (C++ creates it at this point automatically)
  output_file_p->open(output_filename.c_str(), std::ios::app);

  return output_file_p;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// function to check the programs input arguments and determine the input and output 
// filenames
//
// usage should be ./dnacompressor -i input -o output [-c] | [-d] (-c for compress
// -d for decompress) 

int cmp_filehandler::check_args (int argc, char *argv[], vector<string> &io, 
				 bool &format_out,
				 int &memory_usage,
				 bool &numbering){

  // ret_val should be overwritten - 0 is the "error" status
  int ret_val = 0;

    // write actual arguments into vector
  vector<string> args;
  for (int i = 0 ; i < argc; i++)
    args.push_back(argv[i]);
  
  // bitmap for the arguments passed (initialized)
  int* arg_bitmap = new int[number_of_flags];
  zeros(arg_bitmap, number_of_flags);
  
  // construct bitmap
  for (int i = 0 ; i < argc ; i++){
    for (int j = 0 ; j < number_of_flags ; j++){
      if (args[i] == expected_args[j]){
	arg_bitmap[j] = 1;
      }
      
      // get the input filename
      if (expected_args[0] == args[i])
	io[0] = args[i+1];

      // get the output filename
      if (expected_args[1] == args[i])
	io[1] = args[i+1];
      
      // get the memory usage value 
      if (expected_args[6] == args[i]){
	memory_usage = atoi(args[i+1].c_str());
	
	// 5 byte array is bottom limit
	if (memory_usage < 5)
	  memory_usage = 5;

	// 2 GB array is top limit [not tested this high
	// might break everything...]
	if (memory_usage > 2000000000)
	  memory_usage = 2000000000;
	
      }
    }
  }
  
  // if true lacking either input our output
  if (arg_bitmap[0] == 0 || arg_bitmap[1] == 0){
    usage();
    exit(1);
  }

  // XOR for -d/-c 
  if (arg_bitmap[2] == 1 && arg_bitmap[3] == 1){
    usage();
    exit(1);
  }
  
  if (arg_bitmap[2] == 0 && arg_bitmap[3] == 0){
    usage();
    exit(1);
  }
  
  // if the help flag is raised at all (ignore everything else)
  if (arg_bitmap[4] == 1){
    help();
    exit(0);
  }
  
  // compress mode
  if (arg_bitmap[2] == 1){
    io[1] = io[1].append(".pfsh");
    ret_val = 1;
  }

  // decompress mode
  if (arg_bitmap[3] == 1)
    ret_val = 2;

  // -----------------------------------------------------------
  // get additional options based on the bitmap flags 
  if (arg_bitmap[5] == 1)
    format_out = true;
  
  // for numbering to be true formatting must also be true
  
  if (arg_bitmap[7] == 1){
    
    // if more than 99999 bases then numbering
    // breaks down, so ignore it
    if(99999 >= get_number_bases(io[0])){
      numbering = true;
      format_out = true; 
    }
  }  
  
  return ret_val;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// function which sets the content of an integer array of size length to 0

void cmp_filehandler::zeros(int *argc, int size){
  for (int i = 0 ; i < size ; i++)
    argc[i] = 0;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// prints pufferfish usage

void cmp_filehandler::usage(){
  cerr << "ERROR: Unsuported input:" << endl
       << "****** USAGE IS AS FOLLOWS ******" << endl << endl
       << "./pufferfish -i INPUT -o OUTPUT [-c] | [-d] [OPTIONS]" << endl << endl
       << "___________________________________________________" << endl
       << "                      options                      " << endl
       << "-h                  Print help associated with pufferfish" << endl << endl
       << "-f                  Adds formatting to output (-d mode only)" << endl << endl
       << "-n                  Adds numbering and formatting to output" << endl 
       << "                    (-d mode only)" << endl << endl
       << "-m                  Define dedicated memory (-c mode only)" << endl << endl;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// prints pufferfish help

void cmp_filehandler::help(){
  cout << "pufferfish is a superlightweight tool for compressing/decompressing\nDNA into a highly portable format" << endl
       << "Usage is:" << endl
       << "./pufferfish -i INPUT -o OUTPUT [-c] | [-d] [OPTIONS]" << endl
       << "___________________________________________________" << endl
       << "                      options                      " << endl
       << "-h                  Print help associated with pufferfish" << endl << endl
       << "-f                  Adds formatting to output (-d mode only)" << endl << endl
       << "-n                  Adds numbering and formatting to output" << endl 
       << "                    (-d mode only)" << endl << endl
       << "-m                  Define dedicated memory (-c mode only)" << endl << endl << endl
       << "Please address bug reports to alex@holehouse.org" << endl;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// function to return the size of the file parsed in. Returns -1 if fails else size is 
// returned. Requires #include <sys/stat.h>

int cmp_filehandler::get_file_size(string filename){
  
  struct stat results;
  int size;
  
  if (stat(filename.c_str(), &results) == 0)
    size = results.st_size;
  else
    size = -1;
  
  return size;
}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// function to return the number of bases for a compressed file
//
// returns -1 if fails else size is returned

int cmp_filehandler::get_number_bases(string filename){
  return (4*(get_file_size(filename)-2));
}


// END OF FILE

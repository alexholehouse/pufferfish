// --- Custom header for this file built by autoClasser --- //
// Alex Holehouse (alex.holehouse@gmail.com)
// Part of the dnacompress project
// Contact me at alex.holehouse@gmail.com for more details
// version 1.0 - December 2011


#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>

#include "cmp_filehandler.h"

using namespace std;


 
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// default constructor
cmp_filehandler::cmp_filehandler() {
  
  // initialize the flags we want the filehander to be able to deal with
  expected_args.push_back("-i"); // input file
  expected_args.push_back("-o"); // output file
  expected_args.push_back("-c"); // compress
  expected_args.push_back("-d"); // decompres
  expected_args.push_back("-h"); // help

  if (int(expected_args.size()) != number_of_flags){
    cerr << "Added flag variables without updating the number_of_flag constants. Quitting - please correct!" << endl;
    exit(1);
  }
  
    
}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// function to load a file based purly on the filename (stream
ifstream* cmp_filehandler::load_input_file(string input_filename){
  
  cout << "Attempting to open file: " << input_filename << endl; 
  
  ifstream* input_file_p = new ifstream; // input filestream opened using new_filename
  
  input_file_p->open(input_filename.c_str());

  // check file opened ok
  if (!input_file_p->good()){
    cerr << "Error: Problem reading file "<< input_filename << endl;
    cerr << "Exiting..." << endl;
    exit(1);
  }

  return input_file_p;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
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
  output_file_p->open(output_filename.c_str(), ios::app);

  return output_file_p;
}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// function to check the programs input arguments and determine the input and output 
// filenames

// usage should be ./dnacompressor -i input -o output [-c] | [-d] (-c for compress
// -d for decompress) 
int cmp_filehandler::check_args (int argc, char *argv[], vector<string> &io){

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
      
      if (expected_args[0] == args[i])
	io[0] = args[i+1];

      if (expected_args[1] == args[i])
	io[1] = args[i+1];

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
  if (arg_bitmap[2] == 1)
    return 1;

  // decompress mode
  if (arg_bitmap[3] == 1)
    return 2;
  
  // somethings gone wrong mode
  return 0;
}

void cmp_filehandler::zeros(int *argc, int size){
  for (int i = 0 ; i < size ; i++)
    argc[i] = 0;
}

void cmp_filehandler::usage(){
  cerr << "Error in usage - should be;" << endl
       << "dnacom -i INPUT -o OUTPUT [-c] || [-d]" << endl
       << "Exiting..." << endl;
}

void cmp_filehandler::help(){
  cerr << "dnacompress is a superlightweight tool for compressing/decompressing DNA into a highly portable format" << endl
       << "Usage is:" << endl
       << "dnacom -i INPUT -o OUTPUT [-c] || [-d]" << endl
       << "Exiting..." << endl << endl
       << "Please address bug reports to alex@holehouse.org" << endl;
}


// END OF FILE

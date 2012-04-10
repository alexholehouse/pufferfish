// Alex Holehouse (alex.holehouse@gmail.com)
// Part of the pufferfish project
// Contact me at alex.holehouse@gmail.com for more details
// version 1.0 - December 2011


#include <iostream>
#include <fstream>
#include <cstdlib>
#include "cmp_filehandler.h"
#include "cmp_encode.h"
#include "cmp_decode.h"
#include "cmp_ui.h"

// using declarations
using std::endl;
using std::ifstream;
using std::ofstream;
using std::cout;
using std::cerr;





int main (int argc, char *argv[]){

  // varz
  int input_status;
  int filesize = -1;
  cmp_filehandler handler;
  cmp_ui interface;
  ifstream* input_file_p;
  ofstream* output_file_p;
  vector<string> io_filenames (2);

  // argument flags (default values set here)
  bool formatting = false;
  bool numbering = false;
  int memory_usage = 1000;

  // checks we have the flags we're expecting (-i, -o and -c or -d) 
  // and returns the io filenames in the io_filename vector [0] is 
  // input, [1] is output
  input_status = handler.check_args(argc, argv, io_filenames, formatting, memory_usage, numbering);
  
  
				
  // load the input and output files
  input_file_p = handler.load_input_file(io_filenames[0], filesize);
  output_file_p = handler.load_output_file(io_filenames[1]);
  
  // compress 
  if (input_status == 1){
    cmp_encode encoder(memory_usage);
    if(encoder.encode(input_file_p, output_file_p)){

      // must close to get filedata
      input_file_p->close();
      output_file_p->close();
      
      // write summary
      interface.compression_summary(io_filenames[0], 
				    io_filenames[1], 
				    handler.get_file_size(io_filenames[0]),
				    handler.get_file_size(io_filenames[1]),
				    handler.get_number_bases(io_filenames[1]));
    }
    
    else {
      cerr << interface.ER_compression();
      exit(1);
    }
  }
  
  // decompress
  else if (input_status == 2){
    
    cmp_decode decoder(formatting, numbering);
    if(decoder.decode(input_file_p, output_file_p)){

      // must close to get filedata
      input_file_p->close();
      output_file_p->close();
      
      // print summary to output
      interface.decompression_summary(io_filenames[0], 
				      io_filenames[1], 
				      handler.get_file_size(io_filenames[0]),
				      handler.get_file_size(io_filenames[1]),
				      handler.get_number_bases(io_filenames[0]));
    }
    
    else {
      cerr << interface.ER_decompression();
      exit(1);
    }
  
  }
  
  
  // if it's all gone wrong
  else {
    cerr << interface.ER_arguments();
    
    // always close your streams
    input_file_p->close();
    output_file_p->close();
    
    exit(1);
  }
  
  return 0;
}



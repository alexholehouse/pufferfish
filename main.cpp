#include <iostream>
#include <fstream>
#include <cstdlib>
#include "cmp_filehandler.h"
#include "cmp_encode.h"
#include "cmp_decode.h"

using namespace std;
int main (int argc, char *argv[]){

  // varz
  int input_status;
  cmp_filehandler handler;
  ifstream* input_file_p;
  ofstream* output_file_p;
  vector<string> io_filenames (2);

  // checks we have the flags we're expecting (-i, -o and -c or -d) 
  // and returns the io filenames in the io_filename vector [0] is 
  // input, [1] is output
  input_status = handler.check_args(argc, argv, io_filenames);
  
  // load the input and output files
  input_file_p = handler.load_input_file(io_filenames[0]);
  output_file_p = handler.load_output_file(io_filenames[1]);
  
  // compress 
  if (input_status == 1){
    cmp_encode encoder;
    if(encoder.encode(input_file_p, output_file_p)){
      
      cout << "o---------------------------------------" << endl;
      cout << "|  COMPRESSION COMPLETE" << endl;
      cout << "|  Original: " << io_filenames[0] << endl;
      cout << "|  Compressed: " << io_filenames[1] << endl;
      cout << "o---------------------------------------" << endl;
    }
    
    else {
      cerr << "Error: Something has gone wrong during compression. " << endl << "Exiting.." << endl;
      exit(1);
    }
  }
  
  // decompress
  else if (input_status == 2){
    
    cmp_decode decoder;
    decoder.decode(input_file_p, output_file_p);

    cout << "o---------------------------------------" << endl;
    cout << "|  DECOMPRESSION COMPLETE" << endl;
    cout << "|  Compressed: " << io_filenames[0] << endl;
    cout << "|  Decompressed: " << io_filenames[1] << endl;
    cout << "o---------------------------------------" << endl;
  
  }

  else {
    cerr << "Error: Something has gone wrong with the input arguments. " << endl << "Exiting.." << endl;  

    input_file_p->close();
    output_file_p->close();
    
    exit(1);
  }
  
  input_file_p->close();
  output_file_p->close();
  return 0;
}


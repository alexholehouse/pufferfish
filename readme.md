# Pufferfish (v1.0)

Pufferfish (the software formerly known as dnacompressor for a while) is an easy to use, lightweight and powerful tool for DNA compression and decompression.

NOTE
At present we're still in alpha (December 2010) so certain features remain in the source for testing and diagnostics. Notably, byteReader.* are used for translating bytes into binary, which was used for diagnostics, but will not be required for the final system.


## Basic overview

DNA files in FASTA are a lot bigger than they need to be for storage or transmission. To help deal with this, pufferfish takes as input a text file containing the FASTA format, and very quickly outputs a compressed version of that data.
You can then re-expand that data to its original size using the same tool. The focus here was to provide a tiny program (compiled binary is 183Kb) with big power and functionality.
At the moment usage is limited to

    ./pufferfish -i <input file> -o <output file> [-c] | [-d]
    
Which is to say you take an input file (which must exist) and an output file (which can exits, if it does it will be overwritten) and use either `-c` flag to indicate compress or `-d` flag to indicate decompress.

## Usage

    ./pufferfish -i <input file> -o <output file> [OPTIONS]
    
where `[OPTIONS]` must be one of compress or decomress (`-c` or `-d` and then any number of the others. See below for detailed explanation;

#### compress
    -c
Compresses the input file and generates the output file

#### decompress
    -d
Decompresses a file stored in pufferfish format back to FASTA format

#### help
    -h 
Prints out help and usage instrictions for pufferfish

## Installation
At the moment the software is only on for linux, although it's pure C++ so porting into a windows command line tool should be fairly straightforward (minial OS interaction through POSIX compliant means).

1. Compile using make

    make
    
2. Done. To make it a system-wide executable you'll need to copy the binary to your /usr/bin directory or add the binary's directory to the `<$PATH>` variable. 

## Functionality
Pretty limited at present, beyond compression and decompression, but things currently being added include;

* Define free memory usage from command line
* Output formatting options
* Installation scripts to offer system wide installation
* Search NCBI BLAST using a compressed file (i.e. decompress in background and run a search using the web API - this might be a bit over the top)
* Improved performance through a number of avenues;
    * Parallelization (and associated customization)
    * Algorithmic optimization
    * Advanced compression structuring
* Direct transmission link (i.e. no centralized server but direct P2P transmission)
* Hilarious logo (less of a priority)

## Contact
Contact me at alex@holehouse.org
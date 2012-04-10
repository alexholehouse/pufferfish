# Pufferfish (v1.0 - alpha)

Pufferfish (the software formerly known as dnacompressor) is an easy to use, lightweight and powerful tool for DNA compression and decompression,, currently only available for Linux.

NOTE
At present we're still in alpha (December 2011) so certain features remain in the source for testing and diagnostics. Notably, byteReader is used for translating bytes into a cstring which looks like binary, which was used for diagnostics, but will not be required for the final system.


## Basic overview

DNA files in FASTA (i.e. raw text) are a lot bigger than they need to be for storage or transmission - where a byte represents each character (A,T,C or G). To help deal with this, pufferfish takes as input a text file containing the FASTA format, and very quickly outputs a compressed version of that data.
You can then re-expand that data to its original size using the same tool. The focus here was to provide a tiny program (compiled binary is 183Kb) with big power and functionality.
At the moment usage is limited to

    $>./pufferfish -i <input file> -o <output file> [-c] | [-d]
    
Which is to say you take an input file (which must exist) and an output file (which can exits, if it does it will be overwritten) and use either `-c` flag to indicate compress or `-d` flag to indicate decompress.

## Usage

Note that while the order of flags is irrelevant, at the moment you can't combine flags (i.e. `-fn` doesn't work, you'd need to do `-f -n`).

    $>./pufferfish -i <input file> -o <output file> [OPTIONS]
    
where `[OPTIONS]` must be one of compress or decomress (`-c` or `-d` and then any number of the others. See below for detailed explanation;

##### compress
    -c
Compresses the input file and generates the output file

##### decompress
    -d
Decompresses a file stored in pufferfish format back to FASTA format

##### help
    -h 
Prints out help and usage instructions for pufferfish. Note that help overrides everything and forces the help output and nothing else.

##### memory
    -m
Sets the amount of dedicated memory used for the compression process (note that at present dedicated memory for decompression isn't controllable - this may be something we add later).
Note that at present the lower limit is capped at 5 bytes and the upper limit at 2 GBs (which is probably not recommended). Default is 1 MB which should be plenty!

##### formatting
    -f
For decompression only, formats the output into eight blocks of four bases per line

##### numbering
    -n
For decompression only, adds base numbers to the start of each line. NB If number of bases is greater than 99999 then the formatting becomes distorted so if this is the case numbering is forced off.



## Installation
At the moment the software is only on for linux, although it's pure C++ so porting into a windows command line tool should be fairly straightforward (minimal OS interaction through POSIX compliant methods).

To install, simply run the insall script (executable). You'll be prompted for your root password at some point to add the binary to a PATH directory.

     `$> ./install`
    
## Uninstallation
To remove, like installing, just run the uninstall binary. Again, you'll be prompted for your root password.

     `$> ./uninstall`


## Functionality
Pretty limited at present, beyond compression and decompression, but things currently being added include;

* Define free memory usage from command line **[DONE]**
* Output formatting options **[DONE]** (mostly)
* Installation scripts to offer system wide installation **[DONE]**
* Search NCBI BLAST using a compressed file (i.e. decompress in background and run a search using the web API - this might be a bit over the top)
* Improved performance through a number of avenues;
    * Parallelization (and associated customization)
    * Algorithmic optimization
    * Advanced compression structuring
* Direct transmission link (i.e. no centralized server but direct P2P transmission)
* Hilarious logo (less of a priority)

## Contact
Contact me at alex@holehouse.org

## License

(The MIT License)

Copyright © 2011 Alex Holehouse

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ‘Software’), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED ‘AS IS’, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE


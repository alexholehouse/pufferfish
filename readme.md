# Pufferfish (v1.0)

Pufferfish (the software formerly known as dnacompressor for a while) is an easy to use, lightweight and powerful tool for DNA compression and decompression.

## Basic overview

DNA files in FASTA are a lot bigger than they need to be for storage or transmission. To help deal with this, pufferfish takes as input a text file containing the FASTA format, and very quickly outputs a compressed version of that data.
You can then re-expand that data to its original size using the same tool. The focus here was to provide a tiny program (compiled binary is 183Kb) with big power and functionality.
At the moment usage is limited to

    ./pufferfish -i <input file> -o <output file> [-c] | [-d]
    
Which is to say you take an input file (which must exist) and an output file (which can exits, if it does it will be overwritten) and use either `-c` flag to indicate compress or `-d` flag to indicate decompress.

## Installation

# COMP 345 Advanced Program Design with C++ 
Fall 2017 (Section N)

## Assignment 3 - Essay Generator
* Michael McMahon, **Student ID: 26250912**
* Christopher Dufort, **Student ID: 40030286**
* Jesse Tremblay,	**Student ID: 40027271**
* November, 7th, 2017
* Windows 7/10
* ISO C++11
* Visual Studio 2015/2017, Visual Studio Code v1.17+
* Also use g++ and make from cmdline.
* g++ 6.3.0 32-bit
* g++ 7.2.0 64-bit
* Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 for x86
* stopwords.txt for the stopwords
* INPUT: index.txt, file1.txt, file2.txt, file3.txt | a3index.txt , a3files.txt | abbreviations.txt
* INPUT: a3data (contains 3 query files [qx.txt] and 30 source documents [qxdx.file])
* OUTPUT: output.txt
* Documentation generated via Doxygen 1.8.13

### To to build the application:

```bash
make -f makefile.mk indexing.exe
make -f makefile.mk googler.exe
make -f makefile.mk summarizer.exe

```
To run the application
>indexing.exe
>googler.exe  
>summarizer.exe




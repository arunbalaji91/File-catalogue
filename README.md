Purpose:
This project is used to analyze the directory structure on the local machine, looking for duplicate file names and searching for text in specified files.
1. Used standard C++ and standard libray, compile and link from the command line, using Visual Studio 2013.
2. Used C++ std::iostream library for all input and output to and from user's console and C++ operator such as new and delete      for all dynamic memory management.

STL containers used:
   vector, list, set, map
   
The project performs the following actions based on user specifications:
  1. *.*               : lists out all the files in the root directory.
  2. *.* /s            : lists out all the files starting from the root directory.
  3. *.* /d            : lists out only those files which have duplicate filenames.
  4. *.* /s /d         : lists out all the files starting from root directory which have duplicate filenames.
  5. *.* /s /f text    : lists out all the files starting from the root directory and performs text search on those files.
  6. *.* /s /d /f text : lists out all the files starting from root directory which have duplicate filenames and performs text                           search on those files.
  7. If nothing is specified then the total number of files present in root directory is displayed.

The text search also supports multiple word search.

 
  



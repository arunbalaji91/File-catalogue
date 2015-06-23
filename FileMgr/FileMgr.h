#ifndef FILEMGR_H
#define FILEMGR_H

/////////////////////////////////////////////////////////////////////////////
// FileMgr.h - parses command line arguments and calls other packages      //
//             such as DataStore                                           //
// ver 2.2                                                                 //
// ----------------------------------------------------------------------- //
// copyright © Jim Fawcett, 2012                                           //
// All rights granted provided that this notice is retained                //
// ----------------------------------------------------------------------- //
// Language:    Visual C++, Visual Studio 2010                             //
// Platform:    Lenovo_Z510, Core i5, Windows 8                            //
// Application: Spring Projects, 2015                                      //
// Author:      Arunbalaji Sivakumar, MS-CE, Syracuse University           //
//              (845) 453-5920, asivak01@syr.edu                           //
/////////////////////////////////////////////////////////////////////////////

/*
* Module Operations:
* ==================
* This module provides class FileMgr.
*
* The FileMgr supports parsing command line arguments, get absolute path from the relative path, identify patterns,
* switches, save files and their paths and perfrom search operations on the catalogged files.
*
* Public Interface:
* =================
* FileMgr(const std::string& path, DataStore& ds) : path_(path), store_(ds)
* void FileMgr::addPattern(const std::string& patt)
* std::string& FileMgr::doAnalysis()
* if ((path_.find("../")) != std::string::npos)
* { -------- }
* else if ((path_.find("./")) != std::string::npos)
* { -------- }
* else if (path_[1] != ':')
* { -------- }
*      --   These 'if statements' analyzes the path 
*      --   provided in command line and converts 
*      --   it from relative path to absolute path.
*
* void FileMgr::search(std::string& path)
* {
*    	if ( !switches_.empty() && ( ((switches_.find("/s")) != std::string::npos) || 
* 		((switches_.find("/S")) != std::string::npos)) )
*  ................
*  ...............
* }
*     --    This checks the switches for /s and if it is present 
* 	  --    it perfrom recursive search on all sub-directories 
*
*	 void FileMgr::find(const std::string& path)
*	 std::vector<std::string> files = FileSystem::Directory::getFiles(path, patt);
*     --    This gets the list of file names based on the path and pattern provided.
*
*	 void FileMgr::search_text(const std::string& search_text, const std::vector<std::string>& patterns_s)

* Required Files:
* ===============
* FileMgr.h, FileMgr.cpp, DataStore.h, DataStore.cpp, executivve.cpp
*
* Build Command:
* ==============
* cl /EHa /DTEST_FILEMGR FileMgr.cpp
*
* Maintenance History:
* ====================
* ver 2.2 : 06 Feb 15
* - added return_object() frunction to send the DataStore object back to executive.
*
* ver 2.1 : 03 Feb 15
* - added search text functionality to search for text in catalogged files
*  
* ver 2.0 : 01 Feb 15
* - added doAnalysis() to further parse the path.
* - updated search() function to search recursively.
*   
* ver 1.0 : 21 Jan 15
* - first release
*/


#include "FileSystem.h"
#include "../DataStore/DataStore.h"
#include "../Display/Display.h"

class FileMgr
{
public:
	using iterator = DataStore::iterator;
	using patterns = std::vector<std::string>;
	using switches = std::string;
	
	std::string& doAnalysis();
	FileMgr(const std::string&, DataStore&);
	void addPattern(const std::string&);
	void addSwitches(const std::string&);
	void search(std::string&);
	void find(const std::string&);

	void search_normal(const std::string&, const std::string&, const std::string&);
	void search_with_pattern(const std::string&, const std::vector<std::string>&, const std::string&, const std::string&);
	void search_text(const std::string&, const std::vector<std::string>&);
	
	DataStore return_object();

private:
	std::string path_;
	patterns patterns_;
	switches switches_;
	DataStore store_;
};

#endif

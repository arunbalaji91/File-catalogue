#ifndef DISPLAY_H
#define DISPLAY_H

/////////////////////////////////////////////////////////////////////////////
// Display.h - displays the filenames and paths                            //
//                                                                         //
// ver 2.0                                                                 //
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
* This module provides class Display.
*
* The Display supports printing the filenames and paths in the console.
*
* Public Interface:
* =================
* void Display::display_general(DataStore ds_info)
* void Display::Display_store_count(DataStore ds_info)
* void Display::display_duplicates(DataStore ds_info)

* Required Files:
* ===============
* Display.h, Display.cpp, DataStore.h, DataStore.cpp, executivve.cpp
*
* Build Command:
* ==============
* cl /EHa /DTEST_DISPLAY Display.cpp
*
* Maintenance History:
* ====================*
* ver 2.0 : 08 Feb 15
* - added all Display() functions.
*
* ver 1.0 : 05 Feb 15
* - first release
*/


#include <vector>
#include <map>
#include <list>
#include <set>
#include <string>
#include <iostream>
#include "../DataStore/DataStore.h"

class Display
{
public:

	using Path = std::string;
	using  ListOfIters = std::list <Path>;
	using File = std::string;
	using Store = std::map < File, ListOfIters >;
	using iterator = Store::iterator;
	using list_iterator = ListOfIters::iterator;

	void display_general(DataStore);
	void Display_store_count(DataStore);
	void display_duplicates(DataStore);



};


#endif

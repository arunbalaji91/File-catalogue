#ifndef DATASTORE_H
#define DATASTORE_H

/////////////////////////////////////////////////////////////////////////////
// DataStore.h - saves the filenames and their paths in an STL MAP         //
//                                                                         //
// ver 2.1                                                                 //
// ----------------------------------------------------------------------- //
// Language:    Visual C++, Visual Studio 2010                             //
// Platform:    Lenovo_Z510, Core i5, Windows 8		                       //
// Application: Spring Projects, 2015                                      //
// Author:      Arunbalaji Sivakumar, MS-CE, Syracuse University           //
//              (845) 453-5920, asivak01@syr.edu                           //
/////////////////////////////////////////////////////////////////////////////
/*
* Module Operations:
* ==================
* This module provides class DataStore
*
* The DataStore supports storing the filenames and paths as keys and values in STL map.
* Other packages will request for the contents of the map but cannot edit the Map.
*
*
* Public Interface:
* =================
* void DataStore::save(const std::string& filename, const std::string& path)
*   --  This uses iterators to store the filenames as key and the their paths as values.
*
* std::vector<std::string> DataStore::display()
* std::vector<std::string> DataStore::display_duplicates()
*   -- These functions provide a copy of the content stored in map in a form of vector.
*
* std::string DataStore::store_count()
*   -- This gets the count of filenames and paths stored in the map.
*
* Required Files:
* ===============
* DataStore.h, DataStore.cpp, executivve.cpp
*
* Build Command:
* ==============
* cl /EHa /DTEST_DATASTORE DataStore.cpp
*
* Maintenance History:
* ====================
* ver 2.1 : 05 Feb 15
* - added display() functions to get the contents stored in map 
*
* ver 2.0 : 02 Feb 15
* - updated save() to add keys and values into map.
*   Linux version.
* ver 1.0 : 23 Jan 15
* - first release
*/

#include <vector>
#include <map>
#include <list>
#include <set>
#include <string>
#include <iostream>

class DataStore
{
public:
	using Path = std::string;
	using  ListOfIters = std::list <Path>;
	using File = std::string;
	using Store = std::map < File, ListOfIters >;
	using iterator = Store::iterator;
	using list_iterator = ListOfIters::iterator;

	void save(const std::string&, const std::string&);
	std::vector<std::string> display();
	std::string store_count();
	std::vector<std::string> display_duplicates();
	iterator begin() { return store.begin(); }
	iterator end() { return store.end(); }

private:
	Store store;
};
#endif

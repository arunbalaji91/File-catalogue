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


#include "DataStore.h"
#include <iostream>

/* ------------------------------------------- save files and their paths in the STL DataStore --------------------------------- */
void DataStore::save(const std::string& filename, const std::string& path)
{
	if (store.count(filename) > 0)
	{
		store[filename].push_back(path);
	}
	else
	{
		ListOfIters li;
		li.push_back(path);
		store.insert(std::make_pair(filename, li));
	}
}

/* ------------------------------------------- Send filenames and their paths stored in the STL DataStore  --------------------------------- */
std::vector<std::string> DataStore::display()
{
	list_iterator itl;
	iterator it;
	std::vector<std::string> file_path;
	for (it = store.begin(); it != store.end(); it++)
	{
		file_path.push_back(it->first);
		for (itl = it->second.begin(); itl != it->second.end(); itl++)
		{
			file_path.push_back(*itl);
		}
	}
	return file_path;
}

/* ------------------------------------------- Send filenames and their duplicate paths stored in the STL DataStor-------------------------- */
std::vector<std::string> DataStore::display_duplicates()
{
	std::vector<std::string> Dfile_path;
	std::cout << std::endl << std::endl;
	list_iterator itl;
	for (iterator it = store.begin(); it != store.end(); it++)
	{
		if (it->second.size() > 1)
		{
			Dfile_path.push_back(it->first);
			for (itl = it->second.begin(); itl != it->second.end(); itl++)
			{
				Dfile_path.push_back(*itl);
			}
		}
	}
	return Dfile_path;
}

/* ------------------------------------------- Send number of files and paths stored in the STL DataStore  --------------------------------- */
std::string DataStore::store_count()
{
		int num_file = 0, num_dirs = 0;
		std::string temp_path;
		std::vector<std::string> temp;
		list_iterator itl1, itl2;
		iterator it1, it2;
		size_t i;
		num_file = store.size();
		for (it1 = store.begin(); it1 != store.end(); it1++)
		{
			for (itl1 = it1->second.begin(); itl1 != it1->second.end(); itl1++)
			{
				for (i = 0; i < temp.size(); i++)
				{
					if (temp[i] == *itl1)
					{
						break;
					}
				}
				if (i == temp.size())
				{
					temp.push_back(*itl1);
				}
			}
		}
		temp_path = "";
		temp_path.append(std::to_string(store.size()));
		temp_path.append("_");
		temp_path.append(std::to_string(temp.size()));
		return temp_path;
}

#ifdef TEST_DATASTORE
int main()
{
	std::cout << "\n Testing DataStore";

	DataStore ds;
	ds.save("one");
	ds.save("two");
	ds.save("three");
	DataStore::iterator iter = ds.begin();
	std::cout << "\n " << (*iter).c_str();

	for (auto item : ds)
	{
		std::cout << "\n" << item.c_str();
	}

	std::cout << "\n\n";
	return 0;
}
#endif

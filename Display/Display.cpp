#include "Display.h"
#include <iostream>

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


/* ------------------------------------------- Display files and their paths in the STL DataStore --------------------------------- */
void Display::display_general(DataStore ds_info)
{
	std::vector<std::string> file_path;
	file_path = ds_info.display();
	for (size_t i = 0; i < file_path.size(); i++)
	{
		if (!(file_path[i].find(":") != std::string::npos))
		{
			std::cout << "filename        :" << file_path[i] << std::endl;
		}
		else
		{
			std::cout << "path                   :" << file_path[i] << std::endl;
		}
		std::cout << std::endl;
	}
}

/* ------------------------------------------- Display number of files and paths stored in the STL DataStore  --------------------------------- */
void Display::Display_store_count(DataStore ds_info)
{
	std::string nFiles_mPaths = ds_info.store_count();
	std::cout << "There are " << nFiles_mPaths.substr(0, nFiles_mPaths.find("_")) << " files present in " << nFiles_mPaths.substr(nFiles_mPaths.find("_") + 1, std::string::npos) << " directories" << std::endl;
}

/* ------------------------------------------- Send filenames and their duplicate paths stored in the STL DataStor-------------------------- */
void Display::display_duplicates(DataStore ds_info)
{
	std::vector<std::string> Dfile_path;
	Dfile_path = ds_info.display_duplicates();
	for (size_t i = 0; i < Dfile_path.size(); i++)
	{
		if (!(Dfile_path[i].find(":")!= std::string::npos))
		{
			std::cout << "filename        :" << Dfile_path[i] << std::endl;
		}
		else
		{
			std::cout << "multiple path   :" << Dfile_path[i] << std::endl;
		}
		std::cout << std::endl;
	}
}

#ifdef TEST_DISPLAY
int main()
{
	std::cout << "\n  Testing Display";

	Display disp;
	DataStore ds;
	disp.display_general(ds);
	disp.Display_store_count(ds);
	disp.display_duplicates(ds);

	std::cout << "\n\n";
	return 0;
}
#endif

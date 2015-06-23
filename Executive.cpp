/////////////////////////////////////////////////////////////////////////////
// Executivve.cpp - main function of project 1                             //
//                                                                         //
// ver 2.1                                                                 //
// ----------------------------------------------------------------------- //
// Language:    Visual C++, Visual Studio 2010                             //
// Platform:    Dell XPS 8300, Core i7, Windows 7 SP1                      //
// Application: Spring Projects, 2015                                      //
// Author:      Arunbalaji Sivakumar, MS-CE, Syracuse University           //
//              (845) 453-5920, asivak01@syr.edu                           //
/////////////////////////////////////////////////////////////////////////////

/*
* Module Operations:
* ==================
* This module creates various package objects and performs various operations
* to analyse the command line arguments and console inputs.
*
* Required Files:
* ===============
* FileMgr.h, FileMgr.cpp, FileSystem.h, FileSystem.cpp, DataStore.h, DataStore.cpp, Display.h, Display.cpp
*
* Build Command:
* ==============
* cl compile
*
* Maintenance History:
* ====================*
* ver 2.1 : 05 Jan 15
* - added operations to perfrom seaarch by using th entered text and pattern in console menu.
* ver 2.0 : 30 Jan 15
* - added operations to sepereate command line arguments.
*
* ver 1.0 : 25 Jan 15
* - first release
*/


#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "../FileMgr/FileMgr.h"
#include "../DataStore/DataStore.h"
#include "../Display/Display.h"

//#ifdef TEST_EXECUTIVVE
int main(int argc, char* argv[])
{
	std::string path, pattern, switches, final_string, single_pattern, search_text, new_search_text_pattern;
	std::vector<std::string> user_input, switches_, temp_pattern;
	size_t pos = 0;
	int temp1;
	user_input.assign(argv + 1, argv + argc);

	/* -------------------------------------- Get path, pattern(s) and switch(es) from the command line arguments ------------------------------- */
	path = "";
	for (size_t i = 0; i < user_input.size(); i++)
	{
		if ((user_input[i].find("\\") != std::string::npos) || (user_input[i].find("./") != std::string::npos) || (user_input[i].find("../") != std::string::npos))
		{
			path.append(user_input[i]);
		}
		else if ((user_input[i].find("*.")) != std::string::npos)
		{
			temp_pattern.push_back(FileSystem::Path::toLower(user_input[i]));
		}
		else if (user_input[i].find("/") != std::string::npos)
		{
			switches.append(user_input[i]);
		}
		else
		{
			switches.append(" ");
			switches.append(user_input[i]);
		}
	}
	if (path.empty())
	{
		path = "./";
	}
	if (temp_pattern.size() == 0)
	{
		temp_pattern.push_back("*.*");
	}
	DataStore ds;
	FileMgr fm(path, ds);
	Display disp;

	/* ------------------------------------------------------------ get search text if available ---------------------------------------*/
	if ((switches.find("/f") != std::string::npos) || (switches.find("/F") != std::string::npos))
	{
		if ((switches.find("/F") != std::string::npos))
		{
			temp1 = switches.find("/F") + 2;
		}
		else
		{
			temp1 = switches.find("/f") + 2;
		}
		search_text = switches.substr(temp1, std::string::npos);
	}

	/* ------------------------------------------------------------ adding patterns to FileMgr -----------------------------------------*/
	for (size_t i = 0; i < temp_pattern.size(); i++)
	{
		fm.addPattern(temp_pattern[i]);
	}

	/* ------------------------------------------------------------ send the switches to FileMgr ---------------------------------------*/
	fm.addSwitches(switches);

	/* -----------------------------------------------------------  call FileMgr to start process --------------------------------------*/
	std::string temp_path = fm.doAnalysis();

	/* -----------------------------------------------------------  start performing user actions --------------------------------------*/
	fm.search(temp_path);

	/* ----------------------------------------------------------- Get the processed DataStore object --------------------------------------------------*/
	ds = fm.return_object();

	/* --------------------------------------------- Call to Display files and paths stored in STL dataStore  ---------------------------*/
	if (user_input.size() == 0)
	{
		disp.Display_store_count(ds);
	}
	else if (!((switches.find("/D")) != (std::string::npos)) && !((switches.find("/d")) != (std::string::npos)))
	{
		disp.display_general(ds);
	}
	else if (((switches.find("/d")) != (std::string::npos)) && ((switches.find("/s")) != (std::string::npos)) ||
		(((switches.find("/D")) != (std::string::npos)) && ((switches.find("/S")) != (std::string::npos))))
	{
		std::cout << "main dup" << std::endl;
		disp.display_duplicates(ds);
	}

	/* -----------------------------------------------------------  perform text search on catalogged files ----------------------------*/
	if (!search_text.empty())
	{
		std::vector<std::string> temp_v;
		fm.search_text(search_text, temp_v);
	}
	else if ((switches.find("/f") != std::string::npos) || (switches.find("/F") != std::string::npos))
	{
		std::cout << std::endl << "No search text provided" << std::endl << std::endl;
	}
	while (1)
	{
		std::cout << std::endl <<"ENTER THE TEXT TO BE SEARCHED IN THE CATALOGGED FILES -----> eg: \"TEXT\" *.cpp *.txt or \"TEXT\" :" << std::endl << std::endl;
		std::getline(std::cin, new_search_text_pattern);
		if (!new_search_text_pattern.empty())
		{
			std::cout << std::endl << std::endl;
			search_text = new_search_text_pattern.substr(new_search_text_pattern.find_first_of("\"") + 1, new_search_text_pattern.find_last_of("\"") - 1);
			if (search_text[search_text.size() - 1] == '\"')
			{
				temp1 = search_text.size() - 1;
				search_text = search_text.substr(0, temp1);
			}
			if (new_search_text_pattern.find_last_of("\"") < (new_search_text_pattern.find_first_of("*.")))
			{
				temp1 = search_text.size();
				final_string = new_search_text_pattern.substr(temp1 + 2, std::string::npos);
			}
			else
			{
				final_string = new_search_text_pattern.substr(0, new_search_text_pattern.find_first_of("\""));
			}
			temp_pattern.clear();
			std::istringstream iss (final_string);
			std::string temp;
			while (iss >> temp)
			{
				temp_pattern.push_back(temp);
			}			
			fm.search_text(search_text, temp_pattern);
		}
		else
		{
			break;
		}
	}
}
//#endif

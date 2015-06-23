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


#include "FileMgr.h"
#include <iostream>

FileMgr::FileMgr(const std::string& path, DataStore& ds) : path_(path), store_(ds)
{
	patterns_.push_back("*.*");
}

/* -------------- to add individual patterns ---------*/
void FileMgr::addPattern(const std::string& patt)
{
	if (patterns_.size() == 1 && patterns_[0] == "*.*")
		patterns_.pop_back();
	patterns_.push_back(patt);
}

/* -------------get all the user provided switches --------*/
void FileMgr::addSwitches(const std::string& swit)
{
	switches_ = swit;
}

std::string& FileMgr::doAnalysis()
{
	std::string new_path_, temp;
	if ((path_.find("../")) != std::string::npos)
	{
		temp = FileSystem::Directory::getCurrentDirectory();
		new_path_ = temp.substr(0, temp.find_last_of("\\"));
		for (size_t i = 0; i < path_.size(); i++)
		{
			if (path_[i] == '/')
			{
				path_[i] = '\\';
			}
		}
		temp = path_.substr(path_.find_first_of("\\"));		
		new_path_.append(temp);
		path_ = new_path_;
		FileSystem::Directory::setCurrentDirectory(path_);
	}
	else if ((path_.find("./")) != std::string::npos)
	{
		new_path_ = FileSystem::Directory::getCurrentDirectory();
		for (size_t i = 0; i < path_.size(); i++)
		{
			if (path_[i] == '/')
			{
				path_[i] = '\\';
			}
		}
		temp = path_.substr(path_.find_first_of("\\"));
		new_path_.append(temp);
		path_ = new_path_;
		FileSystem::Directory::setCurrentDirectory(path_);
	}
	else if (path_[1] != ':')
	{
		new_path_ = FileSystem::Directory::getCurrentDirectory();
		new_path_.append("\\");
		new_path_.append(path_);
		path_ = new_path_;
		FileSystem::Directory::setCurrentDirectory(path_);
	}
	return path_;
}


/* ----------------------------------------------------- search for files matchig the path and pattern ---------------------------------------*/
void FileMgr::search(std::string& path)
{
	find(path);
	std::vector<std::string> sub_dirs;
	if ( !switches_.empty() && ( ((switches_.find("/s")) != std::string::npos) || ((switches_.find("/S")) != std::string::npos)) )
	{
		sub_dirs.clear();
		sub_dirs = FileSystem::Directory::getDirectories(path, "*.*");
		for (size_t i = 0; i < sub_dirs.size(); i++)
		{
			std::string tt;
			if (sub_dirs[i] != "." && sub_dirs[i] != "..")
			{
				tt = path;
				tt.append("\\");
				tt.append(sub_dirs[i]);
				search(tt);
			}
		}
	}
}

/* -------------------------------------------------------- add the matched files and their path to the STL DataStore -----------------------------------------*/
void FileMgr::find(const std::string& path)
{
	if (patterns_[0] != "*.*")
	{
		for (auto patt : patterns_)
		{
			std::vector<std::string> files = FileSystem::Directory::getFiles(path, patt);
			for (auto f : files)
			{
				store_.save(f, path);
			}
		}
	}
	else
	{
		std::vector<std::string> files = FileSystem::Directory::getFiles(path);
		for (auto f : files)
		{
			store_.save(f, path);
		}
	}
}

/* ----------------------------------------------------------- Return the processed DataStore object --------------------------------------------------*/
DataStore FileMgr::return_object()
{
	return store_;
}

/* --------------------------------------------- Search for text in files stored in the STL DataStore -----------------------------------------------*/
void FileMgr::search_text(const std::string& search_text, const std::vector<std::string>& patterns_s)
{
	using Path = std::string;
	using  ListOfIters = std::list < Path >;
	using File = std::string;
	using list_iterator = ListOfIters::iterator;
	std::string temp_filespec;
	std::cout << "list of catalogged files having the search text " << search_text << " is/are....." << std::endl;
	for (iterator it = store_.begin(); it != store_.end(); it++)
	{
		for (list_iterator it2 = it->second.begin(); it2 != it->second.end(); it2++)
		{
			if (!FileSystem::Directory::setCurrentDirectory(*it2) && !FileSystem::File::exists(it->first))
			{
				std::cout << "cannot set current directory for the path  " << *it2 << std::endl;
				if (!FileSystem::File::exists(it->first))
				{
					std::cout << "cannot find file " << it->first << "in the current directory" << std::endl;
				}
			}
			else
			{
				if (!patterns_s.empty())
				{
					search_with_pattern(search_text, patterns_s, it->first, *it2);				
				}
				else if (patterns_s.empty() || patterns_s[0] == "*.*")
				{
					search_normal(search_text, it->first, *it2);
				}
			}
		}
	}
}

/* --------------------------------------------- Search for text in files stored in the STL DataStore with user specified patterns ----------------------------*/
void FileMgr::search_with_pattern(const std::string& search_text, const std::vector<std::string>& patterns_s, const std::string& filename, const std::string& path)
{
	std::string temp_filespec;
	for (size_t i = 0; i < patterns_s.size(); i++)
	{
		if (FileSystem::Path::getExt(filename) == FileSystem::Path::getExt(patterns_s[i]))
		{
			FileSystem::File fs(filename);
			bool x = fs.open(FileSystem::File::in, FileSystem::File::text);
			if (x == false)
			{
				std::cout << "error opening" << std::endl;
			}
			if (fs.isGood())
			{
				temp_filespec = fs.readAll();
				if (!temp_filespec.empty() && (temp_filespec.find(search_text) != std::string::npos))
				{
					std::cout << std::endl << "file name     :  " << filename << std::endl;
					std::cout << "path          :  " << path << std::endl << std::endl;
					temp_filespec = "";
				}
			}
			else
			{
				std::cout << "The file cannot be read" << std::endl << std::endl;
			}
			fs.flush();
			fs.clear();
			fs.close();
		}
	}
}

/* ------------------------------------------ look for text in the saved files in datastore -----------------------------------------------------*/
void FileMgr::search_normal(const std::string& text, const std::string& filename, const std::string& path)
{
	std::string temp;
	FileSystem::File fs(filename);
	bool x = fs.open(FileSystem::File::in, FileSystem::File::text);
	if (x == false)
	{
		std::cout << "error opening" << std::endl;
	}
	if (fs.isGood())
	{
		temp = fs.readAll();
		if (!temp.empty() && (temp.find(text) != std::string::npos))
		{
			std::cout << std::endl << "file name     :  " << filename << std::endl;
			std::cout << "path          :  " << path << std::endl << std::endl;
			temp = "";
		}
	}
	else
	{
		std::cout << "The file cannot be read" << std::endl << std::endl;
	}
	fs.flush();
	fs.clear();
	fs.close();
}

#ifdef TEST_FILEMGR
int main(int argc, char* argv[])
{
	DataStore ds;
	std::vector<std::string> vec;
	vec.push_back("*.txt");
	vec.push_back("*.cpp");
	vec.push_back("*.h");
	std::string p = "./";
	FileMgr fm(p, ds);
	fm.addPattern("*.h");
	fm.addPattern("*.*");
	fm.search(p);
	fm.search_text("FileMgr", vec);
	std::cout << "\n\n";
	std::getchar();
	return 0;
}
#endif

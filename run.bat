@echo off
: --------------------------------------- requirement 3 -----------------------------------------------
echo                                                    "DEMONSTRATING REQUIREMENT 3 WITH /S"  
echo                                                 "Get all files starting from root directory" 
echo:                                            
echo       :Executivve\Executivve\main_folder\sub_folder_2 *.cpp *.txt /s
echo:
"Executivve/Debug/Executivve.exe" Executivve\Executivve\main_folder\sub_folder_2 *.cpp *.txt /s
:
:
:
:
echo                                                        "DEMONSTRATING REQUIREMENT 3 WITHOUT /S"                                            
echo                                                         "Get all files only at root directory" 
echo:
echo       :Executivve\Executivve\main_folder\sub_folder_2 *.cpp *.txt
echo:
"Executivve/Debug/Executivve.exe" Executivve\Executivve\main_folder\sub_folder_2 *.cpp *.txt
:
:
:
: --------------------------------------- requirement 5 -----------------------------------------------
echo                                                        DEMONSTRATING REQUIREMENT 5 WITH /D     
echo                                                        "Get files with duplicate filename"                                        
echo:
echo       :Executivve\Executivve\main_folder\sub_folder_2 *.cpp *.txt /d
echo:
"Executivve/Debug/Executivve.exe" Executivve\Executivve\main_folder\sub_folder_2 *.cpp *.txt /d
:
:
:
:
echo                                                        DEMONSTRATING REQUIREMENT 5 WITHOUT /D   
echo                                                          "Get files only in root directory"  
echo:
echo       :Executivve\Executivve\main_folder\sub_folder_2 *.cpp *.txt
echo:                                        
"Executivve/Debug/Executivve.exe" Executivve\Executivve\main_folder\sub_folder_2 *.cpp *.txt
:
:
:
:
echo                                                        DEMONSTRATING REQUIREMENT 5 WITH /S AND /D 
echo                                 "Get all files starting from root directory which only has duplicate filenames "                                           
echo:
echo       :Executivve\Executivve\main_folder\sub_folder_2 *.cpp *.txt /s /d
echo:
"Executivve/Debug/Executivve.exe" Executivve\Executivve\main_folder\sub_folder_2 *.cpp *.txt /s /d
:
:
:
:
: --------------------------------------- requirement 6 -----------------------------------------------
echo                                                        DEMONSTRATING REQUIREMENT 6 WITH /S /F AND SEARCH TEXT      
echo                                          "Get all files starting from root directory and perfrom text search on those files"                                     
echo:
echo       :Executivve\Executivve\main_folder\sub_folder_2 *.cpp *.txt /s /f Apples and oranges
echo:
"Executivve/Debug/Executivve.exe" Executivve\Executivve\main_folder\sub_folder_2 *.cpp *.txt /s /f Apples and oranges
:
:
:
:
echo                                                        DEMONSTRATING REQUIREMENT 6 WITH /S /D /F AND  SEARCH TEXT                                           
echo                            "Get files starting from root directory which has duplicate filenames and perfrom text search on those files"
echo:
echo       :Executivve\Executivve\main_folder\sub_folder_2 *.cpp *.txt /s /d /f apples	and	oranges
echo:
"Executivve/Debug/Executivve.exe" Executivve\Executivve\main_folder\sub_folder_2 *.cpp *.txt /s /d /f apples	and	oranges
:
:
:
: --------------------------------------- requirement 7 -----------------------------------------------
echo                                                        DEMONSTRATING REQUIREMENT 6 NOTHHING
echo                                                  "Dispaly total number of files and directories"                                           
"Executivve/Debug/Executivve.exe"
:
:
:

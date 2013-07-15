// ***CRARExtractor***
// ListContents - print out file listing of the rar file
// ExtractFile - extract specified file name
// ExtractAll - goes through list, extracts all files and directories
// CleanUp - deletes all files and directories listed within the rar file list

// Possible future additions:
// check for existing files before overwriting them during extraction
// compare files before deleting them in cleanup (make sure file size etc is the same)

#ifndef RAREX
#define RAREX

#include "unrarlib.h"
#include <stdio.h>
#include <io.h> // needed by _filelength()
//#include <iostream.h>
#include <string>
#include <direct.h> // for making directorys

#include <windows.h> // messing with resources requires this
#include "resource.h" // need this for the rar file as a resource                     
                                          
using namespace std;

class CRARExtractor
{
public:
	CRARExtractor(); // constructor
	~CRARExtractor(); // deconstructor
	void ListContents(); // list contents of rar file, only used in debugging
	void ExtractFile(char *filename); // extracts filename from the rar file
	void ExtractAll(); // extracts all files within the rar file list
	void CleanUp(); // removes all files listed in the rar file from the working directory

private:
	ArchiveList_struct *list; // list of all files and their details held within the rar file
	MemoryFile rarfile; // the rar file, as held in memory
	int filecounter; // how many files are in the rar file

	void CreateList(); // remakes the rar file list and resets the pointer to the start
	void openRARResource(MemoryFile *memfile, int resource_id); // opens a rar file from a resource
	void PrintList(); // print out the list struct
	string FormatString(char *thestring); // format a filename into acceptable format
	bool IsDir(char *filename); // checks to see if a file is a file or a directory
	void RemoveFile(char *filename, unsigned long newfilesize); // delete filename
	bool FileExists(char *filename); // does the filename exist
	long GetFileSize(char *filename); // return size of the filename
};
#endif
/* ***************************************************************************
 **
 **  This file is part of the UniquE RAR File Library.
 **
 **  Copyright (C) 2000-2002 by Christian Scheurer (www.ChristianScheurer.ch)
 **  UNIX port copyright (c) 2000-2002 by Johannes Winkelmann (jw@tks6.net)
 ** 
 **  The contents of this file are subject to the UniquE RAR File Library
 **  License (the "unrarlib-license.txt"). You may not use this file except 
 **  in compliance with the License. You may obtain a copy of the License
 **  at http://www.unrarlib.org/license.html.
 **  Software distributed under the License is distributed on an "AS IS"
 **  basis, WITHOUT WARRANTY OF ANY KIND, either express or implied warranty.
 ** 
 **  Alternatively, the contents of this file may be used under the terms
 **  of the GNU General Public License Version 2 or later (the "GPL"), in
 **  which case the provisions of the GPL are applicable instead of those
 **  above. If you wish to allow use of your version of this file only
 **  under the terms of the GPL and not to allow others to use your version
 **  of this file under the terms of the UniquE RAR File Library License,
 **  indicate your decision by deleting the provisions above and replace
 **  them with the notice and other provisions required by the GPL. If you
 **  do not delete the provisions above, a recipient may use your version
 **  of this file under the terms of the GPL or the UniquE RAR File Library
 **  License.
 ** 
 ************************************************************************** */

#include "CRARExtractor.h"

CRARExtractor::CRARExtractor()
{
	list = NULL;

	openRARResource(&rarfile, IDR_RARFILE1); // open rar resource
}

CRARExtractor::~CRARExtractor()
{
	if(list != NULL) free(list);
}

void CRARExtractor::ExtractFile(char *filename)
// extract filename from the rar file
{
	FILE *datafp; // the file to write data to
	char *data_ptr; // points to decompressed data
	unsigned long data_size; // holds size of current file
	string filestring; // for converting filename to a string, easier to edit strings

	if(urarlib_get(&data_ptr, &data_size, filename, &rarfile, "password")) 
	{
		// file successfully decompressed into memory
	} 
	else // couldnt find file in memory, or could not decompress file
	{ 
		if(data_ptr != NULL) free(data_ptr); // free memory
		return;
	}

	filestring = filename;

	if(IsDir(filename)) // we have a directory so we dont write the data
	{
		if( _mkdir( filename ) == 0 ) // mkdir success
		{
		}
		else // mkdir failed		
		{
			// this can fail if the directory already exists so we assume it worked
			// if it didnt already exist, all files copying to the directory will fail anyway
		}
	}
	else // we have a file so we write it
	{
		if (FileExists(filename)) // file already exists
		{
			if(data_ptr != NULL) free(data_ptr); // free memory
			return; // exit out, better not alter it
		}

		if ((datafp = fopen(filestring.c_str(), "wb")) == NULL) // if the file cant be opened/created
		{
			if(data_ptr != NULL) free(data_ptr); // free memory
			return;
		}

		fwrite(data_ptr, 1, data_size, datafp); // write data to file
		fclose(datafp);
	}

	if(data_ptr != NULL) free(data_ptr); // free memory
}

void CRARExtractor::ExtractAll()
// find each file from the rar file list and extract them
{
	CreateList(); // reset the file list
	while(filecounter > 0) // while there are still files left
	{
		filecounter--;
		ExtractFile(list->item.Name); // extract current list entry
		(ArchiveList_struct*)list = (ArchiveList_struct*)list->next; // move to next entry
	}

}

void CRARExtractor::openRARResource(MemoryFile *memfile, int resource_id)
/* get pointer to RAR file in memory which is linked as resource file       */
/* This works fine for MS VisualC 6.0, you may have to change this method   */
/* for other compilers and operating systems. Please give me your versions  */
/* for gcc, BC and other compilers, so I can distribute them with the next  */
/* release.                                                                 */
{
	HRSRC           hsResourceFH;             /* needed to load resources     */
	HGLOBAL         hgResourceLH;
	HINSTANCE	    hInstance  = GetModuleHandleA(NULL); 

	memfile->data   = 0;                      /* init with NULL values        */
	memfile->size   = 0;
	memfile->offset = 0;

	hsResourceFH = FindResource(hInstance, MAKEINTRESOURCE(resource_id), "RARFILE");
	if(hsResourceFH)
	{
		hgResourceLH = LoadResource(hInstance, hsResourceFH);
		if(hgResourceLH)
		{
			memfile->size = SizeofResource(hInstance, hsResourceFH);
			memfile->data = (void*)LockResource(hgResourceLH);
		}
	} 
}

void CRARExtractor::ListContents()
// creates a list of the current rar file and then outputs it to screen
{
	CreateList();
	//PrintList(); // used for debug stuff
}

void CRARExtractor::CreateList()
// creates a list, erasing any old ones and setting the list pointer at the start
{
	// file counter will equal the number of file entries in the list
	filecounter = urarlib_list(&rarfile, (ArchiveList_struct*)&list);
}

void CRARExtractor::PrintList()
// display structure of information about a RAR archive
// *** shouldnt be used since it uses cout's and printf's ***                  
{
	// set up table headings
	/*cout << "                   Name     Size  Packed   OS  FileTime    ";
	cout << "CRC-32 Attr Ver Meth\n";
	cout << "     ------------------------------------------------------";
	cout << "--------------------\n";*/

	while(list != NULL){ // while the list isnt empty
		if(list->item.NameSize < 23)
		{
			printf("%23s", list->item.Name);
		} 
		else
		{
			printf("%23s", "[name too long]");
		}
		//cout << list->item.UnpSize;
		printf("%9d",  list->item.UnpSize);
		printf("%8d",  list->item.PackSize);
		printf("%5d",  list->item.HostOS);
		printf("%10x", list->item.FileTime);
		printf("%10x", list->item.FileCRC);
		printf("%5d",  list->item.FileAttr);
		printf("%4d",  list->item.UnpVer);
		printf("%5d",  list->item.Method);
		//cout << "\n";

		(ArchiveList_struct*)list = (ArchiveList_struct*)list->next; // next list item
	}

	//cout << "\n\n";
}

string CRARExtractor::FormatString(char *thestring)
// form filename into directory acceptable format
// not used anymore
{
	string tempstring;

	tempstring = thestring;
	tempstring.insert(0, "\\"); // stick \\'s at the start of the string

	return tempstring;
}

bool CRARExtractor::IsDir(char *filename)
// checks a filename to see if its a filename(return false) or a directory(return true)
// simply searches for a '.' in the filename
// PROBLEM: if u have a directory with an extension eg \myhouse.dir\blah
// itll think its a file!
{
	string tempstring;
	int searchvalue = 0;

	tempstring = filename;
	searchvalue = tempstring.find("."); // look for a dot

	if(searchvalue < 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CRARExtractor::CleanUp()
// goes through the rar file list and removes each file and directory
// need to do two passes, pass one kills files, pass two kills directorys
// this is because directorys cannot be removed if they contain files
// PROBLEM: it cant handle sub, sub directories! eg \gfx\menus
{

	CreateList(); // set up the rar file list

	while(filecounter > 0) // kill files, first pass
	{
		filecounter--;
		if (!IsDir(list->item.Name)) // make sure its a file
			RemoveFile(list->item.Name, list->item.UnpSize); // Remove this entry
		(ArchiveList_struct*)list = (ArchiveList_struct*)list->next; // move to next entry
	}

	CreateList(); // set up the rar file list
	while(filecounter > 0) // kill directories, second pass
	{
		filecounter--;
		if (IsDir(list->item.Name)) // make sure its a directory
			RemoveFile(list->item.Name, list->item.UnpSize); // Remove this entry
		(ArchiveList_struct*)list = (ArchiveList_struct*)list->next; // move to next entry
	}
}

void CRARExtractor::RemoveFile(char *filename, unsigned long newfilesize)
// removes files and directories
// if a directory has files in it, it will fail at deleting it!
{
	if (IsDir(filename)) // if its a directory
	{
		if (_rmdir(filename) == -1) // dir remove failed
		{
		}
			
	}
	else // if its a file
	{
		if (newfilesize != GetFileSize(filename)) // check if its the same size
		{ // file is a different size, must be a different file
			return; // dont remove this file, might be different
		}

		if (remove(filename) == -1) // file delete failed
		{
			// it might be protected or in use by an application
			// theres nothing we can really do
		}
	}
}

bool CRARExtractor::FileExists(char *filename)
// checks if the file specified by filename exists
// just a simple open for reading test
// this could possibly fail if another application opens the file and wont share it
{
	FILE *tempstream; // temporary file

	if ((tempstream = fopen(filename, "r")) == NULL) // file couldnt be opened, doesnt exist
		return false;
		
	fclose(tempstream); // close file
	return true;
}

long CRARExtractor::GetFileSize(char *filename)
// returns the length of the existing file filename
// this wont work if the file is over 4 gigabytes HAH!
{
	FILE *tempstream; // temporary file
	int streamhandle; // handle for the temp file
	long thelength; // holds the length of the file in bytes

	if ((tempstream = fopen(filename, "r")) == NULL) // open file
		return 0; // file wouldnt open, exit out

	streamhandle = _fileno(tempstream); // get its handle
	
	thelength = _filelength(streamhandle); 

	fclose(tempstream); // close that file

	return thelength; // return file size
}
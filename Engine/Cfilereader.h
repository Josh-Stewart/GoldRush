// DO NOT PLAY WITH THE CONFIG FILE ITS FRAGILE

// known problems:
// o	Config file must have a newline after the final data entry or it will have trouble
//		writing to the last data entry
// o	Doesnt do any checks to see if the file is corrupt or in the right format

#ifndef CFILEREADER
#define CFILEREADER
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

class Cfilereader {

private:
	
	ifstream configfile; // the master file variable

	string defaultfilename; // default config filename
	string configfilename; // filename of configfile

	int LoadFile(string filename); // load a file from its name
	int LoadFile(); // load the configfile

	void CloseFile(); // close current file

	string GetStringFromConfig(); // gets a string from the config file
	string FindLabel(string thelabel); // finds the label and returns the data held within it
	int WriteToLabel(string thelabel, string newdata); // find the label and write newdata under it

public:

	Cfilereader(); // default constructor
	Cfilereader(string filename); // filename provides the name/location of the configfile
	~Cfilereader();

	string LoadFromConfig(string label); // returns the data held under label
	int SaveToConfig(string label, string newvalue); // saves newvalue under label

	void CreateDefault(); // creates a new configfile with default values
	bool Exists(); // checks to see if configfile exists
};
#endif

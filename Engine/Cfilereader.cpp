#include "Cfilereader.h"

Cfilereader::Cfilereader()
{
	defaultfilename = "goldrush.cfg";
	configfilename = defaultfilename;
}

Cfilereader::Cfilereader(string filename)
{
	configfilename = filename;
}

Cfilereader::~Cfilereader()
{
	if (configfile.is_open()) // if it hasnt been closed
		configfile.close();
}

int Cfilereader::LoadFile(string filename)
{
	configfile.open(filename.c_str(), ios::in | ios::out);
	if (!configfile)
	{
		cout << "Cannot open config file " << filename.c_str() << ".\n";
		return 1;
	}
	configfile.seekg(0, ios::beg); // set file to start
	configfile.clear(); // clear flags (eof etc)
	return 0;
}

int Cfilereader::LoadFile()
{
	configfile.open(defaultfilename.c_str(), ios::in | ios::out);
	if (!configfile)
	{
		cout << "Cannot open config file.\n";
		return 1;
	}
	configfile.seekg(0, ios::beg); // set file to start
	configfile.clear(); // clear flags (eof etc)
	return 0;
}

void Cfilereader::CloseFile()
{
	configfile.seekg(0, ios::beg);
	configfile.clear();

	if (configfile.is_open()) // its still open
		configfile.close();
}

string Cfilereader::GetStringFromConfig()
{
	string tempstring;
	getline(configfile, tempstring);
	cout << tempstring << "\n";
	return tempstring;
}

string Cfilereader::FindLabel(string thelabel)
{
	string thedata; // string to be returned
	char nextchar; // used to hold characters from the file

	while(!configfile.eof()) // loop until EOF
    {
		// we get each character one at a time until we hit eof or a newline
        while(configfile.peek() != '\n' && !configfile.eof())
        {
			
            if(configfile.peek() != ':') // if we dont have the whole label
            {
				nextchar = configfile.get();
				thedata += (char)nextchar;
            }
            else // we have the whole label
			{
				if (thelabel == thedata) // compare thedata and thelabel
				{
					thedata.erase();
					configfile.ignore(255, ':'); // get rid of colon
					// get the rest of the line
					while(configfile.peek() != '\n' && !configfile.eof())
					{
						nextchar = configfile.get();
						thedata += (char)nextchar;
					}
					// we should now have the string value
					return thedata; // success
				}
				else
				{
					getline(configfile, thedata); // get the rest of the line
					thedata.erase(); // clear string ready for next use
				}
			}
		}
        configfile.ignore(255, '\n');
    }
	return "NOTFOUND"; // couldnt find string
}

int Cfilereader::WriteToLabel(string thelabel, string newdata)
{	
	if (thelabel.empty()) return 1;

	streampos colonindex; // address of the spot after the colon

	string currentlabel; // holds the current label name
	string tempstring, bufferstring;

	char nextchar; // temp char to hold chars as they are read

	ostream oconfigfile(configfile.rdbuf()); // copies the configfile input stream into output stream (an input output stream :D)

	oconfigfile.seekp(0, ios::beg); // set file to start
	oconfigfile.clear(); // clear flags

	while(!configfile.eof()) // loop until EOF
	{
		// we get each character one at a time until we hit eof or a newline
		while(configfile.peek() != '\n' && !configfile.eof())
		{
			if(configfile.peek() != ':') // if we dont have the whole label
			{
				nextchar = configfile.get();
				currentlabel += (char)nextchar;
			}
			else
			{
				if (thelabel != currentlabel) // if its the wrong label
				{
					getline(configfile, currentlabel); // get the rest of the line
					currentlabel.erase(); // empty the label string
				}
				else // if its the right label
				{
					currentlabel.empty(); // empty the label
					configfile.ignore(255, ':'); // get rid of colon
					colonindex = configfile.tellg(); // set colonindex to address of the spot after the colon
					
					while(configfile.peek() != '\n' && !configfile.eof()) { nextchar = configfile.get();}// move buffer to the end of the line					
					if(configfile.peek() == '\n') nextchar = configfile.get();

					bufferstring.erase();
					tempstring.erase();

					while(!configfile.eof())
					{
						bufferstring += '\n';
						getline(configfile, tempstring);
						bufferstring += tempstring;
					}

					//cout << "changing " << thelabel << " to " << newdata << "\n";

					oconfigfile.seekp(colonindex, ios::beg); // now go back to the colon index					
					oconfigfile.write(newdata.c_str(), newdata.size());

					oconfigfile << bufferstring;
					return 0; // success
				}
			}
		}
		configfile.ignore(255, '\n'); // so we dont get stuck on a newline
	}

	return 1; // couldnt find the label
}

string Cfilereader::LoadFromConfig(string label)
{
	string thedata; // string to be returned

	// open config file
	if (LoadFile() == 1) // an error occured opening the file
	{ 
		return "BADFILE"; 
	}

	// find string label and set thedata to the value held under string label 
	thedata = FindLabel(label);

	// close configfile
	CloseFile();
	return thedata;
}

int Cfilereader::SaveToConfig(string label, string newvalue)
{
	// open config file
	if (LoadFile() == 1) // an error occured opening the file
	{ 
		return 1; 
	}

	// find string label
	// save newvalue under label
	if (WriteToLabel(label,newvalue) == 1)
	{
		CloseFile();
		return 1;
	}

	// close config file
	CloseFile();
	return 0; // success
}

void Cfilereader::CreateDefault()
{
	ofstream newfile;
	FILE *tempfile = NULL;

	// create the file
	tempfile = fopen(configfilename.c_str(), "w");
	if (tempfile == NULL)
	{
		//file creation failed
	}
	fclose(tempfile);

	newfile.open(configfilename.c_str(), ios::in | ios::out);
	if (!newfile)
	{
		// failed to create the file
		return;
	}	

	// set the values
	newfile.write("thisis:thetop\n", 14);
	newfile.write("musicvolume:0\n", 14);
	newfile.write("soundvolume:150\n", 16);
	newfile.write("name0:Empty\n", 12);
	newfile.write("name1:Empty\n", 12);
	newfile.write("name2:Empty\n", 12);
	newfile.write("name3:Empty\n", 12);
	newfile.write("name4:Empty\n", 12);
	newfile.write("name5:Empty\n", 12);
	newfile.write("name6:Empty\n", 12);
	newfile.write("name7:Empty\n", 12);
	newfile.write("name8:Empty\n", 12);
	newfile.write("name9:Empty\n", 12);
	newfile.write("score0:0\n", 9);
	newfile.write("score1:0\n", 9);
	newfile.write("score2:0\n", 9);
	newfile.write("score3:0\n", 9);
	newfile.write("score4:0\n", 9);
	newfile.write("score5:0\n", 9);
	newfile.write("score6:0\n", 9);
	newfile.write("score7:0\n", 9);
	newfile.write("score8:0\n", 9);
	newfile.write("score9:0\n", 9);
	newfile.write("levelsave_level:1\n", 18);
	newfile.write("levelsave_track_0_0:0\n", 22);
	newfile.write("levelsave_track_1_0:0\n", 22);
	newfile.write("levelsave_track_2_0:0\n", 22);
	newfile.write("levelsave_track_3_0:0\n", 22);
	newfile.write("levelsave_track_4_0:0\n", 22);
	newfile.write("levelsave_track_5_0:0\n", 22);
	newfile.write("levelsave_track_6_0:0\n", 22);
	newfile.write("levelsave_track_7_0:0\n", 22);
	newfile.write("levelsave_track_0_1:0\n", 22);
	newfile.write("levelsave_track_1_1:0\n", 22);
	newfile.write("levelsave_track_2_1:0\n", 22);
	newfile.write("levelsave_track_3_1:0\n", 22);
	newfile.write("levelsave_track_4_1:0\n", 22);
	newfile.write("levelsave_track_5_1:0\n", 22);
	newfile.write("levelsave_track_6_1:0\n", 22);
	newfile.write("levelsave_track_7_1:0\n", 22);
	newfile.write("levelsave_track_0_2:0\n", 22);
	newfile.write("levelsave_track_1_2:0\n", 22);
	newfile.write("levelsave_track_2_2:0\n", 22);
	newfile.write("levelsave_track_3_2:0\n", 22);
	newfile.write("levelsave_track_4_2:0\n", 22);
	newfile.write("levelsave_track_5_2:0\n", 22);
	newfile.write("levelsave_track_6_2:0\n", 22);
	newfile.write("levelsave_track_7_2:0\n", 22);
	newfile.write("levelsave_track_0_3:0\n", 22);
	newfile.write("levelsave_track_1_3:0\n", 22);
	newfile.write("levelsave_track_2_3:0\n", 22);
	newfile.write("levelsave_track_3_3:0\n", 22);
	newfile.write("levelsave_track_4_3:0\n", 22);
	newfile.write("levelsave_track_5_3:0\n", 22);
	newfile.write("levelsave_track_6_3:0\n", 22);
	newfile.write("levelsave_track_7_3:0\n", 22);
	newfile.write("levelsave_track_0_4:0\n", 22);
	newfile.write("levelsave_track_1_4:0\n", 22);
	newfile.write("levelsave_track_2_4:0\n", 22);
	newfile.write("levelsave_track_3_4:0\n", 22);
	newfile.write("levelsave_track_4_4:0\n", 22);
	newfile.write("levelsave_track_5_4:0\n", 22);
	newfile.write("levelsave_track_6_4:0\n", 22);
	newfile.write("levelsave_track_7_4:0\n", 22);
	newfile.write("levelsave_track_0_5:0\n", 22);
	newfile.write("levelsave_track_1_5:0\n", 22);
	newfile.write("levelsave_track_2_5:0\n", 22);
	newfile.write("levelsave_track_3_5:0\n", 22);
	newfile.write("levelsave_track_4_5:0\n", 22);
	newfile.write("levelsave_track_5_5:0\n", 22);
	newfile.write("levelsave_track_6_5:0\n", 22);
	newfile.write("levelsave_track_7_5:0\n", 22);
	newfile.write("levelsave_track_0_6:0\n", 22);
	newfile.write("levelsave_track_1_6:0\n", 22);
	newfile.write("levelsave_track_2_6:0\n", 22);
	newfile.write("levelsave_track_3_6:0\n", 22);
	newfile.write("levelsave_track_4_6:0\n", 22);
	newfile.write("levelsave_track_5_6:0\n", 22);
	newfile.write("levelsave_track_6_6:0\n", 22);
	newfile.write("levelsave_track_7_6:0\n", 22);
	newfile.write("levelsave_track_0_7:0\n", 22);
	newfile.write("levelsave_track_1_7:0\n", 22);
	newfile.write("levelsave_track_2_7:0\n", 22);
	newfile.write("levelsave_track_3_7:0\n", 22);
	newfile.write("levelsave_track_4_7:0\n", 22);
	newfile.write("levelsave_track_5_7:0\n", 22);
	newfile.write("levelsave_track_6_7:0\n", 22);
	newfile.write("levelsave_track_7_7:0\n", 22);
	newfile.write("levelsave_track_0_8:0\n", 22);
	newfile.write("levelsave_track_1_8:0\n", 22);
	newfile.write("levelsave_track_2_8:0\n", 22);
	newfile.write("levelsave_track_3_8:0\n", 22);
	newfile.write("levelsave_track_4_8:0\n", 22);
	newfile.write("levelsave_track_5_8:0\n", 22);
	newfile.write("levelsave_track_6_8:0\n", 22);
	newfile.write("levelsave_track_7_8:0\n", 22);
	newfile.write("levelsave_track_0_9:0\n", 22);
	newfile.write("levelsave_track_1_9:0\n", 22);
	newfile.write("levelsave_track_2_9:0\n", 22);
	newfile.write("levelsave_track_3_9:0\n", 22);
	newfile.write("levelsave_track_4_9:0\n", 22);
	newfile.write("levelsave_track_5_9:0\n", 22);
	newfile.write("levelsave_track_6_9:0\n", 22);
	newfile.write("levelsave_track_7_9:0\n", 22);
	newfile.write("levelsave_track_0_10:0\n", 23);
	newfile.write("levelsave_track_1_10:0\n", 23);
	newfile.write("levelsave_track_2_10:0\n", 23);
	newfile.write("levelsave_track_3_10:0\n", 23);
	newfile.write("levelsave_track_4_10:0\n", 23);
	newfile.write("levelsave_track_5_10:0\n", 23);
	newfile.write("levelsave_track_6_10:0\n", 23);
	newfile.write("levelsave_track_7_10:0\n", 23);
	newfile.write("levelsave_track_0_11:0\n", 23);
	newfile.write("levelsave_track_1_11:0\n", 23);
	newfile.write("levelsave_track_2_11:0\n", 23);
	newfile.write("levelsave_track_3_11:0\n", 23);
	newfile.write("levelsave_track_4_11:0\n", 23);
	newfile.write("levelsave_track_5_11:0\n", 23);
	newfile.write("levelsave_track_6_11:0\n", 23);
	newfile.write("levelsave_track_7_11:0\n", 23);

	newfile.write("levelsave_powerup1:gfx/blacksmall.bmp\n", 38);
	newfile.write("levelsave_powerup2:gfx/blacksmall.bmp\n", 38);
	newfile.write("levelsave_powerup3:gfx/blacksmall.bmp\n", 38);
	newfile.write("levelsave_powerup4:gfx/blacksmall.bmp\n", 38);
	newfile.write("levelsave_powerup5:gfx/blacksmall.bmp\n", 38);
	newfile.write("levelsave_powerup6:gfx/blacksmall.bmp\n", 38);
	newfile.write("levelsave_cartbody:0\n", 21);
	newfile.write("levelsave_cartwheel:0\n", 22);
	newfile.write("levelsave_cartweight:0\n", 23);

	newfile.write("dont:use\n", 9);

	// close the file
	newfile.seekp(0, ios::beg);
	newfile.clear();

	if (newfile.is_open()) // its still open
		newfile.close();
}

bool Cfilereader::Exists()
{
	FILE *cfile;

	cfile = fopen(configfilename.c_str(), "r");
	if (cfile == NULL) return false;

	fclose(cfile);
	return true;
}
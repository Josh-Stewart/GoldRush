////////////////////////////////////
// HighScore system
// Author: Leigh Shayler
// Date :12/8/2002
/////////////////////////////////
#ifndef CHIGHSCORE
#define CHIGHSCORE
#include <iostream>
#include <string>
#include "Cfilereader.h"

using namespace std;

class CHighScores
{
public:

	int AddScore(string Name, int Score);//Add a score to memory+returns position added

	int CheckScore(int Score); //checks if the score should enter into highscores

	int ReadScores(); //Read from file

	int WriteScores(); //Write to file

	char* DisplayScores(int i); //returns a string containing name and score

	int Scores[10];
	string Names[10];
	string TempString;
private:


	Cfilereader HSreader;
};
#endif
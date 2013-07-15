#include "CHighScores.h"


int CHighScores::AddScore(string Name, int Score)
{
	for(int i = 0;i<10;i++)
	{
		if(Score > Scores[i])
		{
			//shuffle down array
			for(int j=9;j>i;j--)
			{
				Scores[j] = Scores[j-1];
				Names[j] = Names[j-1];
			}
		//add 
		Scores[i] = Score;
		Names[i].assign(Name);
		return i;//position score added
		}
	}
	return -1;//score not added
}

int CHighScores::CheckScore(int Score)
{
	for(int i = 0;i<10;i++)
	{
		if(Score > Scores[i])
		{
			return 1;//score addable
		}
	}
	return 0;//score not addable
}

int CHighScores::ReadScores()
{
	char Temp[10] = {' '};
	for(int i=0;i<10;i++)
	{
		TempString.assign("name");
		itoa(i,Temp,10);
		TempString.append(Temp);
		//cout << TempString << endl;
		Names[i] = HSreader.LoadFromConfig(TempString);

		TempString.assign("score");
		TempString.append(Temp);
		TempString = HSreader.LoadFromConfig(TempString);

		Scores[i] = atoi(TempString.c_str());
		
		
	}
	return 0;
}


CHighScores::WriteScores()
{
	char Temp[1] = {' '};
	for(int i=0;i<10;i++)
	{
		Temp[1] = ' ';
		TempString.assign("name");
		itoa(i,Temp,10);
		TempString.append(Temp);
		
		HSreader.SaveToConfig(TempString,Names[i]);

		TempString.assign("score");
		TempString.append(Temp);
		itoa(Scores[i],Temp,10);

		HSreader.SaveToConfig(TempString,Temp);

	}
	return 0;
}

char* CHighScores::DisplayScores(int i)
{

	return NULL;
}
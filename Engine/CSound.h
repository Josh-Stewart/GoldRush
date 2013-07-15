///////////////////////////////////
// Sound System Header
// Author : Leigh Shayler
// Date : 8/8/2002
////////////////////////////////////////////////

#ifndef SOUNDSYS
#define SOUNDSYS

#include <stdio.h>
#include <conio.h>
#include <string>
#include "fmod.h"
#include "fmod_errors.h"

#include <iostream>

class CSound
{
private:
	bool INITIALISED;
	int SOUND_VOLUME;
	int MUSIC_VOLUME;
	int TEMP_VOLUME; //Used for music FADE effects
	FSOUND_STREAM *CurrentSong;
	FSOUND_SAMPLE *CurrentSound;
	int pan;
	int freq;
	char input;
	char input1;
	char *songname;

public:
	CSound();
	int Initialise(int rate,int channels, int svol, int mvol);
	int Startmusic(char *song);
	int Stopmusic();
	int Playsound(int soundnum);
	int Loopsound(int soundnum);
	int Stopsound(int channum);
	int SetMusicVolume(int vol);
	int SetSoundVolume(int vol);
	int GetMusicVolume();
	int GetSoundVolume();
	int Setpan(int chan, int pan);
	int SetFreq(int channel, int NewFreq);

	void SHUTDOWN();
};
#endif

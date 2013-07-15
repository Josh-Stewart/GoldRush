#include "Csound.h"

CSound::CSound()
{

}

int CSound::Initialise(int rate,int channels,int svol,int mvol)
{
	if((channels > 16) || (channels < 0))
	{
		return 1;
	}
	FSOUND_SetOutput(FSOUND_OUTPUT_DSOUND);
	FSOUND_Init(rate,channels,FSOUND_INIT_USEDEFAULTMIDISYNTH);

	songname = "Empty";


	SetSoundVolume(svol);
	SetMusicVolume(mvol);

	CurrentSong = NULL;
	CurrentSound = 0;
	
	pan = 127;
	freq = 11250;

	FSOUND_Sample_Load(0,"sfx/click.wav",FSOUND_LOOP_OFF,0);
	FSOUND_Sample_Load(1,"sfx/dong.wav",FSOUND_LOOP_OFF,0);

	FSOUND_Sample_Load(3,"sfx/computer.wav",FSOUND_LOOP_OFF,0);
	FSOUND_Sample_Load(4,"sfx/scitech.wav",FSOUND_LOOP_OFF,0);
	FSOUND_Sample_Load(5,"sfx/speed.wav",FSOUND_LOOP_OFF,0);
	FSOUND_Sample_Load(6,"sfx/placetrack.wav",FSOUND_LOOP_OFF,0);
	FSOUND_Sample_Load(7,"sfx/removetrack.wav",FSOUND_LOOP_OFF,0);

	FSOUND_Sample_Load(8, "sfx/click3.wav",FSOUND_LOOP_OFF,0);
	FSOUND_Sample_Load(9, "sfx/pickuptrack.wav",FSOUND_LOOP_OFF,0);

	FSOUND_Sample_Load(10, "sfx/cartexplode.wav",FSOUND_LOOP_OFF,0);
	FSOUND_Sample_Load(11, "sfx/cart-good.wav",FSOUND_LOOP_OFF,0);
	FSOUND_Sample_Load(12, "sfx/pickup.wav",FSOUND_LOOP_OFF,0);

	FSOUND_Sample_Load(13, "sfx/crusher.wav",FSOUND_LOOP_OFF, 0);

	return 0;

}
///////////////////////////////////////////////////////////////////////////////
//StartMusic will play a song. The song must be past as a pointer through *song
//there is a limit of one song playing at once.
// Format for songs is of  *.MID
////////////////////////////////////////////////////////////////////////////////

int CSound::Startmusic(char *song)
{

	songname = song;
	CurrentSong = FSOUND_Stream_OpenFile(song,FSOUND_LOOP_NORMAL,0);

	
	//if (!CurrentSong)
	//{
		//printf("Error Loading!\n");
		//printf("%s\n", FMOD_ErrorString(FSOUND_GetError()));
	//	return 1;
	//}
	FSOUND_Stream_Play(0,CurrentSong);
	SetMusicVolume(MUSIC_VOLUME); // be adam: stream play seems to reset the music volume
//	ret = FMUSIC_PlaySong(CurrentSong);
	
//	if (!ret)
	{
		//printf("Error Playing!\n");
		//printf("%s\n", FMOD_ErrorString(FSOUND_GetError()));
//		return 2;
		//printf("Press Any Key.\n");
	}
//	getchar();
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//stopmusic will stop the currently playing song pointed to by CurrentSong. 
///////////////////////////////////////////////////////////////////////////////
int CSound::Stopmusic()
{

	FSOUND_Stream_Stop(CurrentSong);
	FSOUND_Stream_Close(CurrentSong);
	if (CurrentSong != NULL)
		CurrentSong = NULL;
	return 0;
}


//////////////////////////////////////////////////////////////////////////////////
//playsound plays a sound from the sound index. The sounds can only be played after
// they have been loaded into the sound index. returns the channel its played on
//////////////////////////////////////////////////////////////////////////////////
int CSound::Playsound(int soundnum)
{

	printf("Playing Sound\n");
	for(int i =1;i< int(FSOUND_GetMaxChannels);i++)
	{
		if(!FSOUND_IsPlaying(i))
		{
			FSOUND_PlaySound(i,FSOUND_Sample_Get(soundnum));
			return i;
		}
	}
	return 1;
}

//////////////////////////////////////////////////////////////////////////////////
//loopsound plays a sound from the sound index. The sounds can only be played after
// they have been loaded into the sound index. the sounds called here loop infinitely
//////////////////////////////////////////////////////////////////////////////////

int CSound::Loopsound(int soundnum)
{

	for(int i =1;i< int(FSOUND_GetMaxChannels);i++)
	{
		if(!FSOUND_IsPlaying(i))
		{
			FSOUND_PlaySound(i,FSOUND_Sample_Get(soundnum));
			FSOUND_SetLoopMode(i,FSOUND_LOOP_NORMAL);
			return i;
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////
//stopsound stops a sound in a given channel. 
//////////////////////////////////////////////////////////////////////////////////

int CSound::Stopsound(int channum)
{

	FSOUND_StopSound(channum);
	return 0;
}
/////////////////////////////////////
// sets music volume
////////////////////////////////////////
int CSound::SetMusicVolume(int vol)
{
	MUSIC_VOLUME = vol;
	FSOUND_SetVolume(0,MUSIC_VOLUME);
	// by adam- fixed by leigh: switch off music if its volume is 0, or start it if volume is > 0 and nothing is playing

	if (MUSIC_VOLUME == 0 && CurrentSong != NULL)
	{
		Stopmusic();
	}
	if (MUSIC_VOLUME > 0 && CurrentSong == NULL && songname != "Empty")
	{
		Startmusic(songname);
	}

	return vol;
}

/////////////////////////////////////////////
// sets sount volume
///////////////////////////////////////////
int CSound::SetSoundVolume(int vol)
{
	SOUND_VOLUME = vol;
	FSOUND_SetSFXMasterVolume(SOUND_VOLUME);
	SetMusicVolume(MUSIC_VOLUME);
	return vol;
};

/////////////////////////////////////
// gets music volume
////////////////////////////////////////
int CSound::GetMusicVolume()
{

	return MUSIC_VOLUME;
}

/////////////////////////////////////////////
// gets sount volume
///////////////////////////////////////////
int CSound::GetSoundVolume()
{
	

	return SOUND_VOLUME;
};
///////////////////////////
// Set Pan
/////////////////////////////
int CSound::Setpan(int chan, int pan)
{
	if(pan>255)
		pan = 255;

	if(pan<0)
		pan = 0;

	FSOUND_SetPan(chan, pan);
	return 0;
}

//////////////////////////////////////////
// Set Frequency
///////////////////////////////////////////
int CSound::SetFreq(int channel, int NewFreq)
{
	FSOUND_SetFrequency(channel,NewFreq);
	return NewFreq;
}
/////////////////////////////////////////////
// shuts down system
///////////////////////////////////////////
void CSound::SHUTDOWN()
{
	for(int i=1;i<16;i++)
	{
		Stopsound(i);
	}

	Stopmusic();
}
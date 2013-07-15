#include <stdio.h>
#include "fmod.h"
#include "fmod_errors.h"

//////////////////////////////////////////////////////////////////////////////
//Sample sound setup for the use with the Scitech Project Win32 program only
//Author: Leigh Shayler
// Date : 9/7/2002
//
// Modified 10/7/2002
// Added Panning and Frequencing shift support.

// NOTE: Pan and frequency are not update automatically and a SetPan and
//		 SetFrequency must be called to update looping sounds. Will write a
//		 refresh function which automatically updates everything from pointers
//		 provided at initialization.
//////////////////////////////////////////////////////////////////////////////


bool INITIALISED = false;
int SOUND_VOLUME = 190;
int MUSIC_VOLUME = 190;
int TEMP_VOLUME = 0; //Used for music FADE effects
FMUSIC_MODULE *CurrentSong = NULL;
FSOUND_SAMPLE *CurrentSound = 0;
int pan = 127;
int freq = 11250;
char input;
char input1;

/////////////////////////////////////////////////////////////////////////////
//Initialise sets the appropriate output,playback rate and number of channels
//for the sound system to use will exit and return false if initialisation fails
//
// Default and currently only sound output is DirectSound..
//Max Channels is 16.
//////////////////////////////////////////////////////////////////////////////

int initialise(int rate,int channels)
{
	printf("Initialising Sound System..........\n");
	if((channels > 16) || (channels < 0))
	{
		return 1;
	}
	FSOUND_SetOutput(FSOUND_OUTPUT_DSOUND);
	FSOUND_Init(rate,channels,FSOUND_INIT_USEDEFAULTMIDISYNTH);

	return 0;

}
///////////////////////////////////////////////////////////////////////////////
//StartMusic will play a song. The song must be past as a pointer through *song
//there is a limit of one song playing at once.
// Format for songs is of  *.MID
////////////////////////////////////////////////////////////////////////////////

int startmusic(char *song)
{
	int ret;
	
	printf("Music is ON\n");
	CurrentSong = FMUSIC_LoadSong(song);

	if (!CurrentSong)
	{
		printf("Error Loading!\n");
		printf("%s\n", FMOD_ErrorString(FSOUND_GetError()));
		return 1;
	}

	ret = FMUSIC_PlaySong(CurrentSong);
	
	if (!ret)
	{
		printf("Error Playing!\n");
		printf("%s\n", FMOD_ErrorString(FSOUND_GetError()));
		return 1;
		printf("Press Any Key.\n");
	}


	getchar();
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//stopmusic will stop the currently playing song pointed to by CurrentSong. 
///////////////////////////////////////////////////////////////////////////////
int stopmusic()
{

	FMUSIC_StopSong(CurrentSong);
	FMUSIC_FreeSong(CurrentSong);
	
	return 0;
}

////////////////////////////////////////////////////////////////////////////////
// loadsounds will loads all of the sounds effects into memory for quick use.
//The first parameter in the Sample_Load function denotes the index position of the
//sound effect, accessing sounds is done using this index and the get_sound function
//////////////////////////////////////////////////////////////////////////////////
int loadsounds()
{
	FSOUND_Sample_Load(0,"cart3+rail.wav",FSOUND_LOOP_OFF,0);
	FSOUND_Sample_Load(1,"dong.wav",FSOUND_LOOP_OFF,0);
	FSOUND_Sample_Load(2,"placetrack.wav",FSOUND_LOOP_OFF,0);
	// Load the rest of sounds into sample index here.

	return 0;

}

//////////////////////////////////////////////////////////////////////////////////
//playsound plays a sound from the sound index. The sounds can only be played after
// they have been loaded into the sound index.
//////////////////////////////////////////////////////////////////////////////////
int playsound(int soundnum)
{
	printf("Playing Sound\n");
	FSOUND_PlaySound(soundnum,FSOUND_Sample_Get(soundnum));
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////
//loopsound plays a sound from the sound index. The sounds can only be played after
// they have been loaded into the sound index. the sounds called here loop infinitely
//////////////////////////////////////////////////////////////////////////////////

int loopsound(int soundnum)
{
	printf("Playing Sound\n");
	FSOUND_PlaySound(soundnum,FSOUND_Sample_Get(soundnum));
	FSOUND_SetLoopMode(soundnum,FSOUND_LOOP_NORMAL);
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////
//stopsound stops a sound in a given channel. 
//////////////////////////////////////////////////////////////////////////////////

int stopsound(int channum)
{

	FSOUND_StopSound(channum);
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////
//Test Function to demonstrate the abilities of the sound system
///////////////////////////////////////////////////////////////////////////////////
int main()
{

	if (FSOUND_GetVersion() < FMOD_VERSION)
	{
		printf("Error : You are using the wrong DLL version!  You should be using FMOD %.02f\n", FMOD_VERSION);
		return 1;
	}

	initialise(44100,16);
	loadsounds();
//	startmusic("Breathe.mid");

//	input = getch();
	
//	FSOUND_SetPan(2,0);

//	playsound(0);

	for(int i = 0;i = 100;i++)
	{
		printf("Sound System Demo\n\n");
		printf("Press the Number Below Corresponding to Your Choice :\n\n");
		printf("1. Start Music\n");
		printf("2. Stop Music\n");
		printf("3. Play a Sound \n");
		printf("4. Loop a Sound\n");
		printf("5. Stop a Sound\n");
		printf("6. Pan a Playing Sound\n");
		printf("7. Alter Frequency of a Playing Sound\n");

		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");

		input = getchar();
//////////////////////////////////////////////
//Startmusic Section of the menu
//////////////////////////////////////////////
		if(input == '1')
		{
			//startmusic("test.s3m");
			startmusic("123.mid");
		}
//////////////////////////////////////////////
//Stopmusic Section of the menu
//////////////////////////////////////////////
		if(input == '2')
		{
			stopmusic();
		}
//////////////////////////////////////////////
//Playsound Section of the menu
//////////////////////////////////////////////
		if(input == '3')
		{
			for(int j = 0;j<10;j++)
			{
				j = 0;
				printf("Sound System Demo\n\n");
				printf("Select a Sound To Play From The List Below\n\n");
				printf("1. Cart\n");
				printf("2. Dong\n");
				printf("3. Place Track\n");
				printf("4. Exit\n");

				printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

				input1 = getchar();
				if(input1 == '1')
				{
					playsound(0);
				}
				if(input1 == '2')
				{
					playsound(1);
				}
				if(input1 == '3')
				{
					playsound(2);
				}
				if(input1 == '4')
				{
					j = 10;
				}
			}
			
		}
//////////////////////////////////////////////
//END OF Playsound Section of the menu
//////////////////////////////////////////////
//////////////////////////////////////////////
//Loopsound Section of the menu
//////////////////////////////////////////////
		if(input == '4')
		{
			for(int j = 0;j<10;j++)
			{
				j = 0;
				printf("Sound System Demo\n\n");
				printf("Select a Sound To Loop From The List Below\n\n");
				printf("1. Cart\n");
				printf("2. Dong\n");
				printf("3. Place Track\n");
				printf("4. Exit\n");

				printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

				input1 = getchar();
				if(input1 == '1')
				{
					loopsound(0);
				}
				if(input1 == '2')
				{
					loopsound(1);
				}
				if(input1 == '3')
				{
					loopsound(2);
				}
				if(input1 == '4')
				{
					j = 10;
				}
			}
		}
//////////////////////////////////////////////
//END OF Loopsound Section of the menu
//////////////////////////////////////////////
//////////////////////////////////////////////
//Stopsound Section of the menu
//////////////////////////////////////////////
		if(input == '5')
		{
					for(int j = 0;j<10;j++)
			{
				j = 0;
				printf("Sound System Demo\n\n");
				printf("Select a Sound To Stop Playing From The List Below\n\n");
				printf("1. Cart\n");
				printf("2. Dong\n");
				printf("3. Place Track\n");
				printf("4. Exit\n");

				printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

				input1 = getchar();
				if(input1 == '1')
				{
					stopsound(0);
				}
				if(input1 == '2')
				{
					stopsound(1);
				}
				if(input1 == '3')
				{
					stopsound(2);
				}
				if(input1 == '4')
				{
					j = 10;
				}
			}
		}
//////////////////////////////////////////////
//END OF stopsound  Section of the menu
//////////////////////////////////////////////
//////////////////////////////////////////////
//Pan Section of the menu
//////////////////////////////////////////////
		if(input == '6')
		{
			printf("Sound System Demo\n\n");
			printf("Select a Sound To Pan From The List Below\n\n");
			printf("1. Cart\n");


			printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

			input = getchar();
			if((input == '1') || (input == '2') || (input == '3'))
			{
			for(int i = 0;i<10;i++)
			{
				
				i = 0;

				input1 = getchar();
				printf("Press '+' or '-' to change the Pan.\n");
				printf("Press '0' to Exit.\n\n");
				printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
				if((input1 == '-') || (input1 == '=') || (input1 == '0'))
				{
					if(input1 == '-')
					{
						pan = pan - 10;
						if(pan<0)
						{
							pan = 0;
						}
						FSOUND_SetPan(0,pan);
					}
					if(input1 == '=')
					{
						pan = pan + 10;
						if(pan>255)
						{
							pan = 255;
						}
						FSOUND_SetPan(0,pan);
					}
					if(input1 == '0')
					{
						i = 12;
					}
				}
			}
			}
			input = 0;
		}
//////////////////////////////////////////////
//END OF Pan Section of the menu
//////////////////////////////////////////////
//////////////////////////////////////////////
//Frequency Section of the menu
//////////////////////////////////////////////
		if(input == '7')
		{
			printf("Sound System Demo\n\n");
			printf("Select a Sound To Frequency Alter From The List Below\n\n");
			printf("1. Cart\n");


			printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

			input = getchar();
			if((input == '1') || (input == '2') || (input == '3'))
			{
			for(int i = 0;i<10;i++)
			{
				
				i = 0;

				input1 = getchar();
				printf("Press '+' or '-' to change the Frequency.\n");
				printf("Press '0' to Exit.\n\n");
				printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
				if((input1 == '-') || (input1 == '=') || (input1 == '0'))
				{
					if(input1 == '-')
					{
						freq = freq - 200;
						if(freq<1000)
						{
							freq = 1000;
						}
						FSOUND_SetFrequency(0,freq);
					}
					if(input1 == '=')
					{
						freq = freq + 200;
						if(pan>255)
						{
							freq = 18000;
						}
						FSOUND_SetFrequency(0,freq);
					}
					if(input1 == '0')
					{
						i = 12;
					}
				}
			}
			}
			input = 0;
		}
//////////////////////////////////////////////
//END OF Frequency Section of the menu
//////////////////////////////////////////////
			
		i = 1;
	}

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////
//////////////////////END OF CODE//////////////////////////////////////////////////////
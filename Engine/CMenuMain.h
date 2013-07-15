//////////////////////////////////////////
// Main Menu class
// Author : Leigh Shayler
// 7/8/2002
//
// NOTE: Z values for Main Menu are 10-12
///////////////////////////////////////////
#ifndef CMENUMAIN
#define CMENUMAIN

#include "stdlib.h"
#include "globals.h"
#include "ddutil.h"
#include "Game_Main.h"
#include "Game_Shutdown.h"
#include "CLevelData.h"


class CMenuMain
{
private:
	RLiterator TI;//temp iterator
	RLiterator CurrentTrack; //for grabtrack()
	int CurrentTrackType; // adam: to keep track of what type of track we're playing with
	int MenuState;
	int TrackMenuState;

	int StartSpeed;
	int SelectedPowerup;
	int TempScore;


	int Snap_x;
	int Snap_y;

	int CartSoundHandle; // required to be able to stop loopin cart sound
	int FrameCounter; //to count frames for the cart explosion

	bool GameOn; //is there currently a game in progress?
	bool EntryMode; //for entering new highscores

public:
	int WheelType;
	int BodyShape;
	int WeightReduction; //all three of these affect the max speed of the cart.

	int Score;
	char mytemp[6];
	string TempString;
	string Powerups[6];
////////////////////////////////////////
// Constructor
////////////////////////////////////////
	CMenuMain();
//////////////////////////////////////
//MainMenu fucntions
/////////////////////////////////////
	int MainOn(); //turns menu on
	int MainOff(); // turns meu off
//////////////////////////////////////
//lowergamebar fucntions
/////////////////////////////////////
	int LowerBarOn();
	int AdjustSpeedSlider();
	int LowerBarOff();

//////////////////////////////////////
//Load save menu
////////////////////////////////
	int LoadSaveOn();
	int LoadSaveOff();
//////////////////////////////////////
//OptionsMenu fucntions
/////////////////////////////////////
	int OptionsOn();

	int AdjustSoundSlider();
	int TestSound();
	int AdjustMusicSlider();

	int OptionsOff();
//////////////////////////////////////
//HighScoreMenu fucntions
/////////////////////////////////////
	int HighScoresOn(bool EntryMode);
	int HighScoresOff();
//////////////////////////////////////
//newtrackpiece  fucntions
/////////////////////////////////////
	int NewTrackOn();
	int NewTrackOff();
//////////////////////////////////////
//powerup fucntions
/////////////////////////////////////
	int PowerupOn();
	int PowerupOff();
//////////////////////////////////////
//next level fucntions
//////////////////////////////////////
	int NextLevelOn(int Level);
	int NextLevelOff();
//////////////////////////////////////
//trackmenu fucntions
//////////////////////////////////////
	void TrackMenu1On();
	void TrackMenu2On();
	void TrackMenu3On();

	void TrackMenusOff();
///////////////////////////////////////////////////////////////
//other fucntions
/////////////////////////////////////
	void DoExit();

	int CartExplosion(int x, int y); //state 8

	int RunIntro();
	int RunOutro();
	int LevelSuccess();
	int LevelFailure();
	int GetState();

	void GrabTrack(RLiterator Track);
	void DiscardTrack();
	void MenuCollider();
///////////////////////////////////////////////////////////
};

#endif
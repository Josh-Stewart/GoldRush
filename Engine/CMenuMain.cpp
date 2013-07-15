/////////////////////////////////////////
// Main Menu Class
// Author : Leigh Shayler
// Date : 7/8/2002
////////////////////////////////////////////////

#include "CMenuMain.h"
#include "Text.h"

CMenuMain::CMenuMain()
{
	MenuState = 0;
	GameOn = false;
	TrackMenuState = 0;
	CurrentTrack = NULL;
	SelectedPowerup = 1;

	StartSpeed = 20;
	Score = 0;
	TempScore = 0;

	WheelType =0;
	BodyShape =0;
	WeightReduction =0; //all three of these affect the max speed of the cart.

	for(int j=0; j<6;j++)
	{
		Powerups[j] = "gfx/blacksmall.bmp";
	}
						

}


int CMenuMain::GetState()
{
	return MenuState;
}

CMenuMain::MainOn()
{
	if(MenuState != 1)
	{	
		if(GameOn == false)
		{
		OrderedInsert(new Popup("gfx/mainBG3.bmp","Menu_Main_BG1", 0, 0, 10, 800,600,1,0));

		OrderedInsert(new Popup("gfx/newgamebtn.bmp","Menu_Main_B1", 20, 175, 10, 600,50,2,0));
		OrderedInsert(new Popup("gfx/loadsavebtn.bmp","Menu_Main_B2", 20, 235, 10, 600,50,2,0));
		OrderedInsert(new Popup("gfx/optionsbtn.bmp","Menu_Main_B3", 20, 295, 10, 600,50,2,0));
		OrderedInsert(new Popup("gfx/highscoresbtn.bmp","Menu_Main_B4", 20, 355, 10, 600,50,2,0));
		OrderedInsert(new Popup("gfx/bigexitbtn.bmp","Menu_Main_B5", 20, 415, 10, 600,50,2,0));
		
		

		}
		else
		{
		OrderedInsert(new Popup("gfx/mainBG3.bmp","Menu_Main_BG1", 0, 0, 10, 800,600,1,0));

		//resume game btn
		OrderedInsert(new Popup("gfx/resumegamebtn.bmp","Menu_Main_B0", 20, 168, 10, 600,50,2,0));

		OrderedInsert(new Popup("gfx/newgamebtn.bmp","Menu_Main_B1", 20, 226, 10, 600,50,2,0));
		OrderedInsert(new Popup("gfx/loadsavebtn.bmp","Menu_Main_B2", 20, 284, 10, 600,50,2,0));
		OrderedInsert(new Popup("gfx/optionsbtn.bmp","Menu_Main_B3", 20, 342, 10, 600,50,2,0));
		OrderedInsert(new Popup("gfx/highscoresbtn.bmp","Menu_Main_B4", 20, 400, 10, 600,50,2,0));
		OrderedInsert(new Popup("gfx/bigexitbtn.bmp","Menu_Main_B5", 20, 458, 10, 600,50,2,0));
		}
		//////version information in main menu (lower right hand corner)////////
		OrderedInsert(new Text(12,"Menu_Main_T1","Zero41 Interactive. V 1.5",590,580,10,200,80,false));
		///////end of version control


		MenuState = 1;
		
		
	}
	return MenuState;
	
}

int CMenuMain::MainOff()
{
	if(MenuState == 1)
	{
		RemoveElementsMatching("Menu_Main");
	}
	return MenuState;
}



int CMenuMain::OptionsOn()
{
	if(MenuState != 2)
	{
		//background and titlebar
//		OrderedInsert(new Popup("gfx/mainBG3.bmp","Menu_Options_BG1", 0, 0, 10, 800,600,1,0));

		OrderedInsert(new Popup("gfx/optBG.bmp","Menu_Options_BG", 200, 100, 10, 400,400,1,0));
//		OrderedInsert(new Popup("gfx/optionstitle.bmp","Menu_Options_TT", 203, 103, 11, 394,40,1,0));

		//slider1
		OrderedInsert(new Popup("gfx/sliderbase.bmp","Menu_Options_SB1", 225, 224, 11, 350,4,1,0));
		OrderedInsert(new Popup("gfx/slider.bmp","Menu_Options_SL1", (SoundSystem.GetSoundVolume()+225), 210, 12, 16,32,1,0));
		//test button
		OrderedInsert(new Popup("gfx/testbtn.bmp","Menu_Options_B1", 368, 290, 11, 128,32,2,0));
		//slider2
		OrderedInsert(new Popup("gfx/sliderbase.bmp","Menu_Options_SB2", 225, 400, 11, 350,4,1,0));
		OrderedInsert(new Popup("gfx/slider.bmp","Menu_Options_SL2", (SoundSystem.GetMusicVolume()+225), 386, 12, 16,32,1,0));
		//exit button
		OrderedInsert(new Popup("gfx/exitbtn.bmp","Menu_Options_B2", 530, 463, 11, 128,32,2,0));

		MenuState = 2;
		return 2;
	}
	return MenuState;
}

int CMenuMain::AdjustSoundSlider()
{

	if((mouse_x >225) && (mouse_x < 575))
	{
		//must replace with findbyname
		(*(ReturnElementMatching("Menu_Options_SL1")))->MoveAbs((mouse_x-8),(210));
		//
		SoundSystem.SetSoundVolume((mouse_x-233));			
	}
		
	return 0;
}
int CMenuMain::TestSound()
{
	SoundSystem.Playsound(1);
	return 0;
}

int CMenuMain::AdjustMusicSlider()
{
	if((mouse_x >225) && (mouse_x < 575))
	{
		(*(ReturnElementMatching("Menu_Options_SL2")))->MoveAbs((mouse_x-8),(386));		
		SoundSystem.SetMusicVolume((mouse_x-233));			
	}
	return 0;
}

int CMenuMain::OptionsOff()
{
	if(MenuState == 2)
	{
		RemoveElementsMatching("Menu_Options");
		MenuState = 0;
	}
	return MenuState;
}

int CMenuMain::LowerBarOn()
{
	if(MenuState != 10)
	{
		LevelSystem.DisplayLevel(); // display current level

		//OrderedInsert(new Popup("gfx/background1.bmp","Menu_Lower_BG", 0, 0, 0, 800,512,1,0));
		OrderedInsert(new Popup("gfx/lowerbar4.bmp","Menu_Lower_Bar", 0, 512, 1, 800,88,1,0));
		OrderedInsert(new Popup("gfx/menubtn.bmp","Menu_Lower_B1", 12, 524, 2, 64,64,2,0));
		OrderedInsert(new Popup("gfx/mbutton.bmp","Menu_Lower_B2", 56, 524, 2, 256,64,2,0));

		OrderedInsert(new Popup("gfx/initspeed2.bmp","Menu_Lower_SP", 200, 526, 0, 160,60,1,0));

		OrderedInsert(new Popup(Powerups[0].c_str(),"Menu_Lower_P1", 417, 526, 2, 24,24,1,0));
		OrderedInsert(new Popup(Powerups[1].c_str(),"Menu_Lower_P2", 452, 526, 2, 24,24,1,0));
		OrderedInsert(new Popup(Powerups[2].c_str(),"Menu_Lower_P3", 487, 526, 2, 24,24,1,0));
		OrderedInsert(new Popup(Powerups[3].c_str(),"Menu_Lower_P4", 417, 561, 2, 24,24,1,0));
		OrderedInsert(new Popup(Powerups[4].c_str(),"Menu_Lower_P5", 452, 561, 2, 24,24,1,0));
		OrderedInsert(new Popup(Powerups[5].c_str(),"Menu_Lower_P6", 487, 561, 2, 24,24,1,0));
		
		OrderedInsert(new Popup("gfx/tm1.bmp","Menu_Lower_B3", 572, 524, 2, 64,64,1,0));
		OrderedInsert(new Popup("gfx/tm2.bmp","Menu_Lower_B4", 648, 524, 2, 64,64,1,0));
//		OrderedInsert(new Popup("gfx/tm3.bmp","Menu_Lower_I1", 724, 524, 2, 64,64,1,0));
		GameOn = true;
		MenuState = 10;
	}
	return MenuState;
}

int CMenuMain::AdjustSpeedSlider()
{
	if((mouse_x >195) && (mouse_x < 355))
	{
		(*(ReturnElementMatching("Menu_Lower_SP")))->MoveAbs((mouse_x-155),(526));		
		StartSpeed = (int)(((mouse_x-155)/8)+1);
	}
	return 0;
}

int CMenuMain::LowerBarOff()
{
	if(MenuState == 10)
	{
		LevelSystem.HideLevel(); // remove current level, but leave it in memory
		RemoveElementsMatching("Menu_Lower");
		MenuState = 0;
	}
	return MenuState;
}

int CMenuMain::CartExplosion(int x, int y)
{
	MenuState = 8;
	RECT tempRECT;
	tempRECT.bottom = 1;
	tempRECT.left = 0;
	tempRECT.right = 1;
	tempRECT.top = 0;

	TheCart->CurrentStatus = RegularD;
	TheCart->SetSpeed(8);
	FrameCounter = 0;
	return 0;
}

int CMenuMain::RunIntro()
{

	int tempint;
	OrderedInsert(new Popup("gfx/speed.bmp","Menu_Intro", 0, 0, 101, 800,600,1,0));
	RenderForce();
	tempint = SoundSystem.Playsound(5);
	SoundSystem.Setpan(tempint, 255);
	for(int i = 0;i<70;i++)
	{

		Sleep(100);
		UpdateInput();
		SoundSystem.Setpan(tempint, (255 - (i*4)) );
		if(mouse_1)
		{
			SoundSystem.Stopsound(tempint);
			RemoveElementsMatching("Menu_Intro");
			SoundSystem.Startmusic("music/song1.ogg");
			return 1;
		}
	}
	RemoveElementsMatching("Menu_Intro");

	OrderedInsert(new Popup("gfx/title3.bmp","Menu_Intro", 0, 0, 101, 800,600,1,0));
	RenderForce();
	Sleep(500);
	tempint = SoundSystem.Playsound(3);
	for(i = 0;i<30;i++)
	{

		Sleep(100);
		UpdateInput();
		if(mouse_1)
		{
			SoundSystem.Stopsound(tempint);
			RemoveElementsMatching("Menu_Intro");
			SoundSystem.Startmusic("music/song1.ogg");
			return 1;
		}
	}
	RemoveElementsMatching("Menu_Intro");
	SoundSystem.Startmusic("music/song1.ogg");

	return 0;
}

int CMenuMain::RunOutro()
{

	TempString = "      Thankyou for playing Gold Rush...                                ";
	TempString+= "                                                                       ";
	TempString+= "                                                                       ";
	TempString+= "                                                                       ";
	TempString+= "                             Credits                                   ";
	TempString+= "                                                                       ";
	TempString+= "This game was created for Scitech Discovery Centre, with assistance    ";
	TempString+= " from Edith Cowan University by (In Alphabetical Order):               ";
	TempString+= "                                                                       ";
	TempString+= "                            Jon Cahill                                 ";
	TempString+= "                                                                       ";
	TempString+= "                            Adam Payne                                 ";
	TempString+= "                                                                       ";
	TempString+= "                            Leigh Shayler                              ";
	TempString+= "                                                                       ";
	TempString+= "                            Josh Stewart                               ";
	TempString+= "                                                                       ";
	TempString+= "With additional music support from:                                    ";
	TempString+= "                                                                       ";
	TempString+= "             Esa Ruoho (Lackluster) / www.lackluster.info/             ";
	TempString+= "                                                                       ";
	TempString+= "                Nik from 4T Thieves / www.Khavi.Org                    ";
	TempString+= "                                                                       ";
	TempString+= "And thanks to:                                                         ";
	TempString+= "                                                                       ";
	TempString+= "              Michael Gosney from Scitech Discovery Centre.            ";
	SafeListRemove(MouseIterator);
	OrderedInsert(new Text(18,"Menu_Outro_T1",(char*)TempString.c_str(),0,590,11,570,600,false));
	RenderForce();
	Sleep(100);

	for(int i = 0;i<280;i++)
	{
		TI = ReturnElementMatching("Menu_Outro");
		if(TI != NULL)
		{
			(*TI)->Move(0,-2);
			RenderForce();
		}	
		Sleep(25);
		UpdateInput();
		if(mouse_1)
		{
			RemoveElementsMatching("Menu_Outro");
			DoExit();
			return 1;
		}
	}
	Sleep(3000);
	RemoveElementsMatching("Menu_Outro");

	
	DoExit();
	return 0;
}

int CMenuMain::HighScoresOn(bool Entry)
{
	
	if(MenuState != 3)
	{
		
		string tempstringo;
		EntryMode = Entry;
		HighScoreSystem.ReadScores();
		
		MainOn();
//		OrderedInsert(new Popup("gfx/mainBG3.bmp","Menu_High_BG1", 0, 0, 10, 800,600,1,0));
		OrderedInsert(new Popup("gfx/highscoretitle.bmp","Menu_High_TT", 202, (102), 11, 394,40,1,0));
		OrderedInsert(new Popup("gfx/menusmall.bmp","Menu_High_BG", 200, (100), 10, 400,400,1,0));

		//////code for entering name into highscores
		if(EntryMode == true)
		{
			keyboard_active = true;
			keyboard_buffer.erase();
			OrderedInsert(new Text(12,"Menu_High_TE1", "Please enter your name into the highscores.",225,150,11,450,80,false));
			OrderedInsert(new Text(28,"Menu_High_TE2", keyboard_buffer.c_str() ,225,170,11,450,80,false));
		}

		OrderedInsert(new Text(24,"Menu_High_T1", (char*)HighScoreSystem.Names[0].c_str(),225,213,11,150,80,false));
		OrderedInsert(new Text(24,"Menu_High_T2", (char*)HighScoreSystem.Names[1].c_str(),225,233,11,150,80,false));
		OrderedInsert(new Text(24,"Menu_High_T3", (char*)HighScoreSystem.Names[2].c_str(),225,253,11,150,80,false));
		OrderedInsert(new Text(24,"Menu_High_T4", (char*)HighScoreSystem.Names[3].c_str(),225,273,11,150,80,false));
		OrderedInsert(new Text(24,"Menu_High_T5", (char*)HighScoreSystem.Names[4].c_str(),225,293,11,150,80,false));
		OrderedInsert(new Text(24,"Menu_High_T6", (char*)HighScoreSystem.Names[5].c_str(),225,313,11,150,80,false));
		OrderedInsert(new Text(24,"Menu_High_T7", (char*)HighScoreSystem.Names[6].c_str(),225,333,11,150,80,false));
		OrderedInsert(new Text(24,"Menu_High_T8", (char*)HighScoreSystem.Names[7].c_str(),225,353,11,150,80,false));
		OrderedInsert(new Text(24,"Menu_High_T9", (char*)HighScoreSystem.Names[8].c_str(),225,373,11,150,80,false));
		OrderedInsert(new Text(24,"Menu_High_T10",(char*)HighScoreSystem.Names[9].c_str(),225,393,11,150,80,false));


		OrderedInsert(new Text(24,"Menu_High_S1", itoa(HighScoreSystem.Scores[0],mytemp,10),525,213,11,150,80,false));
		OrderedInsert(new Text(24,"Menu_High_S2", itoa(HighScoreSystem.Scores[1],mytemp,10),525,233,11,150,80,false));
		OrderedInsert(new Text(24,"Menu_High_S3", itoa(HighScoreSystem.Scores[2],mytemp,10),525,253,11,150,80,false));
		OrderedInsert(new Text(24,"Menu_High_S4", itoa(HighScoreSystem.Scores[3],mytemp,10),525,273,11,150,80,false));
		OrderedInsert(new Text(24,"Menu_High_S5", itoa(HighScoreSystem.Scores[4],mytemp,10),525,293,11,150,80,false));
		OrderedInsert(new Text(24,"Menu_High_S6", itoa(HighScoreSystem.Scores[5],mytemp,10),525,313,11,150,80,false));
		OrderedInsert(new Text(24,"Menu_High_S7", itoa(HighScoreSystem.Scores[6],mytemp,10),525,333,11,150,80,false));
		OrderedInsert(new Text(24,"Menu_High_S8", itoa(HighScoreSystem.Scores[7],mytemp,10),525,353,11,150,80,false));
		OrderedInsert(new Text(24,"Menu_High_S9", itoa(HighScoreSystem.Scores[8],mytemp,10),525,373,11,150,80,false));
		OrderedInsert(new Text(24,"Menu_High_S10",itoa(HighScoreSystem.Scores[9],mytemp,10),525,393,11,150,80,false));

		OrderedInsert(new Popup("gfx/OKbtn.bmp","Menu_High_OK", 530, (463), 11, 128,32,2,0));
		MenuState = 3;
	}
	return MenuState;
}

int CMenuMain::HighScoresOff()
{
	if(MenuState == 3)
	{
		RemoveElementsMatching("Menu_High");
		MenuState = 0;
	}
	return MenuState;
}

int CMenuMain::NewTrackOn()
{
	if(MenuState != 4)
	{
		//background and titlebar
		OrderedInsert(new Popup("gfx/mainBG3.bmp","Menu_Track_BG1", 0, 0, 10, 800,600,1,0));
		OrderedInsert(new Popup("gfx/menularge.bmp","Menu_Track_BG", 60, 50, 10, 680,400,1,0));
		OrderedInsert(new Popup("gfx/tracktitle.bmp","Menu_Track_TT", 63, 53, 11, 674,40,1,0));	
		//divider1
		OrderedInsert(new Popup("gfx/vdivide355.bmp","Menu_Track_V1", 398, 93, 11, 6,355,1,0));
		//OK button
		OrderedInsert(new Popup("gfx/OKbtn.bmp","Menu_Track_OK", 671, 413, 11, 128,32,2,0));
		OrderedInsert(new Popup("gfx/newtrack1.bmp","Menu_Track_I1", 62, 93, 11, 336,355,1,0));
		
		MenuState = 4;		
	}
	return MenuState;
}

int CMenuMain::NewTrackOff()
{
	if(MenuState == 4)
	{
		RemoveElementsMatching("Menu_Track");
		MenuState = 0;

	}
	return MenuState;
}

int CMenuMain::PowerupOn()
{
	if(MenuState != 5)
	{
		//background and titlebar
		OrderedInsert(new Popup("gfx/mainBG3.bmp","Menu_Powerup_BG1", 0, 0, 10, 800,600,1,0));
		OrderedInsert(new Popup("gfx/menularge.bmp","Menu_Powerup_BG", 60, 50, 10, 680,400,1,0));
		OrderedInsert(new Popup("gfx/poweruptitle.bmp","Menu_Powerup_TT", 63, 53, 11, 674,40,1,0));
	
		//dividers
		OrderedInsert(new Popup("gfx/vdivide310.bmp","Menu_Powerup_V1", 310, 93, 11, 6,310,1,0));
		OrderedInsert(new Popup("gfx/hdivide513.bmp","Menu_Powerup_H1", 62, 403, 11, 513,6,1,0));
		OrderedInsert(new Popup("gfx/vdivide355.bmp","Menu_Powerup_V2", 575, 93, 11, 6,355,1,0));

		OrderedInsert(new Popup((char*)LevelSystem.currentlevel.PowerupImg1.c_str(),"Menu_Powerup_I1", 62, 93, 11, 250,310,1,0));
		OrderedInsert(new Text(18,"Menu_Powerup_T1", (char*)LevelSystem.currentlevel.PowerupText1.c_str(),320,100,11,170,80,false));
		OrderedInsert(new Popup((char*)LevelSystem.currentlevel.PowerupImg1.c_str(),"Menu_Powerup_I2", 579, 93, 11, 159,118,1,0));
		if((TheCart->GetPowerup() ) > (int)(TheCart->GetMaxPowerup() / 2))
		{
			OrderedInsert(new Popup((char*)LevelSystem.currentlevel.PowerupImg2.c_str(),"Menu_Powerup_I3", 579, 211, 11, 159,118,1,0));
		}
		if(TheCart->GetPowerup() == TheCart->GetMaxPowerup())
		{
			OrderedInsert(new Popup((char*)LevelSystem.currentlevel.PowerupImg3.c_str(),"Menu_Powerup_I4", 579, 329, 11, 159,118,1,0));
		}
		//OK + replay buttons
		OrderedInsert(new Popup("gfx/replaybtn.bmp","Menu_Powerup_B1", 430, 413, 11, 128,32,2,0));
		OrderedInsert(new Popup("gfx/OKbtn.bmp","Menu_Powerup_B2", 500, 413, 11, 128,32,2,0));
		//score for level
		TempScore = ((TheCart->GetPowerup())*10);
		TempScore = (TempScore + Score) +1;
		

		itoa(TempScore,mytemp,10);
		TempString = "Score: ";
		TempString = TempString + mytemp;

		OrderedInsert(new Text(24,"Menu_Powerup_T2", (char*)TempString.c_str(),120,420,11,240,80,false));

		MenuState = 5;		
	}
	return MenuState;
}
int CMenuMain::PowerupOff()
{
	if(MenuState == 5)
	{

		RemoveElementsMatching("Menu_Powerup");
		MenuState = 0;
	}
	return SelectedPowerup;
}

int CMenuMain::NextLevelOn(int Level)
{
	if(MenuState != 6)
	{
		LevelSystem.LoadLevel(Level); // load level 1 data in as currentlevel
		OrderedInsert(new Popup("gfx/mainBG3.bmp","Menu_Level_BG1", 0, 0, 10, 800,600,1,0));
		OrderedInsert(new Popup("gfx/menularge.bmp","Menu_Level_BG", 60, 50, 10, 680,400,1,0));
		OrderedInsert(new Popup("gfx/leveltitle.bmp","Menu_Level_TT", 63, 53, 11, 674,40,1,0));
		//divider1
		OrderedInsert(new Popup("gfx/hdivide676.bmp","Menu_Level_H1", 62, 245, 11, 676,6,1,0));
		OrderedInsert(new Popup("gfx/vdivide676.bmp","Menu_Level_V1", 62, 403, 11, 676,6,1,0));
		//OK button
		OrderedInsert(new Popup("gfx/OKbtn.bmp","Menu_Level_B1", 671, 413, 11, 128,32,2,0));

		//material
		OrderedInsert(new Popup(LevelSystem.currentlevel.MaterialImg.c_str(),"Menu_Level_I1", 62, 93, 11, 153,153,1,0));

		OrderedInsert(new Text(20,"Menu_Level_T1", (char*)LevelSystem.currentlevel.MaterialText1.c_str(),225,99,11,300,80,false));
		

		//Obstacle, tempRECT is for creating animated track pieces.
		RECT tempRECT;
		tempRECT.bottom = 1;
		tempRECT.left = 0;
		tempRECT.right = 1;
		tempRECT.top = 0;

		if(LevelSystem.currentlevel.ObstacleAnimated == true)
		{
			OrderedInsert(new Popup("gfx/blueframe.bmp","Menu_Level_I2", 585, 251, 11, 153,153,1,0));
			OrderedInsert(new AnimatedTrack(LevelSystem.currentlevel.ObstacleImg.c_str(),"Menu_Level_I3",628,276,11,64,128,26,tempRECT));


		}
		else
		{
			OrderedInsert(new Popup(LevelSystem.currentlevel.ObstacleImg.c_str(),"Menu_Level_I3", 585,251,11, 153,153,1,0));
		}
		OrderedInsert(new Text(20,"Menu_Level_T2", (char*)LevelSystem.currentlevel.ObstacleText1.c_str(),72,276,11,300,80,false));


		MenuState = 6;
	}
	return MenuState;
}

int CMenuMain::NextLevelOff()
{
	if(MenuState == 6)
	{
		RemoveElementsMatching("Menu_Level");
		MenuState = 0;
	}
	return MenuState;
}

int CMenuMain::LoadSaveOn()
{
	if(MenuState != 7)
	{
		OrderedInsert(new Popup("gfx/loadbg.bmp","Menu_Load_BG", 200, 100, 10, 400,200,1,0));
		OrderedInsert(new Popup("gfx/loadtitle.bmp","Menu_Load_TT", 203, 103, 11, 394,40,1,0));

		OrderedInsert(new Text(14,"Menu_Load_T1", "Do you wish to save your game or load a previously saved game?",223,153,11,320,80,false));

		//OK button
		OrderedInsert(new Popup("gfx/loadbtn.bmp","Menu_Load_B1", 206, 265, 11, 128,32,2,0));
		OrderedInsert(new Popup("gfx/savebtn.bmp","Menu_Load_B2", 276, 265, 11, 128,32,2,0));
		OrderedInsert(new Popup("gfx/exitbtn.bmp","Menu_Load_B3", 530, 265, 11, 128,32,2,0));

		MenuState = 7;
		//return 2;
	}
	return MenuState;
}


int CMenuMain::LoadSaveOff()
{

	if(MenuState == 7)
	{
		RemoveElementsMatching("Menu_Load");
		MenuState = 0;
	}
	return MenuState;
}

void CMenuMain::DoExit()
{

	Game_Shutdown();
}

void CMenuMain::TrackMenu1On()
{
		DiscardTrack();
		OrderedInsert(new Popup("gfx/tm1c.bmp","Menu_Lower_TM1_BD", 572, 524, 4, 64,64,1,0));

		OrderedInsert(new Popup("gfx/TD_btn.bmp","Menu_Lower_TM1_B1", 572, 460, 4, 64,64,1,0));
		OrderedInsert(new Popup("gfx/TR_btn.bmp","Menu_Lower_TM1_B2", 572, 396, 4, 64,64,1,0));
		OrderedInsert(new Popup("gfx/TU_btn.bmp","Menu_Lower_TM1_B3", 572, 332, 4, 64,64,1,0));
		OrderedInsert(new Popup("gfx/TL_btn.bmp","Menu_Lower_TM1_B4", 572, 268, 4, 64,64,1,0));
		TrackMenuState = 1;

		SoundSystem.Playsound(8); // track menu up sound
}

void CMenuMain::TrackMenu2On()
{
		DiscardTrack();
		OrderedInsert(new Popup("gfx/tm2c.bmp","Menu_Lower_TM2_BD", 648, 524, 4, 64,64,1,0));

		OrderedInsert(new Popup("gfx/TC1_btn.bmp","Menu_Lower_TM2_B1", 648, 460, 4, 64,64,1,0));
		OrderedInsert(new Popup("gfx/TC2_btn.bmp","Menu_Lower_TM2_B2", 648, 396, 4, 64,64,1,0));
		OrderedInsert(new Popup("gfx/TC3_btn.bmp","Menu_Lower_TM2_B3", 648, 332, 4, 64,64,1,0));
		OrderedInsert(new Popup("gfx/TC4_btn.bmp","Menu_Lower_TM2_B4", 648, 268, 4, 64,64,1,0));
		TrackMenuState = 2;

		SoundSystem.Playsound(8); // track menu up sound
}

void CMenuMain::TrackMenu3On()
{
		DiscardTrack();
		OrderedInsert(new Popup("gfx/tm3c.bmp","Menu_Lower_TM3_BD", 724, 524, 4, 64,64,1,0));

		OrderedInsert(new Popup("gfx/trackhole.bmp","Menu_Lower_TM3_B1", 724, 460, 4, 64,64,1,0));
		OrderedInsert(new Popup("gfx/trackhole.bmp","Menu_Lower_TM3_B2", 724, 396, 4, 64,64,1,0));
		OrderedInsert(new Popup("gfx/trackhole.bmp","Menu_Lower_TM3_B3", 724, 332, 4, 64,64,1,0));
		OrderedInsert(new Popup("gfx/trackhole.bmp","Menu_Lower_TM3_B4", 724, 268, 4, 64,64,1,0));
		TrackMenuState = 3;

		SoundSystem.Playsound(8); // track menu up sound
}

void CMenuMain::TrackMenusOff()
{
	RemoveElementsMatching("Menu_Lower_TM");	
	TrackMenuState = 0;
}

void CMenuMain::GrabTrack(RLiterator Track)
{
	//MouseIterator
	CurrentTrack = Track;

	SoundSystem.Playsound(9);	
}

void CMenuMain::DiscardTrack()
{
	if(CurrentTrack != NULL)
	{
		SafeListRemove(CurrentTrack);
		CurrentTrack = NULL;
	}
}

int CMenuMain::LevelSuccess()
{


	MenuSystem.LowerBarOff();
	if(LevelSystem.CurrentLevelNumber == 10)//must be 10
	{
		Score = Score + ((TheCart->GetPowerup())*10);
		Score = Score +1;
		OrderedConsoleInsert("You Completed the Level.");
		MenuSystem.GameOn = false;
		MenuSystem.HighScoresOn(true);	
		//add code to add high score if its higher
	}
	else
	{
		if(LevelSystem.CurrentLevelNumber == 1 || LevelSystem.CurrentLevelNumber == 2 || LevelSystem.CurrentLevelNumber == 3 || LevelSystem.CurrentLevelNumber == 5 || LevelSystem.CurrentLevelNumber == 7 || LevelSystem.CurrentLevelNumber == 9)
		{
			PowerupOn();
		}
		else
		{
			NextLevelOn(LevelSystem.CurrentLevelNumber +1);
		}
	}
	return 0;
}
int CMenuMain::LevelFailure()
{
	//break;
	LowerBarOn();
	return 0;
}

void CMenuMain::MenuCollider()
{

	switch(MenuState)
	{
	case 0:///////////////////////////no menu/////////////////
		// no menu is rare while the game is running. so far
		// menu_intro is the only thing that runs in mode 0;
		//////////////////////////////////////////////////////
		break;
		//return 0;
	case 1: //main menu/////////////////////////////////////////////
        //////////button 0///////resume game btn
		RemoveElementsMatching("Menu_Main_BD");

		TI = ReturnElementMatching("Menu_Main_B0");
		if(TI != NULL)
		{
			if((*TI)->IsCollision(*MouseIterator))
			{
				switch(mouse_1)
				{
					case 1:
						OrderedInsert(new Popup("gfx/resumegamebtn.bmp","Menu_Main_BD", 20, 168, 11, 600,50,2,1));
						break;
					case 2:
						OrderedInsert(new Popup("gfx/resumegamebtn.bmp","Menu_Main_BD", 20, 168, 11, 600,50,2,1));
						break;
					case 3:
						MainOff();
						LowerBarOn();
						break;
				}
			break;
			}
		}
		//////////button 1///////
		RemoveElementsMatching("Menu_Main_BD");

		TI = ReturnElementMatching("Menu_Main_B1");
		if((*TI)->IsCollision(*MouseIterator))
		{
			switch(mouse_1)
			{
				case 1:
					if(GameOn==false)
					{
						OrderedInsert(new Popup("gfx/newgamebtn.bmp","Menu_Main_BD", 20, 175, 11, 600,50,2,1));
					}
					else
					{
						OrderedInsert(new Popup("gfx/newgamebtn.bmp","Menu_Main_BD", 20, 226, 11, 600,50,2,1));
					}
					break;
				case 2:
					if(GameOn==false)
					{
						OrderedInsert(new Popup("gfx/newgamebtn.bmp","Menu_Main_BD", 20, 175, 11, 600,50,2,1));
					}
					else
					{
						OrderedInsert(new Popup("gfx/newgamebtn.bmp","Menu_Main_BD", 20, 226, 11, 600,50,2,1));
					}					
					break;
				case 3:
					MainOff();
					NextLevelOn(1);
					break;
			}
		break;
		}
//////////////////button 2////////
		TI = ReturnElementMatching("Menu_Main_B2");
		if((*TI)->IsCollision(*MouseIterator))
		{
			switch(mouse_1)
			{
				case 1:
					if(GameOn==false)
					{
						OrderedInsert(new Popup("gfx/loadsavebtn.bmp","Menu_Main_BD", 20, 235, 11, 600,50,2,1));
					}
					else
					{
						OrderedInsert(new Popup("gfx/loadsavebtn.bmp","Menu_Main_BD", 20, 284, 11, 600,50,2,1));
					}
					break;
				case 2:
					if(GameOn==false)
					{
						OrderedInsert(new Popup("gfx/loadsavebtn.bmp","Menu_Main_BD", 20, 235, 11, 600,50,2,1));
					}
					else
					{
						OrderedInsert(new Popup("gfx/loadsavebtn.bmp","Menu_Main_BD", 20, 284, 11, 600,50,2,1));
					}					
					break;
	
				case 3:
					//MainOff();
					LoadSaveOn();
					break;
					
			}
		break;
		}
///////////////////button3////////
		TI = ReturnElementMatching("Menu_Main_B3");
		if((*TI)->IsCollision(*MouseIterator))
		{
			switch(mouse_1)
			{
				case 1:
					if(GameOn==false)
					{
						OrderedInsert(new Popup("gfx/optionsbtn.bmp","Menu_Main_BD", 20, 295, 11, 600,50,2,1));
					}
					else
					{
						OrderedInsert(new Popup("gfx/optionsbtn.bmp","Menu_Main_BD", 20, 342, 11, 600,50,2,1));
					}
					break;
				case 2:
					if(GameOn==false)
					{
						OrderedInsert(new Popup("gfx/optionsbtn.bmp","Menu_Main_BD", 20, 295, 11, 600,50,2,1));
					}
					else
					{
						OrderedInsert(new Popup("gfx/optionsbtn.bmp","Menu_Main_BD", 20, 342, 11, 600,50,2,1));
					}
					break;
				case 3:
					//MainOff();
					OptionsOn();
					break;
			}
		break;
		}
/////////////////button 4///////////
		TI = ReturnElementMatching("Menu_Main_B4");
		if((*TI)->IsCollision(*MouseIterator))
		{
			switch(mouse_1)
			{
				case 1:
					if(GameOn==false)
					{
						OrderedInsert(new Popup("gfx/highscoresbtn.bmp","Menu_Main_BD", 20, 355, 11, 600,50,2,1));
					}
					else
					{
						OrderedInsert(new Popup("gfx/highscoresbtn.bmp","Menu_Main_BD", 20, 400, 11, 600,50,2,1));
					}
					break;
				case 2:
					if(GameOn==false)
					{
						OrderedInsert(new Popup("gfx/highscoresbtn.bmp","Menu_Main_BD", 20, 355, 11, 600,50,2,1));
					}
					else
					{
						OrderedInsert(new Popup("gfx/highscoresbtn.bmp","Menu_Main_BD", 20, 400, 11, 600,50,2,1));
					}
					break;
				case 3:
					//MainOff();
					HighScoresOn(false);
					break;
			}
		break;
		}
/////////////////button 5////////////
		TI = ReturnElementMatching("Menu_Main_B5");
		if((*TI)->IsCollision(*MouseIterator))
		{
			switch(mouse_1)
			{
				case 1:
					if(GameOn==false)
					{
						OrderedInsert(new Popup("gfx/bigexitbtn.bmp","Menu_Main_BD", 20, 415, 11, 600,50,2,1));
					}
					else
					{
						OrderedInsert(new Popup("gfx/bigexitbtn.bmp","Menu_Main_BD", 20, 458, 11, 600,50,2,1));
					}
					break;
				case 2:
					if(GameOn==false)
					{
						OrderedInsert(new Popup("gfx/bigexitbtn.bmp","Menu_Main_BD", 20, 415, 11, 600,50,2,1));
					}
					else
					{
						OrderedInsert(new Popup("gfx/bigexitbtn.bmp","Menu_Main_BD", 20, 458, 11, 600,50,2,1));
					}
					break;				
				case 3:
					MainOff();
					RunOutro();
					break;
			}
		break;
		}
		break;
////////////////////options menu///////////////////////////////////////////////////////////
	case 2:
		RemoveElementsMatching("Menu_Options_BD");

		TI = ReturnElementMatching("Menu_Options_SL1");
		if((*TI)->IsCollision(*MouseIterator))
		{
			if(mouse_1 == 2)
			{
				AdjustSoundSlider();
				break;
			}
		}

		TI = ReturnElementMatching("Menu_Options_B1");
		if((*TI)->IsCollision(*MouseIterator))
		{
			switch(mouse_1)
			{
			case 1:
				OrderedInsert(new Popup("gfx/testbtn.bmp","Menu_Options_BD", 368, 290, 11, 128,32,2,1));
				break;
			case 2:
				OrderedInsert(new Popup("gfx/testbtn.bmp","Menu_Options_BD", 368, 290, 11, 128,32,2,1));
				break;
			case 3:
				TestSound();
				break;
			}
			break;
		}

		TI = ReturnElementMatching("Menu_Options_SL2");
		if((*TI)->IsCollision(*MouseIterator))
		{
			if(mouse_1 == 2)
			{
				AdjustMusicSlider();
				break;
			}
		}

		TI = ReturnElementMatching("Menu_Options_B2");
		if((*TI)->IsCollision(*MouseIterator))
		{
			switch(mouse_1)
			{
			case 1:
				OrderedInsert(new Popup("gfx/exitbtn.bmp","Menu_Options_BD", 530, 463, 11, 128,32,2,1));
				break;
			case 2:
				OrderedInsert(new Popup("gfx/exitbtn.bmp","Menu_Options_BD", 530, 463, 11, 128,32,2,1));
				break;
			case 3:
				OptionsOff();
				ConfigSystem.SaveToConfig("musicvolume",itoa(SoundSystem.GetMusicVolume(),mytemp,10));
				ConfigSystem.SaveToConfig("musicvolume",itoa(SoundSystem.GetMusicVolume(),mytemp,10));
				MenuState = 1;//main menu return
				break;
			}
			break;
		}
	break;
//////////////////////////highscore menu/////////////////////////////////////////
	case 3:
		RemoveElementsMatching("Menu_High_BD");
		if(keyboard_active == true && EntryMode == true)
		{
			RemoveElementsMatching("Menu_High_TE2");
			OrderedInsert(new Text(24,"Menu_High_TE2", keyboard_buffer.c_str() ,225,170,11,450,80,false));
		}
		if(keyboard_active == false && EntryMode == true)
		{
			HighScoreSystem.AddScore(keyboard_buffer.c_str(),Score);
			HighScoreSystem.WriteScores();
			HighScoresOff();
			HighScoresOn(false);
		}
		TI = ReturnElementMatching("Menu_High_OK");
		if((*TI)->IsCollision(*MouseIterator))
		{
			switch(mouse_1)
			{
			case 1:
				OrderedInsert(new Popup("gfx/OKbtn.bmp","Menu_High_BD", 530, (463), 11, 128,32,2,1));
				break;
			case 2:
				OrderedInsert(new Popup("gfx/OKbtn.bmp","Menu_High_BD", 530, (463), 11, 128,32,2,1));
				break;
			case 3:
				HighScoresOff();
				MenuState = 1; //main menu return
				break;
			}
			break;
		}
		break;
/////////////////////new track menu/////////////////////////////////////////////
	case 4:
		RemoveElementsMatching("Menu_Track_BD");

		TI = ReturnElementMatching("Menu_Track_OK");
		if((*TI)->IsCollision(*MouseIterator))
		{
			switch(mouse_1)
			{
			case 1:
				OrderedInsert(new Popup("gfx/OKbtn.bmp","Menu_Track_BD", 671, 413, 11, 128,32,2,1));
				break;
			case 2:
				OrderedInsert(new Popup("gfx/OKbtn.bmp","Menu_Track_BD", 671, 413, 11, 128,32,2,1));
				break;
			case 3:
				NewTrackOff();
				NextLevelOn(LevelSystem.CurrentLevelNumber+1);
				break;
			}
			break;
		}
		break;

//////////////////////////powerup menu/////////////////////////////////////////
	case 5:
		//RemoveElementsMatching("Menu_Powerup_BD");
///////////powerup 1///////////////////////
		RemoveElementsMatching("Menu_Powerup_BD");

		TI = ReturnElementMatching("Menu_Powerup_I2");
		if(TI != NULL)
		{
			if((*TI)->IsCollision(*MouseIterator))
			{

				switch(mouse_1)
				{
				case 1:
					RemoveElementsMatching("Menu_Powerup_I1");
					RemoveElementsMatching("Menu_Powerup_T1");
					OrderedInsert(new Text(18,"Menu_Powerup_T1", (char*)LevelSystem.currentlevel.PowerupText1.c_str(),320,100,11,170,80,false));
					OrderedInsert(new Popup(LevelSystem.currentlevel.PowerupImg1.c_str(),"Menu_Powerup_I1", 62, 93, 11, 250,310,1,0));
					break;
				case 2:
					RemoveElementsMatching("Menu_Powerup_I1");
					RemoveElementsMatching("Menu_Powerup_T1");
					OrderedInsert(new Text(18,"Menu_Powerup_T1", (char*)LevelSystem.currentlevel.PowerupText1.c_str(),320,100,11,170,80,false));
					OrderedInsert(new Popup(LevelSystem.currentlevel.PowerupImg1.c_str(),"Menu_Powerup_I1", 62, 93, 11, 250,310,1,0));
					break;
				case 3:
					SelectedPowerup = 1;
					break;
				}
				break;
			}
		}
/////////powerup 2//////////////////////
		TI = ReturnElementMatching("Menu_Powerup_I3");
		if(TI != NULL)
		{
			if((*TI)->IsCollision(*MouseIterator))
			{
				switch(mouse_1)
				{
				case 1:
					RemoveElementsMatching("Menu_Powerup_I1");
					RemoveElementsMatching("Menu_Powerup_T1");
					OrderedInsert(new Text(18,"Menu_Powerup_T1", (char*)LevelSystem.currentlevel.PowerupText2.c_str(),320,100,11,170,80,false));
					OrderedInsert(new Popup(LevelSystem.currentlevel.PowerupImg2.c_str(),"Menu_Powerup_I1", 62, 93, 11, 250,310,1,0));
					break;
				case 2:
					RemoveElementsMatching("Menu_Powerup_I1");
					RemoveElementsMatching("Menu_Powerup_T1");
					OrderedInsert(new Text(18,"Menu_Powerup_T1", (char*)LevelSystem.currentlevel.PowerupText2.c_str(),320,100,11,170,80,false));
					OrderedInsert(new Popup(LevelSystem.currentlevel.PowerupImg2.c_str(),"Menu_Powerup_I1", 62, 93, 11, 250,310,1,0));
					break;
				case 3:
					SelectedPowerup = 2;
					break;
				}
				break;
			}
		}
////////////////powerup 3////////////////////////
		TI = ReturnElementMatching("Menu_Powerup_I4");
		if(TI != NULL)
		{
			if((*TI)->IsCollision(*MouseIterator))
			{
				switch(mouse_1)
				{
				case 1:
					RemoveElementsMatching("Menu_Powerup_I1");
					RemoveElementsMatching("Menu_Powerup_T1");
					OrderedInsert(new Text(18,"Menu_Powerup_T1", (char*)LevelSystem.currentlevel.PowerupText3.c_str(),320,100,11,170,80,false));
					OrderedInsert(new Popup(LevelSystem.currentlevel.PowerupImg3.c_str(),"Menu_Powerup_I1", 62, 93, 11, 250,310,1,0));
					break;
				case 2:
					RemoveElementsMatching("Menu_Powerup_I1");
					RemoveElementsMatching("Menu_Powerup_T1");
					OrderedInsert(new Text(18,"Menu_Powerup_T1", (char*)LevelSystem.currentlevel.PowerupText3.c_str(),320,100,11,170,80,false));
					OrderedInsert(new Popup(LevelSystem.currentlevel.PowerupImg3.c_str(),"Menu_Powerup_I1", 62, 93, 11, 250,310,1,0));
					break;
				case 3:
					SelectedPowerup = 3;
					break;
				}
				break;
			}
		}
////////////////replay button/////////////////////////
		TI = ReturnElementMatching("Menu_Powerup_B1");
		if((*TI)->IsCollision(*MouseIterator))
		{
			switch(mouse_1)
			{
			case 1:
				OrderedInsert(new Popup("gfx/replaybtn.bmp","Menu_Powerup_BD", 430, 413, 11, 128,32,2,1));
				break;
			case 2:
				OrderedInsert(new Popup("gfx/replaybtn.bmp","Menu_Powerup_BD", 430, 413, 11, 128,32,2,1));
				break;
			case 3:				
				PowerupOff();
				NextLevelOn(LevelSystem.CurrentLevelNumber);//Load the level just played;
				break;
			}
			break;
		}
/////////////////ok button/////////////////////////
		TI = ReturnElementMatching("Menu_Powerup_B2");
		if((*TI)->IsCollision(*MouseIterator))
		{
			switch(mouse_1)
			{
			case 1:
				OrderedInsert(new Popup("gfx/OKbtn.bmp","Menu_Powerup_BD", 500, 413, 11, 128,32,2,1));
				break;
			case 2:
				OrderedInsert(new Popup("gfx/OKbtn.bmp","Menu_Powerup_BD", 500, 413, 11, 128,32,2,1));
				break;
			case 3:
				PowerupOff();
				//////add appropriate new powerup
				if(LevelSystem.currentlevel.PowerupType == 1)
				WheelType+=SelectedPowerup;
				if(LevelSystem.currentlevel.PowerupType == 2)
				BodyShape+=SelectedPowerup;
				if(LevelSystem.currentlevel.PowerupType == 3)
				WeightReduction+=SelectedPowerup; //all three of these affect the max speed of the cart.
		
				///////SetPoweruppics for LowerBar//////////////
				if(SelectedPowerup == 1)
				{
					if(LevelSystem.CurrentLevelNumber == 1)
					{
						Powerups[0] = LevelSystem.currentlevel.PowerupImg1;
					}
					if(LevelSystem.CurrentLevelNumber == 2)
					{
						Powerups[1] = LevelSystem.currentlevel.PowerupImg1;
					}
					if(LevelSystem.CurrentLevelNumber == 3)
					{
						Powerups[2] = LevelSystem.currentlevel.PowerupImg1;
					}
					if(LevelSystem.CurrentLevelNumber == 5)
					{
						Powerups[3] = LevelSystem.currentlevel.PowerupImg1;
					}
					if(LevelSystem.CurrentLevelNumber == 7)
					{
						Powerups[4] = LevelSystem.currentlevel.PowerupImg1;
					}
					if(LevelSystem.CurrentLevelNumber == 9)
					{
						Powerups[5] = LevelSystem.currentlevel.PowerupImg1;
					}
				}

				if(SelectedPowerup == 2)
				{
					if(LevelSystem.CurrentLevelNumber == 1)
					{
						Powerups[0] = LevelSystem.currentlevel.PowerupImg2;
					}
					if(LevelSystem.CurrentLevelNumber == 2)
					{
						Powerups[1] = LevelSystem.currentlevel.PowerupImg2;
					}
					if(LevelSystem.CurrentLevelNumber == 3)
					{
						Powerups[2] = LevelSystem.currentlevel.PowerupImg2;
					}
					if(LevelSystem.CurrentLevelNumber == 5)
					{
						Powerups[3] = LevelSystem.currentlevel.PowerupImg2;
					}
					if(LevelSystem.CurrentLevelNumber == 7)
					{
						Powerups[4] = LevelSystem.currentlevel.PowerupImg2;
					}
					if(LevelSystem.CurrentLevelNumber == 9)
					{
						Powerups[5] = LevelSystem.currentlevel.PowerupImg2;
					}
				}

				if(SelectedPowerup == 3)
				{
					if(LevelSystem.CurrentLevelNumber == 1)
					{
						Powerups[0] = LevelSystem.currentlevel.PowerupImg3;
					}
					if(LevelSystem.CurrentLevelNumber == 2)
					{
						Powerups[1] = LevelSystem.currentlevel.PowerupImg3;
					}
					if(LevelSystem.CurrentLevelNumber == 3)
					{
						Powerups[2] = LevelSystem.currentlevel.PowerupImg3;
					}
					if(LevelSystem.CurrentLevelNumber == 5)
					{
						Powerups[3] = LevelSystem.currentlevel.PowerupImg3;
					}
					if(LevelSystem.CurrentLevelNumber == 7)
					{
						Powerups[4] = LevelSystem.currentlevel.PowerupImg3;
					}
					if(LevelSystem.CurrentLevelNumber == 9)
					{
						Powerups[5] = LevelSystem.currentlevel.PowerupImg3;
					}
				}
				///////fix tempscore to score for new level
				Score = TempScore;

				/////////if end of level 4 or 8 then show new track piece menu
				if((LevelSystem.CurrentLevelNumber == 4) || (LevelSystem.CurrentLevelNumber == 8))
				{
					NewTrackOn();
				}
				else
				{
					NextLevelOn((LevelSystem.CurrentLevelNumber+1));
				}
				break;
			}
			break;
		}
		break;

//////////////////next level menu///////////////////////////////////////
	case 6:
		RemoveElementsMatching("Menu_Level_BD");

		TI = ReturnElementMatching("Menu_Level_B1");
		if((*TI)->IsCollision(*MouseIterator))
		{
			switch(mouse_1)
			{
			case 1:
				OrderedInsert(new Popup("gfx/OKbtn.bmp","Menu_Level_BD", 671, 413, 11, 128,32,2,1));
				break;
			case 2:
				OrderedInsert(new Popup("gfx/OKbtn.bmp","Menu_Level_BD", 671, 413, 11, 128,32,2,1));
				break;
			case 3:
				NextLevelOff();
				LowerBarOn();
				break;
			}
			break;

		}
		break;
/////////////////////load save menu///////////////////////////////////////////
		case 7:
		RemoveElementsMatching("Menu_Load_BD");
		////////////load button//////////////
		TI = ReturnElementMatching("Menu_Load_B1");
		if((*TI)->IsCollision(*MouseIterator))
		{

			switch(mouse_1)
			{
			case 1:
				OrderedInsert(new Popup("gfx/loadbtn.bmp","Menu_Load_BD", 206, 265, 11, 128,32,2,1));
				break;
			case 2:
				OrderedInsert(new Popup("gfx/loadbtn.bmp","Menu_Load_BD", 206, 265, 11, 128,32,2,1));
				break;
			case 3:
				if(LevelSystem.LoadLevelFromFile() == 0)
				{				
					LoadSaveOff();
					MenuState = 1; //return main menu state
					MainOff();
					LowerBarOn();
				}
				break;
			}
			break;

		}
		
		//////////////save button///////////////
		TI = ReturnElementMatching("Menu_Load_B2");
		if((*TI)->IsCollision(*MouseIterator))
		{
			switch(mouse_1)
			{
			case 1:
				OrderedInsert(new Popup("gfx/savebtn.bmp","Menu_Load_BD", 276, 265, 11, 128,32,2,1));
				break;
			case 2:
				OrderedInsert(new Popup("gfx/savebtn.bmp","Menu_Load_BD", 276, 265, 11, 128,32,2,1));
				break;
			case 3:
				if(GameOn == true)
				{
					LevelSystem.SaveLevel();
					LoadSaveOff();
					MenuState = 1;
				}
				break;
			}
			break;

		}
		

		///////////////////exit button///////////////
		TI = ReturnElementMatching("Menu_Load_B3");
		if((*TI)->IsCollision(*MouseIterator))
		{
			switch(mouse_1)
			{
			case 1:
				OrderedInsert(new Popup("gfx/exitbtn.bmp","Menu_Load_BD", 530, 265, 11, 128,32,2,1));
				break;
			case 2:
				OrderedInsert(new Popup("gfx/exitbtn.bmp","Menu_Load_BD", 530, 265, 11, 128,32,2,1));
				break;
			case 3:
				LoadSaveOff();
				MenuState = 1;
				break;
			}
			break;

		}
		break;
		LevelSystem.LoadLevelFromFile();
		LowerBarOn();
		break;
///////////////////////cart explosion////////////////////////////////
	case 8:
////////////////

		if(FrameCounter == 0 || FrameCounter == 10 || FrameCounter ==20 || FrameCounter == 30)
		{
			OrderedInsert(new AnimatedPopup("gfx/Explosions.bmp","Menu_Explosion",TheCart->Getx(),TheCart->Gety(),200,1000,100,10,0));
			SoundSystem.Playsound(10);
		}
		
		if(FrameCounter == 100)
		{
			RemoveElementsMatching("Menu_Explosion");
			TheCart->CurrentStatus = RegularR;
			MenuState = 10;
			break;
		}

		FrameCounter++;

		break;
///////////////////lower bar////////////////////////////////////////////////
	case 10:
	////////////do snap to grid stuff and track placement code
		if((mouse_y <510) && (TrackMenuState == 0))
		{
			if(CurrentTrack != NULL) //there is currently being a piece of track moved
			{
				// adam: fixed the snap code a little, snap_x was a little buggy
				if (mouse_x < 17) Snap_x = 16; // outside the left hand side boundary
				if (mouse_x > 783) Snap_x = 11 * 64 + 16; // outside the right hand side boundary
				else Snap_x = abs(((mouse_x - 16) / 64)*64) + 16;

				Snap_y = abs(((mouse_y+1) / 64)*64)+1;

				if(mouse_y < 512)
				{
					(*CurrentTrack)->MoveAbs(Snap_x,Snap_y);	
				}

				if(mouse_1 == 3)
				{
					// check for existing track piece excluding CurrentTrack
					if(((FindCollisionLastNotPowerup("mouse",(FindCollisionLastNotPowerup("mouse"))))) != NULL)
					{
						// adam: this will detect obstacles as well since they currently have z = 3
						if( (*(FindCollisionLastNotPowerup("mouse",(FindCollisionLastNotPowerup("mouse")))))->Getz() == 3)
						{
							//if the colliding piece is the current piece
							//added to fix placement bug
			
						//FindCollisionLast("mouse",(FindCollisionLast("mouse")));
						
							SoundSystem.Playsound(7); //cant placetrack sound
						}

						else
						{
							//leaves current track piece where it is
							Snap_x = (Snap_x - 16) / 64;
							Snap_y = (Snap_y - 1) / 64;
							LevelSystem.AddTrack(Snap_x, Snap_y, CurrentTrackType);

							CurrentTrack = NULL;
							SoundSystem.Playsound(6);
							
						}
						
					}
					
					
				}
				if(mouse_2 == 3)
				{
					//remove current track piece and stop trying to place
					DiscardTrack();
					SoundSystem.Playsound(7);
				}
			}
			else
			{
				if(mouse_1 == 3)
				{

					////code for grab a piece of placed track to move
					// adam: changed from a z == 3 check to a string check so you cant move fixed track
					if( (*(FindCollisionLastNotPowerup("mouse")))->GetString() == "Level_Data_Track_Placed")
					{
						SoundSystem.Playsound(9);
						CurrentTrack = (FindCollisionLastNotPowerup("mouse"));

						// adam: added this so currentlevel can keep track of the current grid
						if (mouse_x < 17) Snap_x = 16; // outside the left hand side boundary
						if (mouse_x > 783) Snap_x = 11 * 64 + 16; // outside the right hand side boundary
						else Snap_x = abs(((mouse_x - 16) / 64)*64) + 16;

						Snap_x = abs((Snap_x - 15) / 64);
						Snap_y = abs((mouse_y+1) / 64);

						CurrentTrackType = LevelSystem.RemoveTrack(Snap_x, Snap_y);

					//MainOn();
					}
				}
				if(mouse_2 == 3)
				{
					///// code to remove track piece from track
					// adam: changed from a z == 3 check to a string check so you cant move fixed track
					if( (*(FindCollisionLastNotPowerup("mouse")))->GetString() == "Level_Data_Track_Placed")
					{
						SoundSystem.Playsound(7);
						SafeListRemove(FindCollisionLastNotPowerup("mouse"));

						// adam: added this so currentlevel can keep track of the current grid
						if (mouse_x < 17) Snap_x = 16; // outside the left hand side boundary
						if (mouse_x > 783) Snap_x = 11 * 64 + 16; // outside the right hand side boundary
						else Snap_x = abs(((mouse_x - 16) / 64)*64) + 16;

						Snap_x = abs((Snap_x - 15) / 64);
						Snap_y = abs((mouse_y+1) / 64);

						LevelSystem.RemoveTrack(Snap_x, Snap_y);

					//MainOn();
					}
				}
			}

		}
		//initial speed slider
		if(((mouse_x < 355) && (mouse_x > 205)) && 
				((mouse_y <585) && (mouse_y >526)) && (mouse_1 == 2))
		{
			AdjustSpeedSlider();
			
		}
		///end of initial speed slider
		//////menu button////////////////////////////
		RemoveElementsMatching("Menu_Lower_BD");

		TI = ReturnElementMatching("Menu_Lower_B1");
		if((*TI)->IsCollision(*MouseIterator))
		{
			switch(mouse_1)
			{
			case 1:
				DiscardTrack();
				TrackMenusOff();
				OrderedInsert(new Popup("gfx/menubtn.bmp","Menu_Lower_BD", 12, 524, 2, 64,64,2,1));
				break;
			case 2:
				TrackMenusOff();
				OrderedInsert(new Popup("gfx/menubtn.bmp","Menu_Lower_BD", 12, 524, 2, 64,64,2,1));
				break;
			case 3:
				LowerBarOff();
				MainOn();
				break;
			}
			break;
		}
		///////////////go button////////////////////////
		TI = ReturnElementMatching("Menu_Lower_B2");
		if((*TI)->IsCollision(*MouseIterator))
		{
			switch(mouse_1)
			{
			case 1:
				DiscardTrack();
				TrackMenusOff();
				OrderedInsert(new Popup("gfx/mbutton.bmp","Menu_Lower_BD", 56, 524, 2, 256,64,2,1));
				break;
			case 2:
				TrackMenusOff();
				OrderedInsert(new Popup("gfx/mbutton.bmp","Menu_Lower_BD", 56, 524, 2, 256,64,2,1));
				break;
			case 3:
				////////change state to cart running
				if (ValidateTrack() == true)
				{
					FrameCounter = 0;
					string TempString;
					//ensure the initial speed bar gives correct Speed
					StartSpeed = ((*(ReturnElementMatching("Menu_Lower_SP")))->Getx())/8;	

					//OrderedConsoleInsert(("You started your cart at" + StartSpeed));

					TheCart->ResetPowerups(LevelSystem.currentlevel.totalpickups);
			
					TheBall->SetState(Failed);
					TheCart->SetState(Running);
					Track *theTrack;
					Dynamite *thebomb;
					Crusher *thecrusher;
					RLiterator theiterator;
					theiterator = ReturnElementMatching("Level_Data_Dynamite");

					theTrack = 	(Track*) (*ReturnElementMatching("Level_Data_Track_Start"));

					TheCart->MoveAbs(theTrack->Getx() - 32, theTrack->Gety());
					TheCart->SetSpeed(20);

					theTrack->OnCollision(TheCart);
					/////push cart with initial startspeed

				
					TheCart->Push(StartSpeed);

					
					//if a bomb start it counting down
					if (theiterator != NULL)
					{
						thebomb = (Dynamite*) (*theiterator);
						thebomb->StartTimer();
					}

					theiterator = NULL;
					theiterator = ReturnElementExact("Level_Data_Crusher_End");
					if (theiterator != NULL)
					{
						thecrusher = (Crusher*) (*theiterator);
						thecrusher->SetFrame(26);
					}

					theiterator = NULL;
					//if a crusher is in the level start it at frame 1
					theiterator = ReturnElementExact("Level_Data_Crusher");
					if (theiterator != NULL)
					{
						thecrusher = (Crusher*) (*theiterator);
						thecrusher->SetFrame(1);
					}
					
					///insert stop button
					OrderedInsert(new Popup("gfx/cbutton.bmp","Menu_Lower_BC", 56, 524, 2, 256,64,2,0));
					///play looping cart sound
					CartSoundHandle = SoundSystem.Loopsound(11);
					//setstate to cartmode
					MenuState = 11;
				}
				else
				{
					OrderedConsoleInsert("The track is not completed.");
				}
				break;
			}
			break;

		}
		///////track pieces menu 1 button////////////////////
		TI = ReturnElementMatching("Menu_Lower_B3");
		if((*TI)->IsCollision(*MouseIterator))
		{
			switch(mouse_1)
			{

			case 1:
				if(TrackMenuState == 1)
				{
					TrackMenusOff();
					SoundSystem.Playsound(8); // track menu up sound			
				}
				else
				{
					OrderedInsert(new Popup("gfx/trackhole.bmp","Menu_Lower_BD", 572, 524, 2, 64,64,1,0));
					TrackMenusOff();
					TrackMenu1On();
				}
					break;
			case 2:			
					//OrderedInsert(new Popup("gfx/trackhole.bmp","Menu_Lower_BD", 572, 524, 2, 64,64,1,0));
					//TrackMenusOff();
					//TrackMenu1On();
					break;

			case 3:
				break;
			}
			break;

		}
		///////track pieces menu 2 button////////////////////
		TI = ReturnElementMatching("Menu_Lower_B4");
		if((*TI)->IsCollision(*MouseIterator))
		{
			switch(mouse_1)
			{
			case 1:
				if(TrackMenuState == 2)
				{
					TrackMenusOff();
					SoundSystem.Playsound(8); // track menu up sound
				}
				else
				{
					OrderedInsert(new Popup("gfx/trackhole.bmp","Menu_Lower_BD", 648, 524, 2, 64,64,1,0));
					TrackMenusOff();
					TrackMenu2On();
				}
				break;
			case 2:
				//OrderedInsert(new Popup("gfx/trackhole.bmp","Menu_Lower_BD", 648, 524, 2, 64,64,1,0));
				//TrackMenusOff();
				//TrackMenu2On();
				break;
			case 3:
				break;
			}
			break;

		}
		///////track pieces menu 3 button////////////////////
/*		TI = ReturnElementMatching("Menu_Lower_B5");
		if((*TI)->IsCollision(*MouseIterator))
		{
			switch(mouse_1)
			{
			case 1:
				if(TrackMenuState == 3)
				{
					TrackMenusOff();
					SoundSystem.Playsound(8); // track menu up sound
				}
				else
				{
				OrderedInsert(new Popup("gfx/trackhole.bmp","Menu_Lower_BD", 724, 524, 2, 64,64,1,0));
				TrackMenusOff();
				TrackMenu3On();
				}
				break;
			case 2:
				//OrderedInsert(new Popup("gfx/trackhole.bmp","Menu_Lower_BD", 724, 524, 2, 64,64,1,0));
				//TrackMenusOff();
				//TrackMenu3On();
				break;
			case 3:
				break;
			}
			break;

		}
		*/
		//////////////if a track menu is up check for a collisi0on on that menu
		if(TrackMenuState != 0)
		{
			switch(TrackMenuState)
			{
			case 1:////////////if track menu 1 is on
				TI = ReturnElementMatching("Menu_Lower_TM1_B1");
				if((*TI)->IsCollision(*MouseIterator))//first track piece in menu
				{
					if(mouse_1 ==3)
					{
						
						GrabTrack(OrderedInsert(new Track("gfx/TD.bmp", "Level_Data_Track_Placed", 572, 460, 3, Normal, 2)));
						TrackMenusOff();
						CurrentTrackType = int(T_V);
					}
					break;
				}

				TI = ReturnElementMatching("Menu_Lower_TM1_B2");//2nd track piece in menu
				if((*TI)->IsCollision(*MouseIterator))
				{
					if(mouse_1 ==3)
					{
						
						GrabTrack(OrderedInsert(new Track("gfx/TR.bmp", "Level_Data_Track_Placed", 572, 396, 3, Normal, -1)));
						TrackMenusOff();
						CurrentTrackType = int(T_H);
					}
					break;
				}

				TI = ReturnElementMatching("Menu_Lower_TM1_B3");//3rd track piece in menu
				if((*TI)->IsCollision(*MouseIterator))
				{
					if(mouse_1 ==3)
					{
						
						GrabTrack(OrderedInsert(new Track("gfx/slowdown.bmp", "Level_Data_Track_Placed", 572, 332, 3, SpeedDown, -10)));
						TrackMenusOff();
						CurrentTrackType = int(T_SLOW);
					}
					break;
				}

				TI = ReturnElementMatching("Menu_Lower_TM1_B4");
				if((*TI)->IsCollision(*MouseIterator))
				{
					if(mouse_1 ==3)
					{
						GrabTrack(OrderedInsert(new Track("gfx/speedup.bmp", "Level_Data_Track_Placed", 572, 268, 3, SpeedUp, 10)));
						TrackMenusOff();
						CurrentTrackType = int(T_FAST);
					}
					break;
				}
				break;
			///////////////track menu 2 is on//////////
			case 2:
				TI = ReturnElementMatching("Menu_Lower_TM2_B1");
				if((*TI)->IsCollision(*MouseIterator))
				{
					if(mouse_1 ==3)
					{
						GrabTrack(OrderedInsert(new Track("gfx/TC1.bmp", "Level_Data_Track_Placed", 648, 460, 3, LeftDown, 0)));
						TrackMenusOff();
						CurrentTrackType = int(T_LU);
					}
					break;
				}

				TI = ReturnElementMatching("Menu_Lower_TM2_B2");
				if((*TI)->IsCollision(*MouseIterator))
				{
					if(mouse_1 ==3)
					{
						GrabTrack(OrderedInsert(new Track("gfx/TC2.bmp", "Level_Data_Track_Placed", 648, 396, 3, RightDown, 0)));
						TrackMenusOff();
						CurrentTrackType = int(T_RU);
					}
					break;
				}

				TI = ReturnElementMatching("Menu_Lower_TM2_B3");
				if((*TI)->IsCollision(*MouseIterator))
				{
					if(mouse_1 ==3)
					{
						GrabTrack(OrderedInsert(new Track("gfx/TC3.bmp", "Level_Data_Track_Placed", 648, 332, 3, RightUp, 0)));
						TrackMenusOff();
						CurrentTrackType = int(T_RD);
					}
					break;
				}

				TI = ReturnElementMatching("Menu_Lower_TM2_B4");
				if((*TI)->IsCollision(*MouseIterator))
				{
					if(mouse_1 ==3)
					{
						GrabTrack(OrderedInsert(new Track("gfx/TC4.bmp", "Level_Data_Track_Placed", 648, 268, 3, LeftUp, 0)));
						TrackMenusOff();
						CurrentTrackType = int(T_LD);
					}
					break;
				}
				break;
			//////////////////////
			//case 3: meant to go here
			////////////////////

			}
		}
		break;
	///////////////////CART MODE////////////////////////////////////////////////
	case 11:
	///////////////////////////////////////////////
		RemoveElementsMatching("Menu_Lower_BCD");
		TI = ReturnElementMatching("Menu_Lower_BC");//cancel
		if((*TI)->IsCollision(*MouseIterator))
		{
			switch(mouse_1)
			{
			case 1:
			
				OrderedInsert(new Popup("gfx/cbutton.bmp","Menu_Lower_BCD", 56, 524, 2, 256,64,2,1));
				break;
			case 2:
				
				OrderedInsert(new Popup("gfx/cbutton.bmp","Menu_Lower_BCD", 56, 524, 2, 256,64,2,1));
				break;
			case 3:
				////////return to game
				RemoveElementsMatching("Menu_Lower_BCD");
				RemoveElementsMatching("Menu_Lower_BC");
				OrderedConsoleInsert("You Stopped your Cart.");
				TheCart->SetState(Failed);
				TheBall->SetState(Failed);
				TheBall->SetSpeed(0);
				TheBall->MoveAbs(-80,-80);
				//MenuState = 10;
				//SoundSystem.Stopsound(CartSoundHandle);
				break;
			}
			//break;

		}
		// adjust cart sound for speed of the cart
		SoundSystem.SetFreq(CartSoundHandle, ((TheCart->AdjustSpeed(0)) * 500 + 8500));
	
		///////////////ball release code
		if(FrameCounter == LevelSystem.currentlevel.BallCounter && FrameCounter != 0)
		{
					Track *theTrack;
					theTrack = 	(Track*) (*ReturnElementMatching("Level_Data_Track_Start"));
					TheBall->SetState(Running);
					TheBall->MoveAbs(theTrack->Getx(), theTrack->Gety());
					TheBall->Push(30);
					
		}

		if(TheCart->GetState() == Finished)
		{
			MenuState = 10;
			SoundSystem.Stopsound(CartSoundHandle);
			RemoveElementsMatching("Menu_Lower_BCD");
			RemoveElementsMatching("Menu_Lower_BC");
			TheBall->SetState(Failed);
			TheBall->SetSpeed(0);
			TheBall->MoveAbs(-80,-80);

			LevelSuccess();

			break;
		}
		if(TheCart->GetState() == Failed)
		{
			SoundSystem.Stopsound(CartSoundHandle);
			RemoveElementsMatching("Menu_Lower_BCD");
			RemoveElementsMatching("Menu_Lower_BC");
			CartExplosion(TheCart->Getx(),560);
			TheCart->SetState(Failed);
			TheBall->SetState(Failed);
			TheBall->SetSpeed(0);
			TheBall->MoveAbs(-80,-80);
			LevelSystem.ResetPickups();
			break;
		
		}


		FrameCounter++;
		break;
////////////////////////////////////////////////////////////////////




	}
}


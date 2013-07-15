#include "CLevelData.h"
extern CLogging *log;


CLevelData::CLevelData()
{
}

CLevelData::~CLevelData()
{
}

void CLevelData::LoadLevel(int whichlevel)
// this just sets currentlevel to the chosen level
{
	DestroyLevel(); // make sure nothing is left over

	switch (whichlevel) // set up appropriate level
	{
	case 1:
		SetLevel1();
		break;
	case 2:
		SetLevel2();
		break;
	case 3:
		SetLevel3();
		break;
	case 4:
		SetLevel4();
		break;
	case 5:
		SetLevel5();
		break;
	case 6:
		SetLevel6();
		break;
	case 7:
		SetLevel7();
		break;
	case 8:
		SetLevel8();
		break;
	case 9:
		SetLevel9();
		break;
	case 10:
		SetLevel10();
		break;
	};


}

void CLevelData::DisplayLevel()
{
	DoBackground();
	DoTracks();
	DoObstacles();
	DoPickups();
	DoHazards();
}

void CLevelData::HideLevel()
{
	// remove background
	// remove tracks
	// remove obstacles
	// remove pickups
	// remove start/finish
	// remove hazards
	RemoveElementsMatching("Level_Data"); // blam all level details gone
	RemoveElementsMatching("Level_Data_Dynamite");
}

void CLevelData::DestroyLevel()
// empty all level details here
{
	int x,y; // loop counters

	HideLevel(); // just in case we havent done a hide already
	
	// empty current level
	for (y = 0; y < 8; y++) // set all tracks to none
	{
		for (x = 0; x < 12; x++) 
		{
			currentlevel.placedtrack[y][x] = T_NONE;
			currentlevel.alltrack[y][x] = T_NONE;
		}
	}
}

void CLevelData::DoBackground()
// naming convention = Level_Data_Background
{
	OrderedInsert(new Popup(currentlevel.background.c_str() ,"Level_Data_Background", 0, 0, 0, 800,512,1,0));	
}

void CLevelData::DoTracks() 
// naming convention = Level_Data_Track_Fixed
// placed track is Level_Data_Track_Placed
// will get problems once game resuming is in place since all previously placed track
// will become fixed
{
	int x, y, realx, realy; // temp loop counters/positioners
	int gapx = 16; // gap on left hand side of game screen
	int gapy = 1; // gap from top of screen

	char *trackname; // what should objstring be set to
	char *crushername = "Level_Data_Crusher";
	char *jumpname = "Level_Data_Jump";

	for (y = 0; y < 8; y++)
	{
		for (x = 0; x < 12; x++)
		{
			realx = 64*x + gapx;
			realy = 64*y + gapy;

			// check if this is the start piece (different naming convention)
			if (x == currentlevel.start.x && y == currentlevel.start.y) // this is the start piece
				trackname = "Level_Data_Track_Start";
			else if (x == currentlevel.finish.x && y == currentlevel.finish.y) // this is the finish piece
				trackname = "Level_Data_Track_Finish";
			else // just a regular piece of fixed track
				trackname = "Level_Data_Track_Fixed";

			switch (currentlevel.fixedtrack[y][x]) // do fixed tracks first
			{
			case T_NONE: 
				break;
			case T_H: 
				OrderedInsert(new Track("gfx/TR.bmp", trackname, realx, realy, 3, Normal, -1));
				break;
			case T_V: 
				OrderedInsert(new Track("gfx/TD.bmp", trackname, realx, realy, 3, Normal, 5));
				break;
			case T_LU: 
				OrderedInsert(new Track("gfx/TC1.bmp", trackname, realx, realy, 3, LeftDown, 0));
				break;
			case T_LD: 
				OrderedInsert(new Track("gfx/TC4.bmp", trackname, realx, realy, 3, LeftUp, 0));
				break;
			case T_RU: 
				OrderedInsert(new Track("gfx/TC2.bmp", trackname, realx, realy, 3, RightDown, 0));
				break;
			case T_RD: 
				OrderedInsert(new Track("gfx/TC3.bmp", trackname, realx, realy, 3, RightUp, 0));
				break;
			case T_START:
				OrderedInsert(new Track("gfx/start01.bmp", trackname, realx, realy, 3, Start, 0));
				break;
			case T_FINISH:
				OrderedInsert(new Track("gfx/finish01.bmp", trackname, realx, realy, 3, Finish, 0));
				break;
			case T_CRUSH:
				OrderedInsert(new StaticObj("gfx/crusherbackground.bmp", "Level_Data_Track_Crusher2", realx, realy, 3, 64, 64));
				OrderedInsert(new Crusher("gfx/Crusher.bmp", crushername, realx, realy, 3, 26, 1));
				break;
			case T_CRUSH2:
				OrderedInsert(new StaticObj("gfx/crusherbackground.bmp", "Level_Data_Track_Crusher2", realx, realy, 3, 64, 64));
				OrderedInsert(new Crusher("gfx/Crusher.bmp", "Level_Data_Crusher_End", realx, realy, 3, 26, 26));
				break;
			case T_JUMP:
				OrderedInsert(new Jump("gfx/Jump.bmp", jumpname, realx, realy, 3, 6, 1));
//			case T_FAST: 
//				OrderedInsert(new Track("gfx/TL.bmp", trackname, realx, realy, 3, Normal, -1));
//				break;
//			case T_SLOW: 
//				OrderedInsert(new Track("gfx/TU.bmp", trackname, realx, realy, 3, Normal, 5));
//				break;

			};

			switch (currentlevel.placedtrack[y][x]) // now do placed tracks
			{
			case T_NONE: 
				break;
			case T_H: 
				OrderedInsert(new Track("gfx/TR.bmp", "Level_Data_Track_Placed", realx, realy, 3, Normal, -1));
				break;
			case T_V: 
				OrderedInsert(new Track("gfx/TD.bmp", "Level_Data_Track_Placed", realx, realy, 3, Normal, 5));
				break;
			case T_LU: 
				OrderedInsert(new Track("gfx/TC1.bmp", "Level_Data_Track_Placed", realx, realy, 3, LeftDown, 0));
				break;
			case T_LD: 
				OrderedInsert(new Track("gfx/TC4.bmp", "Level_Data_Track_Placed", realx, realy, 3, LeftUp, 0));
				break;
			case T_RU: 
				OrderedInsert(new Track("gfx/TC2.bmp", "Level_Data_Track_Placed", realx, realy, 3, RightDown, 0));
				break;
			case T_RD: 
				OrderedInsert(new Track("gfx/TC3.bmp", "Level_Data_Track_Placed", realx, realy, 3, RightUp, 0));
				break;
			case T_FAST: 
				OrderedInsert(new Track("gfx/speedup.bmp", "Level_Data_Track_Placed", realx, realy, 3, SpeedUp, 30));
				break;
			case T_SLOW: 
				OrderedInsert(new Track("gfx/slowdown.bmp", "Level_Data_Track_Placed", realx, realy, 3, SpeedDown, -30));
				break;

			};
		}
	}
	FixGrids(); // set up alltrack[][]
}

void CLevelData::DoObstacles()
// naming convention = Level_Data_Obstacle
// z value 3, same as track, track cant be placed on obstacles that way
{
	int x, y, realx, realy; // temp loop counters/positioners
	int gapx = 16; // gap on left hand side of game screen
	int gapy = 1;

	for (y = 0; y < 8; y++)
	{
		for (x = 0; x < 12; x++) // for each grid position
		{
			realx = 64*x + gapx;
			realy = 64*y + gapy;
			switch (currentlevel.obstacles[y][x])
			{
			case O_1: // we got an obstacle, create a staticobj
				OrderedInsert(new StaticObj("gfx/obstacle.bmp", "Level_Data_Obstacle", realx, realy, 3, 64, 64));
				break;
			case O_2:
				OrderedInsert(new StaticObj("gfx/pipes.bmp", "Level_Data_Obstacle", realx, realy, 3, 64, 64));
				break;
			case O_3:
				OrderedInsert(new StaticObj("gfx/brokencart.bmp", "Level_Data_Obstacle", realx, realy, 3, 64, 64));
				break;
			case O_4:
				OrderedInsert(new StaticObj("gfx/gemrock.bmp", "Level_Data_Obstacle", realx, realy, 3, 64, 64));
				break;
			case O_5:
				OrderedInsert(new StaticObj("gfx/gemrock2.bmp", "Level_Data_Obstacle", realx, realy, 3, 64, 64));
				break;
			case O_6:
				OrderedInsert(new StaticObj("gfx/obstacle2.bmp", "Level_Data_Obstacle", realx, realy, 3, 64, 64));
				break;

			case O_NONE:
				break; // no obstacle, exit out
			};
		}
	}
}

void CLevelData::DoPickups()
// naming convention = Level_Data_Pickup
// current z is 2, temporary till pickups are finished proper
{
	int x, y, realx, realy; // temp loop counters/positioners
	int gapx = 16; // gap on left hand side of game screen
	int gapy = 1;

	for (y = 0; y < 8; y++)
	{
		for (x = 0; x < 12; x++)
		{
			realx = 64*x + gapx;
			realy = 64*y + gapy;
			switch (currentlevel.pickups[y][x])
			{
			case P_1: // we got an obstacle, create a static
				OrderedInsert(new Powerup("gfx/pickup1.bmp", "Level_Data_Pickup", realx, realy, 4));
				break;
			case P_2: // we got an obstacle, create a static
				OrderedInsert(new Powerup("gfx/pickup2.bmp", "Level_Data_Pickup", realx, realy, 4));
				break;
			case P_3: // we got an obstacle, create a static
				OrderedInsert(new Powerup("gfx/pickup3.bmp", "Level_Data_Pickup", realx, realy, 4));
				break;
			case P_4: // we got an obstacle, create a static
				OrderedInsert(new Powerup("gfx/pickup4.bmp", "Level_Data_Pickup", realx, realy, 4));
				break;
			case P_NONE: break; // no obstacle, exit out
			};
		}
	}
}

void CLevelData::DoHazards()
{
	int x, y, realx, realy; // temp loop counters/positioners
	int gapx = 16; // gap on left hand side of game screen
	int gapy = 1;

	for (y = 0; y < 8; y++)
	{
		for (x = 0; x < 12; x++)
		{
			realx = 64*x + gapx;
			realy = 64*y + gapy;
			switch (currentlevel.hazards[y][x])
			{
			case H_D:
				OrderedInsert(new Dynamite("gfx/Dynamite.bmp", "Level_Data_Dynamite", realx, realy, 4, currentlevel.DynamiteTime));
				break;
			case H_NONE: 
				break; // no hazard, exit out
			};
		}
	}
}

void CLevelData::AddTrack(int x,int y, int whattype)
// add track to the current grid for game resuming and run time grid updates
{
	currentlevel.placedtrack[y][x] = tracktype(whattype);
	currentlevel.alltrack[y][x] = tracktype(whattype);
}

int CLevelData::RemoveTrack(int x, int y)
// remove track from the current grid, returns the old piece of track
{
	int oldvalue = currentlevel.placedtrack[y][x];
	currentlevel.placedtrack[y][x] = T_NONE;
	currentlevel.alltrack[y][x] = T_NONE;
	return oldvalue;
}

void CLevelData::RemovePickup(int x, int y)
{
	currentlevel.pickups[y][x] = P_NONE;
	currentlevel.remainingpickups--;
}

void CLevelData::RemoveHazards(int x, int y)
{
	currentlevel.hazards[y][x] = H_NONE;
}

void CLevelData::FixGrids()
// coordinate all three grids
// basically sets alltrack to whatever fixedtrack and placed track have
{
	int x, y; // temp x,y array pos
	for (y = 0; y < 8; y++)
	{
		for (x = 0; x < 12; x++)
		{
			if(currentlevel.fixedtrack[y][x] != T_NONE)
				currentlevel.alltrack[y][x] = currentlevel.fixedtrack[y][x];
			if(currentlevel.placedtrack[y][x] != T_NONE)
				currentlevel.alltrack[y][x] = currentlevel.placedtrack[y][x];
		}
	}
}

void CLevelData::SaveLevel()
{
	string arraylabel; // holds the name of the config label to write to
	int x, y, tracktype; // temp x,y array pos
	char tempstr[6];

	itoa(CurrentLevelNumber, tempstr, 10); // convert currentlevel to a string
	ConfigSystem.SaveToConfig("levelsave_level", tempstr); // save level number


	ConfigSystem.SaveToConfig("levelsave_powerup1", MenuSystem.Powerups[0]);
	ConfigSystem.SaveToConfig("levelsave_powerup2", MenuSystem.Powerups[1]);
	ConfigSystem.SaveToConfig("levelsave_powerup3", MenuSystem.Powerups[2]);
	ConfigSystem.SaveToConfig("levelsave_powerup4", MenuSystem.Powerups[3]);
	ConfigSystem.SaveToConfig("levelsave_powerup5", MenuSystem.Powerups[4]);
	ConfigSystem.SaveToConfig("levelsave_powerup6", MenuSystem.Powerups[5]);

	itoa(TheCart->BodyShape, tempstr, 10); // convert currentlevel to a string
	ConfigSystem.SaveToConfig("levelsave_cartbody", tempstr);

	itoa(TheCart->WeightReduction, tempstr, 10); // convert currentlevel to a string
	ConfigSystem.SaveToConfig("levelsave_cartweight", tempstr);

	itoa(TheCart->WheelType, tempstr, 10); // convert currentlevel to a string
	ConfigSystem.SaveToConfig("levelsave_cartwheel", tempstr);

	// save placed tracks
	for (y = 0; y < 8; y++)
	{
		for (x = 0; x < 12; x++) // for each grid position
		{
			arraylabel.assign("levelsave_track_"); // set up label string
			itoa(y, tempstr, 10);
			arraylabel += tempstr;
			arraylabel.append("_");
			itoa(x, tempstr, 10);
			arraylabel += tempstr;

			tracktype = int(currentlevel.placedtrack[y][x]); // grab the tracktype
			itoa(tracktype, tempstr, 10);
			ConfigSystem.SaveToConfig(arraylabel, tempstr); // save it
		}
	}

	// anything else to be saved goes here
}

int CLevelData::LoadLevelFromFile()
{
	string currentdata, arraylabel; // temp string storage
	char tempstr[2];
	int x, y; // temp array pos's

	// load up the level
	if (ConfigSystem.LoadFromConfig("levelsave_level") == "BADFILE")
		return 1;
	if (atoi((ConfigSystem.LoadFromConfig("levelsave_level")).c_str()) < 1 || 
		atoi((ConfigSystem.LoadFromConfig("levelsave_level")).c_str()) > 10) 
	{
		return 2;
	}

	currentdata = ConfigSystem.LoadFromConfig("levelsave_level");
	LoadLevel(atoi(currentdata.c_str()));



	MenuSystem.Powerups[0] = ConfigSystem.LoadFromConfig("levelsave_powerup1").c_str();
	MenuSystem.Powerups[1] = ConfigSystem.LoadFromConfig("levelsave_powerup2").c_str();
	MenuSystem.Powerups[2] = ConfigSystem.LoadFromConfig("levelsave_powerup3").c_str();
	MenuSystem.Powerups[3] = ConfigSystem.LoadFromConfig("levelsave_powerup4").c_str();
	MenuSystem.Powerups[4] = ConfigSystem.LoadFromConfig("levelsave_powerup5").c_str();
	MenuSystem.Powerups[5] = ConfigSystem.LoadFromConfig("levelsave_powerup6").c_str();


	TheCart->BodyShape = atoi(ConfigSystem.LoadFromConfig("levelsave_cartbody").c_str());

	TheCart->WeightReduction = atoi(ConfigSystem.LoadFromConfig("levelsave_cartweight").c_str());

	TheCart->WheelType = atoi(ConfigSystem.LoadFromConfig("levelsave_cartwheel").c_str());


	// set up placed tracks
	for (y = 0; y < 8; y++)
	{
		for (x = 0; x < 12; x++) // for each grid position
		{
			arraylabel = "levelsave_track_"; // set up label string
			itoa(y, tempstr, 10);
			arraylabel += tempstr;
			arraylabel += "_";
			itoa(x, tempstr, 10);
			arraylabel += tempstr;

			currentdata = ConfigSystem.LoadFromConfig(arraylabel);
			if (currentdata == "BADFILE") return 1;
			else if (currentdata == "NOTFOUND") return 3;
			currentlevel.placedtrack[y][x] = tracktype(atoi(currentdata.c_str()));
		}
	}
	return 0;
}

void CLevelData::ResetPickups()
{
	RemoveElementsMatching("Level_Data_Pickup");
	DoPickups();
}
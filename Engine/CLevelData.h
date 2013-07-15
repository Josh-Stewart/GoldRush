/* CLevelData.h

Author : Adam Payne

CLevelData is a class to handle all level data during run time
It keeps track of tracks, the background bitmap, obstacles, hazards, start and finish 
and pickups. It can display them all as well as popups.
Current level data can be accessed through LevelSystem.currentlevel.

This header is used by not only CLevelData.cpp but also level1-10.cpp
The level files set currentlevel to that specific levels data.

Future additions might be data for the level briefings and saving/loading levels in play
*/

#ifndef CLEVELDATA
#define CLEVELDATA

#include <string>

#include "stdlib.h"
#include "globals.h"
#include "ddutil.h"
#include "Game_Main.h"
#include "Game_Shutdown.h"

using namespace std;

enum tracktype
// used in the track array data structure
// this could be replaced with a more standard track storage method pretty easily
{
	T_NONE,	// no track
	T_H,	// flat horizontal track
	T_V,	// vertical track
	T_LU,	// left to up turn
	T_LD,	// left to down turn
	T_RU,	// right to up turn
	T_RD,	// right to down turn
	T_START,
	T_FINISH,
	T_CRUSH, // crusher starting on frame 1
	T_CRUSH2, // crusher starting on frame 26
	T_JUMP,
	T_FAST,
	T_SLOW
};

enum pickuptype
// similar to track array
{
	P_NONE, // no pickup
	P_1, // green
	P_2, // yellow
	P_3, // white
	P_4 // pink
};

enum obstacletype
{
		O_NONE,
		O_1,
		O_2,
		O_3,
		O_4,
		O_5,
		O_6
};


enum hazardtype
//similar to track array
{
	H_NONE,
	H_D
};

struct TrackPosStruct
// holds a x and y position, used for start and finish positions
{
	int x, y;
};

struct LevelStruct
{
public:
	string background; // name of background filename

	string ObstacleImg; // name of obstacle image filename;
	string ObstacleText1; // obstacle text to be displayed
	string ObstacleText2; // obstacle text to be displayed
	string MaterialImg; // name of material image filename
	string MaterialText1; // material text to be displayed
	string MaterialText2; // material text to be displayed
	string PowerupText0;
	string PowerupText1;
	string PowerupText2;
	string PowerupText3;


	string PowerupImg1;
	string PowerupImg2;
	string PowerupImg3;

	int PowerupType; ///can be 1 2 or 3. wheels, body or weightreduction
	int DynamiteTime; // Amount of time the Dynamite counts down from
	int BallCounter; //Number of frames before the ball is released after the cart.


	tracktype fixedtrack[8][12]; // grid of fixed level track
	tracktype placedtrack[8][12]; // grid of tracks which have been placed by player
	tracktype alltrack[8][12]; // grid of all track, USE THIS FOR TRACK CHECKS
	obstacletype obstacles[8][12]; // grid of obstacles
	pickuptype pickups[8][12]; // grid of pickups
	int remainingpickups; // how many pickups are currently on the level
	int totalpickups; // how many pickups are there total
	int hazards[8][12]; // hazards data goes here

	bool ObstacleAnimated;

	TrackPosStruct start, finish; // start and finish pos coordinates
};

class CLevelData
{
public:
	CLevelData();
	~CLevelData();

	void LoadLevel(int whichlevel); // load whichlevel into current level
	void DisplayLevel(); // set bitmaps etc for currentlevel
	void HideLevel(); // removes all level popups
	void DestroyLevel(); // empty currentlevel data

	void AddTrack(int x,int y, int whattype); // add a piece of track to the grid
	int RemoveTrack(int x, int y); // remove a piece of track from the grid, returns the type of track removed

	void CLevelData::RemoveHazards(int x, int y);
	void RemovePickup(int x, int y); // remove pickup from x, y
	void ResetPickups(); // show all pickups again

	void SaveLevel(); // save current tracks etc to the config file
	int LoadLevelFromFile(); // load an old level setup from the config file
		// error codes:
		// 1 = bad level, 2 = bad config file, 3 = an entry not found

	LevelStruct currentlevel; // the currently loaded level
	int CurrentLevelNumber;

private:
	void DoBackground(); // set up and display background
	void DoTracks(); // set up and display tracks
	void DoObstacles(); // set up and display obstacles
	void DoPickups(); // set up and display pickups
	void DoHazards(); // set up and display hazards

	void SetLevel1(); // set up level 1
	void SetLevel2(); // set up level 2
	void SetLevel3(); // set up level 3
	void SetLevel4(); // set up level 4
	void SetLevel5(); // set up level 5
	void SetLevel6(); // set up level 6
	void SetLevel7(); // set up level 7
	void SetLevel8(); // set up level 8
	void SetLevel9(); // set up level 9
	void SetLevel10(); // set up level 10

	void FixGrids(); // fix up/coordinate all 3 track grids
};
#endif
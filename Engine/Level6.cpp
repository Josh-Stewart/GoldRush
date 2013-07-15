/* A Level file - by Adam
Details held in CLevelData.h
*/

#include "CLevelData.h"

void CLevelData::SetLevel6()
{
	CurrentLevelNumber = 6;
	currentlevel.ObstacleAnimated = true;

	int i,j; // loop counters

	//////////////////////////////////////////////////////////////////////
	// set background filename string
	//////////////////////////////////////////////////////////////////////
	currentlevel.background = "gfx/background1.bmp";
	
	currentlevel.ObstacleImg = "gfx/crusher.bmp"; // name of obstacle image filename;
	currentlevel.ObstacleText1 = "Crusher.                             ";
	currentlevel.ObstacleText1 +="On levels with crushers, you must lay";
	currentlevel.ObstacleText1 +="your track to avoid being crushed. It";
	currentlevel.ObstacleText1 +="is sometimes easier to pass crushers ";
	currentlevel.ObstacleText1 +="at different speeds.";

	//coal material
	currentlevel.MaterialImg = "gfx/mat-coal.bmp"; // name of material image filename
	currentlevel.MaterialText1 = "Coal                                 ";
	currentlevel.MaterialText1 +="Coal is a hard blackish rock. It is  ";
	currentlevel.MaterialText1 +="found underground and is often used  ";
	currentlevel.MaterialText1 +="as fuel. Coal was used to power most ";
	currentlevel.MaterialText1 +="early power plants and steam trains  ";
	currentlevel.MaterialText1 +="and is still used widely for a fuel  ";
	currentlevel.MaterialText1 +="source today.";


	currentlevel.PowerupText0 = "Wheels";
	currentlevel.PowerupText1 = "Wheels1"; //
	currentlevel.PowerupText2 = "Wheels2";
	currentlevel.PowerupText3 = "Wheels3";

	currentlevel.PowerupImg1 = "gfx/Powerup16.bmp"; //
	currentlevel.PowerupImg2 = "gfx/Powerup17.bmp";
	currentlevel.PowerupImg3 = "gfx/Powerup18.bmp";

	currentlevel.PowerupType = 1;
	//////////////////////////////////////////////////////////////////////
	// track data grid
	//////////////////////////////////////////////////////////////////////
	
	tracktype temptracks[8][12] =  {	
			//	1		2		3		4		5		6		7		8		9		10		11		12		
/*	1	*/	{	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_FINISH},
/*	2	*/	{	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE},
/*	3	*/	{	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE},
/*	4	*/	{	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE},
/*	5	*/	{	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_CRUSH2,	T_NONE,	T_NONE,	T_CRUSH,	T_NONE,	T_NONE,	T_NONE},
/*	6	*/	{	T_START,T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_H,	T_NONE,	T_NONE,	T_H,	T_NONE,	T_NONE,	T_NONE},
/*	7	*/	{	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE},
/*	8	*/	{	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE}
	};

	for (i = 0; i < 8; i++) // set each element to temptracks
	{
		for (j = 0; j < 12; j++)
		{
			currentlevel.fixedtrack[i][j] = temptracks[i][j];
		}
	}

	//////////////////////////////////////////////////////////////////////
	// obstacles data grid
	//////////////////////////////////////////////////////////////////////

	obstacletype tempobstacles[8][12] =  {	
			//	1		2		3		4		5		6		7		8		9		10		11		12		
/*	1	*/	{	O_5,	O_1,	O_NONE,	O_NONE,	O_NONE,	O_1,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE},
/*	2	*/	{	O_1,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_1,	O_5,	O_NONE,	O_NONE},
/*	3	*/	{	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE},
/*	4	*/	{	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_4,	O_1,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE},
/*	5	*/	{	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE},
/*	6	*/	{	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_1,	O_NONE},
/*	7	*/	{	O_NONE,	O_NONE,	O_5,	O_NONE,	O_1,	O_NONE,	O_1,	O_NONE,	O_5,	O_NONE,	O_NONE,	O_NONE},
/*	8	*/	{	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE}
	};

	for (i = 0; i < 8; i++) // set each element to tempobstacles
	{
		for (j = 0; j < 12; j++)
		{
			currentlevel.obstacles[i][j] = tempobstacles[i][j];
		}
	}

	//////////////////////////////////////////////////////////////////////
	// pickups data grid
	//////////////////////////////////////////////////////////////////////

	pickuptype temppickups[8][12] =  {	
			//	1		2		3		4		5		6		7		8		9		10		11		12		
/*	1	*/	{	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_2,	P_NONE,	P_NONE,	P_NONE},
/*	2	*/	{	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE},
/*	3	*/	{	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_4,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE},
/*	4	*/	{	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE},
/*	5	*/	{	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE},
/*	6	*/	{	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_1,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE},
/*	7	*/	{	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_1,	P_NONE},
/*	8	*/	{	P_NONE,	P_NONE,	P_3,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE}
	};

	for (i = 0; i < 8; i++) // set each element to temppickups
	{
		for (j = 0; j < 12; j++)
		{
			currentlevel.pickups[i][j] = temppickups[i][j];
		}
	}

	//////////////////////////////////////////////////////////////////////
	// total pickups calculation
	//////////////////////////////////////////////////////////////////////

	currentlevel.totalpickups = 0;

	for (i = 0; i < 8; i++) // check each position of temppickups and add 1 if not none
	{
		for (j = 0; j < 12; j++)
		{
			if (temppickups[i][j] != P_NONE) currentlevel.totalpickups++;
		}
	}

	//////////////////////////////////////////////////////////////////////
	// Hazards data grid
	//////////////////////////////////////////////////////////////////////

		hazardtype temphazards[8][12] =  {	
			//	1		2		3		4		5		6		7		8		9		10		11		12		
/*	1	*/	{	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE},
/*	2	*/	{	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE},
/*	3	*/	{	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE},
/*	4	*/	{	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE},
/*	5	*/	{	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE},
/*	6	*/	{	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE},
/*	7	*/	{	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE},
/*	8	*/	{	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE}
	};

	for (i = 0; i < 8; i++) // set each element to temppickups
	{
		for (j = 0; j < 12; j++)
		{
			currentlevel.hazards[i][j] = temphazards[i][j];
		}
	}


	//////////////////////////////////////////////////////////////////////
	// track start and finish data
	//////////////////////////////////////////////////////////////////////

	currentlevel.start.x = 0; // start position
	currentlevel.start.y = 5;

	currentlevel.finish.x = 11; // finish position
	currentlevel.finish.y = 0;

	currentlevel.DynamiteTime = 0;
	currentlevel.BallCounter = 40;

}

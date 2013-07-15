/* A Level file - by Adam
Details held in CLevelData.h
*/

#include "CLevelData.h"

void CLevelData::SetLevel10()
{
	CurrentLevelNumber = 10;
	currentlevel.ObstacleAnimated = true;

	int i,j; // loop counters

	//////////////////////////////////////////////////////////////////////
	// set background filename string
	//////////////////////////////////////////////////////////////////////
	currentlevel.background = "gfx/background5.bmp";
	
	
	currentlevel.ObstacleImg = "gfx/crusher.bmp"; // name of obstacle image filename;
	currentlevel.ObstacleText1 = "Crusher.                             ";
	currentlevel.ObstacleText1 +="On levels with crushers, you must lay";
	currentlevel.ObstacleText1 +="your track to avoid being crushed. It";
	currentlevel.ObstacleText1 +="is sometimes easier to pass crushers ";
	currentlevel.ObstacleText1 +="at different speeds.";

	//silver material
	currentlevel.MaterialImg = "gfx/mat-silver.bmp"; // name of material image filename
	currentlevel.MaterialText1 = "Silver                               ";
	currentlevel.MaterialText1 +="Silver is a valuable silvery precious";
	currentlevel.MaterialText1 +="metal. Silver is used to create coins";
	currentlevel.MaterialText1 +="cutlery and most commonly jewellery. ";
//	currentlevel.MaterialText2 = "for you to stop"; // material text to be displayed


	currentlevel.PowerupText0 = "Wheels";
	currentlevel.PowerupText1 = "Wheels1"; //
	currentlevel.PowerupText2 = "Wheels2";
	currentlevel.PowerupText3 = "Wheels3";

	currentlevel.PowerupImg1 = "gfx/Powerup28.bmp"; //
	currentlevel.PowerupImg2 = "gfx/Powerup2.bmp";
	currentlevel.PowerupImg3 = "gfx/Powerup3.bmp";

	currentlevel.PowerupType = 1;
	//////////////////////////////////////////////////////////////////////
	// track data grid
	//////////////////////////////////////////////////////////////////////
	
	tracktype temptracks[8][12] =  {	
			//	1		2		3		4		5		6		7		8		9		10		11		12		
/*	1	*/	{	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE},
/*	2	*/	{	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE},
/*	3	*/	{	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE},
/*	4	*/	{	T_START,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_FINISH},
/*	5	*/	{	T_NONE,	T_NONE,	T_JUMP,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_CRUSH,	T_NONE,	T_NONE},
/*	6	*/	{	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_H,	T_NONE,	T_NONE},
/*	7	*/	{	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_CRUSH2,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE},
/*	8	*/	{	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_H,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE}
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
/*	1	*/	{	O_4,	O_1,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_1,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE},
/*	2	*/	{	O_1,	O_NONE,	O_NONE,	O_1,	O_5,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE},
/*	3	*/	{	O_NONE,	O_NONE,	O_1,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_4,	O_NONE,	O_NONE,	O_5,	O_1},
/*	4	*/	{	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_1,	O_NONE,	O_NONE,	O_NONE,	O_NONE},
/*	5	*/	{	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_1,	O_NONE,	O_NONE,	O_NONE,	O_NONE},
/*	6	*/	{	O_NONE,	O_NONE,	O_1,	O_5,	O_1,	O_NONE,	O_NONE,	O_4,	O_NONE,	O_NONE,	O_NONE,	O_NONE},
/*	7	*/	{	O_NONE,	O_NONE,	O_NONE,	O_1,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_1},
/*	8	*/	{	O_4,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_1,	O_5}
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
/*	1	*/	{	P_NONE,	P_NONE,	P_NONE,	P_4,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_3},
/*	2	*/	{	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE},
/*	3	*/	{	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE},
/*	4	*/	{	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE},
/*	5	*/	{	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE},
/*	6	*/	{	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_3,	P_NONE},
/*	7	*/	{	P_NONE,	P_NONE,	P_4,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE},
/*	8	*/	{	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE}
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
/*	4	*/	{	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_D},
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
	currentlevel.start.y = 3;

	currentlevel.finish.x = 11; // finish position
	currentlevel.finish.y = 3;

	currentlevel.DynamiteTime = 17;
	currentlevel.BallCounter = 0;

}

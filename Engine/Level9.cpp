/* A Level file - by Adam
Details held in CLevelData.h
*/

#include "CLevelData.h"

void CLevelData::SetLevel9()
{
	CurrentLevelNumber = 9;
	currentlevel.ObstacleAnimated = false;

	int i,j; // loop counters

	//////////////////////////////////////////////////////////////////////
	// set background filename string
	//////////////////////////////////////////////////////////////////////
	currentlevel.background = "gfx/background4.bmp";
	
	
	currentlevel.ObstacleImg = "gfx/gems.bmp"; // name of obstacle image filename;
	currentlevel.ObstacleText1 = "GEMS.                                ";
	currentlevel.ObstacleText1 +="Remember your goal, place your track ";
	currentlevel.ObstacleText1 +="to collect gems.Collect more gems for";
	currentlevel.ObstacleText1 +="more points."; //	currentlevel.ObstacleText2 = "empty"; // obstacle text to be displayed

	//gold material
	currentlevel.MaterialImg = "gfx/mat-ironore.bmp"; // name of material image filename
	currentlevel.MaterialText1 = "Iron-Ore                             ";
	currentlevel.MaterialText1 +="Iron-Ore is the impure form of Iron, ";
	currentlevel.MaterialText1 +="it is a reddish coloured stone that  ";
	currentlevel.MaterialText1 +="when refined into Iron, its a silvery";
	currentlevel.MaterialText1 +="metal used to create steel and tools.";
//	currentlevel.MaterialText2 = "for you to stop"; // material text to be displayed


	currentlevel.PowerupText0 = "Weight Reduction II  ";
	currentlevel.PowerupText1 = "Weight Reduction -4  ";
	currentlevel.PowerupText1 +="The weight of the    ";
	currentlevel.PowerupText1 +="cart affects how fast";
	currentlevel.PowerupText1 +="your cart  can travel";
	currentlevel.PowerupText1 +="at maximum speed and ";
	currentlevel.PowerupText1 +="how long it takes to ";
	currentlevel.PowerupText1 +="slow your cart down. ";
	currentlevel.PowerupText1 +="Reducing the weight  ";
	currentlevel.PowerupText1 +="of your cart enables ";
	currentlevel.PowerupText1 +="your cart to travel  ";
	currentlevel.PowerupText1 +="faster."; //

	currentlevel.PowerupText2 = "Weight Reduction -5  ";
	currentlevel.PowerupText2 +="The weight of the    ";
	currentlevel.PowerupText2 +="cart affects how fast";
	currentlevel.PowerupText2 +="your cart  can travel";
	currentlevel.PowerupText2 +="at maximum speed and ";
	currentlevel.PowerupText2 +="how long it takes to ";
	currentlevel.PowerupText2 +="slow your cart down. ";
	currentlevel.PowerupText2 +="Reducing the weight  ";
	currentlevel.PowerupText2 +="of your cart enables ";
	currentlevel.PowerupText2 +="your cart to travel  ";
	currentlevel.PowerupText2 +="faster."; //

	currentlevel.PowerupText3 = "Weight Reduction -6  ";
	currentlevel.PowerupText3 +="The weight of the    ";
	currentlevel.PowerupText3 +="cart affects how fast";
	currentlevel.PowerupText3 +="your cart  can travel";
	currentlevel.PowerupText3 +="at maximum speed and ";
	currentlevel.PowerupText3 +="how long it takes to ";
	currentlevel.PowerupText3 +="slow your cart down. ";
	currentlevel.PowerupText3 +="Reducing the weight  ";
	currentlevel.PowerupText3 +="of your cart enables ";
	currentlevel.PowerupText3 +="your cart to travel  ";
	currentlevel.PowerupText3 +="faster."; //

	currentlevel.PowerupImg1 = "gfx/Powerup16.bmp"; //
	currentlevel.PowerupImg2 = "gfx/Powerup17.bmp";
	currentlevel.PowerupImg3 = "gfx/Powerup18.bmp";

	currentlevel.PowerupType = 3;
	//////////////////////////////////////////////////////////////////////
	// track data grid
	//////////////////////////////////////////////////////////////////////
	
	tracktype temptracks[8][12] =  {	
			//	1		2		3		4		5		6		7		8		9		10		11		12		
/*	1	*/	{	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_CRUSH2,	T_NONE,	T_NONE},
/*	2	*/	{	T_START,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_H,	T_NONE,	T_NONE},
/*	3	*/	{	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE},
/*	4	*/	{	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE},
/*	5	*/	{	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE},
/*	6	*/	{	T_NONE,	T_NONE,	T_CRUSH,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE},
/*	7	*/	{	T_NONE,	T_NONE,	T_H,	T_NONE,	T_NONE,	T_JUMP,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_FINISH},
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
/*	1	*/	{	O_1,	O_5,	O_1,	O_5,	O_NONE,	O_NONE,	O_1,	O_1,	O_NONE,	O_NONE,	O_1,	O_5},
/*	2	*/	{	O_NONE,	O_NONE,	O_NONE,	O_1,	O_NONE,	O_NONE,	O_NONE,	O_5,	O_NONE,	O_NONE,	O_NONE,	O_NONE},
/*	3	*/	{	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_4,	O_NONE,	O_NONE,	O_4,	O_NONE},
/*	4	*/	{	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_1,	O_NONE,	O_NONE,	O_NONE},
/*	5	*/	{	O_NONE,	O_1,	O_1,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_1,	O_NONE,	O_NONE,	O_NONE,	O_NONE},
/*	6	*/	{	O_1,	O_4,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_1,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE},
/*	7	*/	{	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_1,	O_NONE,	O_NONE},
/*	8	*/	{	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_5,	O_NONE,	O_NONE,	O_4,	O_5,	O_NONE,	O_NONE}
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
/*	1	*/	{	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE},
/*	2	*/	{	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_1,	P_NONE},
/*	3	*/	{	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_4,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE},
/*	4	*/	{	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE},
/*	5	*/	{	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_3,	P_NONE,	P_NONE},
/*	6	*/	{	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE},
/*	7	*/	{	P_NONE,	P_2,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE},
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
	currentlevel.start.y = 1;

	currentlevel.finish.x = 11; // finish position
	currentlevel.finish.y = 6;

	currentlevel.DynamiteTime = 0;
	currentlevel.BallCounter = 30;

}

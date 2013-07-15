/* A Level file - by Adam
Details held in CLevelData.h
*/

#include "CLevelData.h"

void CLevelData::SetLevel7()
{
	CurrentLevelNumber = 7;
	currentlevel.ObstacleAnimated = false;

	int i,j; // loop counters

	//////////////////////////////////////////////////////////////////////
	// set background filename string
	//////////////////////////////////////////////////////////////////////
	currentlevel.background = "gfx/background2.bmp";
	
	
	currentlevel.ObstacleImg = "gfx/dynamitelookout.bmp"; // name of obstacle image filename;
	currentlevel.ObstacleText1 = "Dynamite                             "; // obstacle text to be displayed
	currentlevel.ObstacleText1 +="Some levels have dynamite at the end.";
	currentlevel.ObstacleText1 +="On these levels, you must finish the ";
	currentlevel.ObstacleText1 +="level before the counter on the fuse ";
	currentlevel.ObstacleText1 +="gets to zero.";

	currentlevel.MaterialImg = "gfx/mat-gold.bmp"; // name of material image filename -37 chars
	currentlevel.MaterialText1 = "Gold                                 ";
	currentlevel.MaterialText1 +="Gold is often used in the production ";
	currentlevel.MaterialText1 +="of coins, jewellery and even computer";
	currentlevel.MaterialText1 +="chips. Gold is a very valuable yellow";
	currentlevel.MaterialText1 +="precious metal;It is also very heavy.";
//	currentlevel.MaterialText2 = "for you to stop"; // material text to be displayed


	currentlevel.PowerupText0 = "Aerodynamics I       ";

	currentlevel.PowerupText1 = "Aero +4              ";
	currentlevel.PowerupText1 +="The Aerodynamics of  ";
	currentlevel.PowerupText1 +="your cart affect how ";
	currentlevel.PowerupText1 +="much the air can slow";
	currentlevel.PowerupText1 +="your cart down.Better";      
	currentlevel.PowerupText1 +="aerodynamics lessens ";
	currentlevel.PowerupText1 +="the amount air slows ";
	currentlevel.PowerupText1 +="your cart down and   ";
	currentlevel.PowerupText1 +="the faster you can go";
	currentlevel.PowerupText1 +="Aerodynamics are also";
	currentlevel.PowerupText1 +="used to make air hold";
	currentlevel.PowerupText1 +="your cart onto the   ";
	currentlevel.PowerupText1 +="track which means you";
	currentlevel.PowerupText1 +="can go faster into   ";
	currentlevel.PowerupText1 +="corners."; //

	currentlevel.PowerupText2 = "Aero +5              ";
	currentlevel.PowerupText2 +="The Aerodynamics of  ";
	currentlevel.PowerupText2 +="your cart affect how ";
	currentlevel.PowerupText2 +="much the air can slow";
	currentlevel.PowerupText2 +="your cart down.Better";      
	currentlevel.PowerupText2 +="aerodynamics lessens ";
	currentlevel.PowerupText2 +="the amount air slows ";
	currentlevel.PowerupText2 +="your cart down and   ";
	currentlevel.PowerupText2 +="the faster you can go";
	currentlevel.PowerupText2 +="Aerodynamics are also";
	currentlevel.PowerupText2 +="used to make air hold";
	currentlevel.PowerupText2 +="your cart onto the   ";
	currentlevel.PowerupText2 +="track which means you";
	currentlevel.PowerupText2 +="can go faster into   ";
	currentlevel.PowerupText2 +="corners."; //

	currentlevel.PowerupText3 = "Aero +6              ";
	currentlevel.PowerupText3 +="The Aerodynamics of  ";
	currentlevel.PowerupText3 +="your cart affect how ";
	currentlevel.PowerupText3 +="much the air can slow";
	currentlevel.PowerupText3 +="your cart down.Better";      
	currentlevel.PowerupText3 +="aerodynamics lessens ";
	currentlevel.PowerupText3 +="the amount air slows ";
	currentlevel.PowerupText3 +="your cart down and   ";
	currentlevel.PowerupText3 +="the faster you can go";
	currentlevel.PowerupText3 +="Aerodynamics are also";
	currentlevel.PowerupText3 +="used to make air hold";
	currentlevel.PowerupText3 +="your cart onto the   ";
	currentlevel.PowerupText3 +="track which means you";
	currentlevel.PowerupText3 +="can go faster into   ";
	currentlevel.PowerupText3 +="corners."; //

	currentlevel.PowerupImg1 = "gfx/Powerup13.bmp"; //
	currentlevel.PowerupImg2 = "gfx/Powerup14.bmp";
	currentlevel.PowerupImg3 = "gfx/Powerup15.bmp";

	currentlevel.PowerupType = 2;
	//////////////////////////////////////////////////////////////////////
	// track data grid
	//////////////////////////////////////////////////////////////////////
	
	tracktype temptracks[8][12] =  {	
			//	1		2		3		4		5		6		7		8		9		10		11		12		
/*	1	*/	{	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_CRUSH,	T_NONE,	T_NONE,	T_NONE,	T_NONE},
/*	2	*/	{	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_H,	T_NONE,	T_NONE,	T_NONE,	T_NONE},
/*	3	*/	{	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE},
/*	4	*/	{	T_START,T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE},
/*	5	*/	{	T_NONE,	T_NONE,	T_NONE,	T_CRUSH2,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE},
/*	6	*/	{	T_NONE,	T_NONE,	T_NONE,	T_H,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE},
/*	7	*/	{	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_FINISH},
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
/*	1	*/	{	O_4,	O_1,	O_1,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_1,	O_1},
/*	2	*/	{	O_NONE,	O_5,	O_NONE,	O_NONE,	O_NONE,	O_5,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_4},
/*	3	*/	{	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_1,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE},
/*	4	*/	{	O_NONE,	O_NONE,	O_NONE,	O_1,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE},
/*	5	*/	{	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE},
/*	6	*/	{	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_1,	O_NONE,	O_NONE,	O_1,	O_NONE,	O_1,	O_1},
/*	7	*/	{	O_NONE,	O_NONE,	O_1,	O_NONE,	O_NONE,	O_1,	O_NONE,	O_NONE,	O_5,	O_NONE,	O_NONE,	O_NONE},
/*	8	*/	{	O_NONE,	O_1,	O_5,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE}
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
/*	2	*/	{	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_2,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE},
/*	3	*/	{	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE},
/*	4	*/	{	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_1,	P_NONE},
/*	5	*/	{	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE},
/*	6	*/	{	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_4,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE},
/*	7	*/	{	P_NONE,	P_3,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE},
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
/*	7	*/	{	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_NONE,	H_D},
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
	currentlevel.finish.y = 6;

	currentlevel.DynamiteTime = 12;
	currentlevel.BallCounter = 0;

}

/* A Level file - by Adam
Details held in CLevelData.h
*/

#include "CLevelData.h"

void CLevelData::SetLevel1()
{
	CurrentLevelNumber = 1;
	currentlevel.ObstacleAnimated = false;
	int i,j; // loop counters

	//////////////////////////////////////////////////////////////////////
	// background filename string
	//////////////////////////////////////////////////////////////////////
	currentlevel.background = "gfx/background1.bmp";

	
	currentlevel.ObstacleImg = "gfx/gems.bmp"; // name of obstacle image filename;
	currentlevel.ObstacleText1 = "GEMS.                                ";
	currentlevel.ObstacleText1 +="Welcome to Goldrush, place your track";
	currentlevel.ObstacleText1 +="to collect gems.Collect more gems for";
	currentlevel.ObstacleText1 +="more points."; //	currentlevel.ObstacleText2 = "empty"; // obstacle text to be displayed

		//gold material
	currentlevel.MaterialImg = "gfx/mat-gold.bmp"; // name of material image filename -37 chars
	currentlevel.MaterialText1 = "Gold                                 ";
	currentlevel.MaterialText1 +="Gold is often used in the production ";
	currentlevel.MaterialText1 +="of coins, jewellery and even computer";
	currentlevel.MaterialText1 +="chips. Gold is a very valuable yellow";
	currentlevel.MaterialText1 +="precious metal;It is also very heavy.";
 // material text to be displayed
//	currentlevel.MaterialText2 = "for you to stop"; // material text to be displayed

	currentlevel.PowerupText0 = "Wheels I             ";

	currentlevel.PowerupText1 = "Wheels +1            ";
	currentlevel.PowerupText1 +="The wheels on your   ";
	currentlevel.PowerupText1 +="cart effect how well ";
	currentlevel.PowerupText1 +="it can grip the track";
	currentlevel.PowerupText1 +=",this is known as    ";
	currentlevel.PowerupText1 +="traction.The better  ";
	currentlevel.PowerupText1 +="traction your wheels ";
	currentlevel.PowerupText1 +="have,the faster your ";
	currentlevel.PowerupText1 +="cart can take off and";
	currentlevel.PowerupText1 +="stop.The traction of ";
	currentlevel.PowerupText1 +="your cart wheels also";
	currentlevel.PowerupText1 +="effects how well your";
	currentlevel.PowerupText1 +="cart can stay on the ";
	currentlevel.PowerupText1 +="track."; //

	currentlevel.PowerupText2 = "Wheels +2            ";
	currentlevel.PowerupText2 +="The wheels on your   ";
	currentlevel.PowerupText2 +="cart effect how well ";
	currentlevel.PowerupText2 +="it can grip the track";
	currentlevel.PowerupText2 +=",this is known as    ";
	currentlevel.PowerupText2 +="traction.The better  ";
	currentlevel.PowerupText2 +="traction your wheels ";
	currentlevel.PowerupText2 +="have,the faster your ";
	currentlevel.PowerupText2 +="cart can take off and";
	currentlevel.PowerupText2 +="stop.The traction of ";
	currentlevel.PowerupText2 +="your cart wheels also";
	currentlevel.PowerupText2 +="effects how well your";
	currentlevel.PowerupText2 +="cart can stay on the ";
	currentlevel.PowerupText2 +="track."; //

	currentlevel.PowerupText3 = "Wheels +3            ";
	currentlevel.PowerupText3 +="The wheels on your   ";
	currentlevel.PowerupText3 +="cart effect how well ";
	currentlevel.PowerupText3 +="it can grip the track";
	currentlevel.PowerupText3 +=",this is known as    ";
	currentlevel.PowerupText3 +="traction.The better  ";
	currentlevel.PowerupText3 +="traction your wheels ";
	currentlevel.PowerupText3 +="have,the faster your ";
	currentlevel.PowerupText3 +="cart can take off and";
	currentlevel.PowerupText3 +="stop.The traction of ";
	currentlevel.PowerupText3 +="your cart wheels also";
	currentlevel.PowerupText3 +="effects how well your";
	currentlevel.PowerupText3 +="cart can stay on the ";
	currentlevel.PowerupText3 +="track."; //

	currentlevel.PowerupImg1 = "gfx/Powerup1.bmp"; //
	currentlevel.PowerupImg2 = "gfx/Powerup2.bmp";
	currentlevel.PowerupImg3 = "gfx/Powerup3.bmp";

	currentlevel.PowerupType = 1;
	//////////////////////////////////////////////////////////////////////
	// track data grid
	//////////////////////////////////////////////////////////////////////
	
	tracktype temptracks[8][12] =  {	
			//	1		2		3		4		5		6		7		8		9		10		11		12		
/*	1	*/	{	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE},
/*	2	*/	{	T_START,T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE},
/*	3	*/	{	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE},
/*	4	*/	{	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE},
/*	5	*/	{	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE},
/*	6	*/	{	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE},
/*	7	*/	{	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE,	T_NONE, T_NONE,	T_NONE,	T_FINISH},
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
/*	1	*/	{	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_4,	O_NONE,	O_NONE,	O_1,	O_1},
/*	2	*/	{	O_NONE,	O_NONE,	O_NONE,	O_1,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_1},
/*	3	*/	{	O_1,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_1,	O_NONE,	O_NONE,	O_NONE},
/*	4	*/	{	O_NONE,	O_NONE,	O_NONE,	O_1,	O_NONE,	O_4,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE},
/*	5	*/	{	O_NONE,	O_NONE,	O_1,	O_1,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE},
/*	6	*/	{	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_1,	O_1},
/*	7	*/	{	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_4,	O_NONE,	O_NONE},
/*	8	*/	{	O_4,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE,	O_NONE}
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
/*	2	*/	{	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE},
/*	3	*/	{	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE},
/*	4	*/	{	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_1,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_2,	P_NONE},
/*	5	*/	{	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE},
/*	6	*/	{	P_NONE,	P_NONE,	P_2,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE},
/*	7	*/	{	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_1,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE,	P_NONE},
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
//i hate you adam
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
	currentlevel.BallCounter = 0;

}

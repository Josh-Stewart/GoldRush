/*
	This is an interactivly moving object in the game
	

	Author		: Jon Cahill
	Date		: 30th July 2002

*/

#ifndef BALL
#define BALL

#include "Sprite.h"

class Ball : public Sprite
{
private:

public:
	Ball();

	Ball(LPCSTR BitmapDir, int StartWeight, int Startx, int Starty, int Startz);

	void Draw();

	void CrusherCollision(int SpeedOffset, bool Crushed);

	virtual ~Ball();
};

#endif BALL
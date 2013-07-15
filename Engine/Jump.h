/*
	Inherites from the Animated Track and is used for a specific peice
	of track where the cart has to perform a jump.
	
	Author		: Jon Cahill
	Date		: 30th July 2002

*/

#ifndef JUMP
#define JUMP

#include "AnimatedTrack.h"
#include "Sprite.h"

class Jump : public AnimatedTrack
{
private:
	int RequiredSpeed;

public:
	Jump();

	Jump(LPCSTR BitmapDir, const char *text, int Startx, int Starty, int Startz, int Speed, int NumberFrames);

	//Draw the jump on the screen automatically animated it
	void Draw();

	//Performs the collision code when a collision is detected with the cart
	void OnCollision(Sprite *TheSprite);

	virtual ~Jump();
};

#endif //JUMP
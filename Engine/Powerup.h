/*	
	Author		: Jon Cahill
	Date		: 30th July 2002

*/

#ifndef POWERUP
#define POWERUP

#include "StaticObj.h"
#include "Sprite.h"
#include "Cart.h"

class Powerup : public StaticObj
{
private:

public:
	Powerup();

	Powerup(LPCSTR BitmapDir, const char *text, int Startx, int Starty, int Startz);

	void OnCollision(Sprite *TheSprite);

	virtual ~Powerup();
};

#endif POWERUP
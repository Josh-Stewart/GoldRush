/*
	Inherited from the static screen object this class has a timer
	and it counts down to a final explosion animation.
	
	Author		: Jon Cahill
	Date		: 30th July 2002

*/

#ifndef DYNAMITE
#define DYNAMITE

#include "StaticObj.h"
#include "Text.h"
#include "stdlib.h"
#include "Cart.h"

class Dynamite : public StaticObj
{
private:
	int FramesCounter;
	int Timer;
	int StartTime;
	string thestring;
	Text *TimeDisplay;
	bool DoCount;
	LPDIRECTDRAWSURFACE7 ExplosionBitmap;

public:
	Dynamite();

	Dynamite(LPCSTR BitmapDir, const char *text, int Startx, int Starty, int Startz, int Time);

	void Draw();

	void StartTimer();

	virtual ~Dynamite();

};

#endif //DYNAMITE
/*
	Basic class for which all static objects are derived.
	Can be used by itself to create objects with no real interaction 
	with the rest of the game.
	
	Author		: Jon Cahill
	Date		: 30th July 2002

*/

#ifndef STATIC_OBJ 
#define STATIC_OBJ 

#include "RenderedObject.h"

class StaticObj: public RenderedObject
{
protected:
	int x2, y2;

public:

	StaticObj();

	StaticObj(LPCSTR BitmapDir, int Startx, int Starty, int Startz, int Width, int Height, RECT Collision);
	StaticObj(LPCSTR BitmapDir, const char *text, int Startx, int Starty, int Startz, int Width, int Height, RECT Collision);
	StaticObj(LPCSTR BitmapDir, const char *text, int Startx, int Starty, int Startz, int Width, int Height);

	// Draws the object
	virtual void Draw();

	virtual ~StaticObj();
};


#endif //STATIC_OBJ 
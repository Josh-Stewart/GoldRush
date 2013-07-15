//cursor.h

#ifndef CURSOR 
#define CURSOR 

#include "globals.h"

class Cursor: public RenderedObject
{
protected:
	int CollX, CollY; //normally set to 0,0 for top left
	//LPDIRECTDRAWSURFACE7 SecondCursor;
	bool OriginalCursor;

public:

	Cursor();

	Cursor::Cursor(LPCSTR BitmapDir, const char *text,int Startx, int Starty, int Startz,
									int Width, int Height,
									int CollOffsetX, int CollOffsetY);
	
	/*
	void SetCursorSprite(LPCSTR BitmapDir,int Width, int Height,
									int CollisionX, int CollisionY);
	*/
	// Draws the cursor @ mouse_x,mouse_y
	void Draw();

	virtual ~Cursor();
};


#endif //CURSOR
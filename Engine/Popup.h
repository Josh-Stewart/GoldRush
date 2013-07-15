/*
	Basic Popup for menus etc.

	IS STILL INCOMPLETE
	
	Author		: Jon Cahill
	Date		: 30th July 2002

*/

#ifndef POPUP
#define POPUP

#include "StaticObj.h"

class Popup : public StaticObj
{
private:


public:
	Popup();

	Popup(LPCSTR BitmapDir, int Startx, int Starty, int Startz, int W, int H, int F,int SF);
	Popup(LPCSTR BitmapDir, int Startx, int Starty, int Startz, int W, int H, int F,int SF, RECT Collision);

	Popup(LPCSTR BitmapDir, const char *text, int Startx, int Starty, int Startz, int W, int H, int F,int SF);
	Popup(LPCSTR BitmapDir, const char *text, int Startx, int Starty, int Startz, int W, int H, int F,int SF, RECT Collision);

	int NextBmp();

//	Assign(RenderedObject RO);

	virtual ~Popup();

	

};

#endif //POPUP
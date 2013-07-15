/*
	Animated Popup for menus etc.

	IS STILL INCOMPLETE
	
	Author		: Jon Cahill
	Date		: 30th July 2002

*/

#ifndef ANIMATEDPOPUP
#define ANIMATEDPOPUP

#include "StaticObj.h"
#include "RenderedObject.h"

class AnimatedPopup : public RenderedObject
{
private:


public:
	AnimatedPopup();

	AnimatedPopup(LPCSTR BitmapDir, int Startx, int Starty, int Startz, int W, int H, int F,int SF);
	AnimatedPopup(LPCSTR BitmapDir, int Startx, int Starty, int Startz, int W, int H, int F,int SF, RECT Collision);

	AnimatedPopup(LPCSTR BitmapDir, const char *text, int Startx, int Starty, int Startz, int W, int H, int F,int SF);
	AnimatedPopup(LPCSTR BitmapDir, const char *text, int Startx, int Starty, int Startz, int W, int H, int F,int SF, RECT Collision);

	int NextBmp();

//	Assign(RenderedObject RO);
	void Draw();
	virtual ~AnimatedPopup();

	

};

#endif //POPUP
/*
	Abstract Class that all other rendered objects derive from.
	Stores the bitmap surface, the source and destination rectangles
	and the position values of the bitmap.
	
	Author		: Jon Cahill
	Date		: 30th July 2002

*/

#ifndef RENDERED_OBJECT
#define RENDERED_OBJECT

#include "globals.h"

class RenderedObject
{
protected:
	int x, y, z;
	int Height,Width,Frames;
	LPDIRECTDRAWSURFACE7 TheBitmap;
	RECT SourceRect, DestRect, CollBox;
	bool RenderThis;
	string ObjString;
	LPCSTR mysz; // need this for reloading the bitmap, stores the bitmaps filename/directory
	bool DeleteThis;
public:
	
	RenderedObject();
	
	//Pure Virtual function to make the class an abstract class
	virtual void Draw() = 0;
	
	// Move the bitmap an amount in the x and/or y direction
	void Move(int AmountX, int AmountY);
	
	// Moves the bitmap to a new location on the screen (absolute)
	virtual void MoveAbs(int NewX, int NewY);
	
	//Returns the collision box
	RECT IsCollision();

	//Returns if the object is in collision
	bool IsCollision(RenderedObject *CollWith);
	
	//Does what is needed when a collision occurs
	void OnCollision();

	//Returns XYZ values for use in searching renderlist
	int Getz();
	int Getx();
	int Gety();
	
	//Returns ObjString value for use in searching renderlist
	string GetString();

	// Returns if the object needs to be rendered
	bool NeedRender();
	
	// Sets if the object needs to be rendered or not
	void NeedRender(bool ToRender);

	bool NeedDelete();
	// Reloads the objects bitmap for surface recoverys
	void ReloadMyBitmap();

	virtual ~RenderedObject();

};

#endif //RENDERED_OBJECT
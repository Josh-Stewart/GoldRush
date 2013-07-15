/*
	Basic track piece with no animation.
	Stores information to the direction the cart travels on that bit of track.
	Also stores if the track piece is a finish or start peice.
	
	Author		: Jon Cahill
	Date		: 30th July 2002

*/

#ifndef TRACK
#define TRACK

#include "StaticObj.h"
#include "Sprite.h"

class Track : public StaticObj
{
protected:
	VectorDirection Vector;
	TrackType Type;
	int SpeedOffset;
	bool Reverse;
	int RequiredSpeed;

public:
	Track();

	Track(LPCSTR BitmapDir, int Startx, int Starty, int Startz, RECT Collision);
	Track(LPCSTR BitmapDir, const char *text, int Startx, int Starty, int Startz, RECT Collision);
	Track(LPCSTR BitmapDir, const char *text, int Startx, int Starty, int Startz, TrackType TheType, int SpeedAmount);
	// Flips the direction that the cart moves on the track
	void FlipVector();

	VectorDirection GetVector(){return Vector;};

	// Returns what peice type the track is
	TrackType WhatType(){return Type;};

	void Draw();

	//Peforms collision between the track and the cart
	virtual void OnCollision(Sprite *TheSprite);
	
	// Returns the speed offset of the track peice
	int GetSpeedOffset(){return SpeedOffset;}

	virtual ~Track();
};

#endif //TRACK
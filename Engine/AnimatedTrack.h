/*
	This is the basis for all peices of track which are animated. This class
	now stores a number of frames which is also added to the constructor. The
	Draw method is slightly different so as to update to a new frame during each 
	draw to provide the animation ability for the class.
	
	Author		: Jon Cahill
	Date		: 30th July 2002

*/

#ifndef ANIMATEDTRACK
#define ANIMATEDTRACK

#include "Track.h"


class AnimatedTrack : public Track
{
protected:
	int Frames;
	int Width;
	int Height;
	bool AnimateReverse;

public:
	AnimatedTrack();

	AnimatedTrack(LPCSTR BitmapDir, int Startx, int Starty, int Startz, int NumberFrames, RECT Collision);
	AnimatedTrack(LPCSTR BitmapDir, const char *text, int Startx, int Starty, int Startz,int width, int height, int NumberFrames, RECT Collision);
	
	// Draws the animated track and automatically selects the next frame in the animation
	void Draw();

	virtual ~AnimatedTrack();

};

#endif //ANIMATEDTRACK
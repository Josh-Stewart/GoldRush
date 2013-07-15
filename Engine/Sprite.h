/*
	Basic class for creating objects which move around the 
	screen and interact with other objects.
	
	Author		: Jon Cahill
	Date		: 30th July 2002

*/

#ifndef SPRITE
#define SPRITE

#include "RenderedObject.h"

class Sprite : public RenderedObject
{
protected:
	double Speed;

	int Weight;

	//Animation start positions
	int JumpStart;
	int JumpFallStart;
	int CrushStart;
	int RightDStart;
	int RightD2Start;
	int RightUStart;
	int RightU2Start;
	int LeftDStart;
	int LeftD2Start;
	int LeftUStart;
	int LeftU2Start;
	int UpStart;

	State Current;
	bool Animating;
	int Skipframe;

public:
	Status CurrentStatus;

	Sprite();

	double AdjustSpeed(int SpeedOffset);

	void SetSpeed(int NewSpeed);

	// Moves the Sprite to a new location on the screen (absolute)
	void MoveAbs(int NewX, int NewY);

	State GetState();

	void SetState(State NewState);

	void Push(int StartSpeed);

	virtual void CrusherCollision(int SpeedOffset, bool Crushed);

	void JumpCollision(int RequiredSpeed, int SpeedOffset, int Jumpx, int Jumpy, VectorDirection TheVector);

	void TrackCollision(int SpeedOffset, VectorDirection TheVector, TrackType TheType, int Trackx, int Tracky);

	void PowerupCollision();

	virtual ~Sprite();
};

#endif //SPRITE
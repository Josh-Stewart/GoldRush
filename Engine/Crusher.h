#ifndef CRUSHER
#define CRUSHER

#include "AnimatedTrack.h"
#include "Sprite.h"

class Crusher : public AnimatedTrack
{
private:

public:
	Crusher();

	Crusher(LPCSTR BitmapDir, const char *text, int Startx, int Starty, int Startz, int NumberFrames, int StartFrame);

	void OnCollision(Sprite *TheSprite);

	void SetFrame(int FrameNumber);

	void Draw();

	int GetFrame();

	~Crusher();

};

#endif CRUSHER
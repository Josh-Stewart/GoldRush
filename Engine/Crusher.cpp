#include "Crusher.h"

Crusher::Crusher()
{
}

Crusher::Crusher(LPCSTR BitmapDir, const char *text, int Startx, int Starty, int Startz, int NumberFrames, int StartFrame)
{
	DeleteThis = false;
	ObjString = text;
	//Direct Draw Initialization
	DDSURFACEDESC2 ddsd;
	INITIALIZE_DDRAW(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT | DDSD_CKSRCBLT;
	ddsd.dwWidth = 64 * NumberFrames;
	ddsd.dwHeight = 128;
	ddsd.ddckCKSrcBlt.dwColorSpaceLowValue = _RGB16BIT565(255, 0, 255);
	ddsd.ddckCKSrcBlt.dwColorSpaceHighValue = _RGB16BIT565(255, 0, 255);
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_VIDEOMEMORY;

	if(FAILED(lpdd->CreateSurface(&ddsd, &TheBitmap, NULL)))
	{
		// Failed making surface
	}

	x = Startx;
	y = Starty;
	z = Startz;

	mysz = BitmapDir;
	DDReLoadBitmap(TheBitmap, BitmapDir);

	//Setup the source Rectangle for animations
	SourceRect.top = 0;
	SourceRect.left = 0;
	SourceRect.right = 63;
	SourceRect.bottom = 127;

	// Other variables used with animated track objects
	SpeedOffset = 2;
	CollBox.left = x;
	CollBox.top = y;
	CollBox.right = x + 64;
	CollBox.bottom = y + 128;
	Frames = NumberFrames;
	Width = 64;
	if (StartFrame == 26) 
	{
		SourceRect.left = Width * 25;
		SourceRect.right = Width * 26 - 1;
	}
	RenderThis = true;
	
}

void Crusher::OnCollision(Sprite *TheSprite)
{
	if (SourceRect.left >= 0 && SourceRect.left <= 1088)
	{
		TheSprite->CrusherCollision(SpeedOffset, false);
	}
	else 
	{
		TheSprite->CrusherCollision(SpeedOffset, true);
	}

}

void Crusher::SetFrame(int FrameNumber)
{
//	SourceRect.top = 0;
	SourceRect.left = Width * (FrameNumber - 1);
	SourceRect.right = Width * FrameNumber - 1;
//	SourceRect.bottom = 127 * FrameNumber;

/*	SourceRect.top = 0;
	SourceRect.left = 0;
	SourceRect.right = 63 * FrameNumber;
	SourceRect.bottom = 127;*/
}

void Crusher::Draw()
{	
	lpddsback->BltFast(x, y, TheBitmap, &SourceRect, DDBLTFAST_SRCCOLORKEY);
	
	if (SourceRect.right >= Width * (Frames - 1)) SoundSystem.Playsound(13);

	if (SourceRect.right < Width * Frames - 1 && AnimateReverse == false)
	{
		SourceRect.left += Width;
		SourceRect.right += Width;
	}
	else if (SourceRect.right >= Width)
	{		
		AnimateReverse = true;
		SourceRect.left -= Width;
		SourceRect.right -= Width;
	}
	else if (SourceRect.left > 0 && AnimateReverse == true)
	{
		SourceRect.left -= Width;
		SourceRect.right -= Width;
	}
	else
	{
		AnimateReverse = false;
	}
}

int Crusher::GetFrame()
{
	return SourceRect.right / 64;
}

Crusher::~Crusher()
{
	if(TheBitmap)
	{
		TheBitmap->Release();
		TheBitmap = NULL;
	}
}

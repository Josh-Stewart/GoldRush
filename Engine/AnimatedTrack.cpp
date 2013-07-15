#include "AnimatedTrack.h"

AnimatedTrack::AnimatedTrack()
{
}

AnimatedTrack::AnimatedTrack(LPCSTR BitmapDir, int Startx, int Starty, int Startz, int NumberFrames, RECT Collision)
{
	DeleteThis = false;
	Width = 64;
	Height = 64;
	//Direct Draw Initialization
	DDSURFACEDESC2 ddsd;
	INITIALIZE_DDRAW(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT | DDSD_CKSRCBLT;
	ddsd.dwWidth = 64 * NumberFrames;
	ddsd.dwHeight = 64;
	ddsd.ddckCKSrcBlt.dwColorSpaceLowValue = _RGB16BIT565(255, 0, 255);
	ddsd.ddckCKSrcBlt.dwColorSpaceHighValue = _RGB16BIT565(255, 0, 255);

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
	SourceRect.bottom = 63;

	// Other variables used with animated track objects
	SpeedOffset = 2;
	CollBox = Collision;
	Frames = NumberFrames;
	RenderThis = true;

}
////////constructor for differing height/width animated tracks
AnimatedTrack::AnimatedTrack(LPCSTR BitmapDir, const char *text, int Startx, int Starty, int Startz,int width, int height, int NumberFrames, RECT Collision)
{
	DeleteThis = false;
	ObjString = text;
	Width = width;
	Height = height;
	//Direct Draw Initialization
	DDSURFACEDESC2 ddsd;
	INITIALIZE_DDRAW(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT | DDSD_CKSRCBLT;
	ddsd.dwWidth = (NumberFrames * Width);
	ddsd.dwHeight = Height;
	ddsd.ddckCKSrcBlt.dwColorSpaceLowValue = _RGB16BIT565(255, 0, 255);
	ddsd.ddckCKSrcBlt.dwColorSpaceHighValue = _RGB16BIT565(255, 0, 255);

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
	SourceRect.right = Width-1;
	SourceRect.bottom = Height-1;

	// Other variables used with animated track objects
	SpeedOffset = 2;
	CollBox = Collision;
	Frames = NumberFrames;
	RenderThis = true;
	AnimateReverse = false;

}

void AnimatedTrack::Draw()
{	
	lpddsback->BltFast(x, y, TheBitmap, &SourceRect, DDBLTFAST_SRCCOLORKEY);
	
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

AnimatedTrack::~AnimatedTrack()
{
	if(TheBitmap)
	{
		TheBitmap->Release();
		TheBitmap = NULL;
	}
}
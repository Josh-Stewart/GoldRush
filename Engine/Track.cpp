/*
	Basic track piece with no animation.
	Stores information to the direction the cart travels on that bit of track.
	Also stores if the track piece is a finish or start peice.
	
	Author		: Jon Cahill
	Date		: 30th July 2002

*/

#include "Track.h"

extern CLogging *log;

Track::Track()
{
}

Track::Track(LPCSTR BitmapDir, int Startx, int Starty, int Startz, RECT Collision)
{
	DeleteThis = false;
	//Direct Draw Initialization
	DDSURFACEDESC2 ddsd;
	INITIALIZE_DDRAW(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT | DDSD_CKSRCBLT;
	ddsd.dwWidth = 64;
	ddsd.dwHeight = 64;
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

	//Setup the source Rectangle for drawing
	SourceRect.top = 0;
	SourceRect.left = 0;
	SourceRect.right = 64;
	SourceRect.bottom = 64;

	//Other variables used for Track objects
	SpeedOffset = -1;
	CollBox = Collision;
	Type = Normal;
	RenderThis = true;

}
////added for search by text functions. Leigh
Track::Track(LPCSTR BitmapDir, const char *text, int Startx, int Starty, int Startz, RECT Collision)
{
	DeleteThis = false;
	ObjString = text;
	//Direct Draw Initialization
	DDSURFACEDESC2 ddsd;
	INITIALIZE_DDRAW(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT | DDSD_CKSRCBLT;
	ddsd.dwWidth = 64;
	ddsd.dwHeight = 64;
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

	//Setup the source Rectangle for drawing
	SourceRect.top = 0;
	SourceRect.left = 0;
	SourceRect.right = 64;
	SourceRect.bottom = 64;

	//Other variables used for Track objects
	SpeedOffset = -1;
	Type = Normal;
	CollBox = Collision;
	RenderThis = true;

}

////added for search by text functions. Leigh
Track::Track(LPCSTR BitmapDir, const char *text, int Startx, int Starty, int Startz, TrackType TheType, int SpeedAmount)
{
	DeleteThis = false;
	ObjString = text;
	//Direct Draw Initialization
	DDSURFACEDESC2 ddsd;
	INITIALIZE_DDRAW(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT | DDSD_CKSRCBLT;
	ddsd.dwWidth = 64;
	ddsd.dwHeight = 64;
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

	//Setup the source Rectangle for drawing
	SourceRect.top = 0;
	SourceRect.left = 0;
	SourceRect.right = 64;
	SourceRect.bottom = 64;

	//Other variables used for Track objects
	SpeedOffset = SpeedAmount;
	CollBox.top = Starty;
	CollBox.bottom = (Starty + 63);
	CollBox.left = Startx;
	CollBox.right = (Startx + 63);

	Type = TheType;
	RenderThis = true;
	Reverse = false;
	
	if (Type == Normal || Type == Start || Type == Finish || Type == SpeedUp || Type == SpeedDown)
		Vector = Right;
	else
		Vector = Down;

	string temp;
	temp = BitmapDir;

	if (temp == "gfx/TD.bmp")
	{
		Vector = Down;
	}
}

void Track::FlipVector()
{

	//log->LogWarning("VECTOR FLIPPED");
	
	if (Vector == Right)
	{
		Vector = Left;
	}
	else if (Vector == Left)
	{
		Vector = Right;
	}
	else if (Vector == Up)
	{
		Vector = Down;
	}
	else if (Vector = Down)
	{
		Vector = Up;
	}

}

void Track::OnCollision(Sprite *TheSprite)
{
	if (Vector == Up)
	{
		SpeedOffset = -4;
	}
	else if (Vector == Down)
	{
		SpeedOffset = 5;
	}
	TheSprite->TrackCollision(SpeedOffset, Vector, Type, x, y);
}

void Track::Draw()
{
	lpddsback->BltFast(x, y, TheBitmap, &SourceRect, DDBLTFAST_SRCCOLORKEY);
}

Track::~Track()
{
	if(TheBitmap)
	{
		TheBitmap->Release();
		TheBitmap = NULL;
	}
}
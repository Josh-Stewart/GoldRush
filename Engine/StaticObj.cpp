/*
	Basic class for which all static objects are derived.
	Can be used by itself to create objects with no real interaction 
	with the rest of the game.
	
	Author		: Jon Cahill
	Date		: 30th July 2002

*/

#include "StaticObj.h"

StaticObj::StaticObj()
{
}

StaticObj::StaticObj(LPCSTR BitmapDir, int Startx, int Starty, int Startz, int Width, int Height, RECT Collision)
{
	DeleteThis = false;
	//Direct Draw Initialization
	DDSURFACEDESC2 ddsd;
	INITIALIZE_DDRAW(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT | DDSD_CKSRCBLT;
	ddsd.dwWidth = Width;
	ddsd.dwHeight = Height;
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
	SourceRect.right = Width;
	SourceRect.bottom = Height;

	DestRect.top = y;
	DestRect.left = x;
	DestRect.right = Width - 1;
	DestRect.bottom = Height - 1;

	RenderThis = true;
}

// adam: added a constructor to assign object string
StaticObj::StaticObj(LPCSTR BitmapDir, const char *text, int Startx, int Starty, int Startz, int Width, int Height, RECT Collision)
{
	DeleteThis = false;
	ObjString = text;
	//Direct Draw Initialization
	DDSURFACEDESC2 ddsd;
	INITIALIZE_DDRAW(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT | DDSD_CKSRCBLT;
	ddsd.dwWidth = Width;
	ddsd.dwHeight = Height;
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
	SourceRect.right = Width;
	SourceRect.bottom = Height;

	DestRect.top = y;
	DestRect.left = x;
	DestRect.right = Width - 1;
	DestRect.bottom = Height - 1;

	RenderThis = true;
}

// adam: added constructor to assign objstring and a default collision box 
StaticObj::StaticObj(LPCSTR BitmapDir, const char *text, int Startx, int Starty, int Startz, int Width, int Height)
{
	DeleteThis = false;
	ObjString = text;
	//Direct Draw Initialization
	DDSURFACEDESC2 ddsd;
	INITIALIZE_DDRAW(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT | DDSD_CKSRCBLT;
	ddsd.dwWidth = Width;
	ddsd.dwHeight = Height;
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
	SourceRect.right = Width;
	SourceRect.bottom = Height;

	DestRect.top = 0;
	DestRect.left = 0;
	DestRect.right = 800;
	DestRect.bottom = 600;

	CollBox.top = Starty;
	CollBox.bottom = (Starty + Height);
	CollBox.left = Startx;
	CollBox.right = (Startx + Width);

	RenderThis = true;
}

void StaticObj::Draw()
{
	lpddsback->BltFast(x, y, TheBitmap, &SourceRect, DDBLTFAST_SRCCOLORKEY);
}

StaticObj::~StaticObj()
{
	if(TheBitmap)
	{
		TheBitmap->Release();
		TheBitmap = NULL;
	}
}

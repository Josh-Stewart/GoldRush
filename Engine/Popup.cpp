/*
	Basic Popup for menus etc.

	IS STILL INCOMPLETE
	
	Author		: Jon Cahill
	Date		: 30th July 2002

*/

#include "Popup.h"

Popup::Popup()
{
}

// this is now obsolete and needs to be removed
Popup::Popup(LPCSTR BitmapDir, int Startx, int Starty, int Startz,int W, int H, int F, int SF)
{
	DeleteThis = false;
	Width = W;
	Height = H;
	Frames = F;

	CollBox.top = Starty;
	CollBox.bottom = (Starty + H);
	CollBox.left = Startx;
	CollBox.right = (Startx +(W/F));

	DDSURFACEDESC2 ddsd;
	INITIALIZE_DDRAW(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT | DDSD_CKSRCBLT;
	ddsd.dwWidth = W;
	ddsd.dwHeight = H;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_VIDEOMEMORY;
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

	SourceRect.top = 0;
	SourceRect.left = (W/F)*SF;
	SourceRect.right = (W/F)*(SF+1);
	SourceRect.bottom = H;

	RenderThis = true;
}

Popup::Popup(LPCSTR BitmapDir, int Startx, int Starty, int Startz,int W, int H, int F,int SF, RECT Collision)
{

	
	DeleteThis = false;
	//Direct Draw Initialization
	DDSURFACEDESC2 ddsd;
	INITIALIZE_DDRAW(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
	ddsd.dwWidth = W;
	ddsd.dwHeight = H;

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
	SourceRect.left = (W/F)*SF;
	SourceRect.right = (W/F)*(SF+1);
	SourceRect.bottom = H;

	// Other varibles used for Popup class
	CollBox = Collision;
	Width = W;
	Height = H;
	Frames = F;
}

//new string versions of Popup constructors
Popup::Popup(LPCSTR BitmapDir, const char *text, int Startx, int Starty, int Startz, int W, int H, int F,int SF)
{
	DeleteThis = false;
	ObjString = text;

	Width = W;
	Height = H;
	Frames = F;

	CollBox.top = Starty;
	CollBox.bottom = (Starty + H);
	CollBox.left = Startx;
	CollBox.right = (Startx +(W/F));

	DDSURFACEDESC2 ddsd;
	INITIALIZE_DDRAW(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT | DDSD_CKSRCBLT;
	ddsd.dwWidth = W;
	ddsd.dwHeight = H;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_VIDEOMEMORY;
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

	SourceRect.top = 0;
	SourceRect.left = (W/F)*SF;
	SourceRect.right = (W/F)*(SF+1);
	SourceRect.bottom = H;

	RenderThis = true;
}
//new string versions of Popup constructors
Popup::Popup(LPCSTR BitmapDir, const char *text, int Startx, int Starty, int Startz, int W, int H, int F,int SF, RECT Collision)
{
	DeleteThis = false;
	ObjString = text;

	Width = W;
	Height = H;
	Frames = F;

	DDSURFACEDESC2 ddsd;
	INITIALIZE_DDRAW(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
	ddsd.dwWidth = W;
	ddsd.dwHeight = H;

	if(FAILED(lpdd->CreateSurface(&ddsd, &TheBitmap, NULL)))
	{
		// Failed making surface
	}

	x = Startx;
	y = Starty;
	z = Startz;

	mysz = BitmapDir;
	DDReLoadBitmap(TheBitmap, BitmapDir);

	SourceRect.top = 0;
	SourceRect.left = (W/F)*SF;
	SourceRect.right = (W/F)*(SF+1);
	SourceRect.bottom = H;

	CollBox = Collision;
	
	RenderThis = true;
}

Popup::NextBmp()
{
	if(SourceRect.right == Width)
	{
		SourceRect.left = 0;
		SourceRect.right = Width/Frames;
	}
	else
	{
		SourceRect.left = (SourceRect.left + Width/Frames);
		SourceRect.right = (SourceRect.right + Width/Frames);
	}
	return 0;
}



Popup::~Popup()
{
	if(TheBitmap)
	{
		TheBitmap->Release();
		TheBitmap = NULL;
	}
}




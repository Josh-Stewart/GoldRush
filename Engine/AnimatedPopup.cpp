/*
	Basic Popup for menus etc.

	IS STILL INCOMPLETE
	
	Author		: Jon Cahill
	Date		: 30th July 2002

*/

#include "AnimatedPopup.h"

AnimatedPopup::AnimatedPopup()
{
}

// this is now obsolete and needs to be removed
AnimatedPopup::AnimatedPopup(LPCSTR BitmapDir, int Startx, int Starty, int Startz,int W, int H, int F, int SF)
{

	Width = W;
	Height = H;
	Frames = F;
	DeleteThis = false;
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

AnimatedPopup::AnimatedPopup(LPCSTR BitmapDir, int Startx, int Starty, int Startz,int W, int H, int F,int SF, RECT Collision)
{

	

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
	DeleteThis = false;
}

//new string versions of Popup constructors
AnimatedPopup::AnimatedPopup(LPCSTR BitmapDir, const char *text, int Startx, int Starty, int Startz, int W, int H, int F,int SF)
{
	ObjString = text;

	Width = W;
	Height = H;
	Frames = F;
	DeleteThis = false;
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
AnimatedPopup::AnimatedPopup(LPCSTR BitmapDir, const char *text, int Startx, int Starty, int Startz, int W, int H, int F,int SF, RECT Collision)
{
	ObjString = text;

	Width = W;
	Height = H;
	Frames = F;
	DeleteThis = false;
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

AnimatedPopup::NextBmp()
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

void AnimatedPopup::Draw()
{	
	lpddsback->BltFast(x, y, TheBitmap, &SourceRect, DDBLTFAST_SRCCOLORKEY);
	
	if (SourceRect.right < Width - 1)
	{
		SourceRect.left += Width/Frames;
		SourceRect.right += Width/Frames;
	}
	else
	{
		
		RenderThis = false;
	}
}

AnimatedPopup::~AnimatedPopup()
{
	if(TheBitmap)
	{
		TheBitmap->Release();
		TheBitmap = NULL;
	}
}




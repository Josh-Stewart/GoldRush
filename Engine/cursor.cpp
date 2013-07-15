//cursor.cpp

#include "cursor.h"

Cursor::Cursor()
{
	DeleteThis = false;
	Cursor("gfx/cursor.bmp","Mouse", 0,0,100,32,32,0,0);
}

//most of these parameters arent all that nessecary but will allow us
//to expand the cursors functionality easily later.
//such as changing the cursor image and collision point.
Cursor::Cursor(LPCSTR BitmapDir, const char *text,int Startx, int Starty, int Startz,
								int Width, int Height,
								int CollOffsetX, int CollOffsetY)
{
	DeleteThis = false;
	ObjString = text;
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

	//mouse starting position
	mouse_x = Startx;
	mouse_y = Starty;
	z = Startz;
	
	//new collision XY
	//could re-write cursor collision to be more optimised to just search for a single point collision
	//atm we will just reuse the rendered_obj version
	CollX = CollOffsetX;
	CollY = CollOffsetY;

	//using collision box + offsets
	CollBox.top = Starty + CollOffsetY;
	CollBox.bottom = CollBox.top + 1;
	CollBox.left = Startx + CollOffsetX;
	CollBox.right = CollBox.left + 1;

	mysz = BitmapDir;
	DDReLoadBitmap(TheBitmap, BitmapDir);
	//OriginalCursor = TRUE;

	SourceRect.top = 0;
	SourceRect.left = 0;
	SourceRect.right = Width;
	SourceRect.bottom = Height;

	RenderThis = true;

	//this seems to work.. other methods were playing up.
	//this is one of many haxoring attempts to get the mouse to be "found" in the findcollision code
	string mousetext("mouse");
	ObjString = mousetext;

}

void Cursor::Draw()
{
	//each draw update the collision box too
	
	/* dodgy hack added by someone else ;) doesnt take into account different mouse cursor collision offsets
	CollBox.bottom = (mouse_y + 1);
	CollBox.top = (mouse_y);
	CollBox.left = (mouse_x);
	CollBox.right = (mouse_x + 1);
	*/

	//...but this version does
	CollBox.top = mouse_y + CollY;
	CollBox.bottom = CollBox.top + 1;
	CollBox.left = mouse_x + CollX;
	CollBox.right = CollBox.left + 1;

	//lpddsback->BltFast(mouse_x, mouse_y, TheBitmap, &SourceRect, DDBLTFAST_SRCCOLORKEY);

	// we need to Blt the cursor, Bltfast wont work on a clipped surface
	RECT temprect; // need to set up a destination rectangle

	temprect.left = mouse_x;
	temprect.right = mouse_x + SourceRect.right;
	temprect.top = mouse_y;
	temprect.bottom = mouse_y + SourceRect.bottom;

	// blt it to the PRIMARY, not the back since that isnt clipped
	lpddsprimary->Blt(&temprect, TheBitmap, &SourceRect, DDBLT_KEYSRC, &ddbltfx);
	
	/*
	if (OriginalCursor == TRUE)
		//need trans blt
		lpddsback->BltFast(mouse_x, mouse_y, TheBitmap, &SourceRect, FALSE);
	else 
		lpddsback->BltFast(mouse_x, mouse_y, SecondCursor, &SourceRect, FALSE);
	*/
}
/*
void Cursor::SetCursorSprite(LPCSTR BitmapDir,int Width, int Height,
										int CollisionX, int CollisionY)
{
	//delete old 2nd cursor
	if(SecondCursor)
	{
		SecondCursor->Release();
		SecondCursor = NULL;
	}
	// set to original cursor
	if (BitmapDir == NULL)
	{
		

	} else {// set new cursor
		
		DDSURFACEDESC2 ddsd;
		INITIALIZE_DDRAW(ddsd);
		ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
		ddsd.dwWidth = Width;
		ddsd.dwHeight = Height;

		if(FAILED(lpdd->CreateSurface(&ddsd, &TheBitmap, NULL)))
		{
			// Failed making surface
		}

		DDReLoadBitmap(SecondCursor, BitmapDir);
		OriginalCursor = FALSE;

		SourceRect.top = 0;
		SourceRect.left = 0;
		SourceRect.right = Width;
		SourceRect.bottom = Height;

		//new collision XY
		CollX = CollisionX;
		CollY = CollisionY;
	}
}*/

Cursor::~Cursor()
{
	if(TheBitmap)
	{
		TheBitmap->Release();
		TheBitmap = NULL;
	} /*
	if(SecondCursor)
	{
		SecondCursor->Release();
		SecondCursor = NULL;
	}*/
}
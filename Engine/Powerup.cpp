#include "Powerup.h"

Powerup::Powerup()
{
}

Powerup::Powerup(LPCSTR BitmapDir, const char *text, int Startx, int Starty, int Startz)
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

	CollBox.top = Starty;
	CollBox.bottom = (Starty +64);
	CollBox.left = Startx;
	CollBox.right = (Startx + 64);

	RenderThis = true;

}

void Powerup::OnCollision(Sprite *TheSprite)
{
	if (RenderThis == true)
	{
		RenderThis = false;
		((Cart*)TheSprite)->PowerupCollision();
	}
}

Powerup::~Powerup()
{
	if(TheBitmap)
	{
		TheBitmap->Release();
		TheBitmap = NULL;
	}
}
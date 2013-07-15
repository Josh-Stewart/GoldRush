#include "Jump.h"

extern CLogging *log;

Jump::Jump()
{
}

Jump::Jump(LPCSTR BitmapDir, const char *text, int Startx, int Starty, int Startz, int Speed, int NumberFrames)
{
	DeleteThis = false;
	ObjString = text;
	//Direct Draw Initialization
	DDSURFACEDESC2 ddsd;
	INITIALIZE_DDRAW(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT | DDSD_CKSRCBLT;
	ddsd.dwWidth = 192 * NumberFrames;
	ddsd.dwHeight = 64;
	ddsd.ddckCKSrcBlt.dwColorSpaceLowValue = _RGB16BIT565(255, 0, 255);
	ddsd.ddckCKSrcBlt.dwColorSpaceHighValue = _RGB16BIT565(255, 0, 255);
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_VIDEOMEMORY;

	if(FAILED(lpdd->CreateSurface(&ddsd, &TheBitmap, NULL)))
	{
		// Failed making surface
	}

	mysz = BitmapDir;
	DDReLoadBitmap(TheBitmap, BitmapDir);

	// Set Starting position
	x = Startx;
	y = Starty;
	z = Startz;
		
	//Set the source Rectangle
	SourceRect.top = 0;
	SourceRect.left = 0;
	SourceRect.right = 192;
	SourceRect.bottom = 64;
	
	//Speed adjustment settings
	SpeedOffset = 2;
	RequiredSpeed = Speed;

	//Setup collision box
	CollBox.left = x;
	CollBox.top = y;
	CollBox.right = x + 192;
	CollBox.bottom = y + 64;
	
	//Setup animation information
	Frames = NumberFrames;
	Type = TheJump;
	Vector = Right;

	RenderThis = true;

}

void Jump::Draw()
{
	lpddsback->BltFast(x, y, TheBitmap, &SourceRect, DDBLTFAST_SRCCOLORKEY);
	
	if (SourceRect.right < 192 * Frames - 1)
	{
		SourceRect.left += 192;
		SourceRect.right += 192;
	}
	else
	{
		SourceRect.left = 0;
		SourceRect.right = 192;
	}

}

void Jump::OnCollision(Sprite *TheSprite)
{
	TheSprite->JumpCollision(RequiredSpeed, SpeedOffset, x, y, Vector);

}

Jump::~Jump()
{
	if(TheBitmap)
	{
		TheBitmap->Release();
		TheBitmap = NULL;
	}
}
#include "Dynamite.h"

extern CLogging *log;

Dynamite::Dynamite()
{
}

Dynamite::Dynamite(LPCSTR BitmapDir, const char *text, int Startx, int Starty, int Startz, int Time)
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

	INITIALIZE_DDRAW(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT | DDSD_CKSRCBLT;
	ddsd.dwWidth = 640;
	ddsd.dwHeight = 64;
	ddsd.ddckCKSrcBlt.dwColorSpaceLowValue = _RGB16BIT565(255, 0, 255);
	ddsd.ddckCKSrcBlt.dwColorSpaceHighValue = _RGB16BIT565(255, 0, 255);
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_VIDEOMEMORY;

	if(FAILED(lpdd->CreateSurface(&ddsd, &ExplosionBitmap, NULL)))
	{
		// Failed making surface
	}

	mysz = BitmapDir;
	DDReLoadBitmap(TheBitmap, BitmapDir);
	DDReLoadBitmap(ExplosionBitmap, "gfx/Explosions.bmp");

	SourceRect.left = 0;
	SourceRect.top = 0;
	SourceRect.bottom = 63;
	SourceRect.right = 63;

	RenderThis = true;
	DoCount = false;
	x = Startx;
	y = Starty;
	z = Startz;

	FramesCounter = 0;
	Timer = Time;
	StartTime = Time;
	char temp[2];
	_itoa(Timer, temp, 10);
	thestring = temp; 

	TimeDisplay = new Text(18,"Dynamite Text", thestring, x + 25, y + 25, z, 200, 80,false);
}

void Dynamite::Draw()
{
	if (DoCount)
	{
		if (FramesCounter != 30)
			FramesCounter++;
		else
		{
			Timer--;
			FramesCounter = 0;
			char temp[2];
			_itoa(Timer, temp, 10);
			thestring = temp; 
			TimeDisplay->UpdateText(thestring);
		}

	}

	if (TheCart->GetState() == Failed) 
	{
		Timer = StartTime;
		DoCount = false;
		char temp[2];
		_itoa(Timer, temp, 10);
		thestring = temp;
		TimeDisplay->UpdateText(thestring);
	}

	if (Timer == 0)
	{
		if(DoCount == true) SoundSystem.Playsound(10); //play explosion sound
		TheCart->SetState(Failed);
		if(DoCount == true) OrderedConsoleInsert("The Dynamite Blew up the Track.");
		DoCount = false;
		lpddsback->BltFast(x, y, ExplosionBitmap, &SourceRect, DDBLTFAST_SRCCOLORKEY);
		if (SourceRect.left < 640)
		{
			SourceRect.left += 64;
			SourceRect.right += 64;
		}


	}
	else
	{
		lpddsback->BltFast(x, y, TheBitmap, &SourceRect, DDBLTFAST_SRCCOLORKEY);
		TimeDisplay->Draw();
	}

	
	
}

void Dynamite::StartTimer()
{
	SourceRect.left = 0;
	SourceRect.top = 0;
	SourceRect.bottom = 63;
	SourceRect.right = 63;
	Timer = StartTime;
	FramesCounter = 0;
	DoCount = true;
	char temp[2];
	_itoa(Timer, temp, 10);
	thestring = temp;
	TimeDisplay->UpdateText(thestring);
}

Dynamite::~Dynamite()
{

	delete TimeDisplay;

	if (ExplosionBitmap)
	{
		ExplosionBitmap->Release();
		ExplosionBitmap = NULL;
	}
	
	if(TheBitmap)
	{
		TheBitmap->Release();
		TheBitmap = NULL;
	}
}
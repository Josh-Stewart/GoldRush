#include "Ball.h"

Ball::Ball()
{
}

Ball::Ball(LPCSTR BitmapDir, int StartWeight, int Startx, int Starty, int Startz)
{
	DeleteThis = false;
	//Direct Draw Initialization
	DDSURFACEDESC2 ddsd;
	INITIALIZE_DDRAW(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT | DDSD_CKSRCBLT;
	ddsd.dwWidth = 3072;
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

	//Setup the source Rectangle for animations
	SourceRect.top = 0;
	SourceRect.left = 0;
	SourceRect.right = 64;
	SourceRect.bottom = 64;

	CollBox.top = y + 32;
	CollBox.bottom = y + 32;
	CollBox.left = x + 32;
	CollBox.right = x + 32;

	// Default settings for Cart
	RenderThis = true;
	Weight = StartWeight;
	x = Startx;
	y = Starty;
	x = Startz;
	Skipframe = 0;

	//Start positions of all the animations
	LeftU2Start = 1920;
	RightU2Start = 1920;
	LeftUStart = 2496;
	RightUStart = 2496;
	LeftD2Start = 2496;
	RightD2Start = 2496;
	LeftDStart = 3072;
	RightDStart = 3072;

	JumpStart = 0;
	JumpFallStart = 0;
	CrushStart = 0;
}

void Ball::CrusherCollision(int SpeedOffset, bool Crushed)
{
	AdjustSpeed(SpeedOffset);
	if (Crushed == true)
	{
		Current = Failed;
	}
}

void Ball::Draw()
{
	// Peform correct animation when on regular track heading right
	if (CurrentStatus == RegularR) 
	{
		lpddsback->BltFast(x, y, TheBitmap, &SourceRect, DDBLTFAST_SRCCOLORKEY);
		if (SourceRect.right < LeftU2Start)
		{
			SourceRect.left += 64;
			SourceRect.right += 64;
		}
		else
		{
			SourceRect.left = 0;
			SourceRect.right = 64;
		}
		Move(Speed, 0);
		
	}
	// Peform correct animation when on regular track heading left
	else if (CurrentStatus == RegularL)
	{
		INITIALIZE_DDRAW(ddbltfx);
		ddbltfx.dwDDFX = DDBLTFX_MIRRORLEFTRIGHT;
		DestRect.left = x;
		DestRect.top = y;
		DestRect.right = x + 64;
		DestRect.bottom = y + 64;
		
		lpddsback->Blt(&DestRect, TheBitmap, &SourceRect, DDBLT_KEYSRC | DDBLT_DDFX, &ddbltfx);;
		if (SourceRect.right < LeftU2Start)
		{
			SourceRect.left += 64;
			SourceRect.right += 64;
		}
		else
		{
			SourceRect.left = 0;
			SourceRect.right = 64;
		}
		Move(-Speed, 0);
	}
	// Peform correct animation when on regular track heading down
	else if (CurrentStatus == RegularD)
	{
		if (SourceRect.right < LeftU2Start)
		{
			SourceRect.left += 64;
			SourceRect.right += 64;
		}
		
		if (SourceRect.left == LeftU2Start)
		{
			SourceRect.left = 0;
			SourceRect.right = 64;
		}
		lpddsback->BltFast(x, y, TheBitmap, &SourceRect, DDBLTFAST_SRCCOLORKEY);
		Move(0, Speed);
	}
	// Peform correct animation when on regular track heading up
	else if (CurrentStatus == RegularU)
	{
		DestRect.left = x;
		DestRect.top = y;
		DestRect.right = x + 64;
		DestRect.bottom = y + 64;
				
		if (SourceRect.right < LeftU2Start)
		{
			SourceRect.left += 64;
			SourceRect.right += 64;
		}
		else
		{
			SourceRect.left = 0;
			SourceRect.right = 64;
		}
		
		lpddsback->BltFast(x, y, TheBitmap, &SourceRect, DDBLTFAST_SRCCOLORKEY);
		Move(0, -Speed);
	}
	// Perform correct animation for right down heading down
	else if (CurrentStatus == RightD)
	{	
		INITIALIZE_DDRAW(ddbltfx);
		DestRect.left = x;
		DestRect.top = y;
		DestRect.right = x + 64;
		DestRect.bottom = y + 64;

		if (SourceRect.left < RightD2Start)
		{
			SourceRect.left = RightD2Start;
			SourceRect.right = RightD2Start + 64;
			lpddsback->BltFast(x, y, TheBitmap, &SourceRect, DDBLTFAST_SRCCOLORKEY);
		}
		else if (SourceRect.right == RightDStart)
		{
			CurrentStatus = RegularR;
			SourceRect.left = 0;
			SourceRect.right = 64;
			Move(33, 0);
			Animating = false;
		}
		else
		{
			if (Speed < 2 && Skipframe == 0)
			{
				Skipframe = 1;
			}
			else if (Speed > 6 && Skipframe == 0)
			{
				SourceRect.left += 128;
				SourceRect.right += 128;	
				if (SourceRect.right > RightDStart)
				{
					SourceRect.left = RightDStart - 64;
					SourceRect.right = RightDStart;
				}
			}
			else
			{
				Skipframe = 0;
				SourceRect.left += 64;
				SourceRect.right += 64;
			}
			lpddsback->BltFast(x, y, TheBitmap, &SourceRect, DDBLTFAST_SRCCOLORKEY);
		}
	}
	//Perform correct animation for left down heading down
	else if (CurrentStatus == LeftD)
	{
		INITIALIZE_DDRAW(ddbltfx);
		ddbltfx.dwDDFX = DDBLTFX_MIRRORLEFTRIGHT;
		DestRect.left = x;
		DestRect.top = y;
		DestRect.right = x + 64;
		DestRect.bottom = y + 64;

		if (SourceRect.right < LeftD2Start)
		{
			SourceRect.left = LeftD2Start;
			SourceRect.right = LeftD2Start + 64;
			lpddsback->Blt(&DestRect, TheBitmap, &SourceRect, DDBLT_KEYSRC | DDBLT_DDFX, &ddbltfx);
		}
		else if (SourceRect.right == LeftDStart)
		{
			CurrentStatus = RegularR;
			SourceRect.left = 0;
			SourceRect.right = 64;
			Move(-33, 0);
			Animating = false;
		}
		else 
		{
			if (Speed < 2 && Skipframe == 0)
			{
				Skipframe = 1;
			}
			else if (Speed > 6 && Skipframe == 0)
			{
				SourceRect.left += 128;
				SourceRect.right += 128;	
				if (SourceRect.right > LeftDStart)
				{
					SourceRect.left = LeftDStart - 64;
					SourceRect.right = LeftDStart;
				}
			}
			else
			{
				Skipframe = 0;
				SourceRect.left += 64;
				SourceRect.right += 64;
			}
			lpddsback->Blt(&DestRect, TheBitmap, &SourceRect, DDBLT_KEYSRC | DDBLT_DDFX, &ddbltfx);
		}
	}
	//Perform correct animation for right down heading up
	else if (CurrentStatus == RightD2)
	{
		DestRect.left = x;
		DestRect.top = y;
		DestRect.right = x + 64;
		DestRect.bottom = y + 64;

		if (SourceRect.right < RightD2Start)
		{
			SourceRect.left = RightDStart - 64;
			SourceRect.right = RightDStart;
			lpddsback->BltFast(x, y, TheBitmap, &SourceRect, DDBLTFAST_SRCCOLORKEY);
		}
		else if (SourceRect.left == RightD2Start)
		{
			CurrentStatus = RegularR;
			SourceRect.left = 0;
			SourceRect.right = 64;
			Move(0, -33);
			Animating = false;
		}
		else 
		{
			if (Speed < 2 && Skipframe == 0)
			{
				Skipframe = 1;
			}
			else if (Speed > 6 && Skipframe == 0)
			{
				SourceRect.left -= 128;
				SourceRect.right -= 128;
				if (SourceRect.left < RightD2Start)
				{
					SourceRect.left = RightD2Start;
					SourceRect.right = RightD2Start + 64;
				}
			}
			else
			{
				Skipframe = 0;
				SourceRect.left -= 64;
				SourceRect.right -=64;
			}
			lpddsback->BltFast(x, y, TheBitmap, &SourceRect, DDBLTFAST_SRCCOLORKEY);
		}
	}
	//Perform correct animation for left down heading up
	else if (CurrentStatus == LeftD2)
	{
		INITIALIZE_DDRAW(ddbltfx);
		ddbltfx.dwDDFX = DDBLTFX_MIRRORLEFTRIGHT;
		DestRect.left = x;
		DestRect.top = y;
		DestRect.right = x + 64;
		DestRect.bottom = y + 64;

		if (SourceRect.right < LeftD2Start)
		{
			SourceRect.left = LeftDStart - 64;
			SourceRect.right = LeftDStart;
			lpddsback->Blt(&DestRect, TheBitmap, &SourceRect, DDBLT_KEYSRC | DDBLT_DDFX, &ddbltfx);
		}
		else if (SourceRect.left == LeftD2Start)
		{
			CurrentStatus = RegularR;
			SourceRect.left = 0;
			SourceRect.right = 64;
			Move(0, -33);
			Animating = false;
		}
		else 
		{
			if (Speed < 2 && Skipframe == 0)
			{
				Skipframe = 1;
			}
			else if (Speed > 6 && Skipframe == 0)
			{
				SourceRect.left -= 128;
				SourceRect.right -= 128;
				if (SourceRect.left < LeftD2Start)
				{
					SourceRect.left = LeftD2Start;
					SourceRect.right = LeftD2Start + 64;
				}
			}
			else
			{
				Skipframe = 0;
				SourceRect.left -= 64;
				SourceRect.right -= 64;
			}
			lpddsback->Blt(&DestRect, TheBitmap, &SourceRect, DDBLT_KEYSRC | DDBLT_DDFX, &ddbltfx);
		}
	
	}
	//Perform correct animation for right up heading up
	else if (CurrentStatus == RightU)
	{
		INITIALIZE_DDRAW(ddbltfx);
		ddbltfx.dwDDFX = DDBLTFX_MIRRORLEFTRIGHT;
		DestRect.left = x;
		DestRect.top = y;
		DestRect.right = x + 64;
		DestRect.bottom = y + 64;

		if (SourceRect.right < RightU2Start || SourceRect.right > RightUStart)
		{
			SourceRect.left = RightUStart - 64;
			SourceRect.right = RightUStart;
			lpddsback->Blt(&DestRect, TheBitmap, &SourceRect, DDBLT_KEYSRC | DDBLT_DDFX, &ddbltfx);
		}
		else if (SourceRect.left == RightU2Start)
		{
			CurrentStatus = RegularR;
			SourceRect.left = 0;
			SourceRect.right = 64;
			Move(33, 0);
			Animating = false;
		}
		else 
		{
			if (Speed < 2 && Skipframe == 0)
			{
				Skipframe = 1;
			}
			else if (Speed > 6 && Skipframe == 0)
			{
				SourceRect.left -= 128;
				SourceRect.right -= 128;
				if (SourceRect.left < RightU2Start)
				{
					SourceRect.left = RightU2Start;
					SourceRect.right = RightU2Start + 64;
				}
			}
			else
			{
				Skipframe = 0;
				SourceRect.left -= 64;
				SourceRect.right -= 64;
			}
			lpddsback->Blt(&DestRect, TheBitmap, &SourceRect, DDBLT_KEYSRC | DDBLT_DDFX, &ddbltfx);
		}
	}
	//Perform correct animation for right up heading down
	else if (CurrentStatus == RightU2)
	{
		INITIALIZE_DDRAW(ddbltfx);
		ddbltfx.dwDDFX = DDBLTFX_MIRRORLEFTRIGHT;
		DestRect.left = x;
		DestRect.top = y;
		DestRect.right = x + 64;
		DestRect.bottom = y + 64;
	
		if (SourceRect.right < RightU2Start)
		{
			
			
			SourceRect.left = RightU2Start;
			SourceRect.right = RightU2Start + 64;
			lpddsback->Blt(&DestRect, TheBitmap, &SourceRect, DDBLT_KEYSRC | DDBLT_DDFX, &ddbltfx);
		}
		else if(SourceRect.right == RightUStart)
		{
			CurrentStatus = RegularR;
			SourceRect.left = 0;
			SourceRect.right = 63;
			Move(0, 33);
			Animating = false;
		}
		else
		{
			if (Speed < 2 && Skipframe == 0)
			{
				Skipframe = 1;
			}
			else if (Speed > 6 && Skipframe == 0)
			{
				SourceRect.left += 128;
				SourceRect.right += 128;	
				if (SourceRect.right > RightUStart)
				{
					SourceRect.left = RightUStart - 64;
					SourceRect.right = RightUStart;
				}
			}
			else
			{
				Skipframe = 0;
				SourceRect.left += 64;
				SourceRect.right += 64;
			}
			lpddsback->Blt(&DestRect, TheBitmap, &SourceRect, DDBLT_KEYSRC | DDBLT_DDFX, &ddbltfx);
		}
	}
	//Perform correct animation for left up heading up
	else if (CurrentStatus == LeftU)
	{
		INITIALIZE_DDRAW(ddbltfx);
		DestRect.left = x;
		DestRect.top = y;
		DestRect.right = x + 64;
		DestRect.bottom = y + 64;

		if (SourceRect.right < LeftU2Start)
		{
			SourceRect.left = LeftUStart - 64;
			SourceRect.right = LeftUStart;
			lpddsback->Blt(&DestRect, TheBitmap, &SourceRect, DDBLT_KEYSRC | DDBLT_DDFX | DDBLT_ALPHAEDGEBLEND, &ddbltfx);
		}
		else if (SourceRect.left == LeftU2Start)
		{
			CurrentStatus = RegularR;
			SourceRect.left = 0;
			SourceRect.right = 64;
			Move(-33,0);
			Animating = false;

		}
		else 
		{
			if (Speed < 2 && Skipframe == 0)
			{
				Skipframe = 1;
			}
			else if (Speed > 6 && Skipframe == 0)
			{
				SourceRect.left -= 128;
				SourceRect.right -= 128;
				if (SourceRect.left < LeftU2Start)
				{
					SourceRect.left = LeftU2Start;
					SourceRect.right = LeftU2Start + 64;
				}
			}
			else
			{
				Skipframe = 0;
				SourceRect.left -= 64;
				SourceRect.right -= 64;
			}
			lpddsback->Blt(&DestRect, TheBitmap, &SourceRect, DDBLT_KEYSRC | DDBLT_DDFX, &ddbltfx);
		}
	}
	//Perfrom correct animation for left up heading down
	else if (CurrentStatus == LeftU2)
	{
	
		if (SourceRect.right < LeftU2Start)
		{
			SourceRect.left = LeftU2Start;
			SourceRect.right = LeftU2Start + 64;
			lpddsback->BltFast(x, y, TheBitmap, &SourceRect, DDBLTFAST_SRCCOLORKEY);
		}
		else if (SourceRect.right == LeftUStart)
		{
			CurrentStatus = RegularR;
			SourceRect.left = 0;
			SourceRect.right = 63;
			Move(0, 33);
			Animating = false;
		}
		else 
		{
			if (Speed < 2 && Skipframe == 0)
			{
				Skipframe = 1;
			}
			else if (Speed > 6 && Skipframe == 0)
			{
				SourceRect.left += 128;
				SourceRect.right += 128;	
				if (SourceRect.right > LeftUStart)
				{
					SourceRect.left = LeftUStart - 64;
					SourceRect.right = LeftUStart;
				}
			}
			else
			{
				Skipframe = 0;
				SourceRect.left += 64;
				SourceRect.right += 64;
			}
			lpddsback->BltFast(x, y, TheBitmap, &SourceRect, DDBLTFAST_SRCCOLORKEY);
		}
	}
	else if (CurrentStatus == AJumpR)
	{
		Current = Failed;
	}
}

Ball::~Ball()
{
	if(TheBitmap)
	{
		TheBitmap->Release();
		TheBitmap = NULL;
	}
}
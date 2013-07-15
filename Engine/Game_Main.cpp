/* All Game logic for one frame goes here

  Only 1 frame worth of code as to not starve the message loop

  Author	: Jon Cahill
  Date		: 1st July 2002
*/
#include "Game_Main.h"

//render timer global in game_main
DWORD rendertimer;
DWORD fpstimer = 0;
int fps = 0;
int lastfps;

extern CLogging *log;

int Game_Main()
{
	if (useperformancetimer) // if performance timer is working
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&currentclock);
		if((currentclock - lastclock) * ms_rate < 33)
		{
			return 1;
		}
		QueryPerformanceCounter((LARGE_INTEGER*)&lastclock); // set the last value
	}
	else // if performance timer isnt working use old method
	{
	//return from render unless 33 milliseconds has passed since last render
	if ((GetTickCount() - rendertimer) < 33) 
		{
			return 1;
		}
		//update gameloop/render timer
		rendertimer = GetTickCount();
	}

	UpdateInput();
	
/////////////////////////////////////////////////////////////////////////////////
// Collision Detection Stuff on Mouse Buttons
/////////////////////////////////////////////////////////////////////////////////

	MenuSystem.MenuCollider();
	
	if (mouse_1 == 3)
	{
		dmsg(0,0,"     [B1]");

	}

	if (mouse_2 == 2)
	{


	} else {

	}


	Render();
	if (TheCart->GetState() == Running)
	{
		Sprite_Animation();
	}
	
	return 0;
} 


// DEBUG MESSAGE - takes printf formatted strings / arguments
// and prints them at top of screen 
void dmsg(int x, int y, const char *format, ...)
{
	HDC hdc;
	
	int ret;
	char buf[512];
	
	va_list ap;
	va_start(ap, format);
	//vsprintf(buf, format,ap); //buffer overflows R us
	ret = _vsnprintf( buf, sizeof(buf), format, ap);
	va_end(ap);
		
	if (lpddsback->GetDC(&hdc) == DD_OK) 
	{ 
    SetBkColor(hdc, RGB(0, 0, 255)); 
    SetTextColor(hdc, RGB(255, 255, 0)); 
    if(ret == -1){
		TextOut(hdc, 0, 0, "dmsg too long for buffer", lstrlen("dmsg too long for buffer"));
	} else {
		TextOut(hdc, x, y, buf, lstrlen(buf));
	}
    lpddsback->ReleaseDC(hdc); 
	}
}

void Render()
{ //renders each object in the render list.. waits.. then clears back buffer
	RLiterator tempiterator;
	// Traverse the list and call the draw function on each of the objects
	for (RLiterator i = renderlist.begin() ; i != renderlist.end() ; i++) 
	{
		// mouse needs to be clipepd so exclude it
		if ((*i)->NeedRender() == true && (*i)->GetString() != "mouse")
		{
			(*i)->Draw();
		}

		if ((*i)->NeedDelete() == true)
		{
			tempiterator = i;
			i++;
			SafeListRemove(tempiterator);
			i--;
		}
	
	}
	TheCart->Draw();
	TheBall->Draw();

	// set up fps timers
	if (!useperformancetimer) // if performance timer isnt working
	{
		//FPS counter by josh
		if ((GetTickCount() - fpstimer) < 1000) 
		{
			//if 1 second hasnt past add another frame to counter
			fps++;
		} 
		else  
		{
			lastfps = fps;
			//reset fps
			fps = 0;
			//reset fps timer
			fpstimer = GetTickCount();
		}
	}
	else // if performance timer is working
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&currentclock); // set currentclock to current ticks
		if((currentclock - newfpstimer)*ms_rate < 1000) // if 1000 ms havent passed since last time
		{
			fps++; // increment
		}
		else // 1 sec has passed
		{
			lastfps = fps;
			fps = 0;
			QueryPerformanceCounter((LARGE_INTEGER*)&newfpstimer); // set a new tick counter
		}
	}

	//display fps for that second
//	dmsg(20,20,"FPS: %d", lastfps);

	while(1) 
	{ 
		HRESULT ddrval; 
		ddrval = lpddsprimary->Flip(NULL, 0); 
		if(ddrval == DD_OK) 
		{ 
			break; 
		} 
		if(ddrval == DDERR_SURFACELOST) // GDI probably killed our surfaces in a alt tab
		{ 
			//ddrval = lpddsprimary->Restore(); 
			ddrval = lpdd->RestoreAllSurfaces(); // restore all surfaces in the game
			if(ddrval != DD_OK) 
			{ 
				break; 
			} 
			for (RLiterator i = renderlist.begin() ; i != renderlist.end() ; i++) 
			{
				// go through every bitmap object in the list and reload its bitmap
				// if we dont do this we'll just have a bunch of garbled graphics
				(*i)->ReloadMyBitmap();
			}		
		} 
		if(ddrval != DDERR_WASSTILLDRAWING) 
		{ 
			break; 
		} 
	}

	// surfaces have been flipped, now we can draw any clipped bitmaps using blts
	if ((*ReturnElementMatching("mouse"))->NeedRender()) // render the mouse now
		(*ReturnElementMatching("mouse"))->Draw();

	//clear backbuffer each frame
	INITIALIZE_DDRAW(ddbltfx);
 	ddbltfx.dwFillColor = _RGB16BIT565(0,0,0);
 	lpddsback->Blt(NULL,
 				   NULL,
 				   NULL,
 				   DDBLT_COLORFILL | DDBLT_WAIT,
 				   &ddbltfx);

}


//only to be used in Intro
void RenderForce()
{	// Clears the screen then renders each object in the render list

	//clear screen each frame
	INITIALIZE_DDRAW(ddbltfx);
 	ddbltfx.dwFillColor = _RGB16BIT565(0,0,0);
 	lpddsback->Blt(NULL,
 				   NULL,
 				   NULL,
 				   DDBLT_COLORFILL | DDBLT_WAIT,
 				   &ddbltfx);

	// Traverse the list and call the draw function on each of the objects
	for (RLiterator i = renderlist.begin() ; i != renderlist.end() ; i++) 
	{
		if ((*i)->NeedRender() == true)
		{
			(*i)->Draw();
		}
	}

	while(1) 
	{ 
		HRESULT ddrval; 
		ddrval = lpddsprimary->Flip(NULL, 0); 
		if(ddrval == DD_OK) 
		{ 
			break; 
		} 
		if(ddrval == DDERR_SURFACELOST) 
		{ 
			ddrval = lpddsprimary->Restore(); 
			if(ddrval != DD_OK) 
			{ 
	            break; 
		    } 
		} 
		if(ddrval != DDERR_WASSTILLDRAWING) 
		{ 
			break; 
		} 
	}
	
	
}

void Sprite_Animation()
{
	Track *thetrack;
	Powerup *thepowerup;
	RLiterator Thereturn;
	Crusher *theCrusher;
	Thereturn = FindTrackCollision(TheCart);
	if (Thereturn != NULL)
	{
		log->LogInfo("Collision Dectected");
	}
	else
		log->LogInfo("No Collision");
	thetrack = (Track*) (*FindTrackCollision(TheCart));
	thetrack->OnCollision(TheCart);
	////need code here to stop crashing the game when ball hasnt started///
	if(TheBall->GetState() == Running)
	{
		thetrack = (Track*) (*FindTrackCollision(TheBall));
		thetrack->OnCollision(TheBall);
		if (TheCart->IsCollision(TheBall))
		{
			TheCart->SetState(Failed);
		}
	}
	//////end of ball code for not started ball///
	Thereturn = FindPowerupCollision(TheCart);
	if (Thereturn != NULL)
	{
		thepowerup = (Powerup*) (*Thereturn);
		if (thepowerup->IsCollision(TheCart))
			thepowerup->OnCollision(TheCart);
	}

	Thereturn = FindCrusherCollision(TheCart);
	//Thereturn = ReturnElementMatching("Level_Data_Crusher");
	if(Thereturn != NULL)
	{
		theCrusher = (Crusher*) (*Thereturn);
		if (theCrusher->IsCollision(TheCart))
			theCrusher->OnCollision(TheCart);
	}

	Thereturn = FindCrusherCollision(TheBall);
	//Thereturn = ReturnElementMatching("Level_Data_Crusher");
	if(Thereturn != NULL)
	{
		theCrusher = (Crusher*) (*Thereturn);
		if (theCrusher->IsCollision(TheBall))
			theCrusher->OnCollision(TheBall);
	}

}


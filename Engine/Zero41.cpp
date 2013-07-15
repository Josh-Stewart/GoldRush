/* This is the main windows message loop/handler

  Author	: Jon Cahill
  Date		: 1st July 2002
*/

// turn off warning about symbols too long for debugger (for list<string> etc)
#pragma warning (disable : 4786)

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

//#include <afx.h>
#include "globals.h"
#include "Cart.h"
#include "Ball.h"
#include "Crusher.h"

//defines for windows
#define WINDOW_CLASS_NAME "WINCLASS1"

///////// Globals /////////////////////////////////////////
//All globals here will have a extern buddy in globals.h
///////////////////////////////////////////////////////////
// Windows stuff
HWND main_window_handle = NULL;  // to save the window handle
HINSTANCE hinstance_app = NULL;  // to save the hinstance
HDC hdc;						// need device context for text displaying;
// directdraw stuff
LPDIRECTDRAW7	      lpdd = NULL;
LPDIRECTDRAWSURFACE7  lpddsprimary;   // dd primary surface
LPDIRECTDRAWSURFACE7  lpddsback;   // dd back surface
LPDIRECTDRAWPALETTE   lpddpal;   // a pointer to the created dd palette
LPDIRECTDRAWCLIPPER   lpddclipper;   // dd clipper
DDSURFACEDESC2        ddsd;                  // a direct draw surface description struct
DDBLTFX               ddbltfx;               // used to fill
DDSCAPS2              ddscaps;               // a direct draw surface capabilities struct
HRESULT               ddrval;                // result back from dd calls
DWORD                  start_clock_count; // used for timing

char keybuffer[256]; // keyboard buffer

// for fps timer
__int64 lastclock, currentclock, newfpstimer;
bool useperformancetimer = false, timersetup = false;
double	ms_rate;

Cart *TheCart;
Ball *TheBall;

//logging information
CLogging *log;

//game data structure globals
list<RenderedObject*> renderlist;

CHighScores HighScoreSystem;
CSound SoundSystem;
Cfilereader ConfigSystem;
CRARExtractor RARSystem;

// End of Globals //////////////////////////////////////////

#include "Game_Init.h"
#include "Game_Shutdown.h"
#include "Game_Main.h"

//more globals?
CMenuMain MenuSystem;
RLiterator MouseIterator;

CLevelData LevelSystem;

//Message handler system
LRESULT CALLBACK WindowsProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	PAINTSTRUCT ps;
	

	// Check what the message is
	switch(msg)
	{
	case WM_CREATE:
		{
			return 0;
		}
	break;

	case WM_PAINT:
		{
			hdc = BeginPaint(hwnd, &ps);
			EndPaint(hwnd, &ps);
			
			return 0;
		}
	break;

	case WM_DESTROY:
		{
			PostQuitMessage(0);

			return 0;
		}
	break;

	case WM_CHAR:
		{
			/*if (wparam == VK_ESCAPE)
			{
				PostQuitMessage(0);
			}*/

			return 0;
		}
	break;
	case WM_ACTIVATE:
		{
			
			if ( WA_INACTIVE == wparam ) {
                g_bActive = FALSE;
			}
            else {
                g_bActive = TRUE;
				SetAcquire();           
            }

			//MS code
			//g_bActive = wparam == WA_ACTIVE || wparam == WA_CLICKACTIVE;
			//SetAcquire();
            
			//return TRUE;
		}
	break;
	case WM_SYNCACQUIRE: //this is for re-acquiring input on ctrl-alt-del
		{
			SetAcquire();
		}
	break;

	default:break;

	} // End of switch

	return (DefWindowProc(hwnd, msg, wparam, lparam));

} // End of WindowsProc

int WINAPI WinMain(HINSTANCE hinstance,
				   HINSTANCE hprevinstance,
				   LPSTR lpcmdline,
				   int ncmdshow)

{

	WNDCLASSEX winclass;
	HWND hwnd;
	MSG msg;

	// Window information
	winclass.cbSize = sizeof(WNDCLASSEX);
	winclass.style = CS_DBLCLKS | CS_OWNDC |
					 CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc = WindowsProc;
	winclass.cbClsExtra = 0;
	winclass.cbWndExtra = 0;
	winclass.hInstance = hinstance;
	winclass.hIcon = LoadIcon(hinstance, MAKEINTRESOURCE(IDI_ICON2));
	winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground = HBRUSH(GetStockObject(BLACK_BRUSH));
	winclass.lpszMenuName = NULL;
	winclass.lpszClassName = WINDOW_CLASS_NAME;
	winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&winclass))
		return 0;

	if (!(hwnd = CreateWindowEx(NULL, 
								WINDOW_CLASS_NAME,
								"Zero41",
								WS_VISIBLE | WS_POPUP,
								100, 100,
								800, 600,
								NULL,
								NULL,
								hinstance,
								NULL)))
		
		return 0;

	//Save main window handle
	main_window_handle = hwnd;
	hinstance_app = hinstance;
	//hinstance_app = (HINSTANCE)GetWindowLong( hwnd, GWL_HINSTANCE );

	ShowWindow(main_window_handle, ncmdshow);
    UpdateWindow(main_window_handle);
    SetFocus(main_window_handle);
	//set the font for the game to use

	
	// Memory leak info, need to include MFC to test for memory leaks
	/*#ifdef _DEBUG
		CMemoryState oldMemState, newMemState, diffMemState;
		oldMemState.Checkpoint();
	#endif*/

	//start logging
	//log = new CLogging();
	//log->StartLogging();

	// Game initialization here
	Game_Init();
	
	//message loop
	while(TRUE)
	{
		if(PeekMessage(&msg, NULL, 0,0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} // end if

		// Game processing here
		if (g_bActive) Game_Main(); // only do the game loop if w have focus
	
	} // end while

	// Close game
	Game_Shutdown();
	
	//log->StopLogging();

	// Memory leak info, need to include MFC to test for memory leaks
	/*#ifdef _DEBUG
		newMemState.Checkpoint();
		if( diffMemState.Difference( oldMemState, newMemState ) )
		{
			TRACE( "Memory leaked!\n" );
		}
		else
		{
			TRACE("No Memory Leaks!\n");
		}
	#endif*/

	return (msg.wParam);

} // end WinMain



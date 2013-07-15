/* All initialization code for the game goes here

  Author	: Jon Cahill
  Date		: 1st July 2002
*/
#include "Game_Init.h"

//Prototypes
//void dmsg(HRESULT hr, const char *format, ...);

LPDIRECTDRAWCLIPPER DDraw_Attach_Clipper(LPDIRECTDRAWSURFACE7 lpdds,
                                         int num_rects,
                                         LPRECT clip_list);

void setuptimer();

int Game_Init()
{
	

	//variable to hold results from dx functions
	RECT rect_list = {0,0,SCREEN_WIDTH - 1,SCREEN_HEIGHT - 1};

	// Create the Direct Draw Object
	if (FAILED(DirectDrawCreateEx(NULL, (LPVOID *)&lpdd, IID_IDirectDraw7, NULL)))
	{
		// Error creating the Direct Draw Object
		MessageBox(main_window_handle, "Failed to create DirectDraw object!", "Error", MB_OK);
		Game_Shutdown();
	}

	// Set the Cooperation 
	if (FAILED(lpdd->SetCooperativeLevel(main_window_handle, 
		                                  DDSCL_FULLSCREEN | DDSCL_ALLOWMODEX | 
			                              DDSCL_EXCLUSIVE | DDSCL_ALLOWREBOOT)))
	{
		// Error setting the Cooperation level 
		MessageBox(main_window_handle, "Failed to set DirectDraw cooperation level!", "Error", MB_OK);
		Game_Shutdown();
	}

	//Setting the video resolution
	if (FAILED(lpdd->SetDisplayMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP,0,0)))
	{
		// Error setting the resolution
		MessageBox(main_window_handle, "Failed to set display mode!", "Error", MB_OK);
		Game_Shutdown();
	}


	// clear ddsd and set size
	INITIALIZE_DDRAW(ddsd);

	// Enable valid fields
	ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT | DDSD_CKSRCBLT;

	//Amount of buffers
	ddsd.dwBackBufferCount = 1;

	// Primay Surface Settings
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_COMPLEX | DDSCAPS_FLIP;
	ddsd.ddckCKSrcBlt.dwColorSpaceLowValue = _RGB16BIT565(255, 0, 255);
	ddsd.ddckCKSrcBlt.dwColorSpaceHighValue = _RGB16BIT565(255, 0, 255);

	//Create the primary Surface
	if (FAILED(lpdd->CreateSurface(&ddsd, &lpddsprimary, NULL)))
	{
		// Error creating the primary surface
		MessageBox(main_window_handle, "Failed to create DirectDraw primary surface!", "Error", MB_OK);
		Game_Shutdown();
	}

	INITIALIZE_DDRAW(ddsd);
	// Back buffer settings
	ddsd.dwFlags = DDSD_CAPS | DDSD_CKSRCBLT;
	ddsd.ddsCaps.dwCaps = DDSCAPS_BACKBUFFER;
	ddsd.ddckCKSrcBlt.dwColorSpaceLowValue = _RGB16BIT565(255, 0, 255);
	ddsd.ddckCKSrcBlt.dwColorSpaceHighValue = _RGB16BIT565(255, 0, 255);


	// Attach the back buffer to the primary surface
	if (FAILED(lpddsprimary->GetAttachedSurface(&ddsd.ddsCaps, &lpddsback)))
	{
		// Error attaching back buffer to primary surface
		MessageBox(main_window_handle, "Failed to attach backbuffer to primary DirectDraw surface!", "Error", MB_OK);
		Game_Shutdown();
	}

	/*//Attach clipper to the back ddraw surface
	if (FAILED(lpddclipper = DDraw_Attach_Clipper(lpddsprimary, 1, &rect_list)))
	{
		// Error attaching clipper
	}*/

	if (FAILED(lpdd->CreateClipper(0,&lpddclipper,NULL)))
	{
		// failed to create a clipper
		MessageBox(main_window_handle, "Failed to create primary DirectDraw clipper!", "Error", MB_OK);
		Game_Shutdown();
	}

	if (FAILED(lpddclipper->SetHWnd(0, main_window_handle)))
	{
		// failed to set the clippers cliplist
		MessageBox(main_window_handle, "Failed to set up DirectDraw clipper!", "Error", MB_OK);
		Game_Shutdown();
	}

	if (FAILED(lpddsprimary->SetClipper(lpddclipper)))
	{
		// failed to attach clipper to primary surface
		MessageBox(main_window_handle, "Failed to attach primary DirectDraw clipper!", "Error", MB_OK);
		Game_Shutdown();
	}

	OrderedInsert(new Text(18,"GameInit_Message1", "DirectDraw Initialised successfully...",10,10,10,500,80,false));

	//nice and clean. DI startup
	InitDirectInput();

	OrderedInsert(new Text(18,"GameInit_Message2", "DirectInput Initialised successfully...",10,30,10,500,80,false));

	// if configfile doesnt exist we need to create one
	if (!ConfigSystem.Exists())
	{
		ConfigSystem.CreateDefault();
		OrderedInsert(new Text(18,"GameInit_Message3", "Created config file...",10,50,10,500,80,false));
	}
	else OrderedInsert(new Text(18,"GameInit_Message3", "Config file exists...",10,50,10,500,80,false));

	// do rar system stuff here
	OrderedInsert(new Text(18,"GameInit_Message4", "Extracting game assets...",10,70,10,500,80,false));
	RenderForce();
	RARSystem.ExtractAll();
	OrderedInsert(new Text(18,"GameInit_Message5", "Extraction complete",10,90,10,500,80,false));
	RenderForce();
	
	//initialize highscores
	HighScoreSystem.ReadScores();

	OrderedInsert(new Text(18,"GameInit_Message6", "Initialising Sound System",10,110,10,500,80,false));

	SoundSystem.Initialise(44100,16,(atoi((ConfigSystem.LoadFromConfig("soundvolume")).c_str())),(atoi((ConfigSystem.LoadFromConfig("musicvolume")).c_str())));
	RemoveElementsMatching("GameInit_Message6");
	OrderedInsert(new Text(18,"GameInit_Message6", "Initialising Sound System...Success",10,110,10,500,80,false));

	RenderForce();

	// set up fps limiter/counter timer
	setuptimer();
	

	RemoveElementsMatching("GameInit");

	//setup game objects (load from disk etc)
	
	//push elements onto render list (this is just for testing)

	//renderlist.push_back(new Track("C:/Zero41.bmp", 100, 100, 0));
	//renderlist.push_back(new Track("C:/Zero41.bmp", 200, 100, 1));
	//renderlist.push_back(new Track("C:/Zero41.bmp", 100, 200, 2));
	//renderlist.push_back(new Track("C:/Zero41.bmp", 50,  10,  3));
	//renderlist.push_back(new Track("C:/Zero41.bmp", 500, 400, 4));


	//renderlist.push_back(new Popup("g:/Lowerbar2.bmp", 0, 512, 0, 800,88));
	//renderlist.push_back(new Popup("g:/MButton.bmp", 12, 524, 0, 128,64));

//	renderlist.push_back(new Popup("g:/Trackhole.bmp", 572, 524, 0, 64,64));
//	renderlist.push_back(new Popup("g:/Trackhole.bmp", 648, 524, 0, 64,64));
//	renderlist.push_back(new Popup("g:/Trackhole.bmp", 724, 524, 0, 64,64));


//	CMenuMain MenuMain;


	//mouse cursor testing
	//renderlist.push_back(new Cursor("gfx/cursor.bmp",0,0,100,32,32,0,0));
	
	//ordered insert test code

	TheCart = new Cart("gfx/Cart.bmp", 0, 0, 0, 1);
	TheBall = new Ball("gfx/boulder.bmp", 0, 0, 0, 1);
	
	MenuSystem.RunIntro();

	MouseIterator = OrderedInsert(new Cursor("gfx/cursor.bmp","Mouse",0,0,100,32,32,0,0));

	MenuSystem.MainOn();
	return 0;
		
}
/*
void dmsg(HRESULT hr, const char *format, ...)
{
	int ret;
	char buf[512];
	
	va_list ap;
	va_start(ap, format);
	//vsprintf(buf, format,ap); //buffer overflows R us
	ret = _vsnprintf( buf, sizeof(buf), format, ap);
	va_end(ap);
		
	if(ret == -1){
		MessageBox( NULL, "dmsg too long for buffer", "Debug Message", MB_OK );
	}

	MessageBox( NULL, buf, "Debug Message", MB_OK );
	
	//printf("\n%s", buf);
	//}
	//else print nothing
}*/

LPDIRECTDRAWCLIPPER DDraw_Attach_Clipper(LPDIRECTDRAWSURFACE7 lpdds,
                                         int num_rects,
                                         LPRECT clip_list)

{
// this function creates a clipper from the sent clip list and attaches
// it to the sent surface

int index;                         // looping var
LPDIRECTDRAWCLIPPER lpddclipper;   // pointer to the newly created dd clipper
LPRGNDATA region_data;             // pointer to the region data that contains
                                   // the header and clip list

// first create the direct draw clipper
if (FAILED(lpdd->CreateClipper(0,&lpddclipper,NULL)))
   return(NULL);

// now create the clip list from the sent data

// first allocate memory for region data
region_data = (LPRGNDATA)malloc(sizeof(RGNDATAHEADER)+num_rects*sizeof(RECT));

// now copy the rects into region data
memcpy(region_data->Buffer, clip_list, sizeof(RECT)*num_rects);

// set up fields of header
region_data->rdh.dwSize          = sizeof(RGNDATAHEADER);
region_data->rdh.iType           = RDH_RECTANGLES;
region_data->rdh.nCount          = num_rects;
region_data->rdh.nRgnSize        = num_rects*sizeof(RECT);

region_data->rdh.rcBound.left    =  64000;
region_data->rdh.rcBound.top     =  64000;
region_data->rdh.rcBound.right   = -64000;
region_data->rdh.rcBound.bottom  = -64000;

// find bounds of all clipping regions
for (index=0; index<num_rects; index++)
    {
    // test if the next rectangle unioned with the current bound is larger
    if (clip_list[index].left < region_data->rdh.rcBound.left)
       region_data->rdh.rcBound.left = clip_list[index].left;

    if (clip_list[index].right > region_data->rdh.rcBound.right)
       region_data->rdh.rcBound.right = clip_list[index].right;

    if (clip_list[index].top < region_data->rdh.rcBound.top)
       region_data->rdh.rcBound.top = clip_list[index].top;

    if (clip_list[index].bottom > region_data->rdh.rcBound.bottom)
       region_data->rdh.rcBound.bottom = clip_list[index].bottom;

    } // end for index

// now we have computed the bounding rectangle region and set up the data
// now let's set the clipping list

if (FAILED(lpddclipper->SetClipList(region_data, 0)))
   {
   // release memory and return error
   free(region_data);
   return(NULL);
   } // end if

// now attach the clipper to the surface
if (FAILED(lpdds->SetClipper(lpddclipper)))
   {
   // release memory and return error
   free(region_data);
   return(NULL);
   } // end if

// all is well, so release memory and send back the pointer to the new clipper
free(region_data);
return(lpddclipper);

} // end DDraw_Attach_Clipper

// sets up the frequency for the performance timer
// does several checks to see if its enabled, if not we use the old system
void setuptimer() //by adam
{
	__int64 temprate;
	// set up new timer
	if(QueryPerformanceFrequency((LARGE_INTEGER*)&temprate)) // make sure it works
	{
		if(temprate) // make sure rate got set
		{
			ms_rate = double(temprate)/1000; // converts it to milliseconds
			ms_rate = 1/ms_rate; // invert it for easy multiplication
			if(QueryPerformanceFrequency((LARGE_INTEGER*)&lastclock)) // make sure it will set
			{
				useperformancetimer = true;
			}
			else useperformancetimer = false;
		}
		else useperformancetimer = false;
	}
	else useperformancetimer = false;
	timersetup = true;
}
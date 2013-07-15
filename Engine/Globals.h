
#ifndef GLOBALS_HEADER
#define GLOBALS_HEADER

// turn off warnings about symbols too long for debugger (we need this to have <vector>)
#pragma warning (disable : 4786)

//regular headers
#include <stdio.h>
#include <stdarg.h>
#include <windows.h>
#include <ddraw.h>
#include <dinput.h>
#include <list>
#include <string>
#include <vector>

//for loading bitmaps
#include "ddutil.h"

//STL is fussy about thisn
using namespace std;

//class definitions (weird i know)
class RenderedObject;
class StaticObj;
class Sprite;
class Track;
class AnimatedTrack;
class Ball;
class Dynamite;
class Cart;
class Jump;
class Crusher;
class AnimatedPopup;
class Popup;
class Powerup;

class Text;
//class CSound;


//Menuclasses


//typedefs
typedef list<RenderedObject*>::iterator RLiterator; //list iterator type
typedef list<Track*>::iterator Titerator;



//for the game includes.. 
#include "RenderedObject.h"
#include "Renderer_Tools.h"
#include "Game_Input.h"
#include "CSound.h"
//#include "CMenuMain.h"
#include "Cfilereader.h"
#include "CRARExtractor.h"
#include "CHighScores.h"
#include "CLogging.h"

//hmmm (see comments in gamemain.h)
/*
#include "StaticObj.h"
#include "Track.h"
#include "AnimatedTrack.h"
#include "Sprite.h"
#include "Ball.h"
#include "Cart.h"
#include "Dynamite.h"
#include "Jump.h"
#include "Obstacle.h"
#include "Popup.h" //*/

// default screen size
#define SCREEN_WIDTH    800  // size of screen
#define SCREEN_HEIGHT   600
#define SCREEN_BPP      16    // bits per pixel

// Macros
#define INITIALIZE_DDRAW(ddstruct) {memset(&ddstruct, 0, sizeof(ddstruct)); ddstruct.dwSize=sizeof(ddstruct);}
#define _RGB16BIT565(r, g, b) ((b%32) + ((g%64) << 6) + ((r%32) << 11))

//windows Stuff
extern HWND main_window_handle;
extern HINSTANCE hinstance_app;  // to save the hinstance
extern HDC hdc;					 //save the dc for text display
// directdraw stuff
extern LPDIRECTDRAW7         lpdd;   // dd7 object
extern LPDIRECTDRAWSURFACE7  lpddsprimary;   // dd primary surface
extern LPDIRECTDRAWSURFACE7  lpddsback;   // dd7 back surface
extern LPDIRECTDRAWPALETTE   lpddpal;   // a pointer to the created dd palette
extern LPDIRECTDRAWCLIPPER   lpddclipper;   // dd clipper
extern DDSURFACEDESC2        ddsd;                  // a direct draw surface description struct
extern DDBLTFX               ddbltfx;               // used to fill
extern DDSCAPS2              ddscaps;               // a direct draw surface capabilities struct
extern HRESULT               ddrval;                // result back from dd calls
extern DWORD                 start_clock_count; // used for timing

extern char keybuffer[256]; // keyboard buffer

// fps limiter/counter timer
extern __int64 lastclock, currentclock, newfpstimer;
extern bool useperformancetimer, timersetup;
extern double	ms_rate;

extern Cart *TheCart;
extern Ball *TheBall;

extern list<RenderedObject*> renderlist;
extern CSound SoundSystem;
extern CHighScores HighScoreSystem;
extern Cfilereader ConfigSystem;
extern CRARExtractor RARSystem;

// This is for looking up the type of track piece from the Track class
enum TrackType{
	Start,
	Finish,
	Normal,
	RightDown,
	LeftDown,
	RightUp,
	LeftUp,
	TheJump,
	SpeedUp,
	SpeedDown
};

enum VectorDirection{
	Right,
	Left,
	Up,
	Down
};

enum Status{
	RegularR,
	RegularL,
	RegularU,
	RegularD,
	AJumpR,
	AJumpL,
	JumpFall,
	ACrusher,
	RightD,
	RightD2,
	LeftD,
	LeftD2,
	RightU,
	RightU2,
	LeftU,
	LeftU2,
	None
};

enum State{
	Finished,
	Failed,
	Running
};

// WM_SYNCACQUIRE forces us to re-synchronize our acquisition with the world.
// There are some subtleties with the way Windows manages mouse ownership,
// so we post this message to ourselves to say "Okay, things have settled
// down; now go synchronize DInput with our internal view of the world."
#define WM_SYNCACQUIRE      (WM_USER + 0)


#endif
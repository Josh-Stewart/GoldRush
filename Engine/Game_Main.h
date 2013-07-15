/* All Game logic for one frame goes here

  Only 1 frame worth of code as to not starve the message loop

  Author	: Jon Cahill
  Date		: 1st July 2002
*/
#ifndef GAME_MAIN
#define GAME_MAIN

#include "globals.h"

//urgh
//game object definitions.. these seem to work here (i add a new Track to my RenderedObject list..
//i dont know why these cant go into globals.h. im stumped. Will porlly need to copy these to gameinit.h as well
#include "StaticObj.h"
#include "Track.h"
#include "AnimatedTrack.h"
#include "Sprite.h"
#include "Ball.h"
#include "Cart.h"
#include "Dynamite.h"
#include "Jump.h"
#include "Crusher.h"
#include "AnimatedPopup.h"
#include "Popup.h"
#include "Powerup.h"
#include "cursor.h"
#include "Text.h"
#include "CMenuMain.h"
#include "CLevelData.h"

//CMenuMain requires globals.h and cant be put there
class CMenuMain;
extern CMenuMain MenuSystem;
extern RLiterator MouseIterator;

class CLevelData;
extern CLevelData LevelSystem;

//Menu object includes
int Game_Main();
void Render();
void RenderForce();
void dmsg(int x, int y, const char *format, ...);

void Sprite_Animation();

#endif 
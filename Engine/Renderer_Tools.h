//Renderer_Tools.h

#ifndef RENDERER_TOOLS_HEADER
#define RENDERER_TOOLS_HEADER

#include "globals.h"

//prototypes

//inserting to list
RLiterator OrderedInsert(RenderedObject *const &newobj);
//console tool
RLiterator OrderedConsoleInsert(string ConsoleString);
//removing from list
bool SafeListRemove(RLiterator todelete);
void RemoveZRange (int start, int end);
void RemoveElementsMatching (const char *searchstring);

//finding in the list
RLiterator FindCollision(const char *searchstring); 
RLiterator FindCollisionLast(const char *searchstring);
RLiterator FindCollisionLastNotPowerup(const char *searchstring);
RLiterator FindCollisionLast(const char *searchstring, RLiterator exclude);
RLiterator FindCollisionLastNotPowerup(const char *searchstring, RLiterator exclude);
//takes a sprite object and return track piece that its on
RLiterator FindTrackCollision(Sprite *thesprite);
RLiterator FindPowerupCollision(Sprite *thesprite);
RLiterator FindCrusherCollision(Sprite *thesprite); // needed for multi crushers

RLiterator ReturnElementMatching (const char *searchstring);
RLiterator ReturnElementExact (const char *searchstring);

//validating track functions
bool ValidateTrack();
RLiterator FindTrackAtXY(int x, int y);

#endif //RENDERER_TOOLS_HEADER
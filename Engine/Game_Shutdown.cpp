/* All code to end the game goes here

  Author	: Jon Cahill
  Date		: 1st July 2002
*/
#include "Game_Shutdown.h"

int Game_Shutdown()
{
	
	// adam:DO NOT RUN THIS IT CRASHES
	//RLiterator temp;
	//release game objects
	/*RLiterator j;
	for (RLiterator i = renderlist.begin() ; i != renderlist.end() ; ++i) {		

			SafeListRemove(i);
	}*/

	// added by adam
	// the above code code didnt work but this one seems to
	RLiterator currentobject;
	while(!renderlist.empty()) // if the list is empty then dont even try pull items
	{	
		currentobject = renderlist.begin(); // grab the first item
		delete *currentobject; // delete what it points to
		renderlist.erase(currentobject); // erase it from the list
	}
	currentobject = NULL;

	delete TheCart;
	delete TheBall;

	//clear up DirectInput
	FreeDirectInput();
	SoundSystem.SHUTDOWN();
	RARSystem.CleanUp();

	if(lpddclipper)
	{
		lpddclipper->Release();
		lpddclipper = NULL;
	}

	if(lpddsback)
	{
		lpddsback->Release();
		lpddsback = NULL;
	}

	// Release the primary surface
	if (lpddsprimary)
	{
		lpddsprimary->Release();
		lpddsprimary = NULL;
	} // end if

	// Release DirectDraw surface
	if (lpdd)
	{
		lpdd->Release();
		lpdd = NULL;
	} 

	exit(1);
	//return 0;
}
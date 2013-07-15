/*
	This is an interactivly moving object in the game
	

	Author		: Jon Cahill
	Date		: 30th July 2002

*/

#ifndef CART
#define CART

#include "Sprite.h"

class Cart : public Sprite
{
private:
	int NumberOfPowerups;
	int MaxPowerups;

	//Animation start positions
	int StartVert;

public:
	int WheelType;
	int BodyShape;
	int WeightReduction; //all three of these affect the max speed of the cart.

	Cart();

	Cart(LPCSTR BitmapDir, int StartWeight, int Startx, int Starty, int Startz);

	int GetPowerup();
	int GetMaxPowerup();
	int ResetPowerups(int Powerups);
	void PowerupCollision();
	
	// Renders the cart to the screen with the correct animations
	void Draw();

	virtual ~Cart();
};

#endif CART
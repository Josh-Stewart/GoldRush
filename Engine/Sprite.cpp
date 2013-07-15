/*
	Basic class for creating objects which move around the 
	screen and interact with other objects.
	
	Author		: Jon Cahill
	Date		: 30th July 2002

*/

#include "Sprite.h"

extern CLogging *log;

Sprite::Sprite()
{
}

double Sprite::AdjustSpeed(int SpeedOffset)
{
	Speed += Speed * (0.002 * SpeedOffset);
	if (Speed < 1)
	{
		if(Current != Failed)
		{
			OrderedConsoleInsert("Your Cart was going too slow.");
		}
		SetState(Failed);
		Speed = 20;
	}
	return Speed;
}

void Sprite::MoveAbs(int NewX, int NewY) 
{
	
	x = NewX;
	y = NewY;


	CollBox.left = x + 32;
	CollBox.top = y + 32;
	CollBox.right = x + 32;
	CollBox.bottom = y + 32;


}

State Sprite::GetState()
{
	return Current;
}

void Sprite::SetState(State NewState)
{
	Current = NewState;
	if (Current == Failed)
	{
		Animating = false;
	}
}


void Sprite::CrusherCollision(int SpeedOffset, bool Crushed)
{
	AdjustSpeed(SpeedOffset);
	if (Crushed == true)
	{
		SetState(Failed);
		OrderedConsoleInsert("Your Cart was Crushed.");
	}
}

void Sprite::SetSpeed(int NewSpeed)
{
	Speed = NewSpeed;
}

void Sprite::Push(int StartSpeed)
{
	Speed = StartSpeed / 6; 
	if (Speed < 1)
		Speed = 1;
}

void Sprite::JumpCollision(int RequiredSpeed, int SpeedOffset, int Jumpx, int Jumpy, VectorDirection TheVector)
{
	log->LogInfo("Jump Collision");
	if (Speed >= RequiredSpeed)
	{
		if (TheVector == Right)
		{
			//LoadJump animation
			CurrentStatus = AJumpR;
		}
		else
			CurrentStatus = AJumpL;

		//Adust the speed of the cart
		//Speed = AdjustSpeed(SpeedOffset);
			if (!Animating)
		{
			MoveAbs(Jumpx, Jumpy);
			Animating = true;
		}
	}
	else
	{
		if(Current != Failed)
		{
			OrderedConsoleInsert("Your Cart didn't make it over the Jump.");
		}
		SetState(Failed);
		
	}
}

void Sprite::TrackCollision(int SpeedOffset, VectorDirection TheVector, TrackType TheType, int Trackx, int Tracky)
{
		//Adjustthe speed of the cart
		Speed = AdjustSpeed(SpeedOffset);
		
		//Set Status to normal track going right
		if (TheType == Normal && TheVector == Right)
		{
			CurrentStatus = RegularR;
			//log->LogInfo("Setting RegularR");
		}
		//Set Status to start track going right
		else if (TheType == Start && TheVector == Right)
		{
			CurrentStatus = RegularR;
			//log->LogInfo("Setting RegularR");
		}
		else if (TheType == SpeedUp && TheVector == Right)
		{
			CurrentStatus = RegularR;
			//log->LogInfo("Setting RegularR");
		}
		else if (TheType == SpeedDown && TheVector == Right)
		{
			CurrentStatus = RegularR;
			//log->LogInfo("Setting RegularR");
		}
		//Set Status to start track going right
		else if (TheType == Start && TheVector == Left)
		{
			CurrentStatus = RegularL;
			//log->LogInfo("Setting RegularL");
		}
		else if (TheType == SpeedUp && TheVector == Left)
		{
			CurrentStatus = RegularL;
			//log->LogInfo("Setting RegularL");
		}
		else if (TheType == SpeedDown && TheVector == Left)
		{
			CurrentStatus = RegularL;
			//log->LogInfo("Setting RegularL");
		}
		//Set Status to normal track going left
		else if (TheType == Normal && TheVector == Left)
		{
			CurrentStatus = RegularL;
			//log->LogInfo("Setting RegularL");
		}
		//Set Status to normal track going up
		else if (TheType == Normal && TheVector == Up)
		{
			CurrentStatus = RegularU;
			//log->LogInfo("Setting RegularU");
		}
		//Set Status to normal track going down
		else if (TheType == Normal && TheVector == Down)
		{
			CurrentStatus = RegularD;
			//log->LogInfo("Setting RegularD");
		}
		// Set Status to right and down cornor track heading down
		if (TheType == RightDown && TheVector == Down)
		{
			CurrentStatus = RightD;
			if (!Animating)
			{
				MoveAbs(Trackx, Tracky);
				Animating = true;
			}
			//log->LogInfo("Setting RightD");
		}
		// Set Status to left and down cornor track heading down
		else if (TheType == LeftDown && TheVector == Down)
		{
			CurrentStatus = LeftD;
			if (!Animating)
			{
				MoveAbs(Trackx, Tracky);
				Animating = true;
			}
			//log->LogInfo("Setting LeftD");
		}
		//Set Status to right and down cornor track heading up
		else if (TheType == RightDown && TheVector == Up)
		{
			CurrentStatus = RightD2;
			if (!Animating)
			{
				MoveAbs(Trackx, Tracky);
				Animating = true;
			}
			//log->LogInfo("Setting RightD2");
		}
		//Set Status to left and down cornor track heading up
		else if (TheType == LeftDown && TheVector == Up)
		{
			CurrentStatus = LeftD2;
			if (!Animating)
			{
				MoveAbs(Trackx, Tracky);
				Animating = true;
			}
			//log->LogInfo("Setting LeftD2");
		}
		//Set Status to right and up cornor heading up
		else if (TheType == RightUp && TheVector == Up)
		{
			CurrentStatus = RightU;
			if (!Animating)
			{
				MoveAbs(Trackx, Tracky);
				Animating = true;
			}
			//log->LogInfo("Setting RightU");
		}
		//Set Status to left and up cornor heading up
		else if (TheType == LeftUp && TheVector == Up)
		{
			CurrentStatus = LeftU;
			if (!Animating)
			{
				MoveAbs(Trackx, Tracky);
				Animating = true;
			}
			//log->LogInfo("Setting LeftU");
		}
		//Set Status to right and up cornor heading down
		else if (TheType == RightUp && TheVector == Down)
		{
			CurrentStatus = RightU2;
			if (!Animating)
			{
				MoveAbs(Trackx, Tracky);
				Animating = true;
			}
			//log->LogInfo("Setting RightU2");
		}
		//Set Status to left and up cornor heading down
		else if (TheType == LeftUp && TheVector == Down)
		{
			CurrentStatus = LeftU2;
			if (!Animating)
			{
				MoveAbs(Trackx, Tracky);
				Animating = true;
			}
			//log->LogInfo("Setting LeftU2");
		}
		else if (TheType == Finish)
		{
			Current = Finished;
			Speed = 20;
			CurrentStatus = None;
		}
	
}

void Sprite::PowerupCollision()
{
}

Sprite::~Sprite()
{
	if(TheBitmap)
	{
		TheBitmap->Release();
		TheBitmap = NULL;
	}
}
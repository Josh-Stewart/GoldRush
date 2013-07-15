/*
	Abstract Class that all other rendered objects derive from.
	Stores the bitmap surface, the source and destination rectangles
	and the position values of the bitmap.
	
	Author		: Jon Cahill
	Date		: 30th July 2002

*/

#include "RenderedObject.h"

RenderedObject::RenderedObject()
{

}

void RenderedObject::Move(int AmountX, int AmountY)
{
	x += AmountX;
	y += AmountY;

	CollBox.top = (CollBox.top + AmountY);
	CollBox.bottom = (CollBox.bottom + AmountY);
	CollBox.left = (CollBox.left + AmountX);
	CollBox.right = (CollBox.right + AmountX);

}

void RenderedObject::MoveAbs(int NewX, int NewY) {
	
	x = NewX;
	y = NewY;


	CollBox.bottom = (NewY + (CollBox.bottom - CollBox.top));
	CollBox.top = (NewY);
	CollBox.right = (NewX + (CollBox.right - CollBox.left));
	CollBox.left = (NewX);

}

bool RenderedObject::IsCollision(RenderedObject *CollWith)
{
	RECT TheBox;

	TheBox = CollWith->IsCollision();
	if((TheBox.top >= CollBox.top && TheBox.top <= CollBox.bottom 
		&& TheBox.left >= CollBox.left && TheBox.left <= CollBox.right)
		|| (TheBox.bottom <= CollBox.bottom && TheBox.bottom >= CollBox.top
			 && TheBox.right <= CollBox.right && TheBox.right >= CollBox.right)
		|| (TheBox.top >= CollBox.top && TheBox.top <= CollBox.bottom
		&& TheBox.right >= CollBox.left && TheBox.right <= CollBox.right)
		|| (TheBox.bottom <= CollBox.bottom && TheBox.bottom >= CollBox.top
		&& TheBox.left <= CollBox.right && TheBox.left >= CollBox.left))
	{
		return true;
	}
	else
		return false;
}

RECT RenderedObject::IsCollision()
{
	return CollBox;
}

void RenderedObject::OnCollision()
{
}

int RenderedObject::Getz()
{
	return z;
}

int RenderedObject::Getx()
{
	return x;
}
int RenderedObject::Gety()
{
	return y;
}
string RenderedObject::GetString()
{
	return ObjString;
}

bool RenderedObject::NeedRender()
{
	return RenderThis;
}

bool RenderedObject::NeedDelete()
{
	return DeleteThis;
}

void RenderedObject::NeedRender(bool ToRender)
{
	RenderThis = ToRender;
}



RenderedObject::~RenderedObject()
{
	if(TheBitmap)
	{
		TheBitmap->Release();
		TheBitmap = NULL;
	}
}

void RenderedObject::ReloadMyBitmap()
{
	DDReLoadBitmap(TheBitmap, mysz);
	return;
}
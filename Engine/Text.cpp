#include "Text.h"	

Text::Text()
{

}

Text::Text(int FSIZE, const char *text,char *printtext,int Startx, int Starty, int Startz, int W, int H, bool Console)
{

	ObjString = text;
	textout = (char*)printtext;
	Width = W;
	Height = H;
	fontsize = FSIZE;

	DeathCounter = 50;//frames before deleting
	ConsoleDisplay = Console;

	CollBox.top = Starty;
	CollBox.bottom = (Starty + H);
	CollBox.left = Startx;
	CollBox.right = (Startx +(W));

	DDSURFACEDESC2 ddsd;
	INITIALIZE_DDRAW(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT | DDSD_CKSRCBLT;
	ddsd.dwWidth = W;
	ddsd.dwHeight = H;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_VIDEOMEMORY;
	ddsd.ddckCKSrcBlt.dwColorSpaceLowValue = _RGB16BIT565(255, 0, 255);
	ddsd.ddckCKSrcBlt.dwColorSpaceHighValue = _RGB16BIT565(255, 0, 255);

	if(FAILED(lpdd->CreateSurface(&ddsd, &TheBitmap, NULL)))
	{
		// Failed making surface
	}

	x = Startx;
	y = Starty;
	z = Startz;
//text render code

	 if (lpddsback->GetDC(&hdc) == DD_OK)  
	 {  
		  SetBkMode(hdc, TRANSPARENT); 
		  SetTextColor(hdc, RGB(255,255,255));
		  if(textout.length() < (int)(Width/8))
		  {
			  LOGFONT logfont = {fontsize,0,0,0,FW_SEMIBOLD,false,false,false,DEFAULT_CHARSET ,OUT_CHARACTER_PRECIS,CLIP_DEFAULT_PRECIS, PROOF_QUALITY,FF_MODERN,"Lucida Console"};
			  tempfont = CreateFontIndirect(&logfont);
			SelectObject(hdc,tempfont);
			TextOut(hdc, x, y, textout.c_str(), textout.length()); 
		  }
		  else
		  {
			for(int i = 0;(i*(int)(Width/8))<(int)textout.length();i++)
			{
			  LOGFONT logfont = {fontsize,0,0,0,FW_SEMIBOLD,false,false,false,DEFAULT_CHARSET ,OUT_CHARACTER_PRECIS,CLIP_DEFAULT_PRECIS, PROOF_QUALITY,FF_MODERN,"Lucida Console"};
			  tempfont = CreateFontIndirect(&logfont);
			SelectObject(hdc,tempfont);
				TextOut(hdc, x, (y+(i*20)), (textout.substr((i*(int)(Width/28)),(int)(Width/8))).c_str(), (textout.substr((i*(int)(Width/8)),(int)(Width/8))).length()); 
			}
		  }

		  lpddsback->ReleaseDC(hdc);  

	 }


	

	SourceRect.top = 0;
	SourceRect.left = 0;
	SourceRect.right = W;
	SourceRect.bottom = H;

	RenderThis = true;
}

Text::Text(int FSIZE, const char *text, string printtext,int Startx, int Starty, int Startz, int W, int H, bool Console)
{

	ObjString = text;
	textout = printtext.c_str();
	Width = W;
	Height = H;
	DeathCounter = 50;//frames before deleting
	ConsoleDisplay = Console;
	fontsize = FSIZE;
	
	CollBox.top = Starty;
	CollBox.bottom = (Starty + H);
	CollBox.left = Startx;
	CollBox.right = (Startx +(W));

	DDSURFACEDESC2 ddsd;
	INITIALIZE_DDRAW(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT | DDSD_CKSRCBLT;
	ddsd.dwWidth = W;
	ddsd.dwHeight = H;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_VIDEOMEMORY;
	ddsd.ddckCKSrcBlt.dwColorSpaceLowValue = _RGB16BIT565(255, 0, 255);
	ddsd.ddckCKSrcBlt.dwColorSpaceHighValue = _RGB16BIT565(255, 0, 255);

	if(FAILED(lpdd->CreateSurface(&ddsd, &TheBitmap, NULL)))
	{
		// Failed making surface
	}

	x = Startx;
	y = Starty;
	z = Startz;
//text render code

	 if (lpddsback->GetDC(&hdc) == DD_OK)  
	 {  
		 
		  SetBkMode(hdc, TRANSPARENT); 
		  SetTextColor(hdc, RGB(255,255,255));
		  if(textout.length() < (int)(Width/8))
		  {
			  LOGFONT logfont = {fontsize,0,0,0,FW_SEMIBOLD,false,false,false,DEFAULT_CHARSET ,OUT_CHARACTER_PRECIS,CLIP_DEFAULT_PRECIS, PROOF_QUALITY,FF_MODERN,"Lucida Console"};
			  tempfont = CreateFontIndirect(&logfont);
			SelectObject(hdc,tempfont);
			TextOut(hdc, x, y, textout.c_str(), textout.length()); 
		  }
		  else
		  {
			for(int i = 0;(i*(int)(Width/8))<(int)textout.length();i++)
			{
			  LOGFONT logfont = {fontsize,0,0,0,FW_SEMIBOLD,false,false,false,DEFAULT_CHARSET ,OUT_CHARACTER_PRECIS,CLIP_DEFAULT_PRECIS, PROOF_QUALITY,FF_MODERN,"Lucida Console"};
			  tempfont = CreateFontIndirect(&logfont);
			SelectObject(hdc,tempfont);
				TextOut(hdc, x, (y+(i*20)), (textout.substr((i*(int)(Width/8)),(int)(Width/8))).c_str(), (textout.substr((i*(int)(Width/8)),(int)(Width/8))).length()); 
			}
		  }

		  lpddsback->ReleaseDC(hdc);  


	 }


	

	SourceRect.top = 0;
	SourceRect.left = 0;
	SourceRect.right = W;
	SourceRect.bottom = H;

	RenderThis = true;
}



void Text::Draw()
{	 
	if (lpddsback->GetDC(&hdc) == DD_OK)  
	 {  
		  SetBkMode(hdc, TRANSPARENT); 
		  SetTextColor(hdc, RGB(255,255,255));
		  if(textout.length() < (int)(Width/8))
		  {
//			  LOGFONT logfont = {fontsize,0,0,0,FW_SEMIBOLD,false,false,false,DEFAULT_CHARSET ,OUT_CHARACTER_PRECIS,CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,DEFAULT_PITCH,"ariel"};
//			  tempfont = CreateFontIndirect(&logfont);
			SelectObject(hdc,tempfont);
			TextOut(hdc, x, y, textout.c_str(), textout.length()); 
		  }
		  else
		  {
			for(int i = 0;(i*(int)(Width/8))<(int)textout.length();i++)
			{
//			  LOGFONT logfont = {fontsize,0,0,0,FW_SEMIBOLD,false,false,false,DEFAULT_CHARSET ,OUT_CHARACTER_PRECIS,CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,DEFAULT_PITCH,"ariel"};
//			  HFONT tempfont = CreateFontIndirect(&logfont);
				SelectObject(hdc,tempfont);
				TextOut(hdc, x, (y+(i*(fontsize + 2))), (textout.substr((i*(int)(Width/8)),(int)(Width/8))).c_str(), (textout.substr((i*(int)(Width/8)),(int)(Width/8))).length()); 
			}
		  }

		  lpddsback->ReleaseDC(hdc);  
	 }
	if(ConsoleDisplay == true)
	{
		DeathCounter--;
	}
	if(DeathCounter==0)
	{
		DeleteThis = true;
	}
}

void Text::UpdateText(string newtext)
{
	textout = newtext.c_str();
}

Text::~Text()
{
}



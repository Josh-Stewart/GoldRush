/*	
	Author		: Leigh Shayler
	Date		: 14th October 2002
	BIG NOTE : Text supports multiple lines, the text will be cut
				of and stuck on successive lines. the length of each lines
				in characters is approximately 1/8th of the width supplied
				to the constructor.
				EG. textlength = width/8
*/

#ifndef TEXTObj
#define TEXTObj

#include "StaticObj.h"
#include "Text.h"

class Text : public RenderedObject
{
private:
	string textout;
	int DeathCounter;//used for temporary text on console
	int fontsize;

	bool ConsoleDisplay; //used for temporary text on console
	HFONT tempfont;
public:
	Text();

	Text(int FSIZE, const char *text, char* printtext,int Startx, int Starty, int Startz, int W, int H, bool Console);
	Text(int FSIZE, const char *text, string printtext,int Startx, int Starty, int Startz, int W, int H, bool Console);
	

	void Draw();

	void UpdateText(string newtext);

	virtual ~Text();
};

#endif TEXTObj
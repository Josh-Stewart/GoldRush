//Renderer_Tools.cpp

//renderlist functions, draw optimisations, etc
//works on the list<RenderedObject*> renderlist data structure;

#include "renderer_tools.h"

//for validatetrack()
#include "Track.h"
#include "Jump.h"
#include "Crusher.h"
#include "Sprite.h"
#include "RenderedObject.h"
#include "Text.h"

//log file system
extern CLogging *log;

RLiterator OrderedConsoleInsert(string ConsoleString) 
{
			
	RLiterator current;
	string::size_type pos;

	//Traversing the list and moving each object
	for (current = renderlist.begin() ; current != renderlist.end() ; current++)
		{
		pos = (*current)->GetString().find("CT");
		
		if (pos != string::npos && pos == 0)
			{
				(*current)->Move(0,15);
			}

		}
	
		//add latest text to end of file
		renderlist.push_back(new Text(18,"CT",ConsoleString.c_str(),3,3,1000,800,20,true));
		current = renderlist.end();
		current--;
		return current;
}


RLiterator OrderedInsert(RenderedObject *const &newobj) {

	RLiterator current;
	int newZ;
	bool element_inserted = FALSE;

	newZ = newobj->Getz();

	//Traversing the list and moving each object
	for (current = renderlist.begin() ; current != renderlist.end() ; ++current) {
		if ((*current)->Getz() > newZ) 
		{
			renderlist.insert(current--, newobj);
			element_inserted = TRUE;
			current++;
			return current;
		}
	}
	if (element_inserted != TRUE)
	{
		renderlist.push_back(newobj);
		current = renderlist.end();
		current--;
	}
	return current;
}

//sort of tested
bool SafeListRemove(RLiterator todelete) {
	
	if (todelete != NULL) {
		delete *todelete;
		renderlist.erase(todelete);
		return TRUE;
	} else {
		return FALSE;
	}
}

//working
void RemoveZRange (int start, int end) {
	
	RLiterator current;
	RLiterator todelete;

	//Traversing the list and remove each object in range
	for (current = renderlist.begin() ; current != renderlist.end() ; ) {
		if ((*current)->Getz() >= start && (*current)->Getz() <= end) 
		{
			todelete = current;
			current++;
			delete *todelete;
			renderlist.erase(todelete);
			todelete = NULL;
			
		} else {
			++current;
		}
	}
}

//working
void RemoveElementsMatching (const char *searchstring) {
	
	RLiterator current;
	RLiterator todelete;
	string::size_type pos;


	//Traversing the list and remove each object that has searchstring at the begining of its string desciption
	for (current = renderlist.begin() ; current != renderlist.end() ; ) {
		
		pos = (*current)->GetString().find(searchstring);
		
		if (pos != string::npos && pos == 0) {
			
			todelete = current;
			current++;
			delete *todelete;
			renderlist.erase(todelete);
			todelete = NULL;
		
		} else {
			
			++current;
		}

	} //end for

}
//searches for a matching element and returns an iterator
// Added by Leigh

RLiterator ReturnElementMatching (const char *searchstring) {
	
	RLiterator current;
	string::size_type pos;


	//Traversing the list and remove each object that has searchstring at the begining of its string desciption
	for (current = renderlist.begin() ; current != renderlist.end() ; ) {
		
		pos = (*current)->GetString().find(searchstring);
		
		if (pos != string::npos && pos == 0) 
		{			
				return current;		
		} 
		else 
		{		
			++current;
		}

	} //end for
	return NULL;
}

//searches for a matching element and returns an iterator
// Added by Leigh

RLiterator ReturnElementExact (const char *searchstring) {
	
	RLiterator current;
	string::size_type pos;


	//Traversing the list and remove each object that has searchstring at the begining of its string desciption
	for (current = renderlist.begin() ; current != renderlist.end() ; ) {
		
		pos = (*current)->GetString().compare(searchstring);
		
		if (pos != string::npos && pos == 0) 
		{			
				return current;		
		} 
		else 
		{		
			++current;
		}

	} //end for
	return NULL;
}




//pass a string for an object and it returns what object it is colliding with
//eg pass it "button 1" and it will return the first element that it finds colliding with "button 1"
RLiterator FindCollision(const char *searchstring) {

	RLiterator current;
	RLiterator theobject;

	bool found = false;
	bool collision = false;

	//log->LogInfo("search string = %s",searchstring);

	//Traversing the list and find the object matching the string
	for (current = renderlist.begin() ; current != renderlist.end(); ) {
	
		//string::compare returns 0 if equal
		if (!((*current)->GetString().compare(searchstring)) ) 
		{
			theobject = current;
			found = true;
			break;
		} else {
			++current;
		} 

	} //end for

	if (found == false) {
		//log->LogInfo("cant find object in render list");
		return NULL;
	}

	//Traversing the list to find the first object colliding with theobject
	//if it tries to collide with itself then dont raise collision flags and just continue as normal
	for (current = renderlist.begin() ; current != renderlist.end(); ) {

		if ((*(current))->IsCollision(*theobject)) {
			
			if (current == theobject) {
				//log->LogInfo("trying to delete itself");
				++current;
				continue;
			}
			collision = true;
			break;
		}
		else {
			++current;
		}

	} //end for

	if (collision) {
		
		return current;
	}
	else { 
		//log->LogInfo("cant find a collision with %s", searchstring);
		return NULL;
	}
}

RLiterator FindCollisionLast(const char *searchstring) {

	RLiterator current;
	RLiterator last;
	RLiterator theobject;

	bool found = false;
	bool collision = false;

	//log->LogInfo("search string = %s",searchstring);

	//Traversing the list and find the object matching the string
	for (current = renderlist.begin() ; current != renderlist.end(); ) {
	
		//string::compare returns 0 if equal
		if (!((*current)->GetString().compare(searchstring)) ) 
		{
			theobject = current;
			found = true;
			break;
		} else {
			++current;
		} 

	} //end for

	if (found == false) {
		//log->LogInfo("cant find object in render list");
		return NULL;
	}

	//Traversing the list to find the first object colliding with theobject
	//if it tries to collide with itself then dont raise collision flags and just continue as normal
	for (current = renderlist.begin() ; current != renderlist.end(); ) {

		if ((*(current))->IsCollision(*theobject)) 
		{			
			if (current != theobject) 
			{
				last = current;
				collision = true;
			}			
		}
		++current;
	} //end for

	if (collision) {
		
		return last;
	}
	else { 
		//log->LogInfo("cant find a collision with %s", searchstring);
		return NULL;
	}
}

RLiterator FindCollisionLastNotPowerup(const char *searchstring) {

	RLiterator current;
	RLiterator last;
	RLiterator theobject;

	bool found = false;
	bool collision = false;

	//log->LogInfo("search string = %s",searchstring);

	//Traversing the list and find the object matching the string
	for (current = renderlist.begin() ; current != renderlist.end(); ) {
	
		//string::compare returns 0 if equal
		if (!((*current)->GetString().compare(searchstring)) ) 
		{
			theobject = current;
			found = true;
			break;
		} else {
			++current;
		} 

	} //end for

	if (found == false) {
		//log->LogInfo("cant find object in render list");
		return NULL;
	}

	//Traversing the list to find the first object colliding with theobject
	//if it tries to collide with itself then dont raise collision flags and just continue as normal
	for (current = renderlist.begin() ; current != renderlist.end(); ) {

		if ((*(current))->IsCollision(*theobject)) 
		{			
			if (current != theobject && ((*current)->Getz() != 4)) 
			{
				last = current;
				collision = true;
			}			
		}
		++current;
	} //end for

	if (collision) {
		
		return last;
	}
	else { 
		//log->LogInfo("cant find a collision with %s", searchstring);
		return NULL;
	}
}

RLiterator FindCollisionLast(const char *searchstring, RLiterator exclude) {

	RLiterator current;
	RLiterator last;
	RLiterator theobject;

	bool found = false;
	bool collision = false;

	current = renderlist.begin();
	if(exclude == NULL)
	{
		exclude = current;
	}
	//log->LogInfo("search string = %s",searchstring);

	//Traversing the list and find the object matching the string
	for (current = renderlist.begin() ; current != renderlist.end(); ) {
	
		//string::compare returns 0 if equal
		if (!((*current)->GetString().compare(searchstring)) ) 
		{
			theobject = current;
			found = true;
			break;
		} else {
			++current;
		} 

	} //end for

	if (found == false) {
		//log->LogInfo("cant find object in render list");
		return NULL;
	}

	//Traversing the list to find the first object colliding with theobject
	//if it tries to collide with itself then dont raise collision flags and just continue as normal
	for (current = renderlist.begin() ; current != renderlist.end(); ) {

		if ((*(current))->IsCollision(*theobject)) 
		{			
			if ((current != theobject) && (current != exclude)) 
			{
				last = current;
				collision = true;
			}			
		}
		++current;
	} //end for

	if (collision) {
		
		return last;
	}
	else { 
		//log->LogInfo("cant find a collision with %s", searchstring);
		return NULL;
	}
}

RLiterator FindCollisionLastNotPowerup(const char *searchstring, RLiterator exclude) {

	RLiterator current;
	RLiterator last;
	RLiterator theobject;

	bool found = false;
	bool collision = false;

	current = renderlist.begin();
	if(exclude == NULL)
	{
		exclude = current;
	}
	//log->LogInfo("search string = %s",searchstring);

	//Traversing the list and find the object matching the string
	for (current = renderlist.begin() ; current != renderlist.end(); ) {
	
		//string::compare returns 0 if equal
		if (!((*current)->GetString().compare(searchstring)) ) 
		{
			theobject = current;
			found = true;
			break;
		} else {
			++current;
		} 

	} //end for

	if (found == false) {
		//log->LogInfo("cant find object in render list");
		return NULL;
	}

	//Traversing the list to find the first object colliding with theobject
	//if it tries to collide with itself then dont raise collision flags and just continue as normal
	for (current = renderlist.begin() ; current != renderlist.end(); ) {

		if ((*(current))->IsCollision(*theobject)) 
		{			
			if ((current != theobject) && (current != exclude) && ((*current)->Getz() != 4)) 
			{
				last = current;
				collision = true;
			}			
		}
		++current;
	} //end for

	if (collision) {
		
		return last;
	}
	else { 
		//log->LogInfo("cant find a collision with %s", searchstring);
		return NULL;
	}
}

//takes a sprite object and return track piece that its on
//we could probably re-use FindCollision() for this, but this will be run 30 times a second
//and FindCollision does an extra list search
//returns NULL if nothing found.
RLiterator FindTrackCollision(Sprite *thesprite)
{

	RLiterator current;
	//string::size_type pos;
	string searchstring1 = "Level_Data_Track_Placed";
	string searchstring2 = "Level_Data_Track_Fixed";
	string searchstring3 = "Level_Data_Track_Finish";
	string searchstring4 = "Level_Data_Track_Start";
	string searchstring5 = "Level_Data_Jump";

	bool collision = false;
/*
	//Traversing the list to find the first object colliding with theobject
	//if it tries to collide with itself then dont raise collision flags and just continue as normal
	for (current = renderlist.begin() ; current != renderlist.end(); ) {


		//log->LogInfo("looking in render list for searchstring");
		//does objects text _start_ with "Level_Data_Track*"
		//pos = (*(current))->GetString().find();
		pos = (*current)->GetString().find(searchstring);
		if (pos != string::npos && pos == 0)
		{	
			
			log->LogInfo("found a track piece");
			if (thesprite->IsCollision(*current)) 
			{
				
				log->LogInfo("found a collision");
				collision = true;
				goto end;
			} else {
				current++;
			}
		}

	} //end for
*/
	//log->LogInfo("find track collision is being called.");

	current = renderlist.begin();
	
	while(current != renderlist.end()) // if the list is empty then dont even try pull items
	{	
		//string::compare returns 0 if equal
		if (!((*current)->GetString().compare(searchstring1)) ) 
		{
			//log->LogInfo("found a track piece placed");
			//if (thesprite->IsCollision(*current))
			if ((*current)->IsCollision(thesprite)) 
			{
				//log->LogInfo("found a collision");
				collision = true;
				goto end;
			}
		} //end if 1
		
		//string::compare returns 0 if equal
		if (!((*current)->GetString().compare(searchstring2)) ) 
		{
			//log->LogInfo("found a track piece fixed");
			//if (thesprite->IsCollision(*current)) 
			if ((*current)->IsCollision(thesprite)) 
			{
				//log->LogInfo("found a collision");
				collision = true;
				goto end;
			}
		} //end if 2

		//string::compare returns 0 if equal
		if (!((*current)->GetString().compare(searchstring3)) ) 
		{
			//log->LogInfo("found a track piece fixed");
			//if (thesprite->IsCollision(*current)) 
			if ((*current)->IsCollision(thesprite)) 
			{
				//log->LogInfo("found a collision");
				collision = true;
				goto end;
			}
		} //end if 2

		//string::compare returns 0 if equal
		if (!((*current)->GetString().compare(searchstring4)) ) 
		{
			//log->LogInfo("found a track piece fixed");
			//if (thesprite->IsCollision(*current)) 
			if ((*current)->IsCollision(thesprite)) 
			{
				//log->LogInfo("found a collision");
				collision = true;
				goto end;
			}
		} //end if 2

		if (!((*current)->GetString().compare(searchstring5)) ) 
		{
			//log->LogInfo("found a track piece fixed");
			//if (thesprite->IsCollision(*current)) 
			if ((*current)->IsCollision(thesprite)) 
			{
				//log->LogInfo("found a collision");
				collision = true;
				goto end;
			}
		} //end if 2
				

		current++; 
	} //end while


	end: ;

	if (collision) {
		
		return current;
	}
	else { 
		//log->LogInfo("cant find a collision with some sprite: %s", thesprite->GetString());
		return NULL;
	}

}


//corrects track vectors and returns TRUE if track is valid (complete)
//assumes track pieces in play, text = "Track_Placed"
//and that starting piece text = "Track_Start" and end text = "Track_End"
bool ValidateTrack() {

	bool found = false; // loop flag
	int x,y, x2, y2;
	const int offset = 64;

	RLiterator prev, current, end;
	RLiterator i; //render list loop iterator	

	//store virtual map of the track
	vector<RLiterator> trackmap;
	trackmap.clear();

	//get Track_Start iterator and put it in prev
	//Traversing the list and find the object matching the string
	for (i = renderlist.begin() ; i != renderlist.end(); ) {
	
		//string::compare returns 0 if equal
		if (!((*i)->GetString().compare("Level_Data_Track_Start")) ) 
		{
			prev = i;
			found = true;
			goto validatetrackstart;
		} else {
			++i;
		} 

	} //end for

validatetrackstart: ;

	if (found == false) {
		//log->LogInfo("cant find Start Track in render list");
		return false;
	}

//	log->LogInfo("validate track: found start");

	//get Track_End iterator and put it in end
	//Traversing the list and find the object matching the string
	found = false; //reset found bool
	for (i = renderlist.begin() ; i != renderlist.end(); ) {
	
		//string::compare returns 0 if equal
		if (!((*i)->GetString().compare("Level_Data_Track_Finish")) ) 
		{
			end = i;
			found = true;
			goto validatetrackend;
		} else {
			++i;
		} 

	} //end for

validatetrackend: ;

	if (found == false) {
		//log->LogInfo("cant find End Track in render list");
		return false;
	}
	
	//log->LogInfo("validate track: found end track");

	found = false; //reset found bool
	
	// some variables used within this loop
	Track *pTrack1, *pTrack2;
	TrackType prevtype, currtype;
	VectorDirection prevvector, currvector;
	
	current = prev; //set current to start piece for now to satisfy the while loop 2nd condition
	trackmap.push_back(current); //push the start piece onto the trackmap
	
	while ((prev != end) && (current != NULL)) {
		
		x = (*prev)->Getx();
		y = (*prev)->Gety();
		
		x2 = x; //set for jump checking from right to left
		y2 = y;

		pTrack1 = (Track*)(*prev);
		prevtype = pTrack1->WhatType();
		prevvector = pTrack1->GetVector();
		
		//find next track tile from previous tiles type and vector

		//log->LogInfo("XY of prev[%d,%d]",x,y);

		//find next track piece right (increase X)
		if (prevtype == RightUp && prevvector == Up)
			x += offset;

		else if (prevtype == RightDown && prevvector == Down)
			x += offset;
		
		else if (prevtype == Normal && prevvector == Right)
			x += offset;
		
		//find next track piece down (increase Y)
		else if (prevtype == RightUp && prevvector == Down)
			y += offset;
		
		else if (prevtype == LeftUp && prevvector == Down)
			y += offset;
		
		else if (prevtype == Normal && prevvector == Down)
			y += offset;
		
		//find next track piece left (decrease X)
		else if (prevtype == LeftUp && prevvector == Up)
			x -= offset;
		
		else if (prevtype == LeftDown && prevvector == Down)
			x -= offset;
		
		else if (prevtype == Normal && prevvector == Left)
			x -= offset;

		//find next track piece up (decrease Y)
		else if (prevtype == RightDown && prevvector == Up)
			y -= offset;
		
		else if (prevtype == LeftDown && prevvector == Up)
			y -= offset;
		
		else if (prevtype == Normal && prevvector == Up)
			y -= offset;

		//special cases for speedups/slowdowns
		else if (prevtype == SpeedUp && prevvector == Right)
			x += offset;
	
		else if (prevtype == SpeedDown && prevvector == Right)
			x += offset;

		else if (prevtype == SpeedUp && prevvector == Left)
			x -= offset;

		else if (prevtype == SpeedDown && prevvector == Left)
			x -= offset;

		//special cases for start track piece
		else if (prevtype == Start && prevvector == Right)
			x += offset;

		else if (prevtype == Start && prevvector == Left)
			x -= offset;

		else if (prevtype == Start && prevvector == Down)
			y += offset;

		else if (prevtype == Start && prevvector == Up)
			y -= offset;

		//special cases for jump track pieces (doesnt need to recast the pointer)
		//see special case in null exception catcher below, for finding jumps running right to left
		else if (prevtype == TheJump && prevvector == Right)
			x = x + (offset * 3);
		
		else if (prevtype == TheJump && prevvector == Left)
			x -= offset;
		
		//find tiles at the new position
		current = FindTrackAtXY(x,y);
		if (current == NULL) {
			//catch null exceptions
			//track is not valid or has not been validated			
			
			//special case for jumps comming from right to left.
			//log->LogInfo("looking for jump on left side");
			x2 = x2 - (offset * 3);
			current = FindTrackAtXY(x2,y2);
			if (current == NULL) 
				return false;
			else {
				
				//log->LogInfo("found a track piece (possibly a jump) on left side");
				//extract track type and vector from current.. reuse the pTrack pointer
				pTrack2 = (Jump*)(*current);
				currtype = pTrack2->WhatType();
				
				if (currtype != TheJump) {
					//log->LogError("it wasnt a jump ");
					return false;
				} else {
					//log->LogError("it was a jump!!");
				}
			}
		}

		//check if track runs back in on itself
		int j=0;
		while ((!trackmap.empty()) && (j != trackmap.size())) {
	
			if ((*trackmap[j])->Getx() == (*current)->Getx() && 
				(*trackmap[j])->Gety() == (*current)->Gety() )
			{
				//log->LogError("track is running back on itself!");
				return false;
			}
			
			j++;
		}
		
		trackmap.push_back(current);
	
		//extract track type and vector from current.. reuse the pTrack pointer
		pTrack2 = (Track*)(*current);
		currtype = pTrack2->WhatType();
		currvector = pTrack2->GetVector();
	 
		//now that we have an iterator to the next piece of track in the line we need to check to make sure
		//that its vector is correct.. based on the previous tiles vector. We dont want any sudden changes in
		//track direction.

		//straights that lead into turns
		if (prevvector == Right && prevtype == Normal && currtype == LeftDown && currvector == Down)
			pTrack2->FlipVector();

		else if (prevvector == Left && prevtype == Normal && currtype == RightDown && currvector == Down)
			pTrack2->FlipVector();

		else if (prevvector == Up && prevtype == Normal && currtype == RightUp && currvector == Down)
			pTrack2->FlipVector();
							
		else if (prevvector == Up && prevtype == Normal && currtype == LeftUp && currvector == Down)
			pTrack2->FlipVector();
		
		//straights onto straights
		else if (prevvector == Left && prevtype == Normal && currtype == Normal && currvector == Right)
			pTrack2->FlipVector();

		else if (prevvector == Up && prevtype == Normal && currtype == Normal && currvector == Down)
			pTrack2->FlipVector();

		//turns that lead into straights
		else if (prevvector == Down && prevtype == LeftDown && currtype == Normal && currvector == Right)
			pTrack2->FlipVector();

		else if (prevvector == Up && prevtype == LeftDown && currtype == Normal && currvector == Down)
			pTrack2->FlipVector();
		
		else if (prevvector == Up && prevtype == RightDown && currtype == Normal && currvector == Down)
			pTrack2->FlipVector();

		else if (prevvector == Up && prevtype == LeftUp && currtype == Normal && currvector == Right)
			pTrack2->FlipVector();

		//turns that lead into other turns
		else if (prevvector == Up && prevtype == LeftDown && currtype == RightUp && currvector == Down)
			pTrack2->FlipVector();
		
		else if (prevvector == Up && prevtype == LeftDown && currtype == LeftUp && currvector == Down)
			pTrack2->FlipVector();

		else if (prevvector == Down && prevtype == LeftDown && currtype == RightDown && currvector == Down)
			pTrack2->FlipVector();

		else if (prevvector == Down && prevtype == RightDown && currtype == LeftDown && currvector == Down)
			pTrack2->FlipVector();

		else if (prevvector == Up && prevtype == RightDown && currtype == LeftUp && currvector == Down)
			pTrack2->FlipVector();

		else if (prevvector == Up && prevtype == RightDown && currtype == RightUp && currvector == Down)
			pTrack2->FlipVector();

		else if (prevvector == Up && prevtype == RightUp && currtype == LeftDown && currvector == Down)
			pTrack2->FlipVector();

		else if (prevvector == Up && prevtype == LeftUp && currtype == RightDown && currvector == Down)
			pTrack2->FlipVector();

		//special cases for speedies
		//travelling into a speedy
		else if (prevvector == Left && prevtype == Normal && (currtype == SpeedUp || currtype == SpeedDown) && currvector == Right)
			pTrack2->FlipVector();
		
		else if (prevvector == Down && prevtype == LeftDown && (currtype == SpeedUp || currtype == SpeedDown) && currvector == Right)
			pTrack2->FlipVector();

		else if (prevvector == Up && prevtype == LeftUp && (currtype == SpeedUp || currtype == SpeedDown) && currvector == Right)
			pTrack2->FlipVector();

		else if (prevvector == Left && prevtype == TheJump && (currtype == SpeedUp || currtype == SpeedDown) && currvector == Right)
			pTrack2->FlipVector();

		//travelling out of a speedy
		else if (prevvector == Left && (prevtype == SpeedUp || prevtype == SpeedDown) && currtype == Normal && currvector == Right)
			pTrack2->FlipVector();
		
		else if (prevvector == Left && (prevtype == SpeedUp || prevtype == SpeedDown) && currtype == RightDown && currvector == Down)
			pTrack2->FlipVector();

		else if (prevvector == Left && (prevtype == SpeedUp || prevtype == SpeedDown) && currtype == TheJump && currvector == Right)
			pTrack2->FlipVector();

		else if (prevvector == Right && (prevtype == SpeedUp || prevtype == SpeedDown) && currtype == LeftDown && currvector == Down)
			pTrack2->FlipVector();

		else if (prevvector == Left && (prevtype == SpeedUp || prevtype == SpeedDown) && (currtype == SpeedUp || currtype == SpeedDown) && currvector == Right)
			pTrack2->FlipVector();

		//special jump cases - going into jumps (when we need to flip the jumps vector)
		else if (prevvector == Left && prevtype == Normal && currtype == TheJump && currvector == Right)
			pTrack2->FlipVector();
		
		else if (prevvector == Down && prevtype == LeftDown && currtype == TheJump && currvector == Right)
			pTrack2->FlipVector();

		else if (prevvector == Up && prevtype == LeftUp && currtype == TheJump && currvector == Right)
			pTrack2->FlipVector();

		//special jump cases - leaving jumps
		else if (prevvector == Left && prevtype == TheJump && currtype == Normal && currvector == Right)
			pTrack2->FlipVector();

		else if (prevvector == Left && prevtype == TheJump && currtype == RightDown && currvector == Down)
			pTrack2->FlipVector();

		else if (prevvector == Right && prevtype == TheJump && currtype == LeftDown && currvector == Down)
			pTrack2->FlipVector();

		//special fix for start track types
		else if (prevvector == Right && prevtype == Start && currtype == LeftDown && currvector == Down)
			pTrack2->FlipVector();
			
		//only used if start position is on a different side than usual
		else if (prevvector == Left && prevtype == Start && currtype == RightDown && currvector == Down)
			pTrack2->FlipVector();
		
		else if (prevvector == Left && prevtype == Start && currtype == Normal && currvector == Right)
			pTrack2->FlipVector();

		else if (prevvector == Up && prevtype == Start && currtype == Normal && currvector == Down)
			pTrack2->FlipVector();

		else if (prevvector == Up && prevtype == Start && currtype == LeftUp && currvector == Down)
			pTrack2->FlipVector();
			
		else if (prevvector == Up && prevtype == Start && currtype == RightUp && currvector == Down)
			pTrack2->FlipVector();

		//exceptions for track integrity (connecting to straight bits and causing a T junction)
		//going up into T junction
		else if (prevvector == Up && prevtype ==  Normal && (currtype == Normal || currtype == SpeedUp || currtype == SpeedDown) && (currvector == Left || currvector == Right))
			return false;

		else if (prevvector == Up && prevtype ==  LeftDown && (currtype == Normal || currtype == SpeedUp || currtype == SpeedDown) && (currvector == Left || currvector == Right))
			return false;

		else if (prevvector == Up && prevtype ==  RightDown && (currtype == Normal || currtype == SpeedUp || currtype == SpeedDown) && (currvector == Left || currvector == Right))
			return false;

		//going down into T junction
		else if (prevvector == Down && prevtype == Normal && (currtype == Normal || currtype == SpeedUp || currtype == SpeedDown) && (currvector == Left || currvector == Right))
			return false;
		
		else if (prevvector == Down && prevtype == RightUp && (currtype == Normal || currtype == SpeedUp || currtype == SpeedDown) && (currvector == Left || currvector == Right))
			return false;

		else if (prevvector == Down && prevtype == LeftUp && (currtype == Normal || currtype == SpeedUp || currtype == SpeedDown) && (currvector == Left || currvector == Right))
			return false;

		//going left into T junction
		else if (prevvector == Left && (prevtype ==  Normal || prevtype == SpeedUp || prevtype == SpeedDown) && currtype == Normal && (currvector == Up || currvector == Down))
			return false;
		
		else if (prevvector == Down && prevtype == LeftDown && currtype == Normal && (currvector == Up || currvector == Down))
			return false;

		else if (prevvector == Up && prevtype == LeftUp && currtype == Normal && (currvector == Up || currvector == Down))
			return false;

		//going right into T junction
		else if (prevvector == Right && (prevtype ==  Normal || prevtype == SpeedUp || prevtype == SpeedDown) && currtype == Normal && (currvector == Up || currvector == Down))
			return false;
		
		else if (prevvector == Down && prevtype == RightDown && currtype == Normal && (currvector == Up || currvector == Down))
			return false;

		else if (prevvector == Up && prevtype == RightUp && currtype == Normal && (currvector == Up || currvector == Down))
			return false;

		//start pieces that lead into T junctions
		else if (prevvector == Right && prevtype == Start && currtype == Normal && (currvector == Up || currvector == Down))
			return false;

		//jumps that lead into T Junctions
		else if (prevvector == Right && prevtype == TheJump && currtype == Normal && (currvector == Up || currvector == Down))
			return false;
		
		else if (prevvector == Left && prevtype == TheJump && currtype == Normal && (currvector == Up || currvector == Down))
			return false;

		//extra exceptions for downward turns leading into other turns.. tricky bastards
			
		//doubles of track that arent flat bits
		else if ((prevtype != Normal && prevtype != SpeedUp && prevtype != SpeedDown && prevtype != TheJump) && prevtype == currtype)
			return false;

		else if (prevvector == Down && prevtype == LeftUp && currtype == LeftUp && currvector == Down)
			return false;

		else if (prevvector == Down && prevtype == RightUp && currtype == RightUp && currvector == Down)
			return false;
		
		else if (prevvector == Down && prevtype == LeftUp && currtype == RightUp && currvector == Down)
			return false;
		
		else if (prevvector == Down && prevtype == RightUp && currtype == LeftUp && currvector == Down)
			return false;

		else if (prevvector == Up && prevtype == RightDown && currtype == LeftDown && currvector == Down)
			return false;

		else if (prevvector == Up && prevtype == LeftDown && currtype == RightDown && currvector == Down)
			return false;

		else if (prevvector == Up && prevtype == RightUp && currtype == RightUp && currvector == Down)
			return false;

		else if (prevvector == Up && prevtype == LeftDown && currtype == LeftDown && currvector == Down)
			return false;

		//flat bits into turns
		else if (prevvector == Left && (prevtype == Normal || prevtype == SpeedUp || prevtype == SpeedDown) && currtype == LeftDown && currvector == Down)
			return false;
		
		else if (prevvector == Right && (prevtype == Normal || prevtype == SpeedUp || prevtype == SpeedDown) && currtype == RightDown && currvector == Down)
			return false;

		//special cases for start pieces leading into irregular turns
		else if (prevvector == Right && prevtype == Start && currtype == RightUp && currvector == Down)
			return false;

		else if (prevvector == Right && prevtype == Start && currtype == RightDown && currvector == Down)
			return false;

		//special case for finish piece
		else if (currtype == Finish && currvector == Right && (prevtype != RightDown && prevtype != RightUp && prevtype != Normal && prevtype != SpeedUp && prevtype != SpeedDown))
			return false;

		//set current to previous for the next loop iteration
		prev = current;

	} //end while

	return true;
}

//helper function for ValidateTrack()
//returns iterator of track with starting pos of XY, returns NULL if none is found at that pos.
RLiterator FindTrackAtXY(int x, int y) {
	
	//bool found = false;
	RLiterator i;
	string searchstring1 = "Level_Data_Track_Placed";
	string searchstring2 = "Level_Data_Track_Fixed";
	string searchstring3 = "Level_Data_Track_Finish";
	string searchstring4 = "Level_Data_Jump";
	//string::size_type pos;
	
	//get Track_End iterator and put it in end
	//Traversing the list and find the object matching the string
	i = renderlist.begin() ; 
	
	//log->LogInfo("FindTrackAtXY(): start of while loop.. looking for XY[%d,%d]",x,y);
	while (i != renderlist.end()) {
		
		if ((!((*i)->GetString().compare(searchstring1))) || 
			(!((*i)->GetString().compare(searchstring2))) ||
			(!((*i)->GetString().compare(searchstring3))) ||
			(!((*i)->GetString().compare(searchstring4)))   ) 
		{
			//log->LogInfo("FindTrackAtXY(): found track piece in renderlist [%d,%d]",(*i)->Getx(),(*i)->Gety());
			//does object xy == given xy?
			if ( ((*i)->Getx() == x)  &&  ((*i)->Gety() == y)) 
			{
				//log->LogInfo("FindTrackAtXY(): adjacent piece found!");
				return i;
			}
		}
				
		i++;
	} //end for

	//log->LogInfo("cant find track at Next [%d,%d]",x,y);
	return NULL;
	
}

RLiterator FindPowerupCollision(Sprite *thesprite)
{

	RLiterator current;
	//string::size_type pos;
	string searchstring1 = "Level_Data_Pickup";

	bool collision = false;

	//log->LogInfo("find track collision is being called.");

	current = renderlist.begin();
	
	while(current != renderlist.end()) // if the list is empty then dont even try pull items
	{	
		//string::compare returns 0 if equal
		if (!((*current)->GetString().compare(searchstring1)) ) 
		{
			//log->LogInfo("found a track piece placed");
			//if (thesprite->IsCollision(*current))
			if ((*current)->IsCollision(thesprite)) 
			{
				//log->LogInfo("found a collision");
				collision = true;
				goto end;
			}
		} //end if			

		current++; 
	} //end while


	end: ;

	if (collision) {
		
		return current;
	}
	else { 
		//log->LogInfo("cant find a collision with some sprite: %s", thesprite->GetString());
		return NULL;
	}

}

RLiterator FindCrusherCollision(Sprite *thesprite)
{

	RLiterator current;
	//string::size_type pos;
	string searchstring1 = "Level_Data_Crusher";

	bool collision = false;

	//log->LogInfo("find track collision is being called.");

	current = renderlist.begin();
	
	while(current != renderlist.end()) // if the list is empty then dont even try pull items
	{	
		//string::compare returns 0 if equal
		if (!((*current)->GetString().find(searchstring1)) ) 
		{
			//log->LogInfo("found a track piece placed");
			//if (thesprite->IsCollision(*current))
			if ((*current)->IsCollision(thesprite)) 
			{
				//log->LogInfo("found a collision");
				collision = true;
				goto end;
			}
		} //end if			

		current++; 
	} //end while


	end: ;

	if (collision) {
		
		return current;
	}
	else { 
		//log->LogInfo("cant find a collision with some sprite: %s", thesprite->GetString());
		return NULL;
	}

}
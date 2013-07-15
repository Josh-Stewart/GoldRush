//Game_Input.cpp
//for all the input handling functions

#include "game_input.h"

//global input variables
//made extern in the game_input header
int mouse_x = SCREEN_WIDTH/2;
int mouse_y = SCREEN_HEIGHT/2;
int mouse_1 = 0;
int mouse_2 = 0;

//mouse timer
DWORD mousetimer;

//globals that arent extern
LPDIRECTINPUT7		 g_pDI;	
LPDIRECTINPUTDEVICE7  g_pdidKeyboard;
LPDIRECTINPUTDEVICE7  g_pdidMouse;

BOOL g_bActive = TRUE;
 
bool keyboard_active = false;
string keyboard_buffer;

int scan2ascii(DWORD scancode, unsigned short* result);
void clear_keyboard_buffer();
void deactivate_keyboard();

HRESULT InitDirectInput() {

	HRESULT hr;

	//DIRECTINPUT 7
    // Register with the DirectInput subsystem and get a pointer
    // to a IDirectInput interface we can use
    if( FAILED( hr = DirectInputCreateEx( hinstance_app, DIRECTINPUT_VERSION, IID_IDirectInput7, (VOID**)&g_pDI,NULL)))
    {
        //dmsg(hr, "DirectInputCreate() failed." );
        return hr;
    }

	// Obtain an interface to the system mouse + keyboard devices
	if( FAILED( hr = g_pDI->CreateDeviceEx(GUID_SysKeyboard, IID_IDirectInputDevice7,(void**)&g_pdidKeyboard, NULL)))
	{
		//dmsg( hr, "CreateDeviceEx(keyboard) failed" );
        return hr;
	}

	if( FAILED( hr = g_pDI->CreateDeviceEx(GUID_SysMouse, IID_IDirectInputDevice7,(void**)&g_pdidMouse, NULL)))
	{
		//dmsg( hr, "CreateDeviceEx(mouse) failed" );
        return hr;
	}

	//set data format
	if( FAILED( hr = g_pdidKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		//dmsg(hr, "Keyboard Set Format() failed." );
        return hr;
	}

	if( FAILED( hr = g_pdidMouse->SetDataFormat(&c_dfDIMouse)))
	{
		//dmsg(hr, "Mouse Set Format() failed." );
        return hr;
	}

	//set behaviour
	//NOTE exclusive keyboard stops all outside keys except alt-tab and ctrl-alt-del
	g_pdidKeyboard->SetCooperativeLevel(main_window_handle, 
					DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

	//NOTE excluseive mouse hides cursor
	g_pdidMouse->SetCooperativeLevel(main_window_handle,
					DISCL_EXCLUSIVE | DISCL_FOREGROUND);
	

	// IMPORTANT STEP TO USE BUFFERED DEVICE DATA!
    // DirectInput uses unbuffered I/O (buffer size = 0) by default.
    // Set the buffer size to DINPUT_BUFFERSIZE (defined above) elements.
    // The buffer size is a DWORD property associated with the device.
    DIPROPDWORD dipdw;

    dipdw.diph.dwSize = sizeof(DIPROPDWORD);
    dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    dipdw.diph.dwObj = 0;
    dipdw.diph.dwHow = DIPH_DEVICE;
    dipdw.dwData = 16; //BUFFER SIZE!!

    hr = g_pdidKeyboard->SetProperty( DIPROP_BUFFERSIZE, &dipdw.diph );


	//mouse buffers are evil. immediate data is fine
	//set mouse to absolute mode
	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
    dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    dipdw.diph.dwObj = 0;
    dipdw.diph.dwHow = DIPH_DEVICE;
    dipdw.dwData = DIPROPAXISMODE_REL; //mouse positioning mode 

	if (FAILED(hr = g_pdidMouse->SetProperty(DIPROP_AXISMODE, &dipdw.diph)))
		return hr;

	//acquire devices when done
	g_pdidKeyboard->Acquire();
	g_pdidMouse->Acquire();
	
	mousetimer = GetTickCount();

	return S_OK;

}

void FreeDirectInput() {

	// release direct input stuff
	g_pdidMouse->Unacquire();
    g_pdidKeyboard->Unacquire();

	// Destroy the mouse object
    if( g_pdidMouse )
    {
        // Unacquire the device (just in case) before exitting.
        g_pdidMouse->Unacquire();

        g_pdidMouse->Release();
        g_pdidMouse = NULL;
    }

	// Destroy the keyboard object
    if( g_pdidKeyboard )
    {
        // Unacquire the device (just in case) before exitting.
        g_pdidKeyboard->Unacquire();

        g_pdidKeyboard->Release();
        g_pdidKeyboard = NULL;
    }

    // Destroy the DInput object
    if( g_pDI )
    {
        g_pDI->Release();
        g_pDI = NULL;
    }
}


void SetAcquire()
{
    // nothing to do if g_pKeyboard is NULL
    if (g_pdidKeyboard != NULL) {
		
		if (g_bActive) {
			// acquire the input device 
			g_pdidKeyboard->Acquire();
		} else {
			// unacquire the input device 
			g_pdidKeyboard->Unacquire();
		}
    }
	
	
	if (g_pdidMouse != NULL) {
	    if (g_bActive) {
			// acquire the input device 
			g_pdidMouse->Acquire();
		} else {
			// unacquire the input device 
			g_pdidMouse->Unacquire();
		}
    }

}

int UpdateInput()
{
	HRESULT hr;
	
	//updates mouse_b, mouse_x and mouse_y;
	DIMOUSESTATE mousestate;

	hr = g_pdidMouse->GetDeviceState(sizeof(DIMOUSESTATE),(LPVOID)&mousestate);
	
	//see DX samples for another method to reestablish mouse connection if lost
	//there are lots of other things that could go wrong here.. but we arent checking for everything.
	if (hr == DIERR_INPUTLOST) {
            PostMessage(main_window_handle, WM_SYNCACQUIRE, 0, 0L);
            return 1;
	}
	
	/* Unable to read data or no data available */
    if (FAILED(hr)) {
            return 1;
    }

	//relative mode
	mouse_x = mouse_x + (mousestate.lX * 1.2);
	mouse_y = mouse_y + (mousestate.lY * 1.2);

	// clip the cursor to our client area
    if (mouse_x < 0)                
        mouse_x = 0;

    if (mouse_x >= SCREEN_WIDTH) 
        mouse_x = SCREEN_WIDTH - 1;

    if (mouse_y < 0)                
        mouse_y = 0;

    if (mouse_y >= SCREEN_HEIGHT) 
        mouse_y = SCREEN_HEIGHT - 1;

	//wait before updating buttons (100 milliseconds)
	//needs work or some redoing of menu logic
	//if ((GetTickCount() - mousetimer) < 66)
	//{
	//	return 1;
	
	//} else {
		
		//mousetimer = GetTickCount();
		
		//left mouse button
		if (mousestate.rgbButtons[0] & 0x80)
		{
			switch(mouse_1)
			{
			case 0:
					mouse_1 = 1;
					break;
			case 1:
					mouse_1 = 2;
					break;
			}
		}
		else 
		{	
			switch(mouse_1)
			{
			case 1:
					mouse_1 = 3;
					break;
			case 2:
					mouse_1 = 3;
					break;
			case 3:
					mouse_1 = 0;
					break;
			}
		}
		//right mouse button
		if (mousestate.rgbButtons[1] & 0x80)
		{
			switch(mouse_2)
			{
			case 0:
					mouse_2 = 1;
					break;
			case 1:
					mouse_2 = 2;
					break;
			}
		}
		else 
		{	
			switch(mouse_2)
			{
			case 1:
					mouse_2 = 3;
					break;
			case 2:
					mouse_2 = 3;
					break;
			case 3:
					mouse_2 = 0;
					break;
			}
		}
	//}

	if (keyboard_active)
	{
		DIDEVICEOBJECTDATA didod[ 16 ];  // Receives buffered data 
		DWORD dwElements;
 
		hr = DIERR_INPUTLOST;

		while( hr != DI_OK )
		{
		// basic idea is the getdevicedata will grab the keys pressed and jam them into the buffer
		// buffer overflows could happen but shouldnt do much damage
			dwElements = 16;
			hr = g_pdidKeyboard->GetDeviceData( sizeof(DIDEVICEOBJECTDATA),
												didod, 
												&dwElements, 
												0 );
			if (hr != DI_OK)
			{
				hr = g_pdidKeyboard->Acquire();
					if ( FAILED(hr) )  
						// this could happen if we lost the keyboard input and cant get it back
						return 0;
			}
		}

		if ( FAILED(hr) )
			return 0;

		unsigned short convertedchar;
		for (int i = 0; i < dwElements; i++) 
		{
			// first we test for special key presses
			if (didod[ i ].dwData & 0x80) continue;
			switch(didod[ i ].dwOfs)
			{	
			case DIK_RETURN: // enter was pressed
			case DIK_ESCAPE: // escape was pressed		
				// turn off keyboard active
				if(keyboard_buffer.length() < 1) break;
				keyboard_active = false;
				break;
			case DIK_BACK: // backspace was pressed
				if (keyboard_buffer.length() < 1) break; // dont backspace if its empty
				// get the length of the buffer, then set the buffer to the old buffer take the end element
				keyboard_buffer = keyboard_buffer.substr(0, keyboard_buffer.length() - 1);
				break;
			case DIK_RSHIFT: //shift key pressed
			case DIK_LSHIFT: //shift key pressed
			case DIK_RCONTROL:
			case DIK_LCONTROL:
			case DIK_RALT:
			case DIK_LALT:
			case DIK_TAB: // tab key pressed
			case DIK_F1: // function key pressed
			case DIK_F2: // function key pressed
			case DIK_F3: // function key pressed
			case DIK_F4: // function key pressed
			case DIK_F5:
			case DIK_F6:
			case DIK_F7:
			case DIK_F8:
			case DIK_F9:
			case DIK_F10:
			case DIK_F11:
			case DIK_F12:
			case DIK_NUMLOCK:
			case DIK_SCROLL:
			case DIK_CAPSLOCK:
			case DIK_NUMPADENTER:
			case DIK_NUMPADSLASH:
			case DIK_NUMPADSTAR:
			case DIK_NUMPADMINUS:
			case DIK_NUMPADPLUS:
			case DIK_NUMPADPERIOD:
			case DIK_NUMPAD1:
			case DIK_NUMPAD2:
			case DIK_NUMPAD3:
			case DIK_NUMPAD4:
			case DIK_NUMPAD5:
			case DIK_NUMPAD6:
			case DIK_NUMPAD7:
			case DIK_NUMPAD8:
			case DIK_NUMPAD9:
			case DIK_NUMPAD0:
			case DIK_UP:
			case DIK_DOWN:
			case DIK_LEFT:
			case DIK_RIGHT:
			case DIK_HOME:
			case DIK_END:
			case DIK_INSERT:
			case DIK_DELETE:
			case DIK_PRIOR:
			case DIK_NEXT:
				break;
			
			default: // no special key pressed---limit keypresses to 10
				if(keyboard_buffer.length() < 10)
				{
					scan2ascii(didod[ i ].dwOfs, &convertedchar); // grab the key in ascii form
					keyboard_buffer += char(convertedchar);
				}
			}
		}
	}

	return 0;
}

int scan2ascii(DWORD scancode, unsigned short* result)
{
   HKL layout=GetKeyboardLayout(0);
   unsigned char kstate[256];

   if (GetKeyboardState(kstate)==FALSE)
      return 0;
   UINT vk=MapVirtualKeyEx(scancode,1,layout);
   return ToAsciiEx(vk,scancode,kstate,result,0,layout);
}

void clear_keyboard_buffer()
{
	keyboard_buffer.erase();
}

void deactivate_keyboard()
{
	keyboard_active = false;
}
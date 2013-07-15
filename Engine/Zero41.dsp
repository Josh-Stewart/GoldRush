# Microsoft Developer Studio Project File - Name="Zero41" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Zero41 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Zero41.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Zero41.mak" CFG="Zero41 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Zero41 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Zero41 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Zero41 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "NDEBUG"
# ADD RSC /l 0xc09 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 Delayimp.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ddraw.lib dxguid.lib dinput.lib fmodvc.lib /nologo /subsystem:windows /machine:I386 /DELAYLOAD:fmod.dll
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Zero41 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "_DEBUG"
# ADD RSC /l 0xc09 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ddraw.lib dxguid.lib dinput.lib fmodvc.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Zero41 - Win32 Release"
# Name "Zero41 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "GameObjectCode"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AnimatedPopup.cpp
# End Source File
# Begin Source File

SOURCE=.\AnimatedTrack.cpp
# End Source File
# Begin Source File

SOURCE=.\Ball.cpp
# End Source File
# Begin Source File

SOURCE=.\Cart.cpp
# End Source File
# Begin Source File

SOURCE=.\Crusher.cpp
# End Source File
# Begin Source File

SOURCE=.\cursor.cpp
# End Source File
# Begin Source File

SOURCE=.\Dynamite.cpp
# End Source File
# Begin Source File

SOURCE=.\Jump.cpp
# End Source File
# Begin Source File

SOURCE=.\Popup.cpp
# End Source File
# Begin Source File

SOURCE=.\Powerup.cpp
# End Source File
# Begin Source File

SOURCE=.\RenderedObject.cpp
# End Source File
# Begin Source File

SOURCE=.\Sprite.cpp
# End Source File
# Begin Source File

SOURCE=.\StaticObj.cpp
# End Source File
# Begin Source File

SOURCE=.\Text.cpp
# End Source File
# Begin Source File

SOURCE=.\Track.cpp
# End Source File
# End Group
# Begin Group "MenuClasses"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CMenuMain.cpp
# End Source File
# End Group
# Begin Group "GameLevels"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Level1.cpp
# End Source File
# Begin Source File

SOURCE=.\Level10.cpp
# End Source File
# Begin Source File

SOURCE=.\Level2.cpp
# End Source File
# Begin Source File

SOURCE=.\Level3.cpp
# End Source File
# Begin Source File

SOURCE=.\Level4.cpp
# End Source File
# Begin Source File

SOURCE=.\Level5.cpp
# End Source File
# Begin Source File

SOURCE=.\Level6.cpp
# End Source File
# Begin Source File

SOURCE=.\Level7.cpp
# End Source File
# Begin Source File

SOURCE=.\Level8.cpp
# End Source File
# Begin Source File

SOURCE=.\Level9.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\Cfilereader.cpp
# End Source File
# Begin Source File

SOURCE=.\CHighScores.cpp
# End Source File
# Begin Source File

SOURCE=.\CLevelData.cpp
# End Source File
# Begin Source File

SOURCE=.\CLogging.cpp
# End Source File
# Begin Source File

SOURCE=.\CRARExtractor.cpp
# End Source File
# Begin Source File

SOURCE=.\CSound.cpp
# End Source File
# Begin Source File

SOURCE=.\ddutil.cpp
# End Source File
# Begin Source File

SOURCE=.\Game_init.cpp
# End Source File
# Begin Source File

SOURCE=.\Game_Input.cpp
# End Source File
# Begin Source File

SOURCE=.\Game_Main.cpp
# End Source File
# Begin Source File

SOURCE=.\Game_Shutdown.cpp
# End Source File
# Begin Source File

SOURCE=.\Renderer_Tools.cpp
# End Source File
# Begin Source File

SOURCE=.\Zero41.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "GameObjectHeaders"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AnimatedPopup.h
# End Source File
# Begin Source File

SOURCE=.\AnimatedTrack.h
# End Source File
# Begin Source File

SOURCE=.\Ball.h
# End Source File
# Begin Source File

SOURCE=.\Cart.h
# End Source File
# Begin Source File

SOURCE=.\Crusher.h
# End Source File
# Begin Source File

SOURCE=.\cursor.h
# End Source File
# Begin Source File

SOURCE=.\Dynamite.h
# End Source File
# Begin Source File

SOURCE=.\Jump.h
# End Source File
# Begin Source File

SOURCE=.\Popup.h
# End Source File
# Begin Source File

SOURCE=.\Powerup.h
# End Source File
# Begin Source File

SOURCE=.\RenderedObject.h
# End Source File
# Begin Source File

SOURCE=.\Sprite.h
# End Source File
# Begin Source File

SOURCE=.\StaticObj.h
# End Source File
# Begin Source File

SOURCE=.\Text.h
# End Source File
# Begin Source File

SOURCE=.\Track.h
# End Source File
# End Group
# Begin Group "MenuHeaders"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CMenuMain.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Cfilereader.h
# End Source File
# Begin Source File

SOURCE=.\CHighScores.h
# End Source File
# Begin Source File

SOURCE=.\CLevelData.h
# End Source File
# Begin Source File

SOURCE=.\CLogging.h
# End Source File
# Begin Source File

SOURCE=.\CRARExtractor.h
# End Source File
# Begin Source File

SOURCE=.\CSound.h
# End Source File
# Begin Source File

SOURCE=.\ddutil.h
# End Source File
# Begin Source File

SOURCE=.\Game_init.h
# End Source File
# Begin Source File

SOURCE=.\Game_Input.h
# End Source File
# Begin Source File

SOURCE=.\Game_Main.h
# End Source File
# Begin Source File

SOURCE=.\Game_Shutdown.h
# End Source File
# Begin Source File

SOURCE=.\Globals.h
# End Source File
# Begin Source File

SOURCE=.\Renderer_Tools.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\best.rar
# End Source File
# Begin Source File

SOURCE=.\Miner.ico
# End Source File
# Begin Source File

SOURCE=.\rar_files.rc
# End Source File
# Begin Source File

SOURCE=.\rarfile2.bin
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# End Group
# Begin Group "Unrarlib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\unrarlib.c
# End Source File
# Begin Source File

SOURCE=.\unrarlib.h
# End Source File
# End Group
# End Target
# End Project

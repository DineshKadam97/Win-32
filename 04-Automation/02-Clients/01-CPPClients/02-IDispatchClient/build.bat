cls

del *.exe

del *.res

del *.obj

cl.exe /c /EHsc Window.cpp

rc.exe Window.rc

link.exe Window.obj Window.res user32.lib oleaut32.lib gdi32.lib ole32.lib /SUBSYSTEM:WINDOWS
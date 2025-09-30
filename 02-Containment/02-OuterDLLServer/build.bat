cls

del *.exe

del *.res

del *.obj

cl.exe /c /EHsc ContainmentOuterDllServer.cpp

link.exe ContainmentOuterDllServer.obj user32.lib gdi32.lib kernel32.lib ole32.lib /DEF:ContainmentOuterDllServer.def /DLL /SUBSYSTEM:WINDOWS

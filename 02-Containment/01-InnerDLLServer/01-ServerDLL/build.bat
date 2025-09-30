cls

del *.exe

del *.res

del *.obj

cl.exe /c /EHsc ContainmentInnerDllServer.cpp

link.exe ContainmentInnerDllServer.obj user32.lib gdi32.lib kernel32.lib ole32.lib /DEF:ContainmentInnerDllServer.def /DLL /SUBSYSTEM:WINDOWS

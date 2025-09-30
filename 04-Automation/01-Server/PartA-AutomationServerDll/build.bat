cls

del *.exe

del *.res

del *.obj

cl.exe /c /EHsc AutomationServer.cpp

link.exe AutomationServer.obj user32.lib gdi32.lib kernel32.lib ole32.lib OleAut32.lib /DEF:AutomationServer.def /DLL /SUBSYSTEM:WINDOWS

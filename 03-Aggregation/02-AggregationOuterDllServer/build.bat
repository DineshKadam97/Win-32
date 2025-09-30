cls

del *.exe

del *.res

del *.obj

cl.exe /c /EHsc AggregationOuterDllServer.cpp

link.exe AggregationOuterDllServer.obj user32.lib gdi32.lib kernel32.lib ole32.lib /DEF:AggregationOuterDllServer.def /DLL /SUBSYSTEM:WINDOWS

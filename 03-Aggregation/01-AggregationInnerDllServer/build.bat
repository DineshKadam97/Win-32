cls

del *.exe

del *.res

del *.obj

cl.exe /c /EHsc AggregationInnerDllServer.cpp

link.exe AggregationInnerDllServer.obj user32.lib gdi32.lib kernel32.lib ole32.lib /DEF:AggregationInnerDllServer.def /DLL /SUBSYSTEM:WINDOWS

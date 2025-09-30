cls

del *.dll

del *.exp

del *.lib

del *.obj

cl.exe /c /EHsc /D REGISTER_PROXY_DLL AutomationProxyStub.c AutomationProxyStubDllData.c AutomationProxyStubGuids.c

link.exe AutomationProxyStub.obj  AutomationProxyStubDllData.obj AutomationProxyStubGuids.obj /DLL /DEF:AutomationProxyStub.def user32.lib oleaut32.lib advapi32.lib rpcns4.lib rpcrt4.lib /SUBSYTEM:WINDOWS


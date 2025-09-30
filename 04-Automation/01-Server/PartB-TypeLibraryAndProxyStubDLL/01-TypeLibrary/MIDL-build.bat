cls

del *.tlb

del *.c

del *.h

midl.exe /h AutomationProxyStubHeader.h /iid AutomationProxyStubGuids.c /dlldata AutomationProxyStubDllData.c /proxy AutomationProxyStub.c AutomationServerTypeLib.idl

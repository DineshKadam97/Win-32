1. The exported functionality is provided by interface IMyMath which is given in the     
    header file AutomationServer.h. The required CLSID and IID are also provided in the 
    same header file.

2. Copy both the dlls(AutomationServer.dll and AutomationProxyStub.dll) and type 
   library AutomationServerTypeLib.tlb to C:Windows/System32

3. Now double click on AutomationServer.reg file to register AutomationServer.dll and 
   AutomationServerTypeLib.tlb

4. Now open administrator command prompt or elevated command prompt in 
   C:Windows/System32 and register automationproxystub.dll by giving the command : 
     regsvr32.exe AutomationProxyStub.dll

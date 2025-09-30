cls 

del *.dll

tlbimp.exe C:\Windows\System32\AutomationServerTypeLib.tlb /out:.\AutomationServerTypeLibForDotNet.dll /machine:x64

ildasm.exe /adv AutomationServerTypeLibForDotNet.dll

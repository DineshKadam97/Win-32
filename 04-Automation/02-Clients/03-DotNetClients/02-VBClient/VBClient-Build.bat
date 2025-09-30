cls

del *.exe

VBC.exe /r:AutomationServerTypeLibForDotNet.dll /r:Microsoft.VisualBasic.dll /t:winexe VBAutomationClient.vb


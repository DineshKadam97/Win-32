Imports System.Windows.Forms
Imports AutomationServerTypeLibForDotNet

Public Class VBAutomationClient
    Inherits Form
    Public Sub New()
        Dim objCMyMathClass As New CMyMathClass()
        Dim objIMyMath As Object
        objIMyMath = objCMyMathClass

        Dim iNum1 = 175
        Dim iNum2 = 125

        Dim iSum = objIMyMath.SumOfTwoIntegers(iNum1, iNum2)
        Dim str As String = String.Format("Sum Of {0} And {1} Is {2}", iNum1, iNum2, iSum)
        MsgBox(str)

        Dim iSub = objIMyMath.SubtractionOfTwoIntegers(iNum1, iNum2)
        str = String.Format("Subtraction Of {0} And {1} Is {2}", iNum1, iNum2, iSub)
        MsgBox(str)
        End
    End Sub
    <STAThread()>
    Shared Sub Main()
        Application.EnableVisualStyles()
        Application.Run(New VBAutomationClient())
    End Sub
End Class

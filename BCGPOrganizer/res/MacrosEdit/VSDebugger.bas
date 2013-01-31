'' Copyright (c) Microsoft Corporation.  All rights reserved.
''
'' These samples demonstrate how to use the VS Automation Object Model.
'' They are unsupported, but you can use them as-is.  They are not intended 
'' to demonstrate how to implement fully rigorous commands.  For example, 
'' if a command expects there to be selected text, but you invoke
'' the macro on a blank line, the macro's behavior is undefined.
''
'Option Strict Off
'Option Explicit Off

Imports EnvDTE
Imports EnvDTE80
Imports System.Diagnostics
Imports Microsoft.VisualBasic
Imports Microsoft.VisualBasic.ControlChars

Public Module VSDebugger

    ' This macro steps through an entire program.
    Sub StepOverAll()
        DTE.Debugger.StepOver()
        While DTE.Debugger.CurrentMode <> dbgDebugMode.dbgDesignMode
            DTE.Debugger.StepOver()
        End While
    End Sub


    ' This macro dumps the stack for each thread running in the current program to the 
    ' command window.  The output format is identical to that of the call-stack window 
    ' except the current line is not printed.
    Sub DumpStacks()
        Dim commandWin As EnvDTE.CommandWindow

        commandWin = DTE.Windows.Item(EnvDTE.Constants.vsWindowKindCommandWindow).Object
        If DTE.Debugger.CurrentProgram Is Nothing Then
            commandWin.OutputString("No program is currently being debugged." + vbCrLf)
        Else
            Dim myThread As EnvDTE.Thread

            commandWin.OutputString("Current Program: " + DTE.Debugger.CurrentProgram.Name + vbCrLf)
            For Each myThread In DTE.Debugger.CurrentProgram.Threads
                Dim myFrame As EnvDTE.StackFrame

                commandWin.OutputString("" + vbTab + "Thread (" + Str(myThread.ID) + " ) " + myThread.Name + vbCrLf)

                For Each myFrame In myThread.StackFrames
                    Dim programModule As String
                    Dim pos As Integer
                    Dim functionName As String
                    Dim args As String
                    Dim myArg As EnvDTE.Expression
                    Dim i As Integer = 0

                    pos = InStrRev(myFrame.Module, "\")
                    functionName = myFrame.FunctionName
                    If pos > 0 Then
                        programModule = Right(myFrame.Module, Len(myFrame.Module) - pos)
                    Else
                        programModule = myFrame.Module
                    End If

                    'Create the argument list
                    For Each myArg In myFrame.Arguments
                        If i > 0 Then
                            args = args + ", "
                        End If
                        args = args + myArg.Type + " " + myArg.Name + "=" + myArg.Value
                        i = i + 1
                    Next

                    ' Output the frame information.
                    commandWin.OutputString("" + vbTab + vbTab + programModule + ": " + functionName + "(" + args + ")" + vbCrLf)
                Next
            Next
        End If

    End Sub

    ' Sets a pending breakpoint at the function named "main".  It marks the 
    ' breakpoint as one set by automation.
    Sub AddBreakpointToMain()
        Dim bp As EnvDTE.Breakpoint
        Dim bps As EnvDTE.Breakpoints

        bps = DTE.Debugger.Breakpoints.Add("main")
        For Each bp In bps
            bp.Tag = "SetByMacro"
        Next
    End Sub

    ' Runs to the next breakpoint set, if any. Displays a messagebox indicating exactly what occurred.
    Sub RunToNextBreakpoint()
        DTE.Debugger.Go(True)  ' Runs to next breakpoint or the end of the program.
        If DTE.Debugger.CurrentMode = dbgDebugMode.dbgBreakMode Then
            Dim bp As EnvDTE.Breakpoint

            bp = DTE.Debugger.BreakpointLastHit()   ' Retrieves the bound breakpoint that was hit.
            If bp.Parent().Tag = "SetByMacro" Then  ' Bound breakpoints always have a Pending Parent.
                MsgBox("Hit tagged breakpoint")
                bp.Enabled = False
            Else
                MsgBox("Hit untagged breakpoint")
            End If
        Else
            MsgBox("Program ended")
        End If
    End Sub

    ' This function dumps the names of all the breakpoints last hit to
    ' a new pane in the output window.
    Sub ListBreakpointsLastHit()
        Dim bppane As EnvDTE.OutputWindowPane
        Dim hitbps As EnvDTE.Breakpoints

        bppane = Utilities.GetOutputWindowPane("Debugger")
        hitbps = DTE.Debugger.AllBreakpointsLastHit
        If (hitbps.Count > 0) Then
            Dim bp As EnvDTE.Breakpoint

            For Each bp In DTE.Debugger.AllBreakpointsLastHit
                bppane.OutputString(bp.Name)
            Next
        Else
            bppane.OutputString("No breakpoints were hit")
        End If
    End Sub

    ' This function dumps the name of the breakpoints last hit to
    ' a new pane in the output window.
    Sub BreakpointLastHit()
        Dim bppane As EnvDTE.OutputWindowPane

        bppane = Utilities.GetOutputWindowPane("Debugger")
        If Not DTE.Debugger.BreakpointLastHit Is Nothing Then
            bppane.OutputString(DTE.Debugger.BreakpointLastHit.Name + vbCrLf)
        Else
            bppane.OutputString("No breakpoint was hit" + vbCrLf)
        End If

    End Sub

    ' This function dumps the names of all the breakpoints currently set to
    ' a new pane in the output window.
    Sub ListAllBreakpoints()
        Dim bppane As EnvDTE.OutputWindowPane
        Dim bps As EnvDTE.Breakpoints

        bppane = Utilities.GetOutputWindowPane("Debugger")
        bps = DTE.Debugger.Breakpoints
        If (bps.Count > 0) Then
            Dim bp As EnvDTE.Breakpoint

            For Each bp In bps
                bppane.OutputString(bp.Name + vbCrLf)
            Next
        Else
            bppane.OutputString("No breakpoints are set" + vbCrLf)
        End If
    End Sub

    ' This function displays the current debugger mode in a new
    ' pane in the output window.
    Sub DebuggerMode()
        Dim outputWinPane As EnvDTE.OutputWindowPane

        outputWinPane = Utilities.GetOutputWindowPane("Debugger")
        Select Case DTE.Debugger.CurrentMode
            Case dbgDebugMode.dbgBreakMode
                outputWinPane.OutputString("Break Mode" + vbCrLf)

            Case dbgDebugMode.dbgDesignMode
                outputWinPane.OutputString("Design Mode" + vbCrLf)

            Case dbgDebugMode.dbgRunMode
                outputWinPane.OutputString("Run Mode" + vbCrLf)
        End Select

    End Sub

    ' This function displays the current debugger mode in the output window.
    Sub ShowCurrentProcess()
        Dim outputWinPane As EnvDTE.OutputWindowPane
        Dim proc As EnvDTE.Process

        outputWinPane = Utilities.GetOutputWindowPane("Debugger")
        proc = DTE.Debugger.CurrentProcess
        If (proc Is Nothing) Then
            outputWinPane.OutputString("No process is being debugged")
        Else
            outputWinPane.OutputString("" + Str(proc.ProcessID) + ": " + proc.Name + vbCrLf)
        End If

    End Sub

    ' This function displays the reason break mode was entered in the output window.
    Sub LastBreakReason()
        Dim outputWinPane As EnvDTE.OutputWindowPane

        outputWinPane = Utilities.GetOutputWindowPane("Debugger")
        Select Case DTE.Debugger.LastBreakReason
            Case dbgEventReason.dbgEventReasonBreakpoint
                outputWinPane.OutputString("Breakpoint hit" + vbCrLf)

            Case dbgEventReason.dbgEventReasonNone
                outputWinPane.OutputString("No reason" + vbCrLf)

            Case dbgEventReason.dbgEventReasonExceptionNotHandled
                outputWinPane.OutputString("Exception not handled by the debuggee" + vbCrLf)

            Case dbgEventReason.dbgEventReasonExceptionThrown
                outputWinPane.OutputString("Exception thrown" + vbCrLf)

        End Select
    End Sub

    ' This subroutine attaches to calc.exe if it is running.
    Sub AttachToCalc()
        Dim attached As Boolean = False
        Dim proc As EnvDTE.Process

        For Each proc In DTE.Debugger.LocalProcesses
            If (Right(proc.Name, 8) = "calc.exe") Then
                proc.Attach()
                attached = True
                Exit For
            End If
        Next

        If attached = False Then
            MsgBox("calc.exe is not running")
        End If

    End Sub

    ' This subroutine outputs the lists of processes currently being debugged 
    ' to the output window.
    Sub ListDebuggedProcesses()
        Dim outputWinPane As EnvDTE.OutputWindowPane
        Dim proc As EnvDTE.Process

        outputWinPane = Utilities.GetOutputWindowPane("Debugger")
        If DTE.Debugger.DebuggedProcesses.Count = 0 Then
            outputWinPane.OutputString("No processes are being debugged." + vbCrLf)
        Else
            For Each proc In DTE.Debugger.DebuggedProcesses
                outputWinPane.OutputString("Process: [" + Str(proc.ProcessID) + "] " + proc.Name + vbCrLf)
            Next
        End If

    End Sub

    ' This subroutine displays all the languages supported by this debugger. The list
    ' is output to the output window.
    Sub SupportedLanguages()
        Dim outputWinPane As EnvDTE.OutputWindowPane
        Dim lang As EnvDTE.Language

        outputWinPane = Utilities.GetOutputWindowPane("Debugger")
        outputWinPane.OutputString("Debugger supports the following languages:" + vbCrLf)

        For Each lang In DTE.Debugger.Languages
            outputWinPane.OutputString(lang.Name + vbCrLf)
        Next

    End Sub

    ' This subroutine attempts to detach the debugger from all processes
    ' currently being debugged.
    Sub DetachAll()
        On Error GoTo BadDetach
        DTE.Debugger.DetachAll()
        Exit Sub

BadDetach:
        MsgBox("Could not detach from all processes.")

    End Sub

    ' This subroutine runs to the line number passed in for the currently active
    ' source document.  The parameter is a string instead of an integer because the
    ' command window will only allow the passing of string parameters.
    Sub RunToLine(Optional ByVal line As String = "-1")
        If Val(line) <> -1 Then
            Dim textSelection As EnvDTE.TextSelection

            textSelection = DTE.ActiveDocument.Selection
            textSelection.GotoLine(Val(line))
            DTE.Debugger.RunToCursor()
        End If
    End Sub

    ' This subroutine evaluates the given expression, displaying its value and 
    ' the names and values of each of its immediate data members. Run from 
    ' the command window so as to be able to pass an expression string.
    Sub DumpExpression(Optional ByVal expStr As String = "")
        Dim commandWindow As EnvDTE.CommandWindow
        Dim expression As EnvDTE.Expression

        commandWindow = DTE.Windows.Item(EnvDTE.Constants.vsWindowKindCommandWindow).Object
        expression = DTE.Debugger.GetExpression(expStr, True)
        If expression.IsValidValue Then
            Dim i As Integer = 1

            commandWindow.OutputString(expStr & " = " & expression.Value & vbCrLf)
            While i <= expression.DataMembers.Count
                commandWindow.OutputString(vbTab & expression.DataMembers.Item(i).Name & " = " & expression.DataMembers.Item(i).Value & vbCrLf)
                i = i + 1
            End While
        Else
            commandWindow.OutputString(expStr & " = Invalid value")
        End If

    End Sub

    ' IsDebugging is a helper function for general use.
    Function IsDebugging() As Boolean
        If (DTE.Debugger Is Nothing) Then
            MsgBox("Debugger doesn't exist! Fatal error.")
            Exit Function
        Else
            IsDebugging = (DTE.Debugger.CurrentMode <> dbgDebugMode.dbgDesignMode)
        End If
    End Function

End Module

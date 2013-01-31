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
Imports System.Windows
Imports System.Windows.Forms
Imports System

Public Module Utilities

    ' To run the temporary macro a specified number of times,
    ' copy this commented out macro to the active recording module
    ' and uncomment it.
    'Sub RepeatTempMacro()
    '    Dim i As Integer
    '    Dim num As Integer
    '
    '    num = CType(inputbox("Repeat macro how many times? "), Integer)
    '    For i = 1 To num
    '        temporarymacro()
    '    Next
    'End Sub

    ''
    '' Saving and loading a window layout by name.
    ''

    '' SaveView stores the current window layout into a named view.
    ''
    Sub SaveView()
        Dim name As String

        name = InputBox("Enter the name you want to save as:", "Save window layout")
        If (name = "") Then
            MsgBox("Empty string, enter a valid name.")
        Else
            DTE.WindowConfigurations.Add(name)
        End If
    End Sub

    '' LoadView retrieves the named window layout and applies it.
    ''
    Sub LoadView()
        Dim name As String

        name = InputBox("Which window layout would you like to load?", "Load Window Layout")
        If (name = "") Then
            MsgBox("Empty string, enter a window layout name")
        Else
            DTE.WindowConfigurations.Item(name).Apply()
        End If
    End Sub

    '' 
    '' Turning on and off line numbers in the text editor's view.
    ''

    '' TurnOnLineNumbers turns on line numbers in the text editor view.
    ''
    Sub TurnOnLineNumbers()
        DTE.Properties("TextEditor", "Basic").Item("ShowLineNumbers").Value = True
        DTE.Properties("TextEditor", "PlainText").Item("ShowLineNumbers").Value = True
        DTE.Properties("TextEditor", "CSharp").Item("ShowLineNumbers").Value = True
        DTE.Properties("TextEditor", "HTML").Item("ShowLineNumbers").Value = True
        DTE.Properties("TextEditor", "C/C++").Item("ShowLineNumbers").Value = True
        DTE.Properties("TextEditor", "Visual JSharp").Item("ShowLineNumbers").Value = True
        DTE.Properties("TextEditor", "XML").Item("ShowLineNumbers").Value = True
    End Sub

    '' TurnOffLineNumbers turns off displaying line numbers in the text editor view.
    ''
    Sub TurnOffLineNumbers()
        DTE.Properties("TextEditor", "Basic").Item("ShowLineNumbers").Value = False
        DTE.Properties("TextEditor", "PlainText").Item("ShowLineNumbers").Value = False
        DTE.Properties("TextEditor", "CSharp").Item("ShowLineNumbers").Value = False
        DTE.Properties("TextEditor", "HTML").Item("ShowLineNumbers").Value = False
        DTE.Properties("TextEditor", "C/C++").Item("ShowLineNumbers").Value = False
        DTE.Properties("TextEditor", "Visual JSharp").Item("ShowLineNumbers").Value = False
        DTE.Properties("TextEditor", "XML").Item("ShowLineNumbers").Value = False
    End Sub

    ''
    '' Turning on and off word wrap for all languages.
    ''

    '' TurnOnWordWrap turns on word wrapping in the text editor view so that
    '' you don't need horizontal scroll bars while editing.
    ''
    Sub TurnOnWordWrap()
        DTE.Properties("TextEditor", "Basic").Item("WordWrap").Value = True
        DTE.Properties("TextEditor", "PlainText").Item("WordWrap").Value = True
        DTE.Properties("TextEditor", "CSharp").Item("WordWrap").Value = True
        DTE.Properties("TextEditor", "HTML").Item("WordWrap").Value = True
        DTE.Properties("TextEditor", "C/C++").Item("WordWrap").Value = True
        DTE.Properties("TextEditor", "Visual JSharp").Item("WordWrap").Value = True
        DTE.Properties("TextEditor", "XML").Item("WordWrap").Value = True
    End Sub

    '' TurnOffWordWrap turns off word wrapping in the text editor view.
    ''
    Sub TurnOffWordWrap()
        DTE.Properties("TextEditor", "Basic").Item("WordWrap").Value = False
        DTE.Properties("TextEditor", "PlainText").Item("WordWrap").Value = False
        DTE.Properties("TextEditor", "CSharp").Item("WordWrap").Value = False
        DTE.Properties("TextEditor", "HTML").Item("WordWrap").Value = False
        DTE.Properties("TextEditor", "C/C++").Item("WordWrap").Value = False
        DTE.Properties("TextEditor", "Visual JSharp").Item("WordWrap").Value = False
        DTE.Properties("TextEditor", "XML").Item("WordWrap").Value = False
    End Sub



    ''
    '' The next few routines demonstrate walking a project in a project-independent way.
    '' This example is important due to the way VC implements its
    '' ProjectItems collection.  VC lists all files in its top-level ProjectItems
    '' collection, and it lists those files in the ProjectItems collections
    '' associated with each folder node. However, the ProjectItem.Collection
    '' property always returns the ProjectItems collection where the item
    '' is hierarchically.  Only files actually shown directly under the
    '' the project node in Solution Explorer return the Project.ProjectItems
    '' collection for ProjectItem.Collection.
    ''

    '' ListProj iterates all the items in a project and writes their names,
    '' including folder node names and using indentation to show the
    '' hierarchy of the project.  The output appears in the Output Window by
    '' default, but if you invoke this in the Command Window, it delivers its
    '' output to the Command Window.
    ''
    Sub ListProj()
        Dim project As Project
        Dim projectObjects As Object()
        Dim window As Window
        Dim target As Object

        window = DTE.Windows.Item(Constants.vsWindowKindCommandWindow)
        projectObjects = DTE.ActiveSolutionProjects
        If projectObjects.Length = 0 Then
            Exit Sub
        End If
        project = DTE.ActiveSolutionProjects(0)
        If (DTE.ActiveWindow Is window) Then
            target = window.Object
        Else
            target = GetOutputWindowPane("List Project")
            target.Clear()
        End If
        ListProjAux(project.ProjectItems(), 0, target)
    End Sub

    Sub ListProjAux(ByVal projectItems As EnvDTE.ProjectItems, ByVal level As Integer, ByVal outputWinPane As Object)
        Dim projectItem As EnvDTE.ProjectItem

        For Each projectItem In projectItems
            '' Ignore item if it is not rooted in this collection (check for VC project model).
            If projectItem.Collection Is projectItems Then
                Dim projectItems2 As EnvDTE.ProjectItems
                Dim notSubCollection As Boolean

                OutputItem(projectItem, level, outputWinPane)
                '' Recurse if this item has subitems ...
                projectItems2 = projectItem.ProjectItems
                notSubCollection = projectItems2 Is Nothing
                If Not notSubCollection Then
                    ListProjAux(projectItems2, level + 1, outputWinPane)
                End If
            End If
        Next
    End Sub

    Sub OutputItem(ByVal projectItem As EnvDTE.ProjectItem, ByVal level As Integer, ByVal outputWinPane As Object)
        Dim i As Integer = 0

        While (i < level)
            outputWinPane.OutputString("    ")
            i = i + 1
        End While
        outputWinPane.OutputString(projectItem.FileNames(1))
        outputWinPane.OutputString(Microsoft.VisualBasic.Constants.vbCrLf)
    End Sub

    ''
    '' Miscellaneous commands
    ''

    '' This command wraps a classic COM typelib, runs tlbimp to produce
    '' managed wrappers, puts that DLL in the VSMacros rundir (the PublicAssemblies
    '' subdirectory where you installed devenv.exe), and adds a project reference
    '' to the managed wrappers.
    ''
    '' NOTE: If you run this while the macros debugger is running, you will see an error.
    ''       This macro should only be run from the Macros Explorer inside of Visual Studio.
    Sub AddClassicComRef()
        Dim systemDirectory, outputFileName, outputDirectory As String
        Dim sdkDirectory, macroProjectName As String
        Dim projectToAddReferenceTo As VSLangProj.VSProject
        Dim openFileDialog As Forms.FileDialog
        Dim tlbimpPath As Microsoft.Win32.RegistryKey
        Dim winptr As WinWrapper

        Try
            winptr = New WinWrapper
            openFileDialog = New Forms.OpenFileDialog

            ' Set the initial directory to SystemDrive.
            systemDirectory = System.Environment.SystemDirectory()
            systemDirectory = Left(systemDirectory, InStr(systemDirectory, "\", CompareMethod.Text))
            openFileDialog.InitialDirectory = systemDirectory
            openFileDialog.Filter = "Type Libraries (*.tlb)|*.tlb|DLLs (*.dll)|*.dll|All files (*.*)|*.*"
            openFileDialog.FilterIndex = 1
            openFileDialog.Title = "Open COM type library"

            If openFileDialog.ShowDialog(winptr) = Forms.DialogResult.OK Then

                ' Create the output file name.
                outputFileName = Right(openFileDialog.FileName, Len(openFileDialog.FileName) - Len(System.Environment.CurrentDirectory) - 1)
                outputFileName = Left(outputFileName, InStr(outputFileName, ".", CompareMethod.Text) - 1)
                outputFileName = outputFileName & ".dll"

                ' Set the output directory to the VsMacros dir.
                outputDirectory = Left(DTE.FullName, InStr(DTE.FullName, "devenv.exe", CompareMethod.Text) - 1)
                outputDirectory = outputDirectory & "PublicAssemblies\"

                tlbimpPath = Microsoft.Win32.Registry.LocalMachine.OpenSubKey("software\microsoft\.NetFramework")
                If Not tlbimpPath Is Nothing Then
                    sdkDirectory = tlbimpPath.GetValue("SDKInstallRootv2.0", "") & "bin"
                End If
                If sdkDirectory = "bin" Then
                    MsgBox("Unable to get tlbimp.exe location from registry")
                    Exit Sub
                End If

                Microsoft.VisualBasic.ChDir(sdkDirectory)
                Microsoft.VisualBasic.Shell("cmd /c tlbimp.exe """ & openFileDialog.FileName & """ /out:""" & outputDirectory & outputFileName & """", AppWinStyle.NormalFocus, True)

                ' Get the project to add refernce to.
                macroProjectName = InputBox("Please enter the project to add the reference to (entering nothing or canceling will default to the first project in the solution)", "AddComReference")
                If Len(macroProjectName) = 0 Then
                    ' If no name specified, adds to the first macro project.
                    projectToAddReferenceTo = DTE.MacrosIDE.Solution.Projects.Item(1).Object
                Else
                    Dim project As EnvDTE.Project

                    For Each project In DTE.MacrosIDE.Solution.Projects
                        If project.Name = macroProjectName Then
                            projectToAddReferenceTo = project.Object
                        End If
                    Next
                End If

                If projectToAddReferenceTo Is Nothing Then
                    MsgBox("Was unable to grab Macros solution project")
                    Exit Sub
                End If

                openFileDialog.FileName = outputDirectory & outputFileName
                If openFileDialog.CheckFileExists() = False Then
                    MsgBox("Was unable to create COM+ wrapper")
                    Exit Sub
                End If

                If projectToAddReferenceTo.References.Add(outputDirectory & outputFileName) Is Nothing Then
                    MsgBox("Was unable to add the reference")
                End If
            End If
        Catch err As System.Exception
            MsgBox(err.Message)
        End Try
    End Sub


    '' FindCase launches the Find dialog and sets case sensitivity on.
    ''
    Sub FindCase()
        DTE.ExecuteCommand("Edit.Find")
        DTE.Find.MatchCase = True
    End Sub

    '' FindLastTarget launches the Find dialog guaranteeing to use last
    '' find target, overriding the default tools option that causes
    '' Find to pick up an unselected word from the editor.
    ''
    Sub FindLastTarget()
        Dim findWhatLast As String

        findWhatLast = DTE.Find.FindWhat  ' Fetch before launching dialog to return last pattern.
        DTE.ExecuteCommand("Edit.Find")
        DTE.Find.FindWhat = findWhatLast
    End Sub

    '' FindLine launches the Find dialog, seeding pattern with current line.
    ''
    Sub FindLine()
        Dim textSelection As TextSelection

        textSelection = DTE.ActiveDocument.Selection
        textSelection.CharLeft(True)
        DTE.ExecuteCommand("Edit.Find")
        DTE.Find.FindWhat = textSelection.Text
    End Sub

    '' ListModifiedDocuments lists in the Output Window all the open documents
    '' that are currently dirty (need to be saved).
    ''
    Sub ListModifiedDocuments()
        Dim window As Window
        Dim target As Object
        Dim document As EnvDTE.Document

        window = DTE.Windows.Item(Constants.vsWindowKindCommandWindow)
        If (DTE.ActiveWindow Is window) Then
            target = window.Object
        Else
            target = GetOutputWindowPane("Modified Documents")
            target.clear()
        End If

        For Each document In DTE.Documents
            If Not document.Saved Then
                target.OutputString(document.Name & "   " & document.FullName & Microsoft.VisualBasic.Constants.vbCrLf)
            End If
        Next
    End Sub

    '' InsertDocComments goes through the current document using the VS Code Model
    '' to add documentation style comments to each function.
    ''
    Sub InsertDocComments()
        Dim projectItem As ProjectItem
        Dim fileCodeModel As FileCodeModel
        Dim codeElement As CodeElement
        Dim codeElementType As CodeType
        Dim editPoint As EditPoint
        Dim commentStart As String

        projectItem = DTE.ActiveDocument.ProjectItem
        fileCodeModel = projectItem.FileCodeModel
        codeElement = fileCodeModel.CodeElements.Item(1)

        '' For the sample, don't bother recursively descending all code like
        '' the OutlineCode sample does. Just get a first CodeType in the
        '' file.
        If (TypeOf codeElement Is CodeNamespace) Then
            codeElement = codeElement.members.item(1)
        End If
        If (TypeOf codeElement Is CodeType) Then
            codeElementType = CType(codeElement, CodeType)
        Else
            Throw New Exception("Didn't find a type definition as first thing in file or find a namespace as the first thing with a type inside the namespace.")
        End If

        editPoint = codeElementType.GetStartPoint(vsCMPart.vsCMPartHeader).CreateEditPoint()

        '' Make doc comment start.
        commentStart = LineOrientedCommentStart()
        If (commentStart.Length = 2) Then
            commentStart = commentStart & commentStart.Chars(1) & " "
        ElseIf (commentStart.Length = 1) Then
            commentStart = commentStart & commentStart.Chars(0) & commentStart.Chars(0) & " "
        End If

        '' Make this atomically undo'able.  Use Try...Finally to ensure Undo
        '' Context is close.
        Try
            DTE.UndoContext.Open("Insert Doc Comments")

            '' Iterate over code elements emitting doc comments for functions.
            For Each codeElement In codeElementType.Members
                If (codeElement.Kind = vsCMElement.vsCMElementFunction) Then
                    '' Get Params.
                    Dim parameters As CodeElements
                    Dim codeFunction As CodeFunction
                    Dim codeElement2 As CodeElement
                    Dim codeParameter As CodeParameter

                    codeFunction = codeElement
                    editPoint.MoveToPoint(codeFunction.GetStartPoint(vsCMPart.vsCMPartHeader))
                    'editPoint.LineUp()
                    parameters = codeFunction.Parameters

                    '' Do comment.
                    editPoint.Insert(Microsoft.VisualBasic.Constants.vbCrLf)
                    editPoint.LineUp()
                    editPoint.Insert(Microsoft.VisualBasic.Constants.vbTab & commentStart & "<summary>")
                    editPoint.Insert(Microsoft.VisualBasic.Constants.vbCrLf)
                    editPoint.Insert(Microsoft.VisualBasic.Constants.vbTab & commentStart & "Summary of " & codeElement.Name & ".")
                    editPoint.Insert(Microsoft.VisualBasic.Constants.vbCrLf)
                    editPoint.Insert(Microsoft.VisualBasic.Constants.vbTab & commentStart & "</summary>")
                    editPoint.Insert(Microsoft.VisualBasic.Constants.vbCrLf)
                    editPoint.Insert(Microsoft.VisualBasic.Constants.vbTab & commentStart)

                    For Each codeElement2 In parameters
                        codeParameter = codeElement2
                        editPoint.Insert("<param name=" & codeParameter.Name & "></param>")
                        editPoint.Insert(Microsoft.VisualBasic.Constants.vbCrLf)
                        editPoint.Insert(Microsoft.VisualBasic.Constants.vbTab & commentStart)
                    Next 'param
                End If 'we have a function
            Next 'code elt member
        Finally
            DTE.UndoContext.Close()
        End Try
    End Sub



    '' ListMacroSamples demonstrates using the UIHierarchy object that some VS
    '' tool windows use, such as the Macros Expl and Solution Expl windows.
    ''
    Sub ListMacroSamples()
        Dim uiHierarchy As UIHierarchy
        Dim samplesUIHierarchy As UIHierarchyItem
        Dim outputWindowPane As OutputWindowPane
        Dim uiHierarchyItem As UIHierarchyItem

        uiHierarchy = DTE.Windows.Item(Constants.vsWindowKindMacroExplorer).Object
        samplesUIHierarchy = uiHierarchy.GetItem("Macros\Samples")
        outputWindowPane = Utilities.GetOutputWindowPane("List Macros")
        outputWindowPane.Clear()

        For Each uiHierarchyItem In samplesUIHierarchy.UIHierarchyItems
            Dim macroUIHierarchyItem As UIHierarchyItem

            outputWindowPane.OutputString(uiHierarchyItem.Name & Microsoft.VisualBasic.Constants.vbCrLf)
            For Each macroUIHierarchyItem In uiHierarchyItem.UIHierarchyItems
                outputWindowPane.OutputString("   " & macroUIHierarchyItem.Name & Microsoft.VisualBasic.Constants.vbCrLf)
            Next
        Next
    End Sub

    ''
    '' Helper functions for this and other modules.
    ''
    Function LineOrientedCommentStart(Optional ByVal document As Document = Nothing) As String
        Dim extension As String

        If (document Is Nothing) Then
            document = DTE.ActiveDocument
        End If

        extension = document.Name
        If (extension.EndsWith(".cs") Or extension.EndsWith(".cpp") Or extension.EndsWith(".h") Or extension.EndsWith(".idl") Or extension.EndsWith(".jsl")) Then
            Return "//"
        ElseIf (extension.EndsWith(".vb")) Then
            Return "'"
        Else
            Throw New Exception("Unrecognized file type. You can add this file type by modifying the function Utilities.LineOrientedCommentStart to include the extension of this file.")
        End If
    End Function

    Function GetOutputWindowPane(ByVal Name As String, Optional ByVal show As Boolean = True) As OutputWindowPane
        Dim window As Window
        Dim outputWindow As OutputWindow
        Dim outputWindowPane As OutputWindowPane

        window = DTE.Windows.Item(EnvDTE.Constants.vsWindowKindOutput)
        If show Then window.Visible = True
        outputWindow = window.Object
        Try
            outputWindowPane = outputWindow.OutputWindowPanes.Item(Name)
        Catch e As System.Exception
            outputWindowPane = outputWindow.OutputWindowPanes.Add(Name)
        End Try
        outputWindowPane.Activate()
        Return outputWindowPane
    End Function

    Function PrepareDefaultFind(ByVal prompt As String) As String
        Dim what As String

        DTE.Find.MatchWholeWord = False
        DTE.Find.Action = vsFindAction.vsFindActionFind
        DTE.Find.Target = vsFindTarget.vsFindTargetCurrentDocument
        DTE.Find.MatchCase = False
        DTE.Find.Backwards = False
        DTE.Find.MatchInHiddenText = True
        DTE.Find.PatternSyntax = vsFindPatternSyntax.vsFindPatternSyntaxLiteral

        what = InputBox(prompt)
        If (what <> "") Then
            DTE.Find.FindWhat = what
        End If
        Return what
    End Function

End Module

'' This class is used to set the proper parent to any UI that you may display from within a macro.
''  See the AddClassicComRef macro for an example of how this is used
Public Class WinWrapper
    Implements System.Windows.Forms.IWin32Window

    Overridable ReadOnly Property Handle() As System.IntPtr Implements System.Windows.Forms.IWin32Window.Handle
        Get
            Dim iptr As New System.IntPtr(DTE.MainWindow.HWnd)
            Return iptr
        End Get
    End Property
End Class

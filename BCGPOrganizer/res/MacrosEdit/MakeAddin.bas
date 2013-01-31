'' Copyright (c) Microsoft Corporation.  All rights reserved.
''
'' These samples demonstrate how to use the VS Automation Object Model.
'' They are unsupported, but you can use them as-is.  They are not intended 
'' to demonstrate how to implement fully rigorous commands.  For example, 
'' if a command expects there to be selected text, but you invoke
'' the macro on a blank line, the macro's behavior is undefined.
''

Option Strict Off
Option Explicit Off

Imports EnvDTE
Imports EnvDTE80
Imports System.Diagnostics

Public Module MakeAddin

    ' This sample converts a macros project into an Add-in by moving the necessary code from 
    '  the macro project to the Add-in. 
    Sub MakeAddinFromMacroProj()
        Dim projItem As EnvDTE.ProjectItem
        Dim queryStatusCode As String
        Dim execCode As String
        Dim onConnectionCode As String
        Dim execEditPoint As EnvDTE.EditPoint
        Dim proj As EnvDTE.Project
        Dim macroProject As EnvDTE.Project
        Dim connectProjectItem As EnvDTE.ProjectItem
        Dim objExecCodeElement As EnvDTE.CodeElement
        Dim queryStatusCodeElement As EnvDTE.CodeElement
        Dim onConnectionCodeElement As EnvDTE.CodeElement
        Dim connectCodeElement As EnvDTE.CodeElement
        Dim macroProjectSrc As String
        Dim completionMessage As String

        ' Try to verify that the item is an Add-in.
        Try
            Dim members As EnvDTE.CodeElements

            proj = DTE.ActiveSolutionProjects(0)
            connectProjectItem = proj.ProjectItems.Item("Connect.vb")
            connectCodeElement = connectProjectItem.FileCodeModel.CodeElements.Item("Connect")
            members = CType(connectCodeElement, CodeType).Members
            objExecCodeElement = members.Item("Exec")
            queryStatusCodeElement = members.Item("QueryStatus")
            onConnectionCodeElement = members.Item("OnConnection")
        Catch
            MsgBox("Could not find the proper items in the project." + vbLf + "To use this macro run the Add-in wizard, select VB as the programming language and select to create a Tools Menu item.", MsgBoxStyle.Exclamation, "CreateAddinFromMacros")
            Exit Sub
        End Try

        If (MsgBox("Warning: Running this macro will replace the Exec, QueryStatus, and OnConnection of your Add-in." + vbLf + vbLf + _
                "Do you wish to continue?", MsgBoxStyle.YesNo + MsgBoxStyle.Exclamation, "Create Addin From Macros") = MsgBoxResult.No) Then
            Return
        End If

        macroProjectSrc = InputBox("Enter the name of the Macro Project to create an Add-in out of")
        If Len(macroProjectSrc) = 0 Then
            ' If no name specified, adds to the first macro project.
            macroProject = DTE.MacrosIDE.Solution.Projects.Item(1)
        Else
            Dim objProjenum As EnvDTE.Project

            For Each objProjenum In DTE.MacrosIDE.Solution.Projects
                If objProjenum.Name = macroProjectSrc Then
                    macroProject = objProjenum
                End If
            Next
        End If

        If macroProject Is Nothing Then
            MsgBox("Could not find the specified macro project", MsgBoxStyle.Exclamation, "Make Add-in From Macro Project")
            Exit Sub
        End If

        ' Generate the beginning part of the Exec, QueryStatus, and OnConnection code:
        execCode = "Public Sub Exec(ByVal commandName As String, ByVal executeOption As vsCommandExecOption, ByRef varIn As Object, ByRef varOut As Object, ByRef handled As Boolean) Implements IDTCommandTarget.Exec" + vbLf
        execCode = execCode + "   handled = False" + vbLf
        execCode = execCode + "   If (executeOption = vsCommandExecOption.vsCommandExecOptionDoDefault) Then" + vbLf

        queryStatusCode = "Public Sub QueryStatus(ByVal commandName As String, ByVal neededText As vsCommandStatusTextWanted, ByRef status As vsCommandStatus, ByRef commandText As Object) Implements IDTCommandTarget.QueryStatus" + vbLf
        queryStatusCode = queryStatusCode + "status = vsCommandStatus.vsCommandStatusUnsupported" + vbLf
        queryStatusCode = queryStatusCode + "If neededText = EnvDTE.vsCommandStatusTextWanted.vsCommandStatusTextWantedNone Then" + vbLf

        onConnectionCode = "Public Sub OnConnection(ByVal application As Object, ByVal connectMode As ext_ConnectMode, ByVal addInInst As Object, ByRef custom As System.Array) Implements IDTExtensibility2.OnConnection" + vbLf
        onConnectionCode = onConnectionCode + "_applicationObject = CType(Application, EnvDTE80.DTE2)" + vbLf
        onConnectionCode = onConnectionCode + "_addInInstance = CType(addInInst, EnvDTE.AddIn)" + vbLf
        onConnectionCode = onConnectionCode + "If connectMode = ext_ConnectMode.ext_cm_UISetup Then" + vbLf
        onConnectionCode = onConnectionCode + "Dim objAddIn As AddIn = CType(addInInst, AddIn)" + vbLf
        onConnectionCode = onConnectionCode + "Dim CommandObj As Command" + vbLf
        onConnectionCode = onConnectionCode + "Dim objCommandBar As CommandBar" + vbLf + vbLf
        onConnectionCode = onConnectionCode + "'If your command no longer appears on the appropriate command bar, or if you would like to re-create the command," + vbLf
        onConnectionCode = onConnectionCode + "' close all instances of Visual Studio .NET, open a command prompt (MS-DOS window), and run the command 'devenv /setup'." + vbLf
        onConnectionCode = onConnectionCode + "objCommandBar = CType(_applicationObject.Commands.AddCommandBar(""" + macroProject.Name + """, vsCommandBarType.vsCommandBarTypeMenu, _applicationObject.CommandBars.Item(""Tools"")), Microsoft.VisualStudio.CommandBars.CommandBar)" + vbLf + vbLf

        ' Walk each item in the macro project, and duplicate it in the Add-in project.
        For Each projItem In macroProject.ProjectItems
            Dim win As EnvDTE.Window = projItem.Open(EnvDTE.Constants.vsViewKindCode)
            Dim doc As EnvDTE.Document = win.Document
            Dim textDoc As EnvDTE.TextDocument = doc.Object("TextDocument")
            Dim docText As String = textDoc.StartPoint.CreateEditPoint().GetText(textDoc.EndPoint)

            If (True) Then '((projItem.FileCodeModel.CodeElements.Item(1).Kind = vsCMElement.vsCMElementModule) Or (projItem.FileCodeModel.CodeElements.Item(1).Kind = vsCMElement.vsCMElementClass)) Then
                Dim newTextDocument As EnvDTE.TextDocument
                Dim newProjectItem As EnvDTE.ProjectItem
                Dim textSel As EnvDTE.TextSelection
                Dim newCodeModel As FileCodeModel
                Dim moduleCodeElement As EnvDTE.CodeElement
                Dim codeElt As EnvDTE.CodeElement

                newProjectItem = DTE.ItemOperations.AddNewItem("Visual Basic Items\Module", projItem.Name + ".vb")

                newTextDocument = newProjectItem.Document.Object("TextDocument")

                ' When adding a new item (from ItemOperations.AddNewItem), it places some default code
                '  into the new file. Delete that code here:
                newTextDocument.Selection.SelectAll()
                textSel = newTextDocument.Selection
                textSel.Delete()

                ' EnvironmentEvents already has 'Option Strict Off', don't do it again.
                If (projItem.Name <> "EnvironmentEvents") Then
                    textSel.Insert("Option Strict Off" + vbLf)
                End If
                textSel.Insert(docText)

                ' Macros require the module name to be the same as the file name of the
                '  item. Use that here to find the module in the code model:
                newCodeModel = newProjectItem.FileCodeModel()
                moduleCodeElement = newCodeModel.CodeElements.Item(projItem.Name)
                textSel = newTextDocument.Selection
                textSel.MoveToPoint(moduleCodeElement.GetStartPoint(vsCMPart.vsCMPartWhole), False)
                textSel.EndOfLine(False)

                ' If the file being generated is a class, then the DTE variable must be shared.
                If (projItem.FileCodeModel.CodeElements.Item(1).Kind = vsCMElement.vsCMElementClass) Then
                    textSel.Insert(vbLf + vbTab + "public shared DTE as EnvDTE80.DTE2")
                Else
                    textSel.Insert(vbLf + vbTab + "public Dim DTE as EnvDTE80.DTE2")
                End If

                ' Now create the QueryStatus, Exec & OnConnection for the Add-in:
                For Each codeElt In CType(moduleCodeElement, CodeType).Members()
                    If (codeElt.Kind = vsCMElement.vsCMElementFunction) Then
                        Dim codeFunc As EnvDTE.CodeFunction = codeElt

                        If (IsMacroCallableFunction(codeFunc) = True) Then
                            Dim commandName As String = proj.Name + ".Connect." + codeFunc.Name

                            execCode = execCode + "If commandName = """ + commandName + """ Then" + vbLf
                            execCode = execCode + "handled = True" + vbLf
                            execCode = execCode + projItem.Name + ".DTE = _applicationObject" + vbLf
                            execCode = execCode + projItem.Name + "." + codeFunc.Name + "()" + vbLf
                            execCode = execCode + "Exit Sub" + vbLf + "End If" + vbLf

                            queryStatusCode = queryStatusCode + "If commandName = """ + commandName + """Then" + vbLf
                            queryStatusCode = queryStatusCode + "status = CType(vsCommandStatus.vsCommandStatusEnabled + vsCommandStatus.vsCommandStatusSupported, vsCommandStatus)" + vbLf + "End If" + vbLf

                            onConnectionCode = onConnectionCode + "CommandObj = _applicationObject.Commands.AddNamedCommand(objAddIn, """ + codeFunc.Name + """, """ + codeFunc.Name + """, ""TODO: Enter your command description"", True, 59, Nothing, 1 + 2)  '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled" + vbLf
                            onConnectionCode = onConnectionCode + "CommandObj.AddControl(objCommandBar)" + vbLf
                        End If
                    End If
                Next
            End If
        Next

        ' Generate the end portion of the Exec, QueryStatus, and OnConnection methods,
        '  and then replace the code in the Add-in with the generated code.
        execCode = execCode + "End If" + vbLf + "End Sub" + vbLf

        objExecCodeElement = CType(connectCodeElement, CodeType).Members().Item("Exec")
        execEditPoint = objExecCodeElement.GetStartPoint(vsCMPart.vsCMPartWhole).CreateEditPoint()
        execEditPoint.Delete(objExecCodeElement.GetEndPoint(vsCMPart.vsCMPartWhole))
        execEditPoint.Insert(execCode)

        queryStatusCode = queryStatusCode + vbLf + "End If" + vbLf + "End Sub"
        queryStatusCodeElement = CType(connectCodeElement, CodeType).Members().Item("QueryStatus")
        execEditPoint = queryStatusCodeElement.GetStartPoint(vsCMPart.vsCMPartWhole).CreateEditPoint()
        execEditPoint.Delete(queryStatusCodeElement.GetEndPoint(vsCMPart.vsCMPartWhole))
        execEditPoint.Insert(queryStatusCode)

        onConnectionCode = onConnectionCode + "Else" + vbLf
        onConnectionCode = onConnectionCode + "'If you are not using events, you may wish to remove some of these to increase performance." + vbLf
        onConnectionCode = onConnectionCode + "EnvironmentEvents.DTEEvents = CType(_applicationObject.Events.DTEEvents, EnvDTE.DTEEvents)" + vbLf
        onConnectionCode = onConnectionCode + "EnvironmentEvents.DocumentEvents = CType(_applicationObject.Events.DocumentEvents(Nothing), EnvDTE.DocumentEvents)" + vbLf
        onConnectionCode = onConnectionCode + "EnvironmentEvents.WindowEvents = CType(_applicationObject.Events.WindowEvents(Nothing), EnvDTE.WindowEvents)" + vbLf
        onConnectionCode = onConnectionCode + "EnvironmentEvents.TaskListEvents = CType(_applicationObject.Events.TaskListEvents(""""), EnvDTE.TaskListEvents)" + vbLf
        onConnectionCode = onConnectionCode + "EnvironmentEvents.FindEvents = CType(_applicationObject.Events.FindEvents, EnvDTE.FindEvents)" + vbLf
        onConnectionCode = onConnectionCode + "EnvironmentEvents.OutputWindowEvents = CType(_applicationObject.Events.OutputWindowEvents(""""), EnvDTE.OutputWindowEvents)" + vbLf
        onConnectionCode = onConnectionCode + "EnvironmentEvents.SelectionEvents = CType(_applicationObject.Events.SelectionEvents, EnvDTE.SelectionEvents)" + vbLf
        onConnectionCode = onConnectionCode + "EnvironmentEvents.SolutionItemsEvents = CType(_applicationObject.Events.SolutionItemsEvents, EnvDTE.ProjectItemsEvents)" + vbLf
        onConnectionCode = onConnectionCode + "EnvironmentEvents.MiscFilesEvents = CType(_applicationObject.Events.MiscFilesEvents, EnvDTE.ProjectItemsEvents)" + vbLf
        onConnectionCode = onConnectionCode + "EnvironmentEvents.DebuggerEvents = CType(_applicationObject.Events.DebuggerEvents, EnvDTE.DebuggerEvents)" + vbLf
        onConnectionCode = onConnectionCode + "End If" + vbLf
        onConnectionCode = onConnectionCode + "End Sub"
        onConnectionCodeElement = CType(connectCodeElement, CodeType).Members().Item("OnConnection")
        execEditPoint = onConnectionCodeElement.GetStartPoint(vsCMPart.vsCMPartWhole).CreateEditPoint()
        execEditPoint.Delete(onConnectionCodeElement.GetEndPoint(vsCMPart.vsCMPartWhole))
        execEditPoint.Insert(onConnectionCode)

        ' Reference all the assemblies that the macro project references.
        CopyReferences(proj, macroProject)

        ' Macro projects have a hidden reference to System.Windows.Forms. If you use any
        '  code that calls MsgBox, you will get odd errors when trying to compile the Add-in generated from 
        '  a macro project if you do not add a reference to that assembly.
        proj.Object.References.Add("System.Windows.Forms.dll")

        ' Clean up the code in Connect.vb (it can look nasty if you do not do this).
        Try
            Dim connectTextSelection As EnvDTE.TextSelection = connectProjectItem.Document.Selection()

            connectTextSelection.SelectAll()
            connectTextSelection.SmartFormat()
            connectTextSelection.Collapse()
        Catch
        End Try

        completionMessage = "Add-in generation complete" + vbLf + vbLf
        completionMessage = completionMessage + "To make sure your Add-in compiles, you need to perform two actions:" + vbLf
        completionMessage = completionMessage + "1) If you had any modules with an 'Option Explicit', a duplicate will appear in the generated module. You need to remove the duplicate." + vbLf
        completionMessage = completionMessage + "2) Any calls to automation methods/properties not prepended with 'DTE.' will need to have these manually added (for example, change 'ActiveDocument()' to 'DTE.ActiveDocument()')."
        MsgBox(completionMessage, MsgBoxStyle.Information, "Make Add-in From Macro Project")
    End Sub

    ' Copies the references from one project to another.
    Sub CopyReferences(ByVal objProjectDest As EnvDTE.Project, ByVal objProjectSrc As EnvDTE.Project)
        Dim objReferenceSrc As VSLangProj.Reference
        Dim objReferencesDest As VSLangProj.References

        objReferencesDest = objProjectDest.Object.References

        For Each objReferenceSrc In objProjectSrc.Object.References
            If (objReferenceSrc.Path <> "") Then
                If (objReferenceSrc.Name <> "EnvDTE") And (objReferenceSrc.Name <> "EnvDTE80") And (objReferenceSrc.Name <> "Microsoft.VisualStudio.CommandBars") Then
                    Try
                        objReferencesDest.Add(objReferenceSrc.Path)
                    Catch
                        MsgBox("Could not add a reference to " & objReferenceSrc.Path & vbLf & "Try adding a reference manually.")
                    End Try
                End If
            End If
        Next
    End Sub

    ' Using the rules of what is or is not a macro, determines
    '   if the CodeFunction is a macro.
    Function IsMacroCallableFunction(ByVal codeFunc As EnvDTE.CodeFunction)
        Dim paramText As String
        Dim param As EnvDTE.CodeParameter

        ' Sub/Function that are Private cannot be called.
        If (codeFunc.Access = vsCMAccess.vsCMAccessPrivate) Then
            Return False
        End If

        ' A macro must contain either 0 parameters or all parameters must be optional strings.
        '  If there are no args, short circuit here.
        If (codeFunc.Parameters.Count = 0) Then
            Return True
        End If

        ' The method has parameters, make sure they are Optional strings.
        For Each param In codeFunc.Parameters
            paramText = param.GetStartPoint(vsCMPart.vsCMPartWhole).CreateEditPoint().GetText(param.GetEndPoint(vsCMPart.vsCMPartWhole))
            If (paramText.StartsWith("Optional ") = False) Then
                Return False
            ElseIf (param.Type.TypeKind <> vsCMTypeRef.vsCMTypeRefString) Then
                Return False
            End If
        Next
        Return True
    End Function

End Module

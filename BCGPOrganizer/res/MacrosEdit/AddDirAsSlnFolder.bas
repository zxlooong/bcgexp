'' Copyright (c) Microsoft Corporation.  All rights reserved.
''
'' These samples demonstrate how to use the VS Automation Object Model.
'' They are unsupported, but you can use them as-is.  They are not intended 
'' to demonstrate how to implement fully rigorous commands.  For example, 
'' if a command expects there to be selected text, but you invoke
'' the macro on a blank line, the macro's behavior is undefined.
''


Imports EnvDTE
Imports EnvDTE80
Imports System.Diagnostics

Public Module AddDirAsSlnFolder

    ' A list of folder names, file names, and extensions that we do not want to add
    '  to the solution.
    Dim excludedExtensions As New System.Collections.Specialized.StringCollection
    Dim outputWindowPaneTitle As String = "Add directory as solution folder report"

    ' Function to filter out folder names, file names, and extensions that we do not 
    '  want to add to the solution.
    Function IsFileExcluded(ByVal filePath As String) As Boolean
        Dim extension As String
        Dim fileName As String

        extension = System.IO.Path.GetExtension(filePath)
        extension = extension.ToLower()

        fileName = System.IO.Path.GetFileName(filePath)
        fileName = fileName.ToLower()

        If (excludedExtensions.Contains(extension)) Then
            Return True
        Else
            If (excludedExtensions.Contains(fileName)) Then
                Return True
            Else
                Return False
            End If
        End If
    End Function

    ' Recursively walk all the files and folders within a specified path, 
    '  and add them to the specified solution folder. 
    Sub GenerateSlnFolderOnDirStructure2(ByVal currentPath As String, ByVal currentSlnFolder As EnvDTE80.SolutionFolder)
        Dim folders As String()
        Dim files As String()
        Dim file As String
        Dim folder As String

        folders = System.IO.Directory.GetDirectories(currentPath)
        files = System.IO.Directory.GetFiles(currentPath)

        ' Examine all the files within the folder.
        For Each file In files
            If (Not IsFileExcluded(file)) Then
                Dim projItem As ProjectItem
                Try
                    projItem = currentSlnFolder.Parent.ProjectItems.AddFromFile(file)

                    If (Not (projItem Is Nothing)) Then
                        If (Not (projItem.Document Is Nothing)) Then
                            projItem.Document.Close(vsSaveChanges.vsSaveChangesNo)
                        End If
                    End If
                Catch
                    Dim outputWindowPane As EnvDTE.OutputWindowPane
                    outputWindowPane = GetOutputWindowPane(outputWindowPaneTitle, True)
                    outputWindowPane.OutputString("The item """ + file + """may have not been added to the solution." + vbLf)
                End Try
            End If
        Next

        ' Examine all the subfolders.
        For Each folder In folders
            Dim folderName As String
            Dim newSlnFolder As SolutionFolder
            Dim proj As Project

            If (Not IsFileExcluded(folder)) Then
                folderName = System.IO.Path.GetFileName(folder)
                proj = currentSlnFolder.AddSolutionFolder(folderName)
                newSlnFolder = proj.Object
                GenerateSlnFolderOnDirStructure2(folder, newSlnFolder)
            End If
        Next
    End Sub

    ' Macro to import a folder on disk into a solution folder structure.
    ' Before running this macro, you must:
    ' 1) Change the path pointed to by startFolder to a path on your computer.
    '    You could also call this macro through the command window, supplying
    '    a start path argument.
    ' 2) Ensure that a solution file is open and saved to disk.
    Sub GenerateSlnFolderOnDirStructure(Optional ByVal startFolder As String = "")
        Dim currentSlnFolder As EnvDTE80.SolutionFolder
        Dim proj As Project
        Dim sln2 As EnvDTE80.Solution2
        Dim folderName As String

        If (String.IsNullOrEmpty(startFolder)) Then
            startFolder = InputBox("Enter the folder path to import")
            If (String.IsNullOrEmpty(startFolder)) Then
                Return
            End If
        End If

        If (System.IO.Directory.Exists(startFolder) = False) Then
            MsgBox("The specified folder could not be found")
            Return
        End If

        GetOutputWindowPane(outputWindowPaneTitle, True).Clear()

        If System.IO.Directory.Exists(startFolder) = False Then
            Dim outputWindowPane As EnvDTE.OutputWindowPane
            outputWindowPane = GetOutputWindowPane(outputWindowPaneTitle, True)
            outputWindowPane.OutputString("The path entered could not be found" + vbLf)
            Exit Sub
        End If

        excludedExtensions = New System.Collections.Specialized.StringCollection
        ' If you do not want a file with a particular extension or name
        '  to be added, then add that extension or name to this list:
        excludedExtensions.Add(".obj")
        excludedExtensions.Add(".ilk")
        excludedExtensions.Add(".pch")
        excludedExtensions.Add(".pdb")
        excludedExtensions.Add(".exe")
        excludedExtensions.Add(".dll")
        excludedExtensions.Add(".sbr")
        excludedExtensions.Add(".lib")
        excludedExtensions.Add(".exp")
        excludedExtensions.Add(".bsc")
        excludedExtensions.Add(".tlb")
        excludedExtensions.Add(".ncb")
        excludedExtensions.Add(".sln")
        excludedExtensions.Add(".suo")
        excludedExtensions.Add(".vcproj")
        excludedExtensions.Add(".vbproj")
        excludedExtensions.Add(".csproj")
        excludedExtensions.Add(".vjsproj")
        excludedExtensions.Add(".msi")

        sln2 = DTE.Solution
        folderName = System.IO.Path.GetFileName(startFolder)
        proj = sln2.AddSolutionFolder(folderName)
        currentSlnFolder = proj.Object
        GenerateSlnFolderOnDirStructure2(startFolder, currentSlnFolder)
    End Sub

End Module

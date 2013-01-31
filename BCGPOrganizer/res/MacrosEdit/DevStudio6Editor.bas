'' Copyright (c) Microsoft Corporation.  All rights reserved.
''
'' This module contains macros from the Developer Studio 6.0 macros samples
'' ported to the VSMacros IDE.  Because these macros are almost exactly as
'' they were in the VC++ v6 product, they may not show the best way to write
'' the same macros today.
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
Imports Microsoft.VisualBasic
Imports Microsoft.VisualBasic.ControlChars

Public Module DevStudio6Editor

    Dim ParamArr() As String
    Dim previousSelection As String
    Dim completionWords As String
    Dim completionWordsIndex As Integer

    Sub PrintAllOpenDocuments()
        ' Description:  Prints all open, active documents.
        Dim doc As EnvDTE.Document
        For Each doc In DTE.Documents()
            doc.PrintOut()
        Next
    End Sub

    Sub MultiplePastes()
        ' Description: Performs a paste of what is on the clipboard multiple times.
        ' Inserts linefeeds as newline sequences between pastes.
        Dim NumPastes As Integer
        Dim times As String
        times = InputBox("Enter the number of times to paste")
        NumPastes = CInt(times)
        Dim i As Integer

        For i = 1 To NumPastes
            DTE.ActiveDocument.Selection.paste()
            ' Because the selection remains active, the following 2 lines
            '  clear the selection, while keeping the cursor in the same place.
            '  There are better ways to do this with the updated TextSelection object.
            DTE.ActiveDocument.Selection.LineUp()
            DTE.ActiveDocument.Selection.LineDown()
            DTE.ActiveDocument.Selection.text() = CStr(Lf)
        Next
    End Sub

    Sub CommentOut()
        ' Description: Comments out a selected block of text.
        Dim win As EnvDTE.Window
        Dim TypeOfFile, StartLine, EndLine, Temp As Integer
        Dim CommentType As String

        win = DTE.ActiveWindow
        If win.Type <> EnvDTE.vsWindowType.vsWindowTypeDocument Then
            MsgBox("This macro can only be run when a text editor window is active.")
        Else
            TypeOfFile = FileType(DTE.ActiveDocument)
            If TypeOfFile > 0 And TypeOfFile < 5 Then ' C & Java use the same
                ' style of commentextSelection.
                DTE.ActiveDocument.Selection.text() = "/*" & DTE.ActiveDocument.Selection.text() & "*/"
            ElseIf TypeOfFile = 5 Then
                DTE.ActiveDocument.Selection.text() = "<!-- " & DTE.ActiveDocument.Selection.text() & " -->"
            ElseIf TypeOfFile = 6 Or TypeOfFile = 7 Then
                ' Becuase there is no group comment as in the other file types,
                '  we must iterate through each line, and prepend a ' to the line.
                '  Also, because VBS/DEF does not have a 'end the comment at this
                '  particular column' delimiter, entire lines of code rather than sections
                '  must be commented out.
                If TypeOfFile = 6 Then
                    CommentType = " ' "
                Else
                    CommentType = " ; "
                End If

                StartLine = DTE.ActiveDocument.Selection.TopLine
                EndLine = DTE.ActiveDocument.Selection.BottomLine
                If EndLine < StartLine Then
                    Temp = StartLine
                    StartLine = EndLine
                    EndLine = Temp
                End If

                If EndLine = StartLine Then
                    DTE.ActiveDocument.Selection.text() = CommentType & DTE.ActiveDocument.Selection.text()

                Else
                    For i = StartLine To EndLine
                        DTE.ActiveDocument.Selection.GotoLine(i)
                        DTE.ActiveDocument.Selection.SelectLine()
                        DTE.ActiveDocument.Selection.text() = CommentType & DTE.ActiveDocument.Selection.text()
                    Next
                End If
            Else
                MsgBox("Unable to comment out the highlighted text" + CStr(Lf) + "because the file type was unrecognized." + CStr(Lf) + "If the file has not yet been saved, " + CStr(Lf) + "please save it and try again.")
            End If
        End If
    End Sub



    Function FileType(ByVal doc As EnvDTE.Document) As Integer
        ' This routine has many uses if you are trying to determine the type of a source
        '   file.
        ' Return value:  0 Unknown file type
        '               1 C-related file, this includes .c, .cpp, .cxx, .h, .hpp, .hxx
        '               2 Java-related file, this includes .jav, .java
        '               3 ODL-style file, .odl, .idl
        '               4 Resource file, .rc, .rc2
        '               5 HTML-style file, this includes .html, and .htm
        '               6 VBS-style file, .dsm
        '               7 Def-style file, .def
        ' USE: Pass this function the document for which you want to get information.

        Dim pos As Integer
        Dim ext As String
        ext = doc.Name
        FileType = 0

        pos = InStr(ext, ".")
        If pos > 0 Then
            Do While pos <> 1
                ext = Mid(ext, pos, Len(ext) - pos + 1)
                pos = InStr(ext, ".")
            Loop
            ext = LCase(ext)
        End If
        If ext = ".rc" Or ext = ".rc2" Then
            FileType = 4

        ElseIf doc.Language = EnvDTE.Constants.dsCPP Then
            FileType = 1
        ElseIf doc.Language = EnvDTE.Constants.dsJava Then
            FileType = 2
        ElseIf doc.Language = EnvDTE.Constants.dsIDL Then
            FileType = 3
        ElseIf doc.Language = EnvDTE.Constants.dsHTML_IE3 Then
            FileType = 5
        ElseIf ext = ".xml" Then
            FileType = 5
        ElseIf doc.Language = EnvDTE.Constants.dsHTML_RFC1866 Then
            FileType = 5
        ElseIf doc.Language = EnvDTE.Constants.dsVBSMacro Then '
            FileType = 6
        ElseIf ext = ".def" Then
            FileType = 7
        Else
            FileType = 0
        End If
    End Function

    Sub ToggleCommentStyle()
        Dim CmtBlock As String
        Dim TmpBlock As String
        Dim selection As EnvDTE.TextSelection
        ' Description: Toggles between comment styles /* and //.

        TmpBlock = ""
        selection = DTE.ActiveDocument.Selection
        CmtBlock = selection.Text()

        TypeOfFile = FileType(DTE.ActiveDocument)

        If TypeOfFile > 0 And TypeOfFile < 5 Then ' C/C++ style comment.
            ' Get the first two characters of the comment block.
            Trim(CmtBlock)
            If InStr(CmtBlock, "//") <> 0 Then
                Do While InStr(CmtBlock, "//") <> 0
                    TmpBlock = TmpBlock + Left(CmtBlock, InStr(CmtBlock, "//") - 1)
                    CmtBlock = Right(CmtBlock, (Len(CmtBlock) - InStr(CmtBlock, "//") - 1))
                Loop
                CmtBlock = "/*" + TmpBlock + CmtBlock + "*/"
            ElseIf InStr(CmtBlock, "/*") <> 0 Then
                CmtBlock = Right(CmtBlock, Len(CmtBlock) - InStr(CmtBlock, "/*") - 1)
                Do While InStr(CmtBlock, CStr(Lf)) <> 0
                    TmpBlock = TmpBlock + Left(CmtBlock, InStr(CmtBlock, CStr(Lf))) + "//"
                    CmtBlock = Right(CmtBlock, (Len(CmtBlock) - InStr(CmtBlock, CStr(Lf))))
                Loop
                CmtBlock = "//" + TmpBlock + Trim(CmtBlock)
                CmtBlock = Left(CmtBlock, InStr(CmtBlock, "*/") - 1)
            End If
            selection = DTE.ActiveDocument.Selection
            selection.Delete()
            selection.Text() = CmtBlock
        Else
            MsgBox("This macro does not work on this type of file.")
        End If
    End Sub


    Function StripTabs(ByVal MyStr As String)
        ' Strips the leading tab spaces.
        While InStr(MyStr, Microsoft.VisualBasic.ControlChars.Tab) > 1
            MyStr = Right(MyStr, Len(MyStr) - InStr(MyStr, CStr(Microsoft.VisualBasic.ControlChars.Tab)))
        End While
        StripTabs = Trim(MyStr)
    End Function

    Sub CloseExceptActive()
        ' Description: Closes all editor windows except the current one.
        Dim current As Integer = 1
        Dim i As Integer
        Dim countOfDocs As Integer = DTE.Documents.Count

        While (True)
            Dim doc As EnvDTE.Document
            doc = DTE.Documents.Item(current)
            If DTE.ActiveDocument.FullName <> doc.FullName Then
                ' Not the current doc.
                doc.Close(vsSaveChangesPrompt)
            Else
                current = current + 1
            End If
            countOfDocs = DTE.Documents.Count

            If (current > countOfDocs) Then
                Exit While
            End If
        End While

    End Sub

    Sub AddRevisionMarks()
        ' DESCRIPTION: Adds comments to a file that describe the changes made.

        ' This routine adds a new comment block to the top of a file, where the
        ' programmer can place revision marks to describe the changes made to the file.
        ' The rules this routine uses are as follows:
        ' 1) Start at the top of the file.
        ' 2) Scan through each line; if the current line starts with a comment,
        '      advance to the next line.
        ' 3) If we are currently in a group comment block, keep advancing until
        '     the end of the block is found.
        ' 4) If we are in a line item comment (for example: //, ', rem, and so on),
        '      keep advancing until a line that does not start with a comment is found.
        '     By 'start with a comment', it is meant a line in which
        '      the first set of characters is not a comment delimiter
        '      after stripping off spaces and tabs from the beginning.
        ' 5) Insert a blank line; this allows the next invocation of this macro
        '     to place the newer revision mark before all others.
        ' 6) Insert the revision block.
        Dim CurrText As String
        Dim selection As EnvDTE.TextSelection
        Dim DefaultUserName As String
        Dim BeginComment As String
        Dim EndComment As String
        Dim EveryLine As String
        Dim CurrentCount As Integer

        ' Change this to the programmer's name for a default.
        DefaultUserName = "..."

        ' Because the user may not have closed a comment (for example a /* without a */),
        '  try to protect ourselves from an infinite loop.
        BreakAfter = 10 ' Max number of lines to scan before aborting.
        CurrentCount = 1

        BeginComment = "" ' The token for the specified language for the beginning
        ' of a comment.
        EndComment = "" 'Same, except for the end of a comment.
        EveryLine = "" 'Does the comment mark need to be placed on every line
        ' (VBS, DEF types)?

        ' First, make sure the active document is a text window
        '  (not necessary, but good practice).
        If DTE.ActiveDocument.Type = "Text" Then

            TypeOfFile = FileType(DTE.ActiveDocument)

            ' Sets ourselves at the very top of the document.
            ' This also clears any selection.
            DTE.ActiveDocument.Selection.StartOfDocument()
            DTE.ActiveDocument.Selection.SelectLine()
            selection = DTE.ActiveDocument.Selection
            CurrText = selection.Text
            CurrText = LTrim(CurrText)

            ' All of the following do relatively the same thing,
            '  except they look for different comment types.
            If TypeOfFile > 0 And TypeOfFile < 5 Then ' C/C++ family of code.
                ContSearch = True
                BeginComment = "/*"
                EndComment = "*/"
                EveryLine = " "

                ' In C/C++ style code, we must look for a //;
                '  if not found, then look for a /*.
                Do
                    selection.Text = CurrText
                    If InStr(CurrText, "//") = 1 Then ' Is a "//" available?
                        selection.SelectLine()
                        CurrText = LTrim(selection.Text) ' Remove whitespace.
                        ContSearch = False ' Looking at // style comments,
                        ' don't look for a /* style.
                    Else
                        Exit Do
                    End If
                Loop

                If ContSearch = False Then
                    DTE.ActiveDocument.Selection.LineUp()
                End If

                ' When the DTE.ActiveDocument.Selection.SelectLine method is called,
                '   it is the same as when you click the mouse in the margin. It
                '   selects the whole line, including the carriage return.
                '   Consequently, the cursor moves down to the next line, which
                '   can really confuse this algorithm. So in a number of places,
                '   you will see a grouping of LineUp/LineDown commands. By executing
                '   these commands, the cursor is moved down, which clears the current
                '   selection (including moving past the carriage return),
                '   then moves us back up, thus putting us on the same line. This
                '   removes the danger of skipping a line (which is what will
                '   happen without the LineUp/LineDown combination).
                If ContSearch = True Then
                    DTE.ActiveDocument.Selection.StartOfDocument()
                    ' Prime the loop with the first line.
                    DTE.ActiveDocument.Selection.SelectLine()
                    CurrText = DTE.ActiveDocument.Selection.Text
                    DTE.ActiveDocument.Selection.LineDown()
                    DTE.ActiveDocument.Selection.LineUp()
                    ' Remove leading whitespace.
                    CurrText = LTrim(CurrText)
                    ' Does line start with a /*?
                    If InStr(CurrText, "/*") = 1 Then
                        While (InStr(CurrText, "*/") = 0) And (BreakAfter > CurrentCount)
                            DTE.ActiveDocument.Selection.SelectLine()
                            CurrText = selection.Text
                            CurrText = LTrim(CurrText)
                            DTE.ActiveDocument.Selection.LineDown()
                            DTE.ActiveDocument.Selection.LineUp()
                            CurrentCount = CurrentCount + 1
                        End While
                        If (BreakAfter > CurrentCount) Then
                            ' Exit the loop because the search has continued for an
                            '   unreasonable number of lines.
                            MsgBox("Could not find a closing comment mark")
                        End If
                    End If
                End If

                ' The code for these is really just a copy of code from the
                '   C/C++ section.

            ElseIf TypeOfFile = 5 Then ' HTML code.
                BeginComment = "<!--"
                EndComment = "-->"
                EveryLine = "    "
                If InStr(CurrText, "<!--") = 1 Then
                    If InStr(CurrText, "-->") <> 0 Then
                        DTE.ActiveDocument.Selection.LineDown()
                    Else
                        Do
                            DTE.ActiveDocument.Selection.SelectLine()
                            CurrText = DTE.ActiveDocument.Selection.Text
                            CurrText = Left(CurrText, Len(CurrText) - 2)
                            selection = DTE.ActiveDocument.Selection
                            selection.Text = CurrText + Lf
                            If InStr(CurrText, "-->") Then
                                Exit Do
                            End If
                        Loop
                    End If
                End If

            ElseIf TypeOfFile = 6 Then ' VBS code.
                BeginComment = "'"
                EndComment = "'"
                EveryLine = "'"
                Do
                    selection = DTE.ActiveDocument.Selection
                    selection.Text = CurrText
                    If InStr(CurrText, "'") = 1 Or InStr(LCase(CurrText), "Rem") = 1 Then
                        DTE.ActiveDocument.Selection.SelectLine()
                        CurrText = LTrim(DTE.ActiveDocument.Selection)
                        ContSearch = False
                    Else
                        Exit Do
                    End If
                Loop
                If ContSearch = False Then
                    DTE.ActiveDocument.Selection.LineUp()
                End If

            ElseIf TypeOfFile = 7 Then 'DEF code
                BeginComment = ";"
                EndComment = ""
                EveryLine = ";"
                Do
                    selection = DTE.ActiveDocument.Selection
                    selection.Text = CurrText
                    If InStr(CurrText, ";") = 1 Then
                        DTE.ActiveDocument.Selection.SelectLine()
                        CurrText = LTrim(DTE.ActiveDocument.Selection)
                        ContSearch = False
                    Else
                        Exit Do
                    End If
                Loop
                If ContSearch = False Then
                    DTE.ActiveDocument.Selection.LineUp()
                End If
            End If

            If TypeOfFile = 0 Then ' Unknown type of code.

                MsgBox("Unable to add revision marks. Unrecognized file type")

            ElseIf (CurrentCount < BreakAfter) Then

                'The BeginComment, EveryLine, and EndComment were set as
                ' avoid duplicating this section...
                ' just insert the generalized block, with the comment markers.
                DTE.ActiveDocument.Selection.StartOfLine()
                ' This is added with one assignment statement, which enables the user
                '  to press undo once and remove the entire change.
                selection = DTE.ActiveDocument.Selection
                selection.Text = CStr(Lf) + BeginComment + "***********************************" + CStr(Lf)
                selection.Text = selection.Text + EveryLine + " REVISION LOG ENTRY" + CStr(Lf)
                selection.Text = selection.Text + EveryLine + " Revision By: " + DefaultUserName + CStr(Lf)
                selection.Text = selection.Text + EveryLine + " Revised on " + CStr(Now()) + CStr(Lf) + EveryLine + " Comments: ..." + CStr(Lf) + EveryLine + "***********************************" + EndComment + CStr(Lf)
            End If
        End If

    End Sub

    Sub AddFunctionDescription()
        ' Description: Creates a comment block for the currently selected C/C++ function prototype.
        Dim Header, prms As String
        Dim fcName, Descr As String
        Dim iPrm, iPrmA As Integer
        Dim selection As EnvDTE.TextSelection
        Dim RetTp As String

        ' Throughout this file, DTE.ActiveDocument.Selection is used in place
        ' of DTE.ActiveDocument.Selection.Text. The two are equivalent, and can
        ' be used interchangeably. The reason for the equivalence is that
        ' Text is regarded as the default property to use. All uses of
        ' ActiveDocument.Selection without any other property default to the Text
        ' property.
        If (DTE.ActiveDocument Is Nothing) Then
            Exit Sub
        End If
        If DTE.ActiveDocument.Language = EnvDTE.Constants.dsCPP Or DTE.ActiveDocument.Language = "CSharp" Then

            selection = DTE.ActiveDocument.Selection()
            Trim(selection.Text)
            Header = ""

            If selection.Text <> "" Then
                Header = StripTabs(Trim(selection.Text))
            End If

            ' Get the function return type.
            If Header <> "" Then
                If DTE.ActiveDocument.Language = "CSharp" Then
                    ' Skip the protection info (public/private ...).
                    Header = Right(Header, Len(Header) - InStr(Header, " "))
                End If
                Reti = InStr(Header, " ")
                Loc1 = InStr(Header, "(")
                If Reti < Loc1 Then
                    RetTp = Left(Header, Loc1 - 1)
                    Header = Right(Header, Len(Header) - Reti)
                End If
                RetTp = Left(RetTp, InStr(RetTp, " "))

                ' Get the function name.
                Loc1 = InStr(Header, "(") - 1
                Loc2 = InStr(Header, ")")

                If Loc1 > 0 And Loc2 > 0 Then ' Make sure there is a '(' and a ')'.
                    fcName = Left(Header, Loc1)
                    Header = Right(Header, Len(Header) - Len(fcName))

                    ' Do we have storage type on the return type?
                    Trim(fcName)
                    If InStr(fcName, " ") <> 0 Then
                        RetTp = RetTp + Left(fcName, InStr(fcName, " "))
                        fcName = Right(fcName, Len(fcName) - InStr(fcName, " "))
                    End If

                    ' Get the function parameters.
                    iPrm = 0
                    iPrmA = 0
                    prms = Header

                    ' Count the number of parameters.
                    Do While InStr(prms, ",") <> 0
                        iPrm = iPrm + 1
                        prms = Right(prms, Len(prms) - InStr(prms, ","))
                    Loop

                    ' Store the parameter list in the array.
                    If iPrm > 0 Then ' If multiple params.
                        iPrm = iPrm + 1
                        iPrmA = iPrm
                        ReDim ParamArr(iPrm)
                        Do While InStr(Header, ",") <> 0
                            ParamArr(iPrm - 1) = Left(Header, InStr(Header, ",") - 1)
                            ' Remove brace from first parameter.
                            If InStr(ParamArr(iPrm - 1), " (") <> 0 Then
                                ParamArr(iPrm - 1) = Right(ParamArr(iPrm - 1), (Len(ParamArr(iPrm - 1)) - (Len(ParamArr(iPrm - 1)) - (Len(ParamArr(iPrm - 1)) - InStr(ParamArr(iPrm - 1), " (")))))
                                Trim(ParamArr(iPrm))
                            End If
                            Header = Right(Header, Len(Header) - InStr(Header, ","))
                            iPrm = iPrm - 1
                        Loop
                        ParamArr(iPrm - 1) = Header

                        ' Remove trailing brace from last parameter.
                        If InStr(ParamArr(iPrm - 1), ")") <> 0 Then
                            ParamArr(iPrm - 1) = Left(ParamArr(iPrm - 1), InStr(ParamArr(iPrm - 1), ")") - 1)
                            Trim(ParamArr(iPrm - 1))
                        End If
                    Else ' Possibly one param.

                        ReDim ParamArr(1)
                        Header = Right(Header, Len(Header) - 1) ' Strip the first brace.
                        Trim(Header)
                        ParamArr(0) = StripTabs(Header)
                        If InStr(ParamArr(0), ")") <> 1 Then
                            ParamArr(0) = Left(ParamArr(0), InStr(ParamArr(0), ")") - 1)
                            Trim(ParamArr(0))
                            iPrmA = 1
                        End If
                    End If

                    ' Position the cursor one line above the selected text.
                    DTE.ActiveDocument.Selection.LineUp()
                    DTE.ActiveDocument.Selection.LineDown()
                    DTE.ActiveDocument.Selection.StartOfLine()
                    selection = DTE.ActiveDocument.Selection()
                    'selection.text = Lf

                    Descr = CStr(Lf) + "// Function name   : " + fcName + CStr(Lf)
                    Descr = Descr + "// Description     : " + CStr(Lf) + "// Return type     : "
                    Descr = Descr + RetTp + CStr(Lf)

                    ' Print the parameter list.
                    Last = iPrmA
                    Do While iPrmA <> 0
                        ' Remove a line feed from any of the argumentextSelection.
                        If InStr(ParamArr(iPrmA - 1), CStr(Lf)) <> 0 Then
                            ParamArr(iPrmA - 1) = Right(ParamArr(iPrmA - 1), (Len(ParamArr(iPrmA - 1)) - (Len(ParamArr(iPrmA - 1)) - (Len(ParamArr(iPrmA - 1)) - InStr(ParamArr(iPrmA - 1), CStr(Lf))))))
                            Trim(ParamArr(iPrmA - 1))
                        End If
                        ParamArr(iPrmA - 1) = StripTabs(ParamArr(iPrmA - 1))
                        ' If there are 2+ parameters, the first parameter will
                        ' have a '(' prepended to it. Remove it here:
                        If iPrmA = Last And Last <> 1 Then
                            ParamArr(iPrmA - 1) = Right(ParamArr(iPrmA - 1), Len(ParamArr(iPrmA - 1)) - 1)
                        End If
                        Descr = Descr + "// Argument        : " + ParamArr(iPrmA - 1) + CStr(Lf)
                        iPrmA = iPrmA - 1
                    Loop
                    Descr = Descr + CStr(Lf)
                    selection = DTE.ActiveDocument.Selection()
                    selection.Text = Descr
                Else
                    MsgBox("It is possible that the function you are trying to work with has a syntax error.")
                End If
            End If

        Else

            MsgBox("You need to have an active C/C++ document open" + CStr(Lf) + "with the function prototype selected.")
        End If

    End Sub
    ' This routine has many uses if you are trying to determine if an identifier
    '   is a valid C identifier.
    '   These identifiers do not include qualification syntax, for example:
    '   foo.bar is not valid
    '   foo is valid
    ' Parameters:    String to test for a valid C identifier.
    ' Return value:  True: passed parameter is a valid C identifier.
    '               False: passed parameter is not a valid C identifier.
    Function ValidId(ByVal Id As String)

        ValidId = True

        ' Don't permit an empty string
        '  (how can you identify nothing with something?).
        If Id = "" Then
            ValidId = False
            Exit Function
        End If

        For i = 1 To Len(Id)
            If Mid(Id, i, 1) < "a" Or Mid(Id, i, 1) > "z" Then
                If Mid(Id, i, 1) < "A" Or Mid(Id, i, 1) > "Z" Then
                    If Mid(Id, i, 1) < "0" Or Mid(Id, i, 1) > "9" Then
                        If Mid(Id, i, 1) <> "_" Then
                            ValidId = False
                        End If
                    End If
                End If
            End If
        Next

        If Mid(Id, 1, 1) >= "0" And Mid(Id, 1, 1) <= "9" Then
            ValidId = False
        End If

    End Function

    Sub PoundDefOut(ByVal ifndef)
        Dim PoundType As String
        Dim ControlVarName As String
        Dim sel As EnvDTE.TextSelection
        Dim selection As EnvDTE.TextSelection
        Dim Ok As Boolean

        If ifndef = True Then
            PoundType = "#ifndef "
        Else
            PoundType = "#ifdef "
        End If

        If FileType(DTE.ActiveDocument) <> 1 Then
            MsgBox("This macro only works on" + Lf + ".c, .cpp, .cxx, .h, .hpp, or .hxx files")
        Else
            ControlVarName = InputBox("What should the control variable be?" + Lf + Lf + "Example: #ifdef ControlVariable", PoundType + " out a section of code")
            Ok = True
            If ValidId(ControlVarName) = False Then
                Ok = False
                MsgBox("""" + ControlVarName + """ is not a valid C identifier." + Lf + "please re-run the macro with a valid C identifier")
            End If

            sel = DTE.ActiveDocument.Selection
            For i = 1 To (Len(sel.Text) - 1)
                If Mid(sel.Text, i, 1) = Lf Then
                    sel.Text = Left(sel.Text, i) + Microsoft.VisualBasic.ControlChars.Tab + Right(sel.Text, Len(sel.Text) - i)
                End If
            Next
            If ControlVarName <> "" And Ok = True Then
                sel.Text = CStr(Microsoft.VisualBasic.ControlChars.Lf) + PoundType + ControlVarName + CStr(Microsoft.VisualBasic.ControlChars.Lf) + CStr(Microsoft.VisualBasic.ControlChars.Tab) + sel.Text + CStr(Lf) + "#endif //" + ControlVarName
                If Right(sel.Text, 1) <> CStr(Microsoft.VisualBasic.ControlChars.Lf) Then
                    sel.Text = sel.Text + CStr(Microsoft.VisualBasic.ControlChars.Lf)
                End If
            End If
        End If
    End Sub

    ' The next two macros are exactly the same, except one uses ifndef and the
    '   other ifdef. We recycle the same code and just use a different
    '   preprocessor directive.
    Sub ifdefOut()
        ' DESCRIPTION: #ifdef / #endif out a section of code.

        PoundDefOut(False)
    End Sub

    Sub ifndefOut()
        ' DESCRIPTION: #ifndef / #endif out a section of code.

        PoundDefOut(True)
    End Sub


    ' Allows the user to make sure the current header file is included only once.
    '  There are two ways to do this, using the #pragma once directive or
    '  surrounding the entire file in a #ifndef/#endif structure. The first way
    '  is much cleaner, but it is VC++ specific, and therefore not portable. If
    '  you plan on compiling your code with other compilers, use the
    '  #ifndef/#endif method. Otherwise, the #pragma once option is preferrable.
    Sub OneTimeInclude()
        ' DESCRIPTION: Adds code to the current header file so it is included only once per c/cpp file.
        Dim ext As String
        Dim DocName As String
        Dim examp As String
        Dim selection As EnvDTE.TextSelection
        Dim pos As Integer
        Dim ControlVarName As String

        ext = DTE.ActiveDocument.Name
        If ext = "" Then
            If MsgBox("The file you are working with does not have a file extension." + Lf + "Are you sure this is a C/C++ header file?", 4) = MsgBoxResult.Cancel Then
                Exit Sub
            End If
            ext = "nofilenamegiven.h"
        End If
        DocName = UCase(ext)
        pos = InStr(ext, ".")
        Do While pos <> 1
            ext = Mid(ext, pos, (Len(ext) - pos + 1))
            pos = InStr(ext, ".")
        Loop
        ext = LCase(ext)
        pos = InStr(DocName, ".")
        If ext = ".h" Or ext = ".hpp" Then
            ' Warn user that this will not work with a compiler other than VC++.
            ' If MsgBox("This macro uses the Visual C++ dependent #pragma once" + Lf + "Is the source to be portable across compilers?", 4)  = 6 Then
            DTE.ActiveDocument.Selection.StartOfDocument(False)
            examp = "__" + Left(DocName, pos - 1) + "_" + UCase(Right(ext, Len(ext) - 1)) + "__"
            ControlVarName = InputBox("What should the control variable be?" + Lf + Lf + "Example: #ifdef " + examp, "One time header include protection", examp)
            selection = DTE.ActiveDocument.Selection
            If ValidId(ControlVarName) = True Then
                selection.Text = "#ifndef " + ControlVarName + CStr(Lf) + "#define " + ControlVarName + CStr(Lf)
                DTE.ActiveDocument.Selection.EndOfDocument(False)
                selection.Text = CStr(Lf) + "#endif //" + ControlVarName
            Else
                MsgBox(ControlVarName + " is not a valid c identifier." + Lf + "please re-run the macro with a valid C identifier")
            End If
            'Else
            '    DTE.ActiveDocument.Selection.StartOfDocument (False)
            '    DTE.ActiveDocument.Selection = "#pragma once" + Lf + Lf
            'End If
        Else
            MsgBox("This macro can only be run on .h or .hpp files")
        End If
    End Sub

    ' Auto-completion macro.

    Sub AddToCompletionWords(ByVal word As String)
        ' If the word is already there, abort.
        If InStr(1, completionWords, " " & word & " ", 1) <> 0 Then
            Exit Sub
        End If

        If word <> " " Then
            completionWords = completionWords & word & " "
        End If

    End Sub

    Private Function ExtractNextCompletionWord()
        ExtractNextCompletionWord = ""

        ' If no words yet, go away.
        If Len(completionWords) <= 1 Then
            Exit Function
        End If

        ' Wrap to beginning if necessary.
        If completionWordsIndex > Len(completionWords) Then
            completionWordsIndex = 2
        End If

        ' Find next <space>.
        Dim newIndex As Integer
        newIndex = InStr(completionWordsIndex, completionWords, " ", 0)
        If newIndex = 0 Then
            Exit Function
        End If

        ExtractNextCompletionWord = Mid(completionWords, completionWordsIndex, newIndex - completionWordsIndex)
        completionWordsIndex = newIndex + 1 ' Skip over <space>.

    End Function

    Sub FillCompletionWords(ByVal word As String)
        '  Find all words in this file which match word, and
        '   add them, space separated, to completionWords.
        previousSelection = word
        completionWords = " "
        completionWordsIndex = 2
        Dim sel As EnvDTE.TextSelection

        sel = DTE.ActiveDocument.Selection

        Dim searchString As String
        searchString = "[^a-zA-Z0-9]" & word
        Dim firstTime As Boolean
        firstTime = True
        Dim firstLine, firstCol As Integer
        sel.StartOfDocument()

        Do While sel.FindText(searchString, vsFindOptions.vsFindOptionsRegularExpression)
            If firstTime Then
                firstLine = sel.TopLine
                firstCol = sel.CurrentColumn
                firstTime = False
            ElseIf firstLine = sel.TopLine And firstCol = sel.CurrentColumn Then
                Exit Do ' Jump out of loop before repeat.
            End If
            sel.WordRight()
            sel.WordLeft(DsMovementOptions.dsExtend)
            AddToCompletionWords(Trim(sel.Text))
            sel.Cancel()
        Loop
    End Sub

    Function SuggestNextCompletionWord()
        SuggestNextCompletionWord = True
        Dim selection As EnvDTE.TextSelection
        Dim word As String

        selection = DTE.ActiveDocument.Selection
        word = ExtractNextCompletionWord()
        If word <> "" Then
            selection.Text = word
            previousSelection = word
        End If

        selection.WordLeft(DsMovementOptions.dsExtend)
    End Function

    Sub AutoCompleteFromFile()
        ' DESCRIPTION: Looks through the active file, searching for the rest of the word that you began to type.
        Dim doc As EnvDTE.Document
        Dim sel As EnvDTE.TextSelection
        Dim origLine, origCol As Integer
        doc = DTE.ActiveDocument
        ' Be sure active document is a text document.
        If doc Is Nothing Then
            Exit Sub
        ElseIf doc.Type <> "Text" Then
            Exit Sub
        End If

        ' Get word to be completed.
        sel = doc.Selection
        sel.Cancel()
        origLine = sel.CurrentLine
        origCol = sel.CurrentColumn
        sel.WordLeft(DsMovementOptions.dsExtend)

        ' If the cursor is sitting just to the right of a space, an infinite loop
        ' resultextSelection. This bit of code protects from that:
        If Right(sel.Text, 1) = " " Then
            sel.CharRight()
            Exit Sub
        End If

        FillCompletionWords(sel.Text)
        sel.MoveToLineAndOffset(origLine, origCol)
        sel.WordLeft(DsMovementOptions.dsExtend)
        SuggestNextCompletionWord()

    End Sub


End Module

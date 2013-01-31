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

Public Module VSEditor

    ' A constant string that is used by some macros to determine when
    '  a searched has wrapped within a text buffer. This should be localized
    '  for each language Visual Studio uses.
    Const passedString = "Passed"

    '' CommentRegion puts line-oriented comment syntax at the beginning
    '' of every line the selection touches and creates an undo so that
    '' there is only one undo action for all the lines edited.
    ''
    Sub CommentRegion()
        Dim selection As EnvDTE.TextSelection
        Dim startPoint As EnvDTE.EditPoint
        Dim endPoint As TextPoint
        Dim commentStart As String

        selection = DTE.ActiveDocument.Selection()
        startPoint = selection.TopPoint.CreateEditPoint()
        endPoint = selection.BottomPoint
        commentStart = Utilities.LineOrientedCommentStart()

        DTE.UndoContext.Open("Comment Region")
        Try
            Do While (True)
                Dim line As Integer

                line = startPoint.Line
                startPoint.Insert(commentStart)
                startPoint.LineDown()
                startPoint.StartOfLine()
                If (line = endPoint.Line) Then
                    Exit Do
                End If
            Loop
        Finally
            ' If an error occurred, then make sure that the undo context is cleaned up.
            ' Otherwise, the editor can be left in a perpetual undo context.
            DTE.UndoContext.Close()
        End Try
    End Sub

    '' NewCommentLine inserts a line break and sets up the next line to continue
    '' the current line-oriented comment line.
    ''
    Sub NewCommentLine()
        Dim textSelection As EnvDTE.TextSelection

        textSelection = DTE.ActiveWindow.Selection
        textSelection.NewLine()
        textSelection.Insert(Utilities.LineOrientedCommentStart())
        textSelection.Insert(" ")
    End Sub


    '' SaveBackup saves a copy of the current document to a name formed
    '' from the doc's name appended with ".bak"
    ''
    Sub SaveBackup()
        Dim fileName As String
        Dim startPoint As EnvDTE.EditPoint
        Dim endPoint As EnvDTE.EditPoint
        Dim textDocument As TextDocument
        Dim text As String

        fileName = DTE.ActiveDocument.FullName + ".bak"

        ' Find the text within the document.
        If (DTE.ActiveDocument Is Nothing) Then
            ' No document to backup.
            Return
        End If
        textDocument = DTE.ActiveDocument.Object
        startPoint = textDocument.StartPoint.CreateEditPoint
        endPoint = textDocument.EndPoint.CreateEditPoint
        text = startPoint.GetText(endPoint)

        ' Create the temp document, save, then close.
        DTE.ItemOperations.NewFile("General\Text File")
        DTE.ActiveDocument.Object("TextDocument").Selection.Insert(text)
        DTE.ActiveDocument.Save(fileName)
        DTE.ActiveDocument.Close(EnvDTE.vsSaveChanges.vsSaveChangesNo) 'Already saved with line above, don't need to save again.

    End Sub

    '' OneFunctionView uses the VS Code Model and the editor's automation
    '' model to create outline sections before and after the function
    '' so that you only see the function that currently contains the caret.
    ''
    Sub OneFunctionView()
        Dim textSelection As EnvDTE.TextSelection
        Dim textSelectionPointSaved As EnvDTE.EditPoint
        Dim editPoint As EnvDTE.EditPoint

        textSelection = DTE.ActiveWindow.Selection
        textSelectionPointSaved = textSelection.ActivePoint.CreateEditPoint
        editPoint = textSelection.ActivePoint.CreateEditPoint

        '' Get the start and outline to start of doc.
        editPoint.MoveToPoint(editPoint.CodeElement(EnvDTE.vsCMElement.vsCMElementFunction).GetStartPoint(vsCMPart.vsCMPartWholeWithAttributes))
        editPoint.LineUp()
        textSelection.MoveToPoint(editPoint, False)
        textSelection.StartOfDocument(True)
        textSelection.OutlineSection()
        'editPoint.LineDown()
        '' Move editPoint back in function and outline from end to end of doc.
        editPoint.MoveToPoint(textSelectionPointSaved)
        editPoint.MoveToPoint(editPoint.CodeElement(EnvDTE.vsCMElement.vsCMElementFunction).GetEndPoint(vsCMPart.vsCMPartWholeWithAttributes))
        editPoint.LineDown()
        textSelection.MoveToPoint(editPoint, False)
        textSelection.EndOfDocument(True)
        textSelection.OutlineSection()
        textSelection.MoveToPoint(textSelectionPointSaved)
    End Sub

    '' BeginningOfFunction moves the caret to the beginning of the containing
    '' definition.
    ''
    Sub BeginningOfFunction()
        Dim textSelection As EnvDTE.TextSelection
        Dim codeElement As EnvDTE.CodeElement

        textSelection = DTE.ActiveWindow.Selection
        Try
            codeElement = textSelection.ActivePoint.CodeElement(vsCMElement.vsCMElementFunction)
            If Not (codeElement Is Nothing) Then
                textSelection.MoveToPoint(codeElement.GetStartPoint(vsCMPart.vsCMPartHeader))
            End If
        Catch
        End Try
    End Sub

    '' LineToTop moves the current line to the top of the window.
    ''
    Sub LineToTop()
        Dim textSelection As EnvDTE.TextSelection

        textSelection = DTE.ActiveWindow.Selection
        textSelection.ActivePoint.TryToShow(vsPaneShowHow.vsPaneShowTop)
    End Sub

    '' EmacsStyleIndentLine can't be bound to the tab key, but you can invoke it
    '' from a key to re-indent the current line relative to surrounding code
    '' without moving the caret.
    ''
    Sub EmacsStyleIndentLine()
        Dim textSelection As EnvDTE.TextSelection
        Dim savedTextSelectionPoint As EnvDTE.EditPoint

        textSelection = DTE.ActiveWindow.Selection
        savedTextSelectionPoint = textSelection.ActivePoint.CreateEditPoint()
        textSelection.SelectLine()
        textSelection.SmartFormat()
        textSelection.MoveToPoint(savedTextSelectionPoint)
    End Sub


    ''
    '' TopOfBlock and helper functions
    ''

    '' TopOfBlock uses indentation levels to guess where the enclosing basic
    '' block starts for a given line of code. This command helps you walk up
    '' through your code jumping to the start of blocks.
    ''
    Sub TopOfBlock()
        Dim textDoc As EnvDTE.TextDocument
        Dim editPoint As EnvDTE.EditPoint
        Dim selection As EnvDTE.TextSelection
        Dim indent As Long
        Dim currentIndent As Long

        textDoc = DTE.ActiveDocument.Object("TextDocument")
        editPoint = textDoc.CreateEditPoint(Nothing)
        selection = textDoc.Selection

        editPoint.LineDown(selection.ActivePoint.Line - 1)

        indent = IndentLevel(editPoint)
        If indent = -1 Then
            Beep()
            Exit Sub
        End If
        currentIndent = indent

        Do While currentIndent >= indent
            currentIndent = IndentLevel(editPoint)
            If currentIndent = -1 Then
                Beep()
                Exit Sub
            Else
                If currentIndent >= indent Then
                    If editPoint.Line = 1 Then
                        Exit Sub
                    Else
                        editPoint.LineUp()
                    End If
                End If
            End If
        Loop

        selection.MoveToLineAndOffset(editPoint.Line, editPoint.LineCharOffset)
    End Sub


    '' Helper for TopOfBlock.
    ''
    Function IndentLevel(ByVal editPoint As EnvDTE.EditPoint)
        Dim lastLine As Long

        Do While True
            lastLine = editPoint.Line
            editPoint.StartOfLine()
            SkipSpaceRight(editPoint)

            If editPoint.Line <> lastLine Then
                ' empty line
                editPoint.LineUp(2)
            ElseIf editPoint.LineCharOffset = editPoint.LineLength + 1 Then
                ' line with only spaces and/or tabs
                editPoint.LineUp()
            Else
                IndentLevel = editPoint.DisplayColumn
                Exit Do
            End If

            If editPoint.Line <> lastLine - 1 Then
                IndentLevel = -1
                Exit Function
            End If
        Loop
    End Function


    '' Helper for IndentLevel. Skips spaces and tabs to the right.
    ''
    Sub SkipSpaceRight(ByVal editPoint As EnvDTE.EditPoint)
        Dim line As Long
        Dim lastPos As Long

        line = editPoint.Line
        '' Don't call IsWhitespace here due to consing overhead.
        Do While editPoint.Line = line And (editPoint.GetText(1) = " " Or editPoint.GetText(1) = CStr(Microsoft.VisualBasic.ControlChars.Tab))
            lastPos = editPoint.LineCharOffset
            editPoint.CharRight()
            If editPoint.LineCharOffset = lastPos Then
                '' end of document
                Exit Sub
            End If
        Loop
    End Sub


    ''
    '' Code outlining sample.
    ''

    '' Collapse the code to view each individual code element.
    ''
    Sub OutlineCode()
        Dim i As Integer
        Dim fileCM As FileCodeModel
        Dim elts As EnvDTE.CodeElements
        Dim elt As EnvDTE.CodeElement

        fileCM = DTE.ActiveDocument.ProjectItem.FileCodeModel
        elts = fileCM.CodeElements
        For i = 1 To elts.Count
            elt = elts.Item(i)
            CollapseElt(elt, elts, i)
        Next
    End Sub

    '' Helper to OutlineCode. Recursively outlines members of elt.
    ''
    Sub CollapseElt(ByVal elt As EnvDTE.CodeElement, ByVal elts As EnvDTE.CodeElements, ByVal loc As Integer)
        Dim epStart As EnvDTE.EditPoint
        Dim epEnd As EnvDTE.EditPoint

        epStart = elt.GetStartPoint(vsCMPart.vsCMPartWholeWithAttributes).CreateEditPoint()
        epEnd = elt.GetEndPoint(vsCMPart.vsCMPartWholeWithAttributes).CreateEditPoint() ' Copy it because we move it later.
        epStart.EndOfLine()
        If ((elt.IsCodeType()) And (elt.Kind <> EnvDTE.vsCMElement.vsCMElementDelegate)) Then
            Dim i As Integer
            Dim mems As EnvDTE.CodeElements

            mems = elt.Members
            For i = 1 To mems.Count
                CollapseElt(mems.Item(i), mems, i)
            Next
        ElseIf (elt.Kind = EnvDTE.vsCMElement.vsCMElementNamespace) Then
            Dim i As Integer
            Dim mems As EnvDTE.CodeElements

            mems = elt.Members
            For i = 1 To mems.Count
                CollapseElt(mems.Item(i), mems, i)
            Next
        End If

        If (epStart.LessThan(epEnd)) Then
            loc = loc + 1
            If (loc <= elts.Count) Then
                epEnd.MoveToPoint(elts.Item(loc).GetStartPoint(vsCMPart.vsCMPartHeader))
                epEnd.LineUp()
                epEnd.EndOfLine()
            End If
            epStart.OutlineSection(epEnd)
        End If
    End Sub

    ' Places the caret at the center of the screen. If the caret cannot be placed
    '    in the center of the screen (because, for example, the caret is at the bottom
    '    or top of the file, or there are only a couple of lines of text), then it will
    '    scroll the view so the caret can be seen.
    Sub CenterScreen()
        Dim textPoint As EnvDTE.TextPoint

        textPoint = DTE.ActiveDocument.Selection.ActivePoint
        textPoint.TryToShow(vsPaneShowHow.vsPaneShowCentered)
    End Sub

    ' Prints the current document with line numbers prepended to each line.
    Sub PrintNumberedLines()
        Dim textSelection As EnvDTE.TextSelection
        Dim textSelectionNewFile As EnvDTE.TextSelection
        Dim i As Integer
        Dim lineCount As Integer
        Dim newText As String

        textSelection = DTE.ActiveDocument.Selection
        textSelection.SelectAll()
        textSelection.Copy()
        textSelectionNewFile = DTE.ItemOperations.NewFile("General\Text File").Selection
        textSelectionNewFile.Paste()
        textSelectionNewFile.StartOfDocument()

        textSelectionNewFile.SelectAll()
        lineCount = textSelectionNewFile.BottomLine
        textSelectionNewFile.StartOfDocument()

        For i = 1 To (lineCount)
            textSelectionNewFile = DTE.ActiveDocument.Selection
            textSelectionNewFile.StartOfLine(EnvDTE.vsStartOfLineOptions.vsStartOfLineOptionsFirstColumn)
            newText = CStr(i) & ". "
            textSelectionNewFile.Text = newText
            textSelectionNewFile.LineDown(True)
        Next
        DTE.ActiveDocument.PrintOut()

        DTE.ActiveDocument.Close(EnvDTE.vsSaveChanges.vsSaveChangesNo)
    End Sub


    ' This macro prompts for a command to run, selects the entire file, 
    ' runs the command, and restores the selection. So you can use it 
    ' to quickly format the entire file without losing the current selection.   
    Sub DoForWholeFile()
        Dim command As String

        command = InputBox("Enter a command: ")
        If (command <> "") Then
            Dim selection As EnvDTE.TextSelection
            Dim anchorPoint As EnvDTE.EditPoint
            Dim activePoint As EnvDTE.EditPoint
            Dim textPane As TextPane
            Dim cornerPoint As EnvDTE.EditPoint

            selection = DTE.ActiveDocument.Selection
            anchorPoint = selection.AnchorPoint.CreateEditPoint
            activePoint = selection.ActivePoint.CreateEditPoint
            textPane = DTE.ActiveDocument.ActiveWindow.Object.activepane
            cornerPoint = textPane.StartPoint.CreateEditPoint


            selection.StartOfDocument()
            selection.EndOfDocument(True)
            DTE.ExecuteCommand(command)
            selection.MoveToPoint(anchorPoint)
            selection.MoveToPoint(activePoint, True)
            textPane.TryToShow(cornerPoint, vsPaneShowHow.vsPaneShowTop)
        End If
    End Sub

    '' LineEmUp aligns all text in the selected lines based on word breaks.
    '' Useful for creating vertically aligned variable or method declarations.
    ''
    Sub LineEmUp()
        Dim selection As EnvDTE.TextSelection
        Dim editPoint As EnvDTE.EditPoint
        Dim rows As Long
        Dim howFarOut As Long = 1
        Dim anyMoved As Boolean = False

        selection = ActiveDocument.Selection
        editPoint = selection.TopPoint.CreateEditPoint
        rows = selection.BottomPoint.Line - selection.TopPoint.Line

        ' Iterate to find the first row that isn't already aligned.
        Do While Not anyMoved
            Dim AnyRowValid = False

            ' The current character and display columns of each element in the
            ' current word column.
            Dim curCharPos(rows) As Long
            Dim curDispPos(rows) As Long
            ' The lowest possible columns at which each element could begin if
            ' whitespace was compressed.
            Dim minCharPos(rows) As Long
            Dim minDispPos(rows) As Long

            ' Iterate over each selected row.
            Dim arrIdx As Long = 0
            Dim maxMinPosIdx As Long = -1

            editPoint.MoveToLineAndOffset(selection.TopPoint.Line, 1)
            For arrIdx = 0 To rows - 1
                Dim originalLine As Long

                originalLine = editPoint.Line
                editPoint.StartOfLine()
                If howFarOut > 1 Then
                    Dim wordCount As Long

                    For wordCount = 1 To howFarOut
                        MoveWordRight(editPoint)
                    Next
                Else
                    SkipSpaceRight(editPoint)
                End If

                ' If we ran off the end of the line, ignore this one.
                If editPoint.Line > originalLine Then
                    curCharPos(arrIdx) = -1
                    curDispPos(arrIdx) = -1
                    minCharPos(arrIdx) = -1
                    minDispPos(arrIdx) = -1
                Else
                    ' Determine the current display column of the EditPoint.
                    curCharPos(arrIdx) = editPoint.LineCharOffset
                    curDispPos(arrIdx) = editPoint.DisplayColumn

                    ' Determine the minimum column that this element can start
                    ' at (there maybe extra whitespace to the left that can be
                    ' eliminated).
                    If howFarOut > 1 Then
                        Do While IsWhitespace(editPoint.GetText(-2))
                            editPoint.CharLeft()
                        Loop
                    End If
                    minCharPos(arrIdx) = editPoint.LineCharOffset
                    minDispPos(arrIdx) = editPoint.DisplayColumn
                    ' Keep track of the maximum minpos.
                    If maxMinPosIdx = -1 OrElse minDispPos(maxMinPosIdx) < minDispPos(arrIdx) Then
                        maxMinPosIdx = arrIdx
                    End If
                End If
                editPoint.LineDown()
            Next

            ' Now look at the CurPos and MinPos arrays to determine the
            ' leftmost column at which all the elements can be aligned.
            anyMoved = False

            For arrIdx = 0 To rows - 1
                If curDispPos(arrIdx) <> -1 Then
                    AnyRowValid = True
                    If curDispPos(arrIdx) <> minDispPos(maxMinPosIdx) Then
                        ' This element is not correctly aligned; move it to the
                        ' correct column.
                        anyMoved = True
                        editPoint.MoveToLineAndOffset(arrIdx + selection.TopPoint.Line, curCharPos(arrIdx))
                        editPoint.DeleteWhitespace(vsWhitespaceOptions.vsWhitespaceOptionsHorizontal)
                        editPoint.PadToColumn(minDispPos(maxMinPosIdx))
                    End If
                End If
            Next

            ' If we ran out of elements to align, terminate the loop.
            If Not AnyRowValid Then
                anyMoved = True
            End If
            howFarOut = howFarOut + 1
        Loop
        FixLineEnds()
    End Sub

    '' FixLineEnds removes whitespace from the ends of all lines in the selection.
    '' Then for any line in the selection that ends with a semicolon, eliminates
    '' any whitespace between the semicolon and the previous character.
    ''
    '' This is a helper for LineEmUp and a command by itself.
    ''
    Sub FixLineEnds()
        Dim selection As EnvDTE.TextSelection
        Dim editPoint As EnvDTE.EditPoint

        selection = ActiveDocument.Selection
        editPoint = selection.TopPoint.CreateEditPoint
        Do While editPoint.Line < selection.BottomPoint.Line
            editPoint.EndOfLine()
            editPoint.DeleteWhitespace(vsWhitespaceOptions.vsWhitespaceOptionsHorizontal)
            If editPoint.GetText(-1) = ";" Then
                editPoint.CharLeft()
                editPoint.DeleteWhitespace(vsWhitespaceOptions.vsWhitespaceOptionsHorizontal)
            End If
            editPoint.LineDown()
        Loop
    End Sub


    ''
    '' The next several functions are part of FillCommentParagraph.
    ''

    '' SetFillColumn sets the column to which FillCommentParagraph fills text.
    '' It is a command and gets used to make sure there is a column inside
    '' FillColumnParagraph. Define this with an optional param so that we can
    '' call it from the commadn line in VS.
    ''
    Sub SetFillColumn(Optional ByVal fillColumn As String = "")
        If (fillColumn.Length > 0) Then
            DTE.Globals.VariableValue("FillColumn") = CInt(fillColumn)
        Else
            Dim column As String

            column = InputBox("Enter the fill column:")
            If (column = "") Then
                column = "80"
            End If
            DTE.Globals.VariableValue("FillColumn") = CInt(column)
        End If
    End Sub

    '' FillCommentParagraph
    ''
    '' Reformats a comment paragraph to fill lines of comments to a specified
    '' column without going past that column. A comment paragraph is defined by
    '' contiguous lines that all start at the same indentation level as lines
    '' of comments.
    ''
    Sub FillCommentParagraph()
        Dim i As Integer = 0
        Dim textDoc As EnvDTE.TextDocument
        Dim editPoint As EnvDTE.EditPoint
        Dim selection As EnvDTE.TextSelection
        Dim linePrefix As String
        Dim columnLimit As Integer = 0

        DTE.UndoContext.Open("Fill Comment Paragraph")
        Try
            If (DTE.Globals.VariableExists("FillColumn") = False) Then
                SetFillColumn()
            End If
            columnLimit = DTE.Globals.VariableValue("FillColumn")

            textDoc = DTE.ActiveDocument.Object("TextDocument")
            selection = DTE.ActiveDocument.Selection
            editPoint = selection.ActivePoint.CreateEditPoint()

            ' Determine what the existing comment formatting looks like.        
            linePrefix = GetCommentLinePrefix(editPoint)

            ' Find the beginning of the paragraph.
            Do While editPoint.Line > 1
                editPoint.LineUp()
                If Not IsOnNonEmptyCommentLine(editPoint, linePrefix) Then
                    editPoint.LineDown()
                    Exit Do
                End If
            Loop

            ' Iterate over each line of the comment paragraph.
            Do While IsOnNonEmptyCommentLine(editPoint, linePrefix)
                editPoint.EndOfLine()
                editPoint.DeleteWhitespace(vsWhitespaceOptions.vsWhitespaceOptionsHorizontal)
                If editPoint.DisplayColumn > columnLimit Then
                    ' Break a long line.
                    Do While editPoint.DisplayColumn > columnLimit
                        MoveWordLeft(editPoint)
                    Loop
                    If editPoint.LineCharOffset <= linePrefix.Length + 1 Then
                        ' If we moved so far to the left that all the text is now
                        ' to our right, we should move one word to the right;
                        ' otherwise, we'll be inserting an empty comment line.
                        editPoint.MoveToLineAndOffset(editPoint.Line, linePrefix.Length + 1)
                        MoveWordRight(editPoint)
                        If editPoint.LineCharOffset = editPoint.LineLength + 1 Then
                            ' Moving right one word put us back at the end of the
                            ' line, so we don't want to insert a newline.
                            GoTo SkipInsertNewline
                        End If
                    End If
                    ' Insert a line break and prep the new line with the correct
                    ' comment formatting.
                    editPoint.Insert(CStr(Microsoft.VisualBasic.Constants.vbNewLine) + linePrefix)
SkipInsertNewline:
                Else
                    ' Merge some more text into a short line, if possible.
                    Dim extraSpace As Integer
                    Dim text As String

                    extraSpace = columnLimit - editPoint.DisplayColumn
                    editPoint.LineDown()

                    If IsOnNonEmptyCommentLine(editPoint, linePrefix) Then
                        Dim startCol As Integer
                        Dim startDispCol As Integer
                        Dim startRow As Integer
                        Dim lastCol As Integer

                        editPoint.StartOfLine()
                        editPoint.CharRight(linePrefix.Length)
                        startCol = editPoint.LineCharOffset
                        startDispCol = editPoint.DisplayColumn
                        lastCol = startCol
                        startRow = editPoint.Line

                        ' Determine how much text we can merge onto the previous line.                    
                        Do While editPoint.DisplayColumn - startDispCol <= extraSpace And startRow = editPoint.Line
                            lastCol = editPoint.LineCharOffset
                            MoveWordRight(editPoint)
                        Loop

                        If startRow < editPoint.Line Then
                            ' Merge the entire line into the previous one.

                            editPoint.LineUp(editPoint.Line - startRow)
                            editPoint.StartOfLine()
                            editPoint.CharRight(startCol - 1)
                            text = editPoint.GetText(editPoint.LineLength - (startCol - 1))
                            editPoint.StartOfLine()
                            editPoint.Delete(editPoint.LineLength + 1)
                            editPoint.LineUp()
                            editPoint.EndOfLine()
                            editPoint.Insert(" " + text)
                        ElseIf lastCol > startCol Then
                            ' Extract and merge a portion of the line.

                            editPoint.CharLeft(editPoint.LineCharOffset - lastCol)
                            text = editPoint.GetText(startCol - lastCol).Trim()
                            editPoint.Delete(startCol - lastCol)
                            editPoint.LineUp()
                            editPoint.EndOfLine()
                            editPoint.Insert(" " + text)
                            editPoint.LineDown()
                        Else
                            ' There isn't enough space to merge even one word onto this line,
                            ' so move to the next line.

                            editPoint.LineDown()
                        End If
                    End If
                End If
            Loop
        Finally
            DTE.UndoContext.Close()
        End Try
    End Sub



    ' IsOnNonEmptyCommentLine
    '
    ' Looks at the line of the given EditPoint and determines whether it is a
    ' comment line (with the same formatting as the given linePrefix) and
    ' contains some text (other than the comment tokens).
    Function IsOnNonEmptyCommentLine(ByVal editPoint As EnvDTE.EditPoint, ByVal linePrefix As String) As Boolean
        Dim lineText As String
        Dim pfxText As String

        editPoint.StartOfLine()
        lineText = editPoint.GetText(editPoint.LineLength).Trim()
        pfxText = linePrefix.Trim()
        If Left(pfxText, 2) = "/*" Or Left(pfxText, 1) = "*" Then
            ' special case for /*...*/ comments
            If (lineText.Length > 2 And (Left(lineText, 2) = "/*" Or Left(lineText, 2) = "*/")) Or (lineText.Length > 1 And Left(lineText, 1) = "*") Then
                IsOnNonEmptyCommentLine = True
            Else
                IsOnNonEmptyCommentLine = False
            End If
        Else
            ' See if the existing line has the same comment tokens as the
            ' given linePrefix.
            If lineText.Equals(pfxText) Or lineText.IndexOf(pfxText) <> 0 Then
                IsOnNonEmptyCommentLine = False
            Else
                IsOnNonEmptyCommentLine = True
            End If
        End If
    End Function


    ' GetCommentLinePrefix
    '
    ' Based on the comment formatting of the given line, determines the string
    ' that should be prepended to new lines of text in order to maintain
    ' consistent formatting.
    Function GetCommentLinePrefix(ByVal editPoint As EnvDTE.EditPoint) As String
        Dim text As String
        Dim trimText As String
        Dim linePrefix As String

        ' Go to the beginning of the line and remove the initial whitespace to
        ' isolate the comment tokens.
        editPoint.StartOfLine()
        text = editPoint.GetText(editPoint.LineLength)
        trimText = text.TrimStart()
        linePrefix = Left(text, Len(text) - Len(trimText))

        If Left(trimText, 2) = "/*" Then
            ' Special-case C-style commentextSelection.
            linePrefix = linePrefix + " * "
        Else
            Dim leftChar As Char

            leftChar = Left(trimText, 1)
            Do While Char.IsPunctuation(leftChar) Or Char.IsWhiteSpace(leftChar)
                linePrefix = linePrefix + leftChar
                trimText = Right(trimText, trimText.Length - 1)
                leftChar = Left(trimText, 1)
            Loop
        End If

        GetCommentLinePrefix = linePrefix
    End Function


    ' MoveWordRight
    '
    ' Moves an EditPoint one word to the right. If the EditPoint is at the
    ' end of the line, it is moved to the beginning of the following line.
    ' I had to write this function because the built-in EditPoint.WordRight()
    ' method treats punctuation as word separators. This function
    ' recognizes only whitespace as a word separator.
    Sub MoveWordRight(ByRef editPoint As EnvDTE.EditPoint)
        Dim lineLen As Long

        lineLen = editPoint.LineLength
        If (editPoint.LineCharOffset > lineLen) Then
            Dim orgLine As Integer

            orgLine = editPoint.Line
            editPoint.LineDown()
            If (editPoint.Line > orgLine) Then
                editPoint.StartOfLine()
            End If
        Else
            ' First skip over non-whitespace characters.
            Do While editPoint.LineCharOffset <= lineLen And Not IsWhitespace(editPoint.GetText(1))
                editPoint.CharRight()
            Loop
            ' Then skip over whitespace characters, moving to the beginning of
            ' the next word.
            Do While editPoint.LineCharOffset <= lineLen And IsWhitespace(editPoint.GetText(1))
                editPoint.CharRight()
            Loop
        End If
    End Sub


    ' MoveWordLeft
    '
    ' Moves an EditPoint one word to the left. If the EditPoint is at the
    ' beginning of the line, it is moved to the end of the following line.
    ' I had to write this function because the built-in EditPoint.WordLeft()
    ' method treats punctuation as word separators. This function
    ' recognizes only whitespace as a word separator.
    Sub MoveWordLeft(ByRef editPoint As EnvDTE.EditPoint)
        Dim lineLen As Long

        lineLen = editPoint.LineLength
        If (editPoint.LineCharOffset = 1) Then
            Dim orgLine As Integer

            orgLine = editPoint.Line
            editPoint.LineUp()
            If (editPoint.Line < orgLine) Then
                editPoint.EndOfLine()
            End If
        Else
            ' First skip over whitespace characters.
            Do While editPoint.LineCharOffset > 1 And IsWhitespace(editPoint.GetText(-1))
                editPoint.CharLeft()
            Loop
            ' Then skip over non-whitespace characters, moving to the beginning
            ' of the previous word.
            Do While editPoint.LineCharOffset > 1 And Not IsWhitespace(editPoint.GetText(-1))
                editPoint.CharLeft()
            Loop
        End If
    End Sub


    ' IsWhitespace
    '
    ' Looks at the given string and returns whether it is composed entirely of
    ' whitespace characters (tabs and spaces).
    Function IsWhitespace(ByVal str As String) As Boolean
        If str.Trim().Length = 0 Then
            IsWhitespace = True
        Else
            IsWhitespace = False
        End If
    End Function


    ''
    '' Finding matching lines, nonmatching lines, and counting matches
    ''

    '' ListMatchingLines prompts for a literal pattern and then lists all
    '' lines in the current buffer that contain the pattern.
    ''
    Sub ListMatchingLines()
        Dim window As Window
        Dim textSelection As TextSelection
        Dim textSelectionPointSaved As TextPoint
        Dim outputWindowPane As OutputWindowPane
        Dim findResult As EnvDTE.vsFindResult
        Dim textDocument As EnvDTE.TextDocument
        Dim lastFoundAt As Integer = 0

        textDocument = DTE.ActiveDocument.Object("TextDocument")
        textSelection = textDocument.Selection
        window = DTE.ActiveDocument.Windows.Item(1)
        Utilities.PrepareDefaultFind("List Matching Lines")

        '' Set up output window pane and loop until no more matches.
        outputWindowPane = GetOutputWindowPane("Matching Lines")
        textSelection.StartOfDocument()
        textSelectionPointSaved = textSelection.ActivePoint.CreateEditPoint()

        ''GetOutputWindowPane activates Output Window, so re-activate our window.
        window.Activate()
        outputWindowPane.Clear()

        CType(DTE.Find, EnvDTE80.Find2).WaitForFindToComplete = True
        findResult = DTE.Find.Execute()
        While (findResult = vsFindResult.vsFindResultFound)
            If textSelection.AnchorPoint.Line <= lastFoundAt Then
                Exit While
            End If

            textSelection.SelectLine()
            outputWindowPane.OutputString("line " + textSelection.AnchorPoint.Line.ToString() + ": " + textSelection.Text)
            lastFoundAt = textSelection.AnchorPoint.Line
            textSelection.StartOfLine(vsStartOfLineOptions.vsStartOfLineOptionsFirstColumn)
            findResult = DTE.Find.Execute()
        End While

        '' Restore caret to location before invoking this command.
        textSelection.MoveToPoint(textSelectionPointSaved)

    End Sub

    Sub ListNonMatchingLines()
        Dim window As EnvDTE.Window
        Dim textSelection As EnvDTE.TextSelection
        Dim textSelectionSaved As EnvDTE.TextPoint
        Dim outputWinPane As EnvDTE.OutputWindowPane
        Dim endLine As Integer
        Dim done As Boolean = False

        window = DTE.ActiveWindow
        textSelection = window.Selection
        textSelectionSaved = textSelection.ActivePoint.CreateEditPoint()
        endLine = textSelection.Parent.EndPoint.Line

        textSelection.StartOfDocument()

        Utilities.PrepareDefaultFind("List Non-matching Lines")
        DTE.Find.Target = vsFindTarget.vsFindTargetCurrentDocumentSelection

        '' Set up output window pane and loop until no more matches.
        outputWinPane = GetOutputWindowPane("Non-matching Lines")
        '' GetOutputWindowPane activates Output Window, so re-activate our window.
        window.Activate()
        outputWinPane.Clear()

        endLine = textSelection.Parent.EndPoint.Line
        While ((endLine <> textSelection.ActivePoint.Line) Or Not done)
            textSelection.SelectLine()
            If (DTE.Find.Execute() = vsFindResult.vsFindResultNotFound) Then
                outputWinPane.OutputString(textSelection.Text)
            End If
            done = InStr(DTE.StatusBar.Text, passedString)
            textSelection.CharLeft()
            textSelection.LineDown()
        End While

        '' Restore caret to location before invoking this command.
        textSelection.MoveToPoint(textSelectionSaved)

    End Sub

    Sub CountOccurrences()
        Dim textSelection As EnvDTE.TextSelection
        Dim textSelectionPointSaved As TextPoint
        Dim count As Integer = 0
        Dim findResult As EnvDTE.vsFindResult
        Dim firstFindLocation As EnvDTE.TextPoint

        textSelection = DTE.ActiveWindow.Selection
        textSelectionPointSaved = textSelection.ActivePoint.CreateEditPoint()
        textSelection.StartOfDocument()
        If (Utilities.PrepareDefaultFind("Count Occurrences") = "") Then
            Return
        End If

        ' The Version 7.0 & 7.1 macros used the following While statement:
        '   While ((findResult = vsFindResult.vsFindResultFound) And (InStr(DTE.StatusBar.Text, "Passed") <> 1))
        ' However, with the Find2.WaitForFindToComplete property the check 
        ' for specific text to be shown in the status bar can be removed.
        CType(DTE.Find, EnvDTE80.Find2).WaitForFindToComplete = True
        findResult = DTE.Find.Execute()
        While (findResult = vsFindResult.vsFindResultFound)
            If (firstFindLocation Is Nothing) Then
                Dim foundSelection As EnvDTE.TextSelection

                foundSelection = DTE.ActiveWindow.Selection
                firstFindLocation = foundSelection.ActivePoint.CreateEditPoint
            Else
                Dim foundSelection As EnvDTE.TextSelection

                foundSelection = DTE.ActiveWindow.Selection
                If (firstFindLocation.EqualTo(foundSelection.ActivePoint)) Then
                    Exit While
                End If
            End If
            count = count + 1
            findResult = DTE.Find.Execute()
        End While

        '' Restore caret to location before invoking this command.
        textSelection.MoveToPoint(textSelectionPointSaved)

        MsgBox("There were " & count & " occurrences.")
    End Sub


    Sub InsertTime()
        Dim textSelection As EnvDTE.TextSelection

        textSelection = CType(DTE.ActiveDocument.Selection(), EnvDTE.TextSelection)
        textSelection.Text = System.DateTime.Now.ToLongTimeString()
    End Sub

    Sub InsertDate()
        Dim textSelection As EnvDTE.TextSelection

        textSelection = CType(DTE.ActiveDocument.Selection(), EnvDTE.TextSelection)
        textSelection.Text = System.DateTime.Now.ToLongDateString()
    End Sub

    Sub InsertTimeDate()
        Dim textSelection As EnvDTE.TextSelection

        textSelection = CType(DTE.ActiveDocument.Selection(), EnvDTE.TextSelection)
        textSelection.Text = System.DateTime.Now.ToLongDateString() + " " + System.DateTime.Now.ToLongTimeString()
    End Sub

    Function IsPrintableFile(ByVal projItem As EnvDTE.ProjectItem) As Boolean
        Dim fileName As String
        Dim extensions As New System.Collections.Specialized.StringCollection
        ' If you add a file to your project that is of a type that can be printed, 
        '  then add the extension of that file type to this list:
        Dim exts As String() = {".cpp", ".c", ".h", ".idl", ".def", ".rgs", ".rc", ".cs", ".vb", ".xml", ".txt", ".jsl"}

        extensions.AddRange(exts)
        fileName = projItem.FileNames(1)
        Return extensions.Contains(System.IO.Path.GetExtension(fileName).ToLower())
    End Function

    ' Walk the list of files in a the project selected within 
    '   Solution Explorer, and then print the file.
    Sub PrintItemsInSelectedProject()
        Dim proj As EnvDTE.Project

        If DTE.ActiveSolutionProjects.Length <> 1 Then
            MsgBox("Select one project within the Solution Explorer, then re-run this macro.")
            Exit Sub
        End If
        proj = DTE.ActiveSolutionProjects(0)
        PrintItemsInSelectedProject(proj.ProjectItems)
    End Sub

    Private Sub PrintItemsInSelectedProject(ByVal projItems As EnvDTE.ProjectItems)
        Dim projItem As EnvDTE.ProjectItem

        For Each projItem In projItems
            If (IsPrintableFile(projItem) = True) Then
                If (projItem.IsOpen(EnvDTE.Constants.vsViewKindTextView)) Then
                    projItem.Document.PrintOut()
                Else
                    Dim doc As EnvDTE.Document

                    doc = projItem.Open(EnvDTE.Constants.vsViewKindTextView).Document
                    doc.PrintOut()
                    doc.Close(vsSaveChanges.vsSaveChangesNo)
                End If
            End If
            PrintItemsInSelectedProject(projItem.ProjectItems)
        Next
    End Sub

End Module

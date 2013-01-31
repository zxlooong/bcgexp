'' Copyright (c) Microsoft Corporation.  All rights reserved.
''
'' These samples demonstrate how to use the VS Automation Object Model.
'' They are unsupported, but you can use them as-is.  They are not intended 
'' to demonstrate how to implement fully rigorous commands.  For example, 
'' if a command expects there to be selected text, but you invoke
'' the macro on a blank line, the macro's behavior is undefined.
''

Imports EnvDTE
Imports System
Imports EnvDTE80
Imports System.Diagnostics
Imports Microsoft.Win32

Public Module Accessibility

    Private Const fontSizeIncrement As Integer = 2
    Private Const minimumSupportedEditorSize As Integer = 3
    Private whiteColor As UInt32 = Convert.ToUInt32(&HFFFFFF) ' FFFFFF is hex value of the RGB color white.
    Private blackColor As UInt32 = Convert.ToUInt32(0)        ' 0 is the value of the RGB color white.

    ' Changes the font size to match the font size of the operating system.
    Public Sub UpdateTextEditorFontSizeToMatchDisplayProperties()
        Dim textEditorFontsAndColors As Properties
        Dim font As System.Drawing.Font
        Dim pointSize As Integer
        Dim fontSize As [Property]

        ' Get font size from menu font to use as an approximation.
        font = System.Windows.Forms.SystemInformation.MenuFont
        pointSize = font.GetHeight() - 3 ' Subtract 3 for adjustment.

        ' Update the text edit font size.
        textEditorFontsAndColors = DTE.Properties("FontsAndColors", "TextEditor")
        fontSize = textEditorFontsAndColors.Item("FontSize")
        fontSize.Value = pointSize
    End Sub

    ' Increases the font size used within the editor.
    Public Sub IncreaseTextEditorFontSize() ' Useful to bind to a keystroke, like Ctrl+Alt+Shift+DownArrow.
        Dim textEditorFontsAndColors As Properties

        textEditorFontsAndColors = DTE.Properties("FontsAndColors", "TextEditor")
        textEditorFontsAndColors.Item("FontSize").Value += fontSizeIncrement
    End Sub

    ' Decreases the font size used within the editor.
    Public Sub DecreaseTextEditorFontSize() ' Useful to bind to a keystroke, like Ctrl+Alt+Shift+UpArrow.
        Dim textEditorFontsAndColors As Properties
        Dim fontSize As [Property]

        textEditorFontsAndColors = DTE.Properties("FontsAndColors", "TextEditor")
        fontSize = textEditorFontsAndColors.Item("FontSize")
        If fontSize.Value >= minimumSupportedEditorSize Then
            fontSize.Value -= fontSizeIncrement
        End If
    End Sub

    ' Turns all colors used within the editor to black and white, or
    '   restores the colors used before the colors were turned black and white.
    Public Sub ToggleTextEditorGrayScale()
        Dim applicationRegistryRootKey As RegistryKey
        Dim accessibilityKey As RegistryKey
        Dim textEditorFontsAndColors As Properties
        Dim fontsAndColors As FontsAndColorsItems
        Dim editorInGrayScale As Boolean

        ' Determine whether the user has toggled grayscale by looking up info in registry.
        applicationRegistryRootKey = Registry.CurrentUser.OpenSubKey(DTE.RegistryRoot, True)
        accessibilityKey = applicationRegistryRootKey.OpenSubKey("Accessibility", True)

        ' Create key if it does not exist.
        If accessibilityKey Is Nothing Then
            applicationRegistryRootKey.CreateSubKey("Accessibility")
            accessibilityKey = applicationRegistryRootKey.OpenSubKey("Accessibility", True)
            accessibilityKey.SetValue("TextEditorInGrayScale", 0)
        End If

        ' Get current editor grayscale state.
        editorInGrayScale = CType(accessibilityKey.GetValue("TextEditorInGrayScale"), Boolean)

        ' Get the Fonts and Colors object.
        textEditorFontsAndColors = DTE.Properties("FontsAndColors", "TextEditor")
        fontsAndColors = textEditorFontsAndColors.Item("FontsAndColorsItems").Object

        ' Determine whether grayscale settings or previous settings should be applied.
        If editorInGrayScale Then
            ' Revert to previous colors found from the registry.
            For Each displayItem As ColorableItems In fontsAndColors
                displayItem.Background = UInt32.Parse(accessibilityKey.GetValue(displayItem.Name + "_BG"))
                displayItem.Foreground = UInt32.Parse(accessibilityKey.GetValue(displayItem.Name + "_FG"))
            Next

            ' Toggle flag in registry to indicate text editor is not in gray scale state.
            accessibilityKey.SetValue("TextEditorInGrayScale", 0)
        Else
            ' Write current colors into registry and apply grayscale.
            For Each displayItem As ColorableItems In fontsAndColors
                accessibilityKey.SetValue(displayItem.Name + "_BG", displayItem.Background.ToString)
                accessibilityKey.SetValue(displayItem.Name + "_FG", displayItem.Foreground.ToString)
                displayItem.Background = whiteColor
                displayItem.Foreground = blackColor
            Next

            ' Toggle flag in registry to indicate text editor is in gray scale state.
            accessibilityKey.SetValue("TextEditorInGrayScale", 1)
        End If
    End Sub

    ' Makes tool windows appear in the MDI document space.
    Public Sub MaximizeToolWindowsInEnvironment()
        For Each window As Window In DTE.Windows
            ' Check that this is a tool window and not a document window.
            If (window.Document Is Nothing) Then
                ' Turn off auto-hiding.
                Try
                    If window.AutoHides = True Then
                        window.AutoHides = False
                    End If
                Catch exception As Exception
                End Try

                ' Set to undockable (which means show the document as maximized).
                Try
                    window.Linkable = False
                Catch
                End Try
            End If
        Next
    End Sub

End Module

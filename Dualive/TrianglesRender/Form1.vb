Imports System.IO
Imports System.Drawing.Imaging

Public Class Form1
    ' Distance between right progress edge and form edge
    ' Not sure how to get it programmatically, so it's hardcoded
    Dim ProgressBarOffset = 28

    Private Sub Form1_Paint(ByVal sender As Object, e As PaintEventArgs) Handles MyBase.Paint
        DrawTriangles(e.Graphics)
    End Sub

    Sub DrawBackground(g As Graphics, bounds As Size, scale As Single)
        Dim brush As New SolidBrush(Color.White)
        Dim size = NumericUpDown3.Value * scale
        Dim hs = size / 2
        Dim center As New Point(bounds.Width / 2, bounds.Height / 2)

        Dim expand As Rectangle
        Dim startpos As Point = New Point(0, 0)
        Dim boundValue = NumericUpDown5.Value
        If (bounds.Width > bounds.Height) Then
            startpos = New Point(0, center.Y - boundValue / 2)
            expand = New Rectangle(startpos, New Size(boundValue, boundValue))
        ElseIf (bounds.Width < bounds.Height) Then
            startpos = New Point(center.X - bounds.Height / 2, 0)
        End If

        expand = New Rectangle(startpos, New Size(boundValue, boundValue))

        Dim twosCounter = 2
        Dim placeCounter = 1
        Dim placeCounterMax = 1
        Dim direction As New Point(1, 0)
        Dim outsideBorder = False
        Dim pos = center

        g.FillPolygon(brush, GetBackgroundTriangle(pos, hs))

        While Not outsideBorder
            outsideBorder = True
            Dim height = GetEquilateralTriangleHeight(size)
            pos += New Point(direction.X * size, direction.Y * height)
            Dim bgtri = GetBackgroundTriangle(pos, hs)
            g.FillPolygon(brush, bgtri)

            For Each p In bgtri
                If expand.Contains(p) Then
                    outsideBorder = False
                    GoTo end_of_for
                End If
            Next
end_of_for:
            placeCounter -= 1
            If placeCounter = 0 Then
                SwitchDirection(direction)
                twosCounter -= 1
                If twosCounter = 0 Then
                    twosCounter = 2
                    placeCounterMax += 1
                End If
                placeCounter = placeCounterMax
            End If
        End While
    End Sub

    Sub DrawCenterpiece(g As Graphics, bounds As Size, scale As Single)
        Dim brush As New SolidBrush(Color.White)
        Dim center As New Point(bounds.Width / 2, bounds.Height / 2)
        Dim size = bounds.Width * scale
        Dim hs = size / 2
        g.FillPolygon(brush, GetBackgroundTriangle(center, hs))
    End Sub

    Sub DrawTriangles(g As Graphics)
        Dim bgScale = NumericUpDown4.Value
        DrawBackground(g, ClientSize, bgScale)

        Dim centerpieceScale = NumericUpDown2.Value
        DrawCenterpiece(g, ClientSize, centerpieceScale)
    End Sub

    Function GetEquilateralTriangleHeight(ByVal base) As Single
        Dim height = Math.Sin(Math.PI / 3) * base
        Return height
    End Function

    Function GetBackgroundTriangle(ByRef pos As Point, ByRef hs As Integer) As Point()
        Dim bgtri(2) As Point
        Dim height = GetEquilateralTriangleHeight(hs * 2)
        Dim halfHeight = height / 2
        bgtri(0) = New Point(pos.X, pos.Y - halfHeight)
        bgtri(1) = New Point(pos.X - hs, pos.Y + halfHeight)
        bgtri(2) = New Point(pos.X + hs, pos.Y + halfHeight)
        Return bgtri
    End Function

    Sub SwitchDirection(ByRef direction As Point)
        Select Case direction
            Case New Point(1, 0)
                direction = New Point(0, 1)
            Case New Point(0, 1)
                direction = New Point(-1, 0)
            Case New Point(-1, 0)
                direction = New Point(0, -1)
            Case New Point(0, -1)
                direction = New Point(1, 0)
        End Select
    End Sub

    Private Sub Form1_Resize(sender As Object, e As EventArgs) Handles Me.ResizeEnd
        Me.Invalidate()
    End Sub

    Private Sub NumericUpDown4_ValueChanged(sender As Object, e As EventArgs) Handles NumericUpDown4.ValueChanged
        Me.Invalidate()
    End Sub

    Private Sub NumericUpDown2_ValueChanged(sender As Object, e As EventArgs) Handles NumericUpDown2.ValueChanged
        Me.Invalidate()
    End Sub

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        If SaveFileDialog1.ShowDialog() <> Windows.Forms.DialogResult.Cancel Then
            Dim path = SaveFileDialog1.FileName.Split(".png")(0)
            Dim size = CInt(NumericUpDown1.Value)
            Dim height = GetEquilateralTriangleHeight(size)
            Dim botHeight = Math.Tan(Math.PI / 6) * (size / 2)
            Dim imageHeight = (height - botHeight) * 2
            Dim bitmap As New Bitmap(size, CInt(Math.Ceiling(imageHeight)))
            Dim graphics As Graphics = graphics.FromImage(bitmap)
            graphics.SmoothingMode = Drawing2D.SmoothingMode.AntiAlias
            graphics.TextRenderingHint = Drawing.Text.TextRenderingHint.AntiAlias
            DrawCenterpiece(graphics, New Size(size, height), 1.0F)
            bitmap.Save(path + ".png", ImageFormat.Png)

            bitmap = New Bitmap(size, CInt(Math.Ceiling(height)))
            graphics = graphics.FromImage(bitmap)
            graphics.SmoothingMode = Drawing2D.SmoothingMode.AntiAlias
            graphics.TextRenderingHint = Drawing.Text.TextRenderingHint.AntiAlias
            DrawCenterpiece(graphics, New Size(size, height), 1.0F)
            Dim noSpacing = "NoSpacing"
            bitmap.Save(path + noSpacing + ".png", ImageFormat.Png)
        End If
    End Sub

    Private Sub Button2_Click(sender As Object, e As EventArgs) Handles Button2.Click
        If SaveFileDialog1.ShowDialog() <> Windows.Forms.DialogResult.Cancel Then
            Dim path = SaveFileDialog1.FileName.Split(".png")(0)
            Dim size = CInt(NumericUpDown5.Value)
            Dim bitmap As New Bitmap(size, size)
            Dim graphics As Graphics = graphics.FromImage(bitmap)
            graphics.SmoothingMode = Drawing2D.SmoothingMode.AntiAlias
            graphics.TextRenderingHint = Drawing.Text.TextRenderingHint.AntiAlias
            DrawBackground(graphics, New Size(size, size), 1.0F)
            bitmap.Save(path + ".png", ImageFormat.Png)

            Dim pieceSize = CInt(NumericUpDown3.Value)
            Dim height = GetEquilateralTriangleHeight(pieceSize)
            bitmap = New Bitmap(pieceSize, CInt(Math.Ceiling(height)))
            graphics = graphics.FromImage(bitmap)
            graphics.SmoothingMode = Drawing2D.SmoothingMode.AntiAlias
            graphics.TextRenderingHint = Drawing.Text.TextRenderingHint.AntiAlias
            DrawCenterpiece(graphics, New Size(pieceSize, height), 1.0F)
            Dim piece = "Piece"
            bitmap.Save(path + piece + ".png", ImageFormat.Png)
        End If
    End Sub
End Class
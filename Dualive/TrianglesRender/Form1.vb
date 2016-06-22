Public Class Form1
    ' Distance between right progress edge and form edge
    ' Not sure how to get it programmatically, so it's hardcoded
    Dim ProgressBarOffset = 28

    Private Sub Form1_Paint(ByVal sender As Object, e As PaintEventArgs) Handles MyBase.Paint
        DrawTriangles(e.Graphics)
    End Sub

    Sub DrawTriangles(g As Graphics)
        Dim brush As New SolidBrush(Color.White)
        Dim center As New Point(ClientSize.Width / 2, ClientSize.Height / 2)
        Dim bounds = ClientRectangle

        Dim scale = NumericUpDown4.Value
        Dim size = NumericUpDown3.Value * scale
        Dim hs = size / 2

        Dim twosCounter = 2
        Dim placeCounter = 1
        Dim placeCounterMax = 1
        Dim direction As New Point(1, 0)
        Dim outsideBorder = False
        Dim pos = center

        g.FillPolygon(brush, GetBackgroundTriangle(pos, hs))

        While Not outsideBorder
            outsideBorder = True
            pos += New Point(direction.X * size, direction.Y * size)
            Dim bgtri = GetBackgroundTriangle(pos, hs)
            g.FillPolygon(brush, bgtri)

            For Each p In bgtri
                If bounds.Contains(p) Then
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

        scale = NumericUpDown2.Value
        size = NumericUpDown1.Value * scale
        hs = size / 2
        g.FillPolygon(brush, GetBackgroundTriangle(center, hs))
    End Sub

    Function GetBackgroundTriangle(ByRef pos As Point, ByRef hs As Integer) As Point()
        Dim bgtri(2) As Point
        bgtri(0) = New Point(pos.X, pos.Y - hs)
        bgtri(1) = New Point(pos.X - hs, pos.Y + hs)
        bgtri(2) = New Point(pos.X + hs, pos.Y + hs)
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

    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles Me.Load
        My.Settings.Reload()
        If My.Settings.LastFolder IsNot Nothing Then
            FolderBrowserDialog1.SelectedPath = My.Settings.LastFolder
            FolderBrowserDialog2.SelectedPath = My.Settings.LastFolder
        End If
    End Sub

    Private Sub Form1_Resize(sender As Object, e As EventArgs) Handles Me.Resize
        ProgressBar1.Width = Me.Width - ProgressBarOffset - ProgressBar1.Left
        ProgressBar2.Width = ProgressBar1.Width
        Me.Invalidate()
    End Sub

    Private Sub NumericUpDown4_ValueChanged(sender As Object, e As EventArgs) Handles NumericUpDown4.ValueChanged
        Me.Invalidate()
    End Sub

    Private Sub NumericUpDown2_ValueChanged(sender As Object, e As EventArgs) Handles NumericUpDown2.ValueChanged
        Me.Invalidate()
    End Sub
End Class
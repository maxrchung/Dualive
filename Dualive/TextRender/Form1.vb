Imports System.IO
Imports System.Drawing.Imaging
Imports System.Runtime.InteropServices

Public Class Form1
    <DllImport("user32.dll", SetLastError:=True)> _
    Public Shared Function CreateCaret(ByVal hWnd As IntPtr, ByVal hBitmap As IntPtr, ByVal nWidth As Integer, ByVal nHeight As Integer) As Boolean
    End Function

    <DllImport("user32.dll", SetLastError:=True)> _
    Public Shared Function ShowCaret(ByVal hWnd As IntPtr) As Boolean
    End Function

    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles Me.Load
        FontDialog1.Font = RichTextBox1.Font
        CreateCaret(RichTextBox1.Handle, IntPtr.Zero, 500, RichTextBox1.Height)
        ShowCaret(RichTextBox1.Handle)
    End Sub

    Private Sub FontToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) _
        Handles FontToolStripMenuItem.Click
        Dim prevFont As Font = RichTextBox1.Font
        If FontDialog1.ShowDialog() <> Windows.Forms.DialogResult.Cancel Then
            RichTextBox1.Font = FontDialog1.Font
        Else
            RichTextBox1.Font = prevFont
        End If
    End Sub

    Private Sub LoadToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) _
        Handles LoadToolStripMenuItem.Click

        If OpenFileDialog1.ShowDialog() <> Windows.Forms.DialogResult.Cancel Then
            Dim fileName = OpenFileDialog1.FileName
            RichTextBox1.Text = File.ReadAllText(fileName)
        End If
    End Sub

    Private Sub FontDialog_Apply(sender As Object, e As EventArgs) Handles FontDialog1.Apply
        RichTextBox1.Font = FontDialog1.Font
    End Sub

    Private Sub RenderToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) _
        Handles RenderToolStripMenuItem.Click
        ' vbLf equivalent(?) to \n
        ' StringSplitOptions to remove any errors with trying to process empty lines
        Dim lines As String() = RichTextBox1.Text.Split(New String() {vbLf}, StringSplitOptions.RemoveEmptyEntries)
        ' Handles exception with nothing on screen
        If lines.Length > 0 Then
            For Each line In lines
                Dim size As Size = TextRenderer.MeasureText(line, RichTextBox1.Font)
                Dim bitmap As New Bitmap(size.Width, size.Height)
                Dim graphics As Graphics = graphics.FromImage(bitmap)
                ' Otherwise really jaggedy
                graphics.SmoothingMode = Drawing2D.SmoothingMode.AntiAlias
                graphics.TextRenderingHint = Drawing.Text.TextRenderingHint.AntiAlias
                Dim foreColor As New SolidBrush(Color.White)
                Dim point As New PointF(0.0F, 0.0F)
                graphics.DrawString(RichTextBox1.Text, RichTextBox1.Font, foreColor, point)
                Dim filePath = line + ".png"
                bitmap.Save(filePath, ImageFormat.Png)
            Next
        End If
    End Sub

    Private Sub RichTextBox1_TextChanged(sender As Object, e As EventArgs) Handles RichTextBox1.TextChanged

    End Sub
End Class
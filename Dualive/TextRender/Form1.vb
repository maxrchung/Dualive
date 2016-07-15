Imports System.IO
Imports System.Drawing.Imaging

Public Class Form1
    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles Me.Load
        My.Settings.Reload()
        If My.Settings.LastFolder IsNot Nothing Then
            FolderBrowserDialog1.SelectedPath = My.Settings.LastFolder
        End If
        If My.Settings.LastFont IsNot Nothing Then
            RichTextBox1.Font = My.Settings.LastFont
            FontDialog1.Font = My.Settings.LastFont
        Else
            FontDialog1.Font = RichTextBox1.Font
        End If
    End Sub

    Private Sub RichTextBox1_KeyDown(sender As Object, e As KeyEventArgs) Handles RichTextBox1.KeyDown
        If e.Control AndAlso e.KeyCode = Keys.N Then
            NewToolStripMenuItem_Click(sender, e)
        ElseIf e.Control AndAlso e.KeyCode = Keys.O Then
            OpenToolStripMenuItem_Click(sender, e)
        ElseIf e.Control AndAlso e.KeyCode = Keys.S Then
            SaveToolStripMenuItem_Click(sender, e)
        ElseIf e.Control AndAlso e.KeyCode = Keys.F Then
            FontToolStripMenuItem_Click(sender, e)
        ElseIf e.Control AndAlso e.KeyCode = Keys.R Then
            RenderToolStripMenuItem_Click(sender, e)
        End If
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

    Private Sub OpenToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) _
        Handles OpenToolStripMenuItem.Click
        If OpenFileDialog1.ShowDialog() <> Windows.Forms.DialogResult.Cancel Then
            Dim fileName = OpenFileDialog1.FileName
            RichTextBox1.Text = File.ReadAllText(fileName)
        End If
    End Sub

    Private Sub FontDialog_Apply(sender As Object, e As EventArgs) Handles FontDialog1.Apply
        RichTextBox1.Font = FontDialog1.Font
        My.Settings.LastFont = FontDialog1.Font
    End Sub

    Private Sub RenderToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles RenderToolStripMenuItem.Click
        If RichTextBox1.TextLength > 0 Then
            ' vbLf equivalent(?) to \n
            ' StringSplitOptions to remove any errors with trying to process empty lines
            Dim lines As String() = RichTextBox1.Text.Split(New String() {vbLf}, StringSplitOptions.RemoveEmptyEntries)
            If FolderBrowserDialog1.ShowDialog() <> Windows.Forms.DialogResult.Cancel Then
                Dim folderPath = FolderBrowserDialog1.SelectedPath
                My.Settings.LastFolder = folderPath
                ProgressBar1.Visible = True
                ProgressBar1.Maximum = lines.Length
                For index As Integer = 0 To lines.Length - 1
                    Dim graphics = Me.CreateGraphics()
                    Dim size As SizeF = graphics.MeasureString(lines(index), RichTextBox1.Font)
                    Dim bitmap As New Bitmap(CInt(size.Width), CInt(size.Height))
                    graphics = graphics.FromImage(bitmap)
                    ' Otherwise really jaggedy
                    graphics.SmoothingMode = Drawing2D.SmoothingMode.AntiAlias
                    graphics.TextRenderingHint = Drawing.Text.TextRenderingHint.AntiAlias
                    Dim foreColor As New SolidBrush(Color.White)
                    Dim point As New PointF(0.0F, 0.0F)
                    graphics.DrawString(lines(index), RichTextBox1.Font, foreColor, point)
                    Dim fullPath As String = Path.Combine(folderPath, CStr(index) + ".png")
                    bitmap.Save(fullPath, ImageFormat.Png)
                    ProgressBar1.Increment(1)
                Next
                ProgressBar1.Value = 0
                ProgressBar1.Visible = False
                ProgressBar1.Enabled = False
            End If
        End If
    End Sub

    Private Sub NewToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles NewToolStripMenuItem.Click
        If RichTextBox1.TextLength > 0 Then
            If MessageBox.Show("Are you sure you want to clear the form?", "Confirmation", MessageBoxButtons.OKCancel) <> Windows.Forms.DialogResult.Cancel Then
                RichTextBox1.Clear()
            End If
        End If
    End Sub

    Private Sub SaveToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles SaveToolStripMenuItem.Click
        If RichTextBox1.TextLength > 0 Then
            If SaveFileDialog1.ShowDialog() <> Windows.Forms.DialogResult.Cancel Then
                Using writer As StreamWriter = My.Computer.FileSystem.OpenTextFileWriter(SaveFileDialog1.FileName, False)
                    Dim lines As String() = RichTextBox1.Text.Split(New String() {vbLf}, StringSplitOptions.RemoveEmptyEntries)
                    For Each line As String In lines
                        writer.WriteLine(line)
                    Next
                End Using
            End If
        End If
    End Sub


End Class
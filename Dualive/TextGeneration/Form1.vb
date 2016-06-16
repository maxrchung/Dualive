Imports System.IO

Public Class Form1
    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles Me.Load
        FontDialog1.Font = RichTextBox1.Font
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

    Private Sub RenderToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) _
        Handles RenderToolStripMenuItem.Click

    End Sub

    Private Sub FontDialog_Apply(sender As Object, e As EventArgs) Handles FontDialog1.Apply
        RichTextBox1.Font = FontDialog1.Font
    End Sub
End Class
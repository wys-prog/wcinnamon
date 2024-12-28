using Godot;
using System.Text;

namespace Wcinnamon.Syslib.FileSystem.FileIO;

public partial class Writer : System.IO.TextWriter
{
  private FileAccess file;

  public override Encoding Encoding => Encoding.UTF8;

  public void Open(string path)
  {
    file = FileAccess.Open(path, FileAccess.ModeFlags.Write);
  }

  public override void Write(char value)
  {
    if (file == null) throw new System.NullReferenceException();

    file.StoreString(value.ToString());
  }


  public override void Write(string value)
  {
    if (file == null) throw new System.NullReferenceException();

    file.StoreString(value);
  }


  public override void Write(char[] buffer, int index, int count)
  {
    if (file == null) throw new System.NullReferenceException();

    string text = new(buffer, index, count);
    file.StoreString(text);
  }

  // Méthode pour fermer le fichier
  public override void Close()
  {
    if (file != null)
    {
      file.Close();
      file = null;
    }
  }

  public bool IsOpen()
  {
    return file != null;
  }

  protected override void Dispose(bool disposing)
  {
    base.Dispose(disposing);
    Close();
  }
}
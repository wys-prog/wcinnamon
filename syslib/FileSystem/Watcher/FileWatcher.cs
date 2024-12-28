using System.IO;
using Godot;

// WC# API, Wys - Wide Cinnamon C# API 
// This code is free, and open source.

namespace Wcinnamon.Syslib.FileSystem.Watcher; // Wcinnamon.Syslib.FileSystem.Watcher.FileWatcher

// This class will watch the specified file « path ».
// When somthing is added to the file, the « callable » will be
// called.
// No default constructor is supported,
// Only the « Create » function is avaible for interactions 
// This class is written for GDScript files.

public partial class FileWatcher : Node
{
  private readonly FileSystemWatcher watcher = new();
  private Callable toCall;

  public void Create(string path, Callable callable)
  {
    watcher.Path = path;
    watcher.EnableRaisingEvents = true;
    watcher.NotifyFilter = NotifyFilters.LastWrite;
    watcher.Changed += OnChange;

    toCall = callable;
    
  }

  private void OnChange(object sender, FileSystemEventArgs args)
  {
    toCall.Call(); // We cannot give any arguments.
  }
}


using System.IO;
using Godot;

namespace Wcinnamon.Syslib.FileSystem.Watcher;

#warning TODO !!! 

public partial class DirectoryWatcher : Node
{
  private readonly FileSystemWatcher watcher = new();
  private Callable toCall;

  public void Create(string path, Callable callable)
  {
    watcher.Path = path;
    watcher.EnableRaisingEvents = true;
    watcher.NotifyFilter = NotifyFilters.LastWrite
                         | NotifyFilters.DirectoryName
                         | NotifyFilters.Attributes
                         | NotifyFilters.Size
                         | NotifyFilters.LastAccess
                         | NotifyFilters.CreationTime
                         | NotifyFilters.Security;

    watcher.Changed += OnChange;

    toCall = callable;

  }

  private void OnChange(object sender, FileSystemEventArgs args)
  {
    toCall.Call(); // We cannot give any arguments.
  }
}
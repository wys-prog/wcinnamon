using System.IO;
using Godot;

namespace Wcinnamon.Source;

public partial class KernelLoader : Node
{
  public static readonly string UserPath = OS.GetUserDataDir();
  public static readonly string SystemFolder = $"{UserPath}/system/";
  public static readonly string ApplicationsFolder = $"{UserPath}/app/";
  public static readonly string LibrariesFOlder = $"{UserPath}/libs/";
  public static readonly string UsersFolder = $"{UserPath}/users/";

  public static readonly string[] SystemFiles =
  [
    $"{SystemFolder}/onboot.gd", $"{SystemFolder}/logs", $"{SystemFolder}/stderr",
    $"{SystemFolder}/server-list"
  ];

  private static void InitDirectory()
  {
    try
    {
      Directory.CreateDirectory(SystemFolder);
      Directory.CreateDirectory(ApplicationsFolder);
      Directory.CreateDirectory(LibrariesFOlder);
      Directory.CreateDirectory(UsersFolder);
    }
    finally { }
  }

  private static void InitFiles()
  {
    foreach (var item in SystemFiles)
    {
      try
      {
        File.Create(item);
      }
      finally { }
    }
  }

  public static void InitKernel()
  {
    InitDirectory();
    InitFiles();
    // Todo « System.Modules » → To clone !! 
  }
}
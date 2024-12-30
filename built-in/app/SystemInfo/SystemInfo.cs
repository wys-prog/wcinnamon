using System;
using System.Collections.Generic;
using System.IO;
using Godot;

namespace Wcinnamon.BuiltIn.App.SystemInfo;

public partial class SystemInfo : Node
{
	public static string[] ListSubDirecories(string dir)
	{
		string[] dirs;

		try
		{
			dirs = Directory.GetDirectories(dir);

			for (int i = 0; i < dirs.Length; i++)
			{
				dirs[i] = $"DIR: ";
			}
		}
		catch (Exception e)
		{
			dirs = [$"[color=red]Error:\n{e}\n"];
		}

		return [.. dirs];
	}
}

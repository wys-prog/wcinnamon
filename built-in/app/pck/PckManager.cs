using Godot;
using System.IO;
using System.Linq;
using System.Collections.Generic;
using Wcinnamon.Source;

namespace Wcinnamon.BuiltIn.App.Pck;

public partial class PckManager : Node
{
	private static readonly List<string> Pck = [];

	private static string[] GetSubDirectories(string path)
	{
		try
		{
			return Directory.GetDirectories(path);
		}
		catch (System.Exception)
		{
			KernelInterface.StandardOutputBuilder.Append($"[color=red]{path}: No such path.[/color]\n");
			return null;
		}
	}

	private static void Mount(string path)
	{
		if (!ProjectSettings.LoadResourcePack(path))
		{
			KernelInterface.StandardOutputBuilder.Append($"[color=red]E: Unable to load {path}.[/color]\n");
		}
	}

	public static void LoadPck(string path)
	{
		Pck.Append(path);
	}

	public static void UnloadPck(string path)
	{
		Pck.Remove(path);
	}

	public static void LoadFolder(string folder)
	{
		KernelInterface.StandardOutputBuilder.Append($"Scanning {folder}...\n");
		string[] directories = GetSubDirectories(folder);

		if (directories == null) return;

		foreach (var item in directories)
		{
			if (item.EndsWith(".zip") || item.EndsWith(".pck"))
			{
				KernelInterface.StandardOutputBuilder.Append($"Mounting {item}...\n");
				Mount(item);
			}
		}
	}

	public static string GetList(string delimiter = "\n")
	{
		string str = "";
		string[] ls = [.. Pck];

		foreach (var item in ls)
		{
			str += item + delimiter;
			KernelInterface.StandardOutputBuilder.Append(item + delimiter);
			GD.Print(item);
		}

		return str;
	}
}

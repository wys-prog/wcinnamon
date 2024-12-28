
using Godot;
using System;
using System.IO;
using System.Linq;
using System.Collections.Generic;
using LibGit2Sharp;

namespace Wcinnamon.BuiltIn.App;

public partial class Pkg : Node
{
	private string[] Files = [];
	private RichTextLabel output;

	private class DoubleString(string a, string b)
	{
		public string First = a, Second = b;
	}

	private class PkgObj
	{
		public List<DoubleString> Links { get; set; } = [];
		public List<DoubleString> PkgLinks { get; set; } = [];
		public string Name { get; set; }
	}

	private void Compile(string line, PkgObj obj)
	{
		line = line.Trim();

		if (line.StartsWith("link:"))
		{
			var parts = line.Substring(5).Split(':', 2); // 5 pour "link:"
			if (parts.Length == 2)
			{
				obj.Links.Add(new DoubleString(parts[0].Trim(), parts[1].Trim()));
			}
		}
		else if (line.StartsWith("pkg:"))
		{
			var parts = line.Substring(4).Split(':', 2); // 4 pour "pkg:"
			if (parts.Length == 2)
			{
				obj.PkgLinks.Add(new DoubleString(parts[0].Trim(), parts[1].Trim()));
			}
		}
		else if (line.StartsWith("name:"))
		{
			obj.Name = line.Substring(5).Trim(); // 5 pour "name:"
		}
	}

	private void CompileFile(Godot.FileAccess file, PkgObj obj)
	{
		ulong len = file.GetLength();
		ulong i = 0;

		while (i < len)
		{
			string line = file.GetLine();
			Compile(line, obj);
			i += (ulong)line.Length;
		}
	}

	private void InstallLink(string path, string link)
	{
		if (!Directory.Exists(path))
			Directory.CreateDirectory(path);

		if (!Directory.GetDirectories(path).IsEmpty())
			Directory.Delete($"{path}/", true);

		output.Text += $"[color=blue]I: Installing {link}...[/color]\n";

		try
		{
			Repository.Clone(link, path);
		}
		catch (Exception e)
		{
			output.Text += $"[color=red]E: C# Exception\n{e}[/color]\n";
			System.Threading.Thread.Sleep(1250);
		}
	}

	private void Execute(string path, PkgObj obj)
	{
		if (!Directory.Exists($"{OS.GetUserDataDir()}/packages/{path}"))
			Directory.CreateDirectory($"{OS.GetUserDataDir()}/packages/{path}");

		foreach (var item in obj.Links)
		{
			InstallLink(item.First, item.Second);
		}

		foreach (var item in obj.PkgLinks)
		{
			Directory.CreateDirectory(item.First);
			Install(item.Second);
		}
	}

	public override void _Ready()
	{
		output = GetNode<RichTextLabel>("Window/RichTextLabel");
	}

	public void Install(string path)
	{
		PkgObj obj = new();

		output.Text += $"[color=blue]I: Compiling {path}...[/color]\n";

		var file = Godot.FileAccess.Open(path, Godot.FileAccess.ModeFlags.Read);

		CompileFile(file, obj);

		output.Text += $"[color=green]S: Package {path} compiled.[/color]\n" +
									 $"[color=blue]I: Executing {path}...[/color]\n";

		Execute(path, obj);
	}

	private void _on_install_button_down()
	{
		foreach (var item in Files)
		{
			try
			{
				Install(item);
			}
			catch (Exception e)
			{
				output.Text += $"[color=red]E: C# Exception\n{e}[/color]\n";
			}
		}
	}

	private void _on_window_close_requested()
	{
		output.Text += "[color=blue]I: Exiting...[/color]\n";
		QueueFree();
	}

	private void AppendFile(string file)
	{
		GD.Print($"Added file: {file}");
		Files = [.. Files, file];
	}
}

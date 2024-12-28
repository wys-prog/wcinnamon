using Godot;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace Wcinnamon.Source;

public partial class Kernel : Node
{
	private RichTextLabel StdOut;

	private static List<string> Parse(string line)
	{
		var args = new List<string>();
		var currentArg = string.Empty;
		var inQuotes = false;

		foreach (var ch in line)
		{
			if (ch == '"')
			{
				inQuotes = !inQuotes;
			}
			else if (ch == ' ' && !inQuotes)
			{
				if (!string.IsNullOrEmpty(currentArg))
				{
					args.Add(currentArg);
					currentArg = string.Empty;
				}
			}
			else
			{
				currentArg += ch;
			}
		}

		if (!string.IsNullOrEmpty(currentArg))
		{
			args.Add(currentArg);
		}

		return args;
	}

	private static string GetName(int length = 4)
	{
		const string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
		Random random = new();
		char[] result = new char[length];

		for (int i = 0; i < length; i++)
		{
			result[i] = chars[random.Next(chars.Length)];
		}

		return new string(result);
	}

	private static string[] PrependArg(string[] argv, string newArg)
	{
		string[] updatedArgv = new string[argv.Length + 1];

		updatedArgv[0] = newArg;

		Array.Copy(argv, 0, updatedArgv, 1, argv.Length);

		return updatedArgv;
	}

	private readonly Dictionary<string, Node> Processes = [];

	public string LoadLocal(string path)
	{
		var script = GD.Load<Script>($"res://built-in/app/{path}");

		if (script == null) return "exe@error";

		var node = new Node() { Name = $"local@{path}" };
		node.SetScript(script);

		string id = $"exe@{path}.{GetName()}";

		Processes[id] = node;

		return id;
	}

	// Public methods  

	public void LoadSystemModule(string path, string[] argv)
	{
		Node node = new() { Name = $"sys@{path}" };
		var script = GD.Load<Script>(path);

		if (script == null) { StdOut.Text += $"[color=red]System error: Cannot load « {path} »\n[/color]"; return; }

		node.SetScript(script);
		AddChild(node);
		Processes[$"sys@{path}.{GetName()}"] = node;
		node.Call("main", argv);
	}

	public void LoadProgram(string path, string[] argv)
	{
		string id = LoadLocal(path);
		Node node = Processes[id];

		if (id == "exe@error")
		{
			StdOut.Text += "[color=red]Cannot load program or script (null pointing reference)[/color]\n";
			return;
		}
		else if (!node.HasMethod("main"))
		{
			StdOut.Text += $"[color=red]Cannot found « main » method in module « {path} »[/color]\n";
			return;
		}

		AddChild(node);
		node.Call("main", argv);
	}

	public void Load(string command)
	{
		if (string.IsNullOrWhiteSpace(command))
			return;

		// Utilisation de Parse pour gérer les arguments avec guillemets
		var parsedArgs = Parse(command);

		if (parsedArgs.Count == 0)
			return;

		// Le premier argument est le chemin du script
		string path = parsedArgs[0];
		string[] argv = parsedArgs.Skip(1).ToArray();

		// Ajout de l'extension .gd si nécessaire
		path = path.EndsWith(".gd") ? path : path + ".gd";

		// Appel de la méthode LoadProgram avec les arguments
		LoadProgram(path, argv);
	}

	public override void _Ready()
	{
		// KernelLoader.InitKernel();

		Node node = new() { Name = "exe@errorHandler" };
		node.SetScript(GD.Load<Script>("res://built-in/app/error.gd"));
		Processes["exe@error"] = node;

	}

	public void ConnectOutput(RichTextLabel label)
	{
		StdOut = label;
	}

	/// Public and static references

	public static readonly string AppGetPath = Path.GetFullPath($"{OS.GetUserDataDir()}/apps/");
}

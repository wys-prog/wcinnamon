using Godot;
using System;
using System.IO;
using Wcinnamon.Source;

namespace Wcinnamon.BuiltIn.App.NotePad;

public partial class Note : TextEdit
{
	private string sourceFile;

	private void HandleFile(StreamReader reader)
	{
		while (!reader.EndOfStream)
		{
			long info = reader.BaseStream.Position * (reader.BaseStream.Length / 100);
			GD.Print(info, '\r');
			Text += reader.ReadLine() + '\n';
		}

		reader.Close();
	}

	public void Open(string path)
	{
		try
		{
			StreamReader reader = new(path);
			HandleFile(reader);
			sourceFile = path;
		}
		catch (Exception)
		{
			KernelInterface.StandardOutputBuilder.Append($"[color=red]E: {path}: No such file.[/color]\n");
		}
	}

	public void Save()
	{
		if (sourceFile != "")
		{
			StreamWriter writer = new(sourceFile);
			writer.Write(Text);
			writer.Close();
		}
	}

	public void Exit()
	{
		Save();
		QueueFree();
	}

	public override void _Input(InputEvent @event)
	{
		if (Input.IsActionPressed("exit")) Exit();
		if (Input.IsActionPressed("save")) Save();
	}
}

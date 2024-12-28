using Godot;
using System.IO;

namespace Wcinnamon.BuiltIn.App.NotePad;

public partial class Notepad : Control
{
	private Window window;
	private TabContainer tabContainer;
	private FileDialog fileDialog;

	public override void _Ready()
	{
		window = GetNode<Window>("Window");
		tabContainer = GetNode<TabContainer>("Window/Container");
		fileDialog = GetNode<FileDialog>("Window/FileDialog");
	}

	public override void _Process(double delta)
	{
		if (Input.IsActionPressed("open"))
		{
			fileDialog.Visible = true;
		}
	}

	public void Open(string file)
	{
		Note note = new(){Name=Path.GetFileNameWithoutExtension(file)};
		note.Open(file);
		tabContainer.AddChild(note);
	}

	private void OnFilesSelected(string[] files)
	{
		foreach (var item in files)
		{
			Open(item);
		}
	}

	private void OnWindowCloseRequested()
	{
		QueueFree();
	}

	private void OnWindowInput(InputEvent @event)
	{
		tabContainer.Size = window.Size;
	}
}

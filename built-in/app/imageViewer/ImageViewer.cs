using Godot;

namespace Wcinnamon.BuiltIn.App.ImageViewer;

public partial class ImageViewer : Control
{
	private static string GetImageType(string filePath)
	{
		FileAccess file = FileAccess.Open(filePath, FileAccess.ModeFlags.Read);
		byte[] header = file.GetBuffer(12);
		file.Close();

		if (header.Length >= 8 &&
				header[0] == 0x89 && header[1] == 0x50 && header[2] == 0x4E && header[3] == 0x47) // PNG
			return "PNG";
		if (header.Length >= 3 &&
				header[0] == 0xFF && header[1] == 0xD8 && header[2] == 0xFF) // JPEG
			return "JPEG";
		if (header.Length >= 4 &&
				header[0] == 0x42 && header[1] == 0x4D) // BMP
			return "BMP";
		if (header.Length >= 8 &&
				header[0] == 0xAB && header[1] == 0x4B && header[2] == 0x54 && header[3] == 0x58 &&
				header[4] == 0x20 && header[5] == 0x31 && header[6] == 0x31 && header[7] == 0xBB) // KTX
			return "KTX";
		if (header.Length >= 12 &&
				header[0] == 0x52 && header[1] == 0x49 && header[2] == 0x46 && header[3] == 0x46 &&
				header[8] == 0x57 && header[9] == 0x45 && header[10] == 0x42 && header[11] == 0x50) // WebP
			return "WebP";

		return "Unknown";
	}

	private Window win;
	private TabContainer container;
	private FileDialog fileDialog;

	private static Image CreateImage(string type, byte[] bytes)
	{
		Image image = new();

		if (type == "PNG") image.LoadPngFromBuffer(bytes);
		else if (type == "JPEG") image.LoadJpgFromBuffer(bytes);
		else if (type == "RIFF") image.LoadWebpFromBuffer(bytes);
		else if (type == "KTX") image.LoadKtxFromBuffer(bytes);
		else if (type == "BMP") image.LoadBmpFromBuffer(bytes);
		else image.LoadSvgFromBuffer(bytes); // « force » rendering of an image.
																				 // And if it's not an SVG image.. Idk .. 

		return new();
	}

	private void Open(string path)
	{
		var file = FileAccess.Open(path, FileAccess.ModeFlags.Read);

		if (file == null) return;

		byte[] bytes = file.GetBuffer((long)file.GetLength());

		file.Close();

		string type = GetImageType(path);

		Image image = CreateImage(type, bytes);
		Control node = new() { Name = System.IO.Path.GetFileName(path) };
		TextureRect rect = new();

		container.AddChild(node);
		node.AddChild(rect);

		ImageTexture texture = new();
		texture.SetImage(image);
		rect.Texture = texture;
	}

	private void OnInput(InputEvent @event)
	{
		container.Size = win.Size;

		int max = container.GetTabCount();

		for (int i = 0; i < max; i++)
		{
			container.GetTabControl(i).Size = win.Size;
		}
	}

	private void OnWindowCloseRequested()
	{
		QueueFree();
	}

	private void OnFileDialogFilesSelected(string[] files)
	{
		foreach (var item in files)
		{
			Open(item);
		}
	}

	public override void _Ready()
	{
		win = GetNode<Window>("Window");
		container = GetNode<TabContainer>("Window/TabContainer");
		fileDialog = GetNode<FileDialog>("Window/FileDialog");
	}

	public override void _Process(double delta)
	{
		if (Input.IsActionPressed("open"))
		{
			fileDialog.Visible = true;
		}
	}

}

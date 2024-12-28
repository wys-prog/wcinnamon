using Godot;
using System.Text;
using System.Collections.Generic;
using Wcinnamon.BuiltIn.App.Pck;

namespace Wcinnamon.Source;

public partial class KernelInterface : Node
{
	private Kernel kernel;
	private static readonly Dictionary<string, string> KeyTable = [];
	private bool isLockMaj = false;
	private bool canUserWrite = false;
	private RichTextLabel StandardOutput;
	private Callable[] NextCallables;
	public PckManager pckManager = new() { Name = "system@pckmanager" };
	public bool waitingUserInput = false;
	public static bool AskClearStdOut = false;
	public static StringBuilder StandardOutputBuilder = new();

	private static void InitKeyTable()
	{
		KeyTable["comma"] = ",";
		KeyTable["space"] = " ";
		KeyTable["enter"] = "\n";
		KeyTable["colon"] = ":";
		KeyTable["semicolon"] = ";";
		KeyTable["tab"] = "  ";
		KeyTable["exclam"] = "!";
		KeyTable["parenleft"] = "(";
		KeyTable["parenright"] = ")";
		KeyTable["ampersand"] = "&";
		KeyTable["kp period"] = ".";
		KeyTable["kp divide"] = "/";
		KeyTable["kp subtract"] = "-";
		KeyTable["kp add"] = "+";
		KeyTable["kp multiply"] = "*";
		KeyTable["kp 0"] = "0";
		KeyTable["kp 1"] = "1";
		KeyTable["kp 2"] = "2";
		KeyTable["kp 3"] = "3";
		KeyTable["kp 4"] = "4";
		KeyTable["kp 5"] = "5";
		KeyTable["kp 6"] = "6";
		KeyTable["kp 7"] = "7";
		KeyTable["kp 8"] = "8";
		KeyTable["kp 9"] = "9";
		KeyTable["quotedbl"] = "\"";
		KeyTable["apostrophe"] = "'";
		KeyTable["less"] = ">";
		KeyTable["bracketleft"] = "[";
		KeyTable["bracketright"] = "]";
		KeyTable["braceleft"] = "{";
		KeyTable["braceright"] = "}";
		KeyTable["alt"] = "";
		KeyTable["equal"] = "=";
		KeyTable["at"] = "@";
		Languages.ComplexKeyBoard.Create(KeyTable);
	}

	private void InitStdOut()
	{
		StandardOutput = GetNode<RichTextLabel>("OutputStream");
	}

	private void UpdateSystem()
	{
		Write("Updating System...");
	}

	private void InitKernel()
	{
		KernelLoader.InitKernel();

		UpdateSystem();

		Write("System started...\n");
		Write("Creating an instance of the kernel (@Kernel)...\n");

		kernel = new() { Name = "@Kernel" };
		AddChild(kernel);
		Write("Added kernel (@Kernel): ");
		Write(kernel);
		Write("Creating a connection with « StdOut » module...\n");
		kernel.ConnectOutput(StandardOutput);
		AddChild(pckManager);
	}

	private void Write(Variant args, bool endl = true)
	{
		string str = args.As<string>();

		StandardOutput.Text += str + ((str.EndsWith('\n') && endl) ? "" : '\n');
	}

	private void AfterReady()
	{
		Write("Scanning usr://...");

		string[] folders = System.IO.Directory.GetDirectories(OS.GetUserDataDir());

		foreach (var item in folders)
		{
			Write(item);
		}

		PckManager.LoadFolder($"{OS.GetUserDataDir()}/apps/");

	}

	private void Wakeup()
	{
		Write("Wcinnamon -- wOS 1.0.0 --\nSimple Input/Ouput commands (built-ins). Type 'help' for help.");
		AfterReady();
	}

	public override void _Ready()
	{
		InitStdOut();
		InitKernel();
		InitKeyTable();
		canUserWrite = true;
		NextCallables = [new(this, nameof(Wakeup))];
	}

	public override void _Process(double delta)
	{
		StandardOutput.Text += StandardOutputBuilder.ToString();
		// Clear StdOut's buffer.
		StandardOutputBuilder = new();

		if (AskClearStdOut)
		{
			StandardOutput.Text = "";
			AskClearStdOut = false;
		}

		foreach (var callable in NextCallables)
		{
			callable.Call();
		}

		NextCallables = [];
	}

	public override void _Input(InputEvent @event)
	{
		if (!canUserWrite) return;

		if (@event is InputEventKey keyEvent && keyEvent.Pressed)
		{
			if (keyEvent.Keycode == Key.Enter && keyEvent.CtrlPressed)
			{
				string[] lines = StandardOutput.Text.Split('\n');

				string lastLine = "";
				for (int i = lines.Length - 1; i >= 0; i--)
				{
					if (!string.IsNullOrWhiteSpace(lines[i]))
					{
						lastLine = lines[i];
						break;
					}
				}

				Write("\n"); // Write the line after getting previous lines
				if (waitingUserInput) waitingUserInput = false;

				kernel.Load(lastLine);
				return;
			}

			if (keyEvent.Keycode == Key.Capslock)
			{
				isLockMaj = !isLockMaj;
				return;
			}

			if (KeyTable.ContainsKey(keyEvent.AsText().ToLower()))
			{
				StandardOutput.Text += KeyTable[keyEvent.AsText().ToLower()];

				return;
			}

			if (keyEvent.Keycode == Key.Backspace && StandardOutput.Text.Length > 0)
			{
				StandardOutput.Text = StandardOutput.Text.Remove(StandardOutput.Text.Length - 1);
				return;
			}

			if (keyEvent.Keycode == Key.Shift || keyEvent.Keycode == Key.Ctrl) return;

			if (!string.IsNullOrEmpty(keyEvent.AsText()))
			{
				string text = keyEvent.AsText();

				// Handling Shift cases 
				if (keyEvent.ShiftPressed)
				{
					text = text.ToUpper();
					int shiftIndex = text.IndexOf("SHIFT+");
					StandardOutput.Text += text.Substr(shiftIndex + "SHIFT+".Length, 1);
				}
				else if (!keyEvent.ShiftPressed)
				{
					StandardOutput.Text += isLockMaj ? text.ToUpper() : text.ToLower();
				}
			}
		}
	}

}


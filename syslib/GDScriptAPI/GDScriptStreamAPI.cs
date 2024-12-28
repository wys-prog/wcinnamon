using Godot;
using Wcinnamon.Source;

namespace Wcinnamon.Syslib.GDScriptAPI;

public partial class GDScriptStreamAPI : Node
{
	/// <summary>
	/// This function will write « str » to Wcinnamon.Source.KernelInterface.StanrdOutputBuilder
	/// </summary>
	/// <param name="str">System.String, string to write to Wcinnamon.Source.KernelInterface.StanrdOutputBuilder</param>
	
	public static void WriteStdout(string str)
	{
		KernelInterface.StandardOutputBuilder.Append(str);
	}

	public static void ClearStdOut()
	{
		KernelInterface.AskClearStdOut = true;
	}
}
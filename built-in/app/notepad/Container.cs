using Godot;

namespace Wcinnamon.BuiltIn.App.NotePad;

public partial class Container : TabContainer
{
	private void OnContainerResized()
	{
		int max = GetTabCount();
		for (int i = 0; i < max; i++)
		{
			GetTabControl(i).Size = Size;
		}
	}
}

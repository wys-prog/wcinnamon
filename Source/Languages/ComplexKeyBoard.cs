using System.Collections.Generic;
using Godot;

namespace Wcinnamon.Source.Languages;

public partial class ComplexKeyBoard : Node
{
  public static void Create(Dictionary<string, string> KeyTable)
  {
    string letters = "æ«€¶ŧ←↓→øþ@ßðđŋħˀĸłµł»¢„“”•·´";
    string keys = "azertyuioopqsdfghjklmwxcvbn,;:";

    for (int i = 0; i < letters.Length; i++)
    {
      KeyTable[$"alt+{keys[i]}"] = $"{letters[i]}";
    }
  }
}
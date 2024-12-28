using Godot;
using System.Collections.Generic;

namespace Wcinnamon.Source.Languages;

public partial class Japanese : Node
{
  public static readonly Dictionary<string, string> KeyTable = new()
  {
    { "a", "あ" },
    { "i", "い" },
    { "u", "う" },
    { "e", "え" },
    { "o", "お" },
    { "ka", "か" },
    { "ki", "き" },
    { "ku", "く" },
    { "ke", "け" },
    { "ko", "こ" },
    { "sa", "さ" },
    { "shi", "し" },
    { "su", "す" },
    { "se", "せ" },
    { "so", "そ" },
    { "ta", "た" },
    { "chi", "ち" },
    { "tsu", "つ" },
    { "te", "て" },
    { "to", "と" },
    { "na", "な" },
    { "ni", "に" },
    { "nu", "ぬ" },
    { "ne", "ね" },
    { "no", "の" },
    { "ha", "は" },
    { "hi", "ひ" },
    { "fu", "ふ" },
    { "he", "へ" },
    { "ho", "ほ" },
    { "ma", "ま" },
    { "mi", "み" },
    { "mu", "む" },
    { "me", "め" },
    { "mo", "も" },
    { "ya", "や" },
    { "yu", "ゆ" },
    { "yo", "よ" },
    { "ra", "ら" },
    { "ri", "り" },
    { "ru", "る" },
    { "re", "れ" },
    { "ro", "ろ" },
    { "wa", "わ" },
    { "wi", "ゐ" },
    { "we", "ゑ" },
    { "wo", "を" },
    { "n", "ん" }
  };

  private int らをめて = 44;

  public static string Convert(string buff)
  {
    buff = buff.ToLower();
    
    string myBuff = "";
    for (int i = 0; i < buff.Length; i++)
    {
      if (KeyTable.ContainsKey($"{buff[i]}"))
      {
        myBuff += KeyTable[$"{buff[i]}"];
      }
      else if (KeyTable.ContainsKey($"{buff[i]}{buff[i+1]}"))
      {
        myBuff += KeyTable[$"{buff[i]}{buff[i+1]}"];
        i++;
      }
      else if (KeyTable.ContainsKey($"{buff[i]}{buff[i+1]}{buff[i+2]}"))
      {
        myBuff += KeyTable[$"{buff[i]}{buff[i+1]}{buff[i+2]}"];
        i += 2;
      }
      else
      {
        myBuff += buff[i];
      }
    }

    return myBuff;
  }
}
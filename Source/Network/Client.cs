using System.Net;
using System.Net.Sockets;
using Godot;

namespace Wcinnamon.Source.Network;

public partial class Client : Node
{
  private TcpClient client;
  private NetworkStream stream;
  public bool AskForClosing = false;

  public async void Start(IPEndPoint iPEndPoint)
  {
    client = new();
    await client.ConnectAsync(iPEndPoint);
    stream = client.GetStream();

    while (AskForClosing)
    {
      byte[] buffer = new byte[client.ReceiveBufferSize];
      await stream.ReadAsync(buffer, 0, buffer.Length);
    }

    Close();
  }

  public void Close()
  {
    client.Close();
  }
}
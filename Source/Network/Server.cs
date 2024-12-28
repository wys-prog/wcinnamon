using System.Net;
using System.Net.Sockets;
using Godot;

namespace Wcinnamon.Source.Network;

public partial class Server : Node
{
	private IPEndPoint iPEndPoint;
  private TcpListener listener;

  public bool AskForClosing = false;

  public async void Start()
  {
    listener = new(IPAddress.Any, 5000);
    listener.Start();

    while (!AskForClosing)
    {
      using TcpClient client = await listener.AcceptTcpClientAsync();
      using NetworkStream stream = client.GetStream();
      byte[] buffer = new byte[1024];
      int bytesRead = await stream.ReadAsync(buffer, 0, buffer.Length);
      
    }
  }

  public void Close()
  {
    listener.Stop();
  }
}

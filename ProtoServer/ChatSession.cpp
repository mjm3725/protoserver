#include "stdafx.h"
#include "ChatSession.h"
#include "Network/TCPServer.h"

void ChatSession::OnConnect()
{
	cout << "connected : " << socket_->remote_endpoint().address().to_string() << endl;
}

void ChatSession::OnDisconnect()
{
	cout << "disconnected : " << socket_->remote_endpoint().address().to_string() << endl;
}

int ChatSession::OnRecv(asio::const_buffer& buf)
{
	const char* data = asio::buffer_cast<const char*>(buf);
	size_t size = asio::buffer_size(buf);

	for (int i = 0; i < size; i++)
	{
		if (data[i] == '\0')
		{
			string s(data, i + 1);

			cout << "chat: " << s << endl;

			server_->VisitSession([&s](auto session)
			{
				session->Send(s.data(), static_cast<int>(s.length()));
			});

			return i + 1;
		}
	}

	return 0;
}
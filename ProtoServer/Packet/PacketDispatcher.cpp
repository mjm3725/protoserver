#include "stdafx.h"
#include "PacketDispatcher.h"
#include "Protocol\Protocol.pb.h"
#include "CmdReqLogin.h"


void PacketDispatcher::Initialize()
{
	AddHandler<PacketCommand::REQ_LOGIN, CmdReqLogin>();
}

void PacketDispatcher::Dispatch(shared_ptr<ISession>& session, asio::const_buffer & buf, int packetLen)
{
	const char* data = asio::buffer_cast<const char*>(buf);

	__int16 cmd = *(__int16*)data;


	auto v = _handlerMap.find(cmd);

	if (v == _handlerMap.end())
	{
		LogHelper::GetInstance()->GetConsoleLogger()->error("Invalid handler : cmd {}", cmd);
		return;
	}

	v->second->ExecuteCommand(session, buf, packetLen);
}

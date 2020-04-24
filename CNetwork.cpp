// CNetwork.cpp
// Winsock Wrapper Class
// Kevin Griffin - 2002
//
/*
	HOW TO USE CNETWORK
	-------------------

	To declare a new networking object:
		
		CNetwork netHost; // declares a network (no debug)
		CNetwork netHost(true); // declares a network with debug

		If you are running a host computer, you must declare two
		network objects.  The second network holds information about
		a the client computer.  Creating a CNetwork vector/array will
		allow for multiple clients.  Client computers require only one
		network object.

	Running a host computer:
	
		1) Declare new CNetwork.
		2) Bind to port using CNetwork::Bind
		3) Listen to port using CNetwork::Listen
		4) Accept new connection using CNetwork::Accept

	Running a client computer:

		1) Declare new CNetwork
		2) Bind to port using CNetwork::Bind
		3) Connect to host using CNetwork::Connect
*/

#include "cnetwork.h"

CNetwork::CNetwork()
{
	int err = WSAStartup(0x202, &wsdata);
	
	if (err != 0)
	{
		ProcessError(err);
		init = false;
	}
	else
		init = true;

	debug = false;
}

CNetwork::CNetwork(bool setDebug)
{
	debug = setDebug;

	int err;

	err = WSAStartup(0x202, &wsdata);
	
	if (err != 0)
	{
		ProcessError(err);
		init = false;
	}
	else
		init = true;
}

CNetwork::~CNetwork()
{
	closesocket(socketInfo);
	WSACleanup();
}


CNetwork::ProcessError(int code)
{
	string errMsg;

	switch(code)
	{
	case WSAEINTR:
		errMsg = "Interrupted function call."; break;
	case WSAEACCES:
		errMsg = "Permission denied.";break;
	case WSAEFAULT:
		errMsg = "Bad address.";break;
	case WSAEMFILE:
		errMsg = "Too many open files.";break;
	case WSAEWOULDBLOCK:
		errMsg = "Resource temporarily unavaliable.";break;
	case WSAEINPROGRESS:
		errMsg = "Operation now in progress.";break;
	case WSAEALREADY:
		errMsg = "Operation already in progress.";break;
	case WSAENOTSOCK:
		errMsg = "Socket operation on nonsocket.";break;
	case WSAEDESTADDRREQ:
		errMsg = "Destination address required.";break;
	case WSAEMSGSIZE:
		errMsg = "Message too long.";break;
	case WSAEPROTOTYPE:
		errMsg = "Protocol wrong type for socket.";break;
	case WSAENOPROTOOPT:
		errMsg = "Bad protocol option.";break;
	case WSAEPROTONOSUPPORT:
		errMsg = "Protocol not supported.";break;
	case WSAESOCKTNOSUPPORT:
		errMsg = "Socket type not supported.";break;
	case WSAEOPNOTSUPP:
		errMsg = "Operation not supported.";break;
	case WSAEPFNOSUPPORT:
		errMsg = "Protocol family not supported.";break;
	case WSAEAFNOSUPPORT:
		errMsg = "Address family not supported by protocol family.";break;
	case WSAEADDRINUSE:
		errMsg = "Address already in use.";break;
	case WSAEADDRNOTAVAIL:
		errMsg = "Cannot assign requested address.";break;
	case WSAENETDOWN:
		errMsg = "Network is down.";break;
	case WSAENETUNREACH:
		errMsg = "Network is unreachable.";break;
	case WSAENETRESET:
		errMsg = "Network dropped connection on reset.";break;
	case WSAECONNABORTED:
		errMsg = "Software caused connection abort.";break;
	case WSAECONNRESET:
		errMsg = "Connection reset by peer.";break;
	case WSAENOBUFS:
		errMsg = "No buffer space availiable.";break;
	case WSAEISCONN:
		errMsg = "Socket is already connected.";break;
	case WSAENOTCONN:
		errMsg = "Socket is not connected.";break;
	case WSAESHUTDOWN:
		errMsg = "Cannot send after socket shutdown.";break;
	case WSAETIMEDOUT:
		errMsg = "Connection timed out.";break;
	case WSAECONNREFUSED:
		errMsg = "Connection refused.";break;
	case WSAEHOSTDOWN:
		errMsg = "Host is down.";break;
	case WSAEHOSTUNREACH:
		errMsg = "No route to host.";break;
	case WSAEPROCLIM:
		errMsg = "Too many processes.";break;
	case WSASYSNOTREADY:
		errMsg = "Network subsystem is unavailable.";break;
	case WSAVERNOTSUPPORTED:
		errMsg = "Winsock.dll version out of range.";break;
	case WSANOTINITIALISED:
		errMsg = "Successful WSAStartup not yet performed.";break;
	case WSAEDISCON:
		errMsg = "Graceful shutdown in progress.";break;
	case WSATYPE_NOT_FOUND:
		errMsg = "Class type not found.";break;
	case WSAHOST_NOT_FOUND:
		errMsg = "Host not found.";break;
	case WSATRY_AGAIN:
		errMsg = "Nonauthoritative host not found.";break;
	case WSANO_RECOVERY:
		errMsg = "This is a nonrecoverable error.";break;
	case WSAEINVAL:
		errMsg = "Invalid Argument";break;
	case WSANO_DATA:
		errMsg = "Valid name, no data record of requested type.";break;
	case WSA_INVALID_HANDLE:
		errMsg = "Specified event object handle is invalid.";break;
	case WSA_INVALID_PARAMETER:
		errMsg = "One or more parameters are invalid.";break;
	case WSA_IO_INCOMPLETE:
		errMsg = "Overlapped I//O event object not in signaled state.";break;
	case WSA_IO_PENDING:
		errMsg = "Overlapped operations will complete later.";break;
	case WSA_NOT_ENOUGH_MEMORY:
		errMsg = "Insufficient memory available.";break;
	case WSA_OPERATION_ABORTED:
		errMsg = "Overlapped operation aborted.";break;
	case WSASYSCALLFAILURE:
		errMsg = "System call failure.";break;
	default:
		errMsg = "Unknown error occured.";break;
	}

	MessageBox(NULL, errMsg.c_str(), "Winsock Error", MB_OK | MB_ICONINFORMATION);

	return 0;
}

int CNetwork::ProcessError(string error)
{
	MessageBox(NULL, error.c_str(), "Winsock Error", MB_OK | MB_ICONINFORMATION);

	return 0;
}

int CNetwork::Bind(int port)
{
	sockaddr_in serverAdd;

	socketInfo = socket(AF_INET, SOCK_STREAM, 0);
	if (socketInfo == INVALID_SOCKET)
	{
		if (debug == true)
			ProcessError(WSAGetLastError());
		return 1;
	}

	memset(&serverAdd, 0, sizeof(sockaddr_in));
	serverAdd.sin_family = AF_INET;
	serverAdd.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAdd.sin_port = htons(port);

	if (bind(socketInfo, (sockaddr*)&serverAdd, sizeof(sockaddr)) == SOCKET_ERROR)
	{
		if (debug == true)
			ProcessError(WSAGetLastError());
		return 1;
	}
	else
		return 0;

	return 0;
}

int CNetwork::Listen()
{
	if (listen(socketInfo, 1) == SOCKET_ERROR)
	{
		if (debug == true)
			ProcessError(WSAGetLastError());
		return 1;
	}
	else
	{
		host = true;
		return 0;
	}
}

int CNetwork::Accept(CNetwork &acceptSocket)
{
	sockaddr_in		client;
	int				clientSize = sizeof(sockaddr_in);

	acceptSocket.socketInfo = accept(socketInfo, (sockaddr*)&client, &clientSize);

	if (acceptSocket.socketInfo	== INVALID_SOCKET)
	{
		if (debug == true)
			ProcessError(WSAGetLastError());
		return 1;
	}
	else
		return 0;
}

int CNetwork::Connect(const char *serverAdd, int port)
{
	sockaddr_in		server;
	LPHOSTENT		host;
	int				err;

	socketInfo = socket(AF_INET, SOCK_STREAM, 0);

	if (socketInfo == INVALID_SOCKET)
	{
		if (debug == true)
			ProcessError(WSAGetLastError());
		return 1;
	}

	memset(&server, 0, sizeof(sockaddr_in));
	server.sin_family	= AF_INET;
	server.sin_port		= htons(port);
	server.sin_addr.s_addr = inet_addr(serverAdd);

	if (server.sin_addr.s_addr == INADDR_NONE)
	{
		host = gethostbyname(serverAdd);
		if (host != NULL)
		{
			server.sin_addr.s_addr = ((LPIN_ADDR)host->h_addr)->s_addr;
		}
		else
			return 1;
	}

	err = connect(socketInfo, (sockaddr*)&server, sizeof(server));

	if (err == SOCKET_ERROR)
	{
		if (debug == true)
			ProcessError(WSAGetLastError());
		return 1;
	}
	else
	{
		host = false;
		return 0;
	}
}

int CNetwork::Send(CNetwork &client, void *buffer, int bufLen)
{
	
	if (send(client.socketInfo, (char *)buffer, bufLen, NULL) == SOCKET_ERROR)
	{
		if (debug == true)
			ProcessError(WSAGetLastError());
		return 1;
	}
	else
		return 0;

}

int CNetwork::Receive(CNetwork &client, void *buffer, int bufLen)
{

	if (recv(client.socketInfo, (char *)buffer, bufLen, NULL) == SOCKET_ERROR)
	{
		if (debug == true)
			ProcessError(WSAGetLastError());
		return 1;
	}
	else
	{

		return 0;
	}
}

int CNetwork::Send(void *buffer, int bufLen)
{

	if (send(socketInfo, (char *)buffer, bufLen, NULL) == SOCKET_ERROR)
	{
		if (debug == true)
			ProcessError(WSAGetLastError());
		return 1;
	}
	else
		return 0;
	
}

int CNetwork::Receive(void *buffer, int bufLen)
{

	
	if (recv(socketInfo, (char *)buffer, bufLen, NULL) == SOCKET_ERROR)
	{
		if (debug == true)
			ProcessError(WSAGetLastError());
		return 1;
	}
	else
	{
		return 0;
	}
	
}












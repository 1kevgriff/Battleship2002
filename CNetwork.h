// CNetwork.h
// Winsock Wrapper Class
// Kevin Griffin - 2002
#ifndef CNETWORK_H
#define CNETWORK_H
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <windows.h>
#include <string>

using namespace std;

class CNetwork
{
public:
	CNetwork();					// default constructor
	CNetwork(bool setDebug);	// overloaded constructor, sets debug mode
	~CNetwork();				// destructor
	int Accept(CNetwork &acceptSocket); // accepts new connections
	int Bind(int port);			// binds protocol to port (use first)
	int Connect(const char *serverAdd, int port); // connects to another computer
	int Listen();				// starts listening to open port
	int ProcessError(int code);	// processes error code
	int ProcessError(string error); // processes user error
	int Send(CNetwork &client, void *buffer, int bufLen); // sends information (Host)
	int Send(void *buffer, int bufLen); // sends information (Client)
	int Receive(CNetwork &client, void *buffer, int bufLen); // recieves information (Host)
	int Receive(void *buffer, int bufLen); // recieves information (Client)

	SOCKET			socketInfo;	// socket information

private:
	bool			debug;		// automatic debug information
	bool			init;		// is winsock ready to go?
	bool			host;		// is this host computer?

	WSADATA			wsdata;		// winsock information
};

#endif
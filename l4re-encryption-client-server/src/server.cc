/*
 * Author:                 Nikita Edward Baruzdin
 * Contact email:          nikita.edward.baruzdin@gmail.com
 * Creation date:          2013-07-21
 * Last modification date: 2013-07-22
 */


#include <iostream>
#include <cctype>
#include <l4/re/util/object_registry>
#include <l4/cxx/ipc_stream>
#include "shared.h"

using namespace std;
using namespace L4;
using namespace L4Re;


//======================================================================
struct ROTN_Server : Server_object
{
	int dispatch(l4_umword_t, Ipc::Iostream &ios);
	void rotate(char *message, unsigned long message_length, int n);
};

//----------------------------------------------------------------------
int ROTN_Server::dispatch(l4_umword_t, Ipc::Iostream &ios)
{
	l4_msgtag_t msgtag;
	ios >> msgtag;
	if (msgtag.label() != ::Protocol::Encryption)
		return -L4_EBADPROTO;

	L4::Opcode opcode;
	ios >> opcode;

	int n = 6;
	switch (opcode)
	{
		case Opcode::encrypt_func:
			cout << "Encryption..." << endl;
			break;
		case Opcode::decrypt_func:
			cout << "Decryption..." << endl;
			n = 26 - n;
			break;
		default:
			return -L4_ENOSYS;
	}

	unsigned long message_length = 0;
	char message[message_buf_length];

	ios >> Ipc::Buf_cp_in<char>(message, message_length);
	rotate(message, message_length, n);
	ios << message;

	return L4_EOK;
}

//----------------------------------------------------------------------
void ROTN_Server::rotate(char *message, unsigned long message_length,
                         int n)
{
	for (unsigned int i = 0; i < message_length - 1; i++)
	{
		if (message[i] >= 'A' && message[i] <= 'Z')
			message[i] = message[i] + n >= 'A' && message[i] + n <= 'Z'
			           ? message[i] + n
			           : message[i] + n - 26 ;
		if (message[i] >= 'a' && message[i] <= 'z')
			message[i] = message[i] + n >= 'a' && message[i] + n <= 'z'
			           ? message[i] + n
			           : message[i] + n - 26;
	}
}

//======================================================================
int main()
{
	ROTN_Server rotn;
	Util::Registry_server<> server;

	Cap<void> channel
	            = server.registry()->register_obj(&rotn, "channel_cap");
	if (!channel.is_valid())
	{
		cerr << "Couldn't register ROTN service, is there a "
		     << "'channel_cap' in the capabilities table?" << endl;
		return 1;
	}

	cout << "Encryption server started." << endl;
	server.loop();

	return 0;
}

/*
 * Author:                 Nikita Edward Baruzdin
 * Contact email:          nikita.edward.baruzdin@gmail.com
 * Creation date:          2013-07-21
 * Last modification date: 2013-07-22
 */


#include <iostream>
#include <cstring>
#include <l4/re/env>
#include <l4/cxx/ipc_stream>
#include "shared.h"

using namespace std;
using namespace L4;
using namespace L4Re;


//----------------------------------------------------------------------
int server_call(Cap<void> const &channel, L4::Opcode opcode,
                char* message)
{
	Ipc::Iostream ios(l4_utcb());
	cout << "Asking to ";
	switch (opcode)
	{
		case Opcode::encrypt_func:
			cout << "encrypt";
			break;
		case Opcode::decrypt_func:
			cout << "decrypt";
			break;
		default:
			cout << "do something unknown";
	}
	cout << ": \"" << message << "\"" << endl;
	ios << L4::Opcode(opcode);
	ios << message;
	l4_msgtag_t tag = ios.call(channel.cap(), ::Protocol::Encryption);
	if (l4_error(tag))
	{
		cerr << "Error calling server: " << l4_error(tag) << endl;
		return l4_error(tag);
	}
	unsigned long message_length = 0;
	ios >> Ipc::Buf_cp_in<char>(message, message_length);
	cout << "Response         : \"" << message << "\"" << endl;
	return 0;
}


//======================================================================
int main()
{
	Cap<void> channel = Env::env()->get_cap<void>("channel_cap");
	if (!channel.is_valid())
	{
		cerr << "Couldn't get channel capability." << endl;
		return 1;
	}

	char *message = new char [message_buf_length];
	strcpy(message, "Lorem ipsum");

	server_call(channel, Opcode::encrypt_func, message);
	server_call(channel, Opcode::decrypt_func, message);

	return 0;
}

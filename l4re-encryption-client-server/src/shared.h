/*
 * Author:                 Nikita Edward Baruzdin
 * Contact email:          nikita.edward.baruzdin@gmail.com
 * Creation date:          2013-07-21
 * Last modification date: 2013-07-22
 */


namespace Opcode
{
	enum Opcodes
	{
		encrypt_func,
		decrypt_func
	};
};

namespace Protocol
{
	enum Protocols
	{
		Encryption
	};
};

const int message_buf_length = 30;

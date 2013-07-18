/*
 * Author                : Nikita Edward Baruzdin
 * Contact email         : nikita.edward.baruzdin@gmail.com
 * Creation date         : 2013-07-16
 * Last modification date: 2013-07-18
 *
 * The program gives an example of a system call invocation in L4Re.
 */


#include <stdio.h>
#include <string.h>

#include <l4/re/env.h>
#include <l4/sys/ipc.h>
#include <l4/sys/vcon.h>


int main(void)
{
	l4re_env_t *env = l4re_env();       // get environment
	l4_msg_regs_t *mr = l4_utcb_mr();   // get msg regs

	char *str = "Hello, world!\n";
	const int str_length = 15;

	mr->mr[0] = L4_VCON_WRITE_OP;
	mr->mr[1] = str_length;
	memcpy(&mr->mr[2], "Hello, world!\n", str_length);

	l4_msgtag_t tag, ret;

	tag = l4_msgtag(L4_PROTO_LOG,   // long     label (protocol)
	                6,              // unsigned words
	                0,              // unsigned items
	                0);             // unsigned flags

	ret = l4_ipc_send(env->log,                 // l4_cap_idx_t dest
	                  l4_utcb(),                // l4_utcb_t   *utcb
	                  tag,                      // l4_msgtag_t  tag
	                  L4_IPC_SEND_TIMEOUT_0);   // l4_timeout_t timeout

	if (l4_msgtag_has_error(ret))
		fprintf(stderr, "Error in message tag.\n");
}


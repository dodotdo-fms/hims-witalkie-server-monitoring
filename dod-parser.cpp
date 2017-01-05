#include "main.h"

#include "net-header.h"

#include "signal-packet.h"
#include "audio-packet.h"


void _get_sigpack(stra& o, tcp_header& th, pcsa p, size_t n)
{
	sstream	r1;

	sigpacket_t*p2	= (sigpacket_t*)p;
	switch(p2->typ) {
	case sigpacket_t::ping_request:
		r1	<< "ping_request   id=" << p2->id;
		break;

	case sigpacket_t::ping_response:
		r1	<< "ping_response  id=" << p2->id;
		break;

	case sigpacket_t::login_request:
		r1	<< "login_request  id=" << p2->id;
		break;

	case sigpacket_t::login_response:
		r1	<< "login_response id=" << p2->id;
		break;

	case sigpacket_t::logout_request:
		r1	<< "logout_request id=" << p2->id;
		break;

	case sigpacket_t::push_to_talk:
		r1	<< "push_to_talk   id=" << p2->id;
		break;

	case sigpacket_t::pop_to_over:
		r1	<< "push_to_talk   id=" << p2->id;
		break;

	case sigpacket_t::join_channel:
		{
			signal_join_chn*p3	= (signal_join_chn*)p;
			r1	<< "join_channel   id=" << p2->id << ", ch=" << p3->chn;
		}
		break;

	case sigpacket_t::joind_channel:
		{
			signal_joind_chn*p3	= (signal_joind_chn*)p;
			r1	<< "joined_channel id=" << p2->id << ", ch=" << p3->chn << ", res=" << p3->res;
		}
		break;

	case sigpacket_t::begin_stream:
		{
			signal_begin_stm*p3	= (signal_begin_stm*)p;
			r1	<< "begin_stream   id=" << p2->id << ", ch=" << p3->chn << ", name=" << p3->name;
		}
		break;

	case sigpacket_t::finsh_stream:
		{
			signal_finsh_stm*p3	= (signal_finsh_stm*)p;
			r1	<< "finsh_stream   id=" << p2->id << ", ch=" << p3->chn;
		}
		break;

	default:
		if (th.syn)	r1	<< "SYN=1 ";
		if (th.rst)	r1	<< "RST=1 ";
		if (th.fin)	r1	<< "FIN=1 ";
		break;
	};

	if (n > 0)
		r1	<< " / len=" << n;
	o	= r1.str();
}
void _get_audpack(stra& o, udp_header& uh, pcsa p, size_t n)
{
	sstream	r1;

	audpacket_t*p2	= (audpacket_t*)p;
	switch(p2->typ) {
	case audpacket_t::connect:
		r1	<< "connect        id=" << p2->id;
		break;

	case audpacket_t::audio:
		{
			audio_audio*p2	= (audio_audio*)p;
			r1	<< "audio          id=" << p2->id << ", seq=" << p2->seq;
		}
		break;

	default:
		break;
	};

	if (n > 0)
		r1	<< " / len=" << n;
	o	= r1.str();
}

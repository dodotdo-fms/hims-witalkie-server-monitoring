#ifndef	__DODOTDO_SIGNAL_PACKET_H__
#define	__DODOTDO_SIGNAL_PACKET_H__


#pragma pack(push, 1)

struct	sigpacket_t
{
	enum TYPE_t : UINT8 {
		_null_			= 0,
		ping_request,
		ping_response,
		login_request,
		login_response,
		logout_request,
		push_to_talk,
		pop_to_over,
		join_channel,
		joind_channel,
		begin_stream,
		finsh_stream,
		_last_
	};

	TYPE_t	typ;
	UINT16	len;
	UID_	id		= -1;

	sigpacket_t(TYPE_t t, size_t n)
		: typ(t), len(n)
	{}
};
typedef	std::shared_ptr<sigpacket_t>	SIGPACK;


struct	signal_ping_req : sigpacket_t {
	signal_ping_req()
		: sigpacket_t(sigpacket_t::ping_request, sizeof(*this))
	{}
};
struct	signal_ping_res : sigpacket_t {
	signal_ping_res()
		: sigpacket_t(sigpacket_t::ping_response, sizeof(*this))
	{}
};
struct	signal_login_req : sigpacket_t {
	signal_login_req()
		: sigpacket_t(sigpacket_t::login_request, sizeof(*this))
	{}
};
struct	signal_login_res : sigpacket_t {
	signal_login_res()
		: sigpacket_t(sigpacket_t::login_response, sizeof(*this))
	{}
};
struct	signal_logout_req : sigpacket_t {
	signal_logout_req()
		: sigpacket_t(sigpacket_t::logout_request, sizeof(*this))
	{}
};
struct	signal_push2talk : sigpacket_t {
	signal_push2talk()
		: sigpacket_t(sigpacket_t::push_to_talk, sizeof(*this))
	{}
};
struct	signal_pop2over : sigpacket_t {
	signal_pop2over()
		: sigpacket_t(sigpacket_t::pop_to_over, sizeof(*this))
	{}
};
struct	signal_join_chn : sigpacket_t {

	CHN_	chn;

	signal_join_chn()
		: sigpacket_t(sigpacket_t::join_channel, sizeof(*this))
	{}
};
struct	signal_joind_chn : sigpacket_t {

	enum RESULT_t : UINT8 {
		success	= 0,
		fail
	};

	CHN_	chn;
	UINT8	res;

	signal_joind_chn()
		: sigpacket_t(sigpacket_t::joind_channel, sizeof(*this))
	{}
};
struct	signal_begin_stm : sigpacket_t {

	CHN_	chn;
	char	name[20];

	signal_begin_stm()
		: sigpacket_t(sigpacket_t::begin_stream, sizeof(*this))
	{
		name[0]	= 0;
	}
};
struct	signal_finsh_stm : sigpacket_t {

	CHN_	chn;

	signal_finsh_stm()
		: sigpacket_t(sigpacket_t::finsh_stream, sizeof(*this))
	{}
};

#pragma pack(pop)

#endif

#ifndef	__DODOTDO_AUDIO_PACKET_H__
#define	__DODOTDO_AUDIO_PACKET_H__


#pragma pack(push, 1)

struct	audpacket_t
{
	enum TYPE_t : UINT8 {
		_null_		= 0,
		connect,
		audio,
		_last_
	};

	UINT8	typ;
	UID_	id		= -1;

	audpacket_t(TYPE_t t)
		: typ(t)
	{}
};

struct	audio_connect : audpacket_t {
	audio_connect()
		: audpacket_t(audpacket_t::connect)
	{}
};
struct	audio_audio : audpacket_t {

	SEQ_	seq;

	audio_audio()
		: audpacket_t(audpacket_t::audio)
	{}
};

#pragma pack(pop)

#endif

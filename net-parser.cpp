#include "main.h"

#include "net-header.h"

#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>

extern u_short	tcpp;
extern u_short	udpp;
extern in_addr	host;

extern void _get_sigpack(stra&, tcp_header&, pcsa, size_t);
extern void _get_audpack(stra&, udp_header&, pcsa, size_t);

void _get_curtime(stra& t)
{
	tm*		tm;
	timeval	tv;
	char	buf[64];

	gettimeofday(&tv, NULL);
	tm	= localtime(&tv.tv_sec);
	sprintf(buf, "%02d:%02d:%02d.%06lu", tm->tm_hour, tm->tm_min, tm->tm_sec, tv.tv_usec);
	t	= buf;
}
int _get_ipstr(stra& src, stra& dst, eth_header* eh, ip_header* ih)
{
	int	fa	= AF_INET;
	switch(htons(eh->ether_type)) {
	case ETHERTYPE_IP:		fa	= AF_INET; break;
	case ETHERTYPE_IPV6:	fa	= AF_INET6; break;
	default:
		return	1;
	};

	char	tmp[INET6_ADDRSTRLEN];
	inet_ntop(fa, &ih->saddr, tmp, sizeof(tmp));	src	= tmp;
	inet_ntop(fa, &ih->daddr, tmp, sizeof(tmp));	dst	= tmp;
	return	0;
}

void _tcp_packet(eth_header* eh, ip_header* ih, tcp_header* th, u_char* pl, size_t len)
{
	int sid		= 1;
	int did		= 0;
	int spr		= th->dest;
	pcsa dir	= "<<";
	if (host.s_addr != ih->daddr)
	{
		sid	= 0;
		did	= 1;
		spr	= th->source;
		dir	= ">>";

		if (host.s_addr != ih->saddr)
			return;
	}

	if (spr != tcpp)
		return;


	stra	tk;
	stra	dod;
	stra	ip[2];
	if (_get_ipstr(ip[0], ip[1], eh, ih) != 0)
		return;

	ip[0].append(":").append(std::to_string(htons(th->source)));
	ip[1].append(":").append(std::to_string(htons(th->dest)));

	_get_curtime(tk);
	_get_sigpack(dod, *th, (pcsa)pl, len);
	fprintf(stdout, "%s TCP %21s %s %21s  %s\n", tk.c_str(), ip[sid].c_str(), dir, ip[did].c_str(), dod.c_str());
}
void _udp_packet(eth_header* eh, ip_header* ih, udp_header* uh, u_char* pl, size_t len)
{
	int sid		= 1;
	int did		= 0;
	int spr		= uh->dest;
	pcsa dir	= "<<";
	if (host.s_addr != ih->daddr)
	{
		sid	= 0;
		did	= 1;
		spr	= uh->source;
		dir	= ">>";

		if (host.s_addr != ih->saddr)
			return;
	}

	if (spr != udpp)
		return;


	stra	tk;
	stra	dod;
	stra	ip[2];
	if (_get_ipstr(ip[0], ip[1], eh, ih) != 0)
		return;

	ip[0].append(":").append(std::to_string(htons(uh->source)));
	ip[1].append(":").append(std::to_string(htons(uh->dest)));

	_get_curtime(tk);
	_get_audpack(dod, *uh, (pcsa)pl, len);
	fprintf(stdout, "%s UDP %21s %s %21s  %s\n", tk.c_str(), ip[sid].c_str(), dir, ip[did].c_str(), dod.c_str());
}

void _packet_parser(struct pcap_pkthdr& header, const u_char* pkt)
{
	eth_header*	eh;
	ip_header*	ih;				// ipheader
	size_t		ihn;			// ipheader length
	udp_header*	uh	= nullptr;
	tcp_header*	th	= nullptr;
	u_char*		pl	= nullptr;	// payload
	u_short		sz;


	{
		eh	= (eth_header*)pkt;
		u_short	ty	= htons(eh->ether_type);
		if (ty != ETHERTYPE_IP && ty != ETHERTYPE_IPV6)
			return;
	}
	{
		ih	= (ip_header*)(pkt + sizeof(eth_header));
		ihn	= ih->ihl * 4;;
		if (ihn < 20) {
			//fprintf(stdout, "   * Invalid IP header length: %u bytes\n", ihn);
			return;
		}
	}

	switch(ih->protocol) {
	case IPPROTO_TCP:
		if (tcpp == 0)
			return;

		th	= (tcp_header*)((u_char*)ih + ihn);
		pl	= (u_char*)th + th->doff *4;
		sz	= htons(ih->tot_len) - (ihn + th->doff *4);
		_tcp_packet(eh, ih, th, pl, sz);
		break;

	case IPPROTO_UDP:
		if (udpp == 0)
			return;

		uh	= (udp_header*)((u_char*)ih + ihn);
		pl	= (u_char*)&uh[1];
		sz	= htons(uh->len) - sizeof(udp_header);
		_udp_packet(eh, ih, uh, pl, sz);
		break;

	default:
		return;
	};
}

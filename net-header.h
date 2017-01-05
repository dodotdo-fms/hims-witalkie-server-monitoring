#ifndef	__NETWORK_PACKET_H__
#define	__NETWORK_PACKET_H__

#include <net/ethernet.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>


typedef	ether_header		eth_header;
typedef	iphdr				ip_header;
typedef	tcphdr				tcp_header;
typedef	udphdr				udp_header;

#endif

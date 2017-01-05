#include "main.h"

#include <pcap.h>


stra	pg_name;
char	ebuf[PCAP_ERRBUF_SIZE];
u_short	tcpp	= htons(4000);
u_short	udpp	= htons(4001);
in_addr	host	= {0};

void print_usage(void)
{
	pcap_if_t*	devs;
	char	buf[512];

	fprintf(stderr, "Usage: %s [dev] [signal-port] [audio-port]\n", pg_name.c_str());
	fprintf(stderr, "default\n");
	fprintf(stderr, "  signal-port : TCP 4000\n");
	fprintf(stderr, "  audio-port  : UDP 4001\n");
	fprintf(stderr, "\n");

	if (pcap_findalldevs(&devs, ebuf) == -1)
	{
		fprintf(stderr, "There is a problem with pcap_findalldevs: %s\n", ebuf);
		return;
	}

	fprintf(stderr, "devices\n");
	for (auto dev=devs; dev!=nullptr; dev=dev->next)
	{
		sstream	s1;

		s1	<< "  " << dev->name << ":";
		for (auto da=dev->addresses; da!=nullptr; da=da->next) {
			if (da->addr == 0 || da->netmask == 0)
				continue;

			if (da->addr->sa_family != AF_INET || da->addr->sa_family == AF_INET6)
				continue;

			inet_ntop(da->addr->sa_family, &((struct sockaddr_in *)da->addr)->sin_addr.s_addr, buf, sizeof(buf)-1);
			s1	<< " " << buf;
		}

		if (dev->addresses != nullptr)
			std::cerr	<< s1.str() << std::endl;
	}

	pcap_freealldevs(devs);
}

int _get_devip(const char* dev)
{
	int		fd;
	ifreq	ifr;

	fd	= socket(AF_INET, SOCK_DGRAM, 0);
	ifr.ifr_addr.sa_family = AF_INET;

	strncpy(ifr.ifr_name, dev, IFNAMSIZ-1);
	ioctl(fd, SIOCGIFADDR, &ifr);
	close(fd);

	sockaddr_in*	si	= (sockaddr_in*)&ifr.ifr_addr;
	host	= si->sin_addr;
	return	0;
}

void _packet_parser(struct pcap_pkthdr& header, const u_char* pkt);

int main(int argc, char **argv)
{
	pcap_t*	pc;
	char*	dev;

	{
		char*	cp;
		if ((cp = strrchr(argv[0], '/')) != NULL)
			pg_name	= cp + 1;
		else
			pg_name	= argv[0];
	}
	{
		if (argc >= 2)	dev	= argv[1];
		if (argc >= 3)	tcpp	= htons(atoi(argv[2]));
		if (argc >= 4)	udpp	= htons(atoi(argv[3]));

		if (argc == 1)
		{
			print_usage();
			return(1);
		}
	}
	{
		fprintf(stdout, "\n");
		fprintf(stdout, "device: %s\n", dev);
		fprintf(stdout, "\n");

		pc	= pcap_open_live(dev, 65535, 1, 1000, ebuf);
		if (pc == nullptr) {
			fprintf(stderr, "Couldn't open device %s: %s\n", dev, ebuf);
			return(2);
		}

		_get_devip(dev);
	}
	{
		int		rc;
		struct pcap_pkthdr*	header;
		const u_char*		pkt;
		while((rc=pcap_next_ex(pc, &header, &pkt)) >= 0)
		{
			if (rc == 0)
				continue;

			_packet_parser(*header, pkt);
		}
	}
	{
		pcap_close(pc);
	}

	return 0;
}

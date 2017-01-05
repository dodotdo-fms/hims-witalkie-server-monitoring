#ifndef	__INIT_H__
#define	__INIT_H__

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <unistd.h>
#include <stdarg.h>

#include <chrono>
#include <ctime>
#include <forward_list>
#include <iostream>
#include <list>
#include <memory>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <unordered_map>
#include <vector>

#include <asio.hpp>
#include <boost/bind.hpp>


using namespace std;

typedef	__UINT8_TYPE__					UINT8;
typedef	__UINT16_TYPE__					UINT16;
typedef	__UINT32_TYPE__					UINT32;

typedef	char*							psa;
typedef	const char*						pcsa;

typedef	__UINT16_TYPE__					CHN_;
typedef	__UINT32_TYPE__					UID_;
typedef	__UINT32_TYPE__					SEQ_;

typedef	volatile bool					vbool;

typedef	std::string						stra;
typedef	std::stringstream				sstream;

typedef	std::shared_timed_mutex			smutex;
typedef	std::condition_variable_any		cdtvar;

typedef std::shared_ptr<stra>			STRASP;
typedef std::forward_list<stra>			flsa;
typedef	std::vector<stra>				VCSA;
typedef	std::vector<std::thread>		vcthrd;
typedef	std::unordered_map<stra, stra>	MPAA;

#endif

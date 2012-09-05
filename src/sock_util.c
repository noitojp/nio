#include <sys/types.h>
#include <sys/socket.h>
#include  <sys/ioctl.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "sock_util.h"

#define BACKLOG_NUMBER 512

int init_listen4(int port)
{
	return( init_listen(port,AF_INET) );
}

int init_listen6(int port)
{
	return( init_listen(port,AF_INET6) );
}

int init_listen(int port,int af)
{
	int sock = -1;
	struct addrinfo hints;
	struct addrinfo *base_res = NULL;
	struct addrinfo *res_ptr = NULL;
	char portstr[32];
	int ret;

	if( port <= 0 ){
		return(-1);
	}
	sprintf(portstr,"%d",port);

	memset(&hints,'\0',sizeof(hints));
	hints.ai_family = af;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	ret = getaddrinfo(NULL,portstr,&hints,&base_res);
	if( ret != 0 ){
		fprintf(stderr,"ERROR: getaddrinfo: %s\n",gai_strerror(ret));
		return(-1);
	}

	for( res_ptr = base_res; res_ptr != NULL; res_ptr = res_ptr->ai_next ){
		sock = socket(res_ptr->ai_family,res_ptr->ai_socktype,res_ptr->ai_protocol);
		if( sock < 0 ){
			continue;
		}

		set_reuseaddr(sock);
		set_sndbuf(sock,65535);
		set_rcvbuf(sock,65535);
		if( bind(sock,res_ptr->ai_addr,res_ptr->ai_addrlen) < 0 ){
			fprintf(stderr,"WARN: bind: %s\n",strerror(errno));
			close(sock); sock = -1;
			continue;
		}

		if( listen(sock,BACKLOG_NUMBER) < 0 ){
			fprintf(stderr,"WARN: listen: %s\n",strerror(errno));
			close(sock); sock = -1;
			continue;
		}

		break;
	}

	freeaddrinfo(base_res); base_res = NULL;
	return(sock);
}

int connect4(const char *host,int port)
{
	return( connect2(host,port,AF_INET) );
}

int connect6(const char *host,int port)
{
	return( connect2(host,port,AF_INET6) );
}

int connect2(const char *host,int port,int af)
{
	int sock = -1;
	struct addrinfo hints;
	struct addrinfo *base_res = NULL;
	struct addrinfo *res_ptr = NULL;
	char portstr[32];
	int ret;

	if( NULL == host || port <= 0 ){
		return(-1);
	}
	sprintf(portstr,"%d",port);

	memset(&hints,'\0',sizeof(hints));
	hints.ai_family = af;
	hints.ai_socktype = SOCK_STREAM;
	ret = getaddrinfo(host,portstr,&hints,&base_res);
	if( ret != 0 ){
		fprintf(stderr,"ERROR: getaddrinfo: %s\n",gai_strerror(ret));
		return(-1);
	}

	for( res_ptr = base_res; res_ptr != NULL; res_ptr = res_ptr->ai_next ){
		sock = socket(res_ptr->ai_family,res_ptr->ai_socktype,res_ptr->ai_protocol);
		if( sock < 0 ){
			continue;
		}

		set_sndbuf(sock,65535);
		set_rcvbuf(sock,65535);
		if( connect(sock,res_ptr->ai_addr,res_ptr->ai_addrlen) < 0 ){
			close(sock); sock = -1;
			continue;
		}

		break;
	}

	freeaddrinfo(base_res); base_res = NULL;
	return(sock);
}

int set_reuseaddr(int sock)
{
	const int on = 1;
	return(setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,(const void*)&on,(socklen_t)sizeof(on)));
}

int set_nodelay(int sock)
{
	const int on = 1;
	return(setsockopt(sock,IPPROTO_TCP,TCP_NODELAY,(const void*)&on,(socklen_t)sizeof(on)));
}

int set_sndbuf(int sock,int siz)
{
	return(setsockopt(sock,SOL_SOCKET,SO_SNDBUF,(const void*)&siz,(socklen_t)sizeof(siz)));
}

int set_rcvbuf(int sock,int siz)
{
	return(setsockopt(sock,SOL_SOCKET,SO_RCVBUF,(const void*)&siz,(socklen_t)sizeof(siz)));
}

int set_nonblock(int sock)
{
	const int on = 1;
	return( ioctl(sock,FIONBIO,&on) );
}

int set_keepalive(int sock)
{
	const int on = 1;
	return(setsockopt(sock,SOL_SOCKET,SO_KEEPALIVE,(const void*)&on,(socklen_t)sizeof(on)));
}

int set_sndtimeo(int sock,int msec)
{
	struct timeval tv;

	tv.tv_sec = msec / 1000;
	tv.tv_usec = (msec % 1000) * 1000;
	return(setsockopt(sock,SOL_SOCKET,SO_SNDTIMEO,(const void*)&tv,(socklen_t)sizeof(tv)));
}

int set_rcvtimeo(int sock,int msec)
{
	struct timeval tv;

	tv.tv_sec = msec / 1000;
	tv.tv_usec = (msec % 1000) * 1000;
	return(setsockopt(sock,SOL_SOCKET,SO_RCVTIMEO,(const void*)&tv,(socklen_t)sizeof(tv)));
}


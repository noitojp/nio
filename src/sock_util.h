#ifndef __SOCK_UTIL_H_
#define __SOCK_UTIL_H_

#ifdef __cplusplus
extern "C" {
#endif

extern int init_listen4(int port);
extern int init_listen6(int port);
extern int init_listen(int port,int af);

extern int connect4(const char *host,int port);
extern int connect6(const char *host,int port);
extern int connect2(const char *host,int port,int af);

extern int set_reuseaddr(int sock);
extern int set_nodelay(int sock);
extern int set_nonblock(int sock);
extern int set_keepalive(int sock);
extern int set_sndbuf(int sock,int siz);
extern int set_rcvbuf(int sock,int siz);
extern int set_sndtimeo(int sock,int msec);
extern int set_rcvtimeo(int sock,int msec);

#ifdef __cplusplus
}
#endif

#endif


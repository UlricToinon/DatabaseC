#ifndef SERVEUR_H_INCLUDED
#define SERVEUR_H_INCLUDED

#ifdef WIN32

#include <winsock2.h>
#include <mysql.h>

#elif defined (linux)

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> /* close */
#include <netdb.h> /* gethostbyname */
#include <mysql.h> /* mysql */
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

#else

#error not defined for this platform

#endif

#define CRLF		"\r\n"
#define PORT	 	65432
#define MAX_CLIENTS 	100

#define BUF_SIZE	1024

#include "client.h"

typedef struct {
 char* nom;
 char* prenom;
}data;

static void init(void);
static void end(void);
static void app(void);
static int init_connection(void);
static void end_connection(int sock);
static int read_client(SOCKET sock, char *buffer);
static void write_client(SOCKET sock, const char *buffer);


#endif // SERVEUR_H_INCLUDED

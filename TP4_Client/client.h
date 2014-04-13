#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

#ifdef WIN32

#include <winsock2.h>

#elif defined WIN64

#include <winsock.h>

#elif defined (linux)

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> /* close */
#include <netdb.h> /* gethostbyname */
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

#define CRLF	 "\r\n"
#define PORT	 65432

#define BUF_SIZE 1024

static void init(void);
static void end(void);
static void app(const char *address);
static int init_connection(const char *address);
static void end_connection(int sock);
static int read_server(SOCKET sock, char *buffer);
static void write_server(SOCKET sock, const char *buffer);
static void read_string(const char* message, char chaine[], int size);

#endif // CLIENT_H_INCLUDED

#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

#include "serveur.h"

typedef struct {
	pthread_t sock_thread;
	pthread_mutex_t mutex_sock;
} client_t;


#endif // CLIENT_H_INCLUDED

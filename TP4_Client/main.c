#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "client.h"

static void init(void)
{
#ifdef WIN32
   WSADATA wsa;
   int err = WSAStartup(MAKEWORD(2, 2), &wsa);
   if(err < 0)
   {
      puts("WSAStartup failed !");
      exit(EXIT_FAILURE);
   }
#endif
}

static void end(void)
{
#ifdef WIN32
   WSACleanup();
#endif
}

static void app(const char *address)
{
    SOCKET sock;
    struct sockaddr_in server;
    char message[BUF_SIZE] , server_reply[BUF_SIZE];
    
    /* creation de socket et initialisation de la connection */
    sock = init_connection(address);
    write_server(sock, "");
    //On garde la communication avec le serveur
    while(1)
    {
         /* Propose un choix */
         printf ("Quel action voulez vous faire ?\n Utilisation : \n Tapez 1 pour lire \n Tapez 2 pour écrire \n Tapez 9 pour vous déconnecter \n \n Veuillez entrer votre valeur : ");
        scanf("%s" , message);
        
        /* Envoi du choix au serveur puis attente de réponse */
        write_server(sock, &message);
        read_server (sock, &server_reply);
        
        /* Cas du mode Ecriture */
        if ( strcmp(server_reply, "Ecriture") == 0){
          /* Demande et envoi des variables nom et prenom */
          printf ("Entrez le nom que vous voulez ajouter : ");
          scanf("%s", message);
          write_server(sock, &message);
          printf ("Entrez le prenom que vous voulez ajouter : ");
          scanf("%s", message);
          write_server(sock, &message);
         	/* Réponse du serveur */
          read_server(sock, &server_reply);
        }
        puts("\nServer reply :");
        puts(server_reply);
        puts("\n");
        /* Si on entre 9, on sort de la boucle while */
        if (strcmp(message, "9") == 0){
          break;
        }
    } // while()
     
    close(sock);
}

static int init_connection(const char *address)
{
   SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
   SOCKADDR_IN sin = { 0 };
   struct hostent *hostinfo;

   if(sock == INVALID_SOCKET)
   {
      perror("socket()");
      exit(errno);
   }

   hostinfo = gethostbyname(address);
   if (hostinfo == NULL)
   {
      fprintf (stderr, "Unknown host %s.\n", address);
      exit(EXIT_FAILURE);
   }

   sin.sin_addr = *(IN_ADDR *) hostinfo->h_addr;
   sin.sin_port = htons(PORT);
   sin.sin_family = AF_INET;

   if(connect(sock,(SOCKADDR *) &sin, sizeof(SOCKADDR)) == SOCKET_ERROR)
   {
       #ifdef WIN32
        perror("connect()");
        exit(WSAGetLastError());
       #elif defined (linux)
        perror("connect()");
        exit(errno);
       #endif // WIN32

   }
   puts("Connected \n");

   return sock;
}

static void end_connection(int sock)
{
   closesocket(sock);
}

static int read_server(SOCKET sock, char *buffer)
{
   int n = 0;

   if((n = recv(sock, buffer, BUF_SIZE - 1, 0)) < 0)
   {
      perror("recv()");
      exit(errno);
   }

   buffer[n] = 0;

   return n;
}

static void write_server(SOCKET sock, const char *buffer)
{
   if(send(sock, buffer, strlen(buffer), 0) < 0)
   {
      perror("send()");
      exit(errno);
   }
}

static void read_string(const char* message, char chaine[], int size)
{
    printf("%s \n", message);
    fgets(chaine, size-1, stdin);
    chaine[strlen(chaine) - 1] = '\0';
}

int main(int argc, char **argv)
{
   init();
   
   char* address = "127.0.0.1";
   app(address);

   end();

   return EXIT_SUCCESS;
}

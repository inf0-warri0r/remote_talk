/*
*Author :Tharindra Galahena
*Project:walkie-talkie application for linux
*Date   :28/04/2012
*/

#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

struct addrinfo  *p;
int pfds[2];

int create_sock(char *c,int port){
	struct addrinfo *serinfo, hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	int sock;
	
	getaddrinfo(c, "3999", &hints, &serinfo);
	for(p = serinfo; p != NULL; p = p -> ai_next){
		if((sock = socket(p -> ai_family, p -> ai_socktype, p -> ai_protocol)) == -1) 				continue;
		break;
	}
	int b = 1;
	
	if(setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &b, sizeof(b)) == -1){
		perror("set");	
	}
	if(p == NULL) {
		printf("aaa\n");
		return 0;	
	}
	return sock;
}
void sendd(int sock, int max, int pid){

	char *buf = malloc(max*4);
	if(p == NULL) return;
	while(1){		
		read(pid, buf, max*4);
		if(sendto(sock, buf, max*4, 0, p -> ai_addr, p -> ai_addrlen) == -1){
			perror("ERROR!\n");
			close(sock);
			exit(0);	
		}
	}
}

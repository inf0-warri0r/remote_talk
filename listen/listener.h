/*
*Author :Tharindra Galahena
*Project:walkie-talkie application for linux
*Date   :28/04/2012
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netdb.h>

socklen_t addr_len;
struct sockaddr_storage th_addr;

int connect_sock(){
	addr_len = sizeof(th_addr);
	struct addrinfo hints, *res, *p;
	int sock;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(NULL, "3999", &hints, &res);
	for(p = res; p != NULL; p = p -> ai_next){
		if((sock = socket(p -> ai_family, p -> ai_socktype, p -> ai_protocol)) == -1) 				
			continue;
		if(bind(sock, p -> ai_addr, p -> ai_addrlen) == -1){
			close(sock);
			continue;		
		}
		break;
	}
	if(p == NULL) {
		printf("Oops!!!\n");
		return 0;	
	}
	return sock;
}
int recive(int sock, char *buf, int max){
	int cc;
	cc = recvfrom(sock, buf, max*4, 0, (struct sockaddr *)&th_addr, &addr_len);
	return cc;
}

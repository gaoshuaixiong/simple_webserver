#include "tiny_webserver.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
	unsigned int listenfd,connfd,port,clientlen;

	struct sockaddr_in clientaddr;
	if(argc!= 2)
	{
		fprintf(stderr,"usage:%s <port>\n",argv[0]);
	}
	port = atoi(argv[1]);

	listenfd = Open_listenfd(port);

	while(1)
	{
		clientlen = sizeof(clientaddr);
		connfd = Accept(listenfd,(sockaddr*)&clientaddr,&clientlen);
		doit(connfd);
		Close(connfd);
	}
	return 0;
}
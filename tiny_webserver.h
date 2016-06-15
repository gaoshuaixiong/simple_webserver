#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "def.h"
#include "riot.h"
using namespace std;

void doit(int fd)
{
	int is_static;
	struct stat sbuf;
	char buf[MAXLINE],method[MAXLINE],uri[MAXLINE],version[MAXLINE];
	char filename[MAXLINE],cgiargs[MAXLINE];
	rio_t rio;
  	
  	rio_readinitb(&rio,fd);
  	rio_readlineb(&rio,buf,MAXLINE);
  	sscanf(buf,"%s %s %s",method,uri,version);
  	if(strcasecmp(method,"GET"))
  	{
  		clienterror(fd,method,"501","Not Implemented","Tiny does not implement this method");
  		return;
  	}
  	read_requesthdrs(&rio);

}

int open_listenfd(int port)
{
	int listenfd,optval = 1;
	struct sockaddr_in serveraddr;

	if((listenfd = socket(AF_INET,SOCK_STREAM,0))<0)
	{
		return -1;
	}

	if(setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,(const void *)&optval,sizeof(int))<0)
	{
		return -1;
	}


	bzero((char*)&serveraddr,sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = port;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(listenfd,(sockaddr*)&serveraddr,sizeof(serveraddr))<0)
		return -1;

	if(listen(listenfd,5)<0)
		return -1;
	return listenfd;
}


int Open_listenfd(unsigned int port)
{
	int listenfd;
	if((listenfd=open_listenfd(port))==-1)
	{
		cout<<"error in Open_listenfd"<<endl;
	}
	else
	{
		return listenfd;
	}
}

int Accept(unsigned int listenfd,struct sockaddr *addr, unsigned int *addrlen)
{
	int connfd;
    if((connfd = accept(listenfd,addr,addrlen))<0)
    {
    	cout<<"error in Accept"<<endl;
    }
    else
    {
    	return connfd;
    }
}

void Close(unsigned int connfd)
{
	close(connfd);
}



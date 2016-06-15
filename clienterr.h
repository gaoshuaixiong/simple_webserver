#include "def.h"
#include "stdio.h"
void cienterror(int fd,char *cause,char * errnum,char * shortmsg,char * longmsg)
{
	char buf[MAXLINE],body[MAXBUF];
	sprintf(body,"<html><title>Tiny Error<title>");
	sprintf(body, "%s<body bgcolor =\"ffffff\">\r\n",body);
	sprintf(body, "%s%s:%s\r\n",body,errnum,shortmsg);
	sprintf(body,"%s<p>%s: %s\r\n",body,longmsg,shortmsg);
}
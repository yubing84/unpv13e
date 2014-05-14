#include "unp.h"

int main(int argc, char ** argv)
{
    int                 sockfd;
    int                 n;
    char                recvline[MAXLINE + 1];
    struct sockaddr_in  servaddr;

    if (argc != 2)
    {
        err_quit("usage: a.out <IPaddress>");
    }
    // socket函数创建一个网际(AF_INET)字节流(SOCK_STREAM)套接字(就是TCP套接字)
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        err_sys("socket error");
    }

    // 指定服务器的IP地址和端口，我们把服务器的IP地址和端口号填入一个网际套接字地址结构(一个名为servaddr的sockaddr_in结构变量)
    // bzero清空整零整个结构，置地址族为AF_INET，端口号为13，IP地址为命令行第一个参数的值
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port   = htons(13); // daytime server
    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
    {
        err_quit("inet_pton error for %s", argv[1]);
    }

    if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0)
    {
        err_sys("connect error");
    }

    while ( (n = read(sockfd, recvline, MAXLINE)) > 0)
    {
        recvline[n] = 0; // null terminate
        if (fputs(recvline, stdout) == EOF)
        {
            err_sys("fputs error");
        }
    }
    if (n < 0)
    {
        err_sys("read error");
    }

    exit(0);
}
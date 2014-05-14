#include    "unp.h"
#include    <time.h>

int
main(int argc, char **argv)
{
    int                 listenfd, connfd;
    struct sockaddr_in  servaddr;
    char                buff[MAXLINE];
    time_t              ticks;

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    // We specify the IP address as INADDR_ANY, 
    // which allows the server to accept a client connection on any interface, in case the server host has multiple interfaces
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(13);   /* daytime server */

    Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

    // By calling listen, the socket is converted into a listening socket, on which incoming connections from clients will be accepted by the kernel.
    // These three steps, socket, bind, and listen, are the normal steps for any TCP server 
    Listen(listenfd, LISTENQ);

    for ( ; ; ) { //  Normally, the server process is put to sleep in the call to accept, waiting for a client connection to arrive and be accepted. 
        // A TCP connection uses what is called a three-way handshake to establish a connection. When this handshake completes, accept returns,
        // and the return value from the function is a new descriptor (connfd) that is called the connected descriptor. 
        // This new descriptor is used for communication with the new client. A new descriptor is returned by accept for each client that connects to our server.

        connfd = Accept(listenfd, (SA *) NULL, NULL);

        ticks = time(NULL);
        // �ڶ�������ָ��Ŀ�Ļ�������С����ֹ���
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        Write(connfd, buff, strlen(buff));
        // ����������tcp������ֹ���У�ÿ�������Ϸ���һ��FIN���ڸ�FIN���ɸ��ԵĶԶ�ȷ�ϡ�
        Close(connfd);
    }
}
// ��������һ��ֻ�ܴ���һ���ͻ����������ͻ�����ͬʱ���ϵͳ�ں���ĳ�������Ŀ�����°�����������У�Ȼ��ÿ�η���һ����accept�����������������Ҫ�ܳ�ʱ�����
// ÿ���ͻ�����ô���Ǳ�����ĳ�ַ�ʽ�ص��Ը����ͻ��ķ��񡣱���������Ϊ��������������Ϊ����ÿ���ͻ���������ִ��һ�Ρ�ͬʱ�ܴ������ͻ��Ĳ����������ж��ֱ�̼���

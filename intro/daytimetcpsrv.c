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
        // 第二个参数指定目的缓冲区大小，防止溢出
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        Write(connfd, buff, strlen(buff));
        // 引发正常的tcp连接终止序列：每个方向上发送一个FIN，第个FIN又由各自的对端确认。
        Close(connfd);
    }
}
// 本服务器一次只能处理一个客户，如果多个客户连接同时到达，系统内核在某个最大数目限制下把它们排入队列，然后每次返回一个给accept函数，如果服务器需要很长时间服务
// 每个客户，那么我们必须以某种方式重叠对各个客户的服务。本例服务器为迭代服务器，因为对于每个客户它都迭代执行一次。同时能处理多个客户的并发服务器有多种编程技术

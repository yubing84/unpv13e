#include <iostream>
#include "unp.h"

int main(int argc, char** argv)
{
    int                listenfd;
    int                connfd;
    pid_t              childpid;
    socklen_t          clilen;
    struct sockaddr_in cliaddr;
    struct sockaddr_in servaddr;

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family      = AF_INET; // ����Ƕ��ޣ����ǽ�����Ŀ�ĵ�ַΪ�κα��ؽӿڵ�����
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    std::cout << SERV_PORT << std::endl;
    servaddr.sin_port        = htons(SERV_PORT);

    Bind(listenfd, (SA*)&servaddr, sizeof(servaddr));

    Listen(listenfd, LISTENQ); // ת��Ϊ�����׽���

    for ( ; ; )
    {
        clilen = sizeof(cliaddr);
        // ������������accept���ã��ȴ��ͻ����ӵ����
        connfd = Accept(listenfd, (SA *) &cliaddr, &clilen);
        // forkΪÿ���ͻ�����һ���������ǵ��ӽ��̣��ӹرռ����׽��֣����ر��������׽���
        if ((childpid = Fork()) == 0) /* child process */
        {
            Close(listenfd);    /* close listening socket */
            str_echo(connfd);   /* process the request */
            std::cout << "exiting tcpserv01 child process" << std::endl;
            // �������ӽ��̵���exit����ֹ���������ӽ����д򿪵�������������֮�رգ�
            // ��ᵼ��TCP������ֹ����
            // ����������ֽڣ�һ���ӷ��������ͻ���FIN���ͣ�һ���ӿͻ�����������ACK�����ˣ�
            // ������ȫ��ֹ���ͻ��׽��ֽ���TIME_WAIT״̬��

            // ��һ����
            // when this child is existed, this process will send sigchild signal to parent process
            // and in the parent process, we did not handle this signal, so the child process,
            // this process will be a zombie process, we can see that by command ps ux
            exit(0);
        }
        Close(connfd); /* parent closes connected socket */
    }
}

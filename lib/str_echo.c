#include <iostream>
#include "unp.h"

// �ӿͻ��������ݣ��������ݻ�����ͻ�
void
str_echo(int sockfd)
{
    ssize_t n;
    char    buf[MAXLINE];

again:
    while ( (n = read(sockfd, buf, MAXLINE)) > 0) // ���׽��ֶ�������
        Writen(sockfd, buf, n);                   // ���������ݻ�����ͻ�������ͻ��ر�����(�����������)����ô���յ��ͻ���FIN�����·������ӽ��̵�read��������0
    // ���ֵ���str_echo�����ķ��أ��Ӷ���tcpserv01.c����ֹ�ӽ��̡�

    if (n < 0 && errno == EINTR)
        goto again;
    else if (n < 0)
        err_sys("str_echo: read error");

    std::cout << "exiting str_echo" << std::endl;
}

#include	"unp.h"

void str_cli(FILE *fp, int sockfd)
{
    char sendline[MAXLINE];
    char recvline[MAXLINE];

    // �ӱ�׼�������һ���ı�
    // �������ļ������������ʱ��fgets������һ����ָ�룬���ǿͻ�������ֹѭ�������ǵ�Fgets������������Ƿ�����������������ֹ���̣����Fgetsֻ���������ļ�������ʱ
    // �ŷ���һ����ָ��
    while (Fgets(sendline, MAXLINE, fp) != NULL)
    {
        // д����������
        Writen(sockfd, sendline, strlen(sendline));
        // ����������Ը��еĻ���
        if (Readline(sockfd, recvline, MAXLINE) == 0)
            err_quit("str_cli: server terminated prematurely");
        // �ѻ���д����׼���
        Fputs(recvline, stdout);
    }
    Fputs("exiting str_cli\n", stdout);
}

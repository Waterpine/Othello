#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
  
#define SERVER_PORT 5000  
#define BUFSIZE 1024

/* 
 ���ӵ��������󣬻᲻ͣѭ�����ȴ����룬 
 ����quit�󣬶Ͽ�������������� 
 */  

int create_session(int clientSocket)
{
    int ret, i, h;
    char str1[4096], str2[4096], buf[BUFSIZE], *str;
    socklen_t len;
    fd_set   t_set1;
    struct timeval  tv;

    str=(char *)malloc(128);
 
    memset(str1, 0, 4096);
    strcat(str1, "GET /create_session/7 HTTP/1.1\n");
    strcat(str1, "Host: 47.89.179.202:5000\n");
    strcat(str1, "Content-Type: text/html\n");
    strcat(str1, "Content-Length: ");
    strcat(str1, str);
    strcat(str1, "\n\n");
    printf("%s\n",str1);
 
    ret = write(clientSocket,str1,strlen(str1));
    if (ret < 0) {
        printf("����ʧ�ܣ����������%d��������Ϣ��'%s'\n",errno, strerror(errno));
        exit(0);
    }
    else {
        printf("��Ϣ���ͳɹ�����������%d���ֽڣ�\n\n", ret);
    }
 
    FD_ZERO(&t_set1);
    FD_SET(clientSocket, &t_set1);
 
    while(1) {
        sleep(2);
        tv.tv_sec = 0;
        tv.tv_usec = 0;
        h = 0;
        printf("--------------->1");
        h = select(clientSocket +1, &t_set1, NULL, NULL, &tv);
        printf("--------------->2");
 
        //if (h == 0) continue;
        if (h < 0) {
            close(clientSocket);
            printf("�ڶ�ȡ���ݱ���ʱSELECT��⵽�쳣�����쳣�����߳���ֹ��\n");
            return -1;
        };
 
        if (h > 0) {
            memset(buf, 0, 4096);
            i = read(clientSocket, buf, 4095);
            if (i == 0) {
                close(clientSocket);
                printf("��ȡ���ݱ���ʱ����Զ�˹رգ����߳���ֹ��\n");
                return -1;
            }
            printf("%s\n", buf);
        }
    }
    printf("done!");
    return 0;
}

int move(int clientSocket, char* x_pos, char* y_pos, char* player)
{
    int send_num;
    char recv_buf [4096];
    char str1[4096];
    char stm[4096];
    strcat(stm, x_pos);
    strcat(stm,"/");
    strcat(stm, y_pos);
    strcat(stm, "/");
    strcat(stm, player);
    while (1)
    {
        printf("begin send\n");
        memset(str1,0,4096);
        strcat(str1, "POST move/"); 
        strcat(str1, stm);
        strcat(str1, "HTTP/1.1\r\n");
        strcat(str1, "Host: 47.89.179.202:5000\r\n");
        strcat(str1, "Content-Length: \r\n");
        strcat(str1, "Content-Type: text/html\r\n");
        strcat(str1, "\r\n");
        printf("str1 = %s\n",str1);
        send_num = send(clientSocket, str1, strlen(str1), 0);
        if (send_num < 0)
        {
            perror("send error");
            exit(1);
        }
        else
        {
            printf("send successful\n");
            printf("begin recv:\n");
            int recv_num = recv(clientSocket, recv_buf, sizeof(recv_buf),0);
            if (recv_num < 0) {
                perror("recv");
                exit(1);
            } 
            else {
                printf("recv sucess:%s\n",recv_buf);
            }
         }
        break;
        sleep(5);
    }
}

int board(int clientSocket)
{
    int ret, i, h;
    char str1[4096], str2[4096], buf[BUFSIZE], *str;
    socklen_t len;
    fd_set   t_set1;
    struct timeval  tv;

    str=(char *)malloc(128);
 
    memset(str1, 0, 4096);
    strcat(str1, "GET /board_string/7 HTTP/1.1\n");
    strcat(str1, "Host: 47.89.179.202:5000\n");
    strcat(str1, "Content-Type: text/html\n");
    strcat(str1, "Content-Length: ");
    strcat(str1, str);
    strcat(str1, "\n\n");
    printf("%s\n",str1);
 
    ret = write(clientSocket,str1,strlen(str1));
    if (ret < 0) {
        printf("����ʧ�ܣ����������%d��������Ϣ��'%s'\n",errno, strerror(errno));
        exit(0);
    }
    else {
        printf("��Ϣ���ͳɹ�����������%d���ֽڣ�\n\n", ret);
    }
 
    FD_ZERO(&t_set1);
    FD_SET(clientSocket, &t_set1);
 
    while(1) {
        sleep(2);
        tv.tv_sec = 0;
        tv.tv_usec = 0;
        h = 0;
        printf("--------------->1");
        h = select(clientSocket +1, &t_set1, NULL, NULL, &tv);
        printf("--------------->2");
 
        //if (h == 0) continue;
        if (h < 0) {
            close(clientSocket);
            printf("�ڶ�ȡ���ݱ���ʱSELECT��⵽�쳣�����쳣�����߳���ֹ��\n");
            return -1;
        };
 
        if (h > 0) {
            memset(buf, 0, 4096);
            i= read(clientSocket, buf, 4095);
            if (i == 0) {
                close(clientSocket);
                printf("��ȡ���ݱ���ʱ����Զ�˹رգ����߳���ֹ��\n");
                return -1;
            }
            printf("%s\n", buf);
        }
    }
}

int main()  
{  
    //�ͻ���ֻ��Ҫһ���׽����ļ������������ںͷ�����ͨ��  
    int clientSocket;  
    //������������socket  
    struct sockaddr_in serverAddr;  
    int ret, i, h;
    char str1[4096], str2[4096], buf[BUFSIZE], *str;
    socklen_t len;
    fd_set   t_set1;
    struct timeval  tv;
    if((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)  
    {  
        perror("socket");  
        return 1;  
    }

    serverAddr.sin_family = AF_INET;  
    serverAddr.sin_port = htons(SERVER_PORT);  
    //ָ���������˵�ip�����ز��ԣ�127.0.0.1  
    //inet_addr()�����������ʮ����IPת���������ֽ���IP  
    serverAddr.sin_addr.s_addr = inet_addr("47.89.179.202");  
    if(connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)  
    {  
        perror("connect");  
        return 1;  
    }  
    printf("connect with destination host...\n");  
    int re;
    re = create_session(clientSocket);
    re = move(clientSocket,"3","2","W");
    re = board(clientSocket);
    
    // Judging black and white by buf


    /*while(1)  
    {  
        memset(sendbuf, 0, 4096);
        strcat(sendbuf, "GET /ymnets/p/6255674.html HTTP/1.1\n");
        strcat(sendbuf, "Host: www.cnblogs.com\n");
        strcat(str1, "Content-Type: text/html\n");
        strcat(str1, "Content-Length: ");
        strcat(str1, str);
        strcat(str1, "\n\n");
 
        /*printf("Input your world:>");  
        scanf("%s", sendbuf);  
        printf("\n");  
  
        send(clientSocket, sendbuf, strlen(sendbuf), 0);  
        if(strcmp(sendbuf, "quit") == 0)  
            break;  
        iDataNum = recv(clientSocket, recvbuf, 200, 0);  
        recvbuf[iDataNum] = '\0';  
        printf("recv data of my world is: %s\n", recvbuf);  
    }  */
    close(clientSocket);  
    return 0;  
} 
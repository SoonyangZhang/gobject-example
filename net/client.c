#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

void error_handling(char* message);

void error_handling(char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc, char **argv) {
    int sock;
    struct sockaddr_in serv_addr;
    char message[1500]="hello server";
    int str_len;
    memset(&serv_addr, 0, sizeof(serv_addr));
	char *ip="127.0.0.1";
	uint16_t port=4321;

    //创建用于internet的流协议(TCP)socket
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        error_handling("socket() error");
    }

    //设置一个socket地址结构client_addr,代表客户机internet地址, 端口
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(ip);
    serv_addr.sin_port = htons(port);

    //把socket和socket地址结构联系起来
    if( connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) == -1) {
        error_handling("connect() error");
    }
	
    str_len = write(sock, message,strlen(message));
	
    if (str_len == -1) {
        error_handling("write() error");
    }
	char buf[1500];
	memset(buf,0,1500);
	str_len = read(sock, buf,1500);
    printf("Message from server : %s \n", buf);
    close(sock);
    return 0;
}

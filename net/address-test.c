#include <stdio.h>
#include <stdint.h>
#include  "netutils.h"
int main(){
    struct in_addr  in4;
    printf("%d\n",sizeof(in4));
    char *ip="127.0.0.1";
    rtc_inet_pton(AF_INET,ip,&in4);
    printf("%d\n",in4);
    char buf[INET6_ADDRSTRLEN];
    rtc_inet_ntop(AF_INET,(void*)&in4,buf,INET6_ADDRSTRLEN);
    printf("%s\n",buf);
    char* ipv6 = "2001:db8:1020:3040:5060:7080:90a0:b0c0";
    struct in6_addr in6;
    char buf6[INET6_ADDRSTRLEN];
    rtc_inet_pton(AF_INET6,ipv6,&in6);
    rtc_inet_ntop(AF_INET6,(void*)&in6,buf6,INET6_ADDRSTRLEN);
    printf("%s\n",buf6);
    return 0;
}


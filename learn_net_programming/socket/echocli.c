#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>


#define ERR_EXIT(m) \
  do \
  { \
    perror(m); \
    exit(EXIT_FAILURE); \
  } while(0)



int main(void){

  int sock;
  if((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP))<0){
    ERR_EXIT("socket");  
  }

  struct sockaddr_in servaddr;
  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(5188);
  servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

  if(connect(sock, (struct sockaddr*)&servaddr, sizeof(servaddr)) <0){
    ERR_EXIT("connect");
  }


  char sendbuf[1024] = {0};
  char recvbuf[1024] = {0};
  char *s;
  while((s = fgets(sendbuf, sizeof(sendbuf), stdin)) != NULL){
   
    write(sock, sendbuf, strlen(sendbuf));
    read(sock, recvbuf, sizeof(recvbuf));
    fputs(recvbuf, stdout);
  }


  close(sock);

  return 0;
}

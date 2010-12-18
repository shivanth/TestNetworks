#include<stdio.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>


#define PORT 2000
#define DEST_IP "127.0.0.1"

void main(){
  char* c="Hello this is one great success";
 int sd=socket(AF_INET,SOCK_STREAM,0);
  struct sockaddr_in myaddr;
  myaddr.sin_family=AF_INET;
  myaddr.sin_port=htons(PORT);
  myaddr.sin_addr.s_addr=inet_addr(DEST_IP);
  memset(&(myaddr.sin_zero),0,8);
  if(connect(sd,(struct sockaddr*)&myaddr,sizeof(myaddr))==-1){
    perror("connect error\n");
    exit(1);
  }
  //gets(c);
  if(send(sd,(const void *)c,strlen(c),0)==-1){
    perror("Error sending\n");
    exit(1);
  }
  printf("data sent\n");
  close(sd);
}

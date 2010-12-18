#include<stdio.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define PORT 2000

void main(){
  struct sockaddr_in myaddr;
  int sock;
  sock=socket(AF_INET,SOCK_STREAM,0);
  if(sock==-1){
    perror("Cannot Create socket");
    exit(1);
  }
  else 
    printf("Done creating socket\n");
    myaddr.sin_family=AF_INET;
    myaddr.sin_port=htons(PORT);
    myaddr.sin_addr.s_addr=INADDR_ANY;
    memset(&(myaddr.sin_zero),0,8);
    if(bind(sock,(struct sockaddr *)&myaddr,sizeof(struct sockaddr))==-1){
      perror("server binding error\n");
      exit(1);
    }
    printf("server binded\n");
    listen(sock,5);int ct;
    int new_fd=accept(sock,(struct sockaddr *)&myaddr,&ct);
    char* c=malloc(200);
    int k;
    if((k=recv(new_fd,(void *)c,200,0))<0){
      printf("error recieving\n");
      exit(0);
    }
    printf("%s",c);
  }

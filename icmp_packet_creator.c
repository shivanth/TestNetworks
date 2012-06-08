#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<linux/ip.h>
#include<linux/icmp.h>
#include<string.h>
#include<unistd.h>
#define MAGIC 12

unsigned short in_cksum(unsigned short *addr,int len);


int main(){
  struct iphdr* ip;
  struct icmphdr*icmp;
  struct sockaddr_in connection;
  char* packet;
  int sockfd,optval;
  if(getuid()!=0){
    fprintf(stderr,"Root privilages needed\n");
    exit(EXIT_FAILURE);
  }
  packet=malloc(sizeof(struct iphdr)+sizeof(struct icmphdr));
  ip=(struct iphdr *)packet;
  icmp=(struct icmphdr*)(packet+sizeof(struct icmphdr));
  ip->ihl=5;
  ip->version=4;
  ip->tos=0;
  ip->tot_len=sizeof(struct iphdr)+sizeof(struct icmphdr);
  ip->id=htons(random());
  ip->ttl=255;
  ip->protocol=IPPROTO_ICMP;

  ip->saddr=inet_addr("127.0.0.1");
  ip->saddr=inet_addr("127.0.0.1");
  if((sockfd=socket(AF_INET,SOCK_RAW,IPPROTO_ICMP))==-1){
    perror("Socket");
    exit(EXIT_FAILURE);
  }
  setsockopt(sockfd,IPPROTO_IP,IP_HDRINCL,&optval,sizeof(int));
  icmp->type=ICMP_ECHO;
  icmp->code=MAGIC;
  icmp->un.echo.id=0;
  icmp->un.echo.sequence=0;
  icmp->checksum=-0;
  icmp->checksum=in_cksum((unsigned short*)icmp,sizeof(struct icmphdr));
  ip->check=in_cksum((unsigned short *)ip,sizeof(struct iphdr));
  connection.sin_family=AF_INET;
  connection.sin_addr.s_addr=inet_addr("127.0.0.1");
  sendto(sockfd,packet,ip->tot_len,0,(struct sockaddr *)&connection,sizeof(struct sockaddr));

  }
unsigned short in_cksum(unsigned short *addr,int len){
  register int sum=0;
  u_short answer=0;
  register u_short *w=addr;
  register int nleft = len;
  while(nleft>1){
    sum+=*w++;
    nleft-=2;
  }
  if(nleft==1){
    *(u_char*)(&answer)=*(u_char*)w;
    sum+=answer;
  }
  sum=(sum>>16)+(sum & 0xffff);
  sum+=(sum>>16);
  answer=~sum;
  return(answer);
}

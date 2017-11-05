/**
 * @file icmpapi.c
 * @author Napat Rungruangbangchan
 * @date 29 January 2011 
 * @brief 
 * @Compiler: gcc(ubuntu 14.04)
 * @License: 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <linux/ip.h>
#include <linux/icmp.h>
#include <string.h>
#include <errno.h>

unsigned short in_cksum(unsigned short *addr, int len){
	int sum = 0;
	unsigned short ans = 0;
	unsigned short *addr_word = addr;
	int nleft = len;
	
	while(nleft > 1){
		sum 	+= *addr_word++;
		nleft 	-= 2;
	}
	if(nleft == 1){
		*(unsigned char *)(&ans) = *(unsigned char *) addr_word;
		sum += ans;
	}
	sum = (sum >> 16) + (sum &0xFFFF);	// add hi 16 to low 16
	sum += (sum >> 16);					// add carry
	ans = ~sum;
	return ans;
}

void setup_ping_ip_header(struct iphdr *ip,char *dst_addr,char *src_addr){
	ip->ihl = 5;
	ip->version = 4;
	ip->tos = 0;
	ip->tot_len = sizeof(struct iphdr) + sizeof(struct icmphdr);
	ip->id = htons(random());
	ip->ttl = 255;
	ip->protocol = IPPROTO_ICMP;
	ip->saddr = inet_addr(src_addr);
	ip->daddr = inet_addr(dst_addr);
	ip->check = 0;
}

void setup_ping_icmp_header(struct icmphdr *icmp){
	icmp->type = ICMP_ECHO;
	icmp->code = 0;
	icmp->un.echo.id = 0;
	icmp->un.echo.sequence = 0;
	icmp->checksum = 0;
}

/* // issue: dont use getip()
char* getip(){
	char buffer[256];
	struct hostent *h;
	gethostname(buffer, 256);
#ifdef DEBUG
	printf("hostname %s\n",buffer);
#endif
	h = gethostbyname(buffer);
	return inet_ntoa(*(struct in_addr *)h->h_addr);
}
*/

int ping(char *dst_addr,char *src_addr,int timeout_ms){
	struct iphdr *ip;
	struct iphdr *ip_reply;
	struct icmphdr *icmp;
	struct icmphdr *icmp_reply;
	struct sockaddr_in connection;
	unsigned char packet[100];
	unsigned char buffer[100];
	int sockfd;
	int optval;
	int addrlen;
	fd_set socket_set;
	struct timeval timeout;
	int timer_ms;
	int received;
	
	// Check root privelidges
	if(getuid()){
		fprintf(stderr, "%s::%s(%d): root privelidges needed\n", __FILE__, __FUNCTION__, __LINE__);
		return -1;
	}
	
	ip 			= (struct iphdr *)(packet);
	icmp 		= (struct icmphdr *)((packet) + sizeof(struct iphdr));
	ip_reply 	= (struct iphdr *)(buffer);
	icmp_reply 	= (struct icmphdr *)((buffer) + sizeof(struct iphdr));

	// Open socket
	if((sockfd 	= socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0){
		fprintf(stderr, "%s::%s(%d): fail to create socket\n", __FILE__, __FUNCTION__, __LINE__);		
		return -1;
	}
	
	// Set socket option (IP Header Included)
	setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, &optval, sizeof(int));
	
	memset(packet,0,sizeof(packet));
	// Setup ip header
	setup_ping_ip_header(ip,dst_addr,src_addr);
	// Setup icmp header
	setup_ping_icmp_header(icmp);
	// Calculate sum
	icmp->checksum 	= in_cksum((unsigned short *)icmp, sizeof(struct icmphdr));
	ip->check 		= in_cksum((unsigned short *)ip, sizeof(struct iphdr));
	
	connection.sin_family 		= AF_INET;
	connection.sin_addr.s_addr 	= inet_addr(dst_addr);
//	bind(sockfd,(struct sockaddr *)&connection,sizeof(connection));
	// Send packet	
	if(sendto(sockfd, packet,ip->tot_len, 0, (struct sockaddr *)&connection, sizeof(struct sockaddr)) < 0){
		fprintf(stderr, "%s::%s(%d): send fail\n", __FILE__, __FUNCTION__, __LINE__);
		perror("sendto: ");
		close(sockfd);
		return -1;
	}
	
	// Listen for response
	addrlen = sizeof(connection);
	timer_ms = 0;
	while(timer_ms < timeout_ms){
		FD_ZERO(&socket_set);
		FD_SET(sockfd, &socket_set);
		timeout.tv_sec = 0;
	  	timeout.tv_usec = 0;
	  	if(select(sockfd+1, &socket_set, NULL, NULL, &timeout) > 0){
	  		if(FD_ISSET(sockfd,&socket_set)){
	  			if((received = recvfrom( sockfd
	  									, buffer
	  									, sizeof(struct iphdr)+sizeof(struct icmphdr)
	  									, 0
	  									, (struct sockaddr *)&connection
	  									, (socklen_t *)&addrlen)) < 0
	  									){
						fprintf(stderr, "%s::%s(%d): recv fail\n", __FILE__, __FUNCTION__, __LINE__);
						close(sockfd);
						return -1;
	    		}
	    		else{
	    			if((ip_reply->saddr == ip->daddr) && (ip_reply->daddr == ip->saddr) && (icmp_reply->type == ICMP_ECHOREPLY)){
	    				close(sockfd);
	  					return timer_ms;
	  				}
	  			}
	  		}
		}
		usleep(1000);
		timer_ms++;
	}
	close(sockfd);
	return -1;
}


/********************* Example
int main(void){
	int ret;
	ret = ping("200.1.1.1","200.1.1.51",500);
	printf("ret = %d\n",ret);
	return 0;
}
*/

//eof

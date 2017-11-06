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
#include <string.h>
#include <sys/time.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <unistd.h>

static unsigned short incksum(unsigned short *ptr16, int byteslen){
    register long sum;
    u_short oddbyte;
    register u_short answer;
 
    sum = 0;
    while(byteslen > 1){
        sum += *ptr16++;
        byteslen -= 2;
    }
 
    if (byteslen == 1){
        oddbyte = 0;
        *((u_char *) & oddbyte) = *(u_char *) ptr16;
        sum += oddbyte;
    }
 
    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);
    answer = ~sum;
 
    return (answer);
}

int ping(char *src_addr, char *dst_addr, int payloadlen, int timeout_ms){
	int sockfd;
	int optval;
    unsigned long daddr;
    unsigned long saddr;
    int payload_size = 0;
    int sent_size;

    int packet_size;
	char *packet;
 
	struct iphdr *ip;
	struct icmphdr *icmp;	
	struct sockaddr_in conn;

	struct iphdr *ip_reply;
	struct icmphdr *icmp_reply;
	fd_set socket_set;
	struct timeval timeout;
	int timer_ms;
	int received;
	int addrlen;	

    saddr = inet_addr(src_addr);
    daddr = inet_addr(dst_addr);
    payload_size = payloadlen;

    // Open socket
    // Raw socket: IPPROTO_RAW, kernel wont fill in the correct ICMP checksum
    // Alternative: IPPROTO_ICMP, kernel will fill in the correct ICMP header checksum
    if((sockfd 	= socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0){
		fprintf(stderr, "%s::%s(%d): fail to create socket\n", __FILE__, __FUNCTION__, __LINE__);		
		perror("Create socket: ");
		return -1;
	}

	// Set socket option to include IP Header
	optval = 1;
	if(setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, (const char*)&optval, sizeof(optval)) == -1){
        fprintf(stderr, "%s::%s(%d)\n", __FILE__, __FUNCTION__, __LINE__);
        perror("Setsockopt: ");
        return -1;
    }	

    // Calculate total packet size
    packet_size = sizeof (struct iphdr) + sizeof (struct icmphdr) + payload_size;
    packet = (char *)malloc(packet_size);
    if (packet == NULL) {
    	fprintf(stderr, "%s::%s(%d)\n", __FILE__, __FUNCTION__, __LINE__);
        perror("out of memory");
        close(sockfd);
        return (0);
    }

    // Setup ip header
    ip = (struct iphdr *) packet;
    icmp = (struct icmphdr *) (packet + sizeof (struct iphdr));
    memset (packet, 0, packet_size);
    ip->ihl = 5;
    ip->version = 4;
    ip->tos = 0;
    ip->tot_len = htons(packet_size);
    ip->id = random();
    ip->ttl = 255;    
    ip->frag_off = 0;
    ip->protocol = IPPROTO_ICMP;
    ip->saddr = saddr;
    ip->daddr = daddr;
    //ip->check = incksum ((u16 *) ip, sizeof (struct iphdr));
    //ip->check = 0;

    // Setup icmp header
    icmp->type = ICMP_ECHO;
    icmp->code = 0;
    icmp->un.echo.id = random();  
    icmp->un.echo.sequence = random();
 	//icmp->checksum = 0;

 	// Set socket connection
	conn.sin_family 		= AF_INET;
	conn.sin_addr.s_addr 	= daddr;	
	memset(&conn.sin_zero, 0, sizeof (conn.sin_zero));

	// Random payload and recalculate checksum
	memset(packet + sizeof(struct iphdr) + sizeof(struct icmphdr), random() % 255, payload_size);
    icmp->checksum = 0;
    icmp->checksum = incksum((unsigned short *)icmp, sizeof(struct icmphdr) + payload_size);

    // Tx
    if ((sent_size = sendto(sockfd, packet, packet_size, 0, (struct sockaddr*)&conn, sizeof (conn))) < 1){
		fprintf(stderr, "%s::%s(%d)\n", __FILE__, __FUNCTION__, __LINE__);
		perror("sendto: ");
		free(packet);
		close(sockfd);
		return -1;
    }

    // Rx setup
    ip_reply 	= (struct iphdr *)(packet);
	icmp_reply 	= (struct icmphdr *)((packet) + sizeof(struct iphdr));
	memset(packet, 0, packet_size);

    // Rx
	addrlen = sizeof(conn);
	timer_ms = 0;
	while(timer_ms < timeout_ms){
		FD_ZERO(&socket_set);
		FD_SET(sockfd, &socket_set);
		// Select with no wait option because need to count and return reply timer
		timeout.tv_sec 	= 0;
	  	timeout.tv_usec = 0;
	  	if(select(sockfd + 1, &socket_set, NULL, NULL, &timeout) > 0){
	  		if(FD_ISSET(sockfd, &socket_set)){
	  			if((received = recvfrom( sockfd
	  									, packet
	  									, sizeof(struct iphdr) + sizeof(struct icmphdr)
	  									, 0
	  									, (struct sockaddr *)&conn
	  									, (socklen_t *)&addrlen)) < 0
	  									){
						fprintf(stderr, "%s::%s(%d)\n", __FILE__, __FUNCTION__, __LINE__);
						perror("recvfrom: ");
						free(packet);
						close(sockfd);
						return -1;
	    		}
	    		else{
	    			// printf("\t ip_reply->saddr: %ul\n", ip_reply->saddr);
	    			// printf("\t ip_reply->daddr: %ul\n", ip_reply->daddr);
	    			// printf("\t ip->saddr: %ul\n", ip->saddr);
	    			// printf("\t ip->daddr: %ul\n", ip->daddr);
	    			// printf("\t icmp_reply->type: %u\n", icmp_reply->type);
	    			// printf("\t ICMP_ECHOREPLY: %u\n", ICMP_ECHOREPLY);	    			
	    			if((ip_reply->saddr == ip->saddr) && (ip_reply->daddr == ip->daddr) && (icmp_reply->type == ICMP_ECHOREPLY)){
	    				free(packet);
	    				close(sockfd);
	  					return timer_ms;
	  				}
	  			}
	  		}
		}
		usleep(1000);
		timer_ms++;
	}

	// Timeout!!
	//fprintf(stderr, "%s::%s(%d): timeout!\n", __FILE__, __FUNCTION__, __LINE__);
	free(packet);
	close(sockfd);
	return -1;    
}


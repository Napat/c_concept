/**
 * @file arp_api.c
 * @author Napat Rungruangbangchan
 * @date 27 September 2017 
 * @brief 
 * @Compiler: gcc(ubuntu 14.04)
 * @License: 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <linux/if_arp.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>

#include "arp_api.h"

static int retrive_inft_info(char* intf_name, struct ifreq* ifr, int* ifindex){
    int sockfd;

    sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (sockfd == -1){
        perror("socket(): ");
        return -1;
    }

    strcpy(ifr->ifr_name, intf_name);
    // Retrieve ethernet interface index
    if (ioctl(sockfd, SIOCGIFINDEX, ifr) == -1){
        perror("SIOCGIFINDEX: ");
        close(sockfd);
        return -1;
    }
    *ifindex = ifr->ifr_ifindex;

    // Retrieve corresponding MAC
    if (ioctl(sockfd, SIOCGIFHWADDR, ifr) == -1){
        perror("SIOCGIFHWADDR: ");
        close(sockfd);
        return -1;
    }

    //printf("interface index is %d\r\n", ifr->ifr_ifindex);
    //printf("ifr_hwaddr is %2x:%2x:%2x:%2x:%2x:%2x\r\n", ifr->ifr_hwaddr.sa_data[0]
    //                                          , ifr->ifr_hwaddr.sa_data[1]
    //                                          , ifr->ifr_hwaddr.sa_data[2]
    //                                          , ifr->ifr_hwaddr.sa_data[3]
    //                                          , ifr->ifr_hwaddr.sa_data[4]
    //                                          , ifr->ifr_hwaddr.sa_data[5]);

    close(sockfd);
    return 0;
}

static int convert_ipstr_to_sockaddr(uint8_t* source_ip, uint8_t* ip_array_out){
    uint8_t index;

    /* A pointer to the next digit to process. */
    uint8_t* start;

    if(source_ip == NULL){
        ip_array_out[0] = 0;
        ip_array_out[1] = 0;
        ip_array_out[2] = 0;
        ip_array_out[3] = 0;
        return 0;
    }

    start = source_ip;
    for (index=0; index<IPV4_LENGTH; index++){
        /* The digit being processed. */
        char c;
        /* The value of this byte. */
        int n = 0;
        while(1){
            c = *start;
            start++;
            if(c >= '0' && c <= '9'){
                n *= 10;
                n += c - '0';
            }
            /* We insist on stopping at "." if we are still parsing
                the first, second, or third numbers. If we have reached
                the end of the numbers, we will allow any character. */
            else if ((index < 3 && c == '.') || index == 3) {
                break;
            }else{
                return 0;
            }
        }
        if (n >= 256) {
            return 0;
        }
        ip_array_out[index] = n;
        //printf("ip_array_out[%u] %u\r\n", index, ip_array_out[index]);
    }

    return 1;
}

// ex. 0xFFFFFF0A -> 10.255.255.255
static bool convert_inaddr_to_ipstr(uint32_t ipv4, char* out){
    uint32_t pout_ip[4] = {0};

    pout_ip[0] = ipv4 & 0xFF;
    pout_ip[1] = (ipv4 >> 8) & 0xFF;
    pout_ip[2] = (ipv4 >> 16) & 0xFF;
    pout_ip[3] = (ipv4 >> 24) & 0xFF;
    

    sprintf( out, "%u.%u.%u.%u", pout_ip[0], pout_ip[1], pout_ip[2], pout_ip[3] );
    return true;
}

// who has [target_ip], tell [source_ip]
int32_t arp_request(char* intf_name, uint8_t* target_ip, uint8_t* source_ip){
    int ret;
    int index;
    int sockfd;
    unsigned char buffer[BUF_SIZE];
    struct ifreq ifr;
    int ifindex;
    struct ethhdr *send_req = (struct ethhdr *)buffer;
    struct arp_header *arp_req = (struct arp_header *)(buffer+ETH2_HEADER_LEN);
    struct sockaddr_ll socket_address;
    unsigned char src_ip[IPV4_LENGTH];
    unsigned char tar_ip[IPV4_LENGTH];

    memset(buffer, 0x00, BUF_SIZE);

    retrive_inft_info(intf_name, &ifr, &ifindex);

    for(index = 0; index < 6; index++){
        send_req->h_dest[index] = (unsigned char)0xff;
        arp_req->target_mac[index] = (unsigned char)0x00;
        // Filling the source  mac address in the header
        send_req->h_source[index] = (unsigned char)ifr.ifr_hwaddr.sa_data[index];
        arp_req->sender_mac[index] = (unsigned char)ifr.ifr_hwaddr.sa_data[index];
        socket_address.sll_addr[index] = (unsigned char)ifr.ifr_hwaddr.sa_data[index];
    }

    // Debug
    // printf("Successfully got eth1 MAC address: %02X:%02X:%02X:%02X:%02X:%02X\n",
    //          send_req->h_source[0],send_req->h_source[1],send_req->h_source[2],
    //          send_req->h_source[3],send_req->h_source[4],send_req->h_source[5]);
    // printf(" arp_reqMAC address: %02X:%02X:%02X:%02X:%02X:%02X\n",
    //             arp_req->sender_mac[0],arp_req->sender_mac[1],arp_req->sender_mac[2],
    //             arp_req->sender_mac[3],arp_req->sender_mac[4],arp_req->sender_mac[5]);
    // printf("socket_address MAC address: %02X:%02X:%02X:%02X:%02X:%02X\n",
    //             socket_address.sll_addr[0],socket_address.sll_addr[1],socket_address.sll_addr[2],
    //             socket_address.sll_addr[3],socket_address.sll_addr[4],socket_address.sll_addr[5]);

    // Prepare sockaddr_ll
    socket_address.sll_family = AF_PACKET;
    socket_address.sll_protocol = htons(ETH_P_ARP);
    socket_address.sll_ifindex = ifindex;
    socket_address.sll_hatype = htons(ARPHRD_ETHER);
    socket_address.sll_pkttype = (PACKET_BROADCAST);
    socket_address.sll_halen = MAC_LENGTH;
    socket_address.sll_addr[6] = 0x00;
    socket_address.sll_addr[7] = 0x00;

    // Setting protocol of the packet
    send_req->h_proto = htons(ETH_P_ARP);

    // Creating ARP request 
    arp_req->hardware_type = htons(HW_TYPE);
    arp_req->protocol_type = htons(ETH_P_IP);
    arp_req->hardware_len = MAC_LENGTH;
    arp_req->protocol_len =IPV4_LENGTH;
    arp_req->opcode = htons(ARP_REQUEST);

    convert_ipstr_to_sockaddr(source_ip, src_ip);
    convert_ipstr_to_sockaddr(target_ip, tar_ip);
    for(index=0; index<IPV4_LENGTH; index++){
        arp_req->sender_ip[index]=src_ip[index];
        arp_req->target_ip[index]=tar_ip[index];
        //arp_req->sender_ip[index]=(unsigned char)source_ip[index];
        //arp_req->target_ip[index]=(unsigned char)target_ip[index];
    }
    // Submit request for a raw socket descriptor.
    if ((sockfd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) < 0){
        perror("socket() failed: ");
        return -1;//return (EXIT_FAILURE);
    }

    buffer[32]=0x00;
    ret = sendto(sockfd, buffer, BUF_SIZE, 0, (struct  sockaddr*)&socket_address, sizeof(socket_address));
    if (ret == -1){
        perror("sendto(): ");
        close(sockfd);
        return -1;
    }

    // printf(" Sent the ARP REQ \n\t");
    // for(index=0;index<BUF_SIZE;index++){
    //     printf("%02X ",buffer[index]);
    //     if(index % 16 ==0 && index !=0){
    //      printf("\n\t");
    //     }
    // }
    close(sockfd);
    return 0;
}

int32_t arp_reply_bcastip(char* intf_name, uint8_t* source_ip){
    int fd;
    struct ifreq ifr;
    char bcast_ipstr[16];

    fd = socket(AF_INET, SOCK_DGRAM, 0);

    /* I want to get an IPv4 IP address */
    ifr.ifr_broadaddr.sa_family = AF_INET;

    strcpy(ifr.ifr_name, intf_name);

    if (ioctl(fd, SIOCGIFBRDADDR, &ifr) == -1){
        perror("SIOCGIFBRDADDR: ");
        close(fd);
        return -1;
    }

    close(fd);

    /* display result */
    //printf("ifr_broadaddr is ");
    //int i;
    //for(i=0; i<14; i++){
    //  printf("%u.", (unsigned char)ifr.ifr_broadaddr.sa_data[i]);
    //}
    //printf("\r\n\r\n");

    struct sockaddr_in* tmp_ifr = (struct sockaddr_in*)&ifr.ifr_broadaddr;
    //printf("sin_addr is %u\r\n", tmp_ifr->sin_addr.s_addr);

    convert_inaddr_to_ipstr(tmp_ifr->sin_addr.s_addr, bcast_ipstr);
    //printf("Bcast address %s\r\n", bcast_ipstr);

    return arp_reply_target(intf_name, source_ip, bcast_ipstr);
}

int32_t arp_reply(char* intf_name, uint8_t* source_ip){
    return arp_reply_target(intf_name, source_ip, "0.0.0.0");
}

// tx: [source_ip] is at [mac address of intf_name]
int32_t arp_reply_target(char* intf_name, uint8_t* source_ip, uint8_t* target_ip){
    int ret;
    int sockfd;
    unsigned char buffer[BUF_SIZE];
    struct sockaddr_ll socket_address;
    struct ethhdr *send_buf = (struct ethhdr *)buffer;
    struct arp_header *arp_buf = (struct arp_header *)(buffer+ETH2_HEADER_LEN);
    struct ifreq ifr;
    int ifindex;
    int index;
    unsigned char src_ip[IPV4_LENGTH];
    unsigned char tar_ip[IPV4_LENGTH];

    memset(buffer, 0x00, BUF_SIZE);

    retrive_inft_info(intf_name, &ifr, &ifindex);

    sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
    if (sockfd < 0){
        perror("socket");
        return -1;
    }

    for (index = 0; index < 6; index++){

        send_buf->h_dest[index] = (unsigned char)0xff;
        arp_buf->target_mac[index] = (unsigned char)0x00;
        /* Filling the source  mac address in the header*/
        send_buf->h_source[index] = (unsigned char)ifr.ifr_hwaddr.sa_data[index];
        arp_buf->sender_mac[index] = (unsigned char)ifr.ifr_hwaddr.sa_data[index];
        socket_address.sll_addr[index] = (unsigned char)ifr.ifr_hwaddr.sa_data[index];
    }

    // Debug
    // printf("Successfully got eth1 MAC address: %02X:%02X:%02X:%02X:%02X:%02X\n",
    //          send_buf->h_source[0],send_buf->h_source[1],send_buf->h_source[2],
    //          send_buf->h_source[3],send_buf->h_source[4],send_buf->h_source[5]);
    // printf(" arp_reqMAC address: %02X:%02X:%02X:%02X:%02X:%02X\n",
    //             arp_buf->sender_mac[0],arp_buf->sender_mac[1],arp_buf->sender_mac[2],
    //             arp_buf->sender_mac[3],arp_buf->sender_mac[4],arp_buf->sender_mac[5]);
    // printf("socket_address MAC address: %02X:%02X:%02X:%02X:%02X:%02X\n",
    //             socket_address.sll_addr[0],socket_address.sll_addr[1],socket_address.sll_addr[2],
    //             socket_address.sll_addr[3],socket_address.sll_addr[4],socket_address.sll_addr[5]);

    // Prepare sockaddr_ll
    socket_address.sll_family = AF_PACKET;
    socket_address.sll_protocol = htons(ETH_P_ARP);
    socket_address.sll_ifindex = ifindex;
    socket_address.sll_hatype = htons(ARPHRD_ETHER);
    socket_address.sll_pkttype = (PACKET_BROADCAST);
    socket_address.sll_halen = MAC_LENGTH;
    socket_address.sll_addr[6] = 0x00;
    socket_address.sll_addr[7] = 0x00;

    // Setting protocol of the packet
    send_buf->h_proto = htons(ETH_P_ARP);

    // Creating ARP reply 
    arp_buf->hardware_type = htons(HW_TYPE);
    arp_buf->protocol_type = htons(ETH_P_IP);
    arp_buf->hardware_len = MAC_LENGTH;
    arp_buf->protocol_len =IPV4_LENGTH;
    arp_buf->opcode = htons(ARP_REPLY);

    convert_ipstr_to_sockaddr(source_ip, src_ip);
    convert_ipstr_to_sockaddr(target_ip, tar_ip);
    for(index=0; index<IPV4_LENGTH; index++){
        arp_buf->sender_ip[index] = src_ip[index];
        arp_buf->target_ip[index] = tar_ip[index];
    }
    // Submit request for a raw socket descriptor.
    //if ((sockfd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) < 0){
    //  perror("socket() failed: ");
    //  return -1;//return (EXIT_FAILURE);
    //}

    buffer[32]=0x00;
    ret = sendto(sockfd, buffer, BUF_SIZE, 0, (struct  sockaddr*)&socket_address, sizeof(socket_address));
    if (ret == -1){
        perror("sendto(): ");
        close(sockfd);
        return -1;
    }
    close(sockfd);
    return 0;
}

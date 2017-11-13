/**
 * @file arp_api.h
 * @author Napat Rungruangbangchan
 * @date 27 September 2017 
 * @brief 
 * @Compiler: gcc(ubuntu 14.04)
 * @License: 
 */

#ifndef __ARP_API_H__
#define __ARP_API_H__

#include <stdint.h>
#include <stdbool.h>
//#include <linux/types.h>

#define PROTO_ARP 		0x0806
#define ETH2_HEADER_LEN 14
#define HW_TYPE 		1
#define PROTOCOL_TYPE 	0x800
#define MAC_LENGTH 		6
#define IPV4_LENGTH 	4
#define ARP_REQUEST 	0x01
#define ARP_REPLY 		0x02
#define BUF_SIZE 		60

struct arp_header{
        unsigned short 	hardware_type;
        unsigned short 	protocol_type;
        unsigned char 	hardware_len;
        unsigned char  	protocol_len;
        unsigned short 	opcode;
        unsigned char 	sender_mac[MAC_LENGTH];
        unsigned char 	sender_ip[IPV4_LENGTH];
        unsigned char 	target_mac[MAC_LENGTH];
        unsigned char 	target_ip[IPV4_LENGTH];
};

// who has [target_ip], tell [source_ip]
int32_t arp_request(char* intf_name, uint8_t* target_ip, uint8_t* source_ip);

// tx: [source_ip] is at [mac address of intf_name]
int32_t arp_reply_bcastip(char* intf_name, uint8_t* source_ip);
int32_t arp_reply(char* intf_name, uint8_t* source_ip);
int32_t arp_reply_target(char* intf_name, uint8_t* source_ip, uint8_t* target_ip);

#endif /* __ARP_API_H__ */
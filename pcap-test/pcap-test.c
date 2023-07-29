#include <stdio.h>          // 표준 입출력 관련 라이브러리
#include <stdlib.h>         // 일반적인 유틸리티 함수들을 포함하는 라이브러리
#include <string.h>         // 문자열 관련 함수들을 포함하는 라이브러리
#include <unistd.h>         // UNIX 운영 체제 API 함수들을 포함하는 라이브러리
#include <arpa/inet.h>      // IP 주소 변환 함수들을 포함하는 라이브러리
#include <sys/socket.h>     // 소켓 관련 함수들을 포함하는 라이브러리
#include <netinet/if_ether.h> // 이더넷 헤더 정의를 포함하는 라이브러리
#include <netinet/ip.h>     // IP 헤더 정의를 포함하는 라이브러리
#include <netinet/tcp.h>    // TCP 헤더 정의를 포함하는 라이브러리

#define MAX_PACKET_SIZE 65536

// 이더넷 맥 주소를 출력하는 함수
void print_mac(const uint8_t* mac) {
    printf("%02x:%02x:%02x:%02x:%02x:%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}

// IP 주소를 출력하는 함수
void print_ip(uint32_t ip) {
    struct in_addr addr;
    addr.s_addr = ip;
    printf("%s", inet_ntoa(addr));
}

// 패킷 페이로드를 16진수 형태로 출력하는 함수 (최대 10바이트까지 출력)
void print_payload(const uint8_t* payload, int payload_length) {
    printf("Payload (Hexadecimal, max 10 bytes): ");
    for (int i = 0; i < payload_length && i < 10; ++i) {
        printf("%02x ", payload[i]);
    }
    printf("\n");
}

int main() {
    int sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL)); // 소켓 생성 (모든 패킷 수신)
    if (sockfd < 0) {
        perror("Failed to create socket");
        return 1;
    }

    while (1) {
        uint8_t buffer[MAX_PACKET_SIZE];
        ssize_t packet_size = recv(sockfd, buffer, sizeof(buffer), 0); // 패킷 수신
        if (packet_size < 0) {
            perror("Failed to receive packet");
            break;
        }

        // 이더넷 헤더
        struct ethhdr* eth_hdr = (struct ethhdr*)buffer;

        // IP 패킷인지 확인
        if (ntohs(eth_hdr->h_proto) == ETH_P_IP) {
            // IP 헤더
            struct iphdr* ip_hdr = (struct iphdr*)(buffer + sizeof(struct ethhdr));

            // TCP 패킷인지 확인
            if (ip_hdr->protocol == IPPROTO_TCP) {
                // TCP 헤더
                struct tcphdr* tcp_hdr = (struct tcphdr*)(buffer + sizeof(struct ethhdr) + ip_hdr->ihl * 4);

                // 페이로드 (데이터)
                int payload_offset = sizeof(struct ethhdr) + ip_hdr->ihl * 4 + tcp_hdr->doff * 4;
                int payload_length = packet_size - payload_offset;
                if (payload_length > 0) {
                    printf("smac: ");
                    print_mac(eth_hdr->h_source); // 소스 MAC 주소 출력
                    printf("\n");
                    printf("dmac: ");
                    print_mac(eth_hdr->h_dest); // 대상 MAC 주소 출력
                    printf("\n");
                    printf("Source IP: ");
                    print_ip(ip_hdr->saddr); // 소스 IP 주소 출력
                    printf("\n");
                    printf("Destination IP: ");
                    print_ip(ip_hdr->daddr); // 대상 IP 주소 출력
                    printf("\n");
                    printf("Source Port: %u, Destination Port: %u\n", ntohs(tcp_hdr->source), ntohs(tcp_hdr->dest)); // 소스 및 대상 포트 출력
                    print_payload(buffer + payload_offset, payload_length); // 페이로드 출력
                    printf("\n");
                }
            }
        }
    }

    close(sockfd); // 소켓 닫기
    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main()
{
    struct ifaddrs *addr, *intf;
    char hostname[NI_MAXHOST];
    int family, s;
    
    if (getifaddrs(&intf) == -1) {
        perror("getifaddrs");
        exit(EXIT_FAILURE);
    }

    for (addr = intf; addr != NULL; addr = addr->ifa_next) {
        family = addr->ifa_addr->sa_family;
        //AF_INET is the address family for IPv4
        if (family == AF_INET) {
          //getnameinfo enables name resolution
          s = getnameinfo(addr->ifa_addr, 
                          sizeof(struct sockaddr_in),
                          hostname, 
                          NI_MAXHOST, 
                          NULL, 
                          0, 
                          NI_NUMERICHOST);
          printf("<interface>: %s \t <address> %s\n", addr->ifa_name, hostname);
        }
    }
    return 0;
}

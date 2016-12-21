/**
	Library          : Cross Platform Native Sockets
	Author           : Gokan EKINCI
	Licence          : CC-BY-NC-ND
*/
#ifndef G_SOCKET_HEADER
#define G_SOCKET_HEADER

#ifdef __unix__
	#include <netinet/in.h>
	#define SCKT_ERROR -1
#endif /* __unix__ */
#ifdef _WIN32
	#include <ws2tcpip.h>
	#define SCKT_ERROR SOCKET_ERROR
#endif /* _WIN32 */

/* Common constants */
typedef struct sockaddr_in6 SockaddrImpl;
#define __OUT__
#define __INOUT__


/**
 * TCP Socket
 */
typedef struct TcpSocket TcpSocket;

/**
 * TCP Server
 */
typedef struct TcpServer TcpServer;

/**
 * UDP Socket
 */
typedef struct UdpSocket UdpSocket;

/**
 * Multicast Socket (it uses UDP protocol)
 */
typedef struct MulticastSocket MulticastSocket;

/**
 * A Generic sockaddr
 */
typedef struct GenericSockAddr GenericSockAddr;

/**
 * Represent a Network Interface for a listener using recv() and recvfrom() functions
 */
typedef struct GenericSockAddr BindInterface;

/**
 * UDP Endpoint. Destination informations for sendto() and Sender informations for recvfrom() 
 */
typedef struct GenericSockAddr UdpEndpoint;

/**
 * Contains informations about the multicast group
 */
typedef struct MulticastGroup MulticastGroup;



struct TcpSocket {
	int _id;
	int _isClosed;
	/* TODO  _closeLock; */
	
	/**
	 * Send data
	 *
	 * @param tcpSocket      Current tcpSocket
	 * @param buffer         The data to send
	 * @param bufferLength   Size of buffer
	 * @return               0 if no error occured, SCKT_ERROR (-1) otherwise
	 */
	int (*send) (TcpSocket* tcpSocket, const char* buffer, size_t bufferLength);
	
	/**
	 * Receive data
	 *
	 * @param tcpSocket      Current tcpSocket
	 * @param buffer         The data to receive
	 * @param bufferLength   Max size of data to receive (max bytes)
	 * @return               0 if no error occured, SCKT_ERROR (-1) otherwise
	 */
	int (*recv) (TcpSocket* tcpSocket, __OUT__ char* buffer, size_t bufferLength);
	
	/**
	 * Setting shutdown options
	 *
	 * @param tcpSocket    Current tcpSocket
	 * @param mode         Shutdown mode
	 * @return             0 if no error occured, SCKT_ERROR (-1) otherwise
	 */
	int (*shutdown) (TcpSocket* tcpSocket, int mode);
	
	/**
	 * Close socket
	 *
	 * @param  tcpSocket    Current tcpSocket
	 * @return              0 if no error occured, SCKT_ERROR (-1) otherwise
	 */
	int (*close) (TcpSocket* tcpSocket);
};

struct UdpSocket {
	int _id;
	int _isClosed;
	/* TODO  _closeLock; */
	
	/**
	 * Send data to udp endpoint
	 *
	 * @param udpSocket      Current udpSocket
	 * @param buffer         The data to send
	 * @param bufferLength   Size of buffer
	 * @param udpEndpoint    Destination info (this parameter must NOT be NULL)
	 * @return               0 if no error occured, SCKT_ERROR (-1) otherwise
	 */
	int (*sendto) (UdpSocket* udpSocket, const char* buffer, size_t bufferLength, const UdpEndpoint* udpEndpoint);
	
	/**
	 * Receive data from udp endpoint
	 *
	 * @param udpSocket      Current udpSocket
	 * @param buffer         The data to receive
	 * @param bufferLength   Max size of data to receive (max bytes)
	 * @param udpEndpoint    Transmitter info (this parameter maybe NULL if this information is not used)
	 * @return               0 if no error occured, SCKT_ERROR (-1) otherwise
	 */
	int (*recvfrom) (UdpSocket* udpSocket, __OUT__ char* buffer, size_t bufferLength, __OUT__ UdpEndpoint* udpEndpoint);
 
 	/**
	 * Setting shutdown options
	 *
	 * @param udpSocket   Current udpSocket
	 * @param mode        Shutdown mode
	 * @return            0 if no error occured, SCKT_ERROR (-1) otherwise
	 */
	int (*shutdown) (UdpSocket* udpSocket, int mode);
	
	/**
	 * Close socket
	 *
	 * @param udpSocket   Current udpSocket
	 * @return            0 if no error occured, SCKT_ERROR (-1) otherwise
	 */
	int (*close) (UdpSocket* udpSocket);
};

struct TcpServer {
	int _id;
	int _isClosed;
	/* TODO  _closeLock; */
	
	/**
	 * Accept a new TCP socket client
	 *
	 * @param tcpServer                     Current tcpServer
	 * @param tcpSocket                     Setting values of accepted tcpSocket client
	 * @param receivedClientInformations    Setting values of received client information, if this param is NULL it won't be set
	 * @return                              0 if no error occured, SCKT_ERROR (-1) otherwise
	 */
	int (*accept) (TcpServer* tcpServer, __OUT__ TcpSocket* tcpSocket, __OUT__ GenericSockAddr* receivedClientInformations);
	
	/**
	 * Setting shutdown options
	 *
	 * @param tcpServer   Current tcpServer
	 * @param mode        Shutdown mode
	 * @return            0 if no error occured, SCKT_ERROR (-1) otherwise
	 */
	int (*shutdown) (TcpServer* tcpServer, int mode);
	
	/**
	 * Close tcp server socket
	 *
	 * @param tcpServer   Current tcpServer
	 * @return            0 if no error occured, SCKT_ERROR (-1) otherwise
	 */
	int (*close) (TcpServer* tcpServer);
};

struct MulticastSocket {
	int _id;
	int _isClosed;
	/* TODO  _closeLock; */
	
	/**
	 * Determine address family of  `_sockaddrMulticastGroup`
	 */
	int _addressFamily;
	
	/**
	 * Used to determine multicast group address for sending
	 */
	SockaddrImpl  _sockaddrMulticastGroup;

	/**
	 * Send data to multicast group
	 *
	 * @param multicastSocket    Current multicastSocket
	 * @param buffer             The data to send
	 * @param bufferLength       Size of buffer
	 * @return                   0 if no error occured, SCKT_ERROR (-1) otherwise
	 */
	int (*send) (MulticastSocket* multicastSocket, const char* buffer, size_t bufferLength);
		
	/**
	 * Receive data from multicast group
	 *
	 * @param multicastSocket    Current multicastSocket
	 * @param buffer             The data to receive
	 * @param bufferLength       Max size of data to receive (max bytes)
	 * @param udpEndpoint        Transmitter info (this parameter maybe NULL if this information is not used)
	 * @return                   0 if no error occured, SCKT_ERROR (-1) otherwise
	 */
	int (*recvfrom) (MulticastSocket* multicastSocket, __OUT__ char* buffer, size_t bufferLength, __OUT__ UdpEndpoint* udpEndpoint);
	
	/**
	 * Send data to specific udp endpoint
	 *
	 * @param multicastSocket      Current multicastSocket
	 * @param buffer               The data to send
	 * @param bufferLength         Size of buffer
	 * @param udpEndpoint          Destination info (this parameter must NOT be NULL)
	 * @return                     0 if no error occured, SCKT_ERROR (-1) otherwise
	 */
	int (*sendto) (MulticastSocket* multicastSocket, const char* buffer, size_t bufferLength, const UdpEndpoint* udpEndpoint);

	/**
	 * Setting shutdown options
	 *
	 * @param multicastSocket   Current udpSocket
	 * @param mode              Shutdown mode
	 * @return                  0 if no error occured, SCKT_ERROR (-1) otherwise
	 */
	int (*shutdown) (MulticastSocket* multicastSocket, int mode);
	
	/**
	 * Close socket
	 *
	 * @param multicastSocket   Current udpSocket
	 * @return                  0 if no error occured, SCKT_ERROR (-1) otherwise
	 */
	int (*close) (MulticastSocket* multicastSocket);
};

struct GenericSockAddr {
	int addressFamily;
	char ip[INET6_ADDRSTRLEN];
	unsigned short port;
};

struct MulticastGroup {
	int addressFamily;
	char ipGroup[INET6_ADDRSTRLEN];
	char ipLocal[INET6_ADDRSTRLEN];
	unsigned short port;
};

/**
 * Use it when starting a program (Needed for Windows)
 *
 * @return    0 if no error occured, SCKT_ERROR (-1) otherwise
 */
int Socket_init_resources(void);



/**
 * Use it when closing a program (Needed for Windows)
 *
 * @return    0 if no error occured, SCKT_ERROR (-1) otherwise
 */
int Socket_close_resources(void);



/**
 * Init a TcpSocket
 *
 * @param tcpSocket               tcpSocket to initialize
 * @param addressFamily           addressFamily (AF_INET for IPv4, AF_INET6 for IPv6)
 * @param ip                      server destination ip address, allowed values: IPv4 format, IPv6 format
 * @param port                    server destination port number
 * @param bindInterface           if specific network interface is used
 * @return                        0 if no error occured, SCKT_ERROR (-1) otherwise
 */
int TcpSocket_init(__OUT__ TcpSocket* tcpSocket, int addressFamily, const char* ip, unsigned short port, const BindInterface* bindInterface);


/**
 * Init a TcpServer
 *
 * @param tcpServer               tcpServer to initialize
 * @param addressFamily           addressFamily (AF_INET for IPv4, AF_INET6 for IPv6)
 * @param ip                      IP address to bind, allowed values: IPv4 format, IPv6 format or INADDR_ANY constant
 * @param port                    Port number to bind
 * @param maxWaitingConnections   Maximum number of waiting connections
 * @return                        0 if no error occured, SCKT_ERROR (-1) otherwise
 */
int TcpServer_init(__OUT__ TcpServer* tcpServer, int addressFamily, const char* ip, unsigned short port, int maxWaitingConnections);



/**
 * Init a UdpSocket
 *
 * @param udpSocket            udpSocket to initialize
 * @param addressFamily        addressFamily (AF_INET for IPv4, AF_INET6 for IPv6)
 * @param bindInterface        if specific network interface is used. You must bind your {@link UdpSocket} if it use {@link UdpSocket#recvfrom} . Read: http://stackoverflow.com/questions/28164563/udp-client-does-not-receive-data-without-bind
 * @return                     0 if no error occured, SCKT_ERROR (-1) otherwise
 */
int UdpSocket_init(__OUT__ UdpSocket* udpSocket, int addressFamily, const BindInterface* bindInterface);



/**
 * Init a MulticastSocket
 *
 * @param multicastSocket      multicastSocket to initialize
 * @param multicastGroup       Informations about multicast group
 * @param reuseaddr            If other instances can receive (1) or not receive (0) a copy of received datagram
 * @param loopback             If sended datagrams are received (1) or not received (0) to localhost
 * @param ttl                  Number of nodes to pass before reaching destination, default is 1, range is 0 to 255
 * @return                     0 if no error occured, SCKT_ERROR (-1) otherwise
 */
int MulticastSocket_init(__OUT__ MulticastSocket* multicastSocket, const MulticastGroup* multicastGroup, unsigned char reuseaddr, unsigned char loopback, unsigned char ttl);




/**
 * Print error message by given error code and message
 * 
 * @param errorCode   error code
 * @param message     message
 */
void SCKT_LOG(int errorCode, const char* message);


#endif /* G_SOCKET_HEADER */

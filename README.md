# GSOCKET by Gokan EKINCI

Gsocket is a socket library for developing programs with TCP/IP, UDP/IP and Multicast protocols.  
  
* Written in C  
* Cross platform: UNIX (Linux, Mac OS), Windows (Vista or later)  
* Compatible with IPv4 and IPv6
* Compatible with C89 or later  
* Compatible with C++98 or later  
* Use an *"object oriented"* pattern  




### Getting started with examples

#### Example of TcpSocket :
  
	#include "gsocket.h"
	#include <stdio.h>

	int main(void) {
		Socket_init_resources();

		TcpSocket c;
		TcpSocket_init(&c, AF_INET, "204.79.197.203", 80, NULL);

		/* Send GET request */
		const char* message = "GET / HTTP/1.1\r\nHost: www.msn.com\r\n\r\n";
		c.send(&c, message, strlen(message) + 1);

		/* Receive response */
		const int max = 2000;
		char buffer[max];
		c.recv(&c, buffer, max);
		printf("%s", buffer);

		c.close(&c);

		printf("\n\n Press any key to exit :)");
		getchar();

		Socket_close_resources();
		return 0;
	}

#### Example of TcpServer       : Example coming soon ! (But you can read gsocket.h, it's very well documented)
#### Example of UdpSocket       : Example coming soon ! (But you can read gsocket.h, it's very well documented)
#### Example of MulticastSocket : Example coming soon ! (But you can read gsocket.h, it's very well documented)



### How to use this library

You need the following files:
  
* The *gsocket.h* header file  
* An implementation for logging, you can use the ***default_logger_implementation.c*** or redefine your own implementation for logging.  
* The core library : ***gsocket-windows-x86.obj*** (for Windows 32bits and 64bits), ***gsocket-linux-x86.o*** coming soon.
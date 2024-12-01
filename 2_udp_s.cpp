/*
This section includes necessary libraries for networking, input/output, and error handling. 
These libraries provide the required functions for creating sockets and managing network communication.
*/
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

using namespace std;

/*
This section sets up the UDP server. The server is configured to listen on a specified port
and can continuously receive and send messages as long as the client is connected.
*/
int main() {
    const int server_port = 5555; // Define the port where the server will listen for incoming messages

    int sock = socket(AF_INET, SOCK_DGRAM, 0); // Create a UDP socket
    if (sock < 0) {
        perror("error creating socket"); // Print an error message if socket creation fails
        return 1; // Exit with error code
    }

    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin)); // Clear the server address structure
    sin.sin_family = AF_INET; // Use IPv4 addressing
    sin.sin_addr.s_addr = INADDR_ANY; // Accept connections on any network interface
    sin.sin_port = htons(server_port); // Convert port number to network byte order

    // Bind the socket to the server's address and port
    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error binding to socket"); // Print an error message if binding fails
        return 1; // Exit with error code
    }

    struct sockaddr_in from;
    unsigned int from_len = sizeof(struct sockaddr_in);
    char buffer[4096];

    // Loop to keep the server running and allow multiple messages to be received and sent
    while (true) {
        int bytes = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &from, &from_len);
        if (bytes < 0) {
            perror("error reading from socket"); // Print an error message if receiving data fails
            continue; // Skip to the next iteration if there's an error
        }

        cout << "The client sent: " << buffer << endl;

        // Send the received message back to the client (echo)
        int sent_bytes = sendto(sock, buffer, bytes, 0, (struct sockaddr *) &from, sizeof(from));
        if (sent_bytes < 0) {
            perror("error writing to socket"); // Print an error message if sending data fails
        }
    }

    close(sock); // Close the socket (This won't be reached since the server is in an infinite loop)
    return 0;
}

/*
This section includes necessary libraries for networking and input/output. 
These libraries provide functions for creating sockets, managing addresses, and handling errors.
*/
#include <limits>  // Required for numeric_limits
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

using namespace std;

/*
This section defines the server's IP address and port number. 
These will be used to send data to the server.
*/
int main() {
    const char* ip_address = "127.0.0.1";
    const int port_no = 5555;

    /*
    This section creates a UDP socket for communication.
    The socket will be used to send and receive data with the server.
    */
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("error creating socket");
    }

    /*
    This section configures the server's address and port.
    The sockaddr_in structure is used to store the server's address information.
    */
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;                   // IPv4 addressing
    sin.sin_addr.s_addr = inet_addr(ip_address); // Convert IP address to binary format
    sin.sin_port = htons(port_no);              // Convert port number to network byte order

    bool continueMessaging = true;
    while (continueMessaging){
            // Prompt the user to enter and send a message
    /*
    This section prepares and sends a message to the server.
    The message will be sent using the sendto() function.
    */
    char data[4096]; // Buffer to store user input
    cout << "Enter a message to send to the server (type 'quit' to exit): ";
    cin.getline(data, sizeof(data)); // Prompt the user to enter a message  
    int data_len = sizeof(data);                // Length of the message
    int sent_bytes = sendto(sock, data, data_len, 0, (struct sockaddr *) &sin, sizeof(sin));
    if (sent_bytes < 0) {
        perror("error writing to socket");
    }

    /*
    This section prepares to receive a response from the server.
    The recvfrom() function will be used to get the server's response.
    */
    struct sockaddr_in from;                    // To store the server's address
    unsigned int from_len = sizeof(struct sockaddr_in);  // Size of the server address structure
    char buffer[4096];                          // Buffer to store the server's response

    /*
    This section receives and displays the server's response.
    The data is received using recvfrom() and printed to the console.
    */
    int bytes = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &from, &from_len);
    if (bytes < 0) {
        perror("error reading from socket");
    }
    cout << "The server sent: " << buffer << endl;

    // Ask the user if they want to continue
    char userChoice;
    cout << "Do you want to send another message? (y/n): ";
    cin >> userChoice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Set loop condition based on user input
    if (userChoice == 'n' || userChoice == 'N') {
        continueMessaging = false;
    }
    }

    /*
    This section closes the socket to release resources.
    This ends the communication with the server.
    */
    close(sock);

    return 0;
}

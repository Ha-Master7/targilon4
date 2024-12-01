/*
This section includes necessary libraries for networking and input/output. 
These libraries provide the required functions for creating sockets, handling IP addresses, and managing the network connection.
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
This section defines the server's IP address and port number. It also starts the process of creating the socket that will be used to communicate with the server.
*/
int main() {
    const char* ip_address = "127.0.0.1";
    const int port_no = 5555;

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("error creating socket");
        return 1;
    }

    /*
    This section configures the server's address using the sockaddr_in structure. 
    The IP address and port number are set up to connect to the server.
    */
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(ip_address);
    sin.sin_port = htons(port_no);

    /*
    This section attempts to connect to the server. 
    If the connection fails, it prints an error message and terminates the process.
    */
    if (connect(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error connecting to server");
        return 1;
    }

    /*
    Loop to continuously send data to the server until the user decides to quit.
    The user is prompted to enter a message, and the message is sent to the server.
    */
    while (true) {
        char data_addr[4096];
        cout << "Enter a message to send to the server (type 'quit' to exit): ";
        cin.getline(data_addr, sizeof(data_addr));

        // Check if the user wants to quit
        if (strcmp(data_addr, "quit") == 0) {
            break;
        }

        int data_len = strlen(data_addr);
        int sent_bytes = send(sock, data_addr, data_len, 0);
        if (sent_bytes < 0) {
            perror("error sending data");
            continue;
        }

        /*
        This section reads the response from the server using the recv() function. 
        The received message is then displayed on the console.
        */
        char buffer[4096];
        int expected_data_len = sizeof(buffer);
        int read_bytes = recv(sock, buffer, expected_data_len, 0);
        if (read_bytes == 0) {
            cout << "Server closed the connection." << endl;
            break;
        } else if (read_bytes < 0) {
            perror("error reading data");
            continue;
        } else {
            buffer[read_bytes] = '\0';  // Null-terminate the received data
            cout << "Server response: " << buffer << endl;
        }
    }

    /*
    This section closes the socket after communication is complete to free up resources.
    */
    close(sock);

    return 0;
}

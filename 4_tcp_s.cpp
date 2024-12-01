/*
This section includes necessary libraries for networking, input/output, and error handling.
These libraries provide functions for creating sockets, managing addresses, and handling errors.
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
This section defines the server's port number and creates a TCP socket for communication.
The socket will be used to listen for incoming client connections.
*/
int main() {
    const int server_port = 5555;

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("error creating socket");
        return 1;
    }

    /*
    This section configures the server's address using the sockaddr_in structure.
    It assigns the server's port and allows connections from any network interface.
    */
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(server_port);

    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error binding socket");
        return 1;
    }

    /*
    This section listens for incoming client connections and accepts them.
    It handles up to 5 queued connection requests.
    */
    if (listen(sock, 5) < 0) {
        perror("error listening to a socket");
        return 1;
    }

    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    int client_sock = accept(sock, (struct sockaddr *) &client_sin, &addr_len);
    if (client_sock < 0) {
        perror("error accepting client");
        return 1;
    }

    /*
    Loop to continuously receive data from the client until the client closes the connection.
    The server echoes each message back to the client.
    */
    while (true) {
        char buffer[4096];
        int expected_data_len = sizeof(buffer);
        int read_bytes = recv(client_sock, buffer, expected_data_len, 0);
        if (read_bytes == 0) {
            cout << "Client closed the connection." << endl;
            break;
        } else if (read_bytes < 0) {
            perror("error reading from socket");
            continue;
        } else {
            buffer[read_bytes] = '\0';  // Null-terminate the received data
            cout << "Client sent: " << buffer << endl;

            // Echo the message back to the client
            int sent_bytes = send(client_sock, buffer, read_bytes, 0);
            if (sent_bytes < 0) {
                perror("error sending to client");
            }
        }
    }

    /*
    This section closes the client socket and the server socket.
    This ends the connection and releases resources.
    */
    close(client_sock);
    close(sock);

    return 0;
}

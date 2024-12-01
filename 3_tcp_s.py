import socket  # Import the socket library for creating and managing network connections

# Create a TCP socket
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # Create a TCP socket (SOCK_STREAM) using IPv4 (AF_INET)

# Define server IP and port
server_ip = ''  # Bind to all available network interfaces
server_port = 12345  # Port number for the server to listen on

# Bind the socket to the server's IP and port
server.bind((server_ip, server_port))  # Associate the socket with the specified IP and port

# Start listening for incoming connections
server.listen(5)  # Start listening with a maximum backlog of 5 pending connections

while True:  # Infinite loop to accept and handle client connections
    # Accept a connection from a client
    client_socket, client_address = server.accept()  # Wait for a client to connect
    print('Connection from: ', client_address)  # Print the address of the connected client

    # Receive data from the client
    data = client_socket.recv(1024)  # Receive up to 1024 bytes of data from the client

    # Process the received data until the client sends an empty string
    while not data.decode('utf-8') == '':  # Continue processing until no more data is received
        print('Received: ', data.decode('utf-8'))  # Decode and print the received data
        client_socket.send(data.upper())  # Convert the data to uppercase and send it back to the client
        data = client_socket.recv(1024)  # Wait for the next chunk of data from the client

    # Handle client disconnection
    print('Client disconnected')  # Notify that the client has disconnected
    client_socket.close()  # Close the connection with the client

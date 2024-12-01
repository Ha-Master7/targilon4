from socket import socket, AF_INET, SOCK_DGRAM  # Import necessary functions and constants from the socket library

# Create a UDP socket
s = socket(AF_INET, SOCK_DGRAM)  # Create a UDP socket using IPv4 (AF_INET) and datagram (SOCK_DGRAM) protocol

# Define the server IP and port
src_ip = ''  # Empty string means the server will listen on all available interfaces
src_port = 12345  # Port number where the server will listen for incoming messages

# Bind the server socket to the specified IP and port
s.bind((src_ip, src_port))  # Bind the socket to the address so it can receive messages

# Start an infinite loop to continuously receive and process client messages
while True:
    # Receive a message from a client
    data, sender_info = s.recvfrom(2048)  # Receive up to 2048 bytes of data and the sender's address information
    print(data.decode('utf-8'))  # Decode the received byte data to a string and print it
    print(sender_info)  # Print the sender's address information (IP and port)

    # Send a response back to the client
    s.sendto(data.upper(), sender_info)  # Convert the received message to uppercase and send it back to the sender

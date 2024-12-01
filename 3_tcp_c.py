import socket  # Import the socket library for network communication

# Create a TCP socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # Create a TCP socket (SOCK_STREAM) using IPv4 (AF_INET)

# Define the destination (server) IP and port
dest_ip = '127.0.0.1'  # Server's IP address (localhost)
dest_port = 12345  # Port number where the server is listening

# Connect to the server
s.connect((dest_ip, dest_port))  # Establish a connection to the server

# Prompt the user to input a message
msg = input("Message to send: ")  # Take the first message input from the user

# Loop to handle multiple messages until the user enters 'bye'
while not msg == 'bye':  # Continue until the user types 'bye'
    s.send(bytes(msg, 'utf-8'))  # Convert the message to bytes using UTF-8 encoding and send it to the server
    data = s.recv(4096)  # Receive up to 4096 bytes of data from the server
    print("Server sent: ", data.decode('utf-8'))  # Decode the server's response and print it
    print("send another message or enter bye: ")
    msg = input()  # Prompt the user for the next message

# Close the connection to the server
s.close()  # Close the client socket after the user exits

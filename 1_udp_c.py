from socket import socket, AF_INET, SOCK_DGRAM  # Import necessary functions and constants from the socket library

# Create a UDP socket
s = socket(AF_INET, SOCK_DGRAM)  # Create a UDP socket using IPv4 (AF_INET) and datagram (SOCK_DGRAM) protocol

# Define the destination (server) IP and port
dst_ip = '127.0.0.1'  # Server's IP address (localhost)
dst_port = 12345  # Server's port number

# added a loop to send messages till client wants to close
while True :          
    message = input("Enter your message to the server: ")  # Take input from the user
    # Send a message to the server
    s.sendto(message.encode('utf-8'), (dst_ip, dst_port))  # Send the byte-encoded message 'Hello' to the server's address

    # Receive a response from the server
    data, sender_info = s.recvfrom(2048)  # Receive up to 2048 bytes of data and the sender's address information
    print(data.decode('utf-8'))  # Decode the received byte data to a string and print it
    print(sender_info)  # Print the address of the sender (server)
    again = input("Do you want to send another message? (y/n): ").strip().lower()  # Ask for input and normalize it
    if again != 'y':  # If the user does not enter 'y', exit the loop
      print("Closing the connection. Goodbye!")
      break

s.close()  # Close the socket after communication is complete


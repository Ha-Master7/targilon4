from socket import socket, AF_INET, SOCK_STREAM

s = socket(AF_INET, SOCK_STREAM)
s.bind(('', 12345))
s.listen(5)

while True:    
    client, addr = s.accept()
    
    request = client.recv(4096)
    print(request)

    client.send(b'HTTP/1.1 200 OK\n')
    client.send(b'Content-Type: text/html\n')
    client.send(b'Access-Control-Allow-Origin: *\n')
    client.send(b'\n')
    client.send(b'Hello world ')
    client.send(b'<b>Hello world</b> ')
    client.send(b'<u>Hello world</u> ')
    client.send(b'<b><u>  Kitov David is the MASTER!!!!  </u></b> ')   #MODIFIED


    client.close()
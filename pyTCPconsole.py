import socket

address = '192.168.1.12'
port = 28924

print('Python socket console v0.1');

while(1):
	string = input('> ')
	string = string + '\n'
	s = socket.create_connection((address, port))
	n = s.send(string.encode('utf-8'));
	print(str(n) + ' bytes written');
	print('Server reply: ' + str(s.recv(64)))
	#s.close()

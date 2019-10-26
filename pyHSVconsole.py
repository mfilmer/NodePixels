import socket

address = '192.168.1.12'
port = 28924

print('Python HSV console v0.1');

while(1):
	H = int(input('H '))
	S = int(input('S '))
	V = int(input('V '))
	#string = char('F') + char(H) + char(S) + char(V) + '\n'
	data = 'F'.encode('utf-8') + bytes([H, S, V]) + '\n'.encode('utf-8')
	s = socket.create_connection((address, port))
	n = s.send(data);
	print(str(n) + ' bytes written');
	print('Server reply: ' + str(s.recv(64)))
	#s.close()

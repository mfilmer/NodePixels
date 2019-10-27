import socket

address = '192.168.1.12'
port = 28924

print('Python HSV console v0.1');

BRIGHTNESS_MSG = 0b000001
FULL_STRING_MSG = 0b000010
FULL_CYCLE_N_MSG = 0b000011


COLOR_RED = [255, 0, 0]
COLOR_GREEN = [0, 255, 0]
COLOR_BLUE = [0, 0, 255]

def MakeCycleCommand(delay, colors):
  n = len(colors)
  data = bytes([FULL_CYCLE_N_MSG]) + bytes([n]) + bytes([0,delay])
  for color in colors:
    data = data + bytes(color)
  return data

def MakeColorCommand(color):
  return bytes([FULL_STRING_MSG]) + bytes(color) + '\n'.encode('utf-8')


def MakeBrightCommand(bright):
	return bytes([BRIGHTNESS_MSG]) + bytes([bright]) + '\n'.encode('utf-8')



comm = MakeBrightCommand(0)
print(comm)


#comm = MakeColorCommand([1,255,1])
#print(comm)

#comm = MakeCycleCommand(100, [COLOR_RED, COLOR_GREEN])
#print(comm)

s = socket.create_connection((address, port))
n = s.send(comm)

print(str(n) + ' bytes written');
print('Server reply: ' + str(s.recv(64)))

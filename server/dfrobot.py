import serial
ser = serial.Serial('/dev/tty.SLAB_USBtoUART', 9600, timeout=1)
ser.write("2;")
print ser.readline()

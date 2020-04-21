# Channel: https://thingspeak.com/channels/1042952 .

import serial
import time
import thingspeak
channel_id = channel_id
write_key = 'write_key'
temperatura = 0
ser = serial.Serial()
ser.baudrate = 9600
ser.port = '/dev/ttyACM0'
ser.open()
channel = thingspeak.Channel(id=channel_id, write_key=write_key)
while 'true':
	temperatura = ser.readline();
	time.sleep(5)
    	print(temperatura)
    	response = channel.update({1:temperatura})
    	time.sleep(5)

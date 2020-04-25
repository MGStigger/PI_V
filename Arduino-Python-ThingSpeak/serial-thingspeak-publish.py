# Channel: https://thingspeak.com/channels/1042952 .

# Importa o publish da biblioteca paho.mqtt
import paho.mqtt.publish as publish

#Importa a biblioteca serial
import serial

# Importa a biblioteca time
import time

# Variavel "host_name" recebe o broker do ThingSpeak
host_name = "mqtt.thingspeak.com"

# Numero do campo (field) que se deseja enviar o valor da temperatura
numero_campo = 1

# ID do Canal
channel_id = channel_id

# Chave para gravar dados no canal
write_key = 'write_key'

# Topico
topico = "channels/"+str(channel_id)+"/publish/fields/field"+(numero_campo)+"/"+write_key

# Variavel temperatura
temperatura = 0

# Variavel "ser" recebe a porta serial
ser = serial.Serial('/dev/ttyACM0')

# Taxa de transmissao
ser.baudrate = 9600

#ser.port = '/dev/ttyACM0'

# Abre a porta serial
ser.open()

while 'true':
	# Le uma linha terminada com "\n"
	temperatura = ser.readline()
    	#print(temperatura)
	# Envia uma mensagem do cliente para o broker
	publish.single(topico, temperatura, hostname=host_name)

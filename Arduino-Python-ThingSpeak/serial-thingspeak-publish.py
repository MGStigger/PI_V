# Channel: https://thingspeak.com/channels/1042952 .

# IMPORTA O PUBLISH DA BIBLIOTECA "paho.mqtt"
import paho.mqtt.publish as publish

#IMPORTA A BIBLIOTECA SERIAL
import serial

# IMPORTA A BIBLIOTECA TIME
import time

# VARIAVEL "host_name" RECEBE O BROKER DO THINGSPEAK
host_name = "mqtt.thingspeak.com"

# NUMERO DO CAMPO (field) QUE SE DESEJA ENVIAR O VALOR DA TEMPERATURA
numero_campo = 1

# ID DO CANAL
channel_id = channel_id

# CHAVE PARA GRAVAR OS DADOS NO CANAL
write_key = 'write_key'

# TOPICO
topico = "channels/"+str(channel_id)+"/publish/fields/field"+(numero_campo)+"/"+write_key

# INICIALIZA A VARIAVEL "temperatura" COM O VALOR ZERO
temperatura = 0

# VARIAVEL "ser" RECEBE A PORTA SERIAL
ser = serial.Serial('/dev/ttyACM0')

# TAXA DE TRANSMISSAO
ser.baudrate = 9600

#ser.port = '/dev/ttyACM0'

# ABRE A PORTA SERIAL
ser.open()

while 'true':
	# LE UMA LINHA TERMINADA COM "\n"
	temperatura = ser.readline()

    	#print(temperatura)

	# ENVIA A MENSAGEM DO CLIENTE PARA O BROKER
	publish.single(topico, temperatura, hostname=host_name)

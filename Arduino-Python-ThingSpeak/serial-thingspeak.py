# Channel: https://thingspeak.com/channels/1042952 .

#IMPORTA AS BIBLIOTECAS
import serial
import time
import thingspeak

#ID DO CANAL
channel_id = 1042952

#CHAVE PARA GRAVAR DADOS NO CANAL
write_key = 'HHIO70MX4XESGDBJ'

#INICIALIZA A VARIAVEL "temperatura" COM O VALOR ZERO
temperatura = 0

#VARIAVEL "ser" RECEBE A PORTA SERIAL
ser = serial.Serial('/dev/ttyACM0')

#TAXA DE TRANSMISSAO
ser.baudrate = 9600

#ser.port = '/dev/ttyACM0'

#ABRE A PORTA SERIAL
ser.open()

#CANAL
channel = thingspeak.Channel(id=channel_id, write_key=write_key)

while 'true':
	#VARIAVEL "temperatura" FAZ A LEITURA DE UMA LINHA TERMINADA COM "\n"
	temperatura = ser.readline();

	#time.sleep(5)

	#IMPRIME O VALOR DA TEMPERATURA
    	print(temperatura)

	#ENVIA O DADO DA TEMPERATURA PARA O CANAL DO THINGSPEAK
    	response = channel.update({1:temperatura})

    	#time.sleep(5)

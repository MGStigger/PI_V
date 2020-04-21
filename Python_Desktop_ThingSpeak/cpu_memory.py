#Neste codigo, enviaremos o uso da CPU em porcentagem e a memoria disponivel de um PC para o ThingSpeak.

#Channel: https://thingspeak.com/channels/1040297 .

import urllib
from time import localtime, strftime
import psutil
import time
import http.client
 
sleep = 20 
key = 'chave_api_thingspeak'  # Chave da API do ThingSpeak
 
def doit():
	cpu_percent = psutil.cpu_percent(interval=1)
	mem = psutil.virtual_memory()	
	params = urllib.parse.urlencode({'field1': cpu_percent, 'field2': mem.available,'key':key})
	headers = {"Content-type": "application/x-www-form-urlencoded","Accept": "text/plain"}
	conn = http.client.HTTPConnection("api.thingspeak.com:80")
	time.sleep(20) 
	try:
		conn.request("POST", "/update", params, headers)
		response = conn.getresponse()
		print (cpu_pc)
		print (mem.available)
		print (strftime("%a, %d %b %Y %H:%M:%S", localtime()))
		print (response.status, response.reason)
		data = response.read()
		conn.close()
	except:
		print ("connection failed")	
 
# sleep por 20 segundos
if __name__ == "__main__":
	while True:
		doit()
		time.sleep(sleep)

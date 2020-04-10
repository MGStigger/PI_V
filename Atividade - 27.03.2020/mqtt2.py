# Ensures paho is in PYTHONPATH
import context
# Importa o publish do paho-mqtt
import paho.mqtt.publish as publish

# Publica
publish.single("mgstigger", "Olá Mundo!", hostname="mqtt.eclipse.org")

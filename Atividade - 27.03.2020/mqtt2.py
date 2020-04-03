import context  # Ensures paho is in PYTHONPATH
import paho.mqtt.publish as publish

publish.single("mgstigger", "Olá Mundo!", hostname="mqtt.eclipse.org")

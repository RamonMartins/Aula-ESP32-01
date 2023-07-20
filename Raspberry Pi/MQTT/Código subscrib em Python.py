import paho.mqtt.client as paho

def on_message(mosq, obj, msg):
    print(f"Payload: {msg.payload.decode('utf8')}")

client = paho.Client()
client.on_message = on_message

client.connect("localhost", 1883, 60)

client.subscribe("home_artur/sensor", 0)

while client.loop() == 0:
    pass

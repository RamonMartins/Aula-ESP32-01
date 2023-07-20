import paho.mqtt.client as paho

def on_message(mosq, obj, msg):
    print("%-20s %d %s" % (msg.topic, msg.qos, msg.payload))
    mosq.publish('pong', 'ack', 0)

client = paho.Client()

client.on_message = on_message

client.connect("192.168.0.58", 1883, 60)

client.subscribe("home_artur/sensor", 0)

while client.loop() == 0:
    pass
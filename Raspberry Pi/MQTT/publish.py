import paho.mqtt.publish as publish

host = "192.168.0.58"

publish.single(topic="home_artur/sensor", payload="valor_do_sensor", hostname=host)
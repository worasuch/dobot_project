import microgear.client as client
import time

appid = "HappyIoT Naja"
gearkey = "HappyIoT Naja"
gearsecret =  "HappyIoT Naja"

client.create(gearkey,gearsecret,appid,{'debugmode': True})

def connection():
	print "Now I am connected with netpie"

def subscription(topic,message):
	print topic+" "+message

client.setname("doraemon")
client.on_connect = connection
client.on_message = subscription
client.subscribe("/mails")

client.connect(True)

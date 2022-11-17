extends Node

const ip = "192.168.137.170"
const port = 80

var client
var connected = false
var txt = ''

signal esq
signal dir
signal dist(x)
signal perto
signal longe


func _ready():
	client = StreamPeerTCP.new()
	client.set_no_delay(true)
	client.connect_to_host(ip, port)
	
	if client.is_connected_to_host():
		connected = true
		print("Conectado")


func _process(_delta):
	if connected and not client.is_connected_to_host():
		connected = false
	else:
		_read_web_socket()


func _read_web_socket():
	while client.get_available_bytes() > 0:
		var message = client.get_utf8_string(client.get_available_bytes())
		
		if message == null:
			continue
		elif message.length() > 0:
			for i in message:
				if i == "\n":
					#print(txt)
					_message_interpreter(txt)
					txt = ''
				else:
					txt = txt + i


func write_web_socket(_txt):
	if connected and client.is_connected_to_host():
		client.put_data(_txt.to_ascii())


func _message_interpreter(_txt):
	var command: String = _txt
	
	if command.strip_edges() == "esq botao_pressionado":
		#print(command)
		emit_signal("esq")
	if command.strip_edges() == "dir botao_pressionado":
		#print(command)
		emit_signal("dir")
	
	if command.strip_edges().begins_with("dis"):
		#print(command.split(" ")[1])
		emit_signal("dist", command.split(" ")[1])
	
	if command.strip_edges() == "perto":
		emit_signal("perto")
	else:
		emit_signal("longe")
	

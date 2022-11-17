extends Node2D


func _ready():
	# warning-ignore: return_value_discarded
	WebSocket.connect("dist", self, "_on_dist")
	# warning-ignore: return_value_discarded
	WebSocket.connect("perto", self, "_ta_perto")
	# warning-ignore: return_value_discarded
	WebSocket.connect("longe", self, "_ta_longe")


func _on_dist(x):
	$Label.text = "Distancia em cm: " + str(x)


func _ta_perto():
	$Label2.text = "Ta muito perto de min."
	WebSocket.write_web_socket("alerta\n")


func _ta_longe():
	$Label2.text = "Ta longe."
	WebSocket.write_web_socket("longe\n")

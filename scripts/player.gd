extends KinematicBody2D


var move = Vector2.ZERO


func _ready():
	# warning-ignore: return_value_discarded
	WebSocket.connect("esq", self, "_on_click_esq")
	# warning-ignore: return_value_discarded
	WebSocket.connect("dir", self, "_on_click_dir")


func _physics_process(_delta):
	move.x = 0
	if Input.is_action_just_pressed("ui_left"):
		_on_click_esq()
	elif Input.is_action_just_pressed("ui_right"):
		_on_click_dir()
	# warning-ignore: return_value_discarded
	move_and_slide(move, Vector2.UP) 


func _on_click_esq():
	if !position.x <= 216:
		position.x -= 31


func _on_click_dir():
	if !position.x >= 278:
		position.x += 31

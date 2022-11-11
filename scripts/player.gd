extends KinematicBody2D


var move = Vector2.ZERO


func _ready():
	WebSocket.connect("esq", self, "_on_click_esq")
	WebSocket.connect("dir", self, "_on_click_dir")


func _physics_process(delta):
	move.x = 0
	if Input.is_action_pressed("ui_left"):
		move.x -= lerp(move.x, 500, 0.5)
	elif Input.is_action_pressed("ui_right"):
		move.x += lerp(move.x, 500, 0.5)
	
	move_and_slide(move, Vector2.UP) 

func _on_click_esq():
	move.x = 0
	move.x -= lerp(move.x, 500, 0.5)


func _on_click_dir():
	move.x = 0
	move.x += lerp(move.x, 500, 0.5)


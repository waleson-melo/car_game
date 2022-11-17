extends Node2D


export var velocidade = 100

func _ready() -> void:
	pass


func _process(delta: float) -> void:
	position.y += velocidade * delta

	if position.y >= 480:
		position.y = -96

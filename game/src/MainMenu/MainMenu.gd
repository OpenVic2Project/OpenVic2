extends Control

signal options_button_pressed

@export
var _new_game_button : BaseButton

func _ready():
	print("From GDScript")
	TestSingleton.hello_singleton()
	_new_game_button.grab_focus()


func _on_new_game_button_pressed():
	get_node("/root/OpenVic2/SFX").play("click")
	print("Start a new game!")
	get_node("/root/OpenVic2").remove_child(get_node("/root/OpenVic2/GameMenu"))
	var sample_game = load("res://src/SampleGame.tscn")
	get_node("/root/OpenVic2").add_child(sample_game)


func _on_continue_button_pressed():
	get_node("/root/OpenVic2/SFX").play("click")
	print("Continue last game!")


func _on_multi_player_button_pressed():
	get_node("/root/OpenVic2/SFX").play("click")
	print("Have fun with friends!")


func _on_options_button_pressed():
	get_node("/root/OpenVic2/SFX").play("click")
	print("Check out some options!")
	options_button_pressed.emit()


func _on_exit_button_pressed():
	await get_node("/root/OpenVic2/SFX").play("click")
	print("See you later!")
	get_tree().quit()

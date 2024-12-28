extends Node

func main(argv: Array) -> void:
	var res = preload('res://built-in/app/notepad/notepad.tscn').instantiate()
	self.add_child(res)

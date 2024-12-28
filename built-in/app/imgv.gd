extends Node

func main(argv: Array) -> void:
	var scene = preload("res://built-in/app/imageViewer/image_viewer.tscn").instantiate()
	self.add_child(scene)

extends Node

func main(argv: Array) -> void:
	var node = preload("res://built-in/app/pkg/packages.tscn").instantiate()
	self.add_child(node)

	for item in argv:
		print('adding file: ', item)
		node.call('AppendFile', str(item))

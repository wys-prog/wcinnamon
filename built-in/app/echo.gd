extends Node

func parse(array: Array) -> String:
	var content : String = ""
	var array_str : String = str(array)

	if array_str.begins_with("[") and array_str.ends_with("]"):
		array_str = array_str.substr(1, array_str.length() - 2)

	var pos : int = array_str.find('"')

	if (pos != -1):
		var end : int = array_str.find('"', pos + 1)
		if (end != -1):
			content = array_str.substr(pos + 1, end - (pos + 1))
		else:
			content = array_str
	else:
		content = array_str

	return content+'\n'

func main(argv: Array) -> void:
	var arguments : Array = str(argv).split(' ', false)

	var pos : int = arguments.find('>')
	var output : String = "kernel://system/stdout"

	if (pos != -1 and pos + 1 < arguments.size()):
		output = arguments[pos + 1]

	var content : String = parse(argv)

	if (output == 'kernel://system/stdout'):
		GDKernelApi.write(content)
		return

	var file : FileAccess = FileAccess.open(output, FileAccess.WRITE)
	if (file):
		file.store_line(content);

	return;

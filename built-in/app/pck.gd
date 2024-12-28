extends Node

func mount(path: String) -> void:

	var success : bool = ProjectSettings.load_resource_pack(path)

	if success:
		GDKernelApi.write('[color=green]S: %s mounted correctly[/color]\n' % path)
		GDKernelApi.mount(path)
	else:
		GDKernelApi.write('[color=red]E: Unable to mount %s pack.[/color]\n' % path)
	return

func list() -> void:
	var listofmodules : String = GDKernelApi.list_mounts()
	GDKernelApi.write('List of all pck modules:\n%s' % listofmodules)
	return 

func parse(argv: Array) -> void:
	var to_skip : bool = false;

	for i in range(0, argv.size()):
		if (to_skip):
			to_skip = false
			continue

		if (str(argv[i]) == 'mount'):
			mount(argv[i+1])
			to_skip = true
		elif (str(argv[i]) == 'ls'):
			list()
		else: GDKernelApi.write('[color=red]E: Unknown command %s.[/color]\n' % str(argv[i]))
	return

func main(argv: Array) -> void:
	parse(argv)

	self.queue_free()

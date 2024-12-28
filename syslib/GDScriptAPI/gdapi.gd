class_name GDKernelApi

# This function will call the « WriteStdOut » function of the 
# C# Wcinnamon.Syslib.GDScriptAPI.GDScriptStreamAPI.WriteStdout() function.
# The « Writestdout » function is a built-in library, lets you to interact with the Kernel.
static func write(elems: Variant) -> void:
	var csharp_api = load("res://syslib/GDScriptAPI/GDScriptStreamAPI.cs")
	csharp_api.call('WriteStdout', str(elems))

static func clear() -> void:
	var csharp_api = load("res://syslib/GDScriptAPI/GDScriptStreamAPI.cs")
	csharp_api.call('ClearStdOut')

static func mount(path: String) -> void:
	var csharp_api = load("res://built-in/app/pck/PckManager.cs")
	csharp_api.call('LoadPck', path)

static func unmount(path: String) -> void:
	var csharp_api = load("res://built-in/app/pck/PckManager.cs")
	csharp_api.call('UnloadPck', path)

static func list_mounts() -> String:
	var csharp_api = load("res://built-in/app/pck/PckManager.cs")
	var rslt : String =  csharp_api.call('GetList', '\n')
	return rslt;

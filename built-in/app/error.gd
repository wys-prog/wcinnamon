extends Node

var file : FileAccess = FileAccess.open(OS.get_user_data_dir() + '/system/stderr', FileAccess.WRITE);

func collect_godot_debug_info() -> String:
	var debug_info : String = "[GODOT DEBUG INFO]\n"

	debug_info += "OS Info:\n"
	debug_info += "  OS: %s\n" % OS.get_name()
	debug_info += "  CPU Cores: %d\n" % OS.get_processor_count()
	debug_info += "  RAM (Estimated): %s MB\n" % OS.get_static_memory_peak_usage()

	debug_info += "\nScene Tree:\n"
	if Engine.has_singleton("SceneTree"):
		var root = get_tree().root
		debug_info += "  Root Name: %s\n" % root.name
		debug_info += "  Active Scenes:\n"
		for i in root.get_child_count():
			debug_info += "    - %s\n" % root.get_child(i).name
	else:
		debug_info += "  SceneTree not available.\n"

	debug_info += "\nExecution Info:\n"
	debug_info += "  FPS: %d\n" % Engine.get_frames_per_second()
	debug_info += "  Debug Mode: %s\n" % str(OS.is_debug_build())

	debug_info += "\nRendering Info:\n"
	debug_info += "  Renderer: %s\n" % RenderingServer.get_video_adapter_name()

	debug_info += "\nNetwork Info:\n"
	debug_info += "  Connected to Internet: %s\n" % str(OS.has_feature("network"))

	debug_info += "\nMemory Info:\n"
	debug_info += "  Static Memory Usage: %s MB\n" % OS.get_static_memory_usage()
	debug_info += "  Peak Memory Usage: %s MB\n" % OS.get_static_memory_peak_usage()

	debug_info += "\nProject Settings:\n"
	debug_info += "  Project Name: %s\n" % ProjectSettings.get_setting("application/config/name")
	debug_info += "  Version: %s\n" % ProjectSettings.get_setting("application/config/version")


	debug_info += "\nStack Trace:\n"
	var trace = get_stack()
	debug_info += str(trace)

	return debug_info

func write(elems: Variant) -> void:
	file.store_string(str(elems))
	file.store_string(collect_godot_debug_info())
	GDKernelApi.write(elems)
	GDKernelApi.write(collect_godot_debug_info())

func main(argv: Array) -> void:
	write('error dialog opened');
	write(['Arguments: ', argv]);

	var dialog : AcceptDialog = AcceptDialog.new();
	dialog.title = "error !";

	var label : RichTextLabel = RichTextLabel.new();
	label.text = 'Exception occured.\nwhat(): ' + str(argv);
	label.text += '\n' + collect_godot_debug_info()
	dialog.size += Vector2i(460, 250)
	dialog.position = Vector2(50, 50)

	add_child(dialog);
	dialog.add_child(label);

	dialog.visible = true;
	file.close();

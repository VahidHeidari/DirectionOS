@echo off

call:clean_dir .
call:clean_dir ./Kernel
call:clean_dir ./Kernel/DataStructures
call:clean_dir ./Kernel/Devices
call:clean_dir ./Kernel/TaskManager
call:clean_dir ./Kernel/Tasks
call:clean_dir ./UserTasks
goto:EOF

:clean_dir
	del   /f /q "%~1\*.c!"		2>nul
	del   /f /q "%~1\*.c~"		2>nul
	del   /f /q "%~1\*.c@"		2>nul
	del   /f /q "%~1\*.c_cbf"	2>nul
	del   /f /q "%~1\*.fct"		2>nul
	del   /f /q "%~1\*.map"		2>nul
	del   /f /q "%~1\*.i"		2>nul
	del   /f /q "%~1\*.h~"		2>nul
	del   /f /q "%~1\*.prj~"	2>nul
	del   /f /q "%~1\*.hdr"		2>nul
	del   /f /q "%~1\*.h!"		2>nul
	del   /f /q "%~1\*.h_cbf"	2>nul
	del   /f /q "%~1\*~"		2>nul
	rmdir /s /q "%~1\Linker"	2>nul
	rmdir /s /q "%~1\List"		2>nul
	rmdir /s /q "%~1\Obj"		2>nul
goto:EOF


cls

del *.obj
del *.res
del *.exe

cl.exe /c /EHsc Window.c

rc.exe Window.rc

link.exe Window.obj Window.res user32.lib gdi32.lib MyMathOne.lib /SUBSYSTEM:WINDOWS

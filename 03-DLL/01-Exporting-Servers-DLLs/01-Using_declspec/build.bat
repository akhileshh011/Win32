cls

del *.obj
del *.dll
del *.lib
del *.exp

cl.exe /c /EHsc MyMathOne.c

link.exe MyMathOne.obj /DLL user32.lib /SUBSYSTEM:WINDOWS

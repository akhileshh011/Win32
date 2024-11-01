cls

del *.obj
del *.dll
del *.lib
del *.exp

cl.exe /c /EHsc MyMathTwo.cpp

link.exe MyMathTwo.obj /DLL /DEF:MyMathTwo.def user32.lib /SUBSYSTEM:WINDOWS

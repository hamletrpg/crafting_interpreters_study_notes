set files=src\memory.c src\main.c src\debug.c src\chunk.c src\value.c 

CL /Zi /I C:\dev\c++\study_material\crafting_interpreters\includes %files% /link /OUT:my_interpreter.exe

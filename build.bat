set files=src\memory.c src\main.c src\debug.c src\chunk.c src\value.c src\vm.c src\compiler.c src\scanner.c src\object.c

CL /Zi /I C:\dev\c++\learning_material\crafting_interpreters_study_notes\includes %files% /link /OUT:my_interpreter.exe

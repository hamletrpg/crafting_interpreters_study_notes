set files=src\main.c src\chunk.c src\debug.c src\memory.c src\vm.c src\value.c

CL /Zi /I .\include %files% /link user32.lib /OUT:mygame.exe
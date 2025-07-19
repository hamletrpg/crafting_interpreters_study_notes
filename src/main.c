#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"

static void repl()
{
  char line[1024];
  for (;;)
  {
    printf("> ");

    if (!fgets(line, sizeof(line), stdin))
    {
      printf("\n");
      break;
    }

    interpret(line);
  }
}

static char* read_file(const char* path)
{
  FILE* file = fopen(path, "rb");
  if (file == NULL)
  {
    fprintf(stderr, "Could not open file \"%s\.\n", path);
    exit(74);
  }

  // Seeking to the end before reading
  fseek(file, 0L, SEEK_END);
  // Checking the size of the file and saving it in a variable 
  size_t file_size = ftell(file);
  // going back at the begining.
  rewind(file);
  
  // we allocate some memory (for my personal project I'll be using some sort of arena/bump allocator)
  // The bump allocator would be the buffer rather than explicitly calling malloc here
  char* buffer = (char*)malloc(file_size + 1);
  if (buffer == NULL)
  {
    fprintf(stderr, "Not enough memory to read \"%s\".\n", path);
    exit(74);
  }
  size_t bytes_read = fread(buffer, sizeof(char), file_size, file);
  if (bytes_read < file_size)
  {
    sprintf(stderr, "Could not read file \"%s\.\n", path);
    exit(74);
  }

  buffer[bytes_read] = '\0';

  fclose(file);
  return buffer;
}

static void run_file(const char* path)
{
  char* source = read_file(path);
  InterpretResult result = interpret(source);
  free(source);

  if (result == INTERPRET_COMPILE_ERROR) exit(65);
  if (result == INTERPRET_RUNTIME_ERROR) exit(70);
}

int main(int argc, const char* argv[])
{
  init_vm();

  if (argc == 1)
  {
    repl();
  }
  else if (argc == 2)
  {
    run_file(argv[1]);
  }
  else 
  {
    fprintf(stderr, "Usage: clox [path]\n");
    exit(64);
  }

  free_vm();

  return 0;
}

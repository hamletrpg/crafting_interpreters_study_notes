// author named Chunks a sequesce of bytecodes
#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"
// Operation Code enumerator
typedef enum 
{
  OP_CONSTANT,
  OP_NIL,
  OP_TRUE,
  OP_FALSE,
  OP_EQUAL,
  OP_GREATER,
  OP_LESS,
  OP_ADD,
  OP_SUBTRACT,
  OP_MULTIPLY,
  OP_DIVIDE,
  OP_NOT,
  OP_NEGATE,
  OP_RETURN,
} OpCode;

typedef struct 
{
  int count;
  int capacity;
  // Code is supposed to be a pointer to an array of data. for some weird reason the 
  // author named this field as "code" rather than "data" (kind of confusing lol)
  uint8_t *code;
  int* lines;
  ValueArray constants;
} Chunk;

void init_chunk(Chunk* chunk);
void write_chunk(Chunk* chunk, uint8_t byte, int line);
void free_chunk(Chunk* chunk);
int add_constant(Chunk* chunk, Value value);

#endif

#ifndef LEXER_FLAG_H
#define LEXER_FLAG_H

#ifdef __cplusplus
extern "C" {
#endif


// =====================
// Lexer Flag API (modular, thread-safe)
// =====================
#include "rift-0/core/lexer/lexer.h"

void lexer_set_flag(LexerContext* ctx, Lexer
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <pthread.h>

// =====================
// Heap-based Priority Queue (thread-safe)
// =====================
typedef struct {
    int priority;
    int value;
} Item;

typedef struct {
    Item* heap;
    int capacity;
    int size;
    pthread_mutex_t lock;
} HeapQueue;

HeapQueue* hq_create(int capacity);
void hq_destroy(HeapQueue* hq);
void hq_enqueue(HeapQueue* hq, int priority, int value);
Item hq_dequeue(HeapQueue* hq);

Flags flag);
void lexer_clear_flag(LexerContext* ctx, LexerFlags flag);
bool lexer_flag_enabled(const LexerContext* ctx, LexerFlags flag);

TokenNode* token_create(TokenType type, const char* value, size_t length);
void token_destroy(TokenNode* token);

#ifdef __cplusplus
}
#endif // End of extern "C"

#endif // LEXER_FLAG_H

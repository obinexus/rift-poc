
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rift-0/core/lexer/lexer.h"

// --- Lexer flag management ---
void lexer_set_flag(LexerContext* ctx, LexerFlags flag) {
    ctx->flags |= flag;
}

void lexer_clear_flag(LexerContext* ctx, LexerFlags flag) {
    ctx->flags &= ~flag;
}

bool lexer_flag_enabled(const LexerContext* ctx, LexerFlags flag) {
    return (ctx->flags & flag) != 0;
}

// --- Modular token creation ---
TokenNode* token_create(TokenType type, const char* value, size_t length) {
    TokenNode* token = (TokenNode*)malloc(sizeof(TokenNode));
    token->type = type;
    token->length = length;
    token->value = (char*)malloc(length + 1);
    memcpy(token->value, value, length);
    token->value[length] = '\0';
    token->memory = NULL;
    return token;
}

void token_destroy(TokenNode* token) {
    if (token) {
        free(token->value);
        free(token);
    }
}

// --- Example: heap-based top-down and shift-reduce matching ---
void demo_lexer_flags() {
    LexerContext ctx = {0};
    lexer_set_flag(&ctx, LEXER_FLAG_RAW_STRING);
    lexer_set_flag(&ctx, LEXER_FLAG_GLOBAL_TB);
    lexer_set_flag(&ctx, LEXER_FLAG_TOP_DOWN);

    if (lexer_flag_enabled(&ctx, LEXER_FLAG_RAW_STRING)) {
        printf("Raw string mode enabled\n");
    }
    if (lexer_flag_enabled(&ctx, LEXER_FLAG_GLOBAL_TB)) {
        printf("Global [tb] matching enabled\n");
    }
    if (lexer_flag_enabled(&ctx, LEXER_FLAG_TOP_DOWN)) {
        printf("Top-down parsing enabled\n");
    }
    lexer_clear_flag(&ctx, LEXER_FLAG_TOP_DOWN);
    lexer_set_flag(&ctx, LEXER_FLAG_SHIFT_REDUCE);
    if (lexer_flag_enabled(&ctx, LEXER_FLAG_SHIFT_REDUCE)) {
        printf("Shift-reduce parsing enabled\n");
    }
}

// --- Example: type-safe token creation ---
void demo_token_creation() {
    TokenNode* t1 = token_create(TOKEN_TYPE_RAW_STRING, "R\"example\"", 10);
    printf("Token type: %d, value: %s\n", t1->type, t1->value);
    token_destroy(t1);
}

int main() {
    demo_lexer_flags();
    demo_token_creation();
    // TODO: Implement heap-based matching and [tb] global matching logic
    // TODO: Implement R'' char literal and R" string literal parsing
    return 0;
}
 
 

/*
 * RIFT-Core-0: Stage-0 Orchestration (Tokenization Only)
 * Part of AEGIS Project - OBINexus Computing
 *
 * This file now only handles Stage-0 orchestration and test main.
 * Lexical analysis logic is in src/core/lexer.c (see include/rift-0/lexer.h)
 * Governance: #[gov:stage_0_core]
 */

// Only standard includes needed for main/test
#include <stdio.h>
#include <stdlib.h>
#include "rift-0/lexer.h"


int main(int argc, char* argv[]) {
    printf("RIFT Stage-0 Tokenizer - AEGIS Project\n");
    printf("======================================\n\n");

    // Create Stage-0 context using lexer module
    RiftStage0Context* ctx = rift_stage0_create();
    if (!ctx) {
        fprintf(stderr, "Failed to initialize Stage-0 context\n");
        return 1;
    }

    // Example: Test token patterns using lexer API (implementation in lexer.c)
    // ...

    // Cleanup
    rift_stage0_destroy(ctx);

    printf("\nTokenizer test complete!\n");
    return 0;
}
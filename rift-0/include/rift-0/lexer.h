/*
 * RIFT-Core-0 Lexer Header
 * Exposes Stage-0 lexical analysis API
 * Governance: #[gov:stage_0_core]
 */

#ifndef RIFT_0_LEXER_H
#define RIFT_0_LEXER_H

#include <stdbool.h>
#include <stdint.h>
#include <regex.h>
#include <pthread.h>


// Forward declaration of Stage-0 context
typedef struct RiftStage0Context RiftStage0Context;

// Create and destroy Stage-0 context
RiftStage0Context* rift_stage0_create(void);
void rift_stage0_destroy(RiftStage0Context* ctx);

// (Other API declarations as needed)

#endif // RIFT_0_LEXER_H

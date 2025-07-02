/*
 * RIFT-Core-0 Header: Stage-0 Tokenization Interface
 * Part of AEGIS Project - OBINexus Computing
 * 
 * Public API for RIFT Stage-0 dual-channel tokenizer
 */

#ifndef RIFT_CORE_0_H
#define RIFT_CORE_0_H
#if defined(__unix__) || defined(__APPLE__)
#include <regex.h>
#endif
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "rift-0/core/gov/rift-gov.0.h"

#ifdef __cplusplus
extern "C" {
#endif

// Versioning macros
#define RIFT_VERSION_MAJOR 0
#define RIFT_VERSION_MINOR 1
#define RIFT_VERSION_PATCH 0


// Public API declarations (implementations elsewhere)
RiftStage0Context* rift_stage0_create(void);
RiftStage0Context* rift_stage0_create_with_config(const RiftStage0Config* config);
void rift_stage0_destroy(RiftStage0Context* ctx);

// Forward declarations if not included by headers
DualChannelOutput* create_dual_channel_output(void);
void set_error_level(DualChannelOutput* output, int level, const char* msg);

// Extern declaration for stage0_patterns if defined elsewhere
// Forward declaration for TokenPattern if not already defined
#ifndef TOKEN_PATTERN_DEFINED
#define TOKEN_PATTERN_DEFINED
typedef struct TokenPattern {
	const char* name;
	const char* pattern;
	int token_type;
} TokenPattern;
#endif

extern const TokenPattern stage0_patterns[];
extern const size_t stage0_patterns_count;
// Memory governance API
TokenMemoryGovernor* create_memory_governor(size_t min_heap, size_t max_heap);
void* governed_malloc(TokenMemoryGovernor* gov, size_t size);
void governed_free(TokenMemoryGovernor* gov, void* ptr, size_t size);

#ifdef __cplusplus
}
#endif

#endif /* RIFT_CORE_0_H */

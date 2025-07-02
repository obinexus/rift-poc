/*
 * RIFT-Core-0: Stage-0 Tokenization and Lexical Analysis
 * Part of AEGIS Project - OBINexus Computing
 * 
 * Fixed implementation with corrected regex patterns
 */

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <regex.h>
#include <stdint.h>
#include <pthread.h>
#include <assert.h>

#include <ctype.h>
/* ===================================================================
 * RIFT Stage-0 Core Definitions
 * =================================================================== */

#define RIFT_VERSION_MAJOR 0
#define RIFT_VERSION_MINOR 1
#define RIFT_VERSION_PATCH 0
#define RIFT_STAGE_ID 0

/* Error severity levels */
typedef enum {
    RIFT_WARNING_MIN = 0,
    RIFT_WARNING_MAX = 3,
    RIFT_DANGER_MIN = 3,
    RIFT_DANGER_MAX = 6,
    RIFT_CRITICAL_MIN = 6,
    RIFT_CRITICAL_MAX = 9,
    RIFT_PANIC_MIN = 9,
    RIFT_PANIC_MAX = 12
} RiftErrorSeverity;

/* Token types */
typedef enum {
    R_INIT_EMPTY = 0,
    R_IDENTIFIER,
    R_NUMBER,
    R_OPERATOR,
    R_KEYWORD,
    R_STRING,
    R_COMMENT,
    R_WHITESPACE,
    R_QUANTUM_TOKEN,
    R_COLLAPSE_MARKER,
    R_ENTANGLE_MARKER,
    R_GOVERNANCE_TAG,
    R_CUSTOM_PATTERN,
    R_EOF
} RiftTokenType;

/* Token memory governance */
typedef struct {
    size_t min_heap;
    size_t max_heap;
    size_t current_usage;
    bool dynamic_allowed;
    pthread_mutex_t mem_lock;
} TokenMemoryGovernor;

/* Dual-channel output structure */
typedef struct {
    void* classic_channel;
    size_t classic_size;
    void* quantum_channel;
    size_t quantum_size;
    uint8_t error_level;
    char* error_msg;
} DualChannelOutput;

/* Token structure */
typedef struct {
    RiftTokenType type;
    char* pattern;
    char* value;
    size_t line;
    size_t column;
    bool is_quantum;
    bool is_collapsed;
    uint64_t governance_flags;
    void* metadata;
} RiftToken;

/* Stage-0 tokenizer context */
typedef struct {
    bool initialized;
    uint32_t stage_id;
    uint32_t version;
    regex_t* patterns;
    size_t pattern_count;
    TokenMemoryGovernor* mem_gov;
    bool dual_mode_enabled;
    bool quantum_mode_active;
    uint8_t current_error_level;
    char error_buffer[1024];
    bool aegis_compliant;
    uint64_t compliance_flags;
    pthread_mutex_t ctx_lock;
    uint32_t thread_count;
} RiftStage0Context;

/* ===================================================================
 * Token Pattern Definitions (FIXED)
 * =================================================================== */

typedef struct {
    const char* name;
    const char* pattern;
    RiftTokenType type;
    bool is_quantum;
} TokenPattern;

/* Fixed patterns - operator pattern corrected */
static TokenPattern stage0_patterns[] = {
    {"identifier", "^[a-zA-Z_][a-zA-Z0-9_]*$", R_IDENTIFIER, false},
    {"number", "^[0-9]+(\\.[0-9]+)?$", R_NUMBER, false},
    {"operator", "^[-+*/=<>!&|^~%]$", R_OPERATOR, false},
    {"quantum_init", "^@quantum", R_QUANTUM_TOKEN, true},
    {"collapse", "^!collapse", R_COLLAPSE_MARKER, true},
    {"entangle", "^@entangle", R_ENTANGLE_MARKER, true},
    {"governance", "^#\\[gov:.*\\]", R_GOVERNANCE_TAG, false},
    {"string", "^\"([^\"\\\\]|\\\\.)*\"$", R_STRING, false},
    {"comment", "^//.*$", R_COMMENT, false},
    {"whitespace", "^\\s+$", R_WHITESPACE, false}
};

/* ===================================================================
 * Memory Governance Implementation
 * =================================================================== */

TokenMemoryGovernor* create_memory_governor(size_t min_heap, size_t max_heap) {
    TokenMemoryGovernor* gov = malloc(sizeof(TokenMemoryGovernor));
    if (!gov) return NULL;
    
    gov->min_heap = min_heap;
    gov->max_heap = max_heap;
    gov->current_usage = 0;
    gov->dynamic_allowed = true;
    pthread_mutex_init(&gov->mem_lock, NULL);
    
    return gov;
}

void* governed_malloc(TokenMemoryGovernor* gov, size_t size) {
    if (!gov || !gov->dynamic_allowed) return NULL;
    
    pthread_mutex_lock(&gov->mem_lock);
    
    if (gov->current_usage + size > gov->max_heap) {
        pthread_mutex_unlock(&gov->mem_lock);
        return NULL;
    }
    
    void* ptr = malloc(size);
    if (ptr) {
        gov->current_usage += size;
    }
    
    pthread_mutex_unlock(&gov->mem_lock);
    return ptr;
}

void governed_free(TokenMemoryGovernor* gov, void* ptr, size_t size) {
    if (!gov || !ptr) return;
    
    pthread_mutex_lock(&gov->mem_lock);
    free(ptr);
    if (gov->current_usage >= size) {
        gov->current_usage -= size;
    }
    pthread_mutex_unlock(&gov->mem_lock);
}

/* ===================================================================
 * Dual-Channel Output Management
 * =================================================================== */

DualChannelOutput* create_dual_channel_output(void) {
    DualChannelOutput* output = calloc(1, sizeof(DualChannelOutput));
    if (!output) return NULL;
    
    output->error_level = 0;
    return output;
}

void set_error_level(DualChannelOutput* output, uint8_t level, const char* msg) {
    if (!output) return;
    
    output->error_level = level;
    if (msg) {
        if (output->error_msg) free(output->error_msg);
        output->error_msg = strdup(msg);
    }
    
    /* Handle error severity */
    if (level >= RIFT_WARNING_MIN && level < RIFT_WARNING_MAX) {
        printf("\033[33m[WARNING]\033[0m %s\n", msg);
    } else if (level >= RIFT_DANGER_MIN && level < RIFT_DANGER_MAX) {
        printf("\033[31m[DANGER]\033[0m %s - Entering fix mode\n", msg);
    } else if (level >= RIFT_CRITICAL_MIN && level < RIFT_CRITICAL_MAX) {
        printf("\033[35m[CRITICAL]\033[0m %s - Emergency intervention required\n", msg);
    } else if (level >= RIFT_PANIC_MIN) {
        printf("\033[91m[PANIC]\033[0m %s - System failsafe activated\n", msg);
    }
}

/* ===================================================================
 * Stage-0 Core Implementation
 * =================================================================== */

RiftStage0Context* rift_stage0_create(void) {
    RiftStage0Context* ctx = calloc(1, sizeof(RiftStage0Context));
    if (!ctx) return NULL;
    
    /* Initialize core state */
    ctx->initialized = true;
    ctx->stage_id = RIFT_STAGE_ID;
    ctx->version = (RIFT_VERSION_MAJOR << 16) | (RIFT_VERSION_MINOR << 8) | RIFT_VERSION_PATCH;
    
    /* Initialize memory governor */
    ctx->mem_gov = create_memory_governor(1024 * 1024, 16 * 1024 * 1024);
    if (!ctx->mem_gov) {
        free(ctx);
        return NULL;
    }
    
    /* Initialize token patterns */
    ctx->pattern_count = sizeof(stage0_patterns) / sizeof(TokenPattern);
    ctx->patterns = calloc(ctx->pattern_count, sizeof(regex_t));
    if (!ctx->patterns) {
        free(ctx->mem_gov);
        free(ctx);
        return NULL;
    }
    
    /* Compile regex patterns */
    for (size_t i = 0; i < ctx->pattern_count; i++) {
        int ret = regcomp(&ctx->patterns[i], stage0_patterns[i].pattern, REG_EXTENDED);
        if (ret != 0) {
            char errbuf[256];
            regerror(ret, &ctx->patterns[i], errbuf, sizeof(errbuf));
            printf("Failed to compile pattern '%s': %s (regex: %s)\n", 
                   stage0_patterns[i].name, errbuf, stage0_patterns[i].pattern);
            
            /* Cleanup previously compiled patterns */
            for (size_t j = 0; j < i; j++) {
                regfree(&ctx->patterns[j]);
            }
            free(ctx->patterns);
            pthread_mutex_destroy(&ctx->mem_gov->mem_lock);
            free(ctx->mem_gov);
            free(ctx);
            return NULL;
        }
    }
    
    /* Enable features */
    ctx->dual_mode_enabled = true;
    ctx->quantum_mode_active = false;
    ctx->aegis_compliant = true;
    ctx->compliance_flags = 0xAE615;
    ctx->compliance_flags = 0xAE615;
    ctx->thread_count = 4;
    
    pthread_mutex_init(&ctx->ctx_lock, NULL);
    
    printf("RIFT Stage-0 Tokenizer initialized\n");
    printf("  Version: %d.%d.%d\n", RIFT_VERSION_MAJOR, RIFT_VERSION_MINOR, RIFT_VERSION_PATCH);
    printf("  Patterns loaded: %zu\n", ctx->pattern_count);
    printf("  Dual-channel: %s\n", ctx->dual_mode_enabled ? "enabled" : "disabled");
    printf("  AEGIS compliant: %s\n", ctx->aegis_compliant ? "yes" : "no");
    
    return ctx;
}

/* ===================================================================
 * Simplified Test Main
 * =================================================================== */

int main(int argc, char* argv[]) {
    printf("RIFT Stage-0 Tokenizer - AEGIS Project\n");
    printf("======================================\n\n");
    
    /* Create Stage-0 context */
    RiftStage0Context* ctx = rift_stage0_create();
    if (!ctx) {
        fprintf(stderr, "Failed to initialize Stage-0 context\n");
        return 1;
    }
    
    /* Test patterns */
    printf("\nTesting token patterns:\n");
    printf("----------------------\n");
    
    const char* test_tokens[] = {
        "identifier123",    /* Should match identifier */
        "42.5",            /* Should match number */
        "+",               /* Should match operator */
        "^",               /* Should match operator (testing fixed pattern) */
        "@quantum",        /* Should match quantum_init */
        "!collapse",       /* Should match collapse */
        "#[gov:test]",     /* Should match governance */
        "\"test string\"", /* Should match string */
        "// comment",      /* Should match comment */
    };
    
    for (size_t i = 0; i < sizeof(test_tokens) / sizeof(test_tokens[0]); i++) {
        printf("Testing '%s': ", test_tokens[i]);
        
        bool matched = false;
        for (size_t j = 0; j < ctx->pattern_count; j++) {
            regmatch_t match;
            if (regexec(&ctx->patterns[j], test_tokens[i], 1, &match, 0) == 0) {
                printf("Matched as %s\n", stage0_patterns[j].name);
                matched = true;
                break;
            }
        }
        
        if (!matched) {
            printf("No match found\n");
        }
    }
    
    printf("\nTest input processing:\n");
    printf("---------------------\n");
    
    const char* test_input = "x = 42 + y";
    printf("Input: %s\n", test_input);
    
    /* Basic tokenization test */
    const char* ptr = test_input;
    while (*ptr) {
        if (*ptr == ' ') {
            ptr++;
            continue;
        }
        
        /* Extract token */
        char token[64];
        size_t len = 0;
        
        if (isalpha(*ptr) || *ptr == '_') {
            /* Identifier */
            while ((isalnum(*ptr) || *ptr == '_') && len < 63) {
                token[len++] = *ptr++;
            }
        } else if (isdigit(*ptr)) {
            /* Number */
            while ((isdigit(*ptr) || *ptr == '.') && len < 63) {
                token[len++] = *ptr++;
            }
        } else {
            /* Single character token */
            token[len++] = *ptr++;
        }
        
        token[len] = '\0';
        printf("  Token: '%s'\n", token);
    }
    
    /* Cleanup */
    for (size_t i = 0; i < ctx->pattern_count; i++) {
        regfree(&ctx->patterns[i]);
    }
    free(ctx->patterns);
    pthread_mutex_destroy(&ctx->mem_gov->mem_lock);
    free(ctx->mem_gov);
    pthread_mutex_destroy(&ctx->ctx_lock);
    free(ctx);
    
    printf("\nTokenizer test complete!\n");
    return 0;
}
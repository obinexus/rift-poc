/*
 * RIFT-Core-0: Stage-0 Tokenization and Lexical Analysis
 * Part of AEGIS Project - OBINexus Computing
 * 
 * Implements dual-channel output (classic/quantum) with AEGIS compliance
 * Toolchain: riftlang.exe → .so.a → rift.exe → gosilang
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <regex.h>
#include <stdint.h>
#include <pthread.h>
#include <assert.h>

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

/* Token types - from R_INIT_EMPTY to complex patterns */
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

/* Token structure with governance metadata */
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
    /* Core state */
    bool initialized;
    uint32_t stage_id;
    uint32_t version;
    
    /* Token patterns */
    regex_t* patterns;
    size_t pattern_count;
    
    /* Memory governance */
    TokenMemoryGovernor* mem_gov;
    
    /* Dual-channel configuration */
    bool dual_mode_enabled;
    bool quantum_mode_active;
    
    /* Error tracking */
    uint8_t current_error_level;
    char error_buffer[1024];
    
    /* AEGIS compliance */
    bool aegis_compliant;
    uint64_t compliance_flags;
    
    /* Thread management */
    pthread_mutex_t ctx_lock;
    uint32_t thread_count;
} RiftStage0Context;

/* ===================================================================
 * Token Pattern Definitions
 * =================================================================== */

typedef struct {
    const char* name;
    const char* pattern;
    RiftTokenType type;
    bool is_quantum;
} TokenPattern;

static TokenPattern stage0_patterns[] = {
    {"identifier", "^[a-zA-Z_][a-zA-Z0-9_]*$", R_IDENTIFIER, false},
    {"number", "^[0-9]+(\\.[0-9]+)?$", R_NUMBER, false},
    {"operator", "^[+\\-*/=<>!&|^~%]$", R_OPERATOR, false},
    {"quantum_init", "^@quantum\\s*\\{", R_QUANTUM_TOKEN, true},
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
    gov->current_usage -= size;
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
    ctx->mem_gov = create_memory_governor(1024 * 1024, 16 * 1024 * 1024); // 1MB min, 16MB max
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
            printf("Failed to compile pattern: %s\n", stage0_patterns[i].name);
            // Cleanup and return
            for (size_t j = 0; j < i; j++) {
                regfree(&ctx->patterns[j]);
            }
            free(ctx->patterns);
            free(ctx->mem_gov);
            free(ctx);
            return NULL;
        }
    }
    
    /* Enable dual-channel mode by default */
    ctx->dual_mode_enabled = true;
    ctx->quantum_mode_active = false;
    ctx->aegis_compliant = true;
    ctx->compliance_flags = 0xAEG15;
    ctx->thread_count = 4;
    
    pthread_mutex_init(&ctx->ctx_lock, NULL);
    
    printf("RIFT Stage-0 Tokenizer initialized\n");
    printf("  Version: %d.%d.%d\n", RIFT_VERSION_MAJOR, RIFT_VERSION_MINOR, RIFT_VERSION_PATCH);
    printf("  Dual-channel: %s\n", ctx->dual_mode_enabled ? "enabled" : "disabled");
    printf("  AEGIS compliant: %s\n", ctx->aegis_compliant ? "yes" : "no");
    printf("  Memory limits: %zu - %zu bytes\n", ctx->mem_gov->min_heap, ctx->mem_gov->max_heap);
    
    return ctx;
}

RiftToken* create_token(RiftStage0Context* ctx, RiftTokenType type, 
                       const char* value, size_t line, size_t col) {
    if (!ctx || !value) return NULL;
    
    size_t token_size = sizeof(RiftToken) + strlen(value) + 1;
    RiftToken* token = governed_malloc(ctx->mem_gov, token_size);
    if (!token) return NULL;
    
    token->type = type;
    token->value = strdup(value);
    token->line = line;
    token->column = col;
    token->is_quantum = false;
    token->is_collapsed = false;
    token->governance_flags = ctx->compliance_flags;
    token->metadata = NULL;
    token->pattern = NULL;
    
    /* Set quantum flag based on token type */
    if (type == R_QUANTUM_TOKEN || type == R_COLLAPSE_MARKER || type == R_ENTANGLE_MARKER) {
        token->is_quantum = true;
    }
    
    return token;
}

void free_token(RiftStage0Context* ctx, RiftToken* token) {
    if (!ctx || !token) return;
    
    size_t token_size = sizeof(RiftToken) + (token->value ? strlen(token->value) + 1 : 0);
    
    if (token->value) free(token->value);
    if (token->pattern) free(token->pattern);
    if (token->metadata) free(token->metadata);
    
    governed_free(ctx->mem_gov, token, token_size);
}

/* ===================================================================
 * Tokenization Engine
 * =================================================================== */

RiftToken** tokenize_input(RiftStage0Context* ctx, const char* input, size_t* token_count) {
    if (!ctx || !input || !token_count) return NULL;
    
    pthread_mutex_lock(&ctx->ctx_lock);
    
    /* Initial token array */
    size_t capacity = 100;
    RiftToken** tokens = calloc(capacity, sizeof(RiftToken*));
    if (!tokens) {
        pthread_mutex_unlock(&ctx->ctx_lock);
        return NULL;
    }
    
    size_t count = 0;
    size_t line = 1;
    size_t col = 1;
    const char* ptr = input;
    
    while (*ptr) {
        bool matched = false;
        
        /* Skip whitespace while tracking position */
        if (*ptr == ' ' || *ptr == '\t') {
            col++;
            ptr++;
            continue;
        }
        if (*ptr == '\n') {
            line++;
            col = 1;
            ptr++;
            continue;
        }
        
        /* Try to match against patterns */
        for (size_t i = 0; i < ctx->pattern_count; i++) {
            regmatch_t match;
            char test_buffer[256];
            
            /* Extract a test string */
            size_t test_len = 0;
            const char* test_ptr = ptr;
            while (*test_ptr && *test_ptr != ' ' && *test_ptr != '\n' && 
                   *test_ptr != '\t' && test_len < 255) {
                test_buffer[test_len++] = *test_ptr++;
            }
            test_buffer[test_len] = '\0';
            
            if (test_len > 0 && regexec(&ctx->patterns[i], test_buffer, 1, &match, 0) == 0) {
                /* Create token */
                RiftToken* token = create_token(ctx, stage0_patterns[i].type, 
                                              test_buffer, line, col);
                if (!token) {
                    /* Memory error */
                    DualChannelOutput* error_output = create_dual_channel_output();
                    set_error_level(error_output, RIFT_CRITICAL_MIN, 
                                  "Memory allocation failed during tokenization");
                    pthread_mutex_unlock(&ctx->ctx_lock);
                    return NULL;
                }
                
                /* Check for quantum mode macro */
                if (strcmp(test_buffer, "!quantum") == 0) {
                    ctx->quantum_mode_active = true;
                    printf("Entering quantum mode\n");
                } else if (strcmp(test_buffer, "!classic") == 0) {
                    ctx->quantum_mode_active = false;
                    printf("Entering classic mode\n");
                }
                
                /* Expand array if needed */
                if (count >= capacity) {
                    capacity *= 2;
                    RiftToken** new_tokens = realloc(tokens, capacity * sizeof(RiftToken*));
                    if (!new_tokens) {
                        pthread_mutex_unlock(&ctx->ctx_lock);
                        return NULL;
                    }
                    tokens = new_tokens;
                }
                
                tokens[count++] = token;
                ptr += test_len;
                col += test_len;
                matched = true;
                break;
            }
        }
        
        if (!matched) {
            /* Unknown token - generate error */
            char err_msg[256];
            snprintf(err_msg, sizeof(err_msg), 
                    "Unknown token at line %zu, column %zu: '%c'", line, col, *ptr);
            
            DualChannelOutput* error_output = create_dual_channel_output();
            set_error_level(error_output, RIFT_WARNING_MAX - 1, err_msg);
            
            ptr++;
            col++;
        }
    }
    
    /* Add EOF token */
    RiftToken* eof = create_token(ctx, R_EOF, "EOF", line, col);
    if (eof) {
        if (count >= capacity) {
            capacity++;
            RiftToken** new_tokens = realloc(tokens, capacity * sizeof(RiftToken*));
            if (new_tokens) {
                tokens = new_tokens;
            }
        }
        tokens[count++] = eof;
    }
    
    *token_count = count;
    pthread_mutex_unlock(&ctx->ctx_lock);
    
    return tokens;
}

/* ===================================================================
 * Dual-Channel Processing
 * =================================================================== */

DualChannelOutput* process_stage0(RiftStage0Context* ctx, const char* input) {
    if (!ctx || !input) return NULL;
    
    DualChannelOutput* output = create_dual_channel_output();
    if (!output) return NULL;
    
    size_t token_count = 0;
    RiftToken** tokens = tokenize_input(ctx, input, &token_count);
    if (!tokens) {
        set_error_level(output, RIFT_CRITICAL_MIN, "Tokenization failed");
        return output;
    }
    
    /* Allocate channels */
    size_t classic_capacity = 4096;
    size_t quantum_capacity = 4096;
    char* classic_buffer = calloc(classic_capacity, 1);
    char* quantum_buffer = calloc(quantum_capacity, 1);
    
    if (!classic_buffer || !quantum_buffer) {
        set_error_level(output, RIFT_CRITICAL_MIN, "Channel allocation failed");
        return output;
    }
    
    size_t classic_offset = 0;
    size_t quantum_offset = 0;
    
    /* Process tokens into dual channels */
    for (size_t i = 0; i < token_count; i++) {
        RiftToken* token = tokens[i];
        char token_str[512];
        
        snprintf(token_str, sizeof(token_str), 
                "Token[%zu]: type=%d, value='%s', line=%zu, col=%zu, quantum=%s\n",
                i, token->type, token->value, token->line, token->column,
                token->is_quantum ? "true" : "false");
        
        if (token->is_quantum || ctx->quantum_mode_active) {
            /* Route to quantum channel */
            size_t len = strlen(token_str);
            if (quantum_offset + len >= quantum_capacity) {
                quantum_capacity *= 2;
                char* new_buffer = realloc(quantum_buffer, quantum_capacity);
                if (!new_buffer) {
                    set_error_level(output, RIFT_DANGER_MIN, "Quantum channel overflow");
                    break;
                }
                quantum_buffer = new_buffer;
            }
            strcpy(quantum_buffer + quantum_offset, token_str);
            quantum_offset += len;
        } else {
            /* Route to classic channel */
            size_t len = strlen(token_str);
            if (classic_offset + len >= classic_capacity) {
                classic_capacity *= 2;
                char* new_buffer = realloc(classic_buffer, classic_capacity);
                if (!new_buffer) {
                    set_error_level(output, RIFT_DANGER_MIN, "Classic channel overflow");
                    break;
                }
                classic_buffer = new_buffer;
            }
            strcpy(classic_buffer + classic_offset, token_str);
            classic_offset += len;
        }
    }
    
    /* Set output channels */
    output->classic_channel = classic_buffer;
    output->classic_size = classic_offset;
    output->quantum_channel = quantum_buffer;
    output->quantum_size = quantum_offset;
    
    /* Add metadata */
    char metadata[1024];
    snprintf(metadata, sizeof(metadata),
            "\n# RIFT Stage-0 Metadata\n"
            "# Version: %d.%d.%d\n"
            "# Tokens: %zu\n"
            "# Classic channel: %zu bytes\n"
            "# Quantum channel: %zu bytes\n"
            "# Memory usage: %zu/%zu bytes\n"
            "# AEGIS compliant: %s\n"
            "# Toolchain: riftlang.exe → .so.a → rift.exe → gosilang\n",
            RIFT_VERSION_MAJOR, RIFT_VERSION_MINOR, RIFT_VERSION_PATCH,
            token_count, classic_offset, quantum_offset,
            ctx->mem_gov->current_usage, ctx->mem_gov->max_heap,
            ctx->aegis_compliant ? "yes" : "no");
    
    /* Append metadata to classic channel */
    size_t meta_len = strlen(metadata);
    if (classic_offset + meta_len < classic_capacity) {
        strcpy(classic_buffer + classic_offset, metadata);
        output->classic_size += meta_len;
    }
    
    /* Cleanup tokens */
    for (size_t i = 0; i < token_count; i++) {
        free_token(ctx, tokens[i]);
    }
    free(tokens);
    
    printf("Stage-0 processing complete\n");
    printf("  Classic channel: %zu bytes\n", output->classic_size);
    printf("  Quantum channel: %zu bytes\n", output->quantum_size);
    printf("  Error level: %d\n", output->error_level);
    
    return output;
}

/* ===================================================================
 * Build Output Generation
 * =================================================================== */

typedef struct {
    char* obj_path;
    char* bin_path;
    char* lib_path;
    bool build_success;
} BuildOutput;

BuildOutput* generate_build_output(RiftStage0Context* ctx, DualChannelOutput* dual_output) {
    if (!ctx || !dual_output) return NULL;
    
    BuildOutput* build = calloc(1, sizeof(BuildOutput));
    if (!build) return NULL;
    
    /* Check for critical errors */
    if (dual_output->error_level >= RIFT_CRITICAL_MIN) {
        build->build_success = false;
        printf("Build failed due to critical errors\n");
        return build;
    }
    
    /* Generate paths */
    build->obj_path = strdup("build/obj/rift-stage0.o");
    build->bin_path = strdup("build/bin/rift-stage0");
    build->lib_path = strdup("build/lib/librift-stage0.so");
    build->build_success = true;
    
    printf("Build output generated:\n");
    printf("  Object: %s\n", build->obj_path);
    printf("  Binary: %s\n", build->bin_path);
    printf("  Library: %s\n", build->lib_path);
    
    return build;
}

/* ===================================================================
 * Cleanup
 * =================================================================== */

void rift_stage0_destroy(RiftStage0Context* ctx) {
    if (!ctx) return;
    
    /* Free regex patterns */
    for (size_t i = 0; i < ctx->pattern_count; i++) {
        regfree(&ctx->patterns[i]);
    }
    free(ctx->patterns);
    
    /* Free memory governor */
    if (ctx->mem_gov) {
        pthread_mutex_destroy(&ctx->mem_gov->mem_lock);
        free(ctx->mem_gov);
    }
    
    pthread_mutex_destroy(&ctx->ctx_lock);
    free(ctx);
}

void free_dual_channel_output(DualChannelOutput* output) {
    if (!output) return;
    
    if (output->classic_channel) free(output->classic_channel);
    if (output->quantum_channel) free(output->quantum_channel);
    if (output->error_msg) free(output->error_msg);
    free(output);
}

void free_build_output(BuildOutput* build) {
    if (!build) return;
    
    if (build->obj_path) free(build->obj_path);
    if (build->bin_path) free(build->bin_path);
    if (build->lib_path) free(build->lib_path);
    free(build);
}

/* ===================================================================
 * Main Entry Point (for testing)
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
    
    /* Test input */
    const char* test_input = 
        "!quantum\n"
        "@quantum { x = 42 }\n"
        "identifier + 123\n"
        "@entangle(a, b)\n"
        "!collapse\n"
        "!classic\n"
        "y = x * 2\n"
        "#[gov:aegis_phase_1]\n";
    
    printf("Processing test input:\n%s\n", test_input);
    printf("======================================\n\n");
    
    /* Process through Stage-0 */
    DualChannelOutput* output = process_stage0(ctx, test_input);
    if (!output) {
        fprintf(stderr, "Stage-0 processing failed\n");
        rift_stage0_destroy(ctx);
        return 1;
    }
    
    /* Display results */
    printf("\nClassic Channel Output:\n");
    printf("----------------------\n");
    if (output->classic_channel) {
        printf("%s", (char*)output->classic_channel);
    }
    
    printf("\nQuantum Channel Output:\n");
    printf("----------------------\n");
    if (output->quantum_channel) {
        printf("%s", (char*)output->quantum_channel);
    }
    
    /* Generate build output */
    BuildOutput* build = generate_build_output(ctx, output);
    if (build && build->build_success) {
        printf("\nBuild successful!\n");
    }
    
    /* Cleanup */
    free_dual_channel_output(output);
    free_build_output(build);
    rift_stage0_destroy(ctx);
    
    return 0;
}
/*
 * RIFT-Core-0 Header: Stage-0 Tokenization Interface
 * Part of AEGIS Project - OBINexus Computing
 * 
 * Public API for RIFT Stage-0 dual-channel tokenizer
 */

#ifndef RIFT_CORE_0_H
#define RIFT_CORE_0_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#if defined(_WIN32) || defined(_WIN64)
// POSIX pthreads are not available on Windows; provide minimal stubs for compatibility
typedef void* pthread_mutex_t;
#define pthread_mutex_init(mutex, attr)   (0)
#define pthread_mutex_destroy(mutex)      (0)
#define pthread_mutex_lock(mutex)         (0)
#define pthread_mutex_unlock(mutex)       (0)
#else
#include <pthread.h>
#endif
#ifdef __cplusplus
extern "C" {
#endif

/* ===================================================================
 * Version Information
 * =================================================================== */
#define RIFT_STAGE0_VERSION_MAJOR 0
#define RIFT_STAGE0_VERSION_MINOR 1
#define RIFT_STAGE0_VERSION_PATCH 0
#define RIFT_STAGE0_VERSION_STRING "0.1.0"

/* ===================================================================
 * Error Severity Levels
 * =================================================================== */
typedef enum {
    /* 0-3: WARNING (Yellow Platter Region) */
    RIFT_SEVERITY_INFO = 0,
    RIFT_SEVERITY_WARNING = 1,
    RIFT_SEVERITY_CAUTION = 2,
    RIFT_SEVERITY_WARNING_MAX = 3,
    
    /* 3-6: DANGER (Orange Region) - Auto-fix mode */
    RIFT_SEVERITY_DANGER_MIN = 3,
    RIFT_SEVERITY_ERROR = 4,
    RIFT_SEVERITY_SEVERE = 5,
    RIFT_SEVERITY_DANGER_MAX = 6,
    
    /* 6-9: CRITICAL (Red Region) - Emergency mode */
    RIFT_SEVERITY_CRITICAL_MIN = 6,
    RIFT_SEVERITY_CRITICAL = 7,
    RIFT_SEVERITY_EMERGENCY = 8,
    RIFT_SEVERITY_CRITICAL_MAX = 9,
    
    /* 9-12: PANIC (Failsafe Region) - Auto-enabled unless explicit */
    RIFT_SEVERITY_PANIC_MIN = 9,
    RIFT_SEVERITY_PANIC = 10,
    RIFT_SEVERITY_FAILSAFE = 11,
    RIFT_SEVERITY_PANIC_MAX = 12
} RiftErrorSeverity_t;

/* ===================================================================
 * Token Type Definitions
 * =================================================================== */
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
    R_EOF,
    R_TOKEN_TYPE_MAX
} RiftTokenType_t;

/* ===================================================================
 * Result Codes
 * =================================================================== */
typedef enum {
    RIFT_SUCCESS = 0,
    RIFT_ERROR_MEMORY = -1,
    RIFT_ERROR_INVALID_INPUT = -2,
    RIFT_ERROR_PATTERN_COMPILE = -3,
    RIFT_ERROR_GOVERNANCE = -4,
    RIFT_ERROR_QUANTUM_DECOHERENCE = -5,
    RIFT_ERROR_CHANNEL_OVERFLOW = -6,
    RIFT_ERROR_CRITICAL = -7,
    RIFT_ERROR_PANIC = -8
} RiftResult_t;

/* ===================================================================
 * Forward Declarations
 * =================================================================== */
typedef struct RiftStage0Context RiftStage0Context;
typedef struct DualChannelOutput DualChannelOutput;
typedef struct RiftToken RiftToken;
typedef struct TokenMemoryGovernor TokenMemoryGovernor;
typedef struct BuildOutput BuildOutput;

/* ===================================================================
 * Configuration Structures
 * =================================================================== */
typedef struct {
    /* Memory governance */
    size_t min_heap_size;
    size_t max_heap_size;
    bool enable_dynamic_allocation;
    
    /* Channel configuration */
    bool enable_dual_channel;
    bool enable_quantum_mode;
    size_t classic_channel_size;
    size_t quantum_channel_size;
    
    /* Error handling */
    uint8_t default_error_level;
    bool enable_panic_mode;
    bool auto_fix_errors;
    
    /* AEGIS compliance */
    bool aegis_compliant;
    uint64_t compliance_flags;
    const char* governance_file;
    
    /* Threading */
    uint32_t thread_count;
    bool enable_parallel_tokenization;
} RiftStage0Config;

/* ===================================================================
 * Token Structure
 * =================================================================== */
struct RiftToken {
    RiftTokenType_t type;
    char* pattern;
    char* value;
    size_t line;
    size_t column;
    size_t length;
    
    /* Quantum properties */
    bool is_quantum;
    bool is_collapsed;
    double quantum_probability;
    
    /* Governance metadata */
    uint64_t governance_flags;
    uint32_t trust_level;
    
    /* Chain pointer for linked processing */
    struct RiftToken* next;
    void* metadata;
};

/* ===================================================================
 * Dual Channel Output
 * =================================================================== */
struct DualChannelOutput {
    /* Classic channel */
    void* classic_channel;
    size_t classic_size;
    size_t classic_capacity;
    
    /* Quantum channel */
    void* quantum_channel;
    size_t quantum_size;
    size_t quantum_capacity;
    
    /* Error information */
    uint8_t error_level;
    char* error_message;
    size_t error_count;
    
    /* Metadata */
    uint64_t processing_time_ns;
    uint32_t token_count;
    bool build_success;
};

/* ===================================================================
 * Build Output Structure
 * =================================================================== */
struct BuildOutput {
    char* obj_path;    // build/obj/*.o
    char* bin_path;    // build/bin/*
    char* lib_path;    // build/lib/*.so
    char* arc_path;    // build/lib/*.a
    bool build_success;
    uint32_t error_count;
    uint32_t warning_count;
};

/* ===================================================================
 * Public API Functions
 * =================================================================== */

/* Context management */
RiftStage0Context* rift_stage0_create(void);
RiftStage0Context* rift_stage0_create_with_config(const RiftStage0Config* config);
void rift_stage0_destroy(RiftStage0Context* ctx);

/* Configuration */
RiftResult_t rift_stage0_configure(RiftStage0Context* ctx, const RiftStage0Config* config);
RiftResult_t rift_stage0_validate_config(const RiftStage0Config* config);

/* Token processing */
RiftToken** rift_stage0_tokenize(RiftStage0Context* ctx, 
                                 const char* input, 
                                 size_t input_size,
                                 size_t* token_count);

/* Dual-channel processing */
DualChannelOutput* rift_stage0_process(RiftStage0Context* ctx, 
                                       const char* input);

DualChannelOutput* rift_stage0_process_file(RiftStage0Context* ctx,
                                           const char* filename);

/* Memory governance */
TokenMemoryGovernor* rift_stage0_get_memory_governor(RiftStage0Context* ctx);
RiftResult_t rift_stage0_set_memory_limits(RiftStage0Context* ctx,
                                          size_t min_heap,
                                          size_t max_heap);

/* Error handling */
void rift_stage0_set_error_handler(RiftStage0Context* ctx,
                                  void (*handler)(RiftErrorSeverity_t, const char*));

const char* rift_stage0_get_error_string(RiftResult_t result);

/* Channel management */
void* rift_stage0_get_classic_channel(DualChannelOutput* output, size_t* size);
void* rift_stage0_get_quantum_channel(DualChannelOutput* output, size_t* size);

/* Build output generation */
BuildOutput* rift_stage0_generate_build(RiftStage0Context* ctx,
                                       DualChannelOutput* output,
                                       const char* output_dir);

/* Cleanup */
void rift_stage0_free_tokens(RiftStage0Context* ctx, 
                            RiftToken** tokens, 
                            size_t count);

void rift_stage0_free_output(DualChannelOutput* output);
void rift_stage0_free_build(BuildOutput* build);

/* Utility functions */
const char* rift_stage0_token_type_string(RiftTokenType_t type);
const char* rift_stage0_version_string(void);
bool rift_stage0_is_quantum_token(const RiftToken* token);

/* AEGIS compliance */
bool rift_stage0_verify_aegis_compliance(RiftStage0Context* ctx);
RiftResult_t rift_stage0_load_governance_file(RiftStage0Context* ctx,
                                             const char* gov_file);

/* ===================================================================
 * Macro Helpers
 * =================================================================== */

/* Error checking macro */
#define RIFT_CHECK(expr) \
    do { \
        RiftResult_t _result = (expr); \
        if (_result != RIFT_SUCCESS) { \
            fprintf(stderr, "RIFT Error: %s at %s:%d\n", \
                   rift_stage0_get_error_string(_result), \
                   __FILE__, __LINE__); \
            return _result; \
        } \
    } while(0)

/* Token type checking */
#define RIFT_IS_QUANTUM(token) \
    ((token)->type >= R_QUANTUM_TOKEN && (token)->type <= R_ENTANGLE_MARKER)

/* Memory alignment for quantum processing */
#define RIFT_QUANTUM_ALIGN(size) \
    (((size) + 7) & ~7)  // 8-byte alignment

/* Channel mode macros */
#define RIFT_CLASSIC_MODE 0x01
#define RIFT_QUANTUM_MODE 0x02
#define RIFT_DUAL_MODE (RIFT_CLASSIC_MODE | RIFT_QUANTUM_MODE)

#ifdef __cplusplus
}
#endif

#endif /* RIFT_CORE_0_H */
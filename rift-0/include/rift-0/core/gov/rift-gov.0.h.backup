

#ifndef RIFT_GOV_0_H
#define RIFT_GOV_0_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#if defined(_WIN32) || defined(_WIN64)
typedef void* pthread_mutex_t;
#define pthread_mutex_init(mutex, attr)   (0)
#define pthread_mutex_destroy(mutex)      (0)
#define pthread_mutex_lock(mutex)         (0)
#define pthread_mutex_unlock(mutex)       (0)
// Provide a stub for regex_t on Windows
typedef void* regex_t;
#else
#include <pthread.h>
#include <regex.h>
#endif


/* ===================================================================
 * Governance Structures
 * ===================================================================*/

/**
 * Token pattern definition for Stage-0 tokenizer
 */
typedef struct {
    const char* name;           /* Pattern name */
    const char* pattern;        /* Regular expression pattern */
    RiftTokenType type;         /* Token type to assign */
    int is_quantum;             /* Quantum channel flag */
    int priority;               /* Pattern matching priority */
    regex_t compiled_regex;     /* Compiled regex (runtime) */
} TokenPattern;

/**
 * Governance configuration structure
 */
typedef struct {
    /* Compliance flags */
    uint32_t zero_trust_enabled : 1;
    uint32_t anti_ghosting_enabled : 1;
    uint32_t audit_trail_enabled : 1;
    uint32_t strict_mode : 1;
    uint32_t reserved_flags : 28;
    
    /* Error thresholds */
    int warning_min;
    int warning_max;
    int danger_min;
    int danger_max;
    int critical_min;
    int critical_max;
    int panic_min;
    int panic_max;
    
    /* Memory governance */
    size_t min_allocation;
    size_t max_allocation;
    const char* scheduler_type;
} GovernanceConfig;

/**
 * AEGIS compliance record
 */
typedef struct {
    uint64_t timestamp;
    uint32_t compliance_level;
    uint32_t violations;
    const char* audit_log;
} AegisComplianceRecord;

/* ===================================================================
 * Pattern Definitions
 * ===================================================================*/

/**
 * Stage-0 token patterns array
 * Defined in implementation file to avoid multiple definition errors
 */
extern const TokenPattern stage0_patterns[];
extern const size_t stage0_patterns_count;

/* ===================================================================
 * Governance Functions
 * ===================================================================*/

/**
 * Initialize governance subsystem
 * @param config Governance configuration
 * @return 0 on success, error code on failure
 */
int rift_gov_init(const GovernanceConfig* config);

/**
 * Cleanup governance subsystem
 */
void rift_gov_cleanup(void);

/**
 * Compile token patterns for use
 * @param patterns Array of token patterns
 * @param count Number of patterns
 * @return 0 on success, error code on failure
 */
int rift_gov_compile_patterns(TokenPattern* patterns, size_t count);

/**
 * Free compiled patterns
 * @param patterns Array of token patterns
 * @param count Number of patterns
 */
void rift_gov_free_patterns(TokenPattern* patterns, size_t count);

/**
 * Check governance compliance
 * @param flags Compliance flags to check
 * @return true if compliant, false otherwise
 */
bool rift_gov_check_compliance(uint32_t flags);

/**
 * Record compliance violation
 * @param violation_type Type of violation
 * @param details Violation details
 */
void rift_gov_record_violation(uint32_t violation_type, const char* details);

/**
 * Get compliance record
 * @return Current compliance record
 */
AegisComplianceRecord rift_gov_get_compliance_record(void);

/**
 * Validate memory allocation against governance rules
 * @param size Requested allocation size
 * @return true if allowed, false otherwise
 */
bool rift_gov_validate_allocation(size_t size);

/**
 * Get error level color code
 * @param level Error level (0-12)
 * @return Color name string
 */
const char* rift_gov_get_error_color(int level);

/* ===================================================================
 * Error Level Definitions
 * ===================================================================*/

#define RIFT_ERROR_WARNING_MIN 0
#define RIFT_ERROR_WARNING_MAX 3
#define RIFT_ERROR_DANGER_MIN  3
#define RIFT_ERROR_DANGER_MAX  6
#define RIFT_ERROR_CRITICAL_MIN 6
#define RIFT_ERROR_CRITICAL_MAX 9
#define RIFT_ERROR_PANIC_MIN   9
#define RIFT_ERROR_PANIC_MAX   12

/* ===================================================================
 * Compliance Flags
 * ===================================================================*/

#define RIFT_GOV_ZERO_TRUST    0x00000001
#define RIFT_GOV_ANTI_GHOST    0x00000002
#define RIFT_GOV_AUDIT_TRAIL   0x00000004
#define RIFT_GOV_STRICT_MODE   0x00000008
#define RIFT_GOV_QUANTUM_SAFE  0x00000010
#define RIFT_GOV_MEMORY_SAFE   0x00000020
#define RIFT_GOV_THREAD_SAFE   0x00000040
#define RIFT_GOV_AEGIS_FULL    0x000000FF
// --- Core Types: always visible, only one definition ---
typedef struct {
    const char* name;
    const char* pattern;
    int type; // Use RiftTokenType if available
    bool is_quantum;
} TokenPattern;

typedef struct TokenMemoryGovernor {
    size_t min_heap;
    size_t max_heap;
    size_t current_usage;
    bool dynamic_allowed;
    pthread_mutex_t mem_lock;
} TokenMemoryGovernor;

typedef struct {
    void* classic_channel;
    size_t classic_size;
    void* quantum_channel;
    size_t quantum_size;
    uint8_t error_level;
    char* error_msg;
} DualChannelOutput;

typedef struct {
    int stage_id;
    int priority; // Lower = higher priority (min-heap)
    char name[64];
    char description[256];
    bool active;
} RiftStageEntry;

typedef struct {
    RiftStageEntry* entries;
    size_t count;
    size_t capacity;
    // Heap property: entries[0] is always the min (highest priority)
} RiftStageQueue;

typedef struct {
    // Core state
    bool initialized;
    uint32_t stage_id;
    uint32_t version;
    // Token patterns
    regex_t* patterns;
    size_t pattern_count;
    // Memory governance
    TokenMemoryGovernor* mem_gov;
    // Dual-channel configuration
    bool dual_mode_enabled;
    bool quantum_mode_active;
    // Error tracking
    uint8_t current_error_level;
    char error_buffer[1024];
    // AEGIS compliance
    bool aegis_compliant;
    uint64_t compliance_flags;
    // Thread management
    pthread_mutex_t ctx_lock;
    uint32_t thread_count;
} RiftStage0Context;

typedef struct {
    // Token fields
    int type;
    char* pattern;
    char* value;
    size_t line;
    size_t column;
    bool is_quantum;
    bool is_collapsed;
    uint64_t governance_flags;
    void* metadata;
} RiftToken;

#ifdef __cplusplus
extern "C" {
#endif

// Priority queue API
void rift_stage_queue_init(RiftStageQueue* queue, size_t capacity);
void rift_stage_queue_free(RiftStageQueue* queue);
void rift_stage_queue_push(RiftStageQueue* queue, const RiftStageEntry* entry);
RiftStageEntry rift_stage_queue_pop(RiftStageQueue* queue);
bool rift_stage_queue_empty(const RiftStageQueue* queue);

// Stage tracker API
void rift_stage_tracker_load_from_xml(RiftStageQueue* queue, const char* xml_path);
void rift_stage_tracker_load_from_json(RiftStageQueue* queue, const char* json_path);

// Utility: Find stage by name or id
RiftStageEntry* rift_stage_queue_find_by_id(RiftStageQueue* queue, int stage_id);
RiftStageEntry* rift_stage_queue_find_by_name(RiftStageQueue* queue, const char* name);


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
} rift_gov_config_t;

/* ===================================================================
 * Build Output Structure
 * =================================================================== */
typedef struct BuildOutput {
    char* obj_path;    // build/obj/*.o
    char* bin_path;    // build/bin/*
    char* lib_path;    // build/lib/*.so
    char* arc_path;    // build/lib/*.a
    bool build_success;
    uint32_t error_count;
    uint32_t warning_count;
} BuildOutput;


// Stage-0 Patterns (extern)
extern const TokenPattern stage0_patterns[];
extern const size_t stage0_patterns_count;

// Memory Governor API
TokenMemoryGovernor* create_memory_governor(size_t min_heap, size_t max_heap);
void* governed_malloc(TokenMemoryGovernor* gov, size_t size);
void governed_free(TokenMemoryGovernor* gov, void* ptr, size_t size);


/**
 * RIFT-0 Governance Compliance Header
 * Auto-generated for Stage-0 (Tokenization & Lexical Analysis)
 * Based on schema.json and AEGIS/PoliC governance requirements
 *
 * Ensures:
 *   - Governance metadata validation for rift-0
 *   - Tokenizer/lexer substage compliance
 *   - Stage 5 optimizer security hooks (future-proof)
 *   - Fallback and nlink integration
 *   - C API for rift-0 governance validation
 */

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
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


// AEGIS Governance Constants
#define MAX_PATH_LENGTH 512
#define MAX_STAGE_COUNT 7
#define MAX_SUBSTAGES_PER_STAGE 4
#define GOVERNANCE_EXPIRY_DAYS 90
#define SHA256_DIGEST_LENGTH 32

// Stage Type Enumeration
typedef enum {
    STAGE_TYPE_LEGACY = 0,
    STAGE_TYPE_EXPERIMENTAL = 1,
    STAGE_TYPE_STABLE = 2
} stage_type_t;

// Validation Result Codes
typedef enum {
    VALIDATION_SUCCESS = 0,
    VALIDATION_SCHEMA_VIOLATION = 1,
    VALIDATION_EXPIRED_GOVERNANCE = 2,
    VALIDATION_SEMVERX_VIOLATION = 3,
    VALIDATION_MISSING_GOVERNANCE = 4,
    VALIDATION_STAKEHOLDER_UNAUTHORIZED = 5,
    VALIDATION_CRITICAL_FAILURE = 6
} validation_result_t;

// Stakeholder Authorization Classes
typedef enum {
    STAKEHOLDER_USER = 1,
    STAKEHOLDER_DEVELOPER = 2,
    STAKEHOLDER_VENDOR = 4
} stakeholder_class_t;

// Governance Configuration Structure
typedef struct {
    char package_name[128];
    char version[32];
    char timestamp[32];
    int stage;
    stage_type_t stage_type;
    int semverx_lock;
    char entry_point[256];
    int nlink_enabled;
    stakeholder_class_t authorized_stakeholders;
} governance_config_t;

// Stage 5 Optimizer Security Structure
typedef struct {
    char optimizer_model[64];
    int minimization_verified;
    char path_hash[65];          // SHA-256 hex string + null terminator
    char post_optimization_hash[65];
    int audit_enabled;
    char security_level[32];
    int semantic_equivalence_proof;
} stage5_optimizer_t;

// Validation Context Structure
typedef struct {
    char project_root[MAX_PATH_LENGTH];
    int verbose_mode;
    int strict_mode;
    FILE *validation_log;
    governance_config_t stage_configs[MAX_STAGE_COUNT];
    int validated_stages;
} validation_context_t;



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


// ...existing code...




// ...existing code...

// --- Stage 5 Optimizer Security (future-proof) ---
typedef struct {
    char optimizer_model[64];
    int minimization_verified;
    char path_hash[65];
    char post_optimization_hash[65];
    int audit_enabled;
    char security_level[32];
    char transformation_log[256];
    int semantic_equivalence_proof;
} rift_stage5_optimizer_t;

// --- Fallback Governance ---
typedef struct {
    int enabled;
    char fallback_directory[64];
    int experimental_bypass;
    int halt_on_critical;
} rift_fallback_gov_t;

// --- NLink Integration ---
typedef struct {
    int semverx_strict_mode;
    int hot_swap_validation;
    int component_lifecycle_tracking;
    int polybuild_coordination;
} rift_nlink_integration_t;



/**
 * Parse and validate rift-0 governance configuration from JSON file
 * @param file_path Path to governance JSON file
 * @param config Output: parsed config struct
 * @return 0 on success, nonzero on error
 */
int rift_gov0_parse_config(const char *file_path, rift_gov_config_t *config);

/**
 * Validate tokenization/lexical analysis governance for rift-0
 * @param config Parsed config struct
 * @return 0 if compliant, nonzero if violation
 */
int rift_gov0_validate_tokenizer(const rift_gov_config_t *config);

/**
 * Validate fallback governance policy
 * @param fallback Fallback config struct
 * @return 0 if fallback allowed, nonzero if not
 */
int rift_gov0_validate_fallback(const rift_fallback_gov_t *fallback);

/**
 * Validate nlink integration policy
 * @param nlink NLink config struct
 * @return 0 if compliant, nonzero if not
 */
int rift_gov0_validate_nlink(const rift_nlink_integration_t *nlink);

#ifdef __cplusplus
}
#endif

#endif 
/**
 * @file rift-gov.0.h
 * @brief RIFT Stage-0 Governance and Pattern Definitions
 * @author OBINexus AEGIS Project
 * 
 * This header defines the governance structures and token patterns
 * for RIFT Stage-0 with proper type isolation.
 */


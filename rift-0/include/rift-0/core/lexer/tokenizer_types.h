#ifndef RIFT_TOKENIZER_TYPES_H
#define RIFT_TOKENIZER_TYPES_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
typedef struct TokenizerContext TokenizerContext;
typedef struct DFAStateMachine DFAStateMachine;
typedef struct DFAState DFAState;
typedef struct RegexComposition RegexComposition;
typedef struct TokenizerStats TokenizerStats;
typedef struct PatternMatchResult PatternMatchResult;
typedef struct TokenizationResult TokenizationResult;

/* Tokenizer configuration */
typedef struct {
    uint32_t processing_flags;
    int validation_level;
    bool trust_tagging_enabled;
    bool preserve_matched_state;
    const char* output_format;
} rift_tokenizer_config_t;

/* Result type for tokenizer operations */
typedef enum {
    RIFT_TOKENIZER_SUCCESS = 0,
    RIFT_TOKENIZER_ERROR_INVALID_INPUT,
    RIFT_TOKENIZER_ERROR_MEMORY,
    RIFT_TOKENIZER_ERROR_PATTERN,
    RIFT_TOKENIZER_ERROR_STATE
} rift_tokenizer_result_t;

/* Token types enumeration */
typedef enum TokenType {
    TOKEN_UNKNOWN = 0,
    TOKEN_IDENTIFIER,
    TOKEN_LITERAL_NUMBER,
    TOKEN_LITERAL_STRING,
    TOKEN_OPERATOR,
    TOKEN_KEYWORD,
    TOKEN_WHITESPACE,
    TOKEN_COMMENT,
    TOKEN_NULL_KEYWORD,
    TOKEN_NIL_KEYWORD,
    TOKEN_ERROR,
    TOKEN_EOF,
    TOKEN_TYPE_COUNT
} TokenType;

/* Use TokenType directly as RiftTokenType */
typedef TokenType RiftTokenType;

/* Token flags */
typedef enum TokenFlags {
    TOKEN_FLAG_NONE = 0x00,
    TOKEN_FLAG_TRUSTED = 0x01,
    TOKEN_FLAG_VERIFIED = 0x02,
    TOKEN_FLAG_SEMANTIC = 0x04,
    TOKEN_FLAG_METADATA = 0x08
} TokenFlags;

/* Token triplet structure */
typedef struct TokenTriplet {
    uint8_t type;      /* TokenType */
    uint16_t mem_ptr;  /* Memory pointer/position */
    uint8_t value;     /* Token flags or additional data */
} TokenTriplet;

/* Tokenizer error codes */
typedef enum TokenizerErrorCode {
    RIFT_TOKENIZER_ERROR_NONE = 0,
    RIFT_TOKENIZER_ERROR_NULL_CONTEXT,
    RIFT_TOKENIZER_ERROR_ALLOCATION_FAILED,
    RIFT_TOKENIZER_ERROR_INVALID_PATTERN,
    RIFT_TOKENIZER_ERROR_BUFFER_OVERFLOW,
    RIFT_TOKENIZER_ERROR_INVALID_STATE
} TokenizerErrorCode;

/* Constants */
#define RIFT_TOKENIZER_DEFAULT_CAPACITY 1024
#define RIFT_TOKENIZER_MAX_TOKENS 65536
#define RIFT_TOKENIZER_MAX_PATTERNS 256
#define RIFT_DEFAULT_TOKEN_CAPACITY 512

/* Version info */
#define RIFT_TOKENIZER_VERSION "0.1.0"
#define RIFT_TOKENIZER_VERSION_MAJOR 0
#define RIFT_TOKENIZER_VERSION_MINOR 1
#define RIFT_TOKENIZER_VERSION_PATCH 0

/* DFA State structure */
struct DFAState {
    uint32_t state_id;
    bool is_final;
    bool is_start;
    char transition_char;
    struct DFAState* next_state;
    struct DFAState* fail_state;
    TokenType token_type;
    size_t match_count;
};

/* DFA State Machine structure */
struct DFAStateMachine {
    int state;
    struct DFAState* start_state;
    struct DFAState* current_state;
};

/* Regex composition structure */
struct RegexComposition {
    bool is_compiled;
    struct DFAState* start_state;
    char* pattern;
    TokenFlags flags;
};

/* Pattern match result */
struct PatternMatchResult {
    bool matched;
    size_t match_length;
    TokenType token_type;
};

/* Tokenization result */
struct TokenizationResult {
    bool success;
    TokenTriplet* tokens;
    size_t count;
    char* error_message;
};

/* Tokenizer statistics */
struct TokenizerStats {
    size_t tokens_processed;
    size_t tokens_generated;
    size_t memory_allocated;
    size_t memory_peak;
    size_t dfa_states_created;
    double processing_time;
    uint32_t error_count;
};

/* Main tokenizer context structure */
struct TokenizerContext {
    /* Token storage */
    TokenTriplet* tokens;
    TokenTriplet* token_buffer;
    size_t token_count;
    size_t token_capacity;
    
    /* Pattern storage */
    RegexComposition** regex_patterns;
    size_t pattern_count;
    size_t pattern_capacity;
    
    /* Input handling */
    const char* input_buffer;
    size_t input_length;
    size_t current_position;
    
    /* Position tracking */
    size_t line_number;
    size_t column_number;
    
    /* Configuration */
    TokenFlags global_flags;
    bool debug_mode;
    bool strict_mode;
    bool thread_safe_mode;
    
    /* Error handling */
    bool has_error;
    TokenizerErrorCode error_code;
    char* error_message;
    
    /* Statistics */
    TokenizerStats stats;
};

/* Alternative context type name */
typedef struct TokenizerContext rift_tokenizer_context_t;

#ifdef __cplusplus
}
#endif

#endif /* RIFT_TOKENIZER_TYPES_H */

/* Additional token types for DSL processing */
#define TOKEN_DELIMITER TOKEN_OPERATOR  /* Temporary alias until proper implementation */
#define TOKEN_R_PATTERN TOKEN_LITERAL_STRING  /* R-pattern tokens */

/* DSL-specific token categories */
typedef enum {
    TOKEN_DSL_RULE = TOKEN_TYPE_COUNT,
    TOKEN_DSL_ACTION,
    TOKEN_DSL_DIRECTIVE,
    TOKEN_DSL_PATTERN,
    TOKEN_DSL_COUNT
} DSLTokenType;


/* Additional token types for comprehensive testing */
#ifndef TOKEN_LITERAL_INT
#define TOKEN_LITERAL_INT TOKEN_LITERAL_NUMBER
#endif

#ifndef TOKEN_LITERAL_FLOAT  
#define TOKEN_LITERAL_FLOAT TOKEN_LITERAL_NUMBER
#endif

/* DFA state definitions */
enum {
    DFA_STATE_START = 0,
    DFA_STATE_ACCEPT = 1,
    DFA_STATE_REJECT = -1
};

#endif /* Include guard end */

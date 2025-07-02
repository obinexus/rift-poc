
#ifndef RIFT_GOV_0_H
#define RIFT_GOV_0_H

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

// --- Governance Config Structures (mirroring schema.json) ---

typedef enum {
    RIFT_STAGE_LEGACY = 0,
    RIFT_STAGE_EXPERIMENTAL = 1,
    RIFT_STAGE_STABLE = 2
} rift_stage_type_t;

typedef struct {
    char package_name[128];
    char version[32];
    char timestamp[32];
    int stage;
    rift_stage_type_t stage_type;
    char description[256];
    int semverx_lock;
    char entry_point[256];
    int nlink_enabled;
    // --- Tokenizer substage ---
    struct {
        int lexeme_validation;
        int token_memory_constraints;
        int encoding_normalization;
    } tokenizer;
    // --- Parser substage ---
    struct {
        int ast_depth_limit;
        char syntax_strictness[16];
        int error_recovery;
    } parser;
    // --- Semantic substage ---
    struct {
        int type_checking;
        int scope_validation;
        int symbol_table_integrity;
    } semantic;
    // --- Validator substage ---
    struct {
        int structural_acyclicity;
        int cost_bounds_enforced;
        int governance_hash_required;
    } validator;
    // --- Bytecode substage ---
    struct {
        int opcode_validation;
        int complexity_limits;
        int operand_alignment;
    } bytecode;
    // --- Verifier substage ---
    struct {
        int bytecode_integrity;
        int stack_safety;
        int memory_bounds;
    } verifier;
    // --- Emitter substage ---
    struct {
        char target_architecture[32];
        int optimization_level;
        int debug_symbols;
    } emitter;
} rift_gov_config_t;

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

// --- API: Governance Validation for rift-0 ---

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

#endif // RIFT_GOV_0_H

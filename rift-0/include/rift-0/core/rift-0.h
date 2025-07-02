/**
 * @file rift-0.h
 * @brief RIFT Stage-0 Core API - Fixed type definitions
 * @author OBINexus AEGIS Project
 * 
 * This header defines the core API for RIFT Stage-0 tokenizer with
 * proper type definitions to avoid conflicts.
 */

#ifndef RIFT_0_CORE_H
#define RIFT_0_CORE_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

/* Include sub-headers in correct order to avoid conflicts */
#include "rift-0/core/lexer/tokenizer_types.h"

/* Forward declarations to avoid circular dependencies */
typedef struct RiftStage0Context RiftStage0Context;
typedef struct RiftStage0Config RiftStage0Config;
typedef struct DualChannelOutput DualChannelOutput;
typedef struct BuildArtifact BuildArtifact;

/* RIFT Stage-0 Configuration Structure */
struct RiftStage0Config {
    /* Memory configuration */
    size_t min_heap_size;
    size_t max_heap_size;
    const char* memory_scheduler;
    
    /* Feature flags */
    bool enable_quantum_mode;
    bool enable_panic_mode;
    bool aegis_compliance;
    
    /* Error handling */
    int warning_threshold;
    int danger_threshold;
    int critical_threshold;
    int panic_threshold;
    
    /* Governance */
    const char* governance_file;
    bool zero_trust_enabled;
    bool anti_ghosting_enabled;
};

/* RIFT Stage-0 Context Structure */
struct RiftStage0Context {
    /* Configuration */
    RiftStage0Config config;
    
    /* State management */
    void* lexer_state;
    void* parser_state;
    uint32_t compliance_flags;
    
    /* Error tracking */
    int error_level;
    char* last_error;
    
    /* Memory management */
    void* heap_base;
    size_t heap_used;
    
    /* Dual channel state */
    bool quantum_channel_active;
    void* quantum_state;
};


// Use TokenPattern from rift-gov.0.h only

/* Dual Channel Output Structure */
struct DualChannelOutput {
    /* Classic channel */
    RiftToken** classic_tokens;
    size_t classic_count;
    
    /* Quantum channel */
    void* quantum_data;
    size_t quantum_size;
    
    /* Metadata */
    uint32_t governance_flags;
    bool channels_synchronized;
};

/* Build Artifact Structure */
struct BuildArtifact {
    char* obj_path;
    char* bin_path;
    char* lib_path;
    bool build_success;
};

/* ===================================================================
 * Core API Functions
 * ===================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Create a new RIFT Stage-0 context with default configuration
 * @return Pointer to new context or NULL on failure
 */
RiftStage0Context* rift_stage0_create(void);

/**
 * Create a new RIFT Stage-0 context with custom configuration
 * @param config Configuration structure
 * @return Pointer to new context or NULL on failure
 */
RiftStage0Context* rift_stage0_create_with_config(const RiftStage0Config* config);

/**
 * Destroy a RIFT Stage-0 context and free resources
 * @param ctx Context to destroy
 */
void rift_stage0_destroy(RiftStage0Context* ctx);

/**
 * Process input through Stage-0 tokenizer
 * @param ctx Stage-0 context
 * @param input Input string to tokenize
 * @return Dual channel output structure
 */
DualChannelOutput* rift_stage0_process(RiftStage0Context* ctx, const char* input);

/**
 * Free dual channel output structure
 * @param output Output to free
 */
void rift_stage0_free_output(DualChannelOutput* output);

/**
 * Get current error level
 * @param ctx Stage-0 context
 * @return Error level (0-12)
 */
int rift_stage0_get_error_level(const RiftStage0Context* ctx);

/**
 * Get last error message
 * @param ctx Stage-0 context
 * @return Error message or NULL
 */
const char* rift_stage0_get_last_error(const RiftStage0Context* ctx);

/**
 * Enable quantum channel
 * @param ctx Stage-0 context
 * @return true on success, false on failure
 */
bool rift_stage0_enable_quantum_channel(RiftStage0Context* ctx);

/**
 * Validate AEGIS compliance
 * @param ctx Stage-0 context
 * @return true if compliant, false otherwise
 */
bool rift_stage0_validate_aegis_compliance(const RiftStage0Context* ctx);

/**
 * Generate build artifacts
 * @param ctx Stage-0 context
 * @return Build artifact structure
 */
BuildArtifact* rift_stage0_generate_build(RiftStage0Context* ctx);

/**
 * Free build artifact structure
 * @param artifact Artifact to free
 */
void rift_stage0_free_build_artifact(BuildArtifact* artifact);

#ifdef __cplusplus
}
#endif

#endif /* RIFT_0_CORE_H */
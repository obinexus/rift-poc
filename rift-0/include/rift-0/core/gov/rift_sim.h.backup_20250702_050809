
// =============================================================================
// SIMULATED CONCURRENCY MODULE - rift_simulated.h
// =============================================================================

#ifndef RIFT_SIMULATED_H
#define RIFT_SIMULATED_H

#include "rift_common.h"

// Simulated concurrency specific structures
typedef struct {
    rift_thread_context_t base_context;   // Common thread context
    uint32_t time_slice_us;               // Time slice in microseconds
    uint32_t current_slice;               // Current time slice counter
    bool yield_requested;                 // Cooperative yield flag
    void (*work_function)(void*);         // Work function pointer
    void* work_data;                      // Work function data
} rift_simulated_context_t;

/**
 * @brief Initialize simulated concurrency subsystem
 * @return 0 on success, error code otherwise
 */
int rift_simulated_init(void);

/**
 * @brief Create new simulated concurrent task
 * @param parent_id Parent RIFT thread ID (0 for root)
 * @param policy Governance policy for new task
 * @param work_func Work function to execute
 * @param work_data Data to pass to work function
 * @param spawn_location Source location of spawn
 * @return RIFT thread ID on success, 0 on failure
 */
uint64_t rift_simulated_spawn(uint64_t parent_id, 
                              const rift_governance_policy_t* policy,
                              void (*work_func)(void*), 
                              void* work_data,
                              const char* spawn_location);

/**
 * @brief Execute one scheduling cycle of simulated concurrency
 * @return Number of active tasks processed
 */
int rift_simulated_schedule_cycle(void);

/**
 * @brief Request cooperative yield from current task
 */
void rift_simulated_yield(void);

/**
 * @brief Terminate simulated concurrent task
 * @param rift_id RIFT thread ID to terminate
 * @return 0 on success, error code otherwise
 */
int rift_simulated_terminate(uint64_t rift_id);

/**
 * @brief Clean up simulated concurrency subsystem
 */
void rift_simulated_cleanup(void);

#endif // RIFT_SIMULATED_H

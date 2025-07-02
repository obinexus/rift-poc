
// =============================================================================
// TRUE CONCURRENCY MODULE - rift_true_concurrency.h  
// =============================================================================

#ifndef RIFT_TRUE_CONCURRENCY_H
#define RIFT_TRUE_CONCURRENCY_H

#include "rift_common.h"

// True concurrency specific structures
typedef struct {
    rift_thread_context_t base_context;   // Common thread context
    pthread_t pthread_handle;             // POSIX thread handle
    pid_t child_process_id;               // Child process ID (if process mode)
    pthread_mutex_t lifecycle_mutex;      // Thread lifecycle synchronization
    pthread_cond_t lifecycle_condition;   // Thread lifecycle condition
    void (*work_function)(void*);         // Work function pointer
    void* work_data;                      // Work function data
} rift_true_context_t;

/**
 * @brief Initialize true concurrency subsystem
 * @return 0 on success, error code otherwise
 */
int rift_true_concurrency_init(void);

/**
 * @brief Spawn new thread with true concurrency
 * @param parent_id Parent RIFT thread ID
 * @param policy Governance policy for new thread
 * @param work_func Work function to execute
 * @param work_data Data to pass to work function
 * @param spawn_location Source location of spawn
 * @return RIFT thread ID on success, 0 on failure
 */
uint64_t rift_true_spawn_thread(uint64_t parent_id,
                                const rift_governance_policy_t* policy,
                                void (*work_func)(void*),
                                void* work_data,
                                const char* spawn_location);

/**
 * @brief Spawn new process with true concurrency
 * @param parent_id Parent RIFT thread ID
 * @param policy Governance policy for new process
 * @param work_func Work function to execute
 * @param work_data Data to pass to work function
 * @param spawn_location Source location of spawn
 * @return RIFT thread ID on success, 0 on failure
 */
uint64_t rift_true_spawn_process(uint64_t parent_id,
                                 const rift_governance_policy_t* policy,
                                 void (*work_func)(void*),
                                 void* work_data,
                                 const char* spawn_location);

/**
 * @brief Handle parent destruction with policy enforcement
 * @param parent_id RIFT ID of destroyed parent
 * @return 0 on success, error code otherwise
 */
int rift_true_handle_parent_destruction(uint64_t parent_id);

/**
 * @brief Terminate thread or process
 * @param rift_id RIFT thread ID to terminate
 * @return 0 on success, error code otherwise
 */
int rift_true_terminate(uint64_t rift_id);

/**
 * @brief Clean up true concurrency subsystem
 */
void rift_true_concurrency_cleanup(void);

#endif // RIFT_TRUE_CONCURRENCY_H

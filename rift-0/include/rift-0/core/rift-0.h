/*
 * RIFT-Core-0 Header: Stage-0 Tokenization Interface
 * Part of AEGIS Project - OBINexus Computing
 * 
 * Public API for RIFT Stage-0 dual-channel tokenizer
 */

#ifndef RIFT_CORE_0_H
#define RIFT_CORE_0_H
#include <regex.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "rift-0/core/gov/rift-gov.0.h"
#ifdef __cplusplus
extern "C" {
#endif




// Public API declarations (implementations elsewhere)
RiftStage0Context* rift_stage0_create(void);
RiftStage0Context* rift_stage0_create_with_config(const RiftStage0Config* config);
void rift_stage0_destroy(RiftStage0Context* ctx);
// ...other API declarations as needed...

#ifdef __cplusplus
}
#endif

#endif /* RIFT_CORE_0_H */
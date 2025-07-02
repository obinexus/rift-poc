
#ifndef RIFT_R_UML_PATTERNS_H
#define RIFT_R_UML_PATTERNS_H

/**
 * r_uml_patterns Module Header
 * RIFT1 - AEGIS Framework
 * OBINexus Computing
 *
 * Auto-generated header for QA compliance
 */

#include "include/core/rift.h"
#include <stddef.h>
#include <stdbool.h>

// RIFT-style regex pattern macros (C11-compliant)
#define R_COMPOSITION_PATTERN "([A-Za-z_][A-Za-z0-9_]*)\s+composed_of\s+([A-Za-z_][A-Za-z0-9_]*)"
#define R_ASSOCIATION_PATTERN "([A-Za-z_][A-Za-z0-9_]*)\s+associated_with\s+([A-Za-z_][A-Za-z0-9_]*)"
#define R_AGGREGATION_PATTERN "([A-Za-z_][A-Za-z0-9_]*)\s+aggregate\s+([A-Za-z_][A-Za-z0-9_]*)"
#define R_INHERITANCE_PATTERN "([A-Za-z_][A-Za-z0-9_]*)\s+(extends|inherits)\s+([A-Za-z_][A-Za-z0-9_]*)"

// Boolean and logical operation macros for analytics and governance
#define R_AND(a, b) ((a) && (b))
#define R_OR(a, b)  ((a) || (b))
#define R_NOT(a)    (!(a))

// For future: recursive descent/top-down and bottom-up extensibility
// Use these macros and helpers in analytics, multi-channel parsing, and governance

// Token type mapping (example)
typedef enum {
    R_INIT_EMPTY = 0,
    R_UML_COMPOSITION,
    R_UML_ASSOCIATION,
    R_UML_AGGREGATION,
    R_UML_INHERITANCE,
    R_END_EOFR
} rift_uml_token_type_t;

// Forward declarations for UML relationship and governance
typedef struct uml_relationship uml_relationship_t;
typedef struct governance_triangle governance_triangle_t;

// Function prototypes (public API)
uml_relationship_t *parse_uml_relationship(const char *pattern, const char *source);
bool validate_uml_governance(uml_relationship_t *rel);
void generate_uml_code(uml_relationship_t *rel, char *output_buffer, size_t buffer_size);

// Boolean helpers for CLI/core analytics
static inline bool rift_and(bool a, bool b) { return a && b; }
static inline bool rift_or(bool a, bool b) { return a || b; }
static inline bool rift_not(bool a) { return !a; }

// For future: recursive descent/top-down and bottom-up extensibility
// void rift_recursive_descent(...);
// void rift_bottom_up_analysis(...);

#endif // RIFT_R_UML_PATTERNS_H

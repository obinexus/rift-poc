#ifndef RIFT_TOKEN_TYPES_GEN_H
#define RIFT_TOKEN_TYPES_GEN_H

typedef enum {
    R_INIT_EMPTY = 0,
    R_IDENTIFIER = 1,
    R_NUMBER = 2,
    R_OPERATOR = 3,
    R_KEYWORD = 4,
    R_STRING = 5,
    R_COMMENT = 6,
    R_WHITESPACE = 7,
    R_QUANTUM_TOKEN = 8,
    R_COLLAPSE_MARKER = 9,
    R_ENTANGLE_MARKER = 10,
    R_GOVERNANCE_TAG = 11,
    R_CUSTOM_PATTERN = 12,
    R_EOF = 13,
    R_TOKEN_TYPE_COUNT
} RiftTokenType

#endif /* RIFT_TOKEN_TYPES_GEN_H */

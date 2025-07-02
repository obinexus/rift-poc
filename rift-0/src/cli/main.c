
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rift-0/core/rift-0.h"
#include "rift-0/lexer.h"
#include "r_extensions/uml/r_uml_patterns.h"

void print_usage() {
    printf("RIFT Stage-0 CLI\n");
    printf("Usage: riftlang <command> [options]\n");
    printf("Commands:\n");
    printf("  token-type <input>      Analyze token types\n");
    printf("  token-mem <input>       Analyze token memory\n");
    printf("  token-value <input>     Analyze token values\n");
    printf("  uml-parse <pattern> <source>   Parse UML relationship\n");
    printf("  uml-validate <pattern> <source> Validate UML governance\n");
    printf("  uml-generate <pattern> <source> Generate UML code\n");
    printf("  --help                  Show this help message\n");
}

int main(int argc, char* argv[]) {
    if (argc < 2 || strcmp(argv[1], "--help") == 0) {
        print_usage();
        return 0;
    }

    // Stage-0 context for token analytics
    RiftStage0Context* ctx = rift_stage0_create();
    if (!ctx) {
        fprintf(stderr, "Failed to initialize Stage-0 context\n");
        return 1;
    }

    if (strcmp(argv[1], "token-type") == 0 && argc >= 3) {
        // TODO: Call token type analytics (stub)
        printf("[token-type] Not yet implemented. Input: %s\n", argv[2]);
    } else if (strcmp(argv[1], "token-mem") == 0 && argc >= 3) {
        // TODO: Call token memory analytics (stub)
        printf("[token-mem] Not yet implemented. Input: %s\n", argv[2]);
    } else if (strcmp(argv[1], "token-value") == 0 && argc >= 3) {
        // TODO: Call token value analytics (stub)
        printf("[token-value] Not yet implemented. Input: %s\n", argv[2]);
    } else if (strcmp(argv[1], "uml-parse") == 0 && argc >= 4) {
        uml_relationship_t* rel = parse_uml_relationship(argv[2], argv[3]);
        if (rel) {
            printf("UML relationship parsed successfully.\n");
            // TODO: Print rel fields
            free(rel);
        } else {
            printf("Failed to parse UML relationship.\n");
        }
    } else if (strcmp(argv[1], "uml-validate") == 0 && argc >= 4) {
        uml_relationship_t* rel = parse_uml_relationship(argv[2], argv[3]);
        if (rel) {
            bool valid = validate_uml_governance(rel);
            printf("UML governance %s.\n", valid ? "valid" : "invalid");
            free(rel);
        } else {
            printf("Failed to parse UML relationship.\n");
        }
    } else if (strcmp(argv[1], "uml-generate") == 0 && argc >= 4) {
        uml_relationship_t* rel = parse_uml_relationship(argv[2], argv[3]);
        if (rel) {
            char buffer[1024];
            generate_uml_code(rel, buffer, sizeof(buffer));
            printf("%s\n", buffer);
            free(rel);
        } else {
            printf("Failed to parse UML relationship.\n");
        }
    } else {
        print_usage();
    }

    rift_stage0_destroy(ctx);
    return 0;
}

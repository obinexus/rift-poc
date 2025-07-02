
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rift-0/core/rift-0.h"
#include "rift-0/lexer.h"

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
/**
 * @brief Main validation entry point
 * @param argc Argument count
 * @param argv Argument vector
 * @return int Exit code (0 = success, non-zero = failure)
 */
int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <project_root> [--verbose] [--strict]\n", argv[0]);
        return 1;
    }
    
    validation_context_t ctx;
    validation_result_t result = rift_validation_init(&ctx, argv[1]);
    
    if (result != VALIDATION_SUCCESS) {
        fprintf(stderr, "[AEGIS] Failed to initialize validation context\n");
        return 1;
    }
    
    // Parse command line options
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "--verbose") == 0) {
            ctx.verbose_mode = 1;
        } else if (strcmp(argv[i], "--strict") == 0) {
            ctx.strict_mode = 1;
        }
    }
    
    printf("AEGIS RIFT Governance Validation Engine v1.0.0\n");
    printf("Project Root: %s\n", ctx.project_root);
    printf("Validation Mode: %s\n", ctx.strict_mode ? "Strict" : "Standard");
    
    // Execute pipeline validation
    result = validate_complete_pipeline(&ctx);
    
    // Report results
    switch (result) {
        case VALIDATION_SUCCESS:
            printf("[SUCCESS] All governance validation passed\n");
            break;
            
        case VALIDATION_SEMVERX_VIOLATION:
            printf("[CRITICAL] SemVerX violation detected - BUILD HALT\n");
            break;
            
        case VALIDATION_EXPIRED_GOVERNANCE:
            printf("[CRITICAL] Expired governance detected - BUILD HALT\n");
            break;
            
        case VALIDATION_MISSING_GOVERNANCE:
            printf("[WARNING] Missing governance files detected\n");
            break;
            
        case VALIDATION_SCHEMA_VIOLATION:
            printf("[WARNING] Schema violations detected\n");
            break;
            
        default:
            printf("[ERROR] Validation failed with code: %d\n", result);
            break;
    }
    
    rift_validation_cleanup(&ctx);
    
    // Return appropriate exit code
    switch (result) {
        case VALIDATION_SUCCESS:
            return 0;
        case VALIDATION_SEMVERX_VIOLATION:
        case VALIDATION_EXPIRED_GOVERNANCE:
            return 1;  // Critical failure
        case VALIDATION_MISSING_GOVERNANCE:
        case VALIDATION_SCHEMA_VIOLATION:
            return 2;  // Warning state
        default:
            return 3;  // General error
    }
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

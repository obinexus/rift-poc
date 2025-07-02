#include <stdio.h>
#include "rift-0.h"

int main(void) {
    printf("RIFT Stage-0 CLI\n");
    printf("Version: %d.%d.%d\n", RIFT_STAGE0_VERSION_MAJOR, RIFT_STAGE0_VERSION_MINOR, RIFT_STAGE0_VERSION_PATCH);
    return 0;
}

/*
 * RIFT-Core-0 Lexer Module
 * Handles Stage-0 lexical analysis (tokenization) using RIFT regular expressions (R""/r"").
 * Governance: #[gov:stage_0_core]
 */

#include "rift-0/lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <regex.h>
#include <stdint.h>
#include <pthread.h>
#include <assert.h>

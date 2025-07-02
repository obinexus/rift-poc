
#include <stdbool.h>
#include <stdint.h>
#include <regex.h>
#include <pthread.h>

#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



// Structure definitions
typedef struct State {
    char* pattern;
    bool is_final;
    size_t id;
} State;

typedef struct Transition {
    State* from_state;
    char* input_pattern;
    State* to_state;
} Transition;

typedef struct RegexAutomaton {
    State** states;
    size_t state_count;
    size_t state_capacity;
    Transition** transitions;
    size_t transition_count;
    size_t transition_capacity;
    State* initial_state;
    State* current_state;
} RegexAutomaton;

typedef struct TokenNode {
    char* type;
    char* value;
} TokenNode;

typedef struct IRGenerator {
    RegexAutomaton* automaton;
    TokenNode** nodes;
    size_t node_count;
    size_t node_capacity;
} IRGenerator;

// Function declarations
State* state_create(const char* pattern, bool is_final);
void state_destroy(State* state);
bool state_matches(State* state, const char* text);

RegexAutomaton* automaton_create(void);
void automaton_destroy(RegexAutomaton* automaton);
State* automaton_add_state(RegexAutomaton* automaton, const char* pattern, bool is_final);
bool automaton_add_transition(RegexAutomaton* automaton, State* from, const char* pattern, State* to);
State* automaton_get_next_state(RegexAutomaton* automaton, const char* input);

IRGenerator* ir_generator_create(RegexAutomaton* automaton);
void ir_generator_destroy(IRGenerator* generator);
TokenNode* ir_generator_process_token(IRGenerator* generator, const char* token);

#ifdef __cplusplus
}
#endif
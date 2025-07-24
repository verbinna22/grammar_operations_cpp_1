#include "stack_1_automatone.h"

namespace grop {

constexpr State get_q_j(uint64_t j) { return 2 + j; }

Automaton generate_stack_1_automaton(int number_of_assign) {
    constexpr State q0 = 0;
    constexpr State qf = 1;
    constexpr State qd = 2;
    constexpr size_t reduced_alphabet_size = 8;
    const size_t alphabet_size = 4 + 4 * number_of_assign + 4;
    const size_t state_number = number_of_assign + 3;
    std::unordered_map<State, std::unordered_map<Symbol, State>> transitions;
    for (Symbol letter = 0; letter < alphabet_size; ++letter) {
        transitions[qf][letter] = qf;
        transitions[qd][letter] = qd;
        if (letter < reduced_alphabet_size) {
            transitions[q0][letter] = q0;
            for (State q = get_q_j(1); q < state_number; ++q) {
                transitions[q][letter] = q;
            }
        } else {
            const size_t i = (letter - 4) / 4;
            const bool is_open = letter % 2;
            if (is_open) {
                transitions[q0][letter] = get_q_j(i);
                for (State q = get_q_j(1); q < state_number; ++q) {
                    transitions[q][letter] = qf;
                }
            } else {
                transitions[q0][letter] = qd;
                for (State q = get_q_j(1); q < state_number; ++q) {
                    if (q == get_q_j(i)) {
                        transitions[q][letter] = q0;
                    } else {
                        transitions[q][letter] = qd;
                    }
                }
            }
        }
    }
    return Automaton(q0, state_number, {q0, qf}, transitions);
}

} // namespace grop

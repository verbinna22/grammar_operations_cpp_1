#ifndef GRAMMAR_WITH_DFA_INTERSECTION_H
#define GRAMMAR_WITH_DFA_INTERSECTION_H

#include "automatone.h"
#include "grammar.h"
#include "points_to_grammar.h"

namespace grop {

Grammar intersect(const Grammar &grammar, const Automaton &automaton);
constexpr NonTerminal get_nt_q1_q2(NonTerminal nt, State q1, State q2,
                                   uint64_t state_number,
                                   uint64_t symbols_number) {
    return symbols_number + 1 + state_number * state_number * (nt - symbols_number) +
           state_number * q2 + q1;
}

constexpr NonTerminal get_nt(NonTerminal nt, uint64_t state_number,
                                   uint64_t symbols_number) {
    return (nt - (symbols_number + 1)) / (state_number * state_number) + symbols_number;
}

constexpr NonTerminal get_q1(NonTerminal nt, uint64_t state_number,
                                   uint64_t symbols_number) {
    return (nt - (symbols_number + 1)) % (state_number);
}

constexpr NonTerminal get_q2(NonTerminal nt, uint64_t state_number,
                                   uint64_t symbols_number) {
    return ((nt - (symbols_number + 1)) % (state_number * state_number)) / state_number;
}

constexpr bool is_i_state_intersect(NonTerminal nt, int number_of_assign, uint64_t state_number,
                                   uint64_t symbols_number) {
    return (nt >= (symbols_number + 1)) && is_i_state((nt - (symbols_number + 1)) / (state_number * state_number), number_of_assign);
}
}

#endif  // GRAMMAR_WITH_DFA_INTERSECTION_H

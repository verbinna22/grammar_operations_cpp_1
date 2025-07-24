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
    return symbols_number + 1 + state_number * state_number * nt +
           state_number * q2 + q1;
}

constexpr bool is_i_state_intersect(NonTerminal nt, int number_of_assign, uint64_t state_number,
                                   uint64_t symbols_number) {
    return is_i_state((nt - (symbols_number + 1)) / (state_number * state_number), number_of_assign);
}
}

#endif  // GRAMMAR_WITH_DFA_INTERSECTION_H

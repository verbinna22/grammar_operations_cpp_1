#ifndef POINTS_TO_GRAMMAR_H
#define POINTS_TO_GRAMMAR_H

#include "grammar.h"
#include "rule.h"

namespace grop {

Grammar generate_points_to_grammar(int number_of_assign);
constexpr bool is_i_state(NonTerminal nt, int number_of_assign) {
    const size_t alphabet_size = 4 + 4 * number_of_assign + 4;
    return nt >= 4 + alphabet_size;
}
}

#endif  // POINTS_TO_GRAMMAR_H

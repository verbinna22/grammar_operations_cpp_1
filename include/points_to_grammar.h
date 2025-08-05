#ifndef POINTS_TO_GRAMMAR_H
#define POINTS_TO_GRAMMAR_H

#include <stdexcept>
#include <string>

#include "grammar.h"
#include "rule.h"

namespace grop {

Grammar generate_points_to_grammar(int number_of_assign);

inline std::string nt_to_string(NonTerminal nt, size_t alphabet_size) {
    nt -= alphabet_size;
    switch (nt) {
    case 0: return "PT";
    case 1: return "Assign";
    case 2: return "Assign_r";
    case 3: return "FT";
    case 4: return "ld_PT_FT_st_i";
    case 5: return "ld_PT_i";
    case 6: return "FT_st_i";
    case 7: return "st_r_PT_FT_ld_r_i";
    case 8: return "st_r_PT_i";
    case 9: return "FT_ld_r_i";
    }
    throw std::logic_error("incorrect nt nt_to_string");
}

constexpr bool is_i_state(NonTerminal nt, int number_of_assign) {
    const size_t alphabet_size = 4 + 4 * number_of_assign + 4;
    return nt >= 4 + alphabet_size;
}
}

#endif  // POINTS_TO_GRAMMAR_H

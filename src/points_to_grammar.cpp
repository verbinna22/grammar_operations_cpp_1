#include "points_to_grammar.h"

#include <cstddef>
#include <vector>

#include "grammar.h"
#include "rule.h"
#include "alphabet.h"

namespace grop {

Grammar generate_points_to_grammar(int number_of_assign) {
    const size_t alphabet_size = 4 + 4 * number_of_assign + 4;
    const NonTerminal PT = 0 + alphabet_size;
    const NonTerminal Assign = 1 + alphabet_size;
    const NonTerminal Assign_r = 2 + alphabet_size;
    const NonTerminal FT = 3 + alphabet_size;
    const NonTerminal ld_PT_FT_st_i = 4 + alphabet_size;
    const NonTerminal ld_PT_i = 5 + alphabet_size;
    const NonTerminal FT_st_i = 6 + alphabet_size;
    const NonTerminal st_r_PT_FT_ld_r_i = 7 + alphabet_size;
    const NonTerminal st_r_PT_i = 8 + alphabet_size;
    const NonTerminal FT_ld_r_i = 9 + alphabet_size;
    const size_t non_terminals_number = 10 + alphabet_size;
    std::vector<Rule> rules = {
        Rule(PT, {Assign, PT}),
        Rule(PT, {alloc}),
        Rule(PT, {ld_PT_FT_st_i, PT}),
        Rule(Assign, {assign}),
        Rule(Assign_r, {assign_r}),
        Rule(ld_PT_FT_st_i, {ld_PT_i, FT_st_i}),
        Rule(ld_PT_i, {ld_i, PT}),
        Rule(FT_st_i, {FT, st_i}),
        Rule(FT, {alloc_r}),
        Rule(FT, {FT, st_r_PT_FT_ld_r_i}),
        Rule(FT, {FT, Assign_r}),
        Rule(st_r_PT_FT_ld_r_i, {st_r_PT_i, FT_ld_r_i}),
        Rule(st_r_PT_i, {st_r_i, PT}),
        Rule(FT_ld_r_i, {FT, ld_r_i})
    };
    for (int i = 1; i <= number_of_assign; ++i) {
        rules.push_back(Rule(Assign, {assign_j_open(i)}));
        rules.push_back(Rule(Assign, {assign_j_close(i)}));
        rules.push_back(Rule(Assign_r, {assign_r_j_open(i)}));
        rules.push_back(Rule(Assign_r, {assign_r_j_close(i)}));
    }
    return Grammar(PT, non_terminals_number, rules, alphabet_size);
}

} // namespace grop

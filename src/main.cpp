
#include <fstream>
#include <iostream>

#include "alphabet.h"
#include "automatone.h"
#include "grammar.h"
#include "grammar_io.h"
#include "grammar_optimize.h"
#include "grammar_with_dfa_intersection.h"
#include "points_to_grammar.h"
#include "stack_1_automatone.h"

int main(int argc, const char **argv) {
    if (argc < 3) {
        return 1;
    }
    const char *CONTEXT_NUMBERS_FILE = argv[1];
    const char *GRAMMAR_FILE = argv[2];
    int number_of_assign;
    {
        std::ifstream context_number_file(CONTEXT_NUMBERS_FILE);
        context_number_file >> number_of_assign;
    }
    const size_t alphabet_size = 4 + 4 * number_of_assign + 4;
    grop::Grammar grammar = grop::generate_points_to_grammar(number_of_assign);
    grop::Automaton dfa = grop::generate_stack_1_automaton(number_of_assign);
    grop::Grammar new_grammar = grop::intersect(grammar, dfa);
    // new_grammar = grop::optimize_rules(new_grammar);
    grop::write_grammar(
        GRAMMAR_FILE, new_grammar,
        [&](auto nt) {
            return grop::is_i_state_intersect(nt, number_of_assign,
                                              dfa.get_state_number(),
                                              grammar.get_symbols_number());
        },
        grop::symbol_to_string, alphabet_size);
    return 0;

    // if (argc < 3) {
    //     return 1;
    // }
    // const char *OLD_GRAMMAR_FILE = argv[1];
    // const char *NEW_GRAMMAR_FILE = argv[2];
    // grop::read_grammar(OLD_GRAMMAR_FILE, const std::unordered_map<std::string, NonTerminal> &alphabet_non_terminals);
}
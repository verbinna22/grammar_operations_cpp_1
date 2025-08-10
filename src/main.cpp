
#include <fstream>
#include <iostream>

#include "alphabet.h"
#include "automatone.h"
#include "grammar.h"
#include "grammar_io.h"
#include "grammar_optimize.h"
#include "grammar_with_dfa_intersection.h"
#include "points_to_grammar.h"
#include "rule.h"
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
    if (number_of_assign == 0) {
        auto non_terminal_to_string = [&](grop::NonTerminal nt) {
            if (nt < alphabet_size) {
                return grop::symbol_to_string(nt);
            }
            return grop::nt_to_string(nt, alphabet_size);
        };
        grop::write_grammar(GRAMMAR_FILE, grammar, non_terminal_to_string);
        return 0;
    }
    grop::Automaton dfa = grop::generate_stack_1_automaton(number_of_assign);
    grop::Grammar new_grammar = grop::intersect(grammar, dfa);
    new_grammar = grop::optimize_rules(new_grammar);
    auto non_terminal_to_string = [&](grop::NonTerminal nt) {
        if (nt < alphabet_size) {
            return grop::symbol_to_string(nt);
        }
        if (nt == alphabet_size) {
            return std::string("N");
        }
        std::stringstream s;
        auto state_number = dfa.get_state_number();
        s << grop::state_to_string(grop::get_q1(nt, state_number, alphabet_size))
        << "_" << grop::state_to_string(grop::get_q2(nt, state_number, alphabet_size))
        << "_" << grop::nt_to_string(grop::get_nt(nt, state_number, alphabet_size), alphabet_size);
        return s.str();
    };
    grop::write_grammar(GRAMMAR_FILE, new_grammar, non_terminal_to_string);
    return 0;

    // grop::Grammar grammar = grop::Grammar(2, 4 + 2, {
    //     grop::Rule(3, {0}),
    //     grop::Rule(3, {3, 0}),
    //     grop::Rule(3, {4}),
    //     grop::Rule(4, {5}),
    //     grop::Rule(4, {3, 5}),
    //     grop::Rule(2, {3}),
    //     grop::Rule(5, {}),
    // }, 2);
    // grammar = grop::optimize_rules(grammar);
    // return 0;
}
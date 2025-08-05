
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <unordered_map>

#include "alphabet.h"
#include "automatone.h"
#include "grammar.h"
#include "grammar_io.h"
#include "grammar_optimize.h"
#include "grammar_with_dfa_intersection.h"
#include "points_to_grammar.h"
#include "rule.h"
#include "stack_1_automatone.h"
#include "symbol.h"

int main() {
    { // build grammar
        grop::Grammar grammar = grop::generate_points_to_grammar(0);
        const size_t alphabet_size = 4 + 4;
        auto non_terminal_to_string = [&](grop::NonTerminal nt) {
            if (nt < alphabet_size) {
                return grop::symbol_to_string(nt);
            }
            return grop::nt_to_string(nt, alphabet_size);
        };
        grop::write_grammar("../test/zero_assign_grammar.cfg", grammar,non_terminal_to_string);
    }
    {
        /*
            A -> a | A a | B
            B -> C | A C
            N -> A
            C -> 

            A -> a | A a
            N -> A
        */
        grop::Grammar grammar = grop::Grammar(2, 4 + 2, {
            grop::Rule(3, {0}),
            grop::Rule(3, {3, 0}),
            grop::Rule(3, {4}),
            grop::Rule(4, {5}),
            grop::Rule(4, {3, 5}),
            grop::Rule(2, {3}),
            grop::Rule(5, {}),
        }, 2);
        auto non_terminal_to_string = [&](grop::NonTerminal nt) {
            switch (nt) {
                case 0: return "a";
                case 1: return "b";
                case 2: return "N";
                case 3: return "A";
                case 4: return "B";
                case 5: return "C";
            }
            throw std::logic_error("error");
        };
        grammar = grop::optimize_rules(grammar);
        grop::write_grammar("../test/optimized_grammar.cfg", grammar,non_terminal_to_string);
    }
    {
        grop::Grammar grammar = grop::Grammar(2, 4 + 2, {
            grop::Rule(3, {0}),
            grop::Rule(4, {1}),
            grop::Rule(2, {2, 3}),
            grop::Rule(2, {3, 4}),
            grop::Rule(2, {3}),
        }, 2);
        auto alphabet_size = 2U;
        grop::Automaton dfa = grop::Automaton(
            0, 3, {1}, std::unordered_map<grop::State, std::unordered_map<grop::Symbol, grop::State>>{
                {0, std::unordered_map<grop::Symbol, grop::State>{ {0, 2}, {1, 1} }},
                {1, std::unordered_map<grop::Symbol, grop::State>{ {0, 1}, {1, 2} }},
                {2, std::unordered_map<grop::Symbol, grop::State>{ {0, 2}, {1, 2} }},
            }
        );
        grop::Grammar new_grammar = grop::intersect(grammar, dfa);
        auto old_non_terminal_to_string = [&](grop::NonTerminal nt) {
            switch (nt) {
                case 0: return "a";
                case 1: return "b";
                case 2: return "N";
                case 3: return "A";
                case 4: return "B";
            }
            throw std::logic_error("error");
        };
        auto state_to_string = [&](grop::State st) {
            switch (st) {
                case 0: return "q0";
                case 1: return "q1";
                case 2: return "qd";
            }
            throw std::logic_error("unreachable");
        };
        auto non_terminal_to_string = [&](grop::NonTerminal nt) {
            if (nt < alphabet_size) {
                return std::string(old_non_terminal_to_string(nt));
            }
            if (nt == alphabet_size) {
                return std::string("N");
            }
            std::stringstream s;
            auto state_number = dfa.get_state_number();
            s << state_to_string(grop::get_q1(nt, state_number, alphabet_size))
            << "_" << state_to_string(grop::get_q2(nt, state_number, alphabet_size))
            << "_" << old_non_terminal_to_string(grop::get_nt(nt, state_number, alphabet_size));
            return s.str();
        };
        grop::write_grammar("../test/intersected_grammar.cfg", new_grammar, non_terminal_to_string);
    }
    return 0;
}
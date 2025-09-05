#include "grammar_with_dfa_intersection.h"

#include <cstdint>
#include <iostream>
#include <unordered_map>

#include "automatone.h"
#include "grammar.h"
#include "rule.h"

namespace grop {

Grammar intersect(const Grammar &grammar, const Automaton &automaton) {
    std::vector<Rule> rules;
    int progress = 0;
    const uint64_t only_non_terminals_number =
        grammar.get_non_terminals_number() - grammar.get_symbols_number();
    const uint64_t state_number = automaton.get_state_number();
    const uint64_t symbols_number = grammar.get_symbols_number();
    const NonTerminal artificial_non_terminal = symbols_number;
    const auto &automaton_transitions = automaton.get_transitions();
    std::unordered_map<State, std::unordered_set<State>> reachable_from;
    for (State q1 = 0; q1 < automaton.get_state_number(); ++q1) {
        for (Symbol s = 0; s < symbols_number; ++s) {
            reachable_from[q1].insert(automaton_transitions.find(q1)->second.find(s)->second);
        }
    }
    for (State qm = 0; qm < automaton.get_state_number(); ++qm) {
        for (State q1 = 0; q1 < automaton.get_state_number(); ++q1) {
            for (State q2 = 0; q2 < automaton.get_state_number(); ++q2) {
                if ((reachable_from[q1].find(q2) == reachable_from[q1].end()) &&
                        (reachable_from[q1].find(qm) != reachable_from[q1].end()) &&
                        (reachable_from[qm].find(q2) != reachable_from[qm].end())) {
                    reachable_from[q1].insert(q2);
                }
            }
        }
    }
    for (const auto &rule : grammar.get_rules()) {
        for (State q1 = 0; q1 < automaton.get_state_number(); ++q1) {
            for (State q2 : reachable_from[q1]) {
#define qd 2
                if (q1 == qd || q2 == qd) {
                    continue;
                }
                if (++progress % 1000 == 0) {
                    std::cout << progress << " " << rules.size() << std::endl;
                }
                if (rule.get_right_part().size() == 0) {
                    rules.push_back(
                        Rule(get_nt_q1_q2(rule.get_main_non_terminal(), q1, q2,
                                          state_number, symbols_number),
                             {}));
                } else if (rule.get_right_part().size() == 1) {
                    if (rule.get_right_part()[0] < symbols_number) {
                        if (automaton_transitions.find(q1)
                                ->second.find(rule.get_right_part()[0])
                                ->second == q2) {
                            rules.push_back(Rule(
                                get_nt_q1_q2(rule.get_main_non_terminal(), q1,
                                             q2, state_number, symbols_number),
                                {rule.get_right_part()[0]}));
                        } else {
                            rules.push_back(Rule(
                                get_nt_q1_q2(rule.get_main_non_terminal(), q1,
                                             q2, state_number, symbols_number),
                                {}));
                        }
                    } else {
                        rules.push_back(
                            Rule(get_nt_q1_q2(rule.get_main_non_terminal(), q1,
                                              q2, state_number, symbols_number),
                                 {get_nt_q1_q2(rule.get_right_part()[0], q1, q2,
                                               state_number, symbols_number)}));
                    }
                } else if (rule.get_right_part().size() == 2) {
                    if (rule.get_right_part()[0] < symbols_number) {
                        State qk = automaton_transitions.find(q1)
                                       ->second.find(rule.get_right_part()[0])
                                       ->second;
                        if (rule.get_right_part()[1] < symbols_number) {
                            if (automaton_transitions.find(qk)
                                    ->second.find(rule.get_right_part()[1])
                                    ->second == q2) {
                                rules.push_back(Rule(
                                    get_nt_q1_q2(rule.get_main_non_terminal(),
                                                 q1, q2, state_number,
                                                 symbols_number),
                                    {rule.get_right_part()[0],
                                     rule.get_right_part()[1]}));
                            } else {
                                rules.push_back(Rule(
                                    get_nt_q1_q2(rule.get_main_non_terminal(),
                                                 q1, q2, state_number,
                                                 symbols_number),
                                    {}));
                            }
                        } else {
                            rules.push_back(Rule(
                                get_nt_q1_q2(rule.get_main_non_terminal(), q1,
                                             q2, state_number, symbols_number),
                                {rule.get_right_part()[0],
                                 get_nt_q1_q2(rule.get_right_part()[1], qk, q2,
                                              state_number, symbols_number)}));
                        }
                    } else {
                        for (State qk : reachable_from[q1]) {
                            if (reachable_from[qk].find(q2) == reachable_from[qk].end()) {
                                continue;
                            }
                            if (rule.get_right_part()[1] < symbols_number) {
                                if (automaton_transitions.find(qk)
                                        ->second.find(rule.get_right_part()[1])
                                        ->second == q2) {
                                    rules.push_back(Rule(
                                        get_nt_q1_q2(
                                            rule.get_main_non_terminal(),
                                            q1,
                                            q2, state_number, symbols_number),
                                        {get_nt_q1_q2(
                                                rule.get_right_part()[0], q1,
                                                qk, state_number,
                                                symbols_number),
                                         rule.get_right_part()[1]}));
                                } else {
                                    rules.push_back(Rule(
                                        get_nt_q1_q2(
                                            rule.get_main_non_terminal(), q1,
                                            q2, state_number, symbols_number),
                                        {}));
                                }
                            } else {
                                rules.push_back(Rule(
                                    get_nt_q1_q2(rule.get_main_non_terminal(),
                                                 q1, q2, state_number,
                                                 symbols_number),
                                    {get_nt_q1_q2(rule.get_right_part()[0], q1,
                                                  qk, state_number,
                                                  symbols_number),
                                     get_nt_q1_q2(rule.get_right_part()[1], qk,
                                                  q2, state_number,
                                                  symbols_number)}));
                            }
                        }
                    }
                }
            }
        }
    }
    for (auto qf : automaton.get_accept_states()) {
        rules.push_back(Rule(artificial_non_terminal,
                             {get_nt_q1_q2(grammar.get_main_non_terminal(),
                                           automaton.get_initial_state(), qf,
                                           state_number, symbols_number)}));
    }
    return Grammar(artificial_non_terminal,
                   state_number * state_number * only_non_terminals_number +
                       symbols_number + 1,
                   rules, grammar.get_symbols_number());
}
}  // namespace grop

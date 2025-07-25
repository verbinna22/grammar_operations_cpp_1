#include "grammar_optimize.h"

#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "grammar.h"
#include "rule.h"

namespace grop {

struct NonTerminalEntity {
    std::vector<int> indicies;
    int empty_number = 0;
    int rule_number = 0;
};

Grammar optimize_rules(const Grammar &grammar) {
    std::unordered_map<NonTerminal, NonTerminalEntity> nt_map;
    std::queue<NonTerminal> q;
    std::unordered_set<NonTerminal> non_empty_nt;
    std::set<int> rules_to_remove;
    int i = 0;
    for (const auto &rule : grammar.get_rules()) {
        for (const auto &nt : rule.get_right_part()) {
            nt_map[nt].indicies.push_back(i);
        }
        nt_map[rule.get_main_non_terminal()].indicies.push_back(i);
        nt_map[rule.get_main_non_terminal()].rule_number++;
        if (rule.get_right_part().size() == 0) {
            rules_to_remove.insert(i);
            nt_map[rule.get_main_non_terminal()].empty_number++;
        } else {
            non_empty_nt.insert(rule.get_main_non_terminal());
        }
        ++i;
    }
    for (NonTerminal nt = grammar.get_symbols_number();
         nt < grammar.get_non_terminals_number(); ++nt) {
        if (non_empty_nt.find(nt) != non_empty_nt.end()) {
            continue;
        }
        for (int j : nt_map[nt].indicies) {
            rules_to_remove.insert(j);
            auto main_nt = grammar.get_rules()[j].get_main_non_terminal();
            if (main_nt != nt) {
                nt_map[main_nt].empty_number++;
                if (nt_map[main_nt].empty_number == nt_map[main_nt].rule_number) {
                    q.push(main_nt);
                }
            }
        }
    }
    while (!q.empty()) {
        auto nt = q.front();
        q.pop();
        for (int j : nt_map[nt].indicies) {
            rules_to_remove.insert(j);
            auto main_nt = grammar.get_rules()[j].get_main_non_terminal();
            if (main_nt != nt) {
                nt_map[main_nt].empty_number++;
                if (nt_map[main_nt].empty_number == nt_map[main_nt].rule_number) {
                    q.push(main_nt);
                }
            }
        }
    }
    std::vector<Rule> rules = grammar.get_rules();
    for (auto it = rules_to_remove.rbegin(); it != rules_to_remove.rend();
         ++it) {
        std::swap(rules[*it], rules[rules.size() - 1]);
        rules.pop_back();
    }
    return Grammar(grammar.get_main_non_terminal(),
                   grammar.get_non_terminals_number(), rules,
                   grammar.get_symbols_number());
}

}  // namespace grop

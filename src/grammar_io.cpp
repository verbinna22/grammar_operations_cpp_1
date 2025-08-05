#include "grammar_io.h"

#include <fstream>
#include <functional>
#include <ostream>
#include <string>
#include <vector>

#include "grammar.h"
#include "rule.h"

namespace grop {

static const char *DELIMITERS = " \t";

static NonTerminal get_non_terminal_by_string(
    const std::string &string, NonTerminal &new_non_terminal,
    std::unordered_map<std::string, NonTerminal> &non_terminal_string_to_number,
    const std::unordered_map<std::string, NonTerminal>
        &alphabet_non_terminals) {
    auto alphabet_found = alphabet_non_terminals.find(string);
    if (alphabet_found != alphabet_non_terminals.end()) {
        return alphabet_found->second;
    }
    auto non_terminal_found = non_terminal_string_to_number.find(string);
    if (non_terminal_found != non_terminal_string_to_number.end()) {
        return non_terminal_found->second;
    }
    return non_terminal_string_to_number[string] = new_non_terminal++;
}

Grammar read_grammar(const std::string &filename,
                     const std::unordered_map<std::string, NonTerminal>
                         &alphabet_non_terminals) {
    std::ifstream file(filename);
    std::unordered_map<std::string, NonTerminal> non_terminal_string_to_number;
    NonTerminal new_non_terminal = alphabet_non_terminals.size();
    std::vector<Rule> rules;
    NonTerminal main_non_terminal;
    for (std::string line; std::getline(file, line);) {
        if (line == "Count:") {
            if (!std::getline(file, line)) {
                throw 239;
            }
            main_non_terminal = get_non_terminal_by_string(
                line, new_non_terminal, non_terminal_string_to_number,
                alphabet_non_terminals);
            goto end;
        }
        if (line.size() > 0) {
            NonTerminal non_terminal;
            std::vector<NonTerminal> right_part;
            std::size_t found = line.find_first_of(DELIMITERS);
            if (found != std::string::npos) {
                non_terminal = get_non_terminal_by_string(
                    line.substr(0, found), new_non_terminal,
                    non_terminal_string_to_number, alphabet_non_terminals);
                line = line.substr(found);
                found = line.find_first_not_of(DELIMITERS);
                line = line.substr(found);
                found = line.find_first_of(DELIMITERS);
                while (found != std::string::npos) {
                    right_part.push_back(get_non_terminal_by_string(
                        line.substr(0, found), new_non_terminal,
                        non_terminal_string_to_number, alphabet_non_terminals));
                    line = line.substr(found);
                    found = line.find_first_not_of(DELIMITERS);
                    line = line.substr(found);
                    found = line.find_first_of(DELIMITERS);
                }
            } else {
                non_terminal = get_non_terminal_by_string(
                    line, new_non_terminal, non_terminal_string_to_number,
                    alphabet_non_terminals);
            }
            rules.push_back(Rule(non_terminal, right_part));
        }
    }
    throw 361;
end:
    return Grammar(main_non_terminal, new_non_terminal, rules,
                   alphabet_non_terminals.size());
}

void write_grammar(
    const std::string &filename, const Grammar &grammar,
    std::function<std::string(NonTerminal)> non_terminal_to_string) {
    std::ofstream file(filename);
    for (const auto &rule : grammar.get_rules()) {
        file << non_terminal_to_string(rule.get_main_non_terminal());
        for (const auto &non_terminal : rule.get_right_part()) {
            file << "\t" << non_terminal_to_string(non_terminal);
        }
        file << "\n";
    }
    file << "Count:\n"
         << non_terminal_to_string(grammar.get_main_non_terminal()) << std::endl;
}

}  // namespace grop

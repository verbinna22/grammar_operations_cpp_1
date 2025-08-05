#ifndef GRAMMAR_IO_H
#define GRAMMAR_IO_H

#include <string>
#include <unordered_map>
#include <functional>
#include <sstream>

#include "grammar.h"

namespace grop {

Grammar read_grammar(
    const std::string &filename,
    const std::unordered_map<std::string, NonTerminal> &alphabet_non_terminals);

void write_grammar(
    const std::string &filename, const Grammar &grammar,
    std::function<std::string(NonTerminal)> non_terminal_to_string);

inline std::string print_non_terminal(
    NonTerminal nt,
    std::function<bool(NonTerminal)> &i_states,
    std::function<std::string(NonTerminal)> symbol_to_string,
    uint64_t alphabet_size) {
        if (nt < alphabet_size) {
            return symbol_to_string(nt);
        }
        if (i_states(nt)) {
            std::stringstream s;
            s << "nt_" << nt << "_i";
            return s.str();
        }
        std::stringstream s;
        s << "nt_" << nt;
        return s.str();
}

}  // namespace grop

#endif  // GRAMMAR_IO_H

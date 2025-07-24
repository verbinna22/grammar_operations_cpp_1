#ifndef GRAMMAR_IO_H
#define GRAMMAR_IO_H

#include <string>
#include <unordered_map>
#include <functional>

#include "grammar.h"

namespace grop {

Grammar read_grammar(
    const std::string &filename,
    const std::unordered_map<std::string, NonTerminal> &alphabet_non_terminals);

void write_grammar(
    const std::string &filename, const Grammar &grammar,
    std::function<bool(NonTerminal)> i_states,
    std::function<std::string(NonTerminal)> symbol_to_string,
    uint64_t alphabet_size);

}  // namespace grop

#endif  // GRAMMAR_IO_H

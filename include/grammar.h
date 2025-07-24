#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <cstdint>

#include "rule.h"

namespace grop {
class Grammar {
   public:
    Grammar(NonTerminal main_non_terminal, uint64_t non_terminals_number,
            const std::vector<Rule> &rules, uint64_t symbols_number) noexcept
        : _main_non_terminal(main_non_terminal),
          _non_terminals_number(non_terminals_number),
          _symbols_number(symbols_number),
          _rules(rules) {}
    Grammar(const Grammar &) = default;
    Grammar(Grammar &&) noexcept = default;
    Grammar &operator=(const Grammar &) = default;
    Grammar &operator=(Grammar &&) noexcept = default;
    ~Grammar() noexcept = default;

    const std::vector<Rule> &get_rules() const noexcept { return _rules; }
    NonTerminal get_main_non_terminal() const noexcept {
        return _main_non_terminal;
    }
    uint64_t get_non_terminals_number() const noexcept {
        return _non_terminals_number;
    }
    uint64_t get_symbols_number() const noexcept { return _symbols_number; }

   private:
    NonTerminal _main_non_terminal;
    uint64_t _non_terminals_number;
    uint64_t _symbols_number;
    std::vector<Rule> _rules;
};
}  // namespace grop

#endif  // GRAMMAR_H

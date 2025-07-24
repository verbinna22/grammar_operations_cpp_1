#ifndef RULE_H
#define RULE_H

#include <cstdint>
#include <vector>

namespace grop {

using NonTerminal = uint64_t;

class Rule {
   public:
    Rule(NonTerminal main_non_terminal,
         const std::vector<NonTerminal> &right_part) noexcept
        : _main_non_terminal(main_non_terminal),
          _right_part(right_part) {}
    Rule(const Rule &) = default;
    Rule(Rule &&) noexcept = default;
    Rule &operator=(const Rule &) = default;
    Rule &operator=(Rule &&) noexcept = default;
    ~Rule() noexcept = default;

    NonTerminal get_main_non_terminal() const noexcept {
        return _main_non_terminal;
    }
    const std::vector<NonTerminal> &get_right_part() const noexcept {
        return _right_part;
    }

   private:
    NonTerminal _main_non_terminal;
    std::vector<NonTerminal> _right_part;
};
}  // namespace grop

#endif  // RULE_H

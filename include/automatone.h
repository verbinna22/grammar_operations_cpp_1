#ifndef AUTOMATONE_H
#define AUTOMATONE_H

#include <unordered_map>
#include <unordered_set>

#include "symbol.h"

namespace grop {

using State = uint64_t;

class Automaton {
   public:
    Automaton(State initial_state, uint64_t state_number,
              const std::unordered_set<State> &accept_states,
              const std::unordered_map<State, std::unordered_map<Symbol, State>>
                  &transitions) noexcept
        : _initial_state(initial_state),
          _state_number(state_number),
          _accept_states(accept_states),
          _transitions(transitions) {}
    Automaton(State initial_state, uint64_t state_number,
              const std::unordered_set<State> &accept_states,
              std::unordered_map<State, std::unordered_map<Symbol, State>>
                  &&transitions) noexcept
        : _initial_state(initial_state),
          _state_number(state_number),
          _accept_states(accept_states),
          _transitions(transitions) {}
    Automaton(const Automaton &) = default;
    Automaton(Automaton &&) noexcept = default;
    Automaton &operator=(const Automaton &) = default;
    Automaton &operator=(Automaton &&) noexcept = default;
    ~Automaton() noexcept = default;

    State get_initial_state() const noexcept { return _initial_state; }
    uint64_t get_state_number() const noexcept { return _state_number; }
    const std::unordered_set<State> &get_accept_states() const noexcept {
        return _accept_states;
    }
    const std::unordered_map<State, std::unordered_map<Symbol, State>> &
    get_transitions() const noexcept {
        return _transitions;
    }

   private:
    State _initial_state;
    uint64_t _state_number;
    std::unordered_set<State> _accept_states;
    std::unordered_map<State, std::unordered_map<Symbol, State>> _transitions;
};
}  // namespace grop

#endif  // AUTOMATONE_H

#ifndef STACK_1_AUTOMATONE_H
#define STACK_1_AUTOMATONE_H

#include <sstream>
#include <stdexcept>
#include <string>
#include "automatone.h"

namespace grop {

Automaton generate_stack_1_automaton(int number_of_assign);

inline std::string state_to_string(State q) {
    if (q > 2) {
        std::stringstream s;
        s << "q" << (q - 2);
        return s.str();
    }
    switch (q) {
        case 0: return "q0";
        case 1: return "qf";
        case 2: return "qd";
    }
    throw std::logic_error("unreachable");
}

}
#endif  // STACK_1_AUTOMATONE_H

#ifndef ALPHABET_H
#define ALPHABET_H

#include <sstream>
#include <string>

#include "rule.h"

namespace grop {

constexpr NonTerminal assign_j_open(int j) { return 4 + 4 * j; }
constexpr NonTerminal assign_j_close(int j) { return 4 + 4 * j + 1; }
constexpr NonTerminal assign_r_j_open(int j) { return 4 + 4 * j + 2; }
constexpr NonTerminal assign_r_j_close(int j) { return 4 + 4 * j + 3; }

constexpr NonTerminal alloc = 0;
constexpr NonTerminal assign = 1;
constexpr NonTerminal assign_r = 2;
constexpr NonTerminal ld_i = 3;
constexpr NonTerminal st_i = 4;
constexpr NonTerminal alloc_r = 5;
constexpr NonTerminal st_r_i = 6;
constexpr NonTerminal ld_r_i = 7;

inline std::string symbol_to_string(NonTerminal nt) {
    switch (nt) {
        case alloc:
            return "alloc";
        case alloc_r:
            return "alloc_r";
        case assign:
            return "assign";
        case assign_r:
            return "assign_r";
        case ld_i:
            return "ld_i";
        case st_i:
            return "st_i";
        case st_r_i:
            return "st_r_i";
        case ld_r_i:
            return "ld_r_i";
        default:
            nt -= 4;
            std::stringstream s;
            s << "assign_";
            if (nt % 4 >= 2) {
                s << "r_";
            }
            s << nt / 4;
            if (nt % 2 == 0) {
                s << "_open";
            } else {
                s << "_close";
            }
            return s.str();
    }
}
}  // namespace grop

#endif  // ALPHABET_H

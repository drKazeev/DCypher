#ifndef DCYPHER_DCYPHER_H
#define DCYPHER_DCYPHER_H

#include <string>
#include <iostream>
#include <time.h>
#include <algorithm>
#include <set>

class DCypher
{
    //переменная, значение которой мы не знаем
    int private_key;
    //константа, которую мы хотим зашифровать
    int cypher_const;
    //множество с всегда истинными функциями
    std::set<std::string> true_expr {"(j * j > 0)",
                                     "(i * i > 0)"
                                     "(i * j == j * i"
                                     "(i + j == j + i)"
                                     "((i * j) * (i * j) == i * i + 2 * i * j + j * j)"
                                     "(i + i * 2 == 3 * i)"
                                     "(j + j == 2 * j)"};
    //множество с всегда истинными функциями
    std::set<std::string> false_expr {"(j * j <= 0)",
                                     "(i * i <= 0)"
                                     "(i * j != j * i"
                                     "(i + j != j + i)"
                                     "((i * j) * (i * j) != i * i + 2 * i * j + j * j)"
                                     "(i + i * 2 != 3 * i)"
                                     "(j + j != 2 * j)"};
public:
    //переменная, значение которой мы знаем
    int public_key;

};



#endif //DCYPHER_DCYPHER_H

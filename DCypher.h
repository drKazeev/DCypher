#ifndef DCYPHER_DCYPHER_H
#define DCYPHER_DCYPHER_H

#include <string>
#include <iostream>
#include <time.h>
#include <algorithm>
#include <vector>

class DCypher
{
    //переменная, значение которой мы не знаем
    int private_key;
    //константа, которую мы хотим зашифровать
    int cypher_const;
    //множество с всегда истинными функциями
    std::vector<std::string> true_expr {"(j * j > 0)",
                                        "(i * i > 0)",
                                        "(i * j == j * i",
                                        "(i + j == j + i)",
                                        "((i * j) * (i * j) == i * i + 2 * i * j + j * j)",
                                        "(i + i * 2 == 3 * i)",
                                        "(j + j == 2 * j)"};
    //множество с всегда истинными функциями
    std::vector<std::string> false_expr {"(j * j <= 0)",
                                         "(i * i <= 0)",
                                         "(i * j != j * i",
                                         "(i + j != j + i)",
                                         "((i * j) * (i * j) != i * i + 2 * i * j + j * j)",
                                         "(i + i * 2 != 3 * i)",
                                         "(j + j != 2 * j)"};
    //множество для функции return_trash
    std::vector<std::string> trash_expr {"(i + j) / ",
                                         "(i * j) * ",
                                         "i - ",
                                         "j + i * ",
                                         "(i - j) * (j - i) +",
                                         "j * j - ",
                                         "i * i - "};

public:
    //переменная, значение которой мы знаем
    int public_key;

    //конструктор
    DCypher(int pr_k, int pub_k, int cyp_c);

    //добавить истинное или ложное выражение в соответствующее множество(второй параметр определяет куда именно)
    //выражение должно быть заключено в круглые скобки!
    void insert_expr(std::string expr, bool b);

    //возвращает случайный эллемент вектора
    std::string pick_random(std::vector<std::string> v);

    //конструировать "противоположное" выражение при помощи добавления отрицания
    std::string negation(std::string expr);

    //генерирует return необходимой константы
    std::string return_const();

    //генерирует return для бесполезных веток
    std::string return_trash();



};



#endif //DCYPHER_DCYPHER_H

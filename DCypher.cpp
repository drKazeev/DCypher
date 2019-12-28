#include "DCypher.h"

DCypher::DCypher(int pr_k, int pub_k, int cyp_c): private_key(pr_k),
                                                            public_key(pub_k),
                                                            cypher_const(cyp_c)
{
}

void DCypher::insert_expr(std::string expr, bool b)
{
    if (b)
        true_expr.push_back(expr);
    else
        false_expr.push_back(expr);
}

std::string DCypher::negation(std::string expr)
{
    srand ( time(NULL) );
    return "(!" + expr + ")";
}

std::string DCypher::pick_random(std::vector<std::string> v)
{
    return v[rand() % v.size()];
}

std::string DCypher::return_const()
{
    if (cypher_const == 0)
        return "i * i - i * " + std::to_string(public_key);
    else
        return "i * i - i * " + std::to_string(public_key) + std::to_string(cypher_const);
}

std::string DCypher::return_trash()
{
    srand ( time(NULL) );
    if (rand() % 3 == 0)
        return  pick_random(trash_expr) + " " + std::to_string(public_key) ;
    else
    if (rand() % 3 == 1)
        return pick_random(trash_expr) + " " + std::to_string(private_key);
    else
        return pick_random(trash_expr) + " " + std::to_string(rand() % 100 + 1);
}


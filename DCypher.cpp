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

std::string DCypher::negation()
{
    srand ( time(NULL) );
    return "(!" + pick_random(rand() % 2) + ")";
}

std::string DCypher::pick_random(bool b)
{
    srand ( time(NULL) );
    if (b)
        return true_expr[rand() % true_expr.size()];
    else
        return true_expr[rand() % true_expr.size()];
}

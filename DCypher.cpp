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
        return "i * i - i * " + std::to_string(public_key) + " + " +std::to_string(cypher_const);
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

std::string DCypher::create_cond(bool b)
{
    if (b)
        return "(" + pick_random(true_expr) + ")?";
    else
        return "(" + pick_random(false_expr) + ")?";
}

std::string DCypher::add_cond(std::string src, std::string cond, std::string op)
{
    std::string expr = " " + op + " " + cond;
    src.insert(src.begin() + src.find_last_of(')'), expr.begin(), expr.end());
    return src;
}

std::string DCypher::gen_cond_op(std::string cond, std::string left, std::string right)
{
    return cond + " " + left + " : " + right;
}

std::string DCypher::gen_expr(int complexity)
{
    srand ( time(NULL) );
    auto res = return_const();
    for (auto i = 0; i < complexity; i++)
    {
        bool b = rand() % 2;
        if (b)
        {
            std::string cond = create_cond(true);
            for (auto j = 0; j < complexity / 2 + 1; j++)
            {
                bool d = rand() % 2;
                if (d)
                    cond = add_cond(cond, pick_random(true_expr), "&&");
                else
                    cond = add_cond(cond, negation(pick_random(false_expr)), "||");
            }
            if (i == 0)
                res = gen_cond_op(cond, res, return_trash());
            else
                res =  gen_cond_op(cond, res, gen_cond_op(cond, return_trash(), return_trash()));
        }
        else
        {
            std::string cond = create_cond(false);
            for (auto j = 0; j < complexity / 2 + 1; j++)
            {
                bool d = rand() % 2;
                if (d)
                    cond = add_cond(cond, negation(pick_random(true_expr)), "&&");
                else
                    cond = add_cond(cond, negation(negation(pick_random(false_expr))), "||");
            }
            if (i == 0)
                res = gen_cond_op(cond, return_trash(), res);
            else
                res = gen_cond_op(cond, gen_cond_op(cond, return_trash(), return_trash()), res);
        }
    }
    return res + ";";
}

/*Examples
 * ((j * j <= 0) || (!(!(i * i <= 0))))? (i * j) *  71 : i * i - i * 12
 * ((i + j != j + i) && (!(i + j == j + i)) && (!(j * j > 0)) && (!(j * j > 0)) && (!(j * j > 0)) && (!(j * j > 0)) && (!(j * j > 0)))? ((i + j != j + i) && (!(i + j == j + i)) && (!(j * j > 0)) && (!(j * j > 0)) && (!(j * j > 0)) && (!(j * j > 0)) && (!(j * j > 0)))? (i + j) /  12 : (i + j) /  12 : ((i + j != j + i) && (!(i + j == j + i)) && (!(j * j > 0)) && (!(j * j > 0)) && (!(j * j > 0)) && (!(j * j > 0)) && (!(j * j > 0)))? ((i + j != j + i) && (!(i + j == j + i)) && (!(j * j > 0)) && (!(j * j > 0)) && (!(j * j > 0)) && (!(j * j > 0)) && (!(j * j > 0)))? (i + j) /  12 : (i + j) /  12 : ((i + j != j + i) && (!(i + j == j + i)) && (!(j * j > 0)) && (!(j * j > 0)) && (!(j * j > 0)) && (!(j * j > 0)) && (!(j * j > 0)))? ((i + j != j + i) && (!(i + j == j + i)) && (!(j * j > 0)) && (!(j * j > 0)) && (!(j * j > 0)) && (!(j * j > 0)) && (!(j * j > 0)))? (i + j) /  12 : (i + j) /  12 : ((i + j != j + i) && (!(i + j == j + i)) && (!(j * j > 0)) && (!(j * j > 0)) && (!(j * j > 0)) && (!(j * j > 0)) && (!(j * j > 0)))? ((i + j != j + i) && (!(i + j == j + i)) && (!(j * j > 0)) && (!(j * j > 0)) && (!(j * j > 0)) && (!(j * j > 0)) && (!(j * j > 0)))? (i + j) /  12 : (i + j) /  12 : ((i + j != j + i) && (!(i + j == j + i)) && (!(j * j > 0)) && (!(j * j > 0)) && (!(j * j > 0)) && (!(j * j > 0)) && (!(j * j > 0)))? ((i + j != j + i) && (!(i + j == j + i)) && (!(j * j > 0)) && (!(j * j > 0)) && (!(j * j > 0)) && (!(j * j > 0)) && (!(j * j > 0)))? (i + j) /  12 : (i + j) /  12 : ((i + j != j + i) && (!(i + j == j + i)) && (!(j * j > 0)) && (!(j * j > 0)) && (!(j * j > 0)) && (!(j * j > 0)) && (!(j * j > 0)))? ((i + j != j + i) && (!(i + j == j + i)) && (!(j * j > 0)) && (!(j * j > 0)) && (!(j * j > 0)) && (!(j * j > 0)) && (!(j * j > 0)))? (i + j) /  12 : (i + j) /  12 : ((i + j != j + i) && (!(i + j == j + i)) && (!(j * j > 0)) && (!(j * j > 0)) && (!(j * j > 0)) && (!(j * j > 0)) && (!(j * j > 0)))? ((i + j != j + i) && (!(i + j == j + i)) && (!(j * j > 0)) && (!(j * j > 0)) && (!(j * j > 0)) && (!(j * j > 0)) && (!(j * j > 0)))? (i + j) /  12 : (i + j) /  12 : ((i + j != j + i) && (!(i + j == j + i)) && (!(j * j > 0)) && (!(j * j > 0)) && (!(j * j > 0)) && (!(j * j > 0)) && (!(j * j > 0)))? ((i + j != j + i) && (!(i + j == j + i)) && (!(j * j > 0)) && (!(j * j > 0)) && (!(j * j > 0)) && (!(j * j > 0)) && (!(j * j > 0)))? (i + j) /  12 : (i + j) /  12 : ((i + j != j + i) && (!(i + j == j + i)) && (!(j * j > 0)) && (!(j * j > 0)) && (!(j * j > 0)) && (!(j * j > 0)) && (!(j * j > 0)))? ((i + j != j + i) && (!(i + j == j + i)) && (!(j * j > 0)) && (!(j * j > 0)) && (!(j * j > 0)) && (!(j * j > 0)) && (!(j * j > 0)))? (i + j) /  12 : (i + j) /  12 : ((j * j > 0) || (!(i + j != j + i)) && (j * j > 0) || (!(i + j != j + i)) && (j * j > 0) || (!(i + j != j + i)) && (j * j > 0))? i * i - i * 12 : (i + j) /  12;
*((i + i * 2 != 3 * i) || (!(!(i + i * 2 != 3 * i))) || (!(!(j + j != 2 * j))))? ((i + i * 2 != 3 * i) || (!(!(i + i * 2 != 3 * i))) || (!(!(j + j != 2 * j))))? i -  31 : i -  31 : ((j + j != 2 * j) || (!(!(i * j != j * i))) || (!(!(j + j != 2 * j))))? i -  31 : i * i - i * 12

 */


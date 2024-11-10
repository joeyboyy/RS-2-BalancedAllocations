#pragma once
#include <random>

static std::mt19937 rng(*(int*)"ANAL");
static std::mt19937 tb_rng(*(int*)"YSIS");

/* Select a random bin with standard/1-choice scheme */
inline int one_choice_drop(std::uniform_int_distribution<int>& uniform_distr)
{
    return uniform_distr(rng);
}

/* Select a random bin with 2-choice scheme */
inline int two_choice_drop(std::uniform_int_distribution<int>& uniform_distr, std::vector<int>& bins)
{
    int opt1 = uniform_distr(rng);
    int opt2 = uniform_distr(rng);

    if (bins[opt1] < bins[opt2])  {
        return opt1;
    }
    else if (bins[opt1] > bins[opt2]) { 
        return opt2;
    }
    else /*bins[opt1] == bins[opt2]*/ {
        std::uniform_int_distribution<int> tie_braker(0, 1);
        if (tie_braker(tb_rng) == 0)
            return opt1;
        else
            return opt2;
    }
}

/* Select a random bin with (1+beta)-choice scheme */
inline int one_plus_beta_choice_drop(std::uniform_int_distribution<int>& uniform_distr, std::vector<int>& bins, double beta)
{
    std::bernoulli_distribution bernoulli(beta);
    if(bernoulli(rng))
        return one_choice_drop(uniform_distr);
    else
        return two_choice_drop(uniform_distr, bins);
}

/* Select a random bin with d-choice scheme, for 1 <= d <= 100 */
inline int d_choice_drop(std::uniform_int_distribution<int>& uniform_distr, std::vector<int>& bins, int d)
{
    constexpr int max_d = 100;
    int opts[max_d]; // array of bins randomly selected

    // draw random bins
    for (int i = 0; i < d; i++)
        opts[i] = uniform_distr(rng);

    // return single possible bin if d == 1
    if (d == 1)
        return opts[0];
    // else...

    // count ties (min_load_ties+1 bins share minimum load)
    int min_load = bins[opts[0]];
    int min_load_idxs[max_d] = {0};
    int min_load_ties = 0;
    for (int i = 1; i < d; i++)
    {
        int X_opti = bins[opts[i]];
        if (X_opti < min_load)
        {
            min_load = X_opti;
            min_load_ties = 0;
            min_load_idxs[0] = i;
        }
        else if (X_opti == min_load)
        {
            min_load_ties++;
            min_load_idxs[min_load_ties] = i;
        }
    }
    // quick return if there are no ties
    if (min_load_ties == 0)
        return opts[min_load_idxs[0]];

    // else: pick a random bin out of the min_load_ties+1 bins sharing minimum load value
    std::uniform_int_distribution<int> tie_braker(0, min_load_ties);
    return opts[min_load_idxs[tie_braker(tb_rng)]];
}

/* Select a random bin with 1-question scheme - d balls, for 1 <= d <= 100 */
inline int one_question_drop(std::uniform_int_distribution<int>& uniform_distr, std::vector<int>& bins, int d, int m)
{
    constexpr int max_d = 100;
    int above[max_d];
    int above_end = 0;
    int below[max_d];
    int below_end = 0;

    // draw random bins and put them in above or below array
    const int median = bins[m/2];
    for (int i = 0; i < d; i++)
    {
        const int tmp = uniform_distr(rng);
        if (bins[tmp] > median)
        {
            above[above_end] = tmp;
            above_end++;
        }
        else
        {
            below[below_end] = tmp;
            below_end++;
        }
    }
    // if exactly one candidate is below --> pick it
    if (below_end == 1)
    {
        return below[0];
    }
    // if several candidates are below --> choose one of them at random
    else if (below_end > 1)
    {
        std::uniform_int_distribution<int> tie_braker(0, below_end-1);
        return below[tie_braker(tb_rng)];
    }
    // if no candidates are below --> choose one of all at random
    else
    {
        std::uniform_int_distribution<int> tie_braker(0, above_end-1);
        return above[tie_braker(tb_rng)];
    }
}

/* Select a random bin with 2-question scheme - d balls, for 1 <= d <= 100 */
inline int two_question_drop(std::uniform_int_distribution<int>& uniform_distr, std::vector<int>& bins, int d, int m)
{
    // this implements the recursive 2-question scheme "unrolled", asking all the questions upfront
    // no matter if they were needed or not (results are the same)

    constexpr int max_d = 100;
    int quart1[max_d];
    int quart1_end = 0;
    int quart2[max_d];
    int quart2_end = 0;
    int quart3[max_d];
    int quart3_end = 0;
    int quart4[max_d];
    int quart4_end = 0;

    // draw random bins and put them in quartile arrays
    const int min25 = bins[1*m/4];
    const int min50 = bins[2*m/4];
    const int min75 = bins[3*m/4];
    for (int i = 0; i < d; i++)
    {
        const int tmp = uniform_distr(rng);
        const int X_tmp = bins[tmp];
        if (X_tmp > min75)
        {
            quart4[quart4_end] = tmp;
            quart4_end++;
        }
        else if (X_tmp > min50)
        {
            quart3[quart3_end] = tmp;
            quart3_end++;
        }
        else if (X_tmp > min25)
        {
            quart2[quart2_end] = tmp;
            quart2_end++;
        }
        else /* X_tmp <= min25 */
        {
            quart1[quart1_end] = tmp;
            quart1_end++;
        }
    }
    // if exactly one candidate is in quartile 1 --> pick it
    if (quart1_end == 1)
    {
        return quart1[0];
    }
    // if several candidates are in quartile 1 --> chose one of them at random
    else if (quart1_end > 1)
    {
        std::uniform_int_distribution<int> tie_braker(0, quart1_end-1);
        return quart1[tie_braker(tb_rng)];
    }
    // if exactly one candidate is in quartile 2 but none in 1 --> pick it
    else if (quart2_end == 1)
    {
        return quart2[0];
    }
    // if severeal candidates are in quartile 2 but none in 1 --> chose one of them at random
    else if (quart2_end > 1)
    {
        std::uniform_int_distribution<int> tie_braker(0, quart2_end-1);
        return quart2[tie_braker(tb_rng)];
    }
    // if exactly one candidate is in quartile 3 but none in 1&2 --> pick it
    else if (quart3_end == 1)
    {
        return quart3[0];
    }
    // if severeal candidates are in quartile 3 but none in 1&2 --> chose one of them at random
    else if (quart3_end > 1)
    {
        std::uniform_int_distribution<int> tie_braker(0, quart3_end-1);
        return quart3[tie_braker(tb_rng)];
    }
    // else all candidates are in quartile 4 --> chose one of them at random
    else 
    {
        std::uniform_int_distribution<int> tie_braker(0, quart4_end-1);
        return quart4[tie_braker(tb_rng)];
    }
}

#ifdef PARTIAL_INFO
/* Drop a ball into a random bin given a k-question allocation scheme
 *
 * Parameters:
 * - uniform_dist       uniform distribution over bins array
 * - bins               bins array (bins[i] = X_i)
 * - m                  number of bins m
 * - d                  number of random bins to choose from: d >= 2
 * - k                  k-question allocation scheme
 * 
 * Returns the index of the selected bin
 */
inline int drop_ball(std::uniform_int_distribution<int>& uniform_distr, std::vector<int>& bins, int m, int d, int k)
{
    if (k == 1) return one_question_drop(uniform_distr, bins, d, m);
    if (k == 2) return two_question_drop(uniform_distr, bins, d, m);
    return -1000000000;

}
#else
/* Drop a ball into a random bin given a d-choice allocation scheme
 *
 * Parameters:
 * - uniform_dist       uniform distribution over bins array
 * - bins               bins array (bins[i] = X_i)
 * - d                  allocation scheme:
 *                      * d-choice for 1 <= d <= upper bound of d_choice_drop()
 *                      * (1+beta)-choice for d == 0
 *                      * undefined behaviour, otherwise
 * - beta               beta value when using 1+beta choice (is ignored otherwise)
 * 
 * Returns the index of the selected bin
 */
inline int drop_ball(std::uniform_int_distribution<int>& uniform_distr, std::vector<int>& bins, int d, double beta)
{
    if (d == 0) return one_plus_beta_choice_drop(uniform_distr, bins, beta);
    if (d == 1) return one_choice_drop(uniform_distr);
    if (d == 2) return two_choice_drop(uniform_distr, bins);
    return d_choice_drop(uniform_distr, bins, d);
}
#endif






#if 0
/* Drop a ball into a random bin given the allocation scheme
 *
 * Parameters:
 * - uniform_dist       uniform distribution over bins array
 * - bins               bins array (bins[i] = X_i)
 * - scheme             allocation scheme:
 *                      * -1: 1-question
 *                      * -2: 2-question
 *                      *  0: (1+beta)-choice
 *                      *  1: d-choice
 *                      * undefined behaviour, otherwise
 * - d                  number of balls involved in the scheme ()
 * - beta               beta value when using 1+beta choice (is ignored otherwise)
 * 
 * Returns the index of the selected bin
 */
inline int drop_ball(std::uniform_int_distribution<int>& uniform_distr, std::vector<int>& bins, int d, int scheme, double beta, int m)
{
    if (scheme == -1) return one_question_drop(uniform_distr, bins, d, m);
    if (scheme == -2) return two_question_drop(uniform_distr, bins, d, m);
    if (scheme == 0) return one_plus_beta_choice_drop(uniform_distr, bins, beta);
    if (scheme == 1) 
    {
        if (d == 1) return one_choice_drop(uniform_distr);
        if (d == 2) return two_choice_drop(uniform_distr, bins);
        return d_choice_drop(uniform_distr, bins, d);
    }
}
#endif
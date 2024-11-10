/*! @file balanced_alloc_batched.cpp
* @brief Balanced allocation experiments, batched version
* @author Manuel Joey Becklas
*
**/
#include "balanced_alloc.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cassert>

// To model partial info, we keep the bins sorted with respect to their load WLOG (the distribution
// of a random number on the bins is the same no matter their order). 
// Defining PARTIAL_INFO/SORT_BINS controls whether the sorted order is enforced or not.
#ifdef PARTIAL_INFO
#define SORT_BINS
#endif

/* Main: Run simulations and save results
 *
 */
int main()
{
    constexpr int T = 20; // #experiment_repetitions
    constexpr int ms[] = {10,100,1000}; // #bins
#ifdef PARTIAL_INFO
    constexpr int ks[][2] = {{1,2},{1,3},{1,5},{2,2},{2,3},{2,5}}; // allocation schemes: [0] k, [1] d
    constexpr int num_schemes = sizeof(ks)/sizeof(int[2]);
#else
    constexpr int ds[] = {0,0,0,1,2,3,4,5,10}; // allocation schemes
    constexpr int num_schemes = sizeof(ds)/sizeof(int);
    constexpr float betas[num_schemes] = {0.25, 0.5, 0.75}; // beta values (only for allocation scheme d == 0)
#endif

    for (const int m : ms) // different values of m
    {
        const int n_max = m*m;  // #balls
        std::uniform_int_distribution<int> uniform_distr(0, m-1);
        const int bs[] = {m, 2*m, 4*m, 8*m, 16*m, 32*m, 64*m, 256*m, 1024*m};
        for (const int b : bs) // batch sizes
        {
            for (int scheme = 0; scheme < num_schemes; scheme++) // different allocation schemes
            {
            #ifdef PARTIAL_INFO
                std::string filename = "../out/avgap_batched" + std::to_string(b/m) + "m_partial_m=" + std::to_string(m) + "_scheme=" + std::to_string(ks[scheme][0]) + "questions-" + std::to_string(ks[scheme][1]) + "bins.txt";
            #else
                std::string filename = "../out/avgap_batched" + std::to_string(b/m) + "m_m=" + std::to_string(m) + "_scheme=" + std::to_string(ds[scheme]) + "_beta=" + std::to_string(betas[scheme]) + ".txt";
            #endif
                std::ofstream out_1(filename);
                if (!out_1) throw;

                std::vector<float> gap(n_max+1+b, 0); // accumulated gap: gap(n) = sum_{t <= T} G_n
            
                for (int t = 0; t < T; t++) // T trials
                {
            #ifdef PARTIAL_INFO
                    std::cerr << "Running " << ks[scheme][0] << "-" << ks[scheme][1] << "-questions for m=" << m << ": trial " << t << "... ";
            #else
                    std::cerr << "Running " << ds[scheme] << "-choice for m=" << m << ": trial " << t << "... ";
            #endif
                    std::vector<int> bins(m, 0); // bins(i) = X_i(n)
                    std::vector<int> bins_old(m); // outdated version of bins
                    int max_load = 0; // = X*(n)

                    for (int n = 1; n <= n_max; ) // balls, 1-indexed!
                    {
                        // update bins_old
                        std::copy(bins.begin(), bins.end(), bins_old.begin());
                        // process a batch
                        for (int bb = 0; bb < b; bb++, n++)
                        {
                            // drop ball / determine bin (with bins_old)
                        #ifdef PARTIAL_INFO
                            int i = drop_ball(uniform_distr, bins_old, m, ks[scheme][1], ks[scheme][0]);
                        #else
                            int i = drop_ball(uniform_distr, bins_old, ds[scheme], betas[scheme]);
                        #endif
                            // place ball (in bins)
                            int& X_i = bins[i];
                            X_i = X_i + 1;
                            if (X_i > max_load)
                            {
                                max_load = X_i;
                            }
                        #ifdef SORT_BINS
                            // restore sorted order of bins
                            // Note that X_i has increased by exactly one --> order can be restored by simply
                            // swapping it with the right-most out-of-order value (or itself, if there is none)
                            // or with the end of the array, if all values are smaller
                            int j;
                            for (j = i+1; j < m; j++)
                            {
                                if (bins[j] >= X_i)
                                    break;
                            }
                            std::swap(X_i, bins[j-1]);
                            // debug check sorting works:
                            // - bins array sorted increasingly
                            // - sum_{i in m} X_i = n (--> no balls get lost)
                            int sum = 0;
                            for (int j = 0; j < m-1; j++)
                            {
                                assert(bins[j] <= bins[j+1]);
                                sum+= bins[j];
                            }
                            sum+= bins[m-1];
                            assert(sum == n);
                        #endif
                            // update gap[n]
                            gap[n] += max_load - (float)n/(float)m;
                        }
                    }
                    std::cerr << "done!\n";
                }

                // write results
                int skip = std::max(n_max / 10000, 1);
                int n = 0;
                for (; n <= 2*m; n++)
                {
                    out_1 << n << " \t" << gap[n]/T << "\n";
                }
                for (; n <= n_max; n+= skip)
                {
                    out_1 << n << " \t" << gap[n]/T << "\n";
                }
            }
        }
    }
}
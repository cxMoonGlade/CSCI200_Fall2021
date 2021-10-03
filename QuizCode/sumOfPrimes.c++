#include <unordered_map>
#include <iostream>
#include <vector>
#include <cmath>


int main(int argc, char** argv) {
    long long n = 20000000;
    int r = sqrt(n);
    std::vector<long long> V;
    for (int i = 1; i <= r; i++) {
        V.push_back(n / i);
    }
    for (int i = V.back() - 1; i > 0; i--) {
        V.push_back(i);
    }
    std::unordered_map<int, long long> S(2 * r);
    for (int i = 0; i < V.size(); i++) {
        const long long v = V[i];
        S[v] = v * (v + 1) / 2 - 1; // (***)
    }
    for (int p = 2; p <= r; p++) {
        if (S[p] > S[p - 1]) {
            for (int i = 0; i < V.size(); i++) {
                const long long v = V[i];
                if (v < p * p) {
                    break;
                }
                S[v] -= p * (S[v / p] - S[p - 1]);
            }
        }
    }
    std::cout << "sum(" << n << ") = " << S[n] << std::endl;
    return 0;
}

//
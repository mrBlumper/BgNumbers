#include <cstdio>
#include <iostream>

#include "primesieve/primesieve.hpp"

#define MAX 800000000

typedef unsigned int Number;
std::vector<Number> primes;
Number index_prime = 0;
Number last_prime = 0;
Number phi_temp[MAX/2+2] = {0};

inline bool isPair(Number n){
    return !(n&0x00000001);
}

Number phi(Number n){
    Number b = n;
    Number phi_ = 0;
        //std::cout<<"--- "<<n<<" "<<last_prime<<"\n";
    if (n == last_prime){
        if (n<=MAX/2+1)
            phi_temp[n] = n - 1;
        return n - 1;
    }

    Number p = 1;
    while (isPair(n) and n) {
        n >>= 1;
        p <<= 1;
    }
    if (p > 1) {
        phi_ = (p>>1) * phi_temp[n];
    } else {
        for (Number i = 1; i < index_prime and primes[i] <= (n/2 + 1); i++){

            while (n % primes[i] == 0 and n) {
                n /= primes[i];
                p *= primes[i];
            }
            if (p > 1) {
                phi_ = p / primes[i] * (primes[i] - 1) * phi_temp[n];
                break;
            }

        }
    }

    if (b <= MAX/2+1){
        phi_temp[b] = phi_;
    }
    return phi_;
}

unsigned long long Mn(unsigned long long A){
    unsigned long long temp_mult = 1;
    unsigned long long temp_add = 0;
    while (A) {
        unsigned long long t = A % 10;
        A /= 10;
        temp_add += t;
        temp_mult *= t;
    }
    return temp_add + temp_mult;
}
int main(){
    std::cout<<"generating primes number under "<<MAX<<"\n";
    primesieve::generate_primes(0, MAX, &primes);
    std::cout<<primes.size()<<" prime number were generated\n";

    phi_temp[1] = 1;

    Number compt = 0;
    Number sub_compt = 2;
    Number explosions = 0;
    std::vector<Number> results;
    for (Number i = 2; i < MAX; i++){
        if (primes[index_prime] <= i){
            last_prime = primes[index_prime];
            index_prime ++;
        }

        if (compt == 1000){
            compt = 0;
            sub_compt += 1000;
            printf("%d [", sub_compt);
            for (Number j = 0; j < results.size(); j++){
                printf("%d ", results[j]);
            }
            printf("], [explosions: %d]\n", explosions);
            explosions = 0;
        }
        compt ++;

        unsigned long long A = (unsigned long long)(index_prime) * (unsigned long long)phi(i);

        unsigned long long mna = Mn(A);
        if (mna == i){
            std::cout<<i<<"\n";
            results.push_back(i);
        } else if (mna > i){
            explosions++;
        }
    }
    return 0;
}

// Name: Ex6_05.cpp - Version 1.0.0
// Author: cdrisko
// Date: 04/30/2020-22:36:56
// Description: Calculating prime numbers using pointer notation

#include <iomanip>
#include <iostream>

int main()
{
    const size_t max {100};                         // Number of primes required
    long primes[max] {2L};                          // First prime defined
    size_t count {1};                               // Count of primes found so far
    long trial {3L};                                // Candidate prime

    while (count < max)
    {
        bool isprime {true};                        // Indicates when a prime is found

        // Try dividing the candidate by all the primes we have
        for (size_t i {}; i < count && isprime; ++i)
        {
            isprime = trial % *(primes + i) > 0;    // False for exact division
        }

        if (isprime)
        {                                           // We got one ...
            *(primes + count++) = trial;            // ... so save it in primes array
        }

        trial += 2;
    }

    // Output primes 10 to a line
    std::cout << "The first " << max << " primes are:" << std::endl;
    for (size_t i {}; i < max; ++i)
    {
        std::cout << std::setw(7) << *(primes + i);
        if ((i+1) % 10 == 0)                        // Newline after every 10th prime
            std::cout << std::endl;
    }
    std::cout << std::endl;
}

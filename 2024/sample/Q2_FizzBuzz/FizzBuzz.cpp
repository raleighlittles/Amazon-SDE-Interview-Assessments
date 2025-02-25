#include <bits/stdc++.h>

void fizzBuzz(int n)
{
    unsigned int i = 1;

    while (i <= n)
    {
        if (i % 3 == 0)
        {
            std::cout << "Fizz";

            if (i % 5 == 0)
            {
                std::cout << "Buzz";
            }

            std::cout << std::endl;
        }
        else if (i % 5 == 0)
        {
            std::cout << "Buzz" << std::endl;
        }
        else
        {
            // Not a multiple of 3 or 5
            std::cout << i << std::endl;
        }

        ++i;
    } // end while
}

int main()
{
    fizzBuzz(15);
    return 0;
}
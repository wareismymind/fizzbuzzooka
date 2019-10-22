#include "flexibuzz.hpp"

#include <iostream>
#include <optional>

void usage()
{
    std::cout << "usage: fb <n>\r\n" << std::endl;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        usage();
        return 1;
    }

    int n = 0;

    try
    {
        n = std::stoi(argv[1]);
    }
    catch (...)
    {
        usage();
        return 1;
    }

    flexibuzz<int, std::string> fb(
        [] (int a, int b) { return a % b == 0; },
        [] (int a) { return std::to_string(a); },
        std::map<int, std::string> {
            { 3, "Fizz" },
            { 5, "Buzz" },
            { 15, "FizzBuzz" }
        });

    for (auto i = 1; i <= n; i++)
        std::cout << fb[i] << std::endl;
}

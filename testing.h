#include "lcs.h"
#include <algorithm>
#include <random>

std::default_random_engine generator;

int generateInt(int left, int right)
{
    std::uniform_int_distribution<int> distribution(left, right);
    return distribution(generator);
}

std::string generateString(size_t size)
{
    std::string result = "";
    for (size_t i = 1; i < size; i++)
    {
        int new_char_number = generateInt(0, 25);
        char new_char = (char)new_char_number + 'a';
        result += new_char;
    }
    return result;
}

bool testingWithCurrentLength(size_t firstLength, size_t secondLength, unsigned int numberOfTests)
{
    bool correctWork = true;
    for (unsigned int i = 0; i < numberOfTests; i++)
    {
        std::string first = generateString(firstLength), second = generateString(secondLength);
        std::vector < std::vector <int> > resultOfFastAlgorithm, resultOfSlowAlgorithm;
        fastLCS(first, second, resultOfFastAlgorithm);
        slowLCS(first, second, resultOfSlowAlgorithm);
        if (!compareVectors(resultOfFastAlgorithm, resultOfSlowAlgorithm))
            correctWork = false;
    }
    return correctWork;
}

bool testing(unsigned int numberOfTests)
{
    bool correctWork = true;
    for (unsigned int i = 0; i <= numberOfTests; i++)
    {
        size_t firstLength = (size_t)generateInt(0, i), secondLength = (size_t)generateInt(0, i);
        unsigned int numberOfTestsWithCurrentLength = (unsigned int)generateInt(10, 30);
        if (!testingWithCurrentLength(firstLength, secondLength, numberOfTestsWithCurrentLength))
            correctWork = false;
    }
    return correctWork;
}

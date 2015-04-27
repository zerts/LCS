#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

const long long INF = 10000000;

void writeVector(std::vector < std::vector <int> > &out)
{
    for (size_t i = 0; i < out.size(); i++)
    {
        for (size_t j = 0; j < out[i].size(); j++)
            std::cout << out[i][j] << ' ';
        std::cout << std::endl;
    }
}

bool compareVectors(std::vector < std::vector <int> > &first, std::vector < std::vector <int> > &second)
{
    if (first.size() != second.size())
        return false;
    for (size_t i = 0; i < first.size(); i++)
    {
        if (first[i].size() != second[i].size())
            return false;
        for (size_t j = 0; j < first[i].size(); j++)
            if (first[i][j] != second[i][j])
                return false;
    }
    return true;
}

void findCriticalPoints(std::string &first, std::string &second, std::vector < std::vector <bool> > &criticalPoints)
{
    criticalPoints.resize(first.size() + 1);
    for (size_t i = 0; i <= first.size(); i++)
        criticalPoints[i].assign(first.size() + 1, false);
    std::vector<int> v(first.size() + 1, 0);
    std::vector < std::vector <int> > indexOnHorisontalVertexes(second.size() + 1, v), indexOnVerticalVertexes(second.size() + 1, v);
    for (size_t j = 0; j <= first.size(); j++)
        indexOnHorisontalVertexes[0][j] = j;
    for (size_t l = 0; l <= second.size(); l++)
        indexOnVerticalVertexes[l][0] = 0;
    for (size_t l = 1; l <= second.size(); l++)
    {
        for (size_t j = 1; j <= first.size(); j++)
        {
            if (second[l - 1] != first[j - 1])
            {
                indexOnHorisontalVertexes[l][j] = std::max(indexOnVerticalVertexes[l][j - 1], indexOnHorisontalVertexes[l - 1][j]);
                indexOnVerticalVertexes[l][j] = std::min(indexOnVerticalVertexes[l][j - 1], indexOnHorisontalVertexes[l - 1][j]);
            }
            else
            {
                indexOnHorisontalVertexes[l][j] = indexOnVerticalVertexes[l][j - 1];
                indexOnVerticalVertexes[l][j] = indexOnHorisontalVertexes[l - 1][j];
            }
        }
    }
    for (size_t i = 1; i <= first.size(); i++)
        criticalPoints[indexOnHorisontalVertexes[second.size()][i]][i] = true;
}

void fastLCS(std::string &first, std::string &second, std::vector < std::vector <int> > &result)
{
    std::vector < std::vector <bool> > criticalPoints;
    findCriticalPoints(first, second, criticalPoints);
    result.resize(first.size() + 1);
    for (size_t i = 0; i <= first.size(); i++)
        result[i].assign(first.size() + 1, 0);
    for (size_t i = 1; i <= first.size(); i++)
        if (!criticalPoints[i][i])
            result[i][i] = 1;
    for (size_t i = 2; i <= first.size(); i++)
    {
        for (size_t j = 0; j <= first.size() - i; j++)
        {
            if (result[j + 1][i + j - 1] != result[j + 2][i + j])
                result[j + 1][i + j] = std::max(result[j + 1][i + j - 1], result[j + 2][i + j]);
            else
            {
                if (result[j + 2][i + j - 1] == result[j + 2][i + j])
                    result[j + 1][i + j] = result[j + 2][i + j];
                else
                {
                    if (criticalPoints[j + 1][i + j])
                        result[j + 1][i + j] = result[j + 2][i + j];
                    else
                        result[j + 1][i + j] = result[j + 2][i + j] + 1;
                }
            }
        }
    }
}


void slowLCS(std::string &first, std::string &second, std::vector < std::vector <int> > &result)
{
    std::vector<int> v(second.size() + 1, 0);
    std::vector < std::vector <int> > lcs(first.size() + 1, v);
    result.resize(first.size() + 1);
    for (size_t i = 0; i <= first.size(); i++)
        result[i].assign(first.size() + 1, 0);
    for (size_t e = 1; e <= first.size(); e++)
    {
        for (size_t i = e; i <= first.size(); i++)
        {
            for (size_t j = 1; j <= second.size(); j++)
            {
                if (first[i - 1] == second[j - 1])
                    lcs[i][j] = lcs[i - 1][j - 1] + 1;
                else
                    lcs[i][j] = std::max(lcs[i - 1][j], lcs[i][j - 1]);
            }
        }
        for (size_t i = e; i <= first.size(); i++)
            result[e][i] = lcs[i][second.size()];
        for (size_t i = 0; i <= first.size(); i++)
            for (size_t j = 0; j <= second.size(); j++)
                lcs[i][j] = 0;
    }
}

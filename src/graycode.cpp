#include "graycode.h"

string gray_to_str(unsigned int gray, int n)
{
    string s;
    for (int i = n - 1; i >= 0; i--)
    {
        s.push_back((gray >> i) & 1 ? '1' : '0');
    }
    return s;
}

vector<string> generate_gray_universe(int n)
{
    if (n <= 0)
        return {};

    size_t N = 1ul << n;
    vector<string> result;
    result.reserve(N);

    for (size_t i = 0; i < N; i++)
    {
        unsigned int cur = static_cast<unsigned int>(i ^ (i >> 1));
        result.push_back(gray_to_str(cur, n));
    }
    return result;
}

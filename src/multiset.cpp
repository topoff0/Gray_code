#include "multiset.h"
#include "random.h"
#include "config.h"

using std::max;
using std::min;

size_t Multiset::get_size() const
{
    return this->counts.size();
}

void Multiset::fill_auto()
{
    for (size_t i = 0; i < counts.size(); i++)
    {
        counts[i] = random::generate_random(0, MULTISET_MAX_CARDINALITY);
    }
    initialized = true;
}

void Multiset::fill_auto_base_on_universe(Multiset U)
{
    for (size_t i = 0; i < U.get_size(); i++)
    {
        counts[i] = random::generate_random(0, U[i]);
    }
    initialized = true;
}

void Multiset::fill_manual(const vector<long long> &values)
{
    if (values.size() != counts.size())
        throw std::invalid_argument("Размер исходного мультимножества не совпадает с количеством вводимых значений");
    for (size_t i = 0; i < counts.size(); i++)
    {
        counts[i] = values[i];
    }
    initialized = true;
}

vector<long long> Multiset::get_cardinalities() const
{
    return counts;
}

bool Multiset::is_initialized()
{
    return initialized;
}

long long &Multiset::operator[](size_t index)
{
    if (index < 0 || index > this->get_size())
        throw std::out_of_range("Индекс мультимножества вне диапазона");
    return counts[index];
}
const long long &Multiset::operator[](size_t index) const
{
    if (index < 0 || index > this->get_size())
        throw std::out_of_range("Индекс мультимножества вне диапазона");
    return counts[index];
}

Multiset ms_union(const Multiset &A, const Multiset &B)
{
    int n = A.get_size();
    Multiset R(n);

    for (int i = 0; i < n; i++)
    {
        R[i] = max(A[i], B[i]);
    }
    return R;
}

Multiset ms_intersection(const Multiset &A, const Multiset &B)
{
    int n = A.get_size();
    Multiset R(n);

    for (int i = 0; i < n; i++)
    {
        R[i] = min(A[i], B[i]);
    }
    return R;
}

Multiset ms_diff(const Multiset &A, const Multiset &B)
{
    int n = A.get_size();
    Multiset R(n);

    for (int i = 0; i < n; i++)
    {
        R[i] = max(0LL, A[i] - B[i]);
    }
    return R;
}

Multiset ms_sym_diff(const Multiset &A, const Multiset &B)
{
    int n = A.get_size();
    Multiset R(n);

    for (int i = 0; i < n; i++)
    {
        R[i] = llabs(A[i] - B[i]);
    }
    return R;
}

Multiset ms_complement(const Multiset &A, const Multiset &U)
{
    int n = A.get_size();
    Multiset R(n);

    for (int i = 0; i < n; i++)
    {
        R[i] = max(0LL, U[i] - A[i]);
    }
    return R;
}

Multiset ms_arith_sum(const Multiset &A, const Multiset &B, const Multiset &U)
{
    int n = A.get_size();
    Multiset R(n);

    for (int i = 0; i < n; i++)
    {
        R[i] = min(A[i] + B[i], U[i]);
    }
    return R;
}

Multiset ms_arith_diff(const Multiset &A, const Multiset &B)
{
    return ms_diff(A, B);
}

Multiset ms_prod(const Multiset &A, const Multiset &B, const Multiset &U)
{
    int n = A.get_size();
    Multiset R(n);

    for (int i = 0; i < n; i++)
    {
        R[i] = min(A[i] * B[i], U[i]);
    }
    return R;
}

Multiset ms_div(const Multiset &A, const Multiset &B)
{
    int n = A.get_size();
    Multiset R(n);

    for (int i = 0; i < n; i++)
    {
        if (B[i] == 0)
            R[i] = 0;
        else
            R[i] = A[i] / B[i];
    }
    return R;
}

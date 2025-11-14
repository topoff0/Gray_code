#pragma once

#include <vector>

using std::vector;

class Multiset
{
private:
    vector<long long> counts;
    bool initialized;

public:
    // === Constructors ===
    Multiset(size_t size) : counts(size, 0), initialized(false) {}

    // === Public Methods ===
    size_t get_size() const;
    void fill_auto();
    void fill_auto_base_on_universe(Multiset U);
    void fill_manual(const vector<long long> &values);
    vector<long long> get_cardinalities() const;
    bool is_initialized();

    // === Override Operators ===
    // << [] >>
    long long &operator[](size_t index);
    const long long &operator[](size_t index) const;
};

Multiset ms_union(const Multiset &A, const Multiset &B);
Multiset ms_intersection(const Multiset &A, const Multiset &B);
Multiset ms_diff(const Multiset &A, const Multiset &B, const Multiset &U);
Multiset ms_sym_diff(const Multiset &A, const Multiset &, const Multiset &U);

Multiset ms_complement(const Multiset &A, const Multiset &U);

Multiset ms_arith_sum(const Multiset &A, const Multiset &B, const Multiset &U);
Multiset ms_arith_diff(const Multiset &A, const Multiset &B);
Multiset ms_prod(const Multiset &A, const Multiset &B, const Multiset &U);
Multiset ms_div(const Multiset &A, const Multiset &B);

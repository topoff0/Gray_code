#pragma once
#include "io.h"

class app
{
private:
    static const vector<pair<string, COLOR>> main_menu_items;
    static const vector<pair<string, COLOR>> main_menu_exit_items;
    static const vector<pair<string, COLOR>> exit_items;
    static const vector<pair<string, COLOR>> universe_creation_items;
    static const vector<pair<string, COLOR>> multiset_creation_items;
    static const vector<pair<string, COLOR>> operation_items;

    static bool _running;
    static bool _back;

    // === Process commands ===
    static void process_main_menu(const int choice);
    static void process_operation(const int choice,
                                  const Multiset &A,
                                  const Multiset &B,
                                  const Multiset &U,
                                  vector<string> universe);
    static void process_universe_creation(const int choice,
                                          Multiset &U,
                                          vector<string> &universe,
                                          bool &stop_creation);
    static void process_multiset_creation(const int choice,
                                          Multiset &A, Multiset &B,
                                          const Multiset &U,
                                          vector<string> &universe,
                                          bool &stop_creation);

    // === Multiset fill ===
    static void fill_multiset_manual(Multiset &M, const Multiset &U, vector<string> &universe);

    class MainMenu
    {
    public:
        static void start();
        static void show_instruction();
        static void show_gray_code_info();
    };

    class Operations
    {
    public:
        class Set
        {
        public:
            static void execute_union(const Multiset &A, const Multiset &B, const string &header, const vector<string> &universe);
            static void execute_intersection(const Multiset &A, const Multiset &B, const string &header, const vector<string> &universe);
            static void execute_difference(const Multiset &A, const Multiset &B, const Multiset &U, const string &header, const vector<string> &universe);
            static void execute_symmetric_difference(const Multiset &A, const Multiset &B, const Multiset &U, const string &header, const vector<string> &universe);
            static void execute_complement(const Multiset &M, const Multiset &U, const string &header, const vector<string> &universe);
        };
        class Arithmetic
        {
        public:
            static void execute_arithmetic_sum(const Multiset &A, const Multiset &B, const Multiset &U, const string &header, const vector<string> &universe);
            static void execute_arithmetic_difference(const Multiset &A, const Multiset &B, const string &header, const vector<string> &universe);
            static void execute_arithmetic_product(const Multiset &A, const Multiset &B, const Multiset &U, const string &header, const vector<string> &universe);
            static void execute_arithmetic_division(const Multiset &A, const Multiset &B, const string &header, const vector<string> &universe);
        };
    };

public:
    static void run();
};

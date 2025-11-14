#include "app.h"
#include "config.h"
#include "menu.h"
#include "multiset.h"
#include "graycode.h"
#include "info.h"

const std::vector<std::pair<std::string, COLOR>> app::main_menu_items = {
    {"Начать работу", BASE},
    {"Инструкция", BASE},
    {"О коде Грея", BASE}};

const std::vector<std::pair<std::string, COLOR>> app::main_menu_exit_items = {
    {"Завершить работу", RED}};

const std::vector<std::pair<std::string, COLOR>> app::exit_items = {
    {"Вернуться в главное меню", RED},
    {"Завершить работу", RED}};

const std::vector<std::pair<std::string, COLOR>> app::multiset_creation_items = {
    {"Создать мультимножество A автоматически", BASE},
    {"Создать мультимножество A вручную", BASE},
    {"Создать мультимножество B автоматически", BASE},
    {"Создать мультимножество B вручную", BASE},
    {"Продолжить", GREEN}};

const std::vector<std::pair<std::string, COLOR>> app::operation_items = {
    {"Объединение (A ∪ B)", BLUE},
    {"Пересечение (A ∩ B)", BLUE},
    {"Разность (A \\ B)", BLUE},
    {"Разность (B \\ A)", BLUE},
    {"Симметрическая разность (A Δ B)", BLUE},
    {"Дополнение A", GREEN},
    {"Дополнение B", GREEN},
    {"Арифметическая сумма (A ⊕ B)", YELLOW},
    {"Арифметическая разность (A ⊖ B)", YELLOW},
    {"Арифметическая разность (B ⊖ A)", YELLOW},
    {"Арифметическое произведение (A ⊗ B)", YELLOW},
    {"Арифметическое деление (A / B)", YELLOW},
    {"Арифметическое деление (B / A)", YELLOW}};

const std::vector<std::pair<std::string, COLOR>> app::universe_creation_items = {
    {"Заполнить универсум автоматически", BASE},
    {"Заполнить универсум вручную", BASE},
    {"Продолжить", GREEN}};

bool app::_running = true;
bool app::_back = false;

void app::process_main_menu(const int choice)
{
    switch (choice)
    {
    case 0:
        _running = false;
        break;
    case 1:
        app::MainMenu::start();
        break;
    case 2:
        app::MainMenu::show_instruction();
        break;
    case 3:
        app::MainMenu::show_gray_code_info();
        break;

    default:
        break;
    }
}

void app::process_operation(const int choice,
                            const Multiset &A,
                            const Multiset &B,
                            const Multiset &U,
                            vector<string> universe)
{
    switch (choice)
    {
    case -1:
    {
        _back = true;
        break;
    }
    case 0:
        _running = false;
        break;
    case 1:
        app::Operations::Set::execute_union(A, B, "Объединение мультимножеств A и B", universe);
        break;
    case 2:
        app::Operations::Set::execute_intersection(A, B, "Пересечение мультимножеств A и B", universe);
        break;
    case 3:
        app::Operations::Set::execute_difference(A, B, U, "Разность мультимножеств A и B", universe);
        break;
    case 4:
        app::Operations::Set::execute_difference(B, A, U, "Разность мультимножеств B и A", universe);
        break;
    case 5:
        app::Operations::Set::execute_symmetric_difference(A, B, U, "Симметрическая разность A и B", universe);
        break;
    case 6:
        app::Operations::Set::execute_complement(A, U, "Дополнение А", universe);
        break;
    case 7:
        app::Operations::Set::execute_complement(B, U, "Дополнение B", universe);
        break;
    case 8:
        app::Operations::Arithmetic::execute_arithmetic_sum(A, B, U, "Арифметическая сумма A и B", universe);
        break;
    case 9:
        app::Operations::Arithmetic::execute_arithmetic_difference(A, B, "Арифметическая разность A и B", universe);
        break;
    case 10:
        app::Operations::Arithmetic::execute_arithmetic_difference(B, A, "Арифметическая разность B и A", universe);
        break;
    case 11:
        app::Operations::Arithmetic::execute_arithmetic_product(A, B, U, "Арифметическое произведение A и B", universe);
        break;
    case 12:
        app::Operations::Arithmetic::execute_arithmetic_division(A, B, "Арифметическое деление A и B", universe);
        break;
    case 13:
        app::Operations::Arithmetic::execute_arithmetic_division(B, A, "Арифметическое деление B и A", universe);
        break;

    default:
        break;
    }
}

void app::process_universe_creation(const int choice, Multiset &U, vector<string> &universe, bool &stop_creation)
{
    switch (choice)
    {
    case -1:
    {
        stop_creation = true;
        _back = true;
        return;
    }
    case 1:
    {
        U.fill_auto();
        break;
    }
    case 2:
    {
        size_t size = U.get_size();
        Multiset MAX(size);
        vector<long long> values(size, MULTISET_MAX_CARDINALITY);
        MAX.fill_manual(values);
        app::fill_multiset_manual(U, MAX, universe);
        break;
    }
    case 3:
    {
        if (U.is_initialized())
            stop_creation = true;
        else
        {
            string error_message = "Универсум не инициализирован";

            io::print_error(error_message);
            io::wait_enter();
        }
        return;
    }

    default:
        return;
    }
    io::print_header("Универсум успешно создан", BOXED, GREEN);
    io::print_multiset(U, "Универсум", universe);
    io::wait_enter();
}

void app::process_multiset_creation(const int choice,
                                    Multiset &A,
                                    Multiset &B,
                                    const Multiset &U,
                                    vector<string> &universe,
                                    bool &stop_creation)
{
    switch (choice)
    {
    case -1:
    {
        stop_creation = true;
        _back = true;
        break;
    }
    case 0:
        stop_creation = true;
        _running = false;
        break;
    case 1:
    {
        A.fill_auto_base_on_universe(U);
        io::print_header("Мультимножество A успешно создано", BOXED, GREEN);
        io::print_multiset(A, "Мультимножество A", universe);
        io::wait_enter();
        break;
    }
    case 2:
    {
        app::fill_multiset_manual(A, U, universe);
        io::print_header("Мультимножество A успешно создано", BOXED, GREEN);
        io::print_multiset(A, "Мультимножество A", universe);
        io::wait_enter();
        break;
    }

    case 3:
    {
        B.fill_auto_base_on_universe(U);
        io::print_header("Мультимножество B успешно создано", BOXED, GREEN);
        io::print_multiset(B, "Мультимножество B", universe);
        io::wait_enter();
        break;
    }

    case 4:
    {
        app::fill_multiset_manual(B, U, universe);
        io::print_header("Мультимножество B успешно создано", BOXED, GREEN);
        io::print_multiset(B, "Мультимножество B", universe);
        io::wait_enter();
        break;
    }
    case 5:
    {
        if (A.is_initialized() && B.is_initialized())
            stop_creation = true;
        else
        {
            string error_message = "Не все мультимножества инициализированы: ( ";
            if (!A.is_initialized())
                error_message += "A";
            if (!B.is_initialized())
            {
                if (!A.is_initialized())
                    error_message += ", ";
                error_message += "B";
            }
            error_message += " )";

            io::print_error(error_message);
            io::wait_enter();
        }
        break;
    }

    default:
        break;
    }
}

void app::fill_multiset_manual(Multiset &M, const Multiset &U, vector<string> &universe)
{
    vector<long long> values;
    size_t size = M.get_size();
    if (size == 0)
    {
        M.fill_auto_base_on_universe(U);
        return;
    }

    io::print_header("Ручное заполнение мультимножества", BOLD);
    io::print_header("Введите мощности для каждого элемента", BOXED);

    for (size_t i = 0; i < size; i++)
    {
        string prompt = "Элемент '" + universe[i] + "' (макс. " + std::to_string(U[i]) + "): ";
        long long value = io::read_number(0, U[i], prompt);
        values.push_back(value);
    }

    M.fill_manual(values);
}

void app::run()
{
    io::print_header("Лабораторная работа №1. Код Грея.", HEADER_STYLE::SIMPLE);
    io::v_space(1);

    Menu main_menu("Главное меню");

    while (_running)
    {
        _back = false;
        main_menu.show(main_menu_items, main_menu_exit_items, "Список команд");
        int choice = io::read_number(-(main_menu_exit_items.size() - 1), main_menu_items.size(), "Введите номер команды");
        process_main_menu(choice);
    }
    io::print_header("Программа завершила свою работу", BOLD, GREEN);
}

void app::MainMenu::start()
{
    io::print_header("СОЗДАНИЕ УНИВЕРСУМА", HEADER_STYLE::BOXED, CYAN);
    string input_prompt = "Введите разрядность кода Грея (0-" + std::to_string(MULTISET_MAX_BIT_DEPTH) + string(")");
    unsigned int bits = static_cast<unsigned int>(io::read_number(0, MULTISET_MAX_BIT_DEPTH, input_prompt));

    vector<string> gray_universe = generate_gray_universe(bits);

    // Меню создания универсума
    Multiset U(bits != 0 ? 1 << bits : 0);
    bool stop_universe_creation = false;
    while (!stop_universe_creation && !_back)
    {
        Menu create_multiset_menu("Меню создания универсума");
        create_multiset_menu.show(universe_creation_items, exit_items, "Список команд", BOXED);
        int choice = io::read_number(-(exit_items.size() - 1), universe_creation_items.size(), "Введите номер команды");
        app::process_universe_creation(choice, U, gray_universe, stop_universe_creation);
    }

    // Меню заполнения мультимножеств
    Multiset A(bits != 0 ? 1 << bits : 0), B(bits != 0 ? 1 << bits : 0);

    bool stop_multiset_creation = false;
    while (!stop_multiset_creation && !_back)
    {
        Menu multiset_menu("Меню создания мультимножеств");
        multiset_menu.show(multiset_creation_items, exit_items, "Список команд");

        int choice = io::read_number(-(exit_items.size() - 1), multiset_creation_items.size(), "Введите номер команды");
        process_multiset_creation(choice, A, B, U, gray_universe, stop_multiset_creation);
    }

    // Меню операций над мультимножествами
    Menu operations_menu("Меню операций над мультимножествами");
    while (_running && !_back)
    {
        operations_menu.show(operation_items, exit_items, "Список операций");

        int choice = io::read_number(-(exit_items.size() - 1), operation_items.size(), "Введите номер операции");
        process_operation(choice, A, B, U, gray_universe);
    }
}

void app::MainMenu::show_instruction()
{
    io::print_text_with_header(
        info::app_instruction_text,
        "ИНСТРУКЦИЯ",
        "",
        HEADER_STYLE::BOXED,
        BLUE);
    io::wait_enter();
}

void app::MainMenu::show_gray_code_info()
{
    io::print_text_with_header(
        info::gray_info,
        "О КОДЕ ГРЕЯ",
        info::gray_info_link,
        HEADER_STYLE::BOXED,
        BLUE);
    io::wait_enter();
}

void app::Operations::Set::execute_union(const Multiset &A, const Multiset &B, const string &header, const vector<string> &universe)
{
    io::print_header(header, BOXED);
    Multiset R = ms_union(A, B);
    io::print_multiset(R, "Результат объединения", universe);
    io::wait_enter();
}

void app::Operations::Set::execute_intersection(const Multiset &A, const Multiset &B, const string &header, const vector<string> &universe)
{
    io::print_header(header, BOXED);
    Multiset R = ms_intersection(A, B);
    io::print_multiset(R, "Результат пересечения", universe);
    io::wait_enter();
}

void app::Operations::Set::execute_difference(const Multiset &A, const Multiset &B, const Multiset &U, const string &header, const vector<string> &universe)
{
    io::print_header(header, BOXED);
    Multiset R = ms_diff(A, B, U);
    io::print_multiset(R, "Результат разности", universe);
    io::wait_enter();
}

void app::Operations::Set::execute_symmetric_difference(const Multiset &A, const Multiset &B, const Multiset &U, const string &header, const vector<string> &universe)
{
    io::print_header(header, BOXED);
    Multiset R = ms_sym_diff(A, B, U);
    io::print_multiset(R, "Результат симметрической разности", universe);
    io::wait_enter();
}

void app::Operations::Set::execute_complement(const Multiset &M, const Multiset &U, const string &header, const vector<string> &universe)
{
    io::print_header(header, BOXED);
    Multiset R = ms_complement(M, U);
    io::print_multiset(R, "Результат дополнения", universe);
    io::wait_enter();
}

void app::Operations::Arithmetic::execute_arithmetic_sum(const Multiset &A, const Multiset &B, const Multiset &U, const string &header, const vector<string> &universe)
{
    io::print_header(header, BOXED);
    Multiset R = ms_arith_sum(A, B, U);
    io::print_multiset(R, "Результат арифметической суммы", universe);
    io::wait_enter();
}

void app::Operations::Arithmetic::execute_arithmetic_difference(const Multiset &A, const Multiset &B, const string &header, const vector<string> &universe)
{
    io::print_header(header, BOXED);
    Multiset R = ms_arith_diff(A, B);
    io::print_multiset(R, "Результат арифметической разности", universe);
    io::wait_enter();
}

void app::Operations::Arithmetic::execute_arithmetic_product(const Multiset &A, const Multiset &B, const Multiset &U, const string &header, const vector<string> &universe)
{
    io::print_header(header, BOXED);
    Multiset R = ms_prod(A, B, U);
    io::print_multiset(R, "Результат арифметического произведения", universe);
    io::wait_enter();
}

void app::Operations::Arithmetic::execute_arithmetic_division(const Multiset &A, const Multiset &B, const string &header, const vector<string> &universe)
{
    io::print_header(header, BOXED);
    Multiset R = ms_div(A, B);
    io::print_multiset(R, "Результат арифметического деления", universe);
    io::wait_enter();
}

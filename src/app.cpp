#include "app.h"
#include "config.h"
#include "menu.h"
#include "multiset.h"
#include "graycode.h"
#include "info.h"

const std::vector<std::pair<std::string, COLOR>> app::operation_items = {
    {"Объединение (A ∪ B)>", BLUE},
    {"Пересечение (A ∩ B)>", BLUE},
    {"Разность (A \\ B)", BLUE},
    {"Разность (B \\ A)", BLUE},
    {"Симметрическая разность (A Δ B)", BLUE},
    {"Дополнение A", GREEN},
    {"Дополнение B", GREEN},
    {"Арифметическая сумма (A ⊕ B)", YELLOW},
    {"Арифметическая разность (A ⊖ B)", YELLOW},
    {"Арифметическая разность (B ⊖ A)", YELLOW},
    {"Арифметическое произведение (A ⊗ B)", YELLOW},
    {"Арифметическое деление (A/B)", YELLOW},
    {"Арифметическое деление (B/A)", YELLOW}};

const std::vector<std::pair<std::string, COLOR>> app::main_menu_items = {
    {"Начать работу", BASE},
    {"Инструкция", BASE},
    {"О коде Грея", BASE}};

const std::vector<std::pair<std::string, COLOR>> app::multiset_creation_items = {
    {"Создать мультимножество A автоматически", BASE},
    {"Создать мультимножество A вручную", BASE},
    {"Создать мультимножество B автоматически", BASE},
    {"Создать мультимножество B вручную", BASE},
    {"Продолжить", GREEN}};

bool app::_running = true;

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
        app::Operations::Set::execute_difference(A, B, "Разность мультимножеств A и B", universe);
        break;
    case 4:
        app::Operations::Set::execute_difference(B, A, "Разность мультимножеств B и A", universe);
        break;
    case 5:
        app::Operations::Set::execute_symmetric_difference(A, B, "Симметрическая разность A и B", universe);
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

void app::process_multiset_creation(const int choice,
                                    Multiset &A,
                                    Multiset &B,
                                    const Multiset &U,
                                    vector<string> &universe,
                                    bool &stop_creation)
{
    switch (choice)
    {
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

    io::print_header("Ручное заполнение мультимножества", BOXED);
    io::print_multiset(U, "Универсум", universe);

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
        main_menu.show(main_menu_items, "Список команд");
        int choice = io::read_number(0, main_menu_items.size(), "Введите номер команды");
        process_main_menu(choice);
    }
    io::print_header("Программа завершила свою работу", BOLD, GREEN);
}

void app::MainMenu::start()
{
    io::print_header("СОЗДАНИЕ УНИВЕРСУМА", HEADER_STYLE::BOXED, CYAN);
    string input_prompt = "Введите разрядность кода Грея (1-" + std::to_string(MULTISET_MAX_BIT_DEPTH) + string(")");
    unsigned int bits = static_cast<unsigned int>(io::read_number(1, MULTISET_MAX_BIT_DEPTH, input_prompt));

    // Создание универсума
    vector<string> gray_universe = generate_gray_universe(bits);

    Multiset U(1 << bits);
    U.fill_auto();

    io::print_header("Универсум успешно создан", BOXED, GREEN);
    io::print_multiset(U, "Универсум", gray_universe);
    io::wait_enter();

    // Меню заполнения мультимножеств
    Multiset A(1 << bits), B(1 << bits);

    bool stop_creation = false;
    while (!stop_creation)
    {
        Menu multiset_menu("Меню создания мультимножеств");
        multiset_menu.show(multiset_creation_items, "Список команд");

        int choice = io::read_number(0, multiset_creation_items.size(), "Введите номер команды");
        process_multiset_creation(choice, A, B, U, gray_universe, stop_creation);
    }

    // Меню операций над мультимножествами
    Menu operations_menu("Меню операций над мультимножествами");
    while (_running)
    {
        operations_menu.show(operation_items, "Список операций");

        int choice = io::read_number(0, operation_items.size(), "Введите номер операции");
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

void app::Operations::Set::execute_difference(const Multiset &A, const Multiset &B, const string &header, const vector<string> &universe)
{
    io::print_header(header, BOXED);
    Multiset R = ms_diff(A, B);
    io::print_multiset(R, "Результат разности", universe);
    io::wait_enter();
}

void app::Operations::Set::execute_symmetric_difference(const Multiset &A, const Multiset &B, const string &header, const vector<string> &universe)
{
    io::print_header(header, BOXED);
    Multiset R = ms_sym_diff(A, B);
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

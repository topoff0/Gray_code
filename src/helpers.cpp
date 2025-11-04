#include "helpers.h"
#include "io.h"

int helpers::count_visible_chars(const string &s)
{
    int count = 0;
    for (unsigned char c : s)
    {
        if ((c & 0xC0) != 0x80)
            count++;
    }
    return count;
}

vector<string> helpers::split_text(const string &text, int max_line_length)
{
    vector<string> lines;
    string current_line;
    size_t byte_pos = 0;                      // позиция в байтах
    size_t text_length_bytes = text.length(); // длина в байтах

    while (byte_pos < text_length_bytes)
    {
        // Пропускаем начальные пробелы (работаем с байтами)
        while (byte_pos < text_length_bytes && text[byte_pos] == ' ')
        {
            byte_pos++;
        }
        if (byte_pos >= text_length_bytes)
            break;

        // Находим конец текущего слова (в байтах)
        size_t word_end = text.find(' ', byte_pos);
        if (word_end == string::npos)
        {
            word_end = text_length_bytes;
        }

        // Извлекаем слово (в байтах)
        string word = text.substr(byte_pos, word_end - byte_pos);

        // Проверяем длину в ВИДИМЫХ СИМВОЛАХ
        int current_line_chars = count_visible_chars(current_line);
        int word_chars = count_visible_chars(word);
        int space_chars = current_line.empty() ? 0 : 1;

        if (current_line_chars + word_chars + space_chars > max_line_length)
        {
            if (!current_line.empty())
            {
                lines.push_back(current_line);
                current_line.clear();
            }
        }

        // Добавляем слово к текущей строке
        if (!current_line.empty())
        {
            current_line += " ";
        }
        current_line += word;

        // Переходим к следующему слову (в байтах)
        byte_pos = word_end + 1;
    }

    // Добавляем последнюю строку
    if (!current_line.empty())
    {
        lines.push_back(current_line);
    }

    return lines;
}
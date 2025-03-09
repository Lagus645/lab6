#include <iostream>
#include <string>
#include <clocale>
using namespace std;

// Функция для проверки, является ли символ цифрой
bool isDigit(char ch) {
    return ch >= '0' && ch <= '9';
}

// Функция для проверки, является ли символ буквой
bool isAlpha(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

// Функция для проверки, является ли символ буквой или цифрой
bool isAlnum(char ch) {
    return isAlpha(ch) || isDigit(ch);
}

// Функция для проверки, состоит ли строка только из цифр
bool isDigitsOnly(const string& str) {
    for (char ch : str) {
        if (!isDigit(ch)) {
            return false;
        }
    }
    return true;
}

// Функция для преобразования слова в идентификатор
string toIdentifier(const string& word) {
    if (word.empty()) {
        return word;
    }

    string identifier;
    // Если первый символ не буква и не подчеркивание, добавляем подчеркивание
    if (!isAlpha(word[0]) && word[0] != '_') {
        identifier += '_';
    }

    // Проходим по каждому символу слова
    for (char ch : word) {
        // Если символ допустим в идентификаторе (буква, цифра или подчеркивание), добавляем его
        if (isAlnum(ch) || ch == '_') {
            identifier += ch;
        }
        else {
            // Иначе заменяем на подчеркивание
            identifier += '_';
        }
    }

    return identifier;
}

// Основная функция для обработки строки
string transformString(const string& input) {
    string result;
    string word;
    bool firstWord = true;

    for (size_t i = 0; i < input.length(); ++i) {
        char ch = input[i];

        // Если символ не пробел и не точка, добавляем его в текущее слово
        if (ch != ' ' && ch != '.') {
            word += ch;
        }
        else {
            // Если слово не пустое, обрабатываем его
            if (!word.empty()) {
                // Пропускаем слова, состоящие только из цифр
                if (!isDigitsOnly(word)) {
                    // Преобразуем слово в идентификатор
                    string identifier = toIdentifier(word);

                    // Добавляем пробел перед словом, если это не первое слово
                    if (!firstWord) {
                        result += ' ';
                    }
                    else {
                        firstWord = false;
                    }

                    // Добавляем преобразованное слово в результат
                    result += identifier;
                }
                word.clear(); // Очищаем текущее слово
            }

            // Если текущий символ — точка, завершаем обработку
            if (ch == '.') {
                break;
            }
        }
    }

    // Добавляем точку в конец строки
    result += '.';

    return result;
}

int main() {
    setlocale(LC_ALL, "russian");
    string input = "123 hello 456 world 789 this is a test 123.";
    string output = transformString(input);

    cout << "Ввод:  " << input << endl;
    cout << "Вывод: " << output << endl;

    return 0;
}
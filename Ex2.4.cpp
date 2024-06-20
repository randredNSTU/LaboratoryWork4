#include <iostream>
#include <vector>
#include <random> // Для minstd_rand и uniform_int_distribution

using namespace std;

// Функция для генерации случайного символа ('A'-'Z', '0'-'9')
char random_char(minstd_rand& rng) {
    uniform_int_distribution<int> dist(0, 35); // диапазон от 'A' до 'Z' и от '0' до '9' в ASCII
    int num = dist(rng);
    if (num < 26) {
        return static_cast<char>('A' + num); // возвращает случайный символ 'A'-'Z'
    } else {
        return static_cast<char>('0' + (num - 26)); // возвращает случайную цифру '0'-'9'
    }
}

// Функция для вывода массива символов
void print_chars(const vector<char>& chars) {
    cout << "[";
    for (size_t i = 0; i < chars.size(); ++i) {
        cout << chars[i];
        if (i < chars.size() - 1) {
            cout << ",";
        }
    }
    cout << "]" << endl;
}

int main() {
    int n;
    cout << "Введите размер массива символов (n >= 5): ";
    cin >> n;

    // Проверка на корректность ввода
    if (n < 5) {
        cerr << "Ошибка: размер массива должен быть не менее 5\n";
        return 1;
    }

    minstd_rand rng(random_device{}()); // Инициализация генератора случайных чисел
    vector<char> chars(n);

    // Инициализация массива случайными символами ('A'-'Z', '0'-'9')
    for (int i = 0; i < n; ++i) {
        chars[i] = random_char(rng);
    }

    // Вывод исходного массива символов
    cout << "Исходный массив символов: ";
    print_chars(chars);

    // Модификация массива: перемещение первых двух элементов в конец
    vector<char> moved_chars;
    moved_chars.push_back(chars[0]);   // сохраняем первый элемент
    moved_chars.push_back(chars[1]);   // сохраняем второй элемент

    chars.erase(chars.begin(), chars.begin() + 2);  // удаляем первые два элемента из начала
    chars.insert(chars.end(), moved_chars.begin(), moved_chars.end());  // добавляем сохранённые элементы в конец

    // Вывод модифицированного массива символов
    cout << "Модифицированный массив символов: ";
    print_chars(chars);

    return 0;
}

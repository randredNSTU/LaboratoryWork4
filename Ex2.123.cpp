#include <iostream>     // для ввода/вывода
#include <vector>       // для использования векторов
#include <random>       // для minstd_rand и uniform_int_distribution
#include <numeric>      // для std::accumulate

using namespace std;    // использование пространства имен std

// Функция для генерации случайного числа в диапазоне [min, max]
int random_int(minstd_rand& rng, int min, int max) {
    uniform_int_distribution<int> dist(min, max);   // определение распределения
    return dist(rng);   // возврат случайного числа в указанном диапазоне
}

// Функция для нахождения самой длинной убывающей последовательности
vector<int> longest_decreasing_sequence(const vector<int>& arr) {
    vector<int> longest_seq;    // вектор для хранения самой длинной последовательности
    vector<int> current_seq;    // вектор для текущей последовательности

    // Проверка последовательности и её обновление
    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i] < arr[i - 1]) {
            current_seq.push_back(arr[i - 1]);    // добавление элемента в текущую последовательность
        } else {
            current_seq.push_back(arr[i - 1]);    // добавление последнего элемента в текущую последовательность
            if (current_seq.size() > longest_seq.size()) {
                longest_seq = current_seq;   // обновление самой длинной последовательности
            }
            current_seq.clear();    // очистка текущей последовательности
        }
    }

    // Последняя проверка
    current_seq.push_back(arr.back());    // добавление последнего элемента
    if (current_seq.size() > longest_seq.size()) {
        longest_seq = current_seq;   // обновление самой длинной последовательности
    }

    return longest_seq;    // возврат самой длинной убывающей последовательности
}

int main() {
    int n;
    cout << "Введите количество чисел в массиве (n >= 10): ";   // вывод сообщения пользователю
    cin >> n;   // считывание количества чисел

    // Проверка на корректность ввода
    if (n < 10) {
        cerr << "Ошибка: количество чисел должно быть не менее 10\n";   // вывод сообщения об ошибке
        return 1;   // возврат кода ошибки
    }

    minstd_rand rng(random_device{}()); // Инициализация генератора случайных чисел
    vector<int> arr(n); // Создание вектора из n элементов

    // Инициализация массива случайными числами из [150, 300]
    for (int i = 0; i < n; ++i) {
        arr[i] = random_int(rng, 150, 300);   // заполнение массива случайными числами
    }

    // Вывод исходного массива
    cout << "Исходный массив:\n";   // вывод сообщения
    for (int num : arr) {
        cout << num << " "; // вывод элементов массива
    }
    cout << "\n";    // переход на новую строку

    // Находим самую длинную убывающую последовательность
    vector<int> longest_seq = longest_decreasing_sequence(arr); // поиск убывающей последовательности

    // Выводим найденную последовательность
    cout << "Самая длинная убывающая последовательность:\n"; // вывод сообщения
    for (int num : longest_seq) {
        cout << num << " "; // вывод элементов последовательности
    }
    cout << "\n";    // переход на новую строку

    // Вычисляем среднеарифметическое значение исходного массива
    double average = static_cast<double>(accumulate(arr.begin(), arr.end(), 0)) / n;   // вычисление среднего арифметического

    // Создаём новый массив из чисел, меньших среднеарифметического значения
    vector<int> less_than_average;  // создание вектора для чисел, меньших среднего
    for (int num : arr) {
        if (num < average) {
            less_than_average.push_back(num);   // добавление числа в вектор
        }
    }

    // Выводим новый массив
    cout << "Массив чисел, меньших среднеарифметического (" << average << "):\n";   // вывод сообщения
    for (int num : less_than_average) {
        cout << num << " "; // вывод элементов массива
    }
    cout << "\n";    // переход на новую строку

    return 0;   // успешное завершение программы
}

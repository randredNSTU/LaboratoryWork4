#include <iostream>
#include <vector>
#include <random> // Для minstd_rand и uniform_int_distribution
#include <algorithm> // Для сортировки
#include <array> // Для подсчёта вхождений

using namespace std;

// Функция для генерации случайного целого числа в диапазоне [100, 900]
int random_number(minstd_rand& rng) {
    uniform_int_distribution<int> dist(100, 900);
    return dist(rng);
}

// Функция для вывода массива целых чисел
void print_numbers(const vector<int>& numbers) {
    cout << "[";
    for (size_t i = 0; i < numbers.size(); ++i) {
        cout << numbers[i];
        if (i < numbers.size() - 1) {
            cout << ",";
        }
    }
    cout << "]" << endl;
}

int main() {
    int n;
    cout << "Введите размер массива целых чисел: ";
    cin >> n;

    minstd_rand rng(random_device{}()); // Инициализация генератора случайных чисел
    vector<int> numbers(n);

    // Инициализация массива случайными целыми числами в диапазоне [100, 900]
    for (int i = 0; i < n; ++i) {
        numbers[i] = random_number(rng);
    }

    // Вывод исходного массива чисел
    cout << "Исходный массив чисел: ";
    print_numbers(numbers);

    // Сортировка массива по убыванию
    sort(numbers.begin(), numbers.end(), greater<int>());

    // Вывод отсортированного массива чисел
    cout << "Отсортированный массив чисел (по убыванию): ";
    print_numbers(numbers);

    // Подсчёт встречаемости каждой цифры в элементах массива
    array<int, 10> digit_counts = {0}; // массив для хранения количества вхождений цифр (0-9)

    for (int number : numbers) {
        while (number > 0) {
            int digit = number % 10; // получаем последнюю цифру числа
            digit_counts[digit]++;   // увеличиваем счётчик для этой цифры
            number /= 10;            // удаляем последнюю цифру числа
        }
    }

    // Вывод количества вхождений каждой цифры
    cout << "Количество вхождений каждой цифры в массиве:\n";
    for (int i = 0; i < 10; ++i) {
        cout << "Цифра " << i << ": " << digit_counts[i] << " раз(а)\n";
    }

    return 0;
}

#include <iostream>
#include <vector>
#include <random>
#include <numeric>
#include <algorithm>
#include <array>

using namespace std;

// Функция для генерации случайного числа в диапазоне [min, max]
int random_int(minstd_rand& rng, int min, int max) {
    uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

// Функция для генерации случайного символа ('A'-'Z', '0'-'9')
char random_char(minstd_rand& rng) {
    uniform_int_distribution<int> dist(0, 35);
    int num = dist(rng);
    if (num < 26) {
        return static_cast<char>('A' + num);
    } else {
        return static_cast<char>('0' + (num - 26));
    }
}

// Функция для генерации случайного целого числа в диапазоне [100, 900]
int random_number(minstd_rand& rng) {
    uniform_int_distribution<int> dist(100, 900);
    return dist(rng);
}

// Функция для нахождения самой длинной убывающей последовательности
vector<int> longest_decreasing_sequence(const vector<int>& arr) {
    vector<int> longest_seq;
    vector<int> current_seq;

    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i] < arr[i - 1]) {
            current_seq.push_back(arr[i - 1]);
        } else {
            current_seq.push_back(arr[i - 1]);
            if (current_seq.size() > longest_seq.size()) {
                longest_seq = current_seq;
            }
            current_seq.clear();
        }
    }

    current_seq.push_back(arr.back());
    if (current_seq.size() > longest_seq.size()) {
        longest_seq = current_seq;
    }

    return longest_seq;
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
    minstd_rand rng(random_device{}());

    // Часть 1: Работа с массивом целых чисел
    int n;
    cout << "Введите количество чисел в массиве (n >= 10): ";
    cin >> n;

    if (n < 10) {
        cerr << "Ошибка: количество чисел должно быть не менее 10\n";
        return 1;
    }

    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        arr[i] = random_int(rng, 150, 300);
    }

    cout << "Исходный массив:\n";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << "\n";

    vector<int> longest_seq = longest_decreasing_sequence(arr);
    cout << "Самая длинная убывающая последовательность:\n";
    for (int num : longest_seq) {
        cout << num << " ";
    }
    cout << "\n";

    double average = static_cast<double>(accumulate(arr.begin(), arr.end(), 0)) / n;
    vector<int> less_than_average;
    for (int num : arr) {
        if (num < average) {
            less_than_average.push_back(num);
        }
    }

    cout << "Массив чисел, меньших среднеарифметического (" << average << "):\n";
    for (int num : less_than_average) {
        cout << num << " ";
    }
    cout << "\n";

    // Часть 2: Работа с массивом символов
    int m;
    cout << "Введите размер массива символов (m >= 5): ";
    cin >> m;

    if (m < 5) {
        cerr << "Ошибка: размер массива должен быть не менее 5\n";
        return 1;
    }

    vector<char> chars(m);
    for (int i = 0; i < m; ++i) {
        chars[i] = random_char(rng);
    }

    cout << "Исходный массив символов: ";
    print_chars(chars);

    vector<char> moved_chars;
    moved_chars.push_back(chars[0]);
    moved_chars.push_back(chars[1]);

    chars.erase(chars.begin(), chars.begin() + 2);
    chars.insert(chars.end(), moved_chars.begin(), moved_chars.end());

    cout << "Модифицированный массив символов: ";
    print_chars(chars);

    // Часть 3: Работа с массивом целых чисел в диапазоне [100, 900]
    int p;
    cout << "Введите размер массива целых чисел: ";
    cin >> p;

    vector<int> numbers(p);
    for (int i = 0; i < p; ++i) {
        numbers[i] = random_number(rng);
    }

    cout << "Исходный массив чисел: ";
    print_numbers(numbers);

    sort(numbers.begin(), numbers.end(), greater<int>());

    cout << "Отсортированный массив чисел (по убыванию): ";
    print_numbers(numbers);

    array<int, 10> digit_counts = {0};
    for (int number : numbers) {
        while (number > 0) {
            int digit = number % 10;
            digit_counts[digit]++;
            number /= 10;
        }
    }

    cout << "Количество вхождений каждой цифры в массиве:\n";
    for (int i = 0; i < 10; ++i) {
        cout << "Цифра " << i << ": " << digit_counts[i] << " раз(а)\n";
    }

    return 0;
}
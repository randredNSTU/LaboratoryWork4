#include <iostream>     // Подключаем стандартную библиотеку ввода-вывода
#include <random>       // Подключаем библиотеку для генерации случайных чисел
#include <cmath>        // Подключаем библиотеку для математических функций
#include <vector>       // Подключаем библиотеку для использования векторов

using namespace std;    // Используем пространство имён std

// Функция для вычисления критерия хи-квадрат
double chiSquaredTest(const vector<int>& observed, int expected) {
    double chiSquared = 0.0;
    for (size_t i = 0; i < observed.size(); ++i) {
        double observed_i = observed[i];
        chiSquared += pow(observed_i - expected, 2) / expected;
    }
    return chiSquared;
}

int main() {
    const int sizes[] = {50, 100, 1000};   // Размеры массивов
    const int n_intervals = 10;            // Количество интервалов
    const int min_value = 1;               // Минимальное значение для генерации
    const int max_value = 100;             // Максимальное значение для генерации

    // Инициализация генератора случайных чисел с использованием minstd_rand
    minstd_rand generator(time(0));

    // Определение диапазона для генерации случайных чисел
    uniform_int_distribution<int> distribution(min_value, max_value);

    // Перебираем все размеры массивов
    for (size_t s = 0; s < sizeof(sizes) / sizeof(sizes[0]); ++s) {
        int n = sizes[s];   // Текущий размер массива
        vector<int> arr(n); // Создаём массив размером n

        // Заполняем массив случайными числами в заданном диапазоне
        for (int i = 0; i < n; ++i) {
            arr[i] = distribution(generator);
        }

        // Вычисляем ширину интервала
        double interval_width = (max_value - min_value + 1) / static_cast<double>(n_intervals);

        // Создаём массив для подсчёта попаданий в интервалы
        vector<int> observed(n_intervals, 0);

        // Заполняем observed массив
        for (int i = 0; i < n; ++i) {
            int value = arr[i];
            int interval_index = (value - min_value) / interval_width;
            if (interval_index >= 0 && interval_index < n_intervals) {
                observed[interval_index]++;
            }
        }

        // Вычисляем ожидаемое количество попаданий в каждый интервал
        int expected = n / n_intervals;

        // Вычисляем критерий хи-квадрат
        double chi_squared = chiSquaredTest(observed, expected);

        // Выводим результаты для текущего размера массива
        cout << "Размер массива: " << n << endl;
        cout << "Ожидаемое количество элементов в интервале: " << expected << endl;
        cout << "Значение критерия хи-квадрат: " << chi_squared << endl;

        // Проверяем гипотезу о нормальном распределении (условие)
        if (chi_squared <= n_intervals - 1) {
            cout << "Гипотеза о нормальном распределении принимается." << endl;
        } else {
            cout << "Гипотеза о нормальном распределении отвергается." << endl;
        }

        cout << endl;   // Пустая строка для разделения вывода результатов для разных размеров массивов
    }

    return 0;   // Возвращаем 0, что означает успешное завершение программы
}

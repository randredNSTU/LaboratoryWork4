#include <iostream>
#include <vector>
#include <random> // Для minstd_rand и uniform_int_distribution
#include <cmath> // Для вычислений

using namespace std;

// Функция для генерации случайного числа в диапазоне [1, 100]
int random_number(minstd_rand& rng) {
    uniform_int_distribution<int> dist(1, 100);
    return dist(rng);
}

// Функция для вывода массива чисел (первые 10 элементов или все в зависимости от параметра show_all)
void print_array(const vector<int>& arr, bool show_all = false) {
    cout << "[";
    int count = show_all ? arr.size() : min(10, static_cast<int>(arr.size())); // определяем количество элементов для вывода
    for (int i = 0; i < count; ++i) {
        cout << arr[i];
        if (i < count - 1) {
            cout << ",";
        }
    }
    if (!show_all && arr.size() > 10) {
        cout << ",...";
    }
    cout << "]" << endl;
}

// Функция для вычисления критерия хи-квадрат
double chi_square_test(const vector<int>& arr, int expected_value) {
    int n = arr.size();
    int num_intervals = 10; // количество интервалов
    int interval_size = 100 / num_intervals; // размер каждого интервала

    vector<int> observed_counts(num_intervals, 0); // фактическое количество элементов в каждом интервале

    // Заполнение фактического количества элементов в интервалах
    for (int number : arr) {
        int interval_index = (number - 1) / interval_size; // определение индекса интервала
        observed_counts[interval_index]++;
    }

    // Вычисление критерия хи-квадрат
    double chi_square = 0.0;
    for (int i = 0; i < num_intervals; ++i) {
        double expected = static_cast<double>(n) / num_intervals; // ожидаемое количество элементов в каждом интервале
        chi_square += pow(observed_counts[i] - expected, 2) / expected;
    }

    return chi_square;
}

int main() {
    minstd_rand rng(random_device{}()); // Инициализация генератора случайных чисел

    // Создание и заполнение массивов размерами 50, 100 и 1000 случайными числами от 1 до 100
    vector<int> arr50(50);
    vector<int> arr100(100);
    vector<int> arr1000(1000);

    for (int i = 0; i < 50; ++i) {
        arr50[i] = random_number(rng);
    }

    for (int i = 0; i < 100; ++i) {
        arr100[i] = random_number(rng);
    }

    for (int i = 0; i < 1000; ++i) {
        arr1000[i] = random_number(rng);
    }

    // Вывод массивов (первые 10 элементов или все)
    bool show_all = false; // измените на true, чтобы вывести все элементы массивов
    cout << "Массив из 50 элементов: ";
    print_array(arr50, show_all);
    cout << "Массив из 100 элементов: ";
    print_array(arr100, show_all);
    cout << "Массив из 1000 элементов: ";
    print_array(arr1000, show_all);

    // Вычисление критерия хи-квадрат для каждого массива
    double chi_square_50 = chi_square_test(arr50, 50 / 10);
    double chi_square_100 = chi_square_test(arr100, 100 / 10);
    double chi_square_1000 = chi_square_test(arr1000, 1000 / 10);

    // Вывод результатов теста
    cout << "Результаты критерия хи-квадрат:\n";
    cout << "Для массива из 50 элементов: " << chi_square_50 << endl;
    cout << "Ожидаемое математическое ожидание: " << 50 / 10 << endl; // для массива из 50 элементов
    cout << "Реальное математическое ожидание: " << static_cast<double>(50) / 10 << endl; // для массива из 50 элементов
    double chi_critical_value = 16.919; // значение хи-критического для степеней свободы 9 и уровня значимости 0.05
    cout << "Хи-критическое значение для уровня значимости 0.05: " << chi_critical_value << endl;
    cout << "Результат проверки гипотезы (превышение хи-критического): " << (chi_square_50 > chi_critical_value ? "Гипотеза отвергается" : "Гипотеза принимается") << endl;
    cout << endl;

    cout << "Для массива из 100 элементов: " << chi_square_100 << endl;
    cout << "Ожидаемое математическое ожидание: " << 100 / 10 << endl; // для массива из 100 элементов
    cout << "Реальное математическое ожидание: " << static_cast<double>(100) / 10 << endl; // для массива из 100 элементов
    cout << "Хи-критическое значение для уровня значимости 0.05: " << chi_critical_value << endl;
    cout << "Результат проверки гипотезы (превышение хи-критического): " << (chi_square_100 > chi_critical_value ? "Гипотеза отвергается" : "Гипотеза принимается") << endl;
    cout << endl;

    cout << "Для массива из 1000 элементов: " << chi_square_1000 << endl;
    cout << "Ожидаемое математическое ожидание: " << 1000 / 10 << endl; // для массива из 1000 элементов
    cout << "Реальное математическое ожидание: " << static_cast<double>(1000) / 10 << endl; // для массива из 1000 элементов
    cout << "Хи-критическое значение для уровня значимости 0.05: " << chi_critical_value << endl;
    cout << "Результат проверки гипотезы (превышение хи-критического): " << (chi_square_1000 > chi_critical_value ? "Гипотеза отвергается" : "Гипотеза принимается") << endl;

    return 0;
}

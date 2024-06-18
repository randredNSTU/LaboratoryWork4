#include <iostream>   // Подключение стандартной библиотеки для ввода-вывода
#include <cmath>      // Подключение библиотеки математических функций
#include <iomanip>    // Подключение библиотеки для управления выводом формата чисел

using namespace std;  // Использование пространства имен std (стандартной библиотеки)

// Функция, для которой ищем корни: cos(x + 0.5) - x - 2
double f(double x) {
    return cos(x + 0.5) - x - 2;  // Определение функции и её возвращаемое значение
}

// Производная функции: -sin(x + 0.5) - 1
double df(double x) {
    return -sin(x + 0.5) - 1;  // Вычисление производной функции
}

// Метод половинного деления для нахождения корня на отрезке [a, b] с точностью ε
void bisectionMethod(double a, double b, double epsilon) {
    // Проверка наличия корней на концах отрезка
    if (f(a) * f(b) > 0) {
        cout << "На заданном интервале нет корней или их количество нечетное." << endl;
        return;  // Возвращаемся, если корни отсутствуют
    }

    // Переменные для хранения текущего приближения корня и числа итераций
    double c, fc;
    int iter = 0;

    cout << "Метод половинного деления:" << endl;
    cout << setw(5) << "N" << setw(15) << "a" << setw(15) << "b" << setw(15) << "b - a" << endl;

    // Начало цикла метода половинного деления
    do {
        iter++;              // Увеличение числа итераций
        c = (a + b) / 2;     // Нахождение середины интервала
        fc = f(c);           // Вычисление значения функции в точке c

        // Вывод текущей итерации: номер, значения a, b и длина интервала b - a
        cout << setw(5) << iter << setw(15) << a << setw(15) << b << setw(15) << b - a << endl;

        // Проверка условия сходимости: если знаки функции на концах интервала разные, сдвигаем границы
        if (f(a) * fc < 0)
            b = c;  // Перемещаем правую границу
        else
            a = c;  // Перемещаем левую границу
    } while (fabs(b - a) > epsilon);  // Повторяем, пока не достигнем заданной точности

    // Вывод приближенного значения корня
    cout << "Приближенный корень методом половинного деления: " << setprecision(10) << c << endl;
}

// Метод Ньютона для нахождения корня с начальным приближением x0 и точностью ε
void newtonMethod(double x0, double epsilon) {
    double x = x0;         // Начальное приближение
    int iter = 0;          // Счетчик итераций

    cout << "Метод Ньютона:" << endl;
    cout << setw(5) << "N" << setw(15) << "x_n" << setw(15) << "x_n+1" << setw(15) << "x_n+1 - x_n" << endl;

    do {
        iter++;              // Увеличение числа итераций
        double fx = f(x);    // Вычисление значения функции в точке x
        double dfx = df(x);  // Вычисление значения производной функции в точке x
        double x1 = x - fx / dfx;  // Вычисление следующего приближения методом Ньютона

        // Вывод текущей итерации: номер, текущее и следующее приближение, их разность
        cout << setw(5) << iter << setw(15) << x << setw(15) << x1 << setw(15) << x1 - x << endl;

        x = x1;  // Переходим к следующему приближению
    } while (fabs(f(x)) > epsilon);  // Повторяем, пока не достигнем заданной точности

    // Вывод приближенного значения корня
    cout << "Приближенный корень методом Ньютона: " << setprecision(10) << x << endl;
}

// Метод простых итераций для нахождения корня с начальным приближением x0 и точностью ε
void fixedPointIteration(double x0, double epsilon) {
    double x = x0;         // Начальное приближение
    int iter = 0;          // Счетчик итераций

    cout << "Метод простых итераций:" << endl;
    cout << setw(5) << "N" << setw(15) << "x_n" << setw(15) << "x_n+1" << setw(15) << "x_n+1 - x_n" << endl;

    do {
        iter++;              // Увеличение числа итераций
        double x1 = cos(x + 0.5) - 2;  // Функция g(x) = cos(x + 0.5) - 2 для метода простых итераций

        // Вывод текущей итерации: номер, текущее и следующее приближение, их разность
        cout << setw(5) << iter << setw(15) << x << setw(15) << x1 << setw(15) << x1 - x << endl;

        x = x1;  // Переходим к следующему приближению
    } while (fabs(f(x)) > epsilon);  // Повторяем, пока не достигнем заданной точности

    // Вывод приближенного значения корня
    cout << "Приближенный корень методом простых итераций: " << setprecision(10) << x << endl;
}

// Основная функция программы
int main() {
    double a = -5.0;        // Начальная левая граница интервала для метода половинного деления
    double b = 5.0;         // Начальная правая граница интервала для метода половинного деления
    double x0 = 0.0;        // Начальное приближение для метода Ньютона и метода простых итераций
    double epsilon = 1e-4;  // Заданная точность

    // Вызываем метод половинного деления
    bisectionMethod(a, b, epsilon);

    cout << endl;

    // Вызываем метод Ньютона
    newtonMethod(x0, epsilon);

    cout << endl;

    // Вызываем метод простых итераций
    fixedPointIteration(x0, epsilon);

    return 0;  // Возвращаем успешный код завершения программы
}
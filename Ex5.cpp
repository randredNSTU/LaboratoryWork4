#include <iostream>  // Подключаем заголовочный файл для работы с вводом/выводом в консоль
#include <vector>    // Подключаем заголовочный файл для работы с векторами
#include <unordered_map>  // Подключаем заголовочный файл для работы с хэш-таблицами

using namespace std;  // Используем пространство имён std для упрощения доступа к стандартным библиотечным элементам

// Функция для генерации последовательности линейного конгруэнтного генератора
void linearCongruentialGenerator(int X0, int A, int B, int C) {
    vector<int> sequence;  // Вектор для хранения сгенерированной последовательности чисел
    unordered_map<int, int> seen;  // Хэш-таблица для отслеживания повторений чисел в последовательности

    int Xi = X0;  // Инициализируем текущее значение Xi начальным значением X0
    int index = 0;  // Индекс текущего элемента последовательности

    // Цикл для генерации последовательности до тех пор, пока не найдём повторение
    while (seen.find(Xi) == seen.end()) {  // Пока текущее значение Xi не найдено в хэш-таблице seen
        seen[Xi] = index;  // Записываем текущий индекс в хэш-таблицу seen для значения Xi
        sequence.push_back(Xi);  // Добавляем текущее значение Xi в конец вектора sequence
        Xi = (A * Xi + B) % C;  // Вычисляем следующее значение Xi по формуле линейного конгруэнтного генератора
        index++;  // Увеличиваем индекс для следующего элемента последовательности
    }

    // Выводим сгенерированную последовательность чисел
    for (int i = 0; i < sequence.size(); ++i) {
        cout << sequence[i] << " ";
    }
    cout << endl;

    // Находим и выводим индекс, с которого начинается повторение последовательности
    cout << seen[Xi] << endl;  // Выводим индекс, соответствующий первому появлению повторяющегося значения Xi
}

int main() {
    // Примеры из задачи
    int X0_1 = 2, A_1 = 3, B_1 = 5, C_1 = 10;  // Параметры для первого примера
    int X0_2 = 5, A_2 = 3, B_2 = 3, C_2 = 7;   // Параметры для второго примера

    cout << "Пример 1" << endl;
    linearCongruentialGenerator(X0_1, A_1, B_1, C_1);  // Вызов функции для первого примера

    cout << "Пример 2" << endl;
    linearCongruentialGenerator(X0_2, A_2, B_2, C_2);  // Вызов функции для второго примера

    return 0;  // Возвращаем 0, что означает успешное завершение программы
}

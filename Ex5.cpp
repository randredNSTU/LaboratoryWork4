#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

struct Generator { //Определяет структуру `Generator`, которая представляет собой линейный конгруэнтный генератор.
    int X0, A, B, C;
    unordered_set<int> sequence; // Множества для хранения сгенерированных чисел и повторяющихся чисел соответственно.
    unordered_set<int> repeating;

    Generator(int X0, int A, int B, int C) : X0(X0), A(A), B(B), C(C) {} // Конструктор структуры `Generator`, инициализирующий поля значениями, переданными в качестве аргументов.

    int next() {
        int current = (A * X0 + B) % C; // генерируем число по формуле
        if (sequence.count(current) > 0) { // проверяет было ли сгенерированно это число 
            repeating.insert(current);//добавляем число во множество повторяющихся чисел
            return -1; //возращаем -1
        }
        sequence.insert(current); //добавляем числов последовательность
        X0 = current; //сгенерированное число становится текущим значением
        return current;
    }
};

int main() {
    int X0, A, B, C; //x0- начальное значение , а- множитель , в- - инкрементирующее значение, С - диапазон значений
    cout << "Enter X0, A, B, C: ";
    cin >> X0 >> A >> B >> C;

    Generator gen(X0, A, B, C);
    

    vector<int> sequence; // Объявляет вектор для хранения сгенерированной последовательности чисел.
    sequence.push_back(X0); // вносим в вектор начальное значение
    int index = 0;
    while (true) {
        int num = gen.next(); //генерация след числа
        if (num == -1)  // если -1,то началось повторение
            break;
        sequence.push_back(num); //добавление сгенерированного числа в вектор
        index++; //увеличиваем индекс
    }

    cout << "Generated sequence: ";
    for (int num : sequence) {
        cout << num << " ";
    }
    cout << "\nIndex of repeating sequence: " << index + 1 << endl;

    return 0;
}
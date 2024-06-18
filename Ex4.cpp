#include <iostream>
#include <vector>
#include <random>

using namespace std;

// Функция для алгоритма, всегда предает
bool alwaysBetray(int round_number, const vector<bool>& self_choices, const vector<bool>& enemy_choices) {
    return false; // Всегда возвращает false, что означает предательство
}

// Функция для алгоритма, всегда сотрудничает
bool alwaysCooperate(int round_number, const vector<bool>& self_choices, const vector<bool>& enemy_choices) {
    return true; // Всегда возвращает true, что означает сотрудничество
}

// Функция для алгоритма, случайный выбор
bool randomChoice(int round_number, const vector<bool>& self_choices, const vector<bool>& enemy_choices) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 1);
    return dis(gen); // Случайный выбор: 0 (предательство) или 1 (сотрудничество)
}

// Функция для вычисления очков в раунде
pair<int, int> calculateRoundScores(bool choiceA, bool choiceB) {
    if (choiceA && choiceB) {
        return {24, 24};    // Оба сотрудничают
    } else if (!choiceA && choiceB) {
        return {0, 20};     // A предал, B сотрудничает
    } else if (choiceA && !choiceB) {
        return {20, 0};     // A сотрудничает, B предал
    } else {
        return {4, 4};      // Оба предали
    }
}

// Функция для проведения игры с заданными алгоритмами
void playGame(bool (*algorithmA)(int, const vector<bool>&, const vector<bool>&),
              bool (*algorithmB)(int, const vector<bool>&, const vector<bool>&)) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> roundsDistribution(100, 200); // Случайное количество раундов от 100 до 200

    int rounds = roundsDistribution(gen); // Генерация случайного количества раундов

    vector<bool> choicesA(rounds); // Выборы алгоритма A
    vector<bool> choicesB(rounds); // Выборы алгоритма B

    // Итерация по всем раундам
    for (int round = 0; round < rounds; ++round) {
        bool choiceA = algorithmA(round, choicesA, choicesB); // Выбор алгоритма A
        bool choiceB = algorithmB(round, choicesB, choicesA); // Выбор алгоритма B

        choicesA[round] = choiceA;
        choicesB[round] = choiceB;

        // Вычисление очков в текущем раунде
        pair<int, int> scores = calculateRoundScores(choiceA, choiceB);

        // Вывод результатов текущего раунда
        cout << "Раунд " << round + 1 << ": ";
        cout << "A выбрал " << (choiceA ? "сотрудничество" : "предательство") << ", ";
        cout << "B выбрал " << (choiceB ? "сотрудничество" : "предательство") << ". ";
        cout << "Очки: A = " << scores.first << ", B = " << scores.second << endl;
    }

    // Вычисление и вывод итоговых результатов
    int totalScoreA = 0, totalScoreB = 0;
    for (int i = 0; i < rounds; ++i) {
        pair<int, int> scores = calculateRoundScores(choicesA[i], choicesB[i]);
        totalScoreA += scores.first;
        totalScoreB += scores.second;
    }
    cout << "Итоговые очки: A = " << totalScoreA << ", B = " << totalScoreB << endl;
    cout << endl;
}

int main() {
    cout << "Игра 1: Всегда предать vs Всегда сотрудничать" << endl;
    playGame(alwaysBetray, alwaysCooperate);

    cout << "Игра 2: Всегда предать vs Случайный выбор" << endl;
    playGame(alwaysBetray, randomChoice);

    cout << "Игра 3: Всегда сотрудничать vs Случайный выбор" << endl;
    playGame(alwaysCooperate, randomChoice);

    return 0;
}

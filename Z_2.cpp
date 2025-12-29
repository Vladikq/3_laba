#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <random>
#include <map>
using namespace std;

// Генерация случайного числа в диапазоне [min, max]
int getRandomNumber(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// Решето Эратосфена для нахождения простых чисел до limit
void Eratosthenes(vector<int>& PrimeNums, int limit) {
    for(int i = 2; i < limit; i++) {
        PrimeNums.push_back(i);
    }

    for (int i = 0; i <= sqrt(PrimeNums.size()); i++) {
        int j = i + 1;
        while (j < PrimeNums.size()) {
            if (PrimeNums[j] % PrimeNums[i] == 0) {
                for (int k = j; k < PrimeNums.size() - 1; k++) {
                    PrimeNums[k] = PrimeNums[k + 1];
                }
                PrimeNums.pop_back();
            } else {
                j++;
            }
        }
    }
}

// Быстрое возведение в степень по модулю
int modPow(int a, int q, int RandNum) {
    int result = 1;
    while (q > 0) {
        if (q % 2 == 1) {
            result = (result * a) % RandNum;
        }
        a = (a * a) % RandNum;
        q /= 2;
    }
    return result;
}

// Разложение n-1 на простые множители для теста Миллера
int MillerRazlozh(int m, int RandNum1, const vector<int>& PrimeNums, 
                 vector<int>& MnozUnikPrime, vector<int>& PrimeMn) {
    for (size_t i = 0; i < PrimeNums.size(); i++) {
        int degree = 0;
        if (RandNum1 % PrimeNums[i] == 0) {
            while (RandNum1 % PrimeNums[i] == 0) {
                RandNum1 /= PrimeNums[i];
                degree += 1;
                PrimeMn.push_back(PrimeNums[i]);
            }
            MnozUnikPrime.push_back(PrimeNums[i]);
            m *= pow(PrimeNums[i], degree);
        }
    }
    return m/2;
}

// Тест Миллера-Рабина на простоту с подробным выводом
bool Miller(int RandNum, const vector<int>& MnozUnikPrime, int t, bool verbose = false) {
    if (RandNum == 2) {
        if (verbose) cout << "  Miller: 2 - простое число" << endl;
        return true;
    }
    if (RandNum < 2 || RandNum % 2 == 0) {
        if (verbose) cout << "  Miller: число составное (меньше 2 или четное)" << endl;
        return false;
    }
    
    if (verbose) {
        cout << "  Miller: проверка числа " << RandNum << endl;
        cout << "  Уникальные делители n-1: ";
        for (size_t i = 0; i < MnozUnikPrime.size(); i++) {
            cout << MnozUnikPrime[i] << " ";
        }
        cout << endl;
    }
    
    for (int j = 0; j < t; j++) {
        int a = getRandomNumber(2, RandNum - 1);
        if (verbose) cout << "  Итерация " << j+1 << ": a = " << a << endl;
        
        if (modPow(a, RandNum - 1, RandNum) == 1) {
            if (verbose) cout << "    a^(n-1) ≡ 1 (mod n) - выполняется" << endl;
            
            bool allConditions = true;
            for (size_t i = 0; i < MnozUnikPrime.size(); i++) {
                int result = modPow(a, (RandNum - 1) / MnozUnikPrime[i], RandNum);
                if (verbose) cout << "    a^((n-1)/" << MnozUnikPrime[i] << ") mod n = " << result;
                
                if (result == 1) {
                    if (verbose) cout << " = 1 - условие нарушено" << endl;
                    allConditions = false;
                    break;
                } else {
                    if (verbose) cout << " ≠ 1 - условие выполняется" << endl;
                }
            }
            
            if (allConditions) {
                if (verbose) cout << "  Miller: число вероятно простое" << endl;
                return true;
            }
        } else {
            if (verbose) cout << "    a^(n-1) mod n ≠ 1 - условие Ферма не выполняется" << endl;
        }
    }
    
    if (verbose) cout << "  Miller: число составное" << endl;
    return false;
}

// Алгоритм Евклида для НОД
int NOD(int a, int b) {
    if (b == 0) return a;
    return NOD(b, a % b);
}

// Разложение для теста Поклингтона
void PoklingtonRazlozh(int RandNum, int& F, int& R, const vector<int>& PrimeMn) {
    for (size_t i = PrimeMn.size() - 1; i + 1 > 0; i--) {
        if (F <= sqrt(RandNum) - 1) {
            F *= PrimeMn[i];
        } else {
            R *= PrimeMn[i];
        }
    }
}

// Тест Поклингтона на простоту с подробным выводом
bool Poklington(int RandNum, const vector<int>& MnozUnikPrime, int t, bool verbose = false) {
    if (RandNum == 2 || RandNum == 5) {
        if (verbose) cout << "  Poklington: 2 или 5 - простое число" << endl;
        return true;
    }
    if (RandNum < 2 || RandNum % 2 == 0) {
        if (verbose) cout << "  Poklington: число составное (меньше 2 или четное)" << endl;
        return false;
    }
    
    if (verbose) {
        cout << "  Poklington: проверка числа " << RandNum << endl;
        cout << "  Уникальные делители: ";
        for (size_t i = 0; i < MnozUnikPrime.size(); i++) {
            cout << MnozUnikPrime[i] << " ";
        }
        cout << endl;
    }
    
    for (int j = 0; j < t; j++) {
        int a = getRandomNumber(2, RandNum - 1);
        if (verbose) cout << "  Итерация " << j+1 << ": a = " << a << endl;
        
        // Проверка условия Ферма
        int fermaResult = modPow(a, RandNum - 1, RandNum);
        if (verbose) cout << "    a^(n-1) mod n = " << fermaResult;
        
        if (fermaResult != 1) {
            if (verbose) cout << " ≠ 1 - условие Ферма не выполняется" << endl;
            continue;
        } else {
            if (verbose) cout << " = 1 - условие Ферма выполняется" << endl;
        }
        
        // Проверка дополнительных условий
        bool allConditions = true;
        for (size_t i = 0; i < MnozUnikPrime.size(); i++) {
            int result = modPow(a, (RandNum - 1) / MnozUnikPrime[i], RandNum);
            if (verbose) cout << "    a^((n-1)/" << MnozUnikPrime[i] << ") mod n = " << result;
            
            if (result == 1) {
                if (verbose) cout << " = 1 - условие нарушено" << endl;
                allConditions = false;
                break;
            } else {
                if (verbose) cout << " ≠ 1 - условие выполняется" << endl;
            }
        }
        
        if (allConditions) {
            if (verbose) cout << "  Poklington: число вероятно простое" << endl;
            return true;
        }
    }
    
    if (verbose) cout << "  Poklington: число составное" << endl;
    return false;
}

// Функция Эйлера φ(n)
int Eiler(int p) {
    int result = p;
    for (int i = 2; i * i <= p; i++) {
        if (p % i == 0) {
            while (p % i == 0) {
                p /= i;
            }
            result -= result / i;
        }
    }
    if (p > 1) {
        result -= result / p;
    }
    return result;
}

// Вычисление вероятности ошибки
bool VerTest(int RandNum, int t, int R, int F) {
    if (NOD(R, F) == 1) {
        double verMiller = (static_cast<double>(Eiler(RandNum - 1)) / static_cast<double>(RandNum - 1)) * t;
        double verPoklington = (static_cast<double>(Eiler(RandNum)) / static_cast<double>(RandNum)) * t;
        double result = 1 - verMiller - verPoklington;
        return (result <= 0.1);
    } else {
        double verMiller = (static_cast<double>(Eiler(RandNum - 1)) / static_cast<double>(RandNum - 1)) * t;
        double result = 1 - verMiller;
        return (result <= 0.1);
    }
}

// Вывод результатов
void InPut(int RandNum, bool millerResult, bool poklingtonResult, bool verTestResult, int k) {
    cout << RandNum << " \t\t";
    
    // Вывод результатов тестов отдельно
    cout << (millerResult ? "+" : "-") << "/";
    cout << (poklingtonResult ? "+" : "-") << " \t\t";
    
    // Вывод результата проверки вероятности
    cout << (verTestResult ? "+" : "-") << " \t\t";
    
    cout << k << endl;
}

// Функция для ввода целого числа с проверкой
int inputInteger(const string& prompt, int minValue, int maxValue) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value < minValue || value > maxValue) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Ошибка! Введите число от " << minValue << " до " << maxValue << ": ";
        } else {
            cin.ignore(1000, '\n');
            return value;
        }
    }
}

int main() {
    system("chcp 65001");
    srand(time(0));
    
    cout << "=== ПРОВЕРКА ПРОСТОТЫ ЧИСЕЛ ===\n" << endl;
    
    // Ввод параметров
    int bitness = inputInteger("Введите битность чисел (от 2 до 16): ", 2, 16);
    int minValue = pow(2, bitness - 1);
    int maxValue = pow(2, bitness) - 1;
    
    cout << "\nДиапазон чисел для битности " << bitness << ": ";
    cout << minValue << " - " << maxValue << endl;
    
    int t = inputInteger("\nВведите количество итераций тестов (t, от 1 до 20): ", 1, 20);
    int numbersCount = inputInteger("Введите количество чисел для проверки (от 1 до 100): ", 1, 100);
    
    // Запрашиваем режим вывода
    char verboseMode;
    cout << "\nВывести подробную информацию по тестам? (y/n): ";
    cin >> verboseMode;
    bool verbose = (verboseMode == 'y' || verboseMode == 'Y');
    
    // Генерация простых чисел
    vector<int> PrimeNums;
    Eratosthenes(PrimeNums, maxValue);
    
    int k = 0;  // счетчик отвергнутых чисел
    
    cout << "\n================================================================" << endl;
    cout << "Число\tТесты (Миллер/Поклингтон)\tВероятность\tОтвергнуто" << endl;
    cout << "----------------------------------------------------------------" << endl;
    
    // Основной цикл проверки чисел
    for (int i = 0; i < numbersCount; i++) {
        vector<int> MnozUnikPrime;
        vector<int> PrimeMn;
        
        int RandNum = getRandomNumber(minValue, maxValue);
        
        if (verbose) {
            cout << "\n=== Проверка числа " << RandNum << " ===" << endl;
        }
        
        int RandNum1 = RandNum - 1;
        int m = 1;
        m = MillerRazlozh(m, RandNum1, PrimeNums, MnozUnikPrime, PrimeMn);
        
        int F = 1;
        int R = 1;
        PoklingtonRazlozh(RandNum, F, R, PrimeMn);
        
        // Выполняем тесты с выводом
        bool millerResult = Miller(RandNum, MnozUnikPrime, t, verbose);
        bool poklingtonResult = Poklington(RandNum, MnozUnikPrime, t, verbose);
        
        // Если verbose режим, добавляем разделитель
        if (verbose) {
            cout << "----------------------------------------" << endl;
        }
        
        // Проверяем оба теста
        if (!millerResult || !poklingtonResult) {
            k++;
            i--;
            
            if (verbose) {
                cout << "Число " << RandNum << " отвергнуто" << endl;
                if (!millerResult) cout << "  Причина: тест Миллера не пройден" << endl;
                if (!poklingtonResult) cout << "  Причина: тест Поклингтона не пройден" << endl;
                cout << "================================================" << endl;
            }
            continue;
        }
        
        // Проверка вероятности
        bool verTestResult = VerTest(RandNum, t, R, F);
        
        // Вывод результатов в таблицу
        InPut(RandNum, millerResult, poklingtonResult, verTestResult, k);
        
        // Сброс счетчика
        if (millerResult && poklingtonResult) {
            k = 0;
        }
        
        if (verbose) {
            cout << "Вероятность ошибки: " << (verTestResult ? "≤ 10%" : "> 10%") << endl;
            cout << "================================================" << endl;
        }
    }
    
    // Вывод статистики
    cout << "\n================================================================" << endl;
    cout << "СТАТИСТИКА:" << endl;
    cout << "Битность чисел: " << bitness << " бит" << endl;
    cout << "Диапазон: " << minValue << " - " << maxValue << endl;
    cout << "Количество итераций тестов: " << t << endl;
    cout << "Количество проверенных чисел: " << numbersCount << endl;
    cout << "================================================================" << endl;
    
    // Легенда
    cout << "\nЛЕГЕНДА:" << endl;
    cout << "Тесты (Миллер/Поклингтон): + - пройден, - - не пройден" << endl;
    cout << "Вероятность: + - вероятность ошибки ≤ 10%, - - вероятность > 10%" << endl;
    
    return 0;
}
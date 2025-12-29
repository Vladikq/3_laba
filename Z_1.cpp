#include <iostream>   
#include <cmath>      
#include <vector>     
#include <iomanip>    

using namespace std;  

// Функция для интервала (6, 10] - полуокружность
vector<pair<float, float>> func4(float& x, float& dx) {
    vector<pair<float, float>> coords;  // Вектор для хранения координат
    
    while (x <= 10) {  // Пока x не превысит 10
        int a = 8, b = -2, r = 2;  // Параметры окружности
        // Формула: y = √(r² - x² + 2ax - a²) + b
        float y = sqrt(pow(r, 2) - pow(x, 2) + (2 * a * x) - pow(a, 2)) + b;
        
        coords.push_back(make_pair(x, y));  // Сохраняем точку (x, y)
        x += dx;  // Увеличиваем x на шаг
    }
    
    return coords;  // Возвращаем все точки интервала
}

// Функция для интервала (4, 6] - константа
vector<pair<float, float>> func3(float& x, float& dx) {
    vector<pair<float, float>> coords;
    
    while (x <= 6) {  // Пока x не превысит 6
        coords.push_back(make_pair(x, -2));  // y всегда = -2
        x += dx;  // Увеличиваем x на шаг
    }
    
    return coords;
}

// Функция для интервала (-2, 4] - линейная
vector<pair<float, float>> func2(float& x, float& dx) {
    vector<pair<float, float>> coords;
    
    while (x <= 4) {  // Пока x не превысит 4
        float y = x * (-0.5);  // y = -0.5x
        coords.push_back(make_pair(x, y));  // Сохраняем точку
        x += dx;  // Увеличиваем x на шаг
    }
    
    return coords;
}

// Функция для интервала (-4, -2] - линейная
vector<pair<float, float>> func1(float& x, float& dx) {
    vector<pair<float, float>> coords;
    
    while (x <= -2) {  // Пока x не превысит -2
        float y = x + 3;  // y = x + 3
        coords.push_back(make_pair(x, y));  // Сохраняем точку
        x += dx;  // Увеличиваем x на шаг
    }
    
    return coords;
}

int main() {
    system("chcp 65001 > nul");  // Устанавливаем кодировку UTF-8
    
    float x = -4;   // Начальное значение x
    float dx = 0.5; // Шаг изменения x
    
    // Вычисляем точки для всех интервалов
    auto coords1 = func1(x, dx);  // Интервал (-4, -2]
    x = -1.5;  // Начало следующего интервала
    auto coords2 = func2(x, dx);  // Интервал (-2, 4]
    x = 4.5;   // Начало следующего интервала
    auto coords3 = func3(x, dx);  // Интервал (4, 6]
    x = 6.5;   // Начало следующего интервала
    auto coords4 = func4(x, dx);  // Интервал (6, 10]
    
    // Выводим заголовок
    cout << "ВЫЧИСЛЕНИЕ КУСОЧНО-ЗАДАННОЙ ФУНКЦИИ" << endl;
    cout << "==========================================" << endl;
    cout << "Параметры: шаг dx = " << dx << endl << endl;
    
    // Вывод точек для первого интервала
    cout << "ИНТЕРВАЛ (-4, -2]: y = x + 3" << endl;
    cout << "----------------------------------------" << endl;
    for (size_t i = 0; i < coords1.size(); i++) {
        cout << "Точка " << i+1 << ": x = " << setw(5) << fixed << setprecision(2) 
             << coords1[i].first 
             << ", y = " << setw(8) << fixed << setprecision(3) 
             << coords1[i].second 
             << "  →  (" << coords1[i].first << ", " 
             << fixed << setprecision(3) << coords1[i].second << ")" << endl;
    }
    cout << endl;
    
    // Вывод точек для второго интервала
    cout << "ИНТЕРВАЛ (-2, 4]: y = -0.5x" << endl;
    cout << "----------------------------------------" << endl;
    for (size_t i = 0; i < coords2.size(); i++) {
        cout << "Точка " << i+1 << ": x = " << setw(5) << fixed << setprecision(2) 
             << coords2[i].first 
             << ", y = " << setw(8) << fixed << setprecision(3) 
             << coords2[i].second 
             << "  →  (" << coords2[i].first << ", " 
             << fixed << setprecision(3) << coords2[i].second << ")" << endl;
    }
    cout << endl;
    
    // Вывод точек для третьего интервала
    cout << "ИНТЕРВАЛ (4, 6]: y = -2" << endl;
    cout << "----------------------------------------" << endl;
    for (size_t i = 0; i < coords3.size(); i++) {
        cout << "Точка " << i+1 << ": x = " << setw(5) << fixed << setprecision(2) 
             << coords3[i].first 
             << ", y = " << setw(8) << fixed << setprecision(3) 
             << coords3[i].second 
             << "  →  (" << coords3[i].first << ", " 
             << fixed << setprecision(3) << coords3[i].second << ")" << endl;
    }
    cout << endl;
    
    // Вывод точек для четвертого интервала
    cout << "ИНТЕРВАЛ (6, 10]: y = √(4 - x² + 16x - 64) - 2" << endl;
    cout << "(верхняя полуокружность с центром (8, -2), радиус = 2)" << endl;
    cout << "-------------------------------------------------------------" << endl;
    for (size_t i = 0; i < coords4.size(); i++) {
        cout << "Точка " << i+1 << ": x = " << setw(5) << fixed << setprecision(2) 
             << coords4[i].first 
             << ", y = " << setw(8) << fixed << setprecision(3) 
             << coords4[i].second 
             << "  →  (" << coords4[i].first << ", " 
             << fixed << setprecision(3) << coords4[i].second << ")" << endl;
    }
    cout << endl;
    
    return 0;  
}
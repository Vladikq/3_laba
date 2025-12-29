#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<long long> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    // Префиксные суммы для быстрого вычисления суммы на отрезке
    vector<long long> prefix_sum(n + 1, 0);
    for (int i = 0; i < n; i++) {
        prefix_sum[i + 1] = prefix_sum[i] + arr[i];
    }
    
    // которую можно получить начиная с позиции i (0-based), когда ходит текущий игрок
    vector<long long> dp(n + 1, 0);
    
    // Базовый случай: если чисел не осталось, разница очков 0
    dp[n] = 0;
    
    // Заполняем dp с конца
    for (int i = n - 1; i >= 0; i--) {
        long long max_diff = LLONG_MIN;
        
        // Текущий игрок может взять от 1 до m чисел
        for (int k = 1; k <= m && i + k <= n; k++) {
            // Сумма чисел, которые берет текущий игрок
            long long current_sum = prefix_sum[i + k] - prefix_sum[i];
            
            // После хода текущего игрока очередь переходит к другому
            // Разница очков = текущая сумма - лучший результат противника
            long long diff = current_sum - dp[i + k];
            
            max_diff = max(max_diff, diff);
        }
        
        dp[i] = max_diff;
    }
    
    // Если разница очков > 0, Павел выигрывает
    cout << (dp[0] > 0 ? 1 : 0) << endl;
    
    return 0;
}
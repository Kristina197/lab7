#include <iostream>
#include <vector>
#include <climits>
#include <unordered_map>
#include <sstream>

using namespace std;

int minCoinsRecursive(int sum, const vector<int>& coins, unordered_map<int, int>& memo) {
    if (sum == 0) return 0;
    
    if (memo.find(sum) != memo.end()) {
        return memo[sum];
    }
    
    int minCount = INT_MAX;
    
    for (int coin : coins) {
        if (coin <= sum) {
            int subResult = minCoinsRecursive(sum - coin, coins, memo);
            
            if (subResult != INT_MAX && subResult + 1 < minCount) {
                minCount = subResult + 1;
            }
        }
    }
    
    memo[sum] = minCount;
    return minCount;
}

int minCoins(int sum, const vector<int>& coins) {
    unordered_map<int, int> memo;
    int result = minCoinsRecursive(sum, coins, memo);
    return result == INT_MAX ? -1 : result;
}

int main() {
    int sum;
    cout << "Введите сумму для размена: ";
    cin >> sum;
    cin.ignore(); // Очищаем буфер после ввода числа

    vector<int> coins;
    string line;
    
    cout << "Введите номиналы монет через пробел: ";
    getline(cin, line);
    
    istringstream iss(line);
    int coin;
    while (iss >> coin) {
        coins.push_back(coin);
    }
    
    // Вычисление и вывод результата
    int result = minCoins(sum, coins);
    if (result == -1) {
        cout << "Невозможно разменять данную сумму указанными монетами." << endl;
    } else {
        cout << "Минимальное количество монет: " << result << endl;
    }
    
    return 0;
}
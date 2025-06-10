#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Рекурсивная функция для проверки возможности размещения
bool canArrange(const vector<int>& items, int ropeLength, int currentSum, int startIndex, int usedItems) {
    // Базовый случай: если текущая сумма равна длине веревки
    if (currentSum == ropeLength) {
        return true;
    }
    
    // Перебираем предметы, начиная с startIndex
    for (int i = startIndex; i < items.size(); ++i) {
        // Пропускаем уже использованные предметы
        if ((usedItems & (1 << i)) != 0) continue;
        
        // Пробуем добавить текущий предмет
        int newSum = currentSum + items[i];
        
        // Если превысили длину веревки - пропускаем
        if (newSum > ropeLength) continue;
        
        // Рекурсивно проверяем дальше
        if (canArrange(items, ropeLength, newSum, i + 1, usedItems | (1 << i))) {
            return true;
        }
    }
    
    return false;
}

// Основная функция для проверки возможности перераспределения
bool canRedistribute(int ropeLength, const vector<int>& items, int removedIndex) {
    // Создаем копию списка предметов без удаленного
    vector<int> remainingItems;
    for (int i = 0; i < items.size(); ++i) {
        if (i != removedIndex) {
            remainingItems.push_back(items[i]);
        }
    }
    
    // Сумма размеров оставшихся предметов должна равняться длине веревки
    int total = 0;
    for (int item : remainingItems) {
        total += item;
    }
    if (total != ropeLength) {
        return false;
    }
    
    // Пытаемся найти комбинацию предметов, которая точно покрывает веревку
    return canArrange(remainingItems, ropeLength, 0, 0, 0);
}

int main() {
    // Пример входных данных
    int ropeLength = 10;
    vector<int> items = {2, 3, 5, 4}; // Предметы (один будет удален)
    int removedIndex = 3; // Индекс удаленного предмета (5)
    
    if (canRedistribute(ropeLength, items, removedIndex)) {
        cout << "Можно перераспределить оставшиеся предметы" << endl;
    } else {
        cout << "Нельзя перераспределить оставшиеся предметы" << endl;
    }
    
    return 0;
}
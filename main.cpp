// ---------------------------------------------------------------------------------------------------------------------
// First in, first out
// ---------------------------------------------------------------------------------------------------------------------

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <numeric>
#include <random>
#include <stack>

using namespace std;

template <typename It>
void PrintRange(It range_begin, It range_end) {
    for (auto it = range_begin; it != range_end; ++it) {
        cout << *it << " "s;
    }
    cout << endl;
}

template <typename Type>
class Queue {
public:
    void Push(const Type& element) {
        if(stack1_.empty()) {
            stack1_.emplace(element);
        } else {
            for(int i = stack1_.size(); i != 0; --i ) {
                stack2_.emplace(stack1_.top());
                stack1_.pop();
            }
            stack1_.push(element);
            for(int i = stack2_.size(); i != 0; --i ) {
                stack1_.emplace(stack2_.top());
                stack2_.pop();
            }
        }
    }
    void Pop() {
        stack1_.pop();
    }
    Type& Front() {
        return stack1_.top();
    }
    uint64_t Size() const {
        return stack1_.size();
    }
    bool IsEmpty() const {
        return stack1_.empty();
    }

private:
    stack<Type> stack1_;
    stack<Type> stack2_;
};

int main() {
    Queue<int> queue;
    vector<int> values(5);
    // заполняем вектор для тестирования очереди
    iota(values.begin(), values.end(), 1);
    // перемешиваем значения
    random_device rd;
    mt19937 g(rd());
    shuffle(values.begin(), values.end(), g);
    PrintRange(values.begin(), values.end());
    cout << "Заполняем очередь"s << endl;
    // заполняем очередь и выводим элемент в начале очереди
    for (int i = 0; i < 5; ++i) {
        queue.Push(values[i]);
        cout << "Вставленный элемент "s << values[i] << endl;
        cout << "Первый элемент очереди "s << queue.Front() << endl;
    }
    cout << "Вынимаем элементы из очереди"s << endl;
    // выводим элемент в начале очереди и вытаскиваем элементы по одному
    while (!queue.IsEmpty()) {
        // сначала будем проверять начальный элемент, а потом вытаскивать,
        // так как операция Front на пустой очереди не определена
        cout << "Будем вынимать элемент "s << queue.Front() << endl;
        queue.Pop();
    }
    return 0;
}
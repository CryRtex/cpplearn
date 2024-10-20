#include "Core.h"
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

// Bir QUEUE yarat içinde bizden aldığın sayıları sırala
namespace Core {
    using namespace std;

    void addingQueue(queue<int>& q) { 
        int queueValue;
        cout << "Queue için değer yazınız: " << endl;
        cin >> queueValue;
        cin.ignore();
        q.push(queueValue); 
    }
    void sortQueue(queue<int>& q) {
        vector<int> temp;  
        while (!q.empty()) {
            temp.push_back(q.front());  
            q.pop();
        }
        sort(temp.begin(), temp.end());

        
        for (int value : temp) {
            q.push(value);
        }
    }

    void queueListener(queue<int>& q) {
        while (!q.empty()) {
            int value = q.front();
            q.pop();
            cout << "Queue element: " << value << endl;
        }
    }
}

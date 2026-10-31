#include <iostream>
#include<unordered_map>
#include<list>
#include<windows.h>

using namespace std;

class LRU_Cache {
    public:
    class Node{
        public:
        int key,val;
        Node* prev;
        Node* next;
        Node(int k, int value){
            key = k;
            val = value;
        }
    };
    Node* head = new Node(-1,-1);
    Node* tail = new Node(-1,-1);
    int limit;
    int hit = 0,miss = 0,eviction = 0;

    unordered_map<int, Node*> m;

    void addNode(Node* newNode){
        Node* oldNode = head->next;
        head->next = newNode;
        oldNode->prev = newNode;
        newNode->prev = head;
        newNode->next = oldNode;
    }

    void deleteNode(Node* oldNode){
        Node* oldPrev = oldNode->prev;
        Node* oldNext = oldNode->next;
        oldPrev->next = oldNext;
        oldNext->prev = oldPrev;
    }

    LRU_Cache(int capacity){
        limit = capacity;
        tail->prev = head;
        head->next = tail;
    }
    void put(int key, int value){
        //if the key exists already, we delete the key-value pair and add new with updated value
        if(m.find(key) != m.end()){
            Node* oldNode = m[key];
            m.erase(key);
            deleteNode(oldNode);
        }
        //Now if we hit the size limit, we need to remove the Least Recently Used data and add the new data
        if(m.size() == limit){
            m.erase(tail->prev->key);
            deleteNode(tail->prev);
            eviction++;
        }
        Node* newNode = new Node(key,value);
        m[key] = newNode;
        addNode(newNode);
    }
    int get(int key){
        // in get function, we dont need to check the limit but when we use this function we need to push the key-value pair to front ie make it Most Recently Used data
        //So we delete the key-value pair node and add the same node after head node
        if(m.find(key) == m.end()){
            miss++;
            return -1;
        }
        Node* ansNode = m[key];
        int ans = ansNode->val;
        m.erase(key);
        deleteNode(ansNode);
        addNode(ansNode);
        m[key] = ansNode;
        hit++;
        return ans;
    }

    void display(){
        //Size status bar
        cout << "==========================" << endl;
        cout << "LRU Cache";
        for(int i=0;i<m.size();i++){
            cout << "■";
        }
        for(int i=m.size();i<limit;i++){
            cout << "□";
        }
        cout << m.size() << "/" << limit << endl;
        cout << "==========================" << endl;


        //Hit rate stats
        float hitrate;
        if(hit != 0 && miss != 0){
                hitrate = (hit*100)/(hit+miss);
        }
        else{
            hitrate = 0;
        }
        cout << "==========================" << endl;
        //Hit is the when the key is found in the map. Miss is when key is not found. Eviction is the number of times the cache is full and we need to remove LRU data
        cout << "Hit Rate Stats: " << "Hit: " <<hit << "|" << "Miss: " << miss << "|" << "Hit Rate: " << hitrate << "|" << "Eviction: " << eviction << "|" << endl;
        cout << "==========================" << endl;


        //Actual data display
        Node* curr = head->next;
        while(curr != tail){
            cout << "|" << curr->key << "|" << curr->val <<"|";
            if(curr->next != tail){
                cout << "->";
            }
            curr = curr->next;
        }
        if(!m.empty()){
            cout << "<- [LRU]" << endl;
        }
        cout << "==========================" << endl;
    }

};

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    int option; // to take the input for selecting between get and put. 1 for put, 2 for get, 3 for exit
    int limit;
    int key, value;
    cout << "Enter the size of LRU Cache :" << endl;
    cin >> limit;
    LRU_Cache cache(limit);
    if(limit <= 0){
        cout << "Invalid size of LRU Cache!" << endl;
    }
    else{

        while(true){
            cache.display();
            cout << "Enter the operation you want to perform" << endl;
            cout << "Enter 1 to insert data\nEnter 2 to get data\nEnter 3 to exit" << endl;
            cin >> option;
            if(option == 1){
                cout << "Enter the key and value: " << endl;
                cin >> key >> value;
                cache.put(key,value);

            }
            else if(option == 2){
                cout << "Enter the key to fetch data: " << endl;
                cin >> key;
                int result = cache.get(key);
                if(result == -1){
                    cout << "Key not found" << endl;
                }
                cout << "|" << key << "|" << result << "|" << endl;
            }
            else if(option == 3){
                break;
            }
            else{
                cout << "Enter a valid option" << endl;
                continue;
            }
        }
    }
}

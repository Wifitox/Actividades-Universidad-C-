#include <iostream>

using namespace std;

struct Node {
    int value;
    Node* next;

    Node(int value) {
        this->value = value;
        next = nullptr;
    }
};

class Stack {
    Node* top;
    int height;

    public:
        Stack(int value){
            Node* newNode = new Node(value);
            top = newNode;
            height = 1;
        }

        void printStack(){
            Node* temp = top;
            while(temp){
                cout << temp->value << endl;
                temp = temp->next;
            }
        }

        void getTop() {
            cout << "Top item: " << top->value << endl;
        }

        void getHeight(){
            cout << "Height: " << height << endl;
        }

        void push(int value){
            Node* newNode = new Node(value);
            if(height == 0) { // En realidad ambos casos son iguales, pero es para que se vea más claro
                top = newNode;
            } else {
            newNode -> next = top;
            top = newNode;
            height++;
            }
        }

        int pop() {
            if(height == 0) return INT_MIN;
            
            Node* temp = top;
            int poppedValue = top->value;
            top = top->next;
            delete temp;
            height--;

            return poppedValue;
            
        }
        
};

int main(){
    Stack* myStack = new Stack(4);


    return 0;
}

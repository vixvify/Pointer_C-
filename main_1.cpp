#include <iostream>
#include <string>
using namespace std;

struct Node {
    string name;
    int score;
    Node *next;
    Node *prev;
};

Node* createNode(string name,int score){
    Node *s = new Node;
    s -> name = name;
    s -> score = score;
    s -> next = NULL;
    s->prev = NULL;
    return s;
}

void addNode(string name,int score,Node** head){
    Node *newNode = createNode(name,score);
    if(*head == NULL){
        *head = newNode;
        cout << newNode->name << endl;
        cout << newNode->score << endl;
        return;
    }
    Node *temp = *head;
    while(temp->next != NULL){
        temp = temp -> next;
    }
    temp -> next = newNode;
    newNode->prev = temp;
    cout << newNode->name << endl;
    cout << newNode->score << endl;
}


int main() {
    Node* head = NULL;
    addNode("aaa",25,&head);
    addNode("bbb",35,&head);
    addNode("ccc",24,&head);
    return 0;
}
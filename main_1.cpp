#include <iostream>
#include <string>
using namespace std;

struct Node {
    string name;
    int score;
    Node* next;
    Node* prev;
};

Node* createNode(const string& name, int score) {
    Node* node = new Node;
    node->name = name;
    node->score = score;
    node->next = nullptr;
    node->prev = nullptr;
    return node;
}

void checkLowScores(Node** head,int k) {

    if (*head == nullptr) return;

    Node* current = *head;
    int count = 1;

    while (current->next != nullptr && count < k) {
        current = current->next;
        count++;
    }

    if (current->next != nullptr) {
        Node* cut = current->next;
        current->next = nullptr;
        cut->prev = nullptr;
    }
}

void addNode(const string& name, int score, Node** head, int k) {

    Node* newNode = createNode(name, score);

    if (*head == nullptr) {
        *head = newNode;
        return;
    }

    Node* current = *head;

    if (score > current->score) {
        newNode->next = current;
        current->prev = newNode;
        *head = newNode;
        checkLowScores(head,k);
        return;
    }

    while (current->next != nullptr && current->next->score > score) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
    newNode->prev = current;

    checkLowScores(head,k);
}

void printList(Node* head) {

    Node* current = head;

    while (current != nullptr) {
        cout << current->name << " " << current->score << "\n";
        current = current->next;
    }
}

int main() {

    Node* head = nullptr;

    addNode("aaa",25,&head,3);
    addNode("bbb",35,&head,3);
    addNode("ccc",24,&head,3);
    addNode("ccc",44,&head,3);
    addNode("ccc",12,&head,3);
    addNode("ccc",5,&head,3);
    addNode("ccc",50,&head,3);

    printList(head);

    return 0;
}
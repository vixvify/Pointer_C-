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

void checkLowScores(Node** head) {

    if (*head == nullptr) return;

    Node* current = *head;
    int count = 1;

    while (current->next != nullptr && count < 3) {
        current = current->next;
        count++;
    }

    if (current->next != nullptr) {
        Node* cut = current->next;
        current->next = nullptr;
        cut->prev = nullptr;
    }
}

void addNode(const string& name, int score, Node** head) {

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
        checkLowScores(head);
        return;
    }

    while (current->next != nullptr && current->next->score > score) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
    newNode->prev = current;

    checkLowScores(head);
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

    addNode("aaa",25,&head);
    addNode("bbb",35,&head);
    addNode("ccc",24,&head);
    addNode("ccc",44,&head);
    addNode("ccc",12,&head);
    addNode("ccc",5,&head);
    addNode("ccc",50,&head);

    printList(head);

    return 0;
}
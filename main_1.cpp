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

void checkLowScores(Node** head) {
    if (*head == NULL) return;
    Node* temp = *head;
    int count = 1;
    while(temp -> next != NULL && count < 3) {
        temp = temp -> next;
        count++;
    }
    if (temp->next != NULL) {
        Node* cut = temp->next;
        temp->next = NULL;
        cut->prev = NULL;
    }
}

void addNode(string name,int score,Node** head){
    Node *newNode = createNode(name,score);
    if(*head == NULL){
        *head = newNode;
        return;
    }
    Node *temp = *head;
    if (score > temp->next->score) {
        newNode->next = temp;
        temp->prev = newNode;
        *head = newNode;
        return;
    }
    while(temp->next != NULL && temp->score > score){
        temp = temp -> next;
    }
    newNode->next = temp->next;
    temp -> next = newNode;
    newNode->prev = temp;

    checkLowScores(head);
}

void printNode(Node* head) {
    Node *temp = head;
    while(temp != NULL) {
        cout << temp -> name << " " << temp -> score << "\n";
        temp = temp -> next;
    }
}


int main() {
    Node* head = NULL;
    addNode("aaa",25,&head);
    addNode("bbb",35,&head);
    addNode("ccc",24,&head);
    addNode("ccc",44,&head);
    addNode("ccc",12,&head);
    addNode("ccc",5,&head);
    addNode("ccc",50,&head);

    printNode(head);
    return 0;
}
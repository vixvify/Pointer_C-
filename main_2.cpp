#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int coef;
    int exp;
    Node* next;
    Node* prev;
};

Node* createNode(int coef, int exp) {
    Node* node = new Node;
    node->coef = coef;
    node->exp = exp;
    node->next = nullptr;
    node->prev = nullptr;
    return node;
}

void addNode(int coef, int exp, Node** head, Node** tail) {

    Node* newNode = createNode(coef, exp);

    if (*head == nullptr) {
        *head = newNode;
        *tail = newNode;
        return;
    }

    (*tail)->next = newNode;
    newNode->prev = *tail;
    *tail = newNode;
}

Node* addPolynomial(Node** head1, Node** head2) {

    Node* p1 = *head1;
    Node* p2 = *head2;

    Node* headResult = nullptr;
    Node* tailResult = nullptr;

    while (p1 != nullptr && p2 != nullptr) {

        if (p1->exp == p2->exp) {

            int coef = p1->coef + p2->coef;

            if (coef != 0)
                addNode(coef, p1->exp, &headResult, &tailResult);

            p1 = p1->next;
            p2 = p2->next;
        }

        else if (p1->exp > p2->exp) {

            addNode(p1->coef, p1->exp, &headResult, &tailResult);
            p1 = p1->next;
        }

        else {

            addNode(p2->coef, p2->exp, &headResult, &tailResult);
            p2 = p2->next;
        }
    }

    while (p1 != nullptr) {
        addNode(p1->coef, p1->exp, &headResult, &tailResult);
        p1 = p1->next;
    }

    while (p2 != nullptr) {
        addNode(p2->coef, p2->exp, &headResult, &tailResult);
        p2 = p2->next;
    }

    return headResult;
}

Node* multiplyPolynomial(Node** head1, Node** head2) {

    Node* p1 = *head1;

    Node* headResult = nullptr;
    Node* tailResult = nullptr;

    vector<int> coef(100, 0);

    while (p1 != nullptr) {

        Node* p2 = *head2;

        while (p2 != nullptr) {

            int exp = p1->exp + p2->exp;
            coef[exp] += p1->coef * p2->coef;

            p2 = p2->next;
        }

        p1 = p1->next;
    }

    for (int i = coef.size() - 1; i >= 0; i--) {

        if (coef[i] != 0)
            addNode(coef[i], i, &headResult, &tailResult);
    }

    return headResult;
}

void printPolynomial(Node* head) {

    Node* temp = head;

    while (temp != nullptr) {
        cout << temp->coef << "x^" << temp->exp << " ";
        temp = temp->next;
    }

    cout << endl;
}

int main() {

    Node* head1 = nullptr;
    Node* tail1 = nullptr;

    Node* head2 = nullptr;
    Node* tail2 = nullptr;

    addNode(2,5,&head1,&tail1);
    addNode(4,3,&head1,&tail1);
    addNode(3,2,&head1,&tail1);
    addNode(5,0,&head1,&tail1);

    addNode(3,5,&head2,&tail2);
    addNode(5,3,&head2,&tail2);
    addNode(4,2,&head2,&tail2);
    addNode(6,0,&head2,&tail2);

    Node* result = multiplyPolynomial(&head1,&head2);

    printPolynomial(result);

    return 0;
}
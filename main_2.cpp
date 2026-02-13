#include <iostream>
using namespace std;

struct Node {
    int coef;
    int exp;
    Node *next;
    Node *prev;
};

Node* createNode(int coef, int exp) {
    Node *s = new Node;
    s -> coef = coef;
    s -> exp = exp;
    s -> next = NULL;
    s->prev = NULL;
    return s;
}

void addNode(int coef, int exp,Node** head){
    Node *newNode = createNode(coef,exp);
    if(*head == NULL){
        *head = newNode;
        return;
    }
    Node *temp = *head;
    while(temp->next != NULL){
        temp = temp -> next;
    }
    temp -> next = newNode;
    newNode->prev = temp;
}

Node* checkexp(Node* headresult) {
    Node *newresult = NULL;
    Node *temp = headresult;
    while (temp != NULL)
    {
        Node *cur = newresult;

        while (cur != NULL){
            if (cur->exp == temp->exp){
                cur->coef += temp->coef;
                break;
            }
            cur = cur->next;
        }

        if (cur == NULL){
            addNode(temp->coef, temp->exp, &newresult);
        }

        temp = temp->next;
    }
    return newresult;
}

Node* addpolynomial(Node** head1,Node** head2) {
    Node *temp1 = *head1;
    Node *temp2 = *head2;
    Node *headresult = NULL;

    while(temp1 != NULL && temp2 != NULL) {
        if(temp1 -> exp == temp2 -> exp) {
            int coef = temp1->coef + temp2->coef;
            if(coef != 0) {
                addNode(coef, temp1->exp, &headresult);
            }
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        else if(temp1 -> exp > temp2 -> exp) {
            addNode(temp1 -> coef,temp1 -> exp,&headresult);
            temp1 = temp1 -> next;
        }
        else if(temp1 -> exp < temp2 -> exp) {
            addNode(temp2 -> coef,temp2 -> exp,&headresult);
            temp2 = temp2 -> next;
        }
    }
    while(temp1 != NULL) {
        addNode(temp1->coef, temp1->exp, &headresult);
        temp1 = temp1->next;
    }
    while(temp2 != NULL) {
        addNode(temp2->coef, temp2->exp, &headresult);
        temp2 = temp2->next;
    }

    return headresult;
}

Node* multiplypolynomial(Node** head1,Node** head2) {
    Node *temp1 = *head1;
    Node *headresult = NULL;

    for(int i = 0; temp1 != NULL ; i++) {
        Node *temp2 = *head2;
        for(int j = 0; temp2 != NULL; j++) {
           addNode(temp1->coef * temp2 ->coef, temp1->exp + temp2->exp,  &headresult);
            temp2 = temp2->next;
        }
        temp1 = temp1->next;
    }
    Node* result = checkexp(headresult);
    return result;
}

int main() {
    Node* head1 = NULL;
    Node* head2 = NULL;
    addNode(2,5,&head1);
    addNode(4,3,&head1);
    addNode(3,2,&head1);
    addNode(5,0,&head1);

    addNode(3,5,&head2);
    addNode(5,3,&head2);
    addNode(4,2,&head2);
    addNode(6,0,&head2);
    cout  << endl;
    // Node* addresult = addpolynomial(&head1,&head2);
    // Node* addtemp = addresult;
    // while(addtemp != NULL) {
    //     cout << addtemp -> coef << "x" << addtemp -> exp << endl;
    //     addtemp = addtemp->next;
    // }
    // cout << endl;
    Node* mulresult = multiplypolynomial(&head1,&head2);
    Node* multemp = mulresult;
    while(multemp != NULL) {
        cout << multemp -> coef << "x" << multemp -> exp << endl;
        multemp = multemp->next;
    }
    return 0;
}
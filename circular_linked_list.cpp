#include <iostream>
using namespace std;

class Node{

    public:
    int data;
    Node* next;

    Node()
    {
        next = nullptr;
    }

    Node(int a)
    {
        data = a;
        next = nullptr;
    }

    Node(int a,Node* b)
    {
        data = a;
        next = b;
    }

};

class cll{

private:
Node* head;

public:

    cll()
    {
        head = nullptr;
    }
    void insertAtBeginning(int a)
    {
        Node* newnode = new Node(a);
        if(head == nullptr)
        {
            newnode -> next = newnode;
            head = newnode;
        }
        else
        {
            newnode -> next = head;
            Node* temp = head;
            while(temp -> next != head)
            {
                temp = temp -> next;
            }
            temp -> next = newnode;
            head = newnode;
        }
    }

    void insertAtEnd(int a)
    {
        Node* newnode = new Node(a);
        if(head == nullptr)
        {
            newnode -> next = newnode;
            head = newnode;
        }
        else
        {
            Node* temp = head;
            while(temp -> next != head)
            {
                temp = temp -> next;
            }
            temp -> next = newnode;
            newnode -> next = head;
        }
    }

    void deletekey(int key)
    {
        if(head == nullptr)
        {
            return;
        }
        else{
               if(head -> next == nullptr)
        {
            if(head -> data == key)
            {
                free(head);
                return;
            }
            return;
        }
        else
        {
            Node* current = head;
            while(current -> next -> data != key)
            {
                current = current -> next;
                if(current == head)
                {
                    cout << "Element not found." << endl;
                    return ;
                }
            }
            Node* temp = current -> next;
            current -> next = current -> next -> next;
            free(temp);
        }
        }
    }

    void display()
    {
        Node* current = head->next;
        if(head != nullptr)
        {
        cout << head -> data << endl;
        while(current != head && current!=nullptr)
        {
            cout << current->data << endl;
            current = current -> next;
        }
        }
    }
};

int main()
{
    cll list;
    list.insertAtEnd(5);
    list.insertAtBeginning(4);
    list.insertAtBeginning(3);
    list.insertAtBeginning(2);
    list.insertAtBeginning(1);

    list.display();
    cout << "-------------------------------" << endl;
    list.deletekey(3);

    list.display();

    return 0;
}
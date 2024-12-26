#include <iostream>
using namespace std;
class menus
{
public:
    void mainmenu();
    void inventory();
};
void menus::mainmenu()
{
    cout << "Main Menu" << endl;
    cout << "1) Inventory" << endl;
    cout << "2) Generate Bill" << endl;
    cout << "4) Show Stock" << endl;
    cout << "5) Show sales" << endl;
    cout << "3) Exit" << endl;
}
void menus::inventory()
{
    cout << "Inventory" << endl;
    cout << "1) Add Item" << endl;
    cout << "2) Delete Item" << endl;
    cout << "3) Update Item" << endl;
    cout << "4) Show Inventory" << endl;
    cout << "5) Exit" << endl;
}
class inventory
{
public:
    int id;
    int price;
    int quantity;
    string name;
    inventory *next;
    inventory *prev;

public:
    inventory()
    {
        cout << "Enter ID: ";
        cin >> id;
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Price: ";
        cin >> price;
        cout << "Enter Quantity: ";
        cin >> quantity;
        next = NULL;
        prev = NULL;
    }
    void additem(inventory *head);
    void deleteitem();
    void updateitem();
    void showinventory(inventory* &head);
};
void inventory::additem(inventory *head)
{

    inventory *newitem = new inventory();
    if (head == NULL)
    {
        head = newitem;
    }
    else
    {
        inventory *temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newitem;
        newitem->prev = temp;
    }
}
void deleteitem()
{

}
void updateitem()
{

}
void showinventory(inventory* &head)
{
    inventory* temp=head;
    while(temp!=NULL)
    {
        cout<<"ID: "<<temp->id<<endl;
        cout<<"Name: "<<temp->name<<endl;
        cout<<"Price: "<<temp->price<<endl;
        cout<<"Quantity: "<<temp->quantity<<endl;
        temp=temp->next;
    }
}
int main()
{
}
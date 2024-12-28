#include <iostream>
#include <string>
using namespace std;

class menus {
public:
    void mainmenu();
    void inventoryMenu();
};

void menus::mainmenu() {
    cout << "\nMain Menu\n";
    cout << "1) Inventory\n";
    cout << "2) Exit\n";
    cout << "Enter your choice: ";
}

void menus::inventoryMenu() {
    cout << "\nInventory Menu\n";
    cout << "1) Add Item\n";
    cout << "2) Delete Item\n";
    cout << "3) Update Item\n";
    cout << "4) Show Inventory\n";
    cout << "5) Exit to Main Menu\n";
    cout << "Enter your choice: ";
}

class inventory {
public:
    int id, price, quantity;
    string name;
    inventory* next;
    inventory* prev;

    inventory() : next(NULL), prev(NULL) {}

    void addItem(inventory*& head);
    void deleteItem(inventory*& head, int id);
    void updateItem(inventory* head, int id);
    void showInventory(inventory* head);
};

void inventory::addItem(inventory*& head) {
    inventory* newitem = new inventory();
    cout << "Enter ID: ";
    cin >> newitem->id;
    cout << "Enter Name: ";
    cin >> newitem->name;
    cout << "Enter Price: ";
    cin >> newitem->price;
    cout << "Enter Quantity: ";
    cin >> newitem->quantity;

    if (head == NULL) {
        head = newitem;
    } else {
        inventory* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newitem;
        newitem->prev = temp;
    }
    cout << "Item added successfully!\n";
}

void inventory::deleteItem(inventory*& head, int id) {
    inventory* temp = head;

    while (temp != NULL && temp->id != id) {
        temp = temp->next;
    }

    if (temp == NULL) {
        cout << "Item with ID " << id << " not found.\n";
        return;
    }

    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    } else {
        head = temp->next;
    }

    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }

    delete temp;
    cout << "Item deleted successfully!\n";
}

void inventory::updateItem(inventory* head, int id) {
    inventory* temp = head;

    while (temp != NULL && temp->id != id) {
        temp = temp->next;
    }

    if (temp == NULL) {
        cout << "Item with ID " << id << " not found.\n";
        return;
    }

    cout << "Enter new Name: ";
    cin >> temp->name;
    cout << "Enter new Price: ";
    cin >> temp->price;
    cout << "Enter new Quantity: ";
    cin >> temp->quantity;
    cout << "Item updated successfully!\n";
}

void inventory::showInventory(inventory* head) {
    if (head == NULL) {
        cout << "Inventory is empty.\n";
        return;
    }

    inventory* temp = head;
    while (temp != NULL) {
        cout << "\nID: " << temp->id
             << "\nName: " << temp->name
             << "\nPrice: " << temp->price
             << "\nQuantity: " << temp->quantity << endl;
        temp = temp->next;
    }
}

int main() {
    menus menu;
    inventory* head = NULL;
    inventory inv;
    int choice, id;

    while (true) {
        menu.mainmenu();
        cin >> choice;

        switch (choice) {
        case 1:
            while (true) {
                menu.inventoryMenu();
                cin >> choice;
                switch (choice) {
                case 1:
                    inv.addItem(head);
                    break;
                case 2:
                    cout << "Enter ID to delete: ";
                    cin >> id;
                    inv.deleteItem(head, id);
                    break;
                case 3:
                    cout << "Enter ID to update: ";
                    cin >> id;
                    inv.updateItem(head, id);
                    break;
                case 4:
                    inv.showInventory(head);
                    break;
                case 5:
                    goto main_menu;
                default:
                    cout << "Invalid choice. Try again.\n";
                }
            }
        main_menu:
            break;
        case 2:
            cout << "Exiting program. Goodbye!\n";
            return 0;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }
}

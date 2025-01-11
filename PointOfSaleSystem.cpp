#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <ctime>
using namespace std;
template <class T>
class stack
{
private:
struct node
{
    T data;
    node *next;
    node(T data)
    {
        this->data = data;
        next = nullptr;
    }
};
    node *top;
public:
    stack()
    {
        top = nullptr;
    }
    void push(string data)
    {
        node<string> *newnode = new node<string>(data);
        newnode->next = top;
        top = newnode;
    }
    void pop()
    {
        if (top == nullptr)
        {
            cout << "Stack is empty!" << endl;
            return;
        }
        node<string> *temp = top;
        top = top->next;
        delete temp;
    }
    string peek()
    {
        if (top == nullptr)
        {
            throw runtime_error("Stack is empty");
        }
        return top->data;
    }
    bool isEmpty()
    {
        return top == nullptr;
    }
    void top()
    {
        if (isEmpty())
        {
            cout << "Stack is empty!" << endl;
            return;
        }
        cout << "Top of the stack: " << top->data << endl;
    }
};
class undoredo
{
private:
    stack<string> undostack;
    stack<string> redostack;
public:
    void performaction(string action)
    {
        undostack.push(action);
        while (!redostack.isEmpty())
        {
            redostack.pop();
        }
        cout << "Performed action: " << action << endl;
    }
    void undo()
    {
        if (undostack.isEmpty())
        {
            cout << "Nothing to undo!" << endl;
            return;
        }
        string lastaction = undostack.peek();
        undostack.pop();
        redostack.push(lastaction);
        cout << "Undone action: " << lastaction << endl;
    }
    void redo()
    {
        if (redostack.isEmpty())
        {
            cout << "Nothing to redo!" << endl;
            return;
        }
        string lastundone = redostack.peek();
        redostack.pop();
        undostack.push(lastundone);
        cout << "Redone action: " << lastundone << endl;
    }
    void printstate()
    {
        cout << "Undo Stack: ";
        stack<string> tempundo = undostack;
        while (!tempundo.isEmpty())
        {
            cout << tempundo.peek() << " ";
            tempundo.pop();
        }
        cout << "\nRedo Stack: ";
        stack<string> tempredo = redostack;
        while (!tempredo.isEmpty())
        {
            cout << tempredo.peek() << " ";
            tempredo.pop();
        }
        cout << "\n";
    }
};
class product
{
public:
    int id;
    string name;
    double price;
    int stock;
    product *next;
    product *prev;
    product(int id, string name, double price, int stock)
    {
        this->id = id;
        this->name = name;
        this->price = price;
        this->stock = stock;
        prev = next = nullptr;
    }
};
class Inventory
{
private:
    product *head;
    int numberofproducts;

public:
    Inventory()
    {
        head = nullptr;
        numberofproducts = 0;
    }
    
    void savestock() const
    {
        ofstream file("inventory.txt");
        if (!file.is_open())
        {
            cout << "Error: Could not open the file to save inventory!" << endl;
            return;
        }

        file << left << setw(10) << "ID"
             << setw(20) << "Name"
             << setw(10) << "Quantity"
             << setw(10) << "Price" << endl;
        file << string(50, '-') << endl;

        product *current = head;
        while (current != NULL)
        {
            file << left << setw(10) << current->id
                 << setw(20) << current->name
                 << setw(10) << current->stock
                 << setw(10) << fixed << setprecision(2) << current->price
                 << endl;
            current = current->next;
        }

        file << string(50, '-') << endl;
    
        file.close();
        cout << "Inventory successfully saved/updated to 'inventory.txt'." << endl;
    }

    bool productexists(int id)
    {
        product *current = head;
        while (current != NULL)
        {
            if (current->id == id)
            {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void addproduct(int id, string name, double price, int stock)
    {
        if (productexists(id))
        {
            cout << "A product with ID " << id << " already exists !!!" << endl;
            cout << "Please enter a different ID" << endl;
            return;
        }
        product *newproduct = new product(id, name, price, stock);
        if (head == NULL)
        {
            head = newproduct;
        }
        else
        {
            product *current = head;
            while (current->next != NULL)
            {
                current = current->next;
            }
            current->next = newproduct;
            newproduct->prev = current;
        }
        numberofproducts++;
        cout << "Product added: " << name << " (ID: " << id << ")" << endl;
        savestock();
    }

    product *findproduct(int id)
    {
        product *current = head;
        while (current != NULL)
        {
            if (current->id == id)
            {
                return current;
            }
            current = current->next;
        }
        return NULL;
    }

    void displaystock() const
    {
        if (head == NULL)
        {
            cout << "No products in inventory !!!" << endl;
            cout << "Please add some products to the inventory" << endl;
            return;
        }
        cout << left << setw(10) << "ID"
             << setw(20) << "Name"
             << setw(10) << "Quantity"
             << setw(10) << "Price" << endl;
        cout << string(50, '-') << endl;
        product *current = head;
        while (current != NULL)
        {
            cout << left << setw(10) << current->id
                 << setw(20) << current->name
                 << setw(10) << current->stock
                 << setw(10) << fixed << setprecision(2) << current->price
                 << endl;
            current = current->next;
        }
        cout << string(50, '-') << endl;
    }
    void removeproduct(int id)
    {
        product *current = head;
        while (current != NULL)
        {
            if (current->id == id)
            {
                if (current->prev != NULL)
                {
                    current->prev->next = current->next;
                }
                else
                {
                    head = current->next;
                }
                if (current->next != NULL)
                {
                    current->next->prev = current->prev;
                }
                cout << "Removed product: " << current->name << " (ID: " << id << ")" << endl;
                delete current;
                numberofproducts--;
                return;
            }
            current = current->next;
        }
        cout << "Product with ID " << id << " not found." << endl;
        savestock();
    }
    void updateproduct(int id, string name, double price, int stock)
    {
        product *current = head;
        while (current != NULL)
        {
            if (current->id == id)
            {
                if (!name.empty())
                    current->name = name;
                if (price >= 0)
                    current->price = price;
                if (stock >= 0)
                    current->stock = stock;
                cout << "Updated product: " << current->name << " (ID: " << id << ")" << endl;
                return;
            }
            current = current->next;
            
        }
        cout << "Product with ID " << id << " not found." << endl;
        savestock();
    }
    void applydiscounttoproduct(int id, double discountpercent)
    {
        product *current = head;
        while (current != NULL)
        {
            if (current->id == id)
            {
                double discountamount = current->price * (discountpercent / 100);
                current->price -= discountamount;
                cout << "Applied " << discountpercent << "% discount. New price: " << current->price << endl;
                savestock();
                return;
            }
            current = current->next;
        }
        cout << "Product with ID " << id << " not found." << endl;
    }
};
struct billnode
{
    int productId;
    int quantity;
    billnode *next;

    billnode(int id, int qty)
    {
        productId = id;
        quantity = qty;
        next = nullptr;
    }
};
class billqueue
{
private:
    billnode *front;
    billnode *rear;

public:
    billqueue()
    {
        front = rear = nullptr;
    }
    bool isEmpty()
    {
        return front == nullptr;
    }

    billnode *getfront()
    {
        return front;
    }

    void enqueue(int productId, int quantity)
    {
        billnode *newNode = new billnode(productId, quantity);
        if (rear == nullptr)
        {
            front = rear = newNode;
        }
        else
        {
            rear->next = newNode;
            rear = newNode;
        }
    }
    void dequeue()
    {
        if (isEmpty())
        {
            cout << "The bill queue is empty!" << endl;
            return;
        }
        billnode *temp = front;
        front = front->next;
        if (front == nullptr)
        {
            rear = nullptr;
        }
        delete temp;
    }

    billnode *peek()
    {
        return front;
    }

    void display()
    {
        if (isEmpty())
        {
            cout << "No items in the bill." << endl;
            return;
        }

        billnode *current = front;
        cout << left << setw(10) << "Product ID" << setw(10) << "Quantity" << endl;
        cout << string(20, '-') << endl;
        while (current != nullptr)
        {
            cout << left << setw(10) << current->productId << setw(10) << current->quantity << endl;
            current = current->next;
        }
        cout << string(20, '-') << endl;
    }
};
class BillingSystem
{
private:
    double total;
    double taxrate;
    double totalsales;
    Inventory inventory;
    billqueue billQueue;

public:
    BillingSystem()
    {
        total = 0;
        taxrate = 0.1;
        totalsales = 0;
    }
    void saveBillToFile()
    {
        ofstream file("bill.txt");
        if (!file.is_open())
        {
            cout << "Error: Could not open the file to save the bill!" << endl;
            return;
        }
        file << "Customer Bill" << endl;
        file << string(30, '-') << endl;
        file << left << setw(10) << "ProductID"
             << setw(15) << "Quantity"
             << setw(10) << "Price"
             << endl;
        file << string(30, '-') << endl;
        billnode *current = billQueue.getfront();
        while (current != nullptr)
        {
            product *prod = inventory.findproduct(current->productId);
            if (prod != nullptr)
            {
                file << left << setw(10) << current->productId
                     << setw(15) << current->quantity
                     << setw(10) << fixed << setprecision(2) << prod->price * current->quantity
                     << endl;
            }
            current = current->next;
        }
        file << string(30, '-') << endl;
        file << "Total (before tax): $" << fixed << setprecision(2) << total << endl;
        file << "Tax: $" << fixed << setprecision(2) << total * taxrate << endl;
        file << "Total (with tax): $" << fixed << setprecision(2) << total * (1 + taxrate) << endl;
        file.close();
        cout << "Bill saved to 'bill.txt'." << endl;
    }

    void addProductToBill(int productId, int quantity)
    {

        product *prod = inventory.findproduct(productId);
        if (prod == nullptr)
        {
            cout << "Product with ID " << productId << " not found in inventory :( !!!" << endl;
            return;
        }

        if (prod->stock < quantity)
        {
            cout << "Insufficient stock for product: " << prod->name << " :( " << endl;
            return;
        }

        billQueue.enqueue(productId, quantity);
        total += prod->price * quantity;
        prod->stock -= quantity;

        cout << "Added " << quantity << " of " << prod->name << " to the bill." << endl;
        inventory.savestock();
    }

    void removeProductFromBill()
    {

        if (billQueue.isEmpty())
        {
            cout << "The bill is empty!" << endl;
            return;
        }

        billnode *billItem = billQueue.peek();
        int productId = billItem->productId;
        int quantity = billItem->quantity;

        product *prod = inventory.findproduct(productId);
        if (prod != nullptr)
        {
            prod->stock += quantity;
            total -= prod->price * quantity;
            cout << "Removed " << quantity << " of " << prod->name << " from the bill." << endl;
        }

        billQueue.dequeue();
        inventory.savestock();
    }

    void displayBill()
    {
        cout << "Current Bill:" << endl
             << string(20, '-') << endl;
        billQueue.display();
        cout << "Total (before tax): $" << fixed << setprecision(2) << total << endl;
        cout << "Tax: $" << fixed << setprecision(2) << total * taxrate << endl;
        cout << "Total (with tax): $" << fixed << setprecision(2) << total * (1 + taxrate) << endl;
    }
     void finalizeBill()
     {
        displayBill();
        cout<<"Enter your payment method"<<endl;
        cout<<"1.Cash"<<endl;
        cout<<"2.Credit Card"<<endl;
        cout<<"3.Debit Card"<<endl;
        cout<<"4.Mobile Wallet"<<endl;
        int choice;
        cin>>choice;
        if(choice==1)
        {
            cout<<"Enter the amount you are paying: ";
            double amount;
            cin>>amount;
            if(amount<total)
            {
                cout<<"Insufficient amount paid. Please pay the full amount."<<endl;
                finalizeBill();
            }
            else
            {
                cout<<"Payment successful. Thank you for shopping with us!"<<endl;
                saveBillToFile();
                checkout();
            }
        }
        else
        {
            cout<<"Payment successful. Thank you for shopping with us!"<<endl;
            saveBillToFile();
            checkout();
        }
        if(choice==2)
        {
            cout<<"Enter your credit card number: ";
            string cardnumber;
            cin>>cardnumber;
            cout<<"Enter the expiry date: ";
            string expirydate;
            cin>>expirydate;
            cout<<"Enter the CVV: ";
            string cvv;
            cin>>cvv;
            cout<<"Payment successful. Thank you for shopping with us!"<<endl;
            saveBillToFile();
            checkout();
        }
        if(choice==3)
        {
            cout<<"Enter your debit card number: ";
            string cardnumber;
            cin>>cardnumber;
            cout<<"Enter the expiry date: ";
            string expirydate;
            cin>>expirydate;
            cout<<"Enter the CVV: ";
            string cvv;
            cin>>cvv;
            cout<<"Payment successful. Thank you for shopping with us!"<<endl;
            saveBillToFile();
            checkout();
        }
        if(choice==4)
        {
            cout<<"Enter your mobile number: ";
            string mobilenumber;
            cin>>mobilenumber;
            cout<<"Enter your mobile wallet password: ";
            string password;
            cin>>password;
            cout<<"Payment successful. Thank you for shopping with us!"<<endl;
            saveBillToFile();
            checkout();
        }
        if (choice>4)
        {
            cout<<"Invalid choice, try again!"<<endl;
            finalizeBill();
        }
     }
    void checkout()
    {
        totalsales += total * (1 + taxrate);
        total = 0;
        while (!billQueue.isEmpty())
        {
            billQueue.dequeue();
        }
        cout << "Checkout complete. Thank you!" << endl;
    }
};
class feedbacksystem
{
public:
    void collectfeedback()
    {
        string name, email, feedback;
        cout << "=============== USER FEEDBACK INTERFACE ===============" << endl;
        cout << "Enter your name: ";
        getline(cin, name);
        cout << "Enter your email: ";
        getline(cin, email);
        cout << "Enter your feedback: ";
        getline(cin, feedback);
        savefeedback(name, email, feedback);
        cout << "Thank you for your feedback!" << endl;
    }
    void savefeedback(const string &name, const string &email, const string &feedback)
    {
        ofstream file("feedback.txt", ios::app);
        if (!file)
        {
            cerr << "Error opening feedback file for writing!" << endl;
            return;
        }
        file << "=============== FEEDBACK ENTRY ===============" << endl;
        file<<"time:"<<getcurrenttime()<<endl;
        file<<"date:"<<getcurrentdate()<<endl;
        file << "Name: " << name << endl;
        file << "Email: " << email << endl;
        file << "Date: " << getcurrenttime() << endl;
        file << "Feedback: " << feedback << endl;
        file << "==============================================" << endl;
        file.close();
    }
    string getcurrenttime() const
    {
        time_t now = time(0);
        char *dt = ctime(&now);
        return dt;
    }
    string getcurrentdate() const
    {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        char buffer[50];
        strftime(buffer, 50, "%Y-%m-%d %H:%M:%S", ltm);
        return string(buffer);
    }
};
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class AutoPilot
{
private:
    BillingSystem &billingSystem;
    Inventory &inventory;
    menus menu;
    const string adminPassword = "1234";

    void resetSystem()
    {
        billingSystem.checkout();
    }

    bool verifyAdmin()
    {
        string inputPassword;
        cout << "Enter Admin Password to Exit Auto Pilot Mode: ";
        cin >> inputPassword;
        return inputPassword == adminPassword;
    }

public:
    AutoPilot(BillingSystem &billing, Inventory &inv) : billingSystem(billing), inventory(inv) {}

    void start()
    {
        while (true)
        {
            system("cls");
            cout << "============== AUTO PILOT MODE ==============" << endl;
            string customerName;
            cout << "Welcome to the store!" << endl;
            cout << "Please enter your name: ";
            cin.ignore(); // Clear buffer
            getline(cin, customerName);

            while (true)
            {
                int productId, quantity;
                cout << endl
                     << "Hello, " << customerName << "! What would you like to buy?" << endl;
                inventory.displaystock();
                cout << "Enter Product ID (or -1 to finish): ";
                cin >> productId;

                if (productId == -1)
                    break;

                cout << "Enter Quantity: ";
                cin >> quantity;

                billingSystem.addProductToBill(productId, quantity);
            }

            cout << endl
                 << "Generating your bill..." << endl;
            billingSystem.displayBill();
            billingSystem.finalizeBill();
            cout << "Thank you, " << customerName << "! Have a great day!" << endl;
            resetSystem();
            cout << "Waiting for the next customer..." << endl;
            cout << "To exit Auto Pilot Mode, press '1' or continue by pressing any other key: ";
            int exitChoice;
            cin >> exitChoice;

            if (exitChoice == 1)
            {
                if (verifyAdmin())
                {
                    cout << "Exiting Auto Pilot Mode. Returning to main menu." << endl;
                    menu.mainmenu();
                    break;
                }
                else
                {
                    cout << "Incorrect password. Continuing Auto Pilot Mode." << endl;
                    start();
                }
            }
        }
    }
};

class menus
{
private:
    Inventory inventory;
    BillingSystem billingSystem;
    int choice;

public:
    void about()
    {
        cout << "A simple offline Point of Sale System featuring efficent inventory management"
             << endl
             << "and a simple billing system for paper-less management of your bussiness " << endl
             << "Developed by: Muhammad Murtaza (F2023266701)" << endl
             << "Mohsin Khan (F2023266704)" << endl
             << "Muhammad Zain-Ul-Abideen (F2023266705)" << endl;
        cout << "Press any key to return to main menu" << endl;
        cin.get();
        mainmenu();
    }
    void nextmenu()
    {
        cout << endl
             << "============== POINT OF SALE SYSTEM ==============" << endl;
        cout << "1) Product Management " << endl;
        cout << "2) Generate Bill" << endl;
        cout << "3) Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice)
        {
        case 1:
            productmenu();
            break;
        case 2:
            billmenu();
            break;
        case 3:
            cout << "Returning to main menu..." << endl;
            mainmenu();
            break;
        default:
            cout << "Invalid choice, try again!" << endl;
            break;
        }
    }
    void billmenu()
    {
        cout << "============== BILLING SYSTEM ==============" << endl;
        int choice;
        cout << "1. Add Product to Bill" << endl;
        cout << "2. Remove Product from Bill" << endl;
        cout << "3. Display Bill" << endl;
        cout << "4. Checkout" << endl;
        cout<<"5.back"<<endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice)
        {
        case 1:
        {
            cout << "ADD PRODUCT TO BILL" << endl;
            int id, quantity;
            cout << "Enter product ID: ";
            cin >> id;
            cout << "Enter quantity: ";
            cin >> quantity;
            billingSystem.addProductToBill(id, quantity);
            cout << "Enter 1 to add more products or press any key to return to billing menu: ";
            cin >> choice;
            if (choice == 1)
            {
                cout << "Enter product ID: ";
                cin >> id;
                cout << "Enter quantity: ";
                cin >> quantity;
                billingSystem.addProductToBill(id, quantity);
            }
            else
            {
                billmenu();
            }
        break;
        case 2:
            cout << "REMOVE PRODUCT FROM BILL" << endl;
            billingSystem.removeProductFromBill();
            cout << "Enter 1 to remove more products or press any key to return to billing menu: ";
            cin >> choice;
            if (choice == 1)
            {
                billingSystem.removeProductFromBill();
            }
            else
            {
                billmenu();
            }
            break;
        case 3:
            billingSystem.displayBill();
            break;
        case 4:
            billingSystem.checkout();
            break;
        case 5:
            cout << "Returning to main menu..." << endl;
            nextmenu();
            break;
        default:
            cout << "Invalid choice, try again!" << endl;
            break;
        }
    }
}
 void productmenu()
{

    int choice;
    cout << "============== PRODUCT MANAGEMENT ==============" << endl;
    cout << "1) Add Product" << endl;
    cout << "2) Remove Product" << endl;
    cout << "3) Update Product" << endl;
    cout << "4) Display Stock" << endl;
    cout << "5) Apply Discount" << endl;
    cout << "6) Back" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();
    switch (choice)
    {
    case 1:
    {
        system("cls");
        addproduct();
        cout << "Product added successfully!" << endl;
        cout << "Enter 1 to add more products or press any key to return to product management menu: ";
        cin >> choice;
        if (choice == 1)
        {
            addproduct();
        }
        else
        {
            productmenu();
        }
    }
    break;
    case 2:
    {
        cout << "============== Remove Product ====================" << endl;
        int id;
        cout << "Enter product ID to remove : ";
        cin >> id;
        inventory.removeproduct(id);
        cout << "Product removed successfully!" << endl;
        cout << "Enter 1 to remove more products or press any key to return to product management menu: ";
        cin >> choice;
        if (choice == 1)
        {
            cout << "Enter product ID to remove : ";
            cin >> id;
            inventory.removeproduct(id);
        }
        else
        {
            productmenu();
        }
    }
    break;
    case 3:
    {
        cout << "============== Update Product ====================" << endl;
        int id, stock;
        string name;
        double price;
        cout << "Enter product ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter new product name (leave empty to keep the same): ";
        getline(cin, name);
        cout << "Enter new product price (negative to keep the same): ";
        cin >> price;
        cout << "Enter new product quantity (negative to keep the same): ";
        cin >> stock;
        inventory.updateproduct(id, name, price, stock);
        cout << "Product updated successfully!" << endl;
        cout << "Enter 1 to update more products or press any key to return to product management menu: ";
        cin >> choice;
        if (choice == 1)
        {
            cout << "Enter product ID to update : ";
            cin >> id;
            cin.ignore();
            cout << "Enter new product name (leave empty to keep the same): ";
            getline(cin, name);
            cout << "Enter new product price (negative to keep the same): ";
            cin >> price;
            cout << "Enter new product quantity (negative to keep the same): ";
            cin >> stock;
            inventory.updateproduct(id, name, price, stock);
        }
        else
        {
            productmenu();
        }
    }
    break;
    case 4:
        inventory.displaystock();
        break;
    case 5:
    {
        cout << "============== Apply Discount ====================" << endl;
        int id;
        double discount;
        cout << "Enter product ID: ";
        cin >> id;
        cout << "Enter discount percentage: ";
        cin >> discount;
        inventory.applydiscounttoproduct(id, discount);
        cout << "Discount applied successfully!" << endl;
        cout << "Enter 1 to apply more discounts or press any key to return to product management menu: ";
        cin >> choice;
        if (choice == 1)
        {
            cout << "Enter product ID: ";
            cin >> id;
            cout << "Enter discount percentage: ";
            cin >> discount;
            inventory.applydiscounttoproduct(id, discount);
        }
        else
        {
            productmenu();
        }
    }
    break;
    case 6:
        cout << "Returning to main menu..." << endl;
        nextmenu();
        break;
    default:
        cout << "Invalid choice, try again!" << endl;
        break;
    }
}
void addproduct()
{
    system("cls");
    cout << "============== Add Product ====================" << endl;
    cout << "Enter product details: " << endl;
    int id, stock;
    string name;
    double price;
    cout << "Enter product ID: ";
    cin >> id;
    cin.ignore();
    cout << "Enter product name: ";
    getline(cin, name);
    cout << "Enter product price: ";
    cin >> price;
    cout << "Enter product quantity: ";
    cin >> stock;
    inventory.addproduct(id, name, price, stock);
}
void mainmenu()
{
    do
    {
        cout << endl
             << "============== POINT OF SALE SYSTEM ==============" << endl;
        cout << "1. Enter Point of Sale System" << endl;
        cout << "2. About the System" << endl;
        cout<<"3.Auto Pilot Mode"<<endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice)
        {
        case 1:
            nextmenu();
            break;
        case 2:
            about();
            break;
        case 3:
        {
            AutoPilot autopilot(billingSystem, inventory);
            autopilot.start();
            break;
        }
        case 4:
            cout << "BYE BYE !!!........." << endl;
            break;
        default:
            cout << "Invalid choice, try again!" << endl;
            break;
        }
    } while (choice != 4);
}
};
int main()
{
    menus menu;
    menu.mainmenu();
    return 0;
}
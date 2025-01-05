// #include <iostream>
// #include <string>
// #include <fstream>
// #include <iomanip>
// using namespace std;

// const int MAX_BILL_ITEMS = 100;

// class Node
// {
// public:
//     string name;
//     double price;
//     int quantity;
//     Node *next;

//     Node(string NAME, double PRICE, int QUANTITY)
//         : name(NAME), price(PRICE), quantity(QUANTITY), next(nullptr) {}
// };

// class Queue
// {
// private:
//     Node *front;
//     Node *rear;
//     int size;

// public:
//     Queue() : front(nullptr), rear(nullptr), size(0) {}

//     ~Queue()
//     {
//         while (!isEmpty())
//         {
//             dequeue();
//         }
//     }

//     bool isEmpty() const
//     {
//         return front == nullptr;
//     }

//     void enqueue(string name, double price, int quantity)
//     {
//         Node *newNode = new Node(name, price, quantity);
//         if (rear)
//         {
//             rear->next = newNode;
//         }
//         rear = newNode;
//         if (!front)
//         {
//             front = rear;
//         }
//         size++;
//     }

//     void dequeue()
//     {
//         if (isEmpty())
//         {
//             cout << "Queue is empty!" << endl;
//             return;
//         }
//         Node *temp = front;
//         front = front->next;
//         if (!front)
//         {
//             rear = nullptr;
//         }
//         delete temp;
//         size--;
//     }

//     Node *peek() const
//     {
//         return front;
//     }

//     int getSize() const
//     {
//         return size;
//     }

//     void printQueue() const
//     {
//         Node *current = front;
//         while (current)
//         {
//             cout << left << setw(20) << current->name
//                  << setw(10) << current->price
//                  << setw(10) << current->quantity
//                  << setw(10) << current->price * current->quantity
//                  << endl;
//             current = current->next;
//         }
//     }
// };

// class BillingSystem
// {
// private:
//     Queue purchasedProducts;
//     double total;
//     double taxRate;
//     double totalSales;

// public:
//     BillingSystem(double TAX_RATE = 0.1) : total(0), taxRate(TAX_RATE), totalSales(0) {}

//     void addProduct(string name, double price, int quantity)
//     {
//         purchasedProducts.enqueue(name, price, quantity);
//         total += price * quantity;
//         cout << "Added to bill: " << name << " | Quantity: " << quantity << " | Subtotal: " << price * quantity << endl;
//     }

//     double calculateTax() const
//     {
//         return total * taxRate;
//     }

//     double getTotalWithTax() const
//     {
//         return total + calculateTax();
//     }

//     void finalizeBill()
//     {
//         cout << "=================== YOUR BILL ===================" << endl;
//         cout << left << setw(20) << "Product"
//              << setw(10) << "Price"
//              << setw(10) << "Quantity"
//              << setw(10) << "Subtotal"
//              << endl;
//         cout << string(50, '-') << endl;

//         purchasedProducts.printQueue();

//         cout << string(50, '-') << endl;
//         cout << "Subtotal: " << total << endl;
//         cout << "Tax (" << taxRate * 100 << "%): " << calculateTax() << endl;
//         cout << "Total: " << getTotalWithTax() << endl;

//         totalSales += getTotalWithTax();
//         saveBill();
//     }

//     void saveBill()
//     {
//         ofstream file("bill.txt", ios::app);
//         file << "=================== YOUR BILL ===================" << endl;
//         file << left << setw(20) << "Product"
//              << setw(10) << "Price"
//              << setw(10) << "Quantity"
//              << setw(10) << "Subtotal"
//              << endl;
//         file << string(50, '-') << endl;

//         Node *current = purchasedProducts.peek();
//         while (current)
//         {
//             file << left << setw(20) << current->name
//                  << setw(10) << current->price
//                  << setw(10) << current->quantity
//                  << setw(10) << current->price * current->quantity
//                  << endl;
//             current = current->next;
//         }

//         file << string(50, '-') << endl;
//         file << "Subtotal: " << total << endl;
//         file << "Tax (" << taxRate * 100 << "%): " << calculateTax() << endl;
//         file << "Total: " << getTotalWithTax() << endl;
//         file.close();

//         cout << "Bill saved to bill.txt" << endl;
//     }

//     double getTotalSales() const
//     {
//         return totalSales;
//     }
// };

// int main()
// {
//     BillingSystem billing;

//     billing.addProduct("Laptop", 999.99, 1);
//     billing.addProduct("Smartphone", 499.49, 2);
//     billing.addProduct("Tablet", 299.99, 3);

//     billing.finalizeBill();

//     cout << "Total sales recorded: " << billing.getTotalSales() << endl;

//     return 0;
// }

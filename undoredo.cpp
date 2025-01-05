// #include <iostream>
// #include <stack>
// #include <string>
// using namespace std;

// // User-defined stack class
// template <typename T>
// class Stack
// {
// private:
//     struct Node
//     {
//         T data;
//         Node* next;
//         Node(T value) : data(value), next(nullptr) {}
//     };

//     Node* topNode;

// public:
//     Stack() : topNode(nullptr) {}

//     ~Stack()
//     {
//         while (!isEmpty())
//         {
//             pop();
//         }
//     }

//     void push(T value)
//     {
//         Node* newNode = new Node(value);
//         newNode->next = topNode;
//         topNode = newNode;
//     }

//     void pop()
//     {
//         if (isEmpty())
//         {
//             return;
//         }
//         Node* temp = topNode;
//         topNode = topNode->next;
//         delete temp;
//     }

//     T top() const
//     {
//         if (!isEmpty())
//         {
//             return topNode->data;
//         }
//         throw runtime_error("Stack is empty");
//     }

//     bool isEmpty() const
//     {
//         return topNode == nullptr;
//     }
// };

// // Undo/Redo System
// class UndoRedo
// {
// private:
//     Stack<string> undoStack;
//     Stack<string> redoStack;

// public:
//     void performAction(const string& action)
//     {
//         undoStack.push(action);
//         while (!redoStack.isEmpty())
//         {
//             redoStack.pop(); // Clear the redo stack when a new action is performed
//         }
//         cout << "Performed action: " << action << endl;
//     }

//     void undo()
//     {
//         if (undoStack.isEmpty())
//         {
//             cout << "Nothing to undo!" << endl;
//             return;
//         }
//         string lastAction = undoStack.top();
//         undoStack.pop();
//         redoStack.push(lastAction);
//         cout << "Undone action: " << lastAction << endl;
//     }

//     void redo()
//     {
//         if (redoStack.isEmpty())
//         {
//             cout << "Nothing to redo!" << endl;
//             return;
//         }
//         string lastUndone = redoStack.top();
//         redoStack.pop();
//         undoStack.push(lastUndone);
//         cout << "Redone action: " << lastUndone << endl;
//     }

//     void printState() const
//     {
//         cout << "\nCurrent State:\n";
//         cout << "Undo Stack: ";
//         Stack<string> tempUndo = undoStack; // Copy to display contents
//         while (!tempUndo.isEmpty())
//         {
//             cout << tempUndo.top() << " ";
//             tempUndo.pop();
//         }
//         cout << "\nRedo Stack: ";
//         Stack<string> tempRedo = redoStack; // Copy to display contents
//         while (!tempRedo.isEmpty())
//         {
//             cout << tempRedo.top() << " ";
//             tempRedo.pop();
//         }
//         cout << "\n";
//     }
// };

// int main()
// {
//     UndoRedo urSystem;
//     int choice;
//     string action;

//     do
//     {
//         cout << "\n========== UNDO/REDO SYSTEM ==========\n";
//         cout << "1. Perform Action\n";
//         cout << "2. Undo\n";
//         cout << "3. Redo\n";
//         cout << "4. Show Current State\n";
//         cout << "0. Exit\n";
//         cout << "Enter your choice: ";
//         cin >> choice;
//         cin.ignore(); // To consume the newline character after input

//         switch (choice)
//         {
//         case 1:
//             cout << "Enter action: ";
//             getline(cin, action);
//             urSystem.performAction(action);
//             break;
//         case 2:
//             urSystem.undo();
//             break;
//         case 3:
//             urSystem.redo();
//             break;
//         case 4:
//             urSystem.printState();
//             break;
//         case 0:
//             cout << "Exiting...\n";
//             break;
//         default:
//             cout << "Invalid choice! Try again.\n";
//         }
//     } while (choice != 0);

//     return 0;
// }

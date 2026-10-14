
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

struct Expense {
    string category;
    double amount;
};

vector<Expense> expenses;

void loadExpenses() {
    ifstream file("expenses.txt");
    Expense expense;

    while (file >> expense.amount) {
        file.ignore(numeric_limits<streamsize>::max(), '\n');
        if (getline(file, expense.category)) {
            expenses.push_back(expense);
        }
    }
}

void saveExpenses() {
    ofstream file("expenses.txt");

    for (const Expense& expense : expenses) {
        file << expense.amount << '\n';
        file << expense.category << '\n';
    }
}

void addExpense() {
    Expense expense;

    cout << "Enter expense category: ";
    getline(cin >> ws, expense.category);

    cout << "Enter amount: ";

    if (!(cin >> expense.amount) || expense.amount <= 0) {
        cout << "Invalid amount. Please enter a positive number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    expenses.push_back(expense);
    saveExpenses();

    cout << "Expense saved successfully!\n";
}

void showExpenses() {
    if (expenses.empty()) {
        cout << "No expenses recorded yet.\n";
        return;
    }

    double total = 0;

    cout << "\n--- EXPENSE HISTORY ---\n";

    for (size_t i = 0; i < expenses.size(); ++i) {
        cout << i + 1 << ". "
             << expenses[i].category << " - "
             << fixed << setprecision(2)
             << expenses[i].amount << '\n';

        total += expenses[i].amount;
    }

    cout << "Total expenses: "
         << fixed << setprecision(2)
         << total << "\n";
}

int main() {
    loadExpenses();

    int choice;

    do {
        cout << "\n============================\n";
        cout << "     C++ EXPENSE TRACKER\n";
        cout << "============================\n";
        cout << "1. Add expense\n";
        cout << "2. View expenses\n";
        cout << "3. Exit\n";
        cout << "Choose an option: ";

        if (!(cin >> choice)) {
            cout << "Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1:
                addExpense();
                break;
            case 2:
                showExpenses();
                break;
            case 3:
                saveExpenses();
                cout << "Expenses saved. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 3);

    return 0;
}

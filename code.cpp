#include <iostream>
#include <map>
using namespace std;
// ATM system class
class ATM
{
public:
  struct User
  {
    string name;
    double balance;
  };

  map<int, User> users; 

public:
  ATM()
  {
    users[10050] = {"Adarsh", 10000.00};
    users[10072] = {"Ayushi", 50000.00};
    users[10154] = {"Aditya", 12000.00};
    users[14123] = {"Ruchika", 75001.00};
    users[10010] = {"Pradeep", 50000.00};
  }

  // Function to verify PIN and return user details
  User *verifyPin(int input_pin)
  {
    if (users.find(input_pin) != users.end())
    {
      return &users[input_pin]; 
    }
    else
    {
      cout << "Incorrect PIN. Please try again." << endl;
      return nullptr;
    }
  }

  // Function to check balance
  void checkBalance(User *user)
  {
    cout << "Your current balance is: $" << user->balance << endl;
  }

  // Function to deposit money
  void deposit(User *user, double amount)
  {
    if (amount > 0)
    {
      user->balance += amount;
      cout << "Successfully deposited $" << amount << endl;
      checkBalance(user);
    }
    else
    {
      cout << "Invalid deposit amount." << endl;
    }
  }

  // Function to withdraw money
  void withdraw(User *user, double amount)
  {
    if (amount > 0 && amount <= user->balance)
    {
      user->balance -= amount;
      cout << "Successfully withdraw $" << amount << endl;
      checkBalance(user);
    }
    else if (amount > user->balance)
    {
      cout << "Insufficient funds." << endl;
    }
    else
    {
      cout << "Invalid withdrawal amount." << endl;
    }
  }
};

void showMenu()
{
  cout << "\n===== ATM System Menu =====" << endl;
  cout << "1. Check Balance" << endl;
  cout << "2. Deposit Money" << endl;
  cout << "3. Withdraw Money" << endl;
  cout << "4. Exit" << endl;
  cout << "===========================" << endl;
}

int main()
{
  // Initialize ATM system
  ATM atm;

  int input_pin;
  int attempts = 0;
  const int max_attempts = 3;
  ATM::User *currentUser = nullptr;

  // PIN authentication
  while (attempts < max_attempts)
  {
    cout << "Enter your PIN: ";
    cin >> input_pin;

    currentUser = atm.verifyPin(input_pin);
    if (currentUser != nullptr)
    {
      cout << "Welcome, " << currentUser->name << " ! " << endl;
      break; // If PIN is correct, proceed to the ATM menu
    }
    attempts++;
    if (attempts == max_attempts)
    {
      cout << "Too many incorrect attempts. Exiting." << endl;
      return 1; // Exit the program after 3 failed attempts
    }
  }

  // Main ATM operations
  int choice;
  double amount;

  do
  {
    showMenu();
    cout << "Enter your choice (1-4): ";
    cin >> choice;

    switch (choice)
    {
    case 1:
      atm.checkBalance(currentUser);
      break;
    case 2:
      cout << "Enter amount to deposit: $";
      cin >> amount;
      atm.deposit(currentUser, amount);
      break;
    case 3:
      cout << "Enter amount to withdraw: $";
      cin >> amount;
      atm.withdraw(currentUser, amount);
      break;
    case 4:
      cout << "Thank you for using the ATM. Goodbye!" << endl;
      break;
    default:
      cout << "Invalid choice. Please try again." << endl;
    }
  } while (choice != 4);

  return 0;
}

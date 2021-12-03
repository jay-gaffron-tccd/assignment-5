#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "Input_Validation_Extended.h"

using namespace std;


class MenuItem
{
  public:
    string Name;
    double ItemCost;
    string Description;
    char AddLetter;
    char RemoveLetter;
    int Count;
    MenuItem() {}
    MenuItem(string name, double itemCost, char addLetter, char removeLetter, string description)
    {
      Name = name;
      ItemCost = itemCost;
      AddLetter = addLetter;
      RemoveLetter = removeLetter;
      Description = description;
      Count = 0;
    }
};

void populateMenu(vector<MenuItem> &);
void showMenu(vector<MenuItem> &);
void acceptOrder(vector<MenuItem> &);
void printReceipt(vector<MenuItem> &, double, double, double, double);

int main()
{
  char ordering = 'y';

  while (ordering == 'y')
  {
    ordering = 'n';
    vector<MenuItem> wholeMenu;
    populateMenu(wholeMenu); //put some default values in the menu
    showMenu(wholeMenu); //print the current data of the menu on screen
    acceptOrder(wholeMenu);
    cout << "\033[2J\033[1;1H";
    cout << "What would you like to order? ";
    ordering = validateChar(ordering);
  }

  return 0;
}

void populateMenu(vector<MenuItem> &entireMenu)
{
  entireMenu.push_back(MenuItem("Water", 4.00, 'A', 'a', "In a bottle"));
  entireMenu.push_back(MenuItem("Chips", 5.00, 'B', 'b', "Bag of chips"));
  entireMenu.push_back(MenuItem("Jerky", 6.00, 'C', 'c', "Bacon Jerky"));
  entireMenu.push_back(MenuItem("Soda", 7.00, 'D', 'd', "In a can"));
  entireMenu.push_back(MenuItem("Nachos", 8.00, 'E', 'e', "With cheese"));
  entireMenu.push_back(MenuItem("Hot Dog", 9.00, 'F', 'f', "With chips"));
  entireMenu.push_back(MenuItem("Burger", 10.00, 'G', 'g', "With chips"));
}

void showMenu(vector<MenuItem> &m)
{
  cout << fixed << setprecision(2);
  cout << "DrT's Effcient Menu" << endl;
  cout << "ADD \tNAME \t COST \tREMOVE\tCOUNT\tDESC"<<endl;
  for(int i = 0; i < m.size(); i++)
    {
      cout << m[i].AddLetter << ")" << setw(10) << m[i].Name
      << setw(5) << "$" << m[i].ItemCost << setw(5) << "(" << m[i].RemoveLetter
      << ")" << setw(7) << m[i].Count << setw(15) << m[i].Description
      <<endl;
    }
}

void acceptOrder(vector<MenuItem> &m)
{
  char option = '\0';// the user-selected menu item
  double subtotal = 0.0;
  double tip = 0.0;
  bool paymentCredit = false;
  double payment = 0.0;
  double change = -1.0;

  do
  {
    cout << "\nPlease choose an item (x to Exit): ";
    cin >> option;

    for(int i=0; i < m.size(); i++)
    {
      if(option == m[i].AddLetter)
      {
      cout << "\nMenu Item " << m[i].AddLetter << " selected.";
      m[i].Count++; //increment the count by 1
      cout << "\033[2J\033[1;1H"; //clear screen
      cout << "\n1 UP on " << m[i].Name << endl;
      subtotal += m[i].ItemCost; //increment the subtotal by the cost of the item
      showMenu(m); //show the updated menu
      cout << "\nSubtotal: $" << subtotal << endl;
      }
      else if(option == m[i].RemoveLetter)
      {
        cout << "\nRemove Item " << m[i].RemoveLetter << " selected.";
        if(m[i].Count > 0) //subtract if and only if the count is > 0
        {
          m[i].Count--; //decrement the count by 1
          cout << "\033[2J\033[1;1H"; //clear screen
          cout << "\n1 DOWN on " << m[i].Name << endl;
          subtotal -= m[i].ItemCost; //decrement the subtotal by the cost of the item
          showMenu(m); //show the updated menu
          cout << "\nSubtotal: $" << subtotal << endl;
        }
        else //the the user why you blocked item removal
        {  
          cout << "\nItem count must be > 0 to remove: " << m[i].Name << endl;
        }
      }
      else if(option != m[i].AddLetter && option != m[i].RemoveLetter && option != 'x' && option != 'X') //test for all of my valid inputs
      {
        if(i == 0)
        {
         cout << "\nInvalid input (" << option << "). Please try again." << endl;
        }
      }
    }
  }
  while(option != 'x' && option != 'X');

  cout << fixed << setprecision(2);
  cout << "Would you like to add a tip? (15% = $" << (subtotal * 0.15) << ", 20% = $" << (subtotal * 0.2) << ", 25% = $" << (subtotal * .25) << "): " << endl;
  tip = validateDouble(tip);

  cout << "\nThank you for placing your order." << endl;

  cout << "\nCash or Credit? (0 for cash, 1 for credit)";
  cin >> paymentCredit;

  if (!paymentCredit)
  {
    while (change < 0)
    {
      cout << "\nHow much cash are you giving?: ";
      payment = validateDouble(payment);
      change = payment - ((subtotal + tip) * 1.0825);
      if (change < 0)
      {
        cout << "That is not enough!";
      }
    }
  }

  printReceipt(m, subtotal, tip, payment, change);
}

void printReceipt(vector<MenuItem> &m, double subtotal, double tip, double payment, double change)
{
  double tax = ((subtotal + tip) * 0.0825);
  int thing = 0;
  cout << "Receipt" << endl;
  for (size_t i = 0; i < m.size(); i++)
  {
    if (m[i].Count > 0)
    {
      cout << setw(10) << m[i].Name << setw(5) << "$" << m[i].ItemCost << setw(7) << m[i].Count << endl;
    }
  }
  
  cout << "Subtotal: " << subtotal << endl;
  cout << "Tip: " << tip << endl;
  cout << "Tax: " << tax << endl;
  cout << "Total: " << subtotal + tip + tax << endl << endl;
  cout << "Tender: " << (change < 0 ? "Credit" : "Cash") << endl;
  if (change > 0)
  {
    cout << "Amount: $" << payment << endl;
    cout << "Change: $" << change << endl;
  }
  cout << "Press any key to continue: ";
  cin >> thing;
}
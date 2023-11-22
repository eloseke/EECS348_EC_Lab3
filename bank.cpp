/*
Author: Eric Loseke
KUID: 3082068
Date created: 19 November 2023
Lab: EC Lab 3
Purpose: Perform operations on different types of bank accounts using classes
*/

#include <iostream>
#include <iomanip>
using namespace std;

//Class prototypes
class SavingsAccount;
class CurrentAccount;

class Account //Base class
{
	public:
		//Class values
		string accountNumber;
		string accountHolder;
		float balance;

		//Display details of an Account
		void displayDetails()
		{
			cout << *this << endl;
		}

		//Deposit money into an Account
		void deposit(float amount)
		{
			balance += amount;
			cout << "Successfully deposited $" << fixed << setprecision(2) << amount << " into account " << accountNumber << "\n\n";
		}

		//Withdraw money from an Account
		bool withdraw(float amount)
		{
			balance -= amount;
			cout << "Successfully withdrew $" << fixed << setprecision(2) << amount << " from account " << accountNumber << "\n\n";
			return true;
		}

		//Overloads operator <<
		friend ostream &operator<<(ostream &output, const Account &acct)
		{
			output << "Account Details for Account (ID: " << acct.accountNumber;
			output << "):\n\tHolder: " << acct.accountHolder;
			output << "\n\tBalance: $" << fixed << setprecision(2) << acct.balance << endl;
			return output;
		}

		//Overloads operator + for comparing two Accounts
		Account operator+(Account & other_acc)
		{
			Account acc;
			acc.accountNumber = accountNumber; acc.accountHolder = accountHolder; acc.balance = balance;
			float amount;
			cout << "Enter amount to be transferred: $";
			cin >> amount;
			cout << endl;
			if (other_acc.withdraw(amount))
			{
				acc.deposit(amount);
				cout << "Successfully transferred $" << fixed << setprecision(2) << amount << " between accounts\n" << endl;
			}
			else
			{
				cout << "Could not transfer $" << fixed << setprecision(2) << amount << " between accounts\n" << endl;
			}
			return acc;
		}
};

class SavingsAccount: public Account //Derived class of Account
{
	public:
		//Values include values from base class
		//New value: interestRate
		float interestRate;
		
		//Set starting values of a SavingsAccount
		SavingsAccount(string id, string name, float start_balance, float rate)
		{
			accountNumber = id;
			accountHolder = name;
			balance = start_balance;
			interestRate = rate;
		}

		//Override displayDetails method for a SavingsAccount
		void displayDetails()
		{
			cout << *this << endl;
		}

		//Modify withdraw method for a SavingsAccount
		bool withdraw(float amount)
		{
			if (balance-amount < 0)
			{
				cout << "Cannot withdraw $" << fixed << setprecision(2) << amount << ": Savings account must maintain a minimum balance of $0" << "\n\n";
				return false;
			}
			else
			{
				balance -= amount;
				cout << "Successfully withdrew $" << fixed << setprecision(2) << amount << " from account " << accountNumber << "\n\n";
				return true;
			}
		}

		//Overload operator << for a SavingsAccount
		friend ostream &operator<<(ostream &output, const SavingsAccount &acct)
		{
			output << "Account Details for Savings Account (ID: " << acct.accountNumber;
			output << "):\n\tHolder: " << acct.accountHolder;
			output << "\n\tBalance: $" << fixed << setprecision(2) << acct.balance;
			output << "\n\tInterest Rate: " << fixed << setprecision(2) << (acct.interestRate)*100 << "%" << endl;
			return output;
		}

		//Overload operator + for comparing two SavingsAccounts
		SavingsAccount operator+(SavingsAccount & other_acc)
		{
			SavingsAccount acc = SavingsAccount(accountNumber, accountHolder, balance, interestRate);
			float amount;
			cout << "Enter amount to be transferred: $";
			cin >> amount;
			cout << endl;
			if (other_acc.withdraw(amount))
			{
				acc.deposit(amount);
				cout << "Successfully transferred $" << fixed << setprecision(2) << amount << " between accounts\n" << endl;
			}
			else
			{
				cout << "Could not transfer $" << fixed << setprecision(2) << amount << " between accounts\n" << endl;
			}
			return acc;
		}

		//Prototype to overload operator + to compare a SavingsAccount and a CurrentAccount
		SavingsAccount operator+(CurrentAccount & other_acc);
};

class CurrentAccount: public Account //Derived class of Account
{
	public:
		//Values include values from base class
		//New value: overdraftlimit
		float overdraftlimit;

		//Set starting values of a CurrentAccount
		CurrentAccount(string id, string name, float start_balance, float limit)
		{
			accountNumber = id;
			accountHolder = name;
			balance = start_balance;
			overdraftlimit = limit;
		}

		//Override displayDetails method for a CurrentAccount
		void displayDetails()
		{
			cout << *this << endl;
		}

		//Override withdraw method for a CurrentAccount
		bool withdraw(float amount)
		{
			if ((balance-amount) < (overdraftlimit*(-1)))
			{
				cout << "Cannot withdraw $" << fixed << setprecision(2) << amount << ": Overdraft limit exceeded" << "\n\n";
				return false;
			}
			else
			{
				balance -= amount;
				cout << "Successfully withdrew $" << fixed << setprecision(2) << amount << " from account " << accountNumber << "\n\n";
				return true;
			}
		}

		//Overload operator << for a CurrentAccount
		friend ostream &operator<<(ostream &output, const CurrentAccount &acct)
		{
			output << "Account Details for Current Account (ID: " << acct.accountNumber;
			output << "):\n\tHolder: " << acct.accountHolder;
			output << "\n\tBalance: $" << fixed << setprecision(2) << acct.balance;
			output << "\n\tOverdraft Limit: $" << fixed << setprecision(2) << acct.overdraftlimit << endl;
			return output;
		}

		//Overload operator + for comparing two CurrentAccounts
		CurrentAccount operator+(CurrentAccount & other_acc)
		{
			CurrentAccount acc = CurrentAccount(accountNumber, accountHolder, balance, overdraftlimit);
			float amount;
			cout << "Enter amount to be transferred: $";
			cin >> amount;
			cout << endl;
			if (other_acc.withdraw(amount))
			{
				acc.deposit(amount);
				cout << "Successfully transferred $" << fixed << setprecision(2) << amount << " between accounts\n" << endl;
			}
			else
			{
				cout << "Could not transfer $" << fixed << setprecision(2) << amount << " between accounts\n" << endl;
			}
			return acc;
		}

		//Prototype to overload operator + for comparing a CurrentAccount and a SavingsAccount
		CurrentAccount operator+(SavingsAccount & other_acc);
};

//Overload operator + for comparing a SavingsAccount and a CurrentAccount (returns a SavingsAccount)
SavingsAccount SavingsAccount::operator+(CurrentAccount & other_acc)
{
	SavingsAccount acc = SavingsAccount(accountNumber, accountHolder, balance, interestRate);
	float amount;
	cout << "Enter amount to be transferred: $";
	cin >> amount;
	cout << endl;
	if (other_acc.withdraw(amount))
	{
		acc.deposit(amount);
		cout << "Successfully transferred $" << fixed << setprecision(2) << amount << " between accounts\n" << endl;
	}
	else
	{
		cout << "Could not transfer $" << fixed << setprecision(2) << amount << " between accounts\n" << endl;
	}
	return acc;
}

//Overload operator + for comparing a CurrentAccount and a SavingsAccount (returns a CurrentAccount)
CurrentAccount CurrentAccount::operator+(SavingsAccount & other_acc)
{
	CurrentAccount acc = CurrentAccount(accountNumber, accountHolder, balance, overdraftlimit);
	float amount;
	cout << "Enter amount to be transferred: $";
	cin >> amount;
	cout << endl;
	if (other_acc.withdraw(amount))
	{
		acc.deposit(amount);
		cout << "Successfully transferred $" << fixed << setprecision(2) << amount << " between accounts\n" << endl;
	}
	else
	{
		cout << "Could not transfer $" << fixed << setprecision(2) << amount << " between accounts\n" << endl;
	}
	return acc;
}

int main() //Run the program
{
	//Create accounts
	SavingsAccount savings("S123", "John Doe", 1000, 0.02);
	CurrentAccount current("C456", "Jane Doe", 2000, 500);

	//Display initial details
	savings.displayDetails();
	current.displayDetails();

	//Deposit and withdraw
	savings.deposit(500);
	current.withdraw(1000);

	//Display details after deposit and withdraw
	savings.displayDetails();
	current.displayDetails();
	
	//Transfer money between accounts (amount transferred is from user input)
	current = current + savings;

	//Display details after transfer
	savings.displayDetails();
	current.displayDetails();
	
	return 0;
}

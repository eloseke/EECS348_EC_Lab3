#include <iostream>
#include <iomanip>
using namespace std;

class SavingsAccount;
class CurrentAccount;

class Account
{
	public:
		string accountNumber;
		string accountHolder;
		float balance;
		void displayDetails()
		{
			cout << *this << endl;
		}
		void deposit(float amount)
		{
			balance += amount;
			cout << "Successfully deposited $" << fixed << setprecision(2) << amount << " into account " << accountNumber << "\n\n";
		}
		bool withdraw(float amount)
		{
			balance -= amount;
			cout << "Successfully withdrew $" << fixed << setprecision(2) << amount << " from account " << accountNumber << "\n\n";
			return true;
		}
		friend ostream &operator<<(ostream &output, const Account &acct)
		{
			output << "Account Details for Account (ID: " << acct.accountNumber;
			output << "):\n\tHolder: " << acct.accountHolder;
			output << "\n\tBalance: $" << fixed << setprecision(2) << acct.balance << endl;
			return output;
		}
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

class SavingsAccount: public Account
{
	public:
		float interestRate;
		SavingsAccount(string id, string name, float start_balance, float rate)
		{
			accountNumber = id;
			accountHolder = name;
			balance = start_balance;
			interestRate = rate;
		}
		void displayDetails()
		{
			cout << *this << endl;
		}
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
		friend ostream &operator<<(ostream &output, const SavingsAccount &acct)
		{
			output << "Account Details for Savings Account (ID: " << acct.accountNumber;
			output << "):\n\tHolder: " << acct.accountHolder;
			output << "\n\tBalance: $" << fixed << setprecision(2) << acct.balance;
			output << "\n\tInterest Rate: " << fixed << setprecision(2) << (acct.interestRate)*100 << "%" << endl;
			return output;
		}
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
		SavingsAccount operator+(CurrentAccount & other_acc);
};

class CurrentAccount: public Account
{
	public:
		float overdraftlimit;
		CurrentAccount(string id, string name, float start_balance, float limit)
		{
			accountNumber = id;
			accountHolder = name;
			balance = start_balance;
			overdraftlimit = limit;
		}
		void displayDetails()
		{
			cout << *this << endl;
		}
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
		friend ostream &operator<<(ostream &output, const CurrentAccount &acct)
		{
			output << "Account Details for Current Account (ID: " << acct.accountNumber;
			output << "):\n\tHolder: " << acct.accountHolder;
			output << "\n\tBalance: $" << fixed << setprecision(2) << acct.balance;
			output << "\n\tOverdraft Limit: $" << fixed << setprecision(2) << acct.overdraftlimit << endl;
			return output;
		}
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
		CurrentAccount operator+(SavingsAccount & other_acc);
};

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

int main()
{
	SavingsAccount savings("S123", "John Doe", 1000, 0.02);
	CurrentAccount current("C456", "Jane Doe", 2000, 500);

	savings.displayDetails();
	current.displayDetails();

	savings.deposit(500);
	savings.withdraw(3000);

	savings.displayDetails();
	current.displayDetails();
	
	current = current + savings;

	savings.displayDetails();
	current.displayDetails();
	
	return 0;
}
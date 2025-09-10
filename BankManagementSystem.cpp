
//===================================================================
//Welcome to  Bank Management System  Project <3
//===================================================================

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <iomanip>
#include <fstream>
using namespace std;

enum enOp { Show = 1, Add = 2, Delete = 3, Update = 4, Search = 5, Transaction, Exit = 7 };

struct stClient {

	string accountNumber = "";
	string pinCode = "";
	string name = "";
	string phoneNumber = "";
	double Balance = 0.0;

	bool flagForDelete = false;//use this to delete.

};
void ShowMainMenu()
{
	system("cls");
	cout << "\n=====================================\n";
	cout << "\t   Main Menue Screen\n";
	cout << "=====================================\n";
	cout << "[1] Show Client List.\n";
	cout << "[2] Add New Client.\n";
	cout << "[3] Delete Client.\n";
	cout << "[4] Update Client Info.\n";
	cout << "[5] Find Client.\n";
	cout << "[6] Transactions.\n";
	cout << "[7] Exit.\n";
	cout << "=====================================\n";

}
void showTransactionsMenu() {
	system("cls");
	cout << "====================================\n";
	cout << "      Transactions Menue Screen\n";
	cout << "====================================\n\n";


	cout << "[1] Deposit.\n";
	cout << "[2] Withdraw.\n";
	cout << "[3] Total Balances.\n";
	cout << "[4] Main Menue.\n\n";
}

vector <string> spiltString(string Line, string delim = "#//#")
{
	string sWord;
	vector <string> vWord;
	int pos;

	while ((pos = Line.find(delim)) != string::npos) {

		sWord = Line.substr(0, pos);
		if (sWord != "")
		{
			vWord.push_back(sWord);
		}
		Line.erase(0, pos + delim.length());
	}
	if (Line != "")
	{
		vWord.push_back(Line);
	}
	return vWord;

}

stClient  convertLineToClient(string Line) {

	vector<string> vSpiletClientData = spiltString(Line);
	stClient stClientData;

	stClientData.accountNumber = vSpiletClientData[0];
	stClientData.pinCode = vSpiletClientData[1];
	stClientData.name = vSpiletClientData[2];
	stClientData.phoneNumber = vSpiletClientData[3];
	stClientData.Balance = stod(vSpiletClientData[4]);

	return stClientData;
}

vector <stClient> loadStClientsFromFile()
{

	fstream MyFile;
	MyFile.open("client.txt", ios::in); // just Read.

	if (MyFile.is_open())
	{
		string Line;
		vector <stClient> vClient;

		while (getline(MyFile, Line))
		{

			vClient.push_back(convertLineToClient(Line));

		}
		MyFile.close();
		return vClient;
	}


}

void PrintClientData(stClient S) {

	cout << "|" << left << setw(20) << S.accountNumber;
	cout << "|" << left << setw(20) << S.pinCode;
	cout << "|" << left << setw(30) << S.name;
	cout << "|" << left << setw(20) << S.phoneNumber;
	cout << "|" << left << setw(20) << S.Balance << endl;

}

stClient addClientInfo(string sAccountNumber)
{

	stClient Client;

	Client.accountNumber = sAccountNumber;

	cout << "PIN Code: ";
	getline(cin >> ws, Client.pinCode);
	cout << "Name: ";
	getline(cin, Client.name);
	cout << "Phone Number: ";
	getline(cin, Client.phoneNumber);
	cout << "Balance: ";
	cin >> Client.Balance;


	return Client;
}


string  convertClientToLine(stClient Client, string delim = "#//#")
{

	string sWord = "";

	sWord += Client.accountNumber + delim;
	sWord += Client.pinCode + delim;
	sWord += Client.name + delim;
	sWord += Client.phoneNumber + delim;
	sWord += to_string(Client.Balance);
	return sWord;

}

void addLineToFile(string Line) {

	fstream MyFile;

	MyFile.open("client.txt", ios::out | ios::app);

	if (MyFile.is_open())
	{

		MyFile << Line << endl;

	}

}


bool checkDuplicateAccountNumber(string newClient, vector <stClient> Client) {


	for (stClient& S : Client)
	{

		if (newClient == S.accountNumber)
		{
			return true;

		}
	}
	return false;
}


bool FindAccountNumber(string newClient, vector <stClient> Client, stClient& stClientFounded) {


	for (stClient& S : Client)
	{

		if (newClient == S.accountNumber)
		{
			stClientFounded = S;
			return true;

		}
	}
	return false;
}

void PrintFoundedData(stClient S) {
	cout << "\n the following are the client details :\n";

	cout << "\n------------------------------------------------\n";

	cout << "Account Number: " << S.accountNumber << endl;
	cout << "PIN code      : " << S.pinCode << endl;
	cout << "Name Client   : " << S.name << endl;
	cout << "Phone Number  : " << S.phoneNumber << endl;
	cout << "Balance       : " << S.Balance << endl;

	cout << "\n------------------------------------------------\n";
}

void printStyleFindScreen() {

	cout << "\n\n==================================================== \n\n";

	cout << "  	    	Find Client Screen						   ";

	cout << "\n\n==================================================== \n\n";

}

void StylingScreenAdd() {

	cout << "\n==================================================== \n\n";

	cout << "  	 	   Add Client	Screen						   ";

	cout << "\n\n==================================================== \n\n";
}
void StylingScreenDelete() {

	cout << "\n==================================================== \n\n";

	cout << "  	 	  Delete Client	Screen						   ";

	cout << "\n\n==================================================== \n\n";
}
void StylingScreenUpdate() {

	cout << "\n==================================================== \n\n";

	cout << "  	 	  Update Client	Screen						   ";

	cout << "\n\n==================================================== \n\n";
}

void GiveFlagToDelete(string Client, vector<stClient>& vClient)
{

	for (stClient& S : vClient)
	{
		if (Client == S.accountNumber)
		{

			S.flagForDelete = true;

		}
	}


}

void  DeletFromFileAndUpdate(vector <stClient>& vClient) {

	fstream MyFile;

	MyFile.open("client.txt", ios::out);

	if (MyFile.is_open())
	{

		for (stClient& S : vClient)
		{

			if (S.flagForDelete == false)
			{

				MyFile << convertClientToLine(S) << endl;

			}

		}
		MyFile.close();

	}
	else
	{
		cout << "file dosent open";
	}


}

void  UpdateTheFileFromVectorClient(vector <stClient>& vClient) {

	fstream MyFile;

	MyFile.open("client.txt", ios::out);

	if (MyFile.is_open())
	{

		for (stClient& S : vClient)
		{



			MyFile << convertClientToLine(S) << endl;


		}
		MyFile.close();

	}



}

void AskUpdateClientInfo(string sAccountNumber, stClient& Client)
{


	cout << endl;
	Client.accountNumber = sAccountNumber;

	cout << "PIN Code: ";
	getline(cin >> ws, Client.pinCode);
	cout << "Name: ";
	getline(cin, Client.name);
	cout << "Phone Number: ";
	getline(cin, Client.phoneNumber);
	cout << "Balance: ";
	cin >> Client.Balance;



}

void UpdateTheClientByVector(string AccountNumber, vector<stClient>& Client) {


	for (stClient& S : Client) {

		if (S.accountNumber == AccountNumber)
		{
			AskUpdateClientInfo(AccountNumber, S);
			break;
		}

	}


}


//Update data screen.
void UpdateDataScreen() {

	stClient Client;
	vector<stClient>vClient = loadStClientsFromFile();
	string AccountNumber;
	char sure = 'n';
	StylingScreenUpdate();
	cout << "Enter Acount Number: ";
	cin >> AccountNumber;


	if (FindAccountNumber(AccountNumber, vClient, Client))
	{
		PrintFoundedData(Client);

		cout << "Are sure want Update this client y/n ? ";
		cin >> sure;
		if (tolower(sure) == 'y')
		{
			UpdateTheClientByVector(AccountNumber, vClient);
			UpdateTheFileFromVectorClient(vClient);


			cout << "Update completed successfully." << endl;
		}
		else
		{
			cout << "Update canceled." << endl;

		}

	}
	else
	{
		cout << "Account number (" << AccountNumber << ") not founded !";
	}


}

//Delete screen .
void DeleteClientScreen() {
	stClient Client;
	vector<stClient>vClient = loadStClientsFromFile();
	string AccountNumber;
	char sure = 'n';
	StylingScreenDelete();
	cout << "Enter Acount Number: ";
	cin >> AccountNumber;


	if (FindAccountNumber(AccountNumber, vClient, Client))
	{
		PrintFoundedData(Client);

		cout << "Are sure want delete this client y/n ? ";
		cin >> sure;
		if (tolower(sure) == 'y')
		{

			GiveFlagToDelete(AccountNumber, vClient);

			DeletFromFileAndUpdate(vClient);




			cout << "Deletion completed successfully." << endl;
		}
		else
		{
			cout << "Deletion canceled." << endl;

		}

	}
	else
	{
		cout << "Account number (" << AccountNumber << ") not founded !";
	}


}

//Find screen .
void FindClientScreen()
{
	printStyleFindScreen();
	string AccountNumber = "";
	cout << "enter account number looking for : ";
	cin >> AccountNumber;

	vector <stClient> vClient = loadStClientsFromFile();
	stClient Client;
	if (FindAccountNumber(AccountNumber, vClient, Client))
	{
		PrintFoundedData(Client);
	}
	else
	{
		cout << "Account number (" << AccountNumber << ") not founded !";
	}


}

//Print Screen function
void PrintDataScreen() {
	vector <stClient> Client = loadStClientsFromFile();
	if (Client.size() == 0)
	{
		cout << "	\n\n		  		  There is no clients. ";
	}
	else
	{
		cout << "	\n\n				  Client List (" << Client.size() << ") Clinets.";
	}

	cout << "\n_____________________________________________________________________________________________________\n\n";
	cout << "|" << left << setw(20) << "Account Number";
	cout << "|" << left << setw(20) << "PIN Code";
	cout << "|" << left << setw(30) << "Name client";
	cout << "|" << left << setw(20) << "Phon Number";
	cout << "|" << left << setw(20) << "Balance";
	cout << "\n_____________________________________________________________________________________________________\n";

	for (stClient& S : Client)
	{
		PrintClientData(S);

	}

	cout << "\n_____________________________________________________________________________________________________\n";
}

//Add clients to System
void AddClientScreem()
{


	string AccountNumber = "";
	char repeatInput = 'n';
	char repeatAdd = 'n';

	StylingScreenAdd();

	do
	{

		do
		{

			cout << "enter account number: ";
			cin >> AccountNumber;

			vector<stClient> vClient = loadStClientsFromFile();

			if (!checkDuplicateAccountNumber(AccountNumber, vClient))
			{
				stClient Client = addClientInfo(AccountNumber);
				string Line = convertClientToLine(Client);
				addLineToFile(Line);
				cout << "Added successfully.\n";
				repeatInput = 'n';
			}
			else
			{
				cout << "Duplicate Account Number. Try another. ";
				repeatInput = 'y';
			}
		} while (repeatInput == 'y');

		cout << "do you want add clients agine y/n :  ";
		cin >> repeatAdd;



	} while (tolower(repeatAdd) == 'y');

}



int readNumber() {
	int num;
	do
	{
		cout << "Choose what do you want to do? [1 to 7]: ";
		cin >> num;
	} while (num > 7 || num < 1);
	return num;
}


void GoBackToMainMenu() {

	cout << "\nPress any key to go back to the Main Menu...";
	system("pause>0");

	ShowMainMenu();
}
void anyKayToCleanTransaction() {

	cout << "\nPress any key to go back to the Main Menu Transactions ...";
	system("pause>0");

}



enum enTransaction { Deposit = 1, Withdraw = 2, TotalBalance = 3, MainList = 4 };

void UpdateTheClientDepositByVector(string AccountNumber, vector<stClient>& Client, double& add) {


	for (stClient& S : Client) {

		if (S.accountNumber == AccountNumber)
		{
			cout << "Please enter deposit amount: ";
			cin >> add;
			S.Balance = S.Balance + add;

			break;
		}

	}


}
void styleDepositBalance() {

	cout << "\n==================================================== \n\n";

	cout << "  	 	   Deposit amount  Screen						   ";

	cout << "\n\n==================================================== \n\n";
}
//Deposit screen
void DepositBalance() {
	styleDepositBalance();
	vector <stClient> vClientData = loadStClientsFromFile();
	string AccountNumber = "";
	stClient Client;
	char keepGoing = 'y';
	char AreSure = 'y';
	double amount;

	while (tolower(keepGoing) == 'y') {


		cout << "Enter AccountNumber ?";
		getline(cin >> ws, AccountNumber);

		if (FindAccountNumber(AccountNumber, vClientData, Client))
		{
			PrintFoundedData(Client);
			cout << "Confirm operation completion? (y/n) ";
			cin >> AreSure;
			if (tolower(AreSure) == 'y')
			{
				UpdateTheClientDepositByVector(AccountNumber, vClientData, amount);
				UpdateTheFileFromVectorClient(vClientData);
				cout << "Deposit completed successfully: +" << amount << endl;

			}
			else
			{
				cout << "Operation canceled." << endl;
			}

			keepGoing = 'n';
		}
		else
		{
			cout << "Error: Client Number (" << AccountNumber << ") does not exist." << endl;
			keepGoing = 'y';

		}
	}


}

void UpdateTheClientWithdrawByVector(string AccountNumber, vector<stClient>& Client, double& withdrawAmount) {


	for (stClient& S : Client) {

		if (S.accountNumber == AccountNumber)
		{
			cout << "Enter how amount withdraw: ";
			cin >> withdrawAmount;

			if (withdrawAmount <= S.Balance)
			{
				S.Balance = S.Balance - withdrawAmount;
			}
			else
			{

				if (withdrawAmount > S.Balance) {
					cout << "Amount exceeds the current balance. Cannot withdraw." << endl;
				}
				else {
					cout << "Withdrawal amount must be positive." << endl;
				}
				withdrawAmount = 0;
			}


			break;
		}

	}


}
void styleWithdrawBalance() {

	cout << "\n==================================================== \n\n";

	cout << "  	 	   Withdraw amount  Screen						   ";

	cout << "\n\n==================================================== \n\n";
}
// With draw Balance
void WithdrawBalance() {

	styleWithdrawBalance();
	vector<stClient> vClientData = loadStClientsFromFile();
	string AccountNumber = "";
	stClient Client;
	char keepGoing = 'y';
	char AreSure = 'y';
	double amount;

	while (keepGoing == 'y') {
		cout << "Enter Account Number: ";
		getline(cin >> ws, AccountNumber);

		if (FindAccountNumber(AccountNumber, vClientData, Client)) {
			PrintFoundedData(Client);
			cout << "Confirm operation completion? (y/n): ";
			cin >> AreSure;

			if (tolower(AreSure) == 'y') {
				UpdateTheClientWithdrawByVector(AccountNumber, vClientData, amount);
				UpdateTheFileFromVectorClient(vClientData);
				cout << "Withdrawal completed successfully: " << amount << endl;
			}
			else {
				cout << "Operation canceled." << endl;
			}

			keepGoing = 'n';
		}
		else {
			cout << "Error: Client Number (" << AccountNumber << ") does not exist." << endl;
			keepGoing = 'y';
		}
	}
}

double SumTotalBalance(vector<stClient>  Client) {

	double sum = 0;
	for (stClient& S : Client) {


		sum += S.Balance;

	}
	return sum;

}
void StyleTotalBalances(double Total) {

	cout << "\n==================================================== \n\n";

	cout << "          Total Balances " << Total << " $         ";

	cout << "\n\n==================================================== \n\n";

}

// Show Total Balances
void ShowTotalBalances() {
	double Total;
	vector <stClient> vClient = loadStClientsFromFile();
	Total = SumTotalBalance(vClient);
	PrintDataScreen();
	StyleTotalBalances(Total);

}


enTransaction readChosses() {

	showTransactionsMenu();
	int num;

	do
	{
		cout << "Choose what do you want to do? [1 to 4]? ";
		cin >> num;

	} while (num > 4 || num < 1);
	return enTransaction(num);

}

void TransactionList()
{
	bool KeepGoing = true;


	while (KeepGoing) {
		enTransaction Option = readChosses();

		switch (Option)
		{

		case Deposit:
			system("cls");
			DepositBalance();
			anyKayToCleanTransaction();
			break;

		case Withdraw:
			system("cls");
			WithdrawBalance();
			anyKayToCleanTransaction();
			break;

		case TotalBalance:
			system("cls");
			ShowTotalBalances();
			anyKayToCleanTransaction();
			break;

		case MainList:
			system("cls");
			KeepGoing = false;
			break;

		default:
			break;
		}


	}


}



void Main_List() {

	bool KeepGoing = true;
	ShowMainMenu();
	while (KeepGoing)
	{


		int MenuNum = readNumber();
		enOp enMenuNum = enOp(MenuNum);

		switch (enMenuNum)
		{
		case Show:
			system("cls");
			PrintDataScreen();
			GoBackToMainMenu();
			break;

		case Add:
			system("cls");
			AddClientScreem();
			GoBackToMainMenu();


			break;

		case Delete:
			system("cls");
			DeleteClientScreen();
			GoBackToMainMenu();

			break;

		case Update:
			system("cls");
			UpdateDataScreen();
			GoBackToMainMenu();

			break;
		case Search:
			system("cls");
			FindClientScreen();
			GoBackToMainMenu();


			break;

		case Transaction:
			TransactionList();
			ShowMainMenu();
			break;

		case Exit:
			system("cls");
			cout << "\n =======================\n\n";
			cout << "      Exiting...\n";
			cout << "\n =======================\n";

			KeepGoing = false;
			system("pause>0");
			break;


		}
	}

}

void  DefultClientsData() {



	stClient client1;
	client1.accountNumber = "A101";
	client1.pinCode = "1234";
	client1.name = "Omar Hassan Al-Masri";
	client1.phoneNumber = "01095412367";
	client1.Balance = 12500.75;
	addLineToFile(convertClientToLine(client1));

	stClient client2;
	client2.accountNumber = "A102";
	client2.pinCode = "2345";
	client2.name = "Ahmad Khaled Al-Haddad";
	client2.phoneNumber = "01189234512";
	client2.Balance = 3150.20;
	addLineToFile(convertClientToLine(client2));

	stClient client3;
	client3.accountNumber = "A103";
	client3.pinCode = "3456";
	client3.name = "Sara Mahmoud Al-Tamimi";
	client3.phoneNumber = "01276342891";
	client3.Balance = 780.00;
	addLineToFile(convertClientToLine(client3));

	stClient client4;
	client4.accountNumber = "A104";
	client4.pinCode = "4567";
	client4.name = "Yousef Adel Al-Khatib";
	client4.phoneNumber = "01098765432";
	client4.Balance = 48900.00;
	addLineToFile(convertClientToLine(client4));

	stClient client5;
	client5.accountNumber = "A105";
	client5.pinCode = "5678";
	client5.name = "Mona Fares Al-Najjar";
	client5.phoneNumber = "01121122334";
	client5.Balance = 9400.25;
	addLineToFile(convertClientToLine(client5));

	stClient client6;
	client6.accountNumber = "1234";
	client6.pinCode = "000034";
	client6.name = "Ahmad Sarayrah";
	client6.phoneNumber = "01121122334";
	client6.Balance = 10000000.25;
	addLineToFile(convertClientToLine(client6));

}

void AddClientIfFileIsEmpty() {


	if (loadStClientsFromFile().empty()) {

		DefultClientsData();
	}

}
void EnsureFileExists() {
	fstream MyFile;


	MyFile.open("client.txt", ios::in);

	if (MyFile.fail()) {
		MyFile.clear();

		MyFile.open("client.txt", ios::out);

	}


	MyFile.close();
}



int main() {

	// Bank Management System  Project Start Up

	EnsureFileExists();
	AddClientIfFileIsEmpty();
	Main_List();

	return 0;
}

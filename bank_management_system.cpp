#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>
using namespace std;

class Account{
    private:
        long long accountNumber;
        double  balance;
        string accountHolderName;
    public:
         // creating a constructor
        Account(int accNum, string name , double initialBalance){
            accountNumber = accNum;
            accountHolderName = name;
            balance = initialBalance;
        }
        //saving information to a file 
        void saveToFile(ofstream &outFile){
            outFile << accountNumber <<endl;
            outFile << accountHolderName <<endl;
            outFile << balance <<endl;
        }
        //load account data from the file 
        void loadAccountData(ifstream &inFile){
            inFile >> accountNumber;
            inFile.ignore();
            getline(inFile,accountHolderName);
            inFile>>balance;
        }
        //accesing the accountNumber from the private specifier
        int getAccountNumber(){
            return accountNumber;
        }
        //deposit func
        void diposit(double amount){
            if(amount > 0){
                balance += amount;
                cout<<"Deposited  amount "<<amount<<" succesfully. New balance is "<<balance<<endl;
            }else{
                cout<<"Deposit failed!!. Please Deposit amount more than 0."<<endl;
            }
        }
        //withdraw func
        void withdraw(double amount){
            if(amount > balance){
                cout<<"Insufficient balance!!. Withdrawal fail."<<endl;
            }else{
                balance-=amount;
                cout<<"Withdraw successful of amount "<<amount<<" . Total remaining balance is "<<balance<<endl;
            }
        }

        // func to display account detail's 
        void displayDetails(){
            cout<<"The account holder name is : "<<accountHolderName<<endl;
            cout<<"The account number is : "<<accountNumber<<endl;
            cout<<"The account balance is : "<<balance<<endl;
        }
};
// to find if the account exist
int findAccount(vector<Account>& accounts , int accountNumber){
    for(int i =0; i<accounts.size();i++){
        if(accounts[i].getAccountNumber()== accountNumber){
            return i;
        }
    }
    return -1;
}
//deleting account
void deleteAccountNumber(vector<Account> &account , long long accountNumber){
    int index = findAccount(account,accountNumber);
    if(index!=-1){
        account.erase(account.begin()+index);
        cout<<"The deletion of the account number "<<accountNumber<<" is successfully completed "<<endl;
    }else{
        cout<<"Account number not found!"<<endl;
    }
}
//saving data
void saveAccountsToFile(vector<Account>&accounts){
    ofstream outFile("account.txt");
    for(int i=0;i<accounts.size();i++){
        accounts[i].saveToFile(outFile);
    }
    outFile.close();
}
//loading file
void loadAccountsFromFile(vector<Account> &accounts) {
    ifstream inFile("account.txt");

    if (!inFile) {
        cout << "No previous account data found.\n";
        return;
    }

    while (!inFile.eof()) {
        Account acc(0, "", 0.0);  // Temporary account object
        acc.loadAccountData(inFile);
        if (inFile) {
            accounts.push_back(acc);
        }
    }

    inFile.close();
}

int main(){
    // vector for keeping multiple accounts
    vector<Account>accounts;

    loadAccountsFromFile(accounts);//loading file

    int ch;
    string accountHolderName;
    long long accountNumber;
    double initialBalance;
    double amount;

    do{
    cout<<endl<<" *****Welcome to the Bank Management System ***** "<<endl;
    cout<<" 1). Create new account  "<<endl;
    cout<<" 2). View Account details "<<endl;
    cout<<" 3). Deposit  "<<endl;
    cout<<" 4). Withdraw "<<endl;
    cout<<" 5). Delete account "<<endl;
    cout<<" 6). Exit  "<<endl;
    cout<<endl<<"Enter choice : ";
    cin>>ch;

    switch(ch){
        case 1:
            cout<<"Enter the Account holder name ";
            cin.ignore();
            getline(cin,accountHolderName);
            cout<<"Enter Account number ";
            cin>>accountNumber;
            cout<<"Enter the initial balance ";
            cin>>initialBalance;

            accounts.push_back(Account(accountNumber,accountHolderName,initialBalance));
            cout<<"Account created successfully. Thank you for creating a Account"<<endl;
            break;
        case 2:{
            cout<<"Enter the account number ";
            cin>>accountNumber;

            int index = findAccount(accounts,accountNumber);
            if(index!=-1){
                accounts[index].displayDetails();
            }else{
                cout<<"Account not found !!"<<endl;
            }
            break;}
        case 3:{
            cout<<"Enter the account number ";
            cin>>accountNumber;

            int index = findAccount(accounts,accountNumber);
            if(index!=-1){
                cout<<"Enter the amount to deposit ";
                cin>>amount;
                accounts[index].diposit(amount);
            }else{
                cout<<"Account not found !!"<<endl;
            }
            
            break;}
        case 4:{
            cout<<"Enter the account number ";
            cin>>accountNumber;

            int index = findAccount(accounts,accountNumber);
            if(index!=-1){
               cout<<"Enter the amount to withdraw ";
               cin>>amount;
               accounts[index].withdraw(amount);
            }else{
                cout<<"Account not found !!"<<endl;
            }
            break;}

        case 5:
            cout<<"Enter the account Number ";
            cin>>accountNumber;
            deleteAccountNumber(accounts,accountNumber);
            saveAccountsToFile(accounts);
            break;
        case 6:
        saveAccountsToFile(accounts);
            cout<<"Existing the system have a pleasant day !!"<<endl;
            break;
        default :
            cout<<"Please enter a valid choice!! "<<endl;   
    }

    }while(ch!=5);

    return 0;
}
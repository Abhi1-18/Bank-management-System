#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

class Account{
    private:
        long long accountNumber;
        double  balance;
        string accountHolderName;
    public:// creating a constructor
        Account(int accNum, string name , double initialBalance){
            accountNumber = accNum;
            accountHolderName = name;
            balance = initialBalance;
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
int main(){
    // vector for keeping multiple accounts
    vector<Account>accounts;

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
    cout<<" 5). Exit  "<<endl;
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
            cout<<"Existing the system have a pleasant day !!"<<endl;
            break;
        default :
            cout<<"Please enter a valid choice!! "<<endl;   
    }

    }while(ch!=5);

    return 0;
}
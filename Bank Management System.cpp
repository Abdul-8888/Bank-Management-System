#include <iostream>
#include <stdlib.h>
#include <string>
#include <conio.h>
#include <fstream>
using namespace std;

/*
    Id: manager, customer, employee = user
    Password: manager = 1111
              employee = 2222
              customer = 3333
*/

//_____________Prototypes______________
void header();
char whichUser();
int menu( int user_password );
void hireEmployee();
void fireEmployee( string employee );
void displayEmployees();
void ageSort( int start );
void workSort( int start );
void deleteCustomer( string customer );
void displayCustomers();
void customerSort( int start );
void addCustomer();
void updateCustomer( string changes );
void cashDeposit( string customer );
void cashWithdraw( string customer );
void cashTransfer( string recipient, int transfer_cash, string customer );
void closeAccount( string customer );
void load();
string parseRecord(string record, int field);
void store();

//_____________Data Structures______________
const int MAX_RECORDS = 50;
string employee_name [MAX_RECORDS];
string education [MAX_RECORDS];
string customer_name [MAX_RECORDS];
int age [MAX_RECORDS];
int experience [MAX_RECORDS];
int working_hour [MAX_RECORDS];
int in_account [MAX_RECORDS];
char user, changes_character;
string user_id, changes, employee, customer, recipient, issue;
int choice, user_password, cash_inflow = 0, cash_outflow = 0, cash_change, transfer_cash, employeeCount = 0, customerCount = 0;

//_____________Main Function______________
main()
{
    ////// assigning values for proper functions
    for (int i = 0; i < MAX_RECORDS; i++)
    {
        working_hour[i] = 0;
        age[i] = 0;
        in_account[i] = 0;
    }
    ////////////////////////////////////////////

    load();

    while ( true )//start of outer loop
    {
        header();
        user = whichUser();

        if (user == 'm') //user login
        {
            cout<<"Enter your manager id..";
            cin>>user_id;
            cout<<"Enter your password..";
            cin>>user_password;
        }

        else if (user == 'e')
        {
            cout<<"Enter employee name: ";
            cin >>employee;
            cout<<"Enter your employee ID: ";
            cin>>user_id;
            cout<<"Enter your password: ";
            cin>>user_password;
        }

        else if (user == 'c')
        {
            cout <<"Enter your name: ";
            cin >> customer;
            cout <<"Enter your customer ID: ";
            cin >>user_id;
            cout <<"Enter your pasword: ";
            cin >>user_password;
        }

        else if (user == 'x')
        {
            break;
        }
        
        else
        {
            cout <<"Invalid user."<<endl <<"Press a key to continue."<<endl;
            getch();
            system("cls");
            continue;
        }

        while ( true )//inner loop
        {
            if ( user_id == "user" && ( user_password == 1111 || user_password == 2222 || user_password == 3333 ) )
            {
                choice = menu ( user_password );
            }
            else
            {
                cout <<"Invalid ID or password." <<endl;
                cout <<"Press a key to continue." <<endl;
                getch();
                system("cls");
                break;
            }

            if( user_password == 1111 && choice < 13 && choice > 0 )//start of manager
            {
                if (choice == 1)//Hiring a new employee
                {
                    hireEmployee();

                }//end of hiring

                else if (choice == 2)//firing an employee
                {
                    cout <<"Enter name of employee: ";
                    cin >>employee;
                    fireEmployee ( employee );

                }//end of firing

                else if (choice == 3)//checking employee list
                {
                    displayEmployees();

                }//end og checking employee list

                else if (choice == 4)//sorting by age
                {
                    for (int i = 0; i < employeeCount; i++)
                    {
                        ageSort( i );
                    }

                    cout <<"Name \t Age \t Experience \t Education \t Working Hour" <<endl;

                    for (int i = 0; i < employeeCount; i++)
                    {
                        if ( age[i] != -1 && age[i] != 0 )
                        {
                            cout <<employee_name[i] <<" \t " <<age[i] <<" \t\t " <<experience[i] <<" \t\t " <<working_hour[i] <<endl;
                        }
                    }
                }//end of sorting by age

                else if (choice == 5)//sorting by work
                {
                    for ( int i = 0; i < employeeCount; i++)
                    {
                        workSort( i );
                    }

                    cout <<"Name \t Age \t Experience \t Education \t Working Hour" <<endl;

                    for (int i = 0; i < employeeCount; i++)
                    {
                        if ( working_hour[i] != 0 && working_hour[i] != -1 )
                        {
                            cout <<employee_name[i] <<" \t " <<age[i] <<" \t\t " <<experience[i] <<" \t\t " <<working_hour[i] <<endl;
                        }   
                    }
                }//end of sorting by work

                else if (choice == 6)//deleting customer
                {
                    cout <<"Enter customer you want to delete: ";
                    cin >>customer;
                    deleteCustomer( customer );

                }// end of deleting customers

                else if (choice == 7)//checking cash outflow
                {
                    cout<<"Cash outflow is: "<<cash_outflow <<endl;
                }//ending cash flow check

                else if (choice == 8)//checking cash inflow
                {
                    cout<<"Cash inflow today is: "<<cash_inflow <<endl;
                }//ending cash inflow

                else if (choice == 9)//customer issues
                {
                    if( issue[0] != '\0' )
                    {
                        cout<<issue<<endl;
                    }
                    else
                    {
                    cout <<"No issues reported."<<endl;
                    }
                }//ending customer issues

                else if (choice == 10)//checking customer list
                {
                    displayCustomers();

                }//end of checking customer list

                else if (choice == 11)//sorting customers
                {
                    for (int i = 0; i < customerCount; i++)
                    {
                        customerSort( i );
                    }

                    cout <<"Name \t Account Balance" <<endl;

                    for (int i = 0; i < customerCount; i++)
                    {
                        if ( in_account[i] != -1 && in_account != 0 )
                        {
                            cout <<customer_name[i] <<" \t " <<in_account[i] <<endl;
                        }
                    }
                }//end of customer sorting

                else if (choice == 12)//exiting
                {
                    system("cls");
                    break;

                }//end of exiting

            }//end of manager

            else if ( user_password == 2222 && choice > 0 && choice < 5 )//start of employee
            {
                if (choice == 1)//adding new customer
                {
                    addCustomer();

                }//ending adding new customer

                else if (choice == 2)//updating an existing account
                {
                    cout <<"Enter the name of customer: ";
                    cin >>changes;
                    updateCustomer( changes );

                }//end of updating customer

                else if ( choice == 3)//update working hours
                {
                    for (int i = 0; i < employeeCount; i++)
                    {
                        if( employee == employee_name[i] )
                        {
                            cout <<"Enter your today's working hour: ";
                            cin >>working_hour[i];
                            break;
                        }
                        if ( i == employeeCount - 1 )
                        {
                            cout <<"No employee with this name yet."<<endl;
                        }
                    }
                }//end of updating working hours
 
                else if (choice == 4)//exiting
                {
                    system("cls");
                    break;

                }//end of exiting

            }//end of employee

            else if ( user_password == 3333 && choice > 0 && choice < 8 )//start of customer
            {
                if (choice == 1)//checking account balance
                {
                    for ( int i = 0; i < customerCount; i++)
                    {
                        if (customer == customer_name[i])
                        {
                            cout <<"Your balance is " <<in_account[i] <<endl;
                            break;
                        }

                        if ( i == customerCount - 1 )
                        {
                            cout <<"No customer with this name.";
                        }
                    }
                }//end of checking account balance

                else if (choice == 2)//depositing cash in account
                {
                    cashDeposit( customer );

                }//end of cash deposit

                else if (choice == 3)//withdraw cash from account
                {
                    cashWithdraw( customer );

                }//end of cash withdraw

                else if (choice == 4)//transfer cash from account
                {
                    cout <<"Enter recipient's name: ";
                    cin >>recipient;
                    cout <<"Enter the ammount to transfer: ";
                    cin >>transfer_cash;

                    cashTransfer( recipient, transfer_cash, customer );

                }//end of transfering

                else if (choice == 5)//deleting account
                {
                    cout <<"Are you sure you want to permanently close your bank account?" <<endl;
                    cout <<"Enter 'y' for yes: ";
                    cin >>changes_character;

                    if ( changes_character == 'y')
                    {
                        closeAccount( customer );
                    }

                    else
                    {
                        cout <<"Account not deleted." <<endl <<"You can still use all the services provided by the bank." <<endl;
                    }
                }// end of deleting account


                else if (choice == 6)//customer issue start
                {
                    cout <<"Enter your issue here: ";
                    cin.ignore();
                    getline(cin, issue);

                }//end of customer issue

                else if (choice == 7)//exiting
                {
                    system("cls");
                    break;

                }//end of exiting

            }//end of customer

            else
            {
                cout <<"Invalid option."<<endl <<"Press any key /to continue."<<endl;
                getch();
                system("cls");
                continue;
            }

            cout <<"Press a key to continue: ";
            getch();
            system("cls");

        }//end of inner loop
        
    }//End of outer loop

    store();

    system("cls");
    header();
    cout<<"Thank you for using this system." <<endl;
    
}//end of main

//_____________Display Header of the Program______________
void header()
{
    cout <<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" <<endl;
    cout <<"$                                  $" <<endl;
    cout <<"$      Bank Management System      $" <<endl;
    cout <<"$                                  $" <<endl;
    cout <<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" <<endl<<endl;
}

//______________Choosing the user of system____________
char whichUser()
{
    cout <<"Welcome to my bank management system!"<<endl;
    cout <<"Enter 'm' for manager, 'e' for employee, 'c' for customer and 'x' to exit the system."<<endl;
    cin >>user;

    return user;
}

//______________User Menu_________________
int menu( int user_password )
{
    int choice = 0;

    if ( user_password == 1111 )
    {
        cout <<"Menu" <<endl;
        cout <<"1. Hire a new employee" <<endl;
        cout <<"2. Fire a current employee" <<endl;
        cout <<"3. Check employee list" <<endl;
        cout <<"4. Sort employee by age" <<endl;
        cout <<"5. Sort employee by work" <<endl;
        cout <<"6. Delete an existing customer" <<endl;
        cout <<"7. Check cash outflow" <<endl;
        cout <<"8. Check cash inflow" <<endl;
        cout <<"9. Check customer issue" <<endl;
        cout <<"10. Check customers list" <<endl;
        cout <<"11. Sort customers by account balance" <<endl;
        cout <<"12. Exit" <<endl;
        cout <<"Your choice here..";
        cin >>choice;
    }

    else if ( user_password == 2222 )
    {
        cout<<"Menu"<<endl;
        cout<<"1. Add a new customer"<<endl;
        cout<<"2. Update an existing customer"<<endl;
        cout<<"3. Update working hours"<<endl;
        cout<<"4. Exit"<<endl;
        cout<<"Your choice here..";
        cin>>choice;
    }

    else if ( user_password == 3333 )
    {
        cout <<"Menu:"<<endl;
        cout <<"1. Check Account Balance"<<endl;
        cout <<"2. Deposit Cash"<<endl;
        cout <<"3. Withdar Cash"<<endl;
        cout <<"4. Transfer Cash"<<endl;
        cout <<"5. Close Bank Account"<<endl;
        cout <<"6. Complain an Issue"<<endl;
        cout <<"7. Exit"<<endl;
        cout<<"Your choice here..";
        cin>>choice;
    }

    return choice;
}

//_____________Hiring Employee____________
void hireEmployee()
{
    for ( ; employeeCount < MAX_RECORDS; )
    {
        cout <<"Enter name: ";
        cin >>employee_name[employeeCount];
        cout <<"Enter education: ";
        cin >>education[employeeCount];
        cout <<"Enter experience: ";
        cin >>experience[employeeCount];
        cout <<"Enter age: ";
        cin >>age[employeeCount];
        employeeCount ++;

        cout <<endl <<"Username for this employee is 'user'."<<endl;
        cout <<"Password for this employee is '2222'."<<endl;
        break;
    }

    if ( employeeCount == MAX_RECORDS )
    {
        cout <<"Cannot add further employee.";
    }
}

//______________Firing Employee________________
void fireEmployee( string employee )
{
    for (int i = 0; i < employeeCount; i++)
    {
        if ( employee == employee_name[i] )
        {
            cout <<employee_name[i] <<" has been fired." <<endl;
            experience[i] = age[i] = -1;
            employee_name[i] = education[i] = "zzzzzz";
            break;
        }
        if ( i == employeeCount - 1 )
        {
            cout <<"No Employee with this name." <<endl;
        }
    }
    
}

//_______________Display Employee_________________
void displayEmployees()
{
    for (int i = 0; i < employeeCount; i++)
    {
        if ( age[i] != 0 && age[i] != -1 )
        {
            cout <<"Name \t Age \t Experience \t Education" <<endl;
            break;
        }
    }
    
    for (int i = 0; i < employeeCount; i++)
    {
        if ( age[i] != -1 && age[i] != 0)
        {
            cout <<employee_name[i]<<" \t " <<age[i] <<" \t " <<experience[i] <<" \t " <<education[i] <<endl;
        }
    }
}

//________________Sorting Employee by Age______________
void ageSort( int start )
{
    string l_employee, l_education;
    int l_experience, l_age, l_working_hour;

    for (int o = start + 1; o < employeeCount; o++)
    {
        if ( age[ start ] < age[o] )
        {
            l_age = age[ start ];
            age[ start ] = age[o];
            age[o] = l_age;

            l_employee = employee_name[ start ];
            employee_name[ start ] = employee_name[o];
            employee_name[o] = l_employee;

            l_working_hour = working_hour[ start ];
            working_hour[ start ] = working_hour[o];
            working_hour[o] = l_working_hour;

            l_experience = experience[ start ];
            experience[ start ] = experience[o];
            experience[o] = l_experience;

            l_education = education[ start ];
            education[ start ] = education[o];
            education[o] = l_education;
        }
    }
    
}

//______________Sorting Employee by Working____________
void workSort( int start )
{
    string l_employee, l_education;
    int l_experience, l_age, l_working_hour;

    for (int o = start + 1; o < employeeCount; o++)
    {
        if ( working_hour[ start ] < working_hour[o] )
        {
            l_working_hour = working_hour[ start ];
            working_hour[ start ] = working_hour[o];
            working_hour[o] = l_working_hour;

            l_employee = employee_name[ start ];
            employee_name[ start ] = employee_name[o];
            employee_name[o] = l_employee;

            l_age = age[ start ];
            age[ start ] = age[o];
            age[o] = l_age;

            l_experience = experience[ start ];
            experience[ start ] = experience[o];
            experience[o] = l_experience;

            l_education = education[ start ];
            education[ start ] = education[o];
            education[o] = l_education;
        }
    }
}

//_______________Deleting Customers______________
void deleteCustomer( string customer )
{
    for (int i = 0; i < customerCount; i++)
    {
        if ( customer_name[i] == customer )
        {
            cout <<"Account of " <<customer <<" has been blocked."<<endl;
            customer_name[i] = "zzzzzz";
            in_account[i] = -1;
            break;
        }

        if ( i == customerCount - 1 )
        {
            cout <<"No Customer with this name." <<endl;
        }
        
    }
    
}

//_______________Display Customers________________
void displayCustomers()
{
    for (int i = 0; i < customerCount; i++)
    {
        if ( in_account[i] != 0 && in_account[i] != -1 )
        {
            cout <<"Name \t Account Balance" <<endl;
            break;
        }
    }
    
    for (int i = 0; i < customerCount; i++)
    {
        if ( in_account[i] != 0 && in_account[i] != -1 )
        {
            cout <<customer_name[i]<<" \t " <<in_account[i] <<endl;
        }
    }
}

//_________________Sorting Customers_______________
void customerSort( int start )
{
    string l_customer;
    int l_in_account;

    for ( int o = start + 1; o < customerCount; o++)
    {
        if ( in_account[ start ] < in_account[o] )
        {
            l_in_account = in_account[ start ];
            in_account[ start ] = in_account[o];
            in_account[o] = l_in_account;

            l_customer = customer_name[ start ];
            customer_name[ start ] = customer_name[o];
            customer_name[o] = l_customer;
        }
    }
}

//_______________Adding Customer__________________
void addCustomer()
{
    for ( ; customerCount < MAX_RECORDS; )
    {
        cout <<"Enter full name: ";
        cin >>customer_name[customerCount];
        cout <<"Enter cash deposited: ";
        cin >>in_account[customerCount];
        customerCount ++;

        cout <<endl <<"Username for this customer is 'user'."<<endl;
        cout <<"Password for this customer is '3333'."<<endl;
        break;
    }

    if ( customerCount == MAX_RECORDS )
    {
        cout <<"Cannot add further customers." <<endl;
    }
    
}

//______________Updating Customer______________
void updateCustomer( string changes )
{
    for (int i = 0; i < customerCount; i++)
    {
        if ( changes == customer_name[i] )
        {
            cout <<"Enter 'd' to deposit cash and 'w' to withdraw cash: ";
            cin >>changes_character;

            if (changes_character == 'd')
            {
                cout <<"Enter cash you want to deposit: ";
                cin >>cash_change;
                in_account[i] = in_account[i] + cash_change;
                cout <<"New account balance is "<< in_account[i] <<endl;
                cash_inflow = cash_inflow + cash_change;
                break;
            }

            else if (changes_character == 'w')
            {
                cout <<"Enter cash you want to withdraw: ";
                cin >>cash_change;
                
                if ( in_account[i] > cash_change )
                {
                    in_account[i] = in_account[i] - cash_change;
                    cout <<"New account balance is "<< in_account[i] <<endl;
                    cash_outflow = cash_outflow + cash_change;
                    break;
                }
                else 
                {
                    cout <<"Account limit Exceeded." <<endl;
                    break;
                }
                
            }

            else
            {
                cout <<"Invalid choice." <<endl;
                break;
            }
        }

        if ( i == customerCount )
        {
            cout <<"No Customer with such name." <<endl;
        }
    }
}

//_________________Depositing Cash__________________
void cashDeposit( string customer )
{
    for (int i = 0; i < customerCount; i++ )
    {
        if ( customer == customer_name[i] )
            {
                cout <<"Enter cash you want to deposit: ";
                cin >>cash_change;
                in_account[i] = in_account[i] + cash_change;
                cout <<"New account balance is "<< in_account[i] <<endl;
                cash_inflow = cash_inflow + cash_change;
                break;
            }
        
        if ( i == customerCount - 1 )
        {
            cout <<"No customer with this name." <<endl;
        } 
    }
}

//_______________Withdraw Cash_________________
void cashWithdraw( string customer )
{
    for (int i = 0; i < customerCount; i++)
    {
        if ( customer == customer_name[i] )
        {
            cout <<"Enter cash you want to withdraw: ";
            cin >>cash_change;

            if ( in_account[i] > cash_change )
            {
                in_account[i] = in_account[i] - cash_change;
                cout <<"New account balance is "<< in_account[i] <<endl;
                cash_outflow = cash_outflow + cash_change;
                break;
            }
            else 
            {
                cout <<"Account limit Exceeded." <<endl;
                break;
            }
        }

        if ( i == customerCount - 1 )
        {
            cout <<"No customer with this name." <<endl;
        }
    }
}

//_______________Cash Transfer______________
void cashTransfer( string recipient, int transfer_cash, string customer )
{
    for (int i = 0; i < customerCount; i++)
    {
        for (int o = 0; o < customerCount; o++)
        {
            if (customer == customer_name[i] )
            {
                if ( recipient == customer_name[o] )
                {
                    if ( transfer_cash < in_account[i] )
                    {
                        in_account[i] = in_account[i] - transfer_cash;
                        in_account[o] = in_account[o] + transfer_cash;
                        cout <<"Your new account balance is "<< in_account[i] <<endl;
                        break;
                    }
                    else
                    {
                        cout <<"Account limit exceeded." <<endl;
                    }
                }

                else if ( o == customerCount)
                {
                    cout <<"No recipient with this name." <<endl;
                }
            }

            else if ( customerCount == i - 1 )
            {
                cout <<"No customer with this name." <<endl;
            }
        }   
    }    
}

//_________Closing bank account________
void closeAccount( string customer )
{
    for (int i = 0; i < customerCount; i++)
    {
        if ( customer_name[i] == customer )
        {
            cout <<"Account of " <<customer <<" has been closed."<<endl;
            cash_outflow = cash_outflow + in_account[i];
            customer_name[i] = "zzzzzz";
            in_account[i] = -1;
            break;
        }

        if ( i == customerCount - 1 )
        {
            cout <<"No Customer with this name." <<endl;
        }
        
    }
    
}

//_________Loading data from file_______
void load()
{
    fstream file;
    string line;

    file.open( "customer.txt", ios :: in);

    while ( file >> line )
    {
        customer_name[ customerCount ] = parseRecord( line, 0);
        in_account[ customerCount ] = stoi( parseRecord( line, 1) );
        customerCount ++;
    }
    file.close();

    file.open( "employee.txt", ios :: in);

    while ( file >> line )
    {
        employee_name[ employeeCount ] = parseRecord( line, 0);
        education[ employeeCount ] = parseRecord( line, 1);
        age[ employeeCount ] = stoi( parseRecord( line, 2) );
        experience[ employeeCount ] = stoi( parseRecord( line, 3) );
        working_hour[ employeeCount ] = stoi( parseRecord( line, 4) );
        employeeCount ++;
    }
    file.close();
}

//___________Parse Record___________
string parseRecord(string record, int field)
{
    int commaCount = 0;
    string item;
    for (int x = 0; x < record.length(); x++)
    {
        if (record[x] == ',')
        {
            commaCount = commaCount + 1;
        }
        else if (commaCount == field)
        {
            item = item + record[x];
        }
    }
    return item;
}

//_________Saving data in the file________
void store()
{
    fstream file;

    file.open( "customer.txt", ios :: out);

    for (int i = 0; i < customerCount; i++)
    {
        if (in_account[i] != 0 && in_account[i] != -1)
        {
            file << customer_name[i] <<"," <<in_account[i] <<endl;
        }
        
    }
    file.close();

    file.open( "employee.txt", ios :: out);

    for (int i = 0; i < employeeCount; i++)
    {
        if (age[i] != 0 && age[i] != -1)
        {
            file << employee_name[i] <<"," <<education[i] <<"," <<age[i] <<"," <<experience[i] <<"," <<working_hour[i] <<endl;
        }
    }
    file.close();   
}

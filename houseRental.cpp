#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_HOUSES = 100;

// Base class
class Property
{
public:
    virtual void displayDetails() const = 0; // Pure virtual function (Polymorphism)
};

// House class inherits from Property
class House : public Property
{
private:
    static int idCounter;
    int houseID;
    string location;
    int rent;
    bool isAvailable;
    string ownerName;
    string rentedByName;
    string rentedByCNIC;

public:
    House()
    {
        houseID = ++idCounter;
        location = "";
        rent = 0;
        isAvailable = true;
        ownerName = "";
        rentedByName = "";
        rentedByCNIC = "";
    }

    // Validation functions for inputs
    int getValidatedInt()
    {
        int value;
        while (true)
        {
            cin >> value;
            if (cin.fail() || value <= 0)
            {
                cin.clear();
                cin.ignore();
                cout << "Invalid input. Please enter a positive integer: ";
            }
            else
            {
                break;
            }
        }
        return value;
    }

    string getValidatedString()
    {
        string value;
        cin.ignore();
        while (true)
        {
            getline(cin, value);
            if (value.empty())
            {
                cout << "Input cannot be empty. Please try again: ";
            }
            else
            {
                break;
            }
        }
        return value;
    }

    void inputHouse()
    {
        cout << "Enter Location: ";
        location = getValidatedString();
        cout << "Enter Rent: ";
        rent = getValidatedInt();
        cout << "Enter Owner Name: ";
        ownerName = getValidatedString();
    }

    void displayDetails() const override
    {
        cout << "\nHouse ID: " << houseID
             << "\nLocation: " << location
             << "\nRent: PKR" << rent
             << "\nOwner: " << ownerName
             << "\nStatus: " << (isAvailable ? "Available" : "Rented");
        if (!isAvailable)
        {
            cout << "\nRented By: " << rentedByName;
        }
        cout << "\n---------------------------\n";
    }

    void markAsRented(string name, string cnic)
    {
        isAvailable = false;
        rentedByName = name;
        rentedByCNIC = cnic;
    }

    void markAsAvailable()
    {
        isAvailable = true;
        rentedByName = "";
        rentedByCNIC = "";
    }

    int getID()
    {
        return houseID;
    }
    string getCNIC()
    {
        return rentedByCNIC;
    }

    bool available()
    {
        return isAvailable;
    }

    void save(ofstream &fout)
    {
        fout << houseID << "," << location << "," << rent << "," << isAvailable
             << "," << ownerName << "," << rentedByName << "," << rentedByCNIC << endl;
    }

    void load(ifstream &fin)
    {
        char comma;
        fin >> houseID >> comma;
        getline(fin, location, ',');
        fin >> rent >> comma >> isAvailable >> comma;
        getline(fin, ownerName, ',');
        getline(fin, rentedByName, ',');
        getline(fin, rentedByCNIC);
    }
};

int House::idCounter = 100;

class RentalSystem
{
private:
    House houses[MAX_HOUSES];
    int houseCount;

public:
    RentalSystem()
    {
        houseCount = 0;
    }

    void loadFromFile()
    {
        ifstream file("houses.txt");
        if (!file.is_open())
            return;

        while (houseCount < MAX_HOUSES)
        {
            House h;
            h.load(file);
            if (file.fail())
                break; // If file is corrupted or ends
            houses[houseCount++] = h;
        }

        file.close();
    }

    void saveToFile()
    {
        ofstream file("houses.txt");
        for (int i = 0; i < houseCount; i++)
        {
            houses[i].save(file);
        }
        file.close();
    }

    void addHouse()
    {
        if (houseCount >= MAX_HOUSES)
        {
            cout << "Cannot add more houses.\n";
            return;
        }
        House h;
        h.inputHouse();
        houses[houseCount++] = h;
        cout << "House added.\n";
    }

    void viewHouses()
    {
        if (houseCount == 0)
        {
            cout << "No houses available.\n";
            return;
        }
        for (int i = 0; i < houseCount; i++)
        {
            houses[i].displayDetails(); // Polymorphism
        }
    }

    void rentHouse()
    {
        int id;
        cout << "Enter House ID to rent: ";
        cin >> id;

        for (int i = 0; i < houseCount; i++)
        {
            if (houses[i].getID() == id)
            {
                if (houses[i].available())
                {
                    string name, cnic;
                    cin.ignore();
                    cout << "Enter Your Name: ";
                    getline(cin, name);
                    cout << "Enter Your CNIC (without dashes): ";
                    
                    getline(cin , cnic);
                    
                    while( cnic.length() != 13 ){
                    	cout<<"Invalid CNIC , enter again: ";
                    	getline(cin , cnic);
					}
                   
                   
                   
                    houses[i].markAsRented(name, cnic);
                    cout << "House Rented Successfully!\n";
                    return;
                }
                else
                {
                    cout << "House is already rented.\n";
                    return;
                }
            }
        }
        cout << "House ID not found.\n";
    }

    void returnHouse()
    {
        int id;
        string cnic;
        cout << "Enter House ID to return: ";
        cin >> id;
        cout << "Enter your cnic: ";
        cin >> cnic;

        for (int i = 0; i < houseCount; i++)
        {
            if (houses[i].getID() == id && houses[i].getCNIC() == cnic)
            {
                if (!houses[i].available())
                {
                    houses[i].markAsAvailable();
                    cout << "House Returned Successfully!\n";
                    return;
                }
                else
                {
                    cout << "House is already available.\n";
                    return;
                }
            }
        }
        cout << "Incorrect information!\n";
    }

    void deleteHouse()
    {
        int id;
        cout << "Enter House ID to delete: ";
        cin >> id;

        for (int i = 0; i < houseCount; i++)
        {
            if (houses[i].getID() == id)
            {
                for (int j = i; j < houseCount - 1; j++)
                {
                    houses[j] = houses[j + 1];
                }
                houseCount--;
                cout << "House Deleted.\n";
                return;
            }
        }
        cout << "House ID not found.\n";
    }
};

// Main Function

int main()
{
    RentalSystem system;
    system.loadFromFile();

    const string ADMIN_PASSWORD = "haris123";

    int loginChoice;

    cout << "Welcome To The House Rentals: ";

    do
    {
        
        do {
            cout << "\nLogin as:\n1. Admin\n2. Customer\n3. Exit\nChoice: ";
            cin >> loginChoice;

            if (cin.fail() || loginChoice < 1 || loginChoice > 3) {
                cin.clear();                
                cin.ignore(10000, '\n');    
                cout << "Invalid input. Please enter 1, 2 or 3.\n";
            }
        } while (loginChoice < 1 || loginChoice > 3);

        if (loginChoice == 1)
        {
            string enteredPassword;
            cout << "Enter Password: ";
            cin >> enteredPassword;

            if (enteredPassword == ADMIN_PASSWORD)
            {
                int adminChoice;
                do
                {
                    do {
                        cout << "\n--- Admin Menu ---\n";
                        cout << "1. Add House\n2. View Houses\n3. Delete House\n4. Back\nChoice: ";
                        cin >> adminChoice;

                        if (cin.fail() || adminChoice < 1 || adminChoice > 4) {
                            cin.clear();
                            cin.ignore(10000, '\n');
                            cout << "Invalid input. Please enter a number between 1 and 4.\n";
                        }
                    } while (adminChoice < 1 || adminChoice > 4);

                    if (adminChoice == 1)
                        system.addHouse();
                    else if (adminChoice == 2)
                        system.viewHouses();
                    else if (adminChoice == 3)
                        system.deleteHouse();

                } while (adminChoice != 4);
            }
            else
            {
                cout << "Incorrect password. Access denied.\n";
            }
        }
        else if (loginChoice == 2)
        {
            int userChoice;
            do
            {
                do {
                    cout << "\n--- User Menu ---\n";
                    cout << "1. View Houses\n2. Rent House\n3. Return House\n4. Back\nChoice: ";
                    cin >> userChoice;

                    if (cin.fail() || userChoice < 1 || userChoice > 4) {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cout << "Invalid input. Please enter a number between 1 and 4.\n";
                    }
                } while (userChoice < 1 || userChoice > 4);

                if (userChoice == 1)
                    system.viewHouses();
                else if (userChoice == 2)
                    system.rentHouse();
                else if (userChoice == 3)
                    system.returnHouse();

            } while (userChoice != 4);
        }

    } while (loginChoice != 3);

    system.saveToFile();
    cout << "Exiting Program. Data saved.\n";
    return 0;
}


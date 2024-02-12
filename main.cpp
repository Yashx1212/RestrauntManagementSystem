#include <bits/stdc++.h>

using namespace std;

const string ADMIN_LOGIN = "amkd2f";
const string EMPLOYEE_LOGIN = "dfko09";
static int uniqueEmployeeId = 1;
static int customerId = 1;

class Menu {
    private: 
        vector <vector<string>> list;
    public: 
        Menu(vector <vector<string>> list){
            this->list = list;
        }

        vector <vector<string>> getMenu() const {
            return list;
        }

        void displayMenu(){
            for(int i = 0; i < list.size() ; i++){
                string index = to_string(i);
                cout << i ;
                for(int j=index.length(); j<=4;j++){
                    cout << " ";
                }
                string dishName = list[i][0];
                cout << dishName ;
                for(int j = dishName.length(); j<=30; j++){
                    cout << " ";
                }
                cout << ": Rs " << list[i][1] << "\n"; 
            }
        }

        void addItem(vector<string> item){
            list.push_back(item);
        }

        void deleteItem(string itemName){
            int index = -1;

            for(int i=0;i<list.size();i++){
                if(list[i][0] == itemName){
                    index = i;
                    break;
                }
            }

            if(index == -1){
                cout << itemName << " Doesn't exist\n";
                return;
            }

            list.erase(list.begin() + index);
            cout << itemName << " Deleted\n" ;
        }

        bool checkSerielNum(int index){
            return index < list.size() && index > 0;
        }
};

class Person {
    private :
        string name;
        
    protected:
        int id;
    
    public:
        Person(){

        }

        Person(string name, int id){
            this->name = name;
            this->id = id;
        }

        string get_name() const {
            return name;
        }

        int getId(){
            return id;
        }

};

class Guest : public Person {
    private :
        vector <int> order_ids;
    public :
        
        Guest(string name,int id) : Person(name, id){
        }
        
        int getBill(Menu m){
            int bill = 0;
            vector<vector<string>> list = m.getMenu();
            for(int i : order_ids){
                cout << list[i][0] << " " << list[i][1] << "\n";
                bill += stoi(list[i][1]);
            }
            return bill;
        }

        void addOrder(int i){
            order_ids.push_back(i);
        }
};

class Employee : public Person {
    private :
        int salary;
    public : 
        Employee(){

        }

        Employee(string name, int id, int salary) : Person(name, id){
            this->salary = salary;
        }

        void addItem (Menu &m, vector<string> item){
            m.addItem(item);
        }

        void deleteItem(Menu &m, string itemName){
            m.deleteItem(itemName);
        }

        int getSalary(){
            return salary;
        }

        void display_employee(){
            cout << this->getId() << " " << this->get_name() << " " << this->getSalary() << "\n";
        }
};

class Admin {
    private: 
    vector <Employee> emp;
    public:

    void addEmployee(){
        cout << "Enter Name and Salary : ";
        string name;
        int salary;
        cin >> name >> salary;
        Employee e(name, uniqueEmployeeId++, salary);
        emp.push_back(e);
    }

    void listEmployee(){
        for(int i=0;i<emp.size(); i++){
            emp[i].display_employee();
        }
    }

    Employee getEmployee(int id){
        for(int i=0;i<emp.size();i++){
            if(emp[i].getId() == id){
                return emp[i];
            }
        }

        return emp[0];
    }
};

void adminControls(Admin &a){
    while(1){
        cout << "Add Employee        : 1\n";
        cout << "List Employees      : 2\n";
        cout << "Exit                : 3\n";
        int input;
        cin >> input;
        if(input  == 3){
            break;
        }else if(input == 1){
            a.addEmployee();
        }else if(input == 2){
            a.listEmployee();
        }else{
            cout << "Wrong Input Try Again \n";
        }
    }
}

void guestControl(Menu &m){
    cout << "Please Enter your name \n";
    string name;
    cin >> name;
    Guest g(name, customerId++);
    while(1){
        int i;
        cout << "Enter 1 to Display Menu.\n";
        cout << "Enter 2 to add items to order.\n";
        cout << "Enter 3 exit\n";
        cin >> i;

        if(i == 1){
            m.displayMenu();
        }else if(i == 2){
            int input = 0;
            
            while(input != -1){
                cout << "Enter the seriel number of the items to order. To exit enter -1\n";
                cin >> input;
                if(input != -1){
                    if(m.checkSerielNum(input))
                        g.addOrder(input);
                    else
                        cout << "Wrong Seriel Number Try Again!\n";
                }
            }
        }else if(i == 3){
            int total = g.getBill(m);
            cout << "Grand Total : " << total << "\n";
            break;

        }else{
            cout << "Wrong Input Try Again!\n";
        }
    }
}

void employeeControl(Menu &m, Admin &a){
    cout << "Enter your Employee Id : ";
    int id;
    cin >> id;
    Employee e = a.getEmployee(id);
    while(1){
        int i;
        cout << "Enter 1 to add item to Menu.\n";
        cout << "Enter 2 to delete item from Menu.\n";
        cout << "Enter 3 to exit\n";
        cin >> i;

        if(i==1){
            vector <string> v(2);
            cout << "Enter Item Name & Price : ";
            cin >> v[0] >> v[1];
            e.addItem(m, v);
        }else if(i==2){
            string name;
            cout << "Enter Item name to delete : ";
            cin >> name;
            e.deleteItem(m, name);
        }else if(i==3){
            break;
        }else{
            cout << "Invalid Input Try Again\n";
        }
    }
}

int main(){
    vector <vector<string>> menu = {{"Mutter Panner", "1100"}, {"Shahi Panner", "1100"}, {"Butter Panner Masala", "1120"}, {"Panner Biryani", "800"}, {"Panner Biryani", "800"}, {"Panner Biryani", "800"}, {"Panner Biryani", "800"}, {"Panner Biryani", "800"}, {"Panner Biryani", "800"}, {"Panner Biryani", "800"}, {"Panner Biryani", "800"}, {"Panner Biryani", "800"}, {"Panner Biryani", "800"}, {"Panner Biryani", "800"}, {"Panner Biryani", "800"}, {"Panner Biryani", "800"}, {"Panner Biryani", "800"}, {"Panner Biryani", "800"}};
    Menu m(menu);
    Admin a;
    int input;

    while(1){
        cout << "Enter 1 to view menu \n";
        cout << "Enter 0 to exit\n";
        cin >> input;
        if(input == -1){
            adminControls(a);
        }else if(input == -2){
            employeeControl(m, a);
        }else if(input == 1){
            guestControl(m);
        }else if(input == 0){
            break;
        }else{
            cout << "Invalid Input Try Again\n";
        }
    }

    return 0;
}
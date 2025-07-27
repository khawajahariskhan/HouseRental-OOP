#include <iostream>
#include <vector>
using namespace std;

class Person {
	protected:
		string name;
		int age;
	public:
		Person(){
			name = "unknown" ;
			age = 0 ;	
		}
		
		Person(string name,int age){
			this-> name = name ;
			this-> age = age ;
		}
		
		virtual void DisplayInfo(){
			cout << "Name: " << name << ", Age: "  << age  << endl;
		}
};

class Teacher : public Person{
	private:
		string subject;
	public:
		Teacher(string name , int age, string subject) : Person(name,age) {
			this -> subject = subject ;
		} 
		
		void DisplayInfo() override{
			Person :: DisplayInfo() ;
			cout << "Subject Taught: " << subject << endl;
		}
};

class Student : public Person{
	private:
		int studentID;
	public:
		Student(string name,int age, int id) : Person(name,age) {
			studentID = id ;
		}
		
		void DisplayInfo() override{
			Person :: DisplayInfo() ;
			cout << "Student ID: " << studentID << endl;
		}
};

class Department {
	vector <Teacher> teachers ;
	vector <Student> students ;
	private:
		string name; 
	public:
		Department(string name){
			this -> name = name ;
		}
		
		void addTeacher(const Teacher *prof){
			teachers.push_back(*prof) ; 
		}
		
		void addStudent(const Student* std){
			students.push_back(*std) ; 
		}
		
		void DisplayInfo(){
			cout << "Department: " << name << endl;
			
			cout << "Teachers: " << endl;
			for (int i=0 ; i < teachers.size(); i++){
				teachers[i].DisplayInfo() ;
			}
			cout << "Students: " << endl;
			for (int i=0 ; i<students.size() ; i++ ){
				students[i].DisplayInfo() ;
			}
		}
};

int main() {
	Department objCS("ComputerScience");
	Department objMath("Mathematics");
	
	Teacher prof1("John Doe", 40, "Computer Networks");
	Teacher prof2("Jane Smith", 35, "Calculus");
	
	Student student1("Alice Johnson", 20, 12345);
	Student student2("Bob Williams",22, 67890);
	
	objCS.addTeacher(&prof1);
	objMath.addTeacher(&prof2);

	objCS.addStudent(&student1);
	objMath.addStudent(&student2);
	objCS.DisplayInfo();
	
	cout<<endl;
	
	objMath.DisplayInfo();
	
	return 0;
}

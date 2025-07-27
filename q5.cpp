#include <iostream>
#include <iomanip>
using namespace std;

class SalesQuarter {
	private:
	double salesQuarter;
	
	public:
		SalesQuarter(double quater=0){
			salesQuarter = quater ;
		}
		
		void setQuater(double quater){
			salesQuarter = quater ;	
		}
		
		double getQuater(){
			return salesQuarter ;
		}
		
};

class SalesPerson {
	public:
		int id;
		SalesQuarter salesQuarters[4];
		static int TotalPerson ;
		
		SalesPerson(int id, double q1, double q2, double q3, double q4){
				this -> id = id ;
				salesQuarters[0].setQuater(q1) ; 
				salesQuarters[1].setQuater(q2) ;
				salesQuarters[2].setQuater(q3) ; 
				salesQuarters[3].setQuater(q4) ; 
				TotalPerson++ ;
		}
		
		SalesPerson(){
			id = 0;
			for (int i=0 ; i<4 ; i++){
				salesQuarters[i].setQuater(0) ;
			}
			TotalPerson++ ;
		}
		
		~SalesPerson(){
			TotalPerson-- ;
		}
			
};

	int SalesPerson :: TotalPerson = 0;
	  
class SalesReport {
	private:
	SalesPerson salespersons[6];
	
	public:
	void generateReport(){
    cout << "------------- Annual Sales Report -------------" << endl;
    cout << left << setw(12) << "Sales Id" 
         << setw(10) << "Qt1" 
         << setw(10) << "Qt2" 
         << setw(10) << "Qt3" 
         << setw(10) << "Qt4" 
         << setw(15) << "Total Sales" << endl;

    for (int i = 0; i < 6; i++) {
        cout << left << setw(12) << salespersons[i].id;

        double total = 0;
        for (int j = 0; j < 4; j++) {
            double sale = salespersons[i].salesQuarters[j].getQuater(); 
            total += sale; 
            cout << setw(10) << sale ;
        }
        	cout << total << endl;
   		}
	}	

	void addSalesPerson(SalesPerson &Person, int index){
		salespersons[index] = Person ;
	}
};

int main() {
	SalesPerson sp1(12345, 1892.00, 0.00, 494.00, 322.00);
	SalesPerson sp2(32214, 343.00, 892.00, 9023.00, 0.00);
	SalesPerson sp3(23422, 1395.00, 1901.00, 0.00, 0.00);
	SalesPerson sp4(57373, 893.00, 892.00, 8834.00, 0.00);
	SalesPerson sp5(35864, 2882.00, 1221.00, 0.00, 1223.00);
	SalesPerson sp6(54654, 893.00, 0.00, 392.00, 3420.00);
	SalesReport report;
	
	report.addSalesPerson(sp1, 0); 
	report.addSalesPerson(sp2, 1);
	report.addSalesPerson(sp3, 2);
	report.addSalesPerson(sp4, 3);
	report.addSalesPerson(sp5, 4);
	report.addSalesPerson(sp6, 5);
	
	report.generateReport();
	
	return 0;
}


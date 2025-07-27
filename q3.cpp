#include <iostream>
#include <vector>
using namespace std;

class Day{
	private:
	string CurrentDay;
	vector <string> days = {"Mon","Tue","Wed","Thr","Fri","Sat","Sun"} ;
	
	int getDayIndex(string day){
		for(int i=0 ; i< days.size(); i++){
			if(day == days[i]){
				return i ;
			}
		}
		return -1 ;
	}
	
	public:
	void setDay(string day){
		CurrentDay = day ;
	}
	
	string AddDay(int n){
		int index = getDayIndex(CurrentDay) ;
		return days[(index+n) % 7] ; 
	}
	
	void printDay(){
		cout << "Day: " << CurrentDay << endl;
	}
	
	string GetDay(){
		return CurrentDay ;
	}
	
	string getPreviousDay(){
		int index = getDayIndex(CurrentDay) ; 
		return days[(index-1)] ;
	}
	
	string getNextDay(){
		int index = getDayIndex(CurrentDay) ;
		return days[index+1] ;
	}
};

#include <iostream>
using namespace std;
int main(){
	Day d ;
	d.setDay("Mon") ;
	
	cout << "Current Day: " << d.GetDay() << endl;
	cout << "Added Day: "  << d.AddDay(3) << endl;
	d.printDay() ;
		
	return 0;
}

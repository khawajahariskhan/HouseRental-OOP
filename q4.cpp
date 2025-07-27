#include <iostream>
using namespace std;

class Time{
	private:
		int second ;
		int minute ;
		int hour ;
	public:
		Time(int hr, int min, int sec){
			if(hr >= 0 & hr <= 23 ){
				hour = hr ;
			}
			else{
				hour = 0 ;
			} 
			
			if(min >=0 & min<=59){
				minute = min ;	
			}
			else{
				minute = 0 ;
			}
			
			if(sec >=0 & sec<= 59){
				second = sec ;
			}
			else{
				second = 0 ;
			}
		}
		
		void convert(){
			if(hour > 24){
				hour = hour % 24 ;
			}
			else if (hour < 0){
				hour = (hour + 24) % 24 ; 
			}
			
			if(minute > 60){
				hour = hour + minute/60 ; 
				minute = minute % 60 ;
			}
			else if(minute < 0){
				int borrow = (-minute + 59 ) / 60 ; 
				hour -= borrow ;
				minute = minute + borrow * 60 ;
			}
			
			if (second < 0){
				int borrow = ( -second + 59 ) / 60 ;
				minute -= borrow ;
				second = second + borrow * 60 ;
			}
			else if(second > 60){
				minute = minute + second/60 ;
				second = second % 60 ;
			}
			
		} 
		
		Time operator+(const Time &object){
			Time result(hour + object.hour, minute + object.minute, second + object.second) ;
			result.convert() ; 
			return result ;
		}
		
		Time operator-(const Time &object){
			Time result(hour + object.hour, minute + object.minute, second + object.second) ;
			result.convert() ; 
			return result ;
		}
		
		void print(){
			cout << "Hours: " << hour << endl;
			cout << "Minutes: " << minute << endl;
			cout << "Seconds: " << second << endl;
		}
};

int main()
{
	Time time1(10, 11, 22) ;
 	Time time2(30, 12, 11) ;
 	Time resultAdd = time1 + time2 ;
 	resultAdd.print() ;
 	
 	Time resultSub = time1 - time2 ;
 	resultSub.print() ;	
	
	return 0;
}

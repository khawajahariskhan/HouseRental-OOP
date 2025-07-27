#include <iostream>
using namespace std;
class Shape { 
	private:
		int id;
	public:
		Shape(int value) : id(value) {
			cout << "id: " << id << " Constructor of Shape " << endl;
		}

	int getId() const{ 
		return id;
	}
	
	virtual void Draw() { 
		cout << "Id: " << id << " Drawing a Shape " << endl;
	}
	
	virtual ~Shape(){} 
};

class Traingle : public Shape {
	private:
		int* points; 
	public:
		Traingle(int value) : Shape(value) {
			points = new int(3) ; 
			cout << getId() << " Constructor of Traingle\n";
		}
	
	void Draw() override {
		cout << getId() << " Drawing a Traingle\n";
	}
	
	~Traingle() override{
	 delete[] points; 
	}
};

class Square : public Shape {
	private:
		int* points ;
	public:
		Square(int value) : Shape(value) {
			points = new int(4) ;
			cout << getId() << " Constructor of Square\n";
		}

	void Draw() override {
		cout << getId() << " Drawing a Square\n";
	}
	
	~Square() override{
		 delete[] points;
	}
};

void drawShape(Shape& shape) {
	shape.Draw(); 
}

int main() {
	Shape shape(1); 
	
	Traingle triangle(2);
	cout << endl;
	
	Square square(3);
	cout << endl;
	
	drawShape(shape);
	cout << endl;
	
	drawShape(triangle);
	cout << endl;
	
	drawShape(square);
	cout << endl;
	
	return 0;
}

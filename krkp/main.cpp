#include <iostream>
#include <vector>
#include <string>
#include <QtWidgets>
#include <QVector>

class Object {
public:
	std::string name;
	Object(std::string _name) : name(_name) { }

	std::vector<double> prop;
};

class Container : public QObject{
	Q_OBJECT
	void (*userFunc)(double&);

public:
	Container() { }
	Container(void (*newUserFunc)(double&)){
		userFunc = newUserFunc;
	}

	std::string name;

	Container* next;
	Object* obj;

public slots:
	void setValue(double value) {
		userFunc(value);
        emit valueChanged(value);
	}
signals:
    void valueChanged(double newValue);
};

void PlusTwo(double& val) {
	//std::cout << "PlusTwo work " << val << std::endl;
	val += 2;
}
void Outt(double& value) {
	std::cout << value;
}

int main() {
	Container cnt1(PlusTwo);
	Container cnt2(Outt);
	QObject::connect(&cnt1, SIGNAL(valueChanged(double)), &cnt2, SLOT(setValue(double)));
	
	cnt1.setValue(10);
	return 0;
}
#include "mmm.moc"

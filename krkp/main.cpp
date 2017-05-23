#include <iostream>
#include <vector>
#include <string>
#include <QtWidgets>
#include <QVector>

class Modifier : public QObject{
	Q_OBJECT
public:
	Modifier(void(*_userFunc)(double&)) : userFunc(_userFunc) { }
	void (*userFunc)(double&);

	std::string name;
public slots:
	void modifierSlot(double val) {
		userFunc(val);
		emit modSignal(val);
	}

signals:
	void modSignal(double val);
};

class Prop : public QObject{
	Q_OBJECT
public:
	Prop(double _val) : propVal(_val) { }
	double propVal;
public slots:
	void propSlot(double val) {
		propVal = val;
	}
};

class Object {
public:
	std::string name;
	Object(std::string _name) : name(_name) { }

	QVector<Prop*> objProp;
	void addProp(double val) {
		objProp.push_back(new Prop(val));
	}

	~Object() {
		for(size_t i = 0; i < objProp.size(); ++i) {
			delete objProp[i];
		}
	}
};

class Container : public QObject{
	Q_OBJECT

public:
	Container() { }
	std::string name;

	Container* next;
	Object* obj;

	QVector<Modifier*> contMods;
	void addModifier(void(*_userFunc)(double&)) {
		contMods.push_back(new Modifier(_userFunc));
	}

	~Container() {
		for(size_t i = 0; i < contMods.size(); ++i) {
			delete contMods[i];
		}
	}
};

void PlusTwo(double& val) {
	//std::cout << "PlusTwo work " << val << std::endl;
	val += 2;
}
void Outt(double& value) {
	std::cout << value;
}

int main() {
	return 0;
}
#include "mmm.moc"

#include <iostream>
#include <vector>
#include <string>
#include <QtWidgets>
#include <QVector>
#include <stack>

class Modifier : public QObject{
	Q_OBJECT
public:
	/* Constructor wih user defined function */
	Modifier(void(*_userFunc)(double&)) : userFunc(_userFunc) { }

	/* Constructor with empty lambda function */
	Modifier() : userFunc([](double&){}) { }
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
	std::string name;
	Prop(double _val) : propVal(_val) { }
	double propVal;
public slots:
	void propSlotChangeVal(double changeVal) {
		propVal += changeVal;
	}
	void propSlotOverwriteVal(double val) {
		propVal = val;
	}
};

class Object {
public:
	Object() { }
	std::string name;

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

class Container : public QObject {
	Q_OBJECT

public:
	Container() {
		next = NULL;
		obj = NULL;
   	}
	std::string name;

	Container* next;
	Object* obj;

	QVector<Modifier*> contMods;

	void addModifier(void(*_userFunc)(double&)) {
		contMods.push_back(new Modifier(_userFunc));
	}
	void addModifier() {
		contMods.push_back(new Modifier());
	}

	void addObject() {
		if(obj != NULL) {
			delete obj;
		}
		obj = new Object();
	}

	~Container() {
		for(size_t i = 0; i < contMods.size(); ++i) {
			delete contMods[i];
		}

		if(obj != NULL) {
			delete obj;
		}
		if(next != NULL) {
			delete next;
		}
	}


};

/*
void PlusTwo(double& val) {
	//std::cout << "PlusTwo work " << val << std::endl;
	val += 2;
}
void Outt(double& value) {
	std::cout << value;
}
*/

void heat(double& h) {
	h += 5;
}

void closed(double& h) {
	h -= 0.2*h;
}

int main() {
	/*
	Container cnt;
	//cnt.addModifier(PlusTwo);
	cnt.addModifier();
	cnt.addObject();
	cnt.obj->addProp(3);

	QObject::connect(cnt.contMods[0], SIGNAL(modSignal(double)), cnt.obj->objProp[0], SLOT(propSlot(double)));
	cnt.contMods[0]->modSignal(222);
	//cnt.contMods[0]->modifierSlot(222);
	std::cout << cnt.obj->objProp[0]->propVal;
	*/

	Container room;
	room.addModifier(heat);
	room.next = new Container; //Table
	room.next->next = new Container; //Bottle
	room.next->next->addModifier(closed); //The bottle is closed now
	room.next->next->addObject(); //Milk is in the bottle
	room.next->next->obj->addProp(10); //Initial temperature of milk is 10

	std::cout << "Addresses:" << std::endl << &room << "->" << room.next << "->" << room.next->next << std::endl;

	std::cout << "Connecting..." << std::endl;
	//Connect room to bottle
	QObject::connect(room.contMods[0], SIGNAL(modSignal(double)), room.next->next->contMods[0], SLOT(modifierSlot(double)));
	//Connect bottle to the milk
	QObject::connect(room.next->next->contMods[0], SIGNAL(modSignal(double)), room.next->next->obj->objProp[0], SLOT(propSlotChangeVal(double)));

	std::cout << "Passing signal..." << std::endl;
	room.contMods[0]->modifierSlot(0);
	std::cout << "reading signal..." << std::endl;
	std::cout << room.next->next->obj->objProp[0]->propVal;
	return 0;
}
#include "mmm.moc"

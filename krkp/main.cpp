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
	Modifier(std::string _name, void(*_userFunc)(double&)) : name(_name), userFunc(_userFunc) { }

	/* Constructor with empty lambda function */
	Modifier() : userFunc([](double&){}) { }
	Modifier(std::string _name) : name(_name), userFunc([](double&){}) { }

	std::string name;
	void (*userFunc)(double&);

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
	Prop(std::string _name, double _val) : name(_name), propVal(_val) { }
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
	Object(std::string _name) : name(_name) { }
	std::string name;

	QVector<Prop*> objProp;
	void addProp(double val) {
		objProp.push_back(new Prop(val));
	}
	void addProp(std::string _name, double val) {
		objProp.push_back(new Prop(_name, val));
	}

	std::string whoami() {
		std::string res = "";
		res += "Object: " + name + '\n';
		res += "Has Properties: ";
		if(objProp.size() != 0) {
			res += '\n';
			QVector<Prop*>::iterator it = objProp.begin();
			while(it != objProp.end()) {
				res += (*it)->name + '\n';
				it++;
			}
		} else res += "NO\n";

		return res;
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

	Container(const std::string& _name) : name(_name) {
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

	void addModifier(std::string _name, void(*_userFunc)(double&)) {
		contMods.push_back(new Modifier(_name, _userFunc));
	}
	void addModifier(std::string _name) {
		contMods.push_back(new Modifier(_name));
	}

	Container* searchContainer(const std::string& _name) {
		Container* nx = this;
		while(nx->name != _name) {
			nx=nx->next;
			if(nx == NULL) break;
		}

		return nx;
	}

	Object* searchObject(const std::string& _name) {
		Container* nx = this;
		bool found = false;

		while(!found) {
			if(nx->obj != NULL) {
				if((nx->obj->name) == _name) {
					found = true;
					continue;
				}
			}
			nx=nx->next;

			if(nx == NULL) {
				break;
			}
		}

		if(!found) {
			return NULL;
		}

		return nx->obj;

	}

	void mkNestedContainers(QVector<std::string> cnts) {
		if(this->next != NULL) {
			//exception here
			return;
		}
		QVector<std::string>::iterator it = cnts.begin();
		Container* currentContainer = this;
		while(it != cnts.end()) {
			currentContainer->next = new Container(*it);
			currentContainer = currentContainer->next;
			it++;
		}
	}

	std::string whoami() {
		std::string res = "";
		res += "Container name: " + name + '\n';
		res += "Has next container: ";

		if(next == NULL) res += "NO\n";
		else res += next->name + '\n';

		res += "Has object: ";
		if(obj == NULL) res += "NO\n";
		else res += obj->name + '\n';

		res += "Container Modifiers: ";
		if(contMods.size() != 0) {
			res += '\n';
			QVector<Modifier*>::iterator it = contMods.begin();
			while(it != contMods.end()) {
				res += (*it)->name + '\n';
				it++;
			}
		} else res += "NO\n";

		return res;

	}

	void addObject() {
		if(obj != NULL) {
			delete obj;
		}
		obj = new Object();
	}
	void addObject(std::string _name) {
		if(obj != NULL) {
			delete obj;
		}
		obj = new Object(_name);
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

	Container room("room");
	room.addModifier("heat", heat);
	room.next = new Container("table"); //Table
	room.next->next = new Container("bottle"); //Bottle
	room.next->next->addModifier("closed", closed); //The bottle is closed now
	room.next->next->addObject("milk"); //Milk is in the bottle
	room.next->next->obj->addProp("temperature", 10); //Initial temperature of milk is 10

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

	std::cout << "Searching addresses:" << std::endl;
	std::cout << "room: " << room.searchContainer("room") << std::endl;
	std::cout << "table: " << room.searchContainer("table") << std::endl;
	std::cout << "bottle: " << room.searchContainer("bottle") << std::endl;

	std::cout << std::endl;
	std::cout << room.whoami() << std::endl;
	std::cout << room.searchContainer("table")->whoami() << std::endl;
	std::cout << room.searchContainer("bottle")->whoami() << std::endl;
	std::cout << room.searchObject("milk")->whoami() << std::endl;
	return 0;
}
#include "mmm.moc"

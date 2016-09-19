#include "histogram.h"
#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

///////////////////////////////////////////////////////////////////
// Вспомогательные функции
void AddBar(Histogram &historgam, const char *strName);
bool AppendBar(Histogram &historgam, const char *strName);

int getLexIndex(Histogram &historgam, const char *strName);
void insertNewElement(Histogram &historgam, char **newNames, const char* strName, int *newBars, int index);

int getMaxElementLen(const Histogram &historgam);

///////////////////////////////////////////////////////////////////
// реализация функций из файла histogram.h


//-----------------------------------------------------------------
// Функция AddBlock увеличивает значение столбца strName гистограмы historgam на 1.
// Если столбца с таким именем не существует, он создается.
void AddBlock(Histogram &historgam, const char *strName){
	if(!AppendBar(historgam, strName)){
		AddBar(historgam, strName);
	}
}

//-----------------------------------------------------------------
// Функция PrintHistogram выводит гистограму на экран.
void PrintHistogram(const Histogram &historgam){
	int tmax = getMaxElementLen(historgam);

	for(int i=0; i<historgam.nBarsSize; i++){
		cout << historgam.BarNames[i];

		int diff = tmax - strlen(historgam.BarNames[i]);
		for(int j=0; j < diff; j++){
			std::cout << " ";
		}

		std::cout << '|';
		//cout.setf
		cout << setfill(historgam.chBlock) << setw(10*historgam.Bars[i]/historgam.nMaxBar) << "" << /*ends <<*/ endl;
	}
}

//-----------------------------------------------------------------
// Функция находит наидлиннейшее название в гистограмме.
int getMaxElementLen(const Histogram &historgam){
	int tmax = strlen(historgam.BarNames[0]);

	for(int i=0; i<historgam.nBarsSize; i++){
		size_t len = strlen(historgam.BarNames[i]);

		if(len > tmax){
			tmax = len;
		}
	}

	return tmax;
}

///////////////////////////////////////////////////////////////////
// реализация вспомогательных функций

//-----------------------------------------------------------------
// Функция AppendBar увеличивает значение столбца strName гистограмы historgam на 1.
bool AppendBar(Histogram &historgam, const char *strName){
	for(int i=0; i<historgam.nBarsSize; i++){
		if(strcmp(historgam.BarNames[i], strName)==0){
			historgam.nMaxBar = max(historgam.nMaxBar, ++historgam.Bars[i]);
			return true;
		}
	}
	return false;
}

// Функция AddBar создает в гистограме historgam новый столбец с именем strName.
//-----------------------------------------------------------------
void AddBar(Histogram &historgam, const char *strName){
	char **newNames = new char *[historgam.nBarsSize+1];
	int   *newBars  = new int[historgam.nBarsSize+1];

	if(historgam.nBarsSize > 0){
		//Get the index where to put
		int index = getLexIndex(historgam, strName);

		//If the index is (-1) -- then we want to add to the end
		if(index == -1){
			index = historgam.nBarsSize;
		}

		insertNewElement(historgam, newNames, strName, newBars, index);

		delete[] historgam.BarNames;
		delete[] historgam.Bars;

	} else {
		newNames[historgam.nBarsSize] = new char[strlen(strName)+1];
		strcpy(newNames[historgam.nBarsSize], strName);
		newBars[historgam.nBarsSize] = 1;
	}

	historgam.nBarsSize++;
	historgam.BarNames = newNames;
	historgam.Bars = newBars;
}

// Найти место для нового элемента, сравнивая данный элемент
// лексикографически с остальными
//-----------------------------------------------------------------
int getLexIndex(Histogram &historgam, const char *strName){
	int ans = -1;

	if(historgam.nBarsSize == 0){
		return (-1);
	}

	if(historgam.bAscending){
		for(int i=0; i<historgam.nBarsSize; i++){
			if(strcmp(strName, historgam.BarNames[i]) >= 0){
				ans = i;
				break;
			}
		}
	} else {
		for(int i=0; i<historgam.nBarsSize; i++){
			if(strcmp(strName, historgam.BarNames[i]) <= 0){
				ans = i;
				break;
			}
		}
	}

	return ans;
}

// Данная функция вставляет новый элемент в требуемое место, 
// формируя новый массив элементов
//-----------------------------------------------------------------
void insertNewElement(Histogram &historgam, char **newNames, const char* strName, int *newBars, int index){
	int arrSize = historgam.nBarsSize;

	// If we want to insert an element to the beginning
	if(index == 0){
		// Allocate memory
		newNames[0] = new char[strlen(strName)+1];

		strcpy(newNames[0], strName);
		newBars[0] = 1;

		for(int i=1; i<=arrSize; i++){
			// Allocate memory
			newNames[i] = new char[strlen(historgam.BarNames[i-1])+1];

			strcpy(newNames[i], historgam.BarNames[i-1]);
			newBars[i] = historgam.Bars[i-1];
		}
	} else {
		// If we want to insert new element somewhere in the middle
		// or at the end

		// Copy the first part before the index element 
		// we want to insert
		for(int i=0; i<index; i++){
			// Allocate memory
			newNames[i] = new char[strlen(historgam.BarNames[i])+1];

			strcpy(newNames[i], historgam.BarNames[i]);
			newBars[i] = historgam.Bars[i];
		}

		// Copy the index element to the 
		// desired location
		//
		// Allocate memory
		newNames[index] = new char[strlen(strName)+1];

		strcpy(newNames[index], strName);
		newBars[index] = 1;

		// Copy all other elements from the old array to the new one
		for(int i=index + 1; i <= arrSize; i++){
			// Allocate memory
			newNames[i] = new char[strlen(historgam.BarNames[i-1])+1];

			strcpy(newNames[i], historgam.BarNames[i - 1]);
			newBars[i] = historgam.Bars[i - 1];
		}
	}

}

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include "List.h"
#include "../MyString.h"

using namespace std;

bool isSeparator(char sym) {											//‘ункци€ провер€ет €вл€етс€ ли символ разделителем
	char* Separator = new char[7]{ '.', ',', '?', '!', ' ', ':', '\0' };
	for (int i = 0; i < 7; i++) {
		if (Separator[i++] == sym) return true;
	}
	return false;
}

bool isNotSeparator(char sym) {											//‘ункци€ провер€ет не €вл€етс€ ли символ разделителем
	char* Separator = new char[7]{ '.', ',', '?', '!', ' ', ':', '\0' };
	int i = 0;
	for (int i = 0; i < 7; i++) {
		if (Separator[i++] == sym) return false;
	}
	return true;
}


int LastTill(MyString& str, bool check(char), int B_Position)				//»щет последний символ удовлетвор€ющий условию до B_Position
{
	for (int i = B_Position; i >= 0; i--)
		if (check(str[i]))
			return i;
	return -1;
}

int FirstFrom(MyString& str, bool check(char), int B_Position = 0)			//»щет первый символ удовлетвор€ющий условию начина€ с B_Position
{
	for (int i = B_Position; i < str.getLength(); i++)
		if (check(str[i]))
			return i;
	return -1;
}

int GetAverageMark(MyString str) {
	int mark1 = str[LastTill(str, isNotSeparator, str.getLength())] - 48;
	int mark2 = str[LastTill(str, isNotSeparator, LastTill(str, isNotSeparator, str.getLength()) - 1)] - 48;
	int mark3 = str[LastTill(str, isNotSeparator, LastTill(str, isNotSeparator, LastTill(str, isNotSeparator, str.getLength()) - 1) - 1)] - 48;
	double mark = mark1 + mark2 + mark3;
	mark /= 3;
	mark = round(mark*100)/100;
	if (int(mark * 100) % 100 > 50) mark = int(mark * 100) / 100 + 1;
	else mark = int(mark * 100) / 100;
	return int(mark);
}

int main() {
	setlocale(LC_ALL, ".1251");
	ifstream Input("Input.txt");	
	List<MyString> Students;
	List<int> AverageMark;
	if (Input.is_open())
	{
		string line;
		while (getline(Input, line))
		{
			MyString str(line);	
			Students.PushBack(str);
			AverageMark.PushBack(GetAverageMark(Students.At(Students.getLength() - 1)));
		}
	}
	Input.close();

	int SumAverageMark = 0;
	for (int i = 0; i < AverageMark.getLength(); i++) {
		SumAverageMark += AverageMark.At(i);
	}
	SumAverageMark /= Students.getLength();

	ofstream OutALl;
	OutALl.open("OutALl.bin", ios::binary);
	List<MyString> StudentsAverageMark;
	for (int i = 0; i < Students.getLength(); i++) {

		MyString current = Students.At(i).Select(0, FirstFrom(Students.At(i), isSeparator));
		current += " ";
		int FirstrLetter = FirstFrom(Students.At(i), isSeparator) + 1;
		int LastLetter = FirstFrom(Students.At(i), isSeparator, FirstrLetter);
		current += Students.At(i).Select(FirstrLetter, LastLetter - FirstrLetter);
		current += " ";
		FirstrLetter = FirstFrom(Students.At(i), isNotSeparator, LastLetter);
		LastLetter = FirstFrom(Students.At(i), isSeparator, FirstrLetter);
		current += Students.At(i).Select(FirstrLetter, LastLetter - FirstrLetter);
		current += " ";
		current += to_string(AverageMark.At(i));
		StudentsAverageMark.PushBack(current);

		size_t len = StudentsAverageMark.At(i).getLength() + 1;
		OutALl.write((char*)&len, sizeof(len));
		OutALl.write((char*)StudentsAverageMark.At(i).getStr(), len);

		cout << StudentsAverageMark.At(StudentsAverageMark.getLength() - 1).getStr() << endl;
	}
	OutALl.close();

	ofstream OutO;
	OutO.open("OutO.bin", ios::binary);
	cout << "Otlichnik" << endl;
	List<MyString> StudentiOtlichniki;
	for (int i = 0; i < Students.getLength(); i++) {
		MyString Otlichnik;
		if (AverageMark.At(i) >= 4) {
			Otlichnik = StudentsAverageMark.At(i).Select(0, LastTill(StudentsAverageMark.At(i), isSeparator, StudentsAverageMark.At(i).getLength() - 2));
			StudentiOtlichniki.PushBack(Otlichnik);

			size_t len = StudentiOtlichniki.At(i).getLength() + 1;
			OutO.write((char*)&len, sizeof(len));
			OutO.write((char*)StudentiOtlichniki.At(StudentiOtlichniki.getLength() - 1).getStr(), len);
			cout << StudentiOtlichniki.At(StudentiOtlichniki.getLength() - 1).getStr() << endl;
		}	
	}
	OutO.close();

	ofstream OutN;
	OutN.open("OutN.bin", ios::binary);
	cout << "Neydachniki" << endl;
	List<MyString> StudentiNeydachniki;
	for (int i = 0; i < Students.getLength(); i++) {
		MyString Neydachniki;
		if (AverageMark.At(i) <= 2) {
			Neydachniki = StudentsAverageMark.At(i).Select(0, LastTill(StudentsAverageMark.At(i), isSeparator, StudentsAverageMark.At(i).getLength() - 2));
			StudentiNeydachniki.PushBack(Neydachniki);

			size_t len = StudentiNeydachniki.At(StudentiNeydachniki.getLength() - 1).getLength() + 1;
			OutN.write((char*)&len, sizeof(len));
			OutN.write((char*)StudentiNeydachniki.At(StudentiNeydachniki.getLength() - 1).getStr(), len);
			cout << StudentiNeydachniki.At(StudentiNeydachniki.getLength() - 1).getStr() << endl;
		}

	}
	OutN.close();

	ofstream OutALlTXT;
	OutALlTXT.open("OutALl.txt");
	OutALlTXT << SumAverageMark << endl;
	for (int i = 0; i < StudentsAverageMark.getLength(); i++) {

		char* This = StudentsAverageMark.At(i).getStr();
		OutALlTXT << This << endl;

	}
	OutALlTXT.close();

	ofstream OutOTXT;
	OutOTXT.open("OutO.txt");
	for (int i = 0; i < StudentiOtlichniki.getLength(); i++) {

		char* This = StudentiOtlichniki.At(i).getStr();
		OutOTXT << This << endl;

	}
	OutOTXT.close();

	ofstream OutNTXT;
	OutNTXT.open("OutN.txt");
	for (int i = 0; i < StudentiNeydachniki.getLength(); i++) {

		char* This = StudentiNeydachniki.At(i).getStr();
		OutNTXT << This << endl;

	}
	OutNTXT.close();


	

	

	system("pause");
	return 0;
}
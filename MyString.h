#include <string>

class MyString
{
	private:
		char* Str;
		int Length;
		char* Separator;								//*for removing*
	public:
		MyString();										//������������ ��� ������� �������/"fsf"/string/MyString
		MyString(const char* nstr);
		MyString(std::string nstr);
		MyString(const MyString& t);	

		MyString& operator = (MyString& t);		
		MyString& operator = (const char* nstr);		//��������������� ����������
		MyString& operator += (const MyString& t);
		bool operator == (const MyString& t) const;
		bool operator != (const MyString& t) const;
		char& operator [] (int Position);

		bool is_empty() const;							//�������� �� ������ ������
		bool IsSeparator(char Checking);				//*for removing*
		bool IsSeparator(int Position);					//*for removing*
		void ChangeSeparators(const char* nstr);		//*for removing*
		//void AddSeparators(const char* nstr);			//*for removing*
		void erase(int begin, int size);				//������� �� ������ size �������� ������� � begin
		//void erase(const char* LineToDelete);			//*for removing*
		void insert(int begin, const char* Addition);	//��������� � ������, ���������, ������� � ������� begin
		char* getStr() const;							//��������� ������ � ���� ������� �����
		char* getSep() const;							//*for removing*
		char* Select(int begin, int length);			//��������� ���������(������ length, ������� � �������� begin) � ���� ������� �����
		//int Find(const char* Sought);					//*for removing*
		int FindFirstIf(bool (*check)(char));			//���� ������ ������� ��������������� �������
		int FindFirstIf(int begin, bool (*check)(char));//���� ������ ������� ��������������� ������� ������� � begin
		int FindLastIf(bool (*check)(char));			//���� ��������� ������� ��������������� �������
		int FindLastIF(int end, bool (*check)(char));	//���� ��������� ������� ��������������� ������� �� end
		int getLength() const;							//����� ������
	private:
		void InitSeparators();							//*for removing*
		int strlen(const char* str);					//��������� ������ ������
		void strcpy(char* Destination, const char* Source);//����������� ����� ������ � ������
		void strcat(char** Destination, const char* Source);//������������� ������ Source �  Destination

};


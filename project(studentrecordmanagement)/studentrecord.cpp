#include<iostream>
#include<fstream>
#include<iomanip>
 
using namespace std;
 
 
 
class student
{
	int idnum;
	char name[50];
	int physics, chemistry, mathematics, english, comscience;
	double per;
	char grade;
	void calculate();	
public:
	void getdata();		
	void showdata() const;	
	void show_tabular() const;
	int getIDNum() const;
}; 
 
 
void student::calculate()
{
	per=(physics+chemistry+mathematics+english+comscience)/5.0;
	if(per>=90)
		grade='A';
	else if(per>=75)
		grade='B';
	else if(per>=65)
		grade='C';
	else if(per>=55)
		grade='D';
	else if(per>=45)
		grade='E';
	else
		grade='F';
}
 
void student::getdata()
{
	cout<<"\nEnter The ID number of the student ";
	cin>>idnum;
	cout<<"\n\nEnter student's Name: ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nEnter student's physics marks: ";
	cin>>physics;
	cout<<"\nEnter student's chemistry marks: ";
	cin>>chemistry;
	cout<<"\nEnter student's mathematics marks: ";
	cin>>mathematics;
	cout<<"\nEnter student's english marks: ";
	cin>>english;
	cout<<"\nEnter student's computer science marks: ";
	cin>>comscience;
	calculate();
}
 
void student::showdata() const
{
	cout<<"\nID Number: "<<idnum;
	cout<<"\nName: "<<name;
	cout<<"\nPhysics: "<<physics;
	cout<<"\nChemistry: "<<chemistry;
	cout<<"\nMathematics: "<<mathematics;
	cout<<"\nEnglish: "<<english;
	cout<<"\nComputer Science: "<<comscience;
	cout<<"\nPercentage: "<<per;
	cout<<"\nLetter Grade: "<<grade;
}
 
void student::show_tabular() const
{
	cout<<idnum<<setw(6)<<" "<<name<<setw(10)<<physics<<setw(4)<<chemistry<<setw(4)<<mathematics<<setw(4)
		<<english<<setw(4)<<comscience<<setw(8)<<per<<setw(6)<<grade<<endl;
}
 
int  student::getIDNum() const
{
	return idnum;
}
 
 
 
void SaveStudent();	
void displayAll();	
void Searchdisplay(int);	
void modifyStudent(int);	
void deleteStudent(int);	
void DisplayClassResult();	
void DisplayResult();			
	
 
 
 
 
void write_student()
{
	student st;
	ofstream outFile;
	outFile.open("student.dat",ios::binary|ios::app);
	st.getdata();
	outFile.write(reinterpret_cast<char *> (&st), sizeof(student));
	outFile.close();
    	cout<<"\n\nStudent record Has Been Created ";
	cin.ignore();
	cin.get();
}
 
 
 
void display_all()
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		st.showdata();
		cout<<"\n\n====================================\n";
	}
	inFile.close();
	cin.ignore();
	cin.get();
}
 
 
 
void display_sp(int n)
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	bool flag=false;
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		if(st.getIDNum()==n)
		{
	  		 st.showdata();
			 flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nrecord not exist";
	cin.ignore();
	cin.get();
}
 
 
void modify_student(int n)
{
	bool found=false;
	student st;
	fstream File;
	File.open("student.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
    	while(!File.eof() && found==false)
	{
 
		File.read(reinterpret_cast<char *> (&st), sizeof(student));
		if(st.getIDNum()==n)
		{
			st.showdata();
			cout<<"\n\nPlease Enter The New Details of student"<<endl;
			st.getdata();
		    	int pos=(-1)*static_cast<int>(sizeof(st));
		    	File.seekp(pos,ios::cur);
		    	File.write(reinterpret_cast<char *> (&st), sizeof(student));
		    	cout<<"\n\n\t Record Updated";
		    	found=true;
		}
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
	cin.ignore();
	cin.get();
}
 
 
 
void delete_student(int n)
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	ofstream outFile;
	outFile.open("Temp.dat",ios::out);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		if(st.getIDNum()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&st), sizeof(student));
		}
	}
	outFile.close();
	inFile.close();
	remove("student.dat");
	rename("Temp.dat","student.dat");
	cout<<"\n\n\tRecord Deleted ..";
	cin.ignore();
	cin.get();
}
 
 
void class_result()
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\n\n\t\tALL STUDENTS RESULT \n\n";
	cout<<"==========================================================\n";
	cout<<"R.No       Name        P   C   M   E   CS   %age   Grade"<<endl;
	cout<<"==========================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		st.show_tabular();
	}
	cin.ignore();
	cin.get();
	inFile.close();
}
 
 
 
 
int main()
{
	char ch;
	int num;
	cout.setf(ios::fixed|ios::showpoint);
	cout<<setprecision(2); 
	do
	{
	system("cls");
	cout<<"\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
	cout<<"\n\n\t1.CREATE STUDENT RECORD";
	cout<<"\n\n\t2.DISPLAY ALL STUDENTS RECORDS";
	cout<<"\n\n\t3.SEARCH STUDENT RECORD ";
	cout<<"\n\n\t4.MODIFY STUDENT RECORD";
	cout<<"\n\n\t5.DELETE STUDENT RECORD";
	cout<<"\n\n\t6. DISPLAY CLASS RESULT";
	cout<<"\n\n\t7. EXIT";
	cout<<"\n\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
	cout<<"\n\n\tPlease Enter Your Choice (1-7): ";
	cin>>ch;
	system("cls");
	switch(ch)
	{
	case '1':	write_student(); break;
	case '2':	display_all(); break;
	case '3':	cout<<"\n\n\tPlease Enter Student's ID number: "; cin>>num;
				display_sp(num); break;
	case '4':	cout<<"\n\n\tPlease Enter Student's ID number: "; cin>>num;
			modify_student(num);break;
	case '5':	cout<<"\n\n\tPlease Enter Student's ID number: "; cin>>num;
			delete_student(num);break;
	case '6' :	class_result(); break;
	case '7':	exit(0);;
	default:	cout<<"\a"; 
		
    }
	}while(ch!='7');
 
	return 0;
}
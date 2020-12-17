#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#define MIN 50
#define MAX 100
using namespace std;

void add_student(); //function prototype
void delete_student();
void search_student();
void find_student();  //finds student of inputted roll no and displays them
void writeToFile();
void readFromFile();
void deleteFile(int); //deletes student of that id
int getNoOfStudent();  //gives number of student whose data is in file
void info();  //gives size of file and number of students inputted

// A student class that hold students attributes like id, name, address and class
// Object of this class will be craeted to store student details
class Student
{
  int stdId;
  int roll;
  char name[MIN];
  char dob[MIN];
  long long phone;
  char address[MIN];

public:
  static int id; //we will increase 'id' whenver student is added to the record
  //Member functions declaration
  void setData(); //this function will take input from user and set the data to attributes of class
  void showData(); //This function will give student data to user when called
  static void incrementId()
  {
    id++;
  }
  int getRoll();
  int getId();
};

fstream inout;

int main()
{

  int choice;
  system("cls");                                                  // COLOR CODE UNDER CSTDLIB HEADER FILE
  system("Color E0");
  while(1)
  {                                                         // 1_____Blue                                       A______Light Green
    cout<<"\n\t\tWhat do you want to do?"<<endl;
    cout<<"\t\t----------------------"<<endl;               // 2_____Green                                    B______Light Aqua
    cout<<"\t\t1-Add student"<<endl;                        // 3_____Aqua                                      C______Light Red
    cout<<"\t\t2-Delete student"<<endl;                       // 4_____Red                                        D______Light Purple
    cout<<"\t\t3-Search student"<<endl;                     // 5_____Purple                                   E______Light Yellow
    cout<<"\t\t4-Quit Program"<<endl;                       // 6_____Yellow                                   F______Bright White
    cout<<"\t\t----------------------"<<endl;               // 7_____White
    cout<<"Enter your choice: ";                            // 8_____Gray
    cin>>choice;                                            // 9_____Light Blue
    switch(choice)                                          // 0_____Black
    {
      case 1:
        add_student(); //calling add_student function to add records.
        break;
      case 2:
        if(Student :: id == 0) //checking whether records are entered or not
        {                    //if not then return to main function
          cout<<"**!!!!!!!!Dont have any records to edit!!!!!!!"<<endl<<"Please add records first!";
          system("pause");
        }
        else                // if record exist then moving to editing part
        {
          delete_student();
        }
        break;
      case 3:
        if(Student :: id == 0) //checking whether records are entered or not
        {                    //if not then return to main function
          cout<<"**!!!!!!!!Dont have any records to edit!!!!!!!"<<endl<<"Please add records first!";
          system("pause");
        }
        else                // if record exist then moving to editing part
        {
          search_student();
        }
        break;
      case 4:
        system("cls");
        info();               // size and no. of students
        return 0;
        break;
      default:
        cout<<"Invalid choice";
        return 0;
        break;
    }
}
  return 0;
}

int Student::id = getNoOfStudent();  //Static member initialization outside the class

// setData function of class Student definition
void Student :: setData()
{
  stdId = Student::id;
  // taking input from user
  cout<<"Enter student roll no in format(1XXX): ";
  cin>>roll;
  cout<<"Enter student name: ";
  cin>>name;
  cout<<"Enter stduent date of birth(dd/mm/yy): ";
  cin>>dob;
  cout<<"Enter stduent phone no: ";
  cin>>phone;
  cout<<"Enter student address: ";
  cin>>address;
}

void Student :: showData()
{
  cout<<stdId<<"  ";
  cout<<setw(11)<<roll<<"   ";
  cout<<setw(14)<<name<<"     ";
  cout<<setw(16)<<dob<<"\t";
  cout<<setw(16)<<phone<<"   ";
  cout<<setw(21)<<address<<"\n\n";
}

int Student :: getRoll()
{
  return roll;
}

int Student::getId()
{
  return stdId;
}

void add_student()
{
  Student::incrementId();
  writeToFile();
  system("CLS");
  cout<<endl;
  cout<<"------------------------------------------------------------------------------------------------------------------------"<<endl;
  cout<<"---------------------------Student updated record Table-----------------------------------------------------------------"<<endl;
  cout<<"------------------------------------------------------------------------------------------------------------------------"<<endl;
  cout<<"------------------------------------------------------------------------------------------------------------------------";
  cout<<"ID         "<<"Roll         "<<"Name                "<<"DOB               "<<"Phone no                 "<<"Address\n\n";
  cout<<"--------------------------------------------------------------------------------"<<endl;
  readFromFile();
  inout.close();
  cout<<"--------------------------------------------------------------------------------"<<endl;
  cout<<"---------------------------------FINISH-----------------------------------------"<<endl;
  cout<<"--------------------------------------------------------------------------------"<<endl;
  cout<<"You want to add more?(Y/n):  ";
  char c;
  cin>>c;
  if(c=='y' || c=='Y')
  {
    add_student();
  }
  else{
    system("cls");
  }
}

void delete_student(){
  //Showing existing record first before editing
  cout<<endl;
  cout<<"-------------------------------------------------------------------------------------------------------------------"<<endl;
  cout<<"---------------------------Student Existing record Table-----------------------------------------------------------"<<endl;
  cout<<"-------------------------------------------------------------------------------------------------------------------"<<endl;
  cout<<"ID         "<<"Roll         "<<"Name                "<<"DOB                "<<"Phone no                 "<<"Address\n\n";
  cout<<"------------------------------------------------------------------------------------------------------------------"<<endl;
  readFromFile();
  find_student();
  int idnumber;
  cout<<"--------------------------------------------------------------------------------"<<endl;
  cout<<"Which ID number do you want to Delete?: ";

  cin>>idnumber;            //Asking the user at which ID he wants to make a change.
  //showing existing information about that specific record
  cout<<"\nExisted information about this record.\n\n";
  cout<<"--------------------------------------------------------------------------------"<<endl;
  cout<<"ID         "<<"Roll         "<<"Name                "<<"DOB                "<<"Phone no                 "<<"Address\n\n";
  cout<<"--------------------------------------------------------------------------------"<<endl;
  Student student;
  inout.open("FILE.txt", ios::in);
  while(inout.read((char*)&student, sizeof(student)))
  {
    if(student.getId() == idnumber)
    {
      student.showData();    // shows data of particular id
    }
    else
    {
      if(inout.eof())
      {
        cout<<"Record not found!"<<endl;
      }
    }
  }
  inout.close();

  deleteFile(idnumber);

  cout<<"\n\nRecord updated successfully."<<endl;
  cout<<endl;
  cout<<"--------------------------------------------------------------------------------------------------------------------"<<endl;
  cout<<"---------------------------Updated record Table---------------------------------------------------------------------"<<endl;
  cout<<"--------------------------------------------------------------------------------------------------------------------"<<endl;
  cout<<"ID         "<<"Roll         "<<"Name                "<<"DOB                "<<"Phone no                 "<<"Address\n\n";;
  cout<<"--------------------------------------------------------------------------------------------------------------------"<<endl;
  readFromFile();
}

void search_student()
{
  find_student();
  cout<<"--------------------------------------------------------------------------------"<<endl;
  cout<<"---------------------------------FINISH-----------------------------------------"<<endl;
  cout<<"--------------------------------------------------------------------------------"<<endl;
  system("pause");
}

void writeToFile()
{
  Student student;
  student.setData();
  inout.open("FILE.txt", ios::app);
  inout.write((char*)&student, sizeof(student));
  inout.close();
}

void readFromFile()
{
  Student student;
  inout.open("FILE.txt", ios::in);
  while(inout.read((char*)&student, sizeof(student)))
  {

    student.showData();
  }
  inout.close();

}

int getNoOfStudent()
{
  Student student;
  int studentNo = 0;
  inout.open("FILE.txt", ios::in);
  while(inout.read((char*)&student, sizeof(student)))
  {
    studentNo ++;
  }
  inout.close();
  return studentNo;
}


void deleteFile(int pidnum)
{
  Student student[MAX];
  int i=0;
  inout.open("FILE.txt", ios::in);
  while(inout.read((char*)&student[i], sizeof(student[i])))
  {
    i+=1;
  }
  int j = i;
  inout.close();
  inout.open("FILE.txt", ios::out);
  for(int i=0; i<j; i++)
  {
    if(student[i].getId() != pidnum)
    {
      inout.write((char*)&student[i], sizeof(student[i]));
    }

  }
  inout.close();
  cout<<"RECORD DELETED SUCCESSUFULLY!!"<<endl;
}

void info()
{
    float size;
    inout.open("FILE.txt",ios::in);
    inout.seekg(0,ios::end);
    size=inout.tellg();
    cout<<"File size: "<<size<<" bytes."<<endl;
    inout.close();
    cout<<"Number of records: "<<getNoOfStudent()<<endl<<endl;

}

void find_student()
{
  int searchkey;
  cout<<"Which roll number of student you want to Find? ";
  cin>>searchkey;                                               //roll number as the searchkey can be entered by the user.
  Student student;
  inout.open("FILE.txt",ios::in);
  while(inout.read((char*)&student, sizeof(student)))
  {
      if (student.getRoll()==searchkey)
          student.showData();
      else
      {
            if (inout.eof())
               cout<<"RECORD NOT FOUND!"<<endl;
      }
  }
  inout.close();
}

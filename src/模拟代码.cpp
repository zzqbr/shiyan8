    #include<iostream>
    #include<fstream>
    #include<iomanip>
    #include<stdlib.h>
    #include<Windows.h>
    #include<conio.h>
    using namespace std ;
     
    #define HEADER1 "      -------------------------学生成绩---------------------- \n"
    #define HEADER2 "     |   学号   |   姓名   |   性别   |   年龄   |   系别   |\n"
    #define HEADER3 "     |----------|----------|----------|----------|----------|\n"
     
    int num; //学生总数
    class Student             //定义学生类
    {
    public:
    	char id[20];//学号 
    	char name[20] ;//名字
    	char sex[5] ;//性别
    	int age ;//年龄
    	char xibie[20] ;//系别
    	Student *next ;
    	void input() ;//输入函数
    	void ReadFile(istream & in) ;//读取文件
    	void show() ;//显示方法
    } ;
     
    void Student::input()     //输入学生信息函数
    {
    	cout<<"\t\t学号：" ;
    	cin>>id ;
    	cout<<"\t\t姓名：" ;
    	cin>>name ;
    	cout<<"\t\t性别：" ;
    	cin>>sex ;
    	cout<<"\t\t年龄：" ;
    	cin>>age ;
    	cout<<"\t\t系别：" ;
    	cin>>xibie ;
    }
     
    void Student::ReadFile(istream & in)        //读取文件
    {
    	in>>id>>name>>sex>>age>>xibie ;
    }
    

void Student::show()          //输出学生信息
{
	cout<<"     |"<<setw(5)<<id<<"     |"<<setw(5)<<name<<"     |"<<setw(8)<<sex<<"  |"<<setw(6)<<age<<"    |"<<setw(6)<<xibie<<"    |"<<endl ;
	cout<<"     |----------|----------|----------|----------|----------|\n" ;
}

class StudentMassage      //定义学生信息类，包含各项处理功能
{
public:
	StudentMassage() ;
	~StudentMassage() ;
	void ShowMenu() ;
	void Display() ;
	void AddItem() ;
	void Find() ;
	void save() ;
	void ModifyItem() ;
	void RemoveItem() ;
	void Swap(Student *p1 , Student *p2) ;
	void Sort() ;
	int ListCount() ;
	int Count() ;
private:
	Student *Head , *End ;
	ifstream in ;
	ofstream out ;
	Student *FindItem(char *id) ;
	Student *FindId(char *name) ;
} ;

Student *StudentMassage::FindItem(char *id)
{
	Student *p ;
	for(p = Head ; p->next != End ; p = p->next)
		if(!strcmp(p->next->id ,id))
			return p ;
	return NULL ;
}

Student *StudentMassage::FindId(char *name)
{
	Student *p ;
	for(p = Head ; p->next != End ; p = p->next)
		if(!strcmp(p->next->name ,name))
			return p ;
	return NULL ;
}

StudentMassage::StudentMassage()   //构造函数
{
	Head = new Student ;
	Head->next = new Student ;
	End = Head->next ;
	in.open("学生成绩.txt") ;
	if(!in)
		cout<<"\n\t\t这是一个新系统，无学生信息，请先输入。"<<endl ;
	else
	{
		while(!in.eof())
		{
			End->ReadFile(in) ;
			if(End->name[0]=='\0')
				break ;
			End->next = new Student ;
			End = End->next ;
		}
		in.close() ;
		cout<<"\n\t\t读取学生信息成功！"<<endl ;
	}
}

StudentMassage::~StudentMassage()       //析构函数
{
	Student *temp ;
	save() ;
	for(temp ; Head->next != End ; )
	{
		temp = Head->next ;
		Head -> next = Head ->next->next ;
		delete temp ;
	}
	delete Head , End ;
}

void StudentMassage::ShowMenu()                      //显示菜单
{
	cout<<"\n\n\t\t\t\t 主菜单"<<endl<<endl<<endl ;
	cout<<"\t\t****************************************"<<endl<<endl ;
	cout<<"\t\t1、增加学生信息          2、显示学生信息"<<endl<<endl ;
	cout<<"\t\t3、删除学生信息          4、学生信息查找"<<endl<<endl ;
	cout<<"\t\t5、修改学生信息          ***************"<<endl<<endl ;
	cout<<"\t\t0、系统安全退出                         "<<endl<<endl ;
	cout<<"\t\t****************************************"<<endl<<endl<<endl ;
	cout<<"\t\t请选择：" ;
}

void StudentMassage::Display()            //显示学生信息
{
	Student *p  ;
	cout<<endl<<HEADER1<<HEADER2<<HEADER3 ;
	for(p = Head->next ; p != End ; p = p->next)
		p->show() ;
	cout<<"\n\n输入任意字符，继续......" ;
	getch() ;
}

void StudentMassage::AddItem()      //添加学生信息
{
	End->input() ;
	End->next = new Student ;
	End = End->next ;
	cout<<"\n\t\t添加成功！"<<endl ;
	cout<<"\n输入任意字符，继续......" ;
	getch() ;
}

void StudentMassage::Find()    //查找函数
{
	char id[20] , name[20] ;
	int x ;
	Student *p = NULL ;
	cout<<"\n\t\t****************************************\n" ;
	cout<<"\t\t\t  1、按学生学号查找"<<endl ;
	cout<<"\t\t\t  2、按学生姓名查找" ;
	cout<<"\n\t\t****************************************\n\n\t\t请选择：" ;
	cin>>x ;
	switch(x)
	{
	case 1:                     //按学期查找
		{
			cout<<"\n\t\t请输入要查找的学生的学号：" ;
			int n;
			cin>>id ;
			n=StudentMassage::ListCount();
			cout<<"班级总人数为："<<n;
			if(p = FindItem(id))
                {cout<<endl<<HEADER1<<HEADER2<<HEADER3 ;
                    for(int i=1;i <= n;i++)
                    {

                        if(p = FindItem(id))
                        {

                            p->next->show() ;
                        }
                    }
                    cout<<"\n请输入任意字符，继续......" ;
                    getch() ;
                }
			else
			{
				cout<<"\t\t没有找到该学号的学生！"<<endl<<endl ;
				cout<<"请输入任意字符，继续......" ;
				getch() ;
			}
		} break ;
	case 2:                      //按班级查找
		{
			cout<<"\n\t\t请输入要查找的学生的班级：" ;
			cin>>name ;
			if(p = FindId(name))
			{
				cout<<endl<<HEADER1<<HEADER2<<HEADER3 ;
				p->next->show() ;
				cout<<"\n请输入任意字符，继续......" ;
				getch() ;
			}
			else
			{
				cout<<"\n\t\t没有找到该班级的学生！"<<endl<<endl ;
				cout<<"请输入任意字符，继续......" ;
				getch() ;
			}
		} break ;
	}
}

void StudentMassage::ModifyItem()     //修改学生信息
{
	char name[20] ;
	Student *p = NULL ;
	cout<<"\n\t\t请输入要修改的学生的姓名：" ;
	cin>>name ;
	if(p = FindItem(name))
	{
		cout<<"\n\t\t已找到该学生，请输入新的信息！"<<endl ;
		p->next->input() ;
		cout<<"\n\t\t修改成功！"<<endl ;
		Display() ;
	}
	else
	{
		cout<<"\n\t\t没有找到！"<<endl ;
		cout<<"\n输入任意字符！继续......." ;
		getch() ;
	}
}

void StudentMassage::RemoveItem()      //删除学生信息
{
	char name[20] ;
	Student *p = NULL , *temp = NULL ;
	cout<<"\n\t\t请输入要删除的学生的姓名：" ;
	cin>>name ;
	if(p = FindItem(name))
	{
		temp = p->next ;
		p->next = p->next->next ;
		delete temp ;
		cout<<"\n\t\t删除成功！"<<endl ;
		Display() ;
	}
	else
	{
		cout<<"\t\t没有找到！"<<endl ;
		cout<<"输入任意字符！继续......" ;
		getch() ;
	}
}

int StudentMassage::ListCount()   //返回记录的学生总数
{
	Student *p ;
	int n = 0 ;
	if(!Head)
		return 0 ;
	for(p = Head->next ; p != End ; p = p->next)
		n ++ ;
        num = n;
	return num ;
}

int StudentMassage::Count()         //成绩统计
{
	Student *p ;
	int x ,count = 0 ;
	if(!Head)
	{
		cout<<"\n\t\t没有资料可以统计！"<<endl ;
		return 0 ;
	}
}

void StudentMassage::Swap(Student *p1 , Student *p2)       //交p1,p2学生信息
{
	Student *temp = new Student ;
	strcpy(temp->name , p1->name) ;
	strcpy(temp->id , p1->id) ;
	strcpy(p1->name , p2->name) ;
	strcpy(p1->id , p2->id) ;
	strcpy(p2->name , temp->name) ;
	strcpy(p2->id , temp->id) ;
}

void StudentMassage::save()                    //存入文件
{
	out.open("学生成绩.txt");
	for(Student *p=Head->next;p!=End;p=p->next)
		out<<p->id<<"\t"<<p->name<<"\t"<<p->sex<<"\t"<<p->age<<"\t"<<p->xibie<<"\t"<<'\n';
	out.close();
	cout<<"\n\t\t学生成绩文件保存成功！"<<endl ;
	cout<<"\n输入任意字符，继续......" ;
	getch() ;
}
int main(
         )
{
	int x ;
	bool quit = false ;
	cout<<"\n\n\n\n\n\n\n\n" ;
	cout<<"\t\t********************************************"<<endl ;
	cout<<"\t\t         欢迎使用学生信息管理系统！"<<endl ;
	cout<<"\t\t********************************************"<<endl ;
	StudentMassage Grade ;
	Sleep(1000) ;
	while(!quit)
	{
		system("cls") ;
		Grade.ShowMenu() ;
		cin>>x ;
		switch(x)
		{
		case 0:quit = true ; break ;
		case 1:Grade.AddItem() ; break ;
		case 2:Grade.Display() ; break ;
		case 3:Grade.RemoveItem(); break ;
		case 4:Grade.ModifyItem(); break ;
		case 5:Grade.save() ; break ;
		case 6:Grade.Count() ; break ;
		}
	}
	return 0;
}


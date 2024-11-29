    #include<iostream>
    #include<fstream>
    #include<iomanip>
    #include<stdlib.h>
    #include<Windows.h>
    #include<conio.h>
    using namespace std ;
     
    #define HEADER1 "      -------------------------ѧ���ɼ�---------------------- \n"
    #define HEADER2 "     |   ѧ��   |   ����   |   �Ա�   |   ����   |   ϵ��   |\n"
    #define HEADER3 "     |----------|----------|----------|----------|----------|\n"
     
    int num; //ѧ������
    class Student             //����ѧ����
    {
    public:
    	char id[20];//ѧ�� 
    	char name[20] ;//����
    	char sex[5] ;//�Ա�
    	int age ;//����
    	char xibie[20] ;//ϵ��
    	Student *next ;
    	void input() ;//���뺯��
    	void ReadFile(istream & in) ;//��ȡ�ļ�
    	void show() ;//��ʾ����
    } ;
     
    void Student::input()     //����ѧ����Ϣ����
    {
    	cout<<"\t\tѧ�ţ�" ;
    	cin>>id ;
    	cout<<"\t\t������" ;
    	cin>>name ;
    	cout<<"\t\t�Ա�" ;
    	cin>>sex ;
    	cout<<"\t\t���䣺" ;
    	cin>>age ;
    	cout<<"\t\tϵ��" ;
    	cin>>xibie ;
    }
     
    void Student::ReadFile(istream & in)        //��ȡ�ļ�
    {
    	in>>id>>name>>sex>>age>>xibie ;
    }
    

void Student::show()          //���ѧ����Ϣ
{
	cout<<"     |"<<setw(5)<<id<<"     |"<<setw(5)<<name<<"     |"<<setw(8)<<sex<<"  |"<<setw(6)<<age<<"    |"<<setw(6)<<xibie<<"    |"<<endl ;
	cout<<"     |----------|----------|----------|----------|----------|\n" ;
}

class StudentMassage      //����ѧ����Ϣ�࣬�����������
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

StudentMassage::StudentMassage()   //���캯��
{
	Head = new Student ;
	Head->next = new Student ;
	End = Head->next ;
	in.open("ѧ���ɼ�.txt") ;
	if(!in)
		cout<<"\n\t\t����һ����ϵͳ����ѧ����Ϣ���������롣"<<endl ;
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
		cout<<"\n\t\t��ȡѧ����Ϣ�ɹ���"<<endl ;
	}
}

StudentMassage::~StudentMassage()       //��������
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

void StudentMassage::ShowMenu()                      //��ʾ�˵�
{
	cout<<"\n\n\t\t\t\t ���˵�"<<endl<<endl<<endl ;
	cout<<"\t\t****************************************"<<endl<<endl ;
	cout<<"\t\t1������ѧ����Ϣ          2����ʾѧ����Ϣ"<<endl<<endl ;
	cout<<"\t\t3��ɾ��ѧ����Ϣ          4��ѧ����Ϣ����"<<endl<<endl ;
	cout<<"\t\t5���޸�ѧ����Ϣ          ***************"<<endl<<endl ;
	cout<<"\t\t0��ϵͳ��ȫ�˳�                         "<<endl<<endl ;
	cout<<"\t\t****************************************"<<endl<<endl<<endl ;
	cout<<"\t\t��ѡ��" ;
}

void StudentMassage::Display()            //��ʾѧ����Ϣ
{
	Student *p  ;
	cout<<endl<<HEADER1<<HEADER2<<HEADER3 ;
	for(p = Head->next ; p != End ; p = p->next)
		p->show() ;
	cout<<"\n\n���������ַ�������......" ;
	getch() ;
}

void StudentMassage::AddItem()      //���ѧ����Ϣ
{
	End->input() ;
	End->next = new Student ;
	End = End->next ;
	cout<<"\n\t\t��ӳɹ���"<<endl ;
	cout<<"\n���������ַ�������......" ;
	getch() ;
}

void StudentMassage::Find()    //���Һ���
{
	char id[20] , name[20] ;
	int x ;
	Student *p = NULL ;
	cout<<"\n\t\t****************************************\n" ;
	cout<<"\t\t\t  1����ѧ��ѧ�Ų���"<<endl ;
	cout<<"\t\t\t  2����ѧ����������" ;
	cout<<"\n\t\t****************************************\n\n\t\t��ѡ��" ;
	cin>>x ;
	switch(x)
	{
	case 1:                     //��ѧ�ڲ���
		{
			cout<<"\n\t\t������Ҫ���ҵ�ѧ����ѧ�ţ�" ;
			int n;
			cin>>id ;
			n=StudentMassage::ListCount();
			cout<<"�༶������Ϊ��"<<n;
			if(p = FindItem(id))
                {cout<<endl<<HEADER1<<HEADER2<<HEADER3 ;
                    for(int i=1;i <= n;i++)
                    {

                        if(p = FindItem(id))
                        {

                            p->next->show() ;
                        }
                    }
                    cout<<"\n�����������ַ�������......" ;
                    getch() ;
                }
			else
			{
				cout<<"\t\tû���ҵ���ѧ�ŵ�ѧ����"<<endl<<endl ;
				cout<<"�����������ַ�������......" ;
				getch() ;
			}
		} break ;
	case 2:                      //���༶����
		{
			cout<<"\n\t\t������Ҫ���ҵ�ѧ���İ༶��" ;
			cin>>name ;
			if(p = FindId(name))
			{
				cout<<endl<<HEADER1<<HEADER2<<HEADER3 ;
				p->next->show() ;
				cout<<"\n�����������ַ�������......" ;
				getch() ;
			}
			else
			{
				cout<<"\n\t\tû���ҵ��ð༶��ѧ����"<<endl<<endl ;
				cout<<"�����������ַ�������......" ;
				getch() ;
			}
		} break ;
	}
}

void StudentMassage::ModifyItem()     //�޸�ѧ����Ϣ
{
	char name[20] ;
	Student *p = NULL ;
	cout<<"\n\t\t������Ҫ�޸ĵ�ѧ����������" ;
	cin>>name ;
	if(p = FindItem(name))
	{
		cout<<"\n\t\t���ҵ���ѧ�����������µ���Ϣ��"<<endl ;
		p->next->input() ;
		cout<<"\n\t\t�޸ĳɹ���"<<endl ;
		Display() ;
	}
	else
	{
		cout<<"\n\t\tû���ҵ���"<<endl ;
		cout<<"\n���������ַ�������......." ;
		getch() ;
	}
}

void StudentMassage::RemoveItem()      //ɾ��ѧ����Ϣ
{
	char name[20] ;
	Student *p = NULL , *temp = NULL ;
	cout<<"\n\t\t������Ҫɾ����ѧ����������" ;
	cin>>name ;
	if(p = FindItem(name))
	{
		temp = p->next ;
		p->next = p->next->next ;
		delete temp ;
		cout<<"\n\t\tɾ���ɹ���"<<endl ;
		Display() ;
	}
	else
	{
		cout<<"\t\tû���ҵ���"<<endl ;
		cout<<"���������ַ�������......" ;
		getch() ;
	}
}

int StudentMassage::ListCount()   //���ؼ�¼��ѧ������
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

int StudentMassage::Count()         //�ɼ�ͳ��
{
	Student *p ;
	int x ,count = 0 ;
	if(!Head)
	{
		cout<<"\n\t\tû�����Ͽ���ͳ�ƣ�"<<endl ;
		return 0 ;
	}
}

void StudentMassage::Swap(Student *p1 , Student *p2)       //��p1,p2ѧ����Ϣ
{
	Student *temp = new Student ;
	strcpy(temp->name , p1->name) ;
	strcpy(temp->id , p1->id) ;
	strcpy(p1->name , p2->name) ;
	strcpy(p1->id , p2->id) ;
	strcpy(p2->name , temp->name) ;
	strcpy(p2->id , temp->id) ;
}

void StudentMassage::save()                    //�����ļ�
{
	out.open("ѧ���ɼ�.txt");
	for(Student *p=Head->next;p!=End;p=p->next)
		out<<p->id<<"\t"<<p->name<<"\t"<<p->sex<<"\t"<<p->age<<"\t"<<p->xibie<<"\t"<<'\n';
	out.close();
	cout<<"\n\t\tѧ���ɼ��ļ�����ɹ���"<<endl ;
	cout<<"\n���������ַ�������......" ;
	getch() ;
}
int main(
         )
{
	int x ;
	bool quit = false ;
	cout<<"\n\n\n\n\n\n\n\n" ;
	cout<<"\t\t********************************************"<<endl ;
	cout<<"\t\t         ��ӭʹ��ѧ����Ϣ����ϵͳ��"<<endl ;
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


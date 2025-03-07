#include <cmath>
#include <iostream>
#include <fstream>
#include <strstream>
#include <string>

using namespace std;

struct tube
{
  int id;
  double dlina;
  double diametr;
  bool inorder;  //in order ->1; out of order ->0
};
struct cs  //compression station
{
  int id;
  string name;
  int cech_n;  // ammount of cech
  int cech_w;  // ammount of cech working
  double eff;  //effectiveness
};
void printmenu()
{
    cout<<"1. Add tube"<<endl
        <<"2. Add compression station"<<endl
        <<"3. See current objects"<<endl
        <<"4. Update pipe condition"<<endl
        <<"5. Update cs effectiveness"<<endl
        <<"6. Save all updates"<<endl
        <<"7. See saved objects"<<endl
        <<"8. Clear screen"<<endl
        <<"0. Exit"<<endl;
    //cout<<"Type command number:";
}
void safeinput()
{
      cin.clear();
      cin.ignore(10000,'\n');

}
void save(tube t, cs c)
{
    fstream fs;
    string filename;
    //tube t1; cs c1;
    cout<<"Type file name (without file format):";
    cin>>filename;
    fs.open(filename+".Vasiutin",fstream::out);
    //fs.open("npz1.Vasiutin",fstream::out);
    if (fs.is_open())
    {
    //for (int i=1;(t1.id!=t.id||c1.id!=c.id);i++)
        fs<<"t"<<endl<<t.id<<endl<<t.dlina<<endl<<t.diametr<<endl<<t.inorder<<endl;
        fs<<"c"<<endl<<c.id<<endl<<c.name<<endl<<c.cech_n<<endl<<c.cech_w<<endl<<c.eff<<endl;
        fs.close();
        //t1=t;
        //c1=c;
    }
    else
    {
    cout<<"Can not open file"<<endl;
    }
}
void load(tube t,cs c)
{
    fstream fs;
    string filename,line;
    char char1;
    cout<<"Type file name (without file format):";
    cin>>filename;
    fs.open(filename+".Vasiutin",fstream::in);
        //fs.open("npz1.Vasiutin",fstream::in);
        if (fs.is_open())
        {
        //strstream strs;
        for (int i=0;!fs.eof();i++)
        {
            string line;
            getline(fs,line,'\n');
            char1=line[0];
            if (char1=='c')
            {
                //getline(fs,line,'|');
                fs>>c.id;
                getline(fs,c.name);
                fs>>c.cech_n>>c.cech_w>>c.eff;
                i+=4;
            }
            else if (char1=='t')
            {
                //getline(fs,line,'|');
                fs>>t.id>>t.dlina>>t.diametr>>t.inorder;
                i+=5;
            }
            else
            {
                break;
            }
        }

    //strs.getline(t.id,100,'|')
    //fs>>t.id>>t.dlina>>t.diametr>>t.inorder;
    //fs>>c.id>>c.name>>c.cech_n>>c.cech_w>>c.eff;
        fs.close();
        }
        else
        {
        cout<<"File does not exist, is not in current folder or does not have format '.Vasiutin'"<<endl;
        }
}
tube newtube ()
{
    tube t;

    //cout<<"Pipe id:"<< <<endl;

    do{
        safeinput();
    cout<<"Type pipe length (meters):";
    cin>>t.dlina;
    }while (t.dlina<=0||cin.fail());

    do{
        safeinput();
    cout<<"Type pipe diameter (meters):";
    cin>>t.diametr;
    }while (t.diametr<=0||t.diametr>=10||cin.fail());

    do{
        safeinput();
    cout<<"Type pipe condition (1/0):";
    cin>>t.inorder;
    }while (t.inorder!=1&&t.inorder!=0);

    return t;
}
cs newcs ()
{
    cs c;

    do{
        safeinput();
    cout<<"Type compression station id:";
    cin>>c.id;
    }while(cin.fail());

        safeinput();
    cout<<"Type compression station name:";
    getline(cin, c.name);

    do{
        safeinput();
    cout<<"Type compression station ammount of cech:";
    cin>>c.cech_n;
    }while(c.cech_n<0||cin.fail());

    do{
        safeinput();
    cout<<"Type compression station ammount of cech in work:";
    cin>>c.cech_w;
    }while(c.cech_w<0||c.cech_w>c.cech_n||cin.fail());

    c.eff=round(100*c.cech_w/c.cech_n);
    /*do{
        safeinput();
    cout<<"Type compression station effectiveness:";
    cin>>c.eff;
    }while(cin.fail());*/
    return c;
}
void printstruct(tube t)
{
    cout<<"pipe id:";
    cout<<t.id<<endl;
    cout<<"pipe length:";
    cout<<t.dlina<<endl;
    cout<<"pipe diameter:";
    cout<<t.diametr<<endl;
    cout<<"pipe condition:";
    cout<<t.inorder<<endl;
};
void printstruct(cs c)
{
    cout<<"id compression station:"<<
    c.id<<endl
    <<"compression station name:"<<
    c.name<<endl<<
    //getline(c.name, cout);
    "compression station ammount of cech:"
    <<c.cech_n<<endl
    <<"compression station ammount of cech in work:"
    <<c.cech_w<<endl
    <<"compression station effectiveness:"
    <<c.eff<<endl;
}
tube edittube (tube t)
{
    char char1;
    do{
          safeinput();

    cout<<"Type pipe condition (y/n):";
    cin>>char1;
    if (char1=='y')
        t.inorder=1;
    else if (char1=='n')
        t.inorder=0;
    }while (char1!='y'&&char1!='n');

    return t;
}
cs editcs (cs c)
{
    do{
          safeinput();

    cout<<"Type compression station effectiveness:"<<endl;
    cin>>c.eff;
    }while(cin.fail());
    return c;
}


int main()
{
    int S;//signal
    setlocale(LC_ALL, "Russian");

        printmenu();
        while (true)
    {
        do{
        cout<<"Type your command:";
        cin>> S;
        if (cin.fail())
        {
        safeinput();
        }
        else
        break;
        }while(true);

        tube t;//{0,0,0,0};
        cs c;//{0,"no current objects",0,0,0};

        switch(S) {
            case 1:     //Add tube
            {
                t=newtube();
                //AllData.push_back(lineData);
            break;
            }

            case 2:     //Add compression station
            {
                c=newcs();
            break;
            }

            case 3:     //See current objects
            {
                printstruct(t);
                printstruct(c);
            break;
            }

            case 4:     //Update pipe
            {
                printstruct(t);
                t=edittube(t);
            break;
            }

            case 5:     //Update cs
            {
                printstruct(c);
                c=editcs(c);
            break;
            }

            case 6:     //Save all updates
            {
                save(t,c);
            break;
            }

            case 7:     //See saved objects
            {
                load(t,c);
                printstruct(t);
                printstruct(c);
            break;
            }

            case 8:     //Clear screen
            {
                system("cls");
                printmenu();
            break;
            }

            case 0:     //Exit
            {
                return 0;
            }

            default:
            {
                cout<<"Invalid command number"<<endl;
            break;
            }
        }
    }
    return 0;
}

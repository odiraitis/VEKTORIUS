#include "header.h"

//setters
void mok::set_gal(double g)
{
    gal_=g;
}
void mok::set_galm(double m)
{
    galm_=m;
}

//
double mediana (Vector<int> temp_paz, int n)
{
    std::string kuris;
    for (int a=0; a<n-1; a++)
        for (int i=a+1; i<n; i++)
            if (temp_paz[i]<temp_paz[a])
                std::swap(temp_paz[i],temp_paz[a]);
    if (n%2==0)
        return 1.0*(temp_paz[n/2]+temp_paz[n/2-1])/2;
    else
        return 1.0*(temp_paz[n/2]);
}
double vidurkis (Vector<int> temp_paz,int n)
{
    int sum=0;
    for (int i=0; i<n; i++)
        sum+=temp_paz[i];
    return 1.0*sum/n;
}
bool skaicius(const std::string &str) // Tikrinimas ar vien tik skaiciai
{
    return std::all_of(str.begin(), str.end(), ::isdigit);
}
bool gavoSkolos( const mok & i )
{
    int n=5;
    return (i<n);
}
bool negavoSkolos( const mok & i )
{
    int n=5;
    return (i>=n);
}
void pazymys (Vector<int>&laikinas, int &sk)
{
    std::string temp; // laikinas kintamas
    while(  std::cin>>temp)
    {
        if(skaicius(temp)==true)
        {
            
            int ivedu=std::stoi(temp);
            if(ivedu>0 && ivedu<11)
            {
                laikinas.push_back(int()); // ivedinejant pazymi pushinu
                laikinas[sk]=ivedu;
                sk++; // didinu nd pazymiu skaiciu
                
            }
            else
            {
                if(laikinas.size()!=0)
                    break;
                else std::cout<<"Ivesk pazymi, kadangi ivestas skaicius nera pazymys, noredami baigti iveskite bet koki kita skaiciu nuo 1 iki 10 "<<std::endl;
            }
            
        }
        else std::cout<<"Ivedete blogus duomenis, veskite dar karta"<<std::endl;
    }
}
void generuoju (Vector<int>&laikinas,int k, int &sk)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1,10);
    for(int j=0; j<k; j++)
    {
        laikinas.push_back(int());
        laikinas[sk]=dist(mt); //generuoju skaicius pushinu ir didinu nd kieki
        sk++;
    }
}
void generuoju (Vector<int>&laikinas,int l)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1,10);
    
    for(int l=0; l<10; l++)
    {
        laikinas.push_back(int());
        laikinas[l]=dist(mt); //generuoju skaicius pushinu ir didinu nd kieki
    }
    
}
void arzodis (Vector<mok>&temp, int i)
{
    for(int j=0; j<temp[i].vard().size(); j++)
    {
        while(!isalpha(temp[i].vard()[j])) // tikrinu ar nera skaiciaus ar kito simbolio kuris nera raide
        {
            std::cout<<"Iveskite mokinio varda naudodami tik raides"<<std::endl;
            std::string var;
            std::cin>>var;
            temp[i].set_vardas(var);
        }
    }
}
void arzodiss (Vector<mok>&temp, int i)
{
    for(int j=0; j<temp[i].pav().size(); j++)
    {
        while(!isalpha(temp[i].pav()[j])) // tikrinu ar nera skaiciaus ar kito simbolio kuris nera raide
        {
            std::cout<<"Iveskite mokinio varda naudodami tik raides"<<std::endl;
            std::string pa;
            std::cin>>pa;
         temp[i].set_pavarde(pa);
        }
    }
}
int ger_egz (int temp)
{
    
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        
        std::cout << "Blogas bandymas.  Iveskite egzamino rezultata: ";
        std::cin>>temp;
    if(temp>=1 && temp<=10) return temp;
}
double galutinis_vid (int temp, Vector<int>temp_paz, int t)
{
    double vid=vidurkis(temp_paz,t-1);
    double gal=0.4*vid+0.6*temp;
    return gal;
}
double galutinis_med (int temp, Vector<int>temp_paz, int t)
{
    double med=mediana(temp_paz,t-1);
    double gal=0.4*med+0.6*temp;
    return gal;
}
int ilg_vard(int n, Vector<mok>temp)
{
    int vardas=6;
    for(int i=0; i<n; i++)
    {
        if(temp[i].vard().size()>vardas) // ieskau ilgiausio vardo
            vardas=temp[i].vard().size();
    }
    return vardas;
}
int ilg_pav(int n,Vector<mok>temp)
{
    int pavarde=7;
    for(int i=0; i<n; i++)
    {
        if(temp[i].pav().size()>pavarde) // ieskau ilgiausio vardo
            pavarde=temp[i].pav().size();
    }
    return pavarde;
}
void sorting (int n,Vector<mok>&temp)
{
    mok laik;
    for(int i=1;i<n;++i)
    {
        for(int j=0;j<(n-i);++j)
            if(temp[j].vard()>temp[j+1].vard())
            {
                laik=temp[j];
                temp[j]=temp[j+1];
                temp[j+1]=laik;
            }
    }
}
void spausdinimas (int n, Vector<char>t, Vector<mok>temp, int vardas, int pavarde)
{
    sorting(n,temp);
    std::cout<<std::left<<std::setw(vardas+1)<<"Vardas ";
    std::cout<<std::left<<std::setw(pavarde+1)<<"Pavarde ";
    std::cout<<"Galutinis (Vid.)";
    std::cout<<(" Galutinis (Med.)\n ");
    char x='x'; // nera vid arba med reiksmes nes jos nenorejo vartotojas
    for (int i=0; i<vardas+pavarde+36; i++)
        printf("-");
    std::cout<<std::endl;
    for (int i=0; i<=n; i++)
    {
        if(t[i]=='1')
        {
            std::cout<<std::left<<std::setw(vardas+1)<<temp[i].vard();
            std::cout<<std::left<<std::setw(pavarde+1)<<temp[i].pav();
            std::cout<<std::left<<std::setw(16)<<std::fixed<<std::setprecision(2)<<temp[i].gal();
            std::cout<<std::left<<std::setw(5)<<x;
            std::cout<<std::endl;
        }
        if(t[i]=='2')
        {
            std::cout<<std::left<<std::setw(vardas+1)<<temp[i].vard();
            std::cout<<std::left<<std::setw(pavarde+1)<<temp[i].pav();
            std::cout<<std::left<<std::setw(16)<<x;
            std::cout<<std::left<<std::setw(5)<<std::fixed<<std::setprecision(2)<<temp[i].galm();
            std::cout<<std::left<<std::endl;
        }
    }
}
void spausdinimas2 (int n, Vector<mok>temp)
{
    std::sort(temp.begin(),temp.end(),lyginuGal);
    std::sort(temp.begin(),temp.end(),lyginuVardus);
    int vardas=ilg_vard(n,temp);
    int pavarde=ilg_pav(n,temp);
    std::cout<<std::left<<std::setw(vardas+1)<<"Vardas ";
    std::cout<<std::left<<std::setw(pavarde+1)<<"Pavarde ";
    std::cout<<"Galutinis (Vid.)";
    std::cout<<(" Galutinis (Med.)\n ");
    char x='x'; // nera vid arba med reiksmes nes jos nenorejo vartotojas
    for (int i=0; i<vardas+pavarde+36; i++)
        printf("-");
    std::cout<<std::endl;
    for (int i=0; i<=n-1; i++)
    {       std::cout<<std::left<<std::setw(vardas+1)<<temp[i].vard();
            std::cout<<std::left<<std::setw(pavarde+1)<<temp[i].pav();
            std::cout<<std::left<<std::setw(16)<<std::fixed<<std::setprecision(2)<<temp[i].gal();
            std::cout<<std::left<<std::setw(5)<<std::fixed<<std::setprecision(2)<<temp[i].galm();
            std::cout<<std::left<<std::endl;
    }
}
void fail_generav()
{
    for(int i=10; i<=100000; i*=10)
    {
        std::ofstream out;
        out.open(std::to_string(i)+".txt");
        
        for(int j=1; j<=i; j++)
        {
           Vector<int>paz;
            std::string s = std::to_string(j);
            out<<"Vardas"+s<<" "<<"Pavarde"+s;
            int skaic=0;
            Vector<int>::iterator IT;
            generuoju(paz,10);
            for(IT=paz.begin(); IT<paz.end();IT++)
            {
                out<<" "<<*IT;
            }
            out<<std::endl;
            
        }
        out.close();
    }
}
void skaitymas2(Vector<mok>&tem, std::string pava, int &l, int &n)
{
    std::string temp;
    std::string eil,vard,pav;
    mok skaitau;
    std::ifstream in_file (pava);
    mok te;
    if (in_file.good()){
        while(std::getline(in_file,eil)){  // Nuskaito po visa eilute txt faile
            tem.push_back(mok());
            std::istringstream in_line(eil); // Skaitymas is eilutes
            in_line>>te;
            tem[n].set_vardas(te.vard());
            tem[n].set_pavarde(te.pav());
             n++;
            int sk=0;
            Vector<int> pazymiai;
            while(in_line>>temp){
                
                if(skaicius(temp)){
                    int ivedu = stoi(temp);
                    if (ivedu>=0 and ivedu<=10){
                        pazymiai.push_back(int());
                        pazymiai[sk]=ivedu;
                        // std::cout<<pazymiai[sk]<<std::endl;
                        sk++;
                    }
                }
            }
            in_line.end;
            int egz = 0;
            egz = pazymiai[sk-1]; // Paskutinis ivestas skaicius egzamino pazimys
            double tempgal, tempgalm;
            tempgal=galutinis_vid(egz,pazymiai,sk);
            tem[l].set_gal(tempgal);
            tempgalm=galutinis_med(egz,pazymiai,sk);
            tem[l].set_galm(tempgalm);
            in_line.clear();
            in_file.clear();
            l++;
        }
    }
   
}
void atranka (Vector<mok>&temp_lievi, Vector<mok>&temp)
{
   remove_copy_if(temp.begin(), temp.end(),
                   back_inserter(temp_lievi), negavoSkolos);
    temp.erase(std::remove_if(temp.begin(), temp.end(),
                      gavoSkolos), temp.end());
}
void spausdinimas2 (int n, Vector<mok>temp, Vector<mok>temp_lievi)
{

    std::ofstream kiet ("kieciukai.txt");
    std::ofstream nus ("nuskriaustukai.txt");
    kiet<<std::left<<std::setw(11+1)<<"Vardas ";
    kiet<<std::left<<std::setw(11+1)<<"Pavarde ";
    kiet<<"Galutinis (Vid.)";
    kiet<<(" Galutinis (Med.)\n ");
    nus<<std::left<<std::setw(11+1)<<"Vardas ";
    nus<<std::left<<std::setw(11+1)<<"Pavarde ";
    nus<<"Galutinis (Vid.)";
    nus<<(" Galutinis (Med.)\n ");
    char x='x'; // nera vid arba med reiksmes nes jos nenorejo vartotojas
    for (int i=0; i<11+11+36; i++)
    {
        kiet<<"-";
        nus<<"-";
    }
    
    kiet<<std::endl;
    nus<<std::endl;
    //----------------------------
   
    for(int i=0; i<temp.size(); i++)
    {
        kiet<<std::left<<std::setw(13+1)<<temp[i].vard();
        kiet<<std::left<<std::setw(13+1)<<temp[i].pav();
        kiet<<std::left<<std::setw(16)<<std::fixed<<std::setprecision(2)<<temp[i].gal();
        kiet<<std::left<<std::setw(5)<<std::fixed<<std::setprecision(2)<<temp[i].galm();
        kiet<<std::endl;
    }

    //----------------------------

    for(int i=0; i<temp_lievi.size(); i++)
    {
        nus<<std::left<<std::setw(13+1)<<temp_lievi[i].vard();
        nus<<std::left<<std::setw(13+1)<<temp_lievi[i].pav();
        nus<<std::left<<std::setw(16)<<std::fixed<<std::setprecision(2)<<temp_lievi[i].gal();
        nus<<std::left<<std::setw(5)<<std::fixed<<std::setprecision(2)<<temp_lievi[i].galm();
        nus<<std::endl;
    }
}
void skaitymas3(Vector<mok>&tem, int &n, int &l)
{
    std::string temp;
    std::string eil,vard,pav;
    std::ifstream in_file ("kursiokai.txt");
    
    if (in_file.good()){
        while(std::getline(in_file,eil)){  // Nuskaito po visa eilute txt faile
            tem.push_back(mok());
            std::istringstream in_line(eil); // Skaitymas is eilutes
            in_line >> vard>>pav;
            
            tem[n].set_vardas(vard);
            tem[n].set_pavarde(pav);
            n++;
            int sk=0;
            Vector<int> pazymiai;
            while(in_line>>temp){
                
                if(skaicius(temp)){
                    int ivedu = stoi(temp);
                    if (ivedu>=0 and ivedu<=10){
                        pazymiai.push_back(int());
                        pazymiai[sk]=ivedu;
                        // std::cout<<pazymiai[sk]<<std::endl;
                        sk++;
                    }
                }
            }
            in_line.end;
            int egz = 0;
            egz = pazymiai[sk-1]; // Paskutinis ivestas skaicius egzamino pazimys
            double tempgal,tempgalm;
            tempgal=galutinis_vid(egz,pazymiai,sk);
            tem[l].set_gal(tempgal);
            tempgalm=galutinis_med(egz,pazymiai,sk);
            tem[l].set_galm(tempgalm);
            in_line.clear();
            in_file.clear();
            l++;
        }
    }
}
bool lyginuVardus(mok i1, mok i2)
{
    return (i1== i2);
}
bool lyginuGal(mok i1, mok i2)
{
    return (i1<i2);
}


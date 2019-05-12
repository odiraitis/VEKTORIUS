#include "header.h"
int main()
{
    int m=0;
    int n;


    char kazkas; // skaityt is failo ar ne

    std::string testas;
    char kurie; // generuoti skaicius ar vesti ranka
    Vector <mok> A; // susikuriu vektoriu
   
    int skaic=0;

    Vector <char> kuris; // generuoti su vidurkiu ar mediana

    int z=0;
    int egz; // egzamino pazymys

    std::cout<<"Jei norite skaityti is failo spauskite 1, jei norite duomenis rinktis pats spauskite 2, jei norite sugeneruoti failus spauskite 3 ?";
    while (std::cin>>kazkas)
    {


        if(kazkas=='2')
        {
            int i=0;
            int nr=0; // studentu skaic

            std::cout<<"Jei norite ivesti nauja mokini spauskite bet koki simboli, jei norite baigti iveskite raide 'f' "<<std::endl;
            while(std::cin>>testas)
            {
                if(testas!="f")
                {
                    A.push_back(mok()); // padarau vietos strukturai
                    nr++;// didinu elementu kieki
                    std::cout<<"Jei norite, kad pazymiai butu sugeneruoti spauskite 1, jei norite juos ivesti rankiniu budu, spauskite 2"<<std::endl;
                    while(std::cin>>kurie)
                    {

                        if(kurie=='1' or kurie=='2')
                        {


                            std::cout<<"Jei galutinis pazymys skaiciuojamas su vidurkiu spauskite 1, jei su mediana 2 "<<std::endl;
                            kuris.push_back(char()); // padarau vietos vektoriuje
                            std::cin>>kuris[skaic];
                            skaic++;
                            while(kuris[i]!='1' && kuris[i]!='2')
                            {
                                std::cout<<"Jei norite skaicuoti su mediana spauskite 1, jei su vidurkiu 2"<<std::endl;
                                kuris.push_back(char());
                                std::cin>>kuris[i];


                            }
                            Vector<int>pazymiai;
                            int sk=0;
                       
                            if(kurie=='2')
                            {
                                std::cout<<"Ivedus kiekviena skaiciu spauskite 'ENTER', norint baigti iveskite bet koki kita skaiciu"<<std::endl;
                                pazymys(pazymiai,sk); // kreipiuosi i pazymiu ivedimo funkcija
                            }
                            if(kurie=='1')
                            {
                                std::cout<<"Iveskite, kiek norite sugeneruoti skaiciu "<<std::endl;
                                std::cin>>n;
                                while(std::cin.fail() or n==0)
                                {
                                    std::cin.clear();
                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                                    std::cout << "Blogas bandymas.  Iveskite skaiciu: ";
                                    std::cin >> n;
                                }
                                generuoju(pazymiai,n,sk);
                            }


                            std::cout<<"Iveskite "<<i+1<<" -ojo mokinio varda ir pavarde"<<std::endl;
                           
                          std::string va, pa;
                           std::cin>>va>>pa;
                           A[i].set_vardas(va);
                          A[i].set_pavarde(pa);
                            arzodis(A,i);
                            arzodiss(A,i);
                            std::cout<<"Iveskite "<<i+1<<" -ojo mokinio egzamino pazymi"<<std::endl;
                            std::cin>>egz;
                            while(std::cin.fail() or egz<1 or egz>10)
                            {
                            egz=ger_egz(egz);
                            }
                            double galut, galutm;
                            galut=galutinis_vid(egz,pazymiai,sk);
                            A[i].set_gal(galut);
                            galutm=galutinis_med(egz,pazymiai,sk);
                            A[i].set_galm(galutm);
                            i++;
                            m++;
                            break;
                        }
                        else
                        {
                            std::cout<<"Iveskite 1 jei norite generuoti arba 2 jei norite vesti pats"<<std::endl;
                        }
                    }
                }
                else break;
                std::cout<<"Jei norite ivesti "<<i+1 <<" -aji mokini spauskite bet koki skaiciu, tik ne 0, norint baigti ivedinejima ivesti 'f'"<<std::endl;
            }
            int did_vard=ilg_vard(nr,A);
            int did_pav=ilg_pav(nr,A);
            spausdinimas(nr,kuris,A,did_vard,did_pav);
        }

        else if (kazkas=='1')
        {
            int kiek=0;
            int kiek2=0;
            skaitymas3(A,kiek,kiek2);
            spausdinimas2(kiek,A);
            
        }
        else if (kazkas=='3')
        {
            int k=0;
            int nr=0;
           // fail_generav();
            std::string pav;
           
            for(int i=10; i<=100000; i*=10)
            {
                std::string temp = std::to_string(i);
                pav=temp +".txt";
                skaitymas2(A,pav,k,nr);
            }
             auto start = std::chrono::high_resolution_clock::now();
            Vector<mok>lievi;
            atranka(lievi,A);
            std::cout<<" Lievu studentu capacity yra : " <<lievi.capacity()<<std::endl;
            std::cout<<" Lievu studentu size yra : " <<lievi.size()<<std::endl;
            lievi.shrink_to_fit();
            std::cout<<" Dabar lievu capacity yra :"<<lievi.capacity()<<std::endl;
            int r=0;
            spausdinimas2(nr,A,lievi);
            //===================================
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> diff = end-start;
            std::cout << "Failu generavimas ir nuskaitymas, paskirstymas uztruko: "
            << diff.count() << " s\n";
            break;
        }
        else if (kazkas!='1' && kazkas!='2' && kazkas!='3')
        {
            std::cout<<"Iveskite 1 arba 2 arba 3"<<std::endl;
        }
    }
    return 0;
}

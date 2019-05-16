# TRECIASND
### :computer:[v1.1](https://github.com/odiraitis/TRECIASND/releases/tag/v1.1) Iš Struct į Class.

### Tikslas : Palyginti abiejų programų: naudojančios struct iš ankstesniojo darbo ir naudojančio class tipo Studentus iš dabartinės realizacijos spartą (veikimo laiką).
-------------------------------------------------------------------------------

```c++
class mok
{
private:
    double gal_; // galutinis
    double galm_;
    std::string vard_;
    std::string pav_;
public:
   
    mok(){
        vard_ = " ";
        pav_ = " ";
        gal_ = 0;
        galm_ = 0;
    }
    //setters
    void set_vardas(std::string v);
    void set_pavarde(std::string p);
    void set_gal(double g);
    void set_galm(double m);
    //getters
    std::string vard()const
    {
        return vard_;
    }
    std::string pav()const
    {
        return pav_;
    }
    double gal()const
    {
        return gal_;
    }
    double galm()const
    {
        return galm_;
    }
};
```
Labai didelių našumo skirtumu naudojant Struct ir Class nepastebiu. Jų veikimo laikas yra minimaliai skirtingas.

Struct : 1. s. 
Class : 1.1 s.

-------------------------------------------------------------------------------

## FLAGAI

Naudojant flagus įsitikinau, kad jie duoda tikrai daug našumo ir optimizuoja programą (aišku tai priklauso ir nuo kompiliatoriaus).



Naudojant Class:

Optimizavimo -01 vėliavėlės vykdymo laikas yra : 1.3924 s.

Optimizavimo -02 vėliavėlės vykdymo laikas yra : 1.14442 s.

Optimizavimo -03 vėliavėlės vykdymo laikas yra : 0.927493 s.

Naudojant Struct:

Optimizavimo -01 vėliavėlės vykdymo laikas yra : 0.852296 s.

Optimizavimo -02 vėliavėlės vykdymo laikas yra : 0.908774 s.

Optimizavimo -03 vėliavėlės vykdymo laikas yra : 0.83839 s.

Didelį našuma kompiliavimo vėliavėlės duoda naudojant Struct, o ne Class.

Tiesa gana geras laikas ir Struct ir Class buvo naudojant -03 vėliavėlę.

--------------------------------------------------------------

### :computer:[v1.2](https://github.com/odiraitis/TRECIASND/releases/tag/v1.2) operatoriu overloadinimas.
 ### PATAISYTA VERSIJA :computer:[v1.21](https://github.com/odiraitis/TRECIASND/releases/tag/v1.21) operatoriu overloadinimas.
 
### Tikslas: pritaikyti operatorius kur tikslinga savo programoje.

Panaudojus operatorius sparta nepasikeitė (taip ir turėjo būti). 

Pagrindinis PLIUSAS yra tai, kad galima kurti naujus tipus, kurie veikia kaip built-in tipai.

Atlikdamas šį darbą pradėjau naudoti friend funkcijas, kurios leidžia tiesiogiai pasiekti PRIVATE kintamuosius ( tačiau tame slypi daug pavojų).

Skaitymo operatorius **>>**

```c++
 friend std::istream& operator>>(std::istream& in, mok &temp) {
    
        in>>temp.vard_>>temp.pav_;
        
        return in;
    }
```
Isvedimo operatorius **<<** 

```c++
 friend std::ostream& operator<<(std::ostream& out,std::vector<mok>&temp) {
        for(int i=0; i<temp.size();i++)
        {
            out<<std::left<<std::setw(11+3)<<temp[i].vard_;
            out<<std::left<<std::setw(11+3)<<temp[i].pav_;
        out<<std::left<<std::setw(16)<<std::fixed<<std::setprecision(2)<<temp[i].gal_;
            out<<std::left<<std::setw(5)<<std::fixed<<std::setprecision(2)<<temp[i].galm_;
            out<<std::endl;
        }
        
        return out;
    }
```
Lyginimo operatorius **<**
```c++
 friend bool operator<(const mok &temp, int n) {
        return (temp.galm_<n && temp.gal_<n);
    }
 ```   
Lyginimo operatorius **<** (operatoriu persidengimas)
 ```c++
    friend bool operator<(const mok &temp1,const mok &temp2) {
        return (temp1.galm_<temp2.galm_);
    }
 ```   
Lyginimo operatorius **>=**
  ```c++
    friend bool operator>=(const mok &temp, int n) {
        return (temp.galm_>=n && temp.gal_>=n);
    }
 ```   
Lyginimo operatorius **==**
  ```c++
    friend bool operator==(const mok &temp1, const mok &temp2)
    {
        return (temp1.vard_== temp2.vard_);
    }
  ``` 
 Lyginimo operatorius **!=**
  ```c++
    friend bool operator!=(const mok &temp1, const mok &temp2)
    {
        return !(temp1.pav_==temp2.pav_);
    }
  ```


 --------------------------------------------------------------
 
### :computer:[v1.5](https://github.com/odiraitis/TRECIASND/releases/tag/v1.2) Ideta base class, bei copy semantika.

Bazinė klasė **zmogus**

 ```c++
class zmogus{
public:
    void set_vardas(std::string v)
    {
        vard_=v;
    }
    void set_pavarde(std::string p)
    {
        pav_=p;
    }
    virtual void set_gal(double g) = 0;
    virtual void set_galm(double m) = 0;
protected:
    std::string vard_;
    std::string pav_;
    
};
 ```
Išvestinė klasė **mok**

 ```c++
class mok: public zmogus
{
private:
    double gal_; // galutinis
    double galm_;
public:
    mok(){
        vard_ = " ";
        pav_ = " ";
        gal_ = 0;
        galm_ = 0;
    }
    
    // copy semantika
    mok(const  mok& a)
    {
        vard_ = a.vard_;
        pav_ = a.pav_;
        gal_ = a.gal_;
        galm_ = a.galm_;
    }
    mok& operator=(const mok& a){
        if(&a == this) return *this;
        vard_ = a.vard_;
        pav_ = a.pav_;
        gal_ = a.gal_;
        galm_ = a.galm_;
        return *this;
    }
   //setters
    void set_gal(double g);
    void set_galm(double m);
    //getters
    std::string vard()const
    {
        return vard_;
    }
    std::string pav()const
    {
        return pav_;
    }
    double gal()const
    {
        return gal_;
    }
    double galm()const
    {
        return galm_;
    }
    friend std::ostream& operator<<(std::ostream& out,std::vector<mok>&temp) {
        for(int i=0; i<temp.size();i++)
        {
            out<<std::left<<std::setw(11+3)<<temp[i].vard_;
            out<<std::left<<std::setw(11+3)<<temp[i].pav_;
        out<<std::left<<std::setw(16)<<std::fixed<<std::setprecision(2)<<temp[i].gal_;
            out<<std::left<<std::setw(5)<<std::fixed<<std::setprecision(2)<<temp[i].galm_;
            out<<std::endl;
        }
        
        return out;
    }
    friend std::istream& operator>>(std::istream& in, mok &temp) {
    
        in>>temp.vard_>>temp.pav_;
        
        return in;
    }
    friend bool operator<(const mok &temp, int n) {
        return (temp.galm_<n && temp.gal_<n);
    }
    friend bool operator<(const mok &temp1,const mok &temp2) {
        return (temp1.galm_<temp2.galm_);
    }
    friend bool operator>=(const mok &temp, int n) {
        return (temp.galm_>=n && temp.gal_>=n);
    }
    friend bool operator==(const mok &temp1, const mok &temp2)
    {
        return (temp1.vard_== temp2.vard_);
    }
    
    friend bool operator!=(const mok &temp1, const mok &temp2)
    {
        return !(temp1.pav_==temp2.pav_);
    }
};
 ```
-----------------------------------------------------------------
 
 ### :computer:[v2.0](https://github.com/odiraitis/TRECIASND/releases/tag/v2.0) Ideta Doxygen dokumentacija ir Unit testu screenshotai.
 
 
 Doxygen yra labai patogus TOOL kurti dokumentaciją.
 
 Ivykdzius doxygen -g "file_name.cpp" ir doxygen "file_name.cpp" ** DOKUMENTACIJĄ SUKURIA DOXYGEN, NEREIKIA KURTI PAČIAM" 
 
 Sukurtuose HTML failuose yra klasių diagramos, netgi klasių paveldėjimų .png failai.
 
 Manau tai geriausia ir paprasčiausia priemonė kurti dokumentaciją.
 
 -----------------------------------------------------------------
 
 Unit testus atlikau naudodamas catch.hpp headerį. 
 
 Sukūrus main ir funkcijų failus belieka includinti catch.hpp (#include "catch.hpp") ir galima pradėti atlikinėti testus. 
 
 
```c++
#define CATCH_CONFIG_MAIN

#include "catch.hpp"

char skaicius( int a ) {
    return a;
}
TEST_CASE( "skaicius", "[skaicius]" ) {
    REQUIRE( skaicius(1) == 1 ); // gerai
    REQUIRE( skaicius(2) == 2 ); // gerai
    REQUIRE( skaicius(3) == 4 ); // 3 nera lygu 4 turi buti failas
    REQUIRE( skaicius(4) == 4 ); // gerai
}
```

Tikrinu ar grazina gera skaiciu, kaip zinome 3 != 4 todel ismes klaida (screenshotai yra unit_test foldery)


```c++
#define CATCH_CONFIG_MAIN

#include "catch.hpp"

std::string zodis( std::string a ) {
    return a;
}

TEST_CASE( "zodis", "zodis" ) {
    REQUIRE( zodis("zodis") == "zodis" );
}
```

Tikrinu ar grazina gera zodi (std::string tipo kintamaji),kaip matoma screenshotuose, testas pasiteisino


```c++
#define CATCH_CONFIG_MAIN

#include "catch.hpp"

int Factorial( int number ) {
    return number <= 1 ? number : Factorial( number - 1 ) * number;  // fail
    // return number <= 1 ? 1      : Factorial( number - 1 ) * number;  // pass
}

TEST_CASE( "Factorial of 0 is 1 (fail)", "[single-file]" ) {
    REQUIRE( Factorial(0) == 1 );
}

TEST_CASE( "Factorials of 1 and higher are computed (pass)", "[single-file]" ) {
    REQUIRE( Factorial(1) == 1 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 6 );
    REQUIRE( Factorial(10) == 3628800 );
}
```

Tikrinu ar grazina gera faktoriala, visais atvejais apskaiciuojamas gerai, isskyrus 0, nes mano algoritmu 0 faktorialas nera 1.

----------------------------------------------------------------------------------------------

#VEKTORIUS
### :computer:[v3.0](https://github.com/odiraitis/VEKTORIUS/releases/tag/v3.0)


Atsisiuntus release terminale, kad paleisti rasyti **make main (arba tiesiog make), tuomet, kad paleisti rasyti ./main , paskui isvalyti text ir object failus rasyti make clean.**

1. Parodysiu kaip veikia capacity() shrink_to_fit() size() erase() begin() end() funkcijos

##capacity()

vector: lievi.capacity()


```c++
Vector<mok>lievi;
atranka(lievi,A);
std::cout<<" Lievu studentu capacity yra : " <<lievi.capacity()<<std::endl;
```
**Lievu studentu capacity yra : 65536**

std::vector: lievi.capacity()


```c++
std::vector<mok>lievi;
atranka(lievi,A);
std::cout<<" Lievu studentu capacity yra : " <<lievi.capacity()<<std::endl;
```
**Lievu studentu capacity yra : 65536**

-----------------------------------------------------------------------

##size()

vector: lievi.size()

```c++
 Vector<mok>lievi;
 atranka(lievi,A);
 std::cout<<" Lievu studentu size yra : " <<lievi.size()<<std::endl;
 ```
 **Lievu studentu size yra : 47638**
 
 std::vector: lievi.size()

```c++
 std::vector<mok>lievi;
 atranka(lievi,A);
 std::cout<<" Lievu studentu size yra : " <<lievi.size()<<std::endl;
 ```
 
  **Lievu studentu size yra : 47638**
  
  -----------------------------------------------------------------------
  
  shrink_to_fit() funkcija turi pakeisti vektoriaus capacity pagal jo size, jie turi tapti lygiais
  
  vector : shrink_to_fit()
  
  ```c++
  Vector<mok>lievi;
  atranka(lievi,A);
  std::cout<<" Lievu studentu capacity yra : " <<lievi.capacity()<<std::endl;
  std::cout<<" Lievu studentu size yra : " <<lievi.size()<<std::endl;
  lievi.shrink_to_fit();
  std::cout<<" Dabar lievu capacity yra :"<<lievi.capacity()<<std::endl;
  
  ```
  
 **Lievu studentu capacity yra : 65536**
 
 **Lievu studentu size yra : 47638**
 
 **Dabar lievu capacity yra :47638**


std::vector : shrink_to_fit()
  
  ```c++
  std::vector<mok>lievi;
  atranka(lievi,A);
  std::cout<<" Lievu studentu capacity yra : " <<lievi.capacity()<<std::endl;
  std::cout<<" Lievu studentu size yra : " <<lievi.size()<<std::endl;
  lievi.shrink_to_fit();
  std::cout<<" Dabar lievu capacity yra :"<<lievi.capacity()<<std::endl;
  
  ```
  
 **Lievu studentu capacity yra : 65536**
 
 **Lievu studentu size yra : 47638**
 
 **Dabar lievu capacity yra :47638**
 
 -----------------------------------------------------------------------
 
 erase() reikalingas atrinkimui su remove if
 
 erase realizavimas vektoriaus klaseje
 
 ```c++
    iterator erase(const_iterator first, const_iterator last)
    {
        const difference_type distance = first - cbegin();
        const difference_type distance_first_last = last - cbegin();
        iterator it_first = begin() + distance;
        iterator it_last = begin() + distance_first_last;
        construct_elements(it_last, end(), array_start_ + distance);
        size_ -= last - first;
        rearrange_pointers();
        return it_first;
     }
   ```
   
   vector : erase() begin() ir end()
   
   Cia naudojamos erase() begin() end() funkcijos:
   
    ```c++
        void atranka (Vector<mok>&temp_lievi, Vector<mok>&temp)
        {
         remove_copy_if(temp.begin(), temp.end(),
                   back_inserter(temp_lievi), negavoSkolos);
           temp.erase(std::remove_if(temp.begin(), temp.end(),
                      gavoSkolos), temp.end());
          }  
    ```
   
  Kad galetume patikrinti ar sios funkcijos veikia teisingai idesiu std::vector ir Vector rezultatus (paskutinius 10 is kieciukai.txt failo)
  
  
  Vector :
  ```
  
Vardas99983   Pavarde99983  6.36            5.60 
Vardas99985   Pavarde99985  8.62            8.80 
Vardas99988   Pavarde99988  5.93            5.80 
Vardas99989   Pavarde99989  6.29            6.60 
Vardas99992   Pavarde99992  8.53            8.00 
Vardas99993   Pavarde99993  7.11            7.60 
Vardas99994   Pavarde99994  6.98            6.80 
Vardas99997   Pavarde99997  7.38            7.60 
Vardas99998   Pavarde99998  5.42            5.20 
Vardas100000  Pavarde100000 7.20            7.60 
```
 std::vector :
 
 ```
Vardas99983   Pavarde99983  6.36            5.60 
Vardas99985   Pavarde99985  8.62            8.80 
Vardas99988   Pavarde99988  5.93            5.80 
Vardas99989   Pavarde99989  6.29            6.60 
Vardas99992   Pavarde99992  8.53            8.00 
Vardas99993   Pavarde99993  7.11            7.60 
Vardas99994   Pavarde99994  6.98            6.80 
Vardas99997   Pavarde99997  7.38            7.60 
Vardas99998   Pavarde99998  5.42            5.20 
Vardas100000  Pavarde100000 7.20            7.60 

 ```
 
 TAIGI SIOS TRYS FUNKCIJOS VEIKIA TEISINGAI
 
 -----------------------------------------------------------------------
 
 2 ir 3.  Efektyvumo ir spartos analizė. Push_back() įvairių dydžių vektorius.
 
| Objektu skaicius| std::vector v1| Vector v2|
|:---:|:---:|:---:|
| 10000 | 0.000885609 s | 0.000563843 s|
| 100000 | 0.00736708 s | 0.0031621 s|
| 1000000 | 0.000885609 s | 0.0277314 s|
| 10000000 | 0.689455 s | 0.334248 s|
| 100000000 | 6.45887 s | 3.25118 s|

**Vector v2 yra dvigubai greitesnis uz std::vector v1**

----------------------------------------------------------------------

Perskirstymu skaicius kai size()==capacity()

| Objektu skaicius| std::vector v1| Vector v2|
|:---:|:---:|:---:|
| 10000 |  14 kartu | 14 kartu|
| 100000 | 17 kartu | 17 kartu|
| 1000000 | 20 kartu | 20 kartu|
| 10000000 | 24 kartus | 24 kartus|
| 100000000 | 27 kartus | 27 kartus|

Perskirstymas ivyko vienodai kartu visais atvejais, taip ir turejo buti jeigu vector klase yra teisinga

----------------------------------------------------------------------

```
10000 objektu pildymas
std::vector v1 uzpildymas uztruko: 0.000885609 s
Perskirstymas ivyko 14 kartu
Vector v2 uzpildymas uztruko: 0.000563843 s
Perskirstymas ivyko 14 kartu
100000 objektu pildymas
std::vector v1 uzpildymas uztruko: 0.00736708 s
Perskirstymas ivyko 17 kartu
Vector v2 uzpildymas uztruko: 0.0031621 s
Perskirstymas ivyko 17 kartu
1000000 objektu pildymas
std::vector v1 uzpildymas uztruko: 0.0604746 s
Perskirstymas ivyko 20 kartu
Vector v2 uzpildymas uztruko: 0.0277314 s
Perskirstymas ivyko 20 kartu
10000000 objektu pildymas
std::vector v1 uzpildymas uztruko: 0.689455 s
Perskirstymas ivyko 24 kartu
Vector v2 uzpildymas uztruko: 0.334248 s
Perskirstymas ivyko 24 kartu
100000000 objektu pildymas
std::vector v1 uzpildymas uztruko: 6.45887 s
Perskirstymas ivyko 27 kartu
Vector v2 uzpildymas uztruko: 3.25118 s
Perskirstymas ivyko 27 kartu
```
 ----------------------------------------------------------------------
 
 Vektoriaus klase pritaikiau savo programai
 
 | std::vector | Vector |
|:---:|:---:|
| 0.943622 s | 1.06083 s|

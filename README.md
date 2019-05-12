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

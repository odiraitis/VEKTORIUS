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



----------------------------------------------------------------------------------------------

# VEKTORIUS
### :computer:[v3.0](https://github.com/odiraitis/VEKTORIUS/releases/tag/v3.0)

**Norint paleisti:**

* `git clone https://github.com/odiraitis/VEKTORIUS.git`

* `make`

* `./main`

**Istrynimui .txt ir .o failam**

* make clean

1. Parodysiu kaip veikia capacity() shrink_to_fit() size() erase() begin() end() funkcijos

## capacity()

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

## size()

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


-------------------------------------------------------------------------

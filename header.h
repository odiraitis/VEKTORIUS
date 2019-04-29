#define pragma once
#include <iostream>
#include <algorithm>
#include <string>
#include <string.h>
#include <vector>
#include <time.h>
#include <cmath>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdlib.h>
#include <chrono>
#include <random>
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
class mok: public zmogus
{
private:
    double gal_; // galutinis
    double galm_;
public:
    ~mok(){}
    mok(){
        vard_ = " ";
        pav_ = " ";
        gal_ = 0;
        galm_ = 0;
    }
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
double mediana (std::vector<int> temp_paz, int n);
double vidurkis (std::vector<int> temp_paz,int n);
bool skaicius(const std::string &str);
bool gavoSkolos( const mok & i );
bool negavoSkolos( const mok & i );
void pazymys (std::vector<int>&laikinas,int &sk);
void generuoju (std::vector<int>&laikinas,int k, int &sk);
void generuoju (std::vector<int>&laikinas,int l);
void arzodis (std::vector<mok>&temp, int i);
void arzodiss (std::vector<mok>&temp, int i);
int ger_egz (int temp);
double galutinis_vid (int temp, std::vector<int>temp_paz, int t);
double galutinis_med (int temp, std::vector<int>temp_paz, int t);
int ilg_vard(int n, std::vector<mok>temp);
int ilg_pav(int n, std::vector<mok>temp);
void sorting (int n, std::vector<mok>&temp);
void spausdinimas (int n, std::vector<char>t, std::vector<mok>temp, int vardas, int pavarde);
void spausdinimas2 (int n, std::vector<mok>temp);
void fail_generav();
void skaitymas2(std::vector<mok>&tem, std::string pava, int &l, int &n);
void atranka (std::vector<mok>&temp_lievi, std::vector<mok>&temp);
void spausdinimas2 (int n, std::vector<mok>temp, std::vector<mok>temp_lievi);
void skaitymas3(std::vector<mok>&tem, int &n, int &l);
bool lyginuVardus(mok i1, mok i2);
bool lyginuGal(mok i1, mok i2);

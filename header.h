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

class mok
{
private:
    double gal_; // galutinis
    double galm_;
    std::string vard_;
    std::string pav_;
public:
   //setters
    void set_vardas(std::string v);
    void set_pavarde(std::string p);
    void set_gal(double g);
    void set_galm(double m);
    //getters
    std::string va()const
    {
        return vard_;
    }
    std::string vard=va();
    std::string pa()const
    {
        return pav_;
    }
    std::string pav=pa();
    double ga()const
    {
        return gal_;
    }
   double gal=ga();
    double gam()const
    {
        return galm_;
    }
    double galm=gam();
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

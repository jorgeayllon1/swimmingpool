#ifndef FONCTIONSUTILES_H
#define FONCTIONSUTILES_H
#include <iostream>
#include <vector>
#include <cmath>

void connexe(int taille,int ordre);
std::vector<bool> decimaltobinary(int n,int taille);
void initialisation();
void troisDeuxUnPartez();
bool sortbyCout1(const std::pair<int, int> &a,
               const std::pair<int, int> &b);
bool sortbyCout2(const std::pair<int, int> &a,
               const std::pair<int, int> &b);

#endif

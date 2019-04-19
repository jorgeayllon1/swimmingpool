#include <iostream>
#include "fonctionsutiles.h"
#define INFINI 9999

using namespace std;

vector<bool> decimaltobinary(int n, int taille)
{

    vector<bool> a(taille, 0);
    for (int i = 0; n > 0; i++)
    {
        a[i] = n % 2;
        n = n / 2;
    }
    return a;
}

void connexe(int taille, int ordre)
{
    int nbdecompatester = pow(2, taille);
    int nbmin=pow(2,ordre);
    for (int j = nbmin; j < nbdecompatester; j++)
    {
        vector<bool> a = decimaltobinary(j, taille);

        int recip = 0;

        for (int i = a.size() - 1; i >= 0; i--)
        {
            if (a[i])
                recip++;
        }
        if (recip >= ordre - 1)
        {
            cout << j << " est ok\n";
        }
        else
        {
            cout << j << " n'est pas ok\n";
        }
    }
}
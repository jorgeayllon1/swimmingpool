#include "graphe.h"
#include <random>
#include "time.h"
#include <windows.h>
using namespace std;

int main()
{
	srand(time(NULL));
	vector<pair<float,float>> total;
	Graphe espace("triville.txt", "triville_weights_0.txt");
	//espace.dessinerGraphe();
	//espace.dijkstraSPT(0);

	//espace.afficherData();
	//int cycle;
	//std::cin>>cycle;
	vector<vector<bool>> G = espace.calcul_sousgraphes_admissibles(&total,0);
	/*for (unsigned int i =0 ; i<G.size();i++)
    {
        //cout<<total[i].first<<" et "<<total[i].second<<endl;
        espace.Conversion(G[i]).dessinerGraphe();
        Sleep(2500);


    }*/
    cout<<"*********************************************************"<<endl;
	//for(int i =0 ; i<G.size();i++)
    ///{
        espace.Conversion(G[0]).dessinerGraphe();
        //cout<<"_"<<espace.Conversion(G[0]).dijkstraSPT(0)<<endl;
        //cout<<"_"<<espace.Conversion(G[0]).dijkstraSPT(1)<<endl;
        //cout<<"_"<<espace.Conversion(G[0]).dijkstraSPT(2)<<endl;
        //cout<<"_"<<espace.Conversion(G[0]).dijkstraSPT(3)<<endl;
        //cout<<"="<<espace.Conversion(G[13]).dijkstraSPT(0)+espace.Conversion(G[13]).dijkstraSPT(1)+espace.Conversion(G[13]).dijkstraSPT(2)+espace.Conversion(G[13]).dijkstraSPT(3)<<endl;
        //std::cout<<" "<<total[0].second<<std::endl;
        //Sleep(15000);
    ///}


    espace.Pareto(total);

	return 0;
}

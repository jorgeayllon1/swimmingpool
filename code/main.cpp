#include "graphe.h"
#include <random>
#include "time.h"
using namespace std;

int main()
{
	srand(time(NULL));
	Graphe espace("manhattan.txt", "manhattan_weights_0.txt");

	vector<pair<float,float>> total;
	vector<vector<bool>> G = espace.calcul_sousgraphes_admissibles(&total,1);
	/*for (unsigned int i =0 ; i<G.size();i++)
    {
        cout<<total[i].first<<" et "<<total[i].second<<endl;
        /*espace.Conversion(G[i]).dessinerGraphe();
        Sleep(2500);*/
    //}
    cout<<"*********************************************************"<<endl;
	//for(int i =0 ; i<G.size();i++)
    ///{
        espace.Conversion(G[0]).dessinerGraphe();
        cout<<"_"<<espace.Conversion(G[6]).dijkstraSPT(0,1)<<endl;
        cout<<"_"<<espace.Conversion(G[6]).dijkstraSPT(1,1)<<endl;
        cout<<"_"<<espace.Conversion(G[6]).dijkstraSPT(2,1)<<endl;
        cout<<"_"<<espace.Conversion(G[6]).dijkstraSPT(3,1)<<endl;
        cout<<"="<<espace.Conversion(G[6]).dijkstraSPT(0,1)+espace.Conversion(G[6]).dijkstraSPT(1,1)+espace.Conversion(G[6]).dijkstraSPT(2,1)+espace.Conversion(G[6]).dijkstraSPT(3,1)<<endl;
        std::cout<<" "<<total[6].second<<std::endl;
        //Sleep(15000);
    ///}


    espace.Pareto(total);


	return 0;
}

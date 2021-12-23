#include <iostream>
#include <fstream>
#include <stdio.h>
#include <queue>
#include <vector>
#include <utility>
#include <bits/stdc++.h>

using namespace std;

ifstream fin("ciclueuler.in");
ofstream fout("ciclueuler.out");

#define NMAX 100001

class Graf{
private:
    int nrNod, nrMuch;
    bool orientat;
    vector<vector<int>> listaAd;

public:
    Graf(int nrNoduri = 0, int nrMuchii = 0, bool eOrientat = false)
    {
        this->nrNod = nrNoduri;
        this->nrMuch = nrMuchii;
        this->orientat = eOrientat;
    }

    ~Graf()
    {
        this->nrNod = 0;
        this->nrMuch = 0;
        listaAd.clear();
    }

    friend class Probleme;

    void set_nrNod(int &);
    void set_nrMuch(int &);
    int get_nrNod();
    int get_nrMuch();

//tema 1 - BF-DF-si-aplicatii
    void bfs(int, vector<int>&);
    void dfs(int, vector<int>&, int, stack<int>&,vector<int>&, vector<vector<int>>);
    bool havel_hakimi(vector<int>&, int);
//tema 2 - Drumuri-minime-si-APM
    void init(vector<int>&,vector<int>&);
    int reprez(int,vector<int>&);
    void unite(int,int,vector<int>&,vector<int>&, vector<pair <int, int>>& muchii_apm);
    void apm_kruskall(int&, vector<pair<int, pair<int, int>>>&,vector<int>&,vector<int>&, vector<pair <int, int>>&);
    void dijkstra(int , vector<int>& , list<pair<int, int> > *muchii_dij);
    bool bellman_ford(int, vector<int>&, list<pair<int, int> > *muchii_dij);
//tema 3 - Maxflow-Royfloyd-Darb
    int darb(int,int&);
    void roy_floyd(vector<vector<int>>&);
    bool bfs_flow(int, int, vector<int>&, vector<vector<int>>&, vector<vector<int>>&, vector<int>&);
    int max_flow(vector<int>&, vector<vector<int>>&,vector<vector<int>>&,vector<int>&);
//tema 4 - Ciclu Eulerian
    bool ciclueurian(vector<int>&, int, list<pair<int, int> > *lista);
};

class Probleme{
public:
//tema 1 - BF-DF-si-aplicatii
    void bfs_infoarena();
    void dfs_infoarena();
    void havel_hakimi();
    void sortare_top_infoarena();
    void ctc_infoarena();
//tema 2 - Drumuri-minime-si-APM
    void apm_infoarena();
    void disjoint_infoarena();
    void dijkstra_infoarena();
    void bellman_ford_infoarena();
//tema 3 - Maxflow-Royfloyd-Darb
    void darb_infoarena();
    void roy_floyd_infoarena();
    void maxflow_infoarena();
//tema 4 - Ciclu Eulerian
    void ciclueulerian_infoarena();
};


void Graf::set_nrNod(int &n) {nrNod = n;}

void Graf::set_nrMuch(int &m) {nrMuch = m;}

int Graf::get_nrNod() {return nrNod;}

int Graf::get_nrMuch() {return nrMuch;}

bool Graf::ciclueurian(vector<int>& ciclu, int nod, list<pair<int, int>> *lista)
{
    for(int i = 1; i <= nrNod; ++i)
        if (lista[i].size() % 2 == 1)
            return false;

    stack<int> st;
    int viz_edge[nrMuch+1] = {0};

    st.push(nod);

    while (!st.empty())
    {
        int x = st.top();

        if(!lista[x].empty())
        {

            int e = lista[x].back().second;
            int vecin = lista[x].back().first;

            lista[x].pop_back();

            if (!viz_edge[e])
            {
                viz_edge[e] = 1;
                st.push(vecin);
            }
        }
        else
        {
            st.pop();
            ciclu.push_back(x);
        }
    }

    return true;
}

void Probleme::ciclueulerian_infoarena()
{
    vector<int> ciclu;
    bool rasp;
    int N, M, x, y;

    fin >> N >> M;

    Graf G(N, M);

    list<pair<int, int> > *lista;
    lista = new list<pair<int,int>> [N + 1];

    for(int i = 0; i < M; i++)
    {
        fin >> x >> y;

        lista[x].push_back(make_pair(y, i));
        lista[y].push_back(make_pair(x, i));
    }

    rasp = G.ciclueurian(ciclu, 1, lista);

    if(!rasp)
        fout << "-1";
    else
    {
        if(!ciclu.empty())
            for (auto i = ciclu.begin(); i != ciclu.end(); i++)
                fout << *i << " ";
    }
}

int main()
{
   Probleme p;

    p.ciclueulerian_infoarena();

    fin.close();
    fout.close();

    return 0;
}

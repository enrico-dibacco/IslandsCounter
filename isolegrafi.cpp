#include <map>
#include <vector>
#include <fstream>
#include <queue>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;



struct Arco
{
    string dest;
    int len;

};
struct Infoq
{
    string city;
    int len;
    bool operator<(const Infoq &other) const
    {
        return len > other.len;
    }


};


map<string, vector<Arco>> mp;
map<string, int> mp_islands;

int visitCities(string & startCity, int island)
{
    string city;
    priority_queue<string> pq;
    pq.push(startCity);
    /* for  (auto item:mp)
    {   
        string city = item.first;

        mp_visited[city] = false;
    } */
    while(!pq.empty())
    {
        city = pq.top();
        pq.pop();
        if(mp_islands[city] == island)
            continue;
        mp_islands[city] = island;

        /* if(infoq.city == "Siracusa")
        {
            cout << "Distanza minima tra le citta indicate nel commento equivale a :" <<  infoq.len;
            break;
        } */
        //cerco tutti i percorsi che partono da infoq.city
        vector<Arco> &ad = mp[city];
        for (int i = 0; i < ad.size(); i++)
        {
            Arco ar = ad[i];
            if (mp_islands[ar.dest] == -1)
            {
                pq.push(ar.dest);
            }
        } 

    }
}
string findNonAssignedCity()
{
    for( auto item : mp_islands)
    {
        if(item.second == -1)
        {
            return item.first;
        }
        
        
    }
    return "";
}


int main()
{
    int islandCounter = 0;
    string line;
    ifstream fs("Grafo_Isole.txt");
    if (!fs.is_open())
    {
        cout << "Error";
        return 0;
    }
    

    while(getline(fs, line))
    {
        stringstream st(line);
        string city1,city2;
        int lunghezza;
        st >> city1 >> city2 >> lunghezza;
        cout<<city1 << " "<< city2 << " " << lunghezza << endl;

        Arco ar1 = {city2, lunghezza};
        Arco ar2 = {city1, lunghezza};
        mp[city1].push_back(ar1);
        mp[city2].push_back(ar2);
        mp_islands[city1] = -1;
        mp_islands[city2] = -1;
    }


/*     
    for(auto item : mp["Palermo"])
    {
        cout << item.dest << " " << item.len << endl;
    }
 */
    
    string city;
    while((city = findNonAssignedCity()).length() > 0)
    {
        
        visitCities(city, islandCounter++);
        
    }
    
    



    cout << "Islands:" << endl;
    for (auto item : mp_islands)
    {
        
        cout << "city " << item.first << " island " << item.second << endl;
    }
    cout << "Islands " << islandCounter << endl;

}

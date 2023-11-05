#include "receiver.h"
#include <vector>
#include <string>
#include "Stock.h"
#include "Package.h"


int main()
{
    Receiver rcv;
    std::string message = "";
    while (true)
    {
        message += rcv.readIML();
        if (message[message.size() - 1] == '$')
            break;
    }
    char delimiter = '#';
    std::vector<std::string> input;
    size_t start = 0, end = 0;
    while ((end = message.find(delimiter, start)) != std::string::npos)
    {
        input.push_back(message.substr(start, end - start));
        start = end + 2;
    }
    delimiter = ' ';
    vector<Package> packages;
    int net_profit = 0;
    for(auto ms : input){
        Package bestPackage;
        int maxProfit = 0;
        int n = packages.size();
        for (int i = 0; i < (1 << n); i++)
        {
            Package P(ms);
            P.indexes.push_back(n);
            for (int j = n - 1; j >= 0; j--)
            {
                if ((i & (1 << j)) != 0){
                    P = P + packages[j];
                    P.indexes.push_back(j);}
            }
            
            bool check = P.isArbitrage();
            if(P.price > maxProfit && check){
                maxProfit = P.price;
                bestPackage = P;
            }
        }
        packages.push_back(Package(ms)); 
        if(bestPackage.indexes.size() == 0)std::cout<<"No Trade"<<std::endl;
        else{
            for(auto k : bestPackage.indexes){
                packages[k].printPackage();
                packages.erase(packages.begin() + k);
            }
            net_profit+=bestPackage.price;
        }
    }
    std::cout << net_profit << std::endl;
    return 0;
}
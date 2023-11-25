#include <vector>
#include <string>
#include "map.h"


class Package
{
public:
    RedBlackTree<int> stocks;
    int price = 0;
    int isBuy;
    int quantity;
    int maxQuantity;
    vector<int> indexes;
    Package() {};
    Package(std::string i) {
        char delimiter = ' ';
        std::vector<std::string> order;
        size_t start = 0;
        size_t end = 0;
        while ((end = i.find(delimiter, start)) != std::string::npos)
        {
            order.push_back(i.substr(start, end - start));
            start = end + 1;
        }
        order.push_back(i.substr(start));
        for(int j = 0; j<order.size()-3; j+=2){
            stocks.insert(order[j],stoi(order[j+1]));
        }
        stocks.nodeCount = (order.size() - 2)/2;
        isBuy = (order[order.size()-1] == "b") ? 1 : -1;
        if(order.size()%2==0) {
            price = stoi(order[order.size()-2]);
            quantity=1;
        }
        else {
            quantity = stoi(order[order.size()-2]);
            price = stoi(order[order.size()-3]);
        }
        maxQuantity = quantity;
    }
    
    Package(RedBlackTree<int> input, int isBuy, int price, vector<int> indexes, int quantity) : stocks(input), isBuy(isBuy), price(price) ,indexes(indexes), quantity(quantity), maxQuantity(quantity) {};
    Package(const Package& other)
    : price(other.price), isBuy(other.isBuy), indexes(other.indexes), quantity(other.quantity),maxQuantity(other.maxQuantity){
        RedBlackTree<int> temp (other.stocks);
        stocks = temp;
    }
    bool operator==(Package& rhs){
        return (this->stocks == rhs.stocks);
    }

    Package operator*(int rhs){
        RedBlackTree<int> temp = this->stocks;
        for(auto i: temp) temp.search(i.first) = i.second * rhs;
        return Package(temp,this->isBuy,this->price*rhs, this->indexes, this->quantity);
    }

    Package operator+(Package& rhs)
    {
        RedBlackTree<int> temp = this->stocks; 
        for(auto i: temp) temp.search(i.first) = i.second * this->isBuy;
        for(auto i : rhs.stocks){
            temp.search(i.first) = temp.search(i.first) + (i.second)*(rhs.isBuy);
        }
        int res = this->price*this->isBuy + rhs.price*rhs.isBuy;
        return Package(temp,1,res, this->indexes,this->quantity);
    }

    bool isArbitrage(){
        for(auto i : stocks){
            if(i.second != 0){
                return false;
            }
        }
        return true;
    }
    void printPackage(){
        for(auto i : stocks){
            std::cout << i.first.name << " " << i.second << " ";
        }
        std::cout << price << " ";
        char b;
        b = (isBuy == 1) ? 's' : 'b';
        std::cout << quantity<<" max "<<maxQuantity<< " " << b << "#" << std::endl;
    }
};


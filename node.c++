#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <unordered_map>

class node{

    int id;
    std::vector<int> edges;

public:
    node(int);
    void addEdge(int);
    bool checkEdge(int);
    int getId();
    void traverse(std::vector<node*>&, int);
    std::vector<int> getEdges();

};

std::vector<int> node::getEdges(){
    return edges;
}

node::node(int in){
    id = in;
}

void node::addEdge(int newNode){

    edges.push_back(newNode);
}

bool node::checkEdge(int checkNode){
    return find(edges.begin(), edges.end(), checkNode) != edges.end();
}

int node::getId(){
    return id;
}

class graph{

    std::vector<node> nodes;
public:
    bool addNode(int);
    void addEdge(int, int);
    bool containsNode(int);
    node* getNode(int);
    int getCount();
    void BFS(std::unordered_map<int,int>&, int, int);
};


bool graph::addNode(int id){
    using namespace std;
    if(containsNode(id))
        return false;

    node newNode(id);
    //cout << "id " << newNode.getId() << endl;
    nodes.push_back(newNode);
    return true;
}


bool graph::containsNode(int id){
    std::vector<node>::iterator it = nodes.begin();
    while (it!=nodes.end()){
        if((*it).getId()==id)
            return true;
        it++;
    }
    return false;
}

node* graph::getNode(int id){
    std::vector<node>::iterator it = nodes.begin();
    while (it!=nodes.end()){
        if((*it).getId()==id)
            return &(*it);
        it++;
    }
    return 0;
}

int graph::getCount(){
    return nodes.size();
}

void graph::BFS(std::unordered_map<int,int>& found, int id, int TTL){

    using namespace std;
    if(TTL==0)
        return;
    node* current = getNode(id);
    vector<int> edges = current->getEdges();
    std::vector<int>::iterator it = edges.begin();
    while (it!=edges.end()){
        if(found.find(*it) == found.end()){
            found[*it] = TTL-1;
            if(found[*it]>0)
                BFS(found, *it, TTL-1);
        }
        else{
            if(TTL-1>found[*it])
                found[*it] = TTL-1;
            if(found[*it]>0&&found[*it]<TTL)
                BFS(found, *it, TTL-1);
        }

        it++;
    }
}


void graph::addEdge(int a, int b){

    using namespace std;
    if(!containsNode(a)){
        addNode(a);
    }
    if(!containsNode(b)){
        addNode(b);
    }
    node* nodeA = getNode(a);
    node* nodeB = getNode(b);

    nodeA->addEdge(b);
    nodeB->addEdge(a);

}

int main(){
    using namespace std;
    int num;
    int count = 1;
    cin >> num;
    while(num!=0){
        graph g;
        int a, b;
        
        for(int i = 0; i < num; i++){
            cin >> a;
            cin >> b;
            g.addEdge(a, b);
        }

        cin >> a;
        cin >> b;
        while(a!=0||b!=0){
            if(!g.containsNode(a)){
                cout << "Case " << count << ": " << g.getCount() << " nodes not reachable from node " << a << " with TTL = " << b << ".";
                count++;
            }
            else{
                unordered_map<int,int> found;
                found[a]=b;
                g.BFS(found, a, b);
                cout << "Case " << count << ": " << g.getCount()-found.size() << " nodes not reachable from node " << a << " with TTL = " << b << ".";
                count++;
            }
            cin >> a;
            cin >> b;
            if(a!=0||b!=0)
                cout << endl;
        }
        cin >> num;
        if(num!=0)
            cout << endl;
        //cout << num << endl;
    }
    return 0;
}
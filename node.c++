#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <unordered_map>
#include <queue>

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

    std::unordered_map<int,node*> nodes;
public:
    bool addNode(int);
    void addEdge(int, int);
    bool containsNode(int);
    node* getNode(int);
    int getCount();
    void BFS(std::unordered_map<int,int>&, std::queue<int>&, int, int);
};


bool graph::addNode(int id){
    using namespace std;
    if(containsNode(id))
        return false;

    node* newNode = new node(id);
    nodes[id]=newNode;
    return true;
}


bool graph::containsNode(int id){
    return nodes.find(id)!=nodes.end();
}

node* graph::getNode(int id){
    return nodes[id];
}

int graph::getCount(){
    return nodes.size();
}

void graph::BFS(std::unordered_map<int,int>& found, std::queue<int>& toCheck, int id, int TTL){

    using namespace std;
    node* current = getNode(id);
    vector<int> edges = current->getEdges();
    std::vector<int>::iterator it = edges.begin();
    while (it!=edges.end()){
        if(found.find(*it)==found.end()){
            found[*it]=TTL-1;
            toCheck.push(*it);
        }
        else
            if(found[*it]<TTL-1){
                found[*it]=TTL-1;
                toCheck.push(*it);
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
                std::queue<int> toCheck;
                unordered_map<int,int> found;
                found[a]=b;
                toCheck.push(a);
                while(toCheck.size()>0){
                    //cout << toCheck.size() << endl;
                    int next = toCheck.front();
                    toCheck.pop();
                    g.BFS(found, toCheck, next, found[next]);

                }
                std::unordered_map<int,int>::iterator it = found.begin();
                int counter=0;
                while (it!=found.end()){
                    if(it->second>=0)
                        counter++;
                    it++;
                }
                cout << "Case " << count << ": " << g.getCount()-counter << " nodes not reachable from node " << a << " with TTL = " << b << ".";
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
    }
    return 0;
}
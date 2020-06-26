#include "graph.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;


/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */

template<typename T>
T min(T& x, T& y){
    return (x < y) ? (x) : (y);
}

Graph::Node *Graph::makeNode(const string &label) {
    Node* tmp = new Node(label);
    nodeList.sortedPush(tmp, [](ListNode<Node*>* n, Node* cmp){
        return (*(n->data) < *cmp && (n->next == nullptr || (*cmp < *(n->next->data))));
    });
    size++;
    return tmp;
}

int Graph::initNode(Graph::Node *&nodeA, Graph::Node *&nodeB, const string &labelA, const string &labelB) {
    int result = 0;

    nodeA = getNodeByLabel(labelA);
    nodeB = getNodeByLabel(labelB);

    if(nodeA == nullptr){
        nodeA = makeNode(labelA);
        result = 1;
    }

    if(nodeB == nullptr){
        nodeB = makeNode(labelB);
        result = 1;
    }

    return result;

}

void Graph::recurDFS(Graph::Node *target, List<Node *> &visit, List<Node *> &result) {
    if(visit.isExist(target)) return;
    result.append(target);
    visit.append(target);

    for (auto i =target->undirectedList().begin(); i != nullptr; i = i->next){
        recurDFS(i->data.first(), visit, result);
    }

}

string Graph::sort(string *tmp, int length, string sep) {
    string result;
    for(int i = 0; i < length; i++){
        string min = tmp[i];
        for(int sub = i; sub < length; sub++){
            bool condition = (isInteger(tmp[sub]) && isInteger(min)) ? (stoi(tmp[sub]) < stoi(min)) : (tmp[sub] < min);
            if(condition){
                min = tmp[sub];
                T_swap<string>(tmp[i], tmp[sub]);
            }
        }

        result += min;
        if(i != length-1) { result += sep; }
    }

    return result;
}

string Graph::makeLexiStr(List<string> &target, string sep) {
    string tmp[target.size()];
    int counter = 0;
    for(auto t = target.begin(); t != nullptr; t = t->next){ tmp[counter++] = t->data; }

    return sort(tmp, target.size(), sep);
}

string Graph::makeNodeStr(List<Node *> &target, string sep) {
    string result;

    for(auto t = target.begin(); t != nullptr; t = t->next) {
        result += t->data->label();
        if(t != target.end()) { result += sep; }
    }

    return result;
}

string Graph::makeLexiStr(List<Node *> &target, string sep) {
    string tmp[target.size()];
    int counter = 0;
    for(auto t = target.begin(); t != nullptr; t = t->next){ tmp[counter++] = t->data->label(); }

    return sort(tmp, target.size(), sep);
}

Graph::Node *Graph::getNodeByLabel(const string &label) {
    for(auto i = nodeList.begin(); i != nullptr; i = i->next){
        if(i->data->label() == label){
            return i->data;
        }
    }
    return nullptr;
}

bool isInteger(const string &str) {
    for(char i: str){ if(!isdigit(i)) { return false; } }
    return true;
}

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////


int Graph::addDirectedEdge(string nodeA, string nodeB) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    Node* targetA = nullptr, *targetB = nullptr;
    int result = initNode(targetA, targetB, nodeA, nodeB);

    targetA->directLink(targetB, 1);
    return result;
    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

int Graph::addDirectedEdge(string nodeA, string nodeB, int weight) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    Node* targetA = nullptr, *targetB = nullptr;
    int result = initNode(targetA, targetB, nodeA, nodeB);

    targetA->directLink(targetB, weight);
    return result;

    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

int Graph::addUndirectedEdge(string nodeA, string nodeB) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    Node* targetA = nullptr, *targetB = nullptr;
    int result = initNode(targetA, targetB, nodeA, nodeB);

    targetA->undirectLink(targetB, 1);
    targetB->undirectLink(targetA, 1);
    return result;

    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

int Graph::addUndirectedEdge(string nodeA, string nodeB, int weight) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    Node* targetA = nullptr, *targetB = nullptr;
    int result = initNode(targetA, targetB, nodeA, nodeB);

    targetA->undirectLink(targetB, weight);
    targetB->undirectLink(targetA, weight);
    return result;

    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}


string Graph::DFS() {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    List<Node*> visit;
    List<string> resultStrList;
    for(auto i = nodeList.begin(); i != nullptr; i = i->next){
        if(visit.isExist(i->data)){ continue; }
        List<Node*> result;
        recurDFS(i->data, visit, result);
        resultStrList.append(makeNodeStr(result, " "));
    }

    string result = makeLexiStr(resultStrList, "\n");
    return result;

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

string Graph::getTopologicalSort() {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    List<Node*> visit;
    List<string> resultStrList;
    for(auto i = nodeList.begin(); i != nullptr; i = i->next){
        if(visit.isExist(i->data)){ continue; }
        List<Node*> result;
        List<Node*> test;

        if(!TOPO(i->data, visit, test, result)){
            return "error";
        };
        resultStrList.append(makeNodeStr(result, " "));
    }

    string result = makeLexiStr(resultStrList, "\n");
    return result;

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

string Graph::getShortestPath(string source, string destination) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    Node* src = getNodeByLabel(source);
    Node* dst = getNodeByLabel(destination);

    if(src == nullptr || dst == nullptr) { return "error"; }

    if(!checkPath(src, dst)){ return "error"; }
    List<string> resultStrList;
    Index<Node*> index(nodeList);
    DijkList l;
    DijkVector* v = initVector();

    for(int i = 0; i < nodeList.size(); i++){
        v->second()[i].first() = index[i];
        v->second()[i].second() = INF;
    }

    v->second()[index[src]].first() = src;
    v->second()[index[src]].second() = 0;


    dijk(src, dst, 0, *v, l, index);

    for(auto i = l.begin(); i != nullptr; i = i->next){
        string result;

        for(Node* target = dst; target != src; target = i->data->second()[index[target]].first()){
            result = target->label() + " " + result;
        }
        result = src->label() + " " + result;
        result += to_string(i->data->second()[index[dst]].second());
        resultStrList.append(result);
    }

    string result = makeLexiStr(resultStrList, "\n");
    return result;

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

string Graph::getAllShortestPaths() {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    Index<Node*> index (nodeList);
    auto weight = new long long *[nodeList.size()];
    for(int i = 0; i <nodeList.size(); i++){
        weight[i] = new long long[nodeList.size()];
        for(int j = 0; j < nodeList.size(); j++){
            weight[i][j] = (i == j) ? (0) : (((long long)INF) * 2 + 1);
        }
    }

    for(auto i = nodeList.begin(); i != nullptr; i = i->next){
        for(auto j = i->data->directedList().begin(); j != nullptr; j = j->next){
            weight[index[i->data]][index[j->data.first()]] = j->data.second();
        }
    }

    for(int k = 0; k < nodeList.size(); k++){
        for(int i = 0; i < nodeList.size(); i++){
            for(int j = 0; j < nodeList.size(); j++){
                weight[i][j] = min(weight[i][j],
                        (weight[i][k] >= INF || weight[k][j] >= INF) ? (INF) :(weight[i][k] + weight[k][j]));
            }
        }
    }

    string result;
    for(int i = 0; i < nodeList.size(); i++){
        for(int j = 0; j < nodeList.size(); j++){

            result += (weight[i][j] >= (long long)INF) ? ("INF") : (to_string(weight[i][j]));
            result += " ";
        }
        result.pop_back();
        result += "\n";
    }
    result.pop_back();
    return result;

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

int Graph::primMST(ofstream &fout, string startNode) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    List<NodeWeight> sorted;
    List<Node*> visit;
    int length = 0;

    Node* start = getNodeByLabel(startNode);

    PRIM(fout, start, sorted, visit, length);

    return length;

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

int Graph::kruskalMST(ofstream &fout) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    int length = 0;
    List<string> resultStrList;
    List<NodeWeight> weightList;

    initWeightList(weightList);

    for(auto i = weightList.begin(); i != nullptr; i = i->next){
        List<Node*> visit;
        NodePair p = i->data.first();
        Node* from = p.first();
        Node* to = p.second();
        int weight = i->data.second();

        kruskalDFS(from, visit);
        if(visit.isExist(to)) continue;
        from->kruskal().append(to);
        to->kruskal().append(from);
        string s = from->label() + " " + to->label()+ " " + to_string(weight);
        resultStrList.append(s);
        length += weight;
    }

    for(auto i = nodeList.begin(); i != nullptr; i = i->next){
        i->data->kruskal().reset();
    }

    string result = makeLexiStr(resultStrList, "\n");
    fout << result << endl;
    return length;

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}



#include "graph.h"
#include <iostream>
#include <string>

using namespace std;


/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */
Graph::Node *Graph::getNodeByLabel(const string &label) {
    for(auto i = nodeList.begin(); i != nullptr; i = i->next){
        if(i->data->label() == label){
            return i->data;
        }
    }
    return nullptr;
}

Graph::Node *Graph::genNode(const string &label) {
    Node* tmp = new Node(label);
    nodeList.append(tmp);
    size++;
    return tmp;
}

void Graph::initVisitArray(Graph::Check *isVisited) {
    int counter = 0;
    for(auto i = nodeList.begin(); i != nullptr; i = i->next) {
        isVisited[counter++] = (Check) { i->data, false };
    }
}

bool Graph::checkVisited(Graph::Node *target, Graph::Check *isVisited) {
    for(int i = 0; i < size; i++){
        if(isVisited[i].data == target && isVisited[i].isVisited){ return true; }
    }
    return false;
}

int Graph::_connected(Graph::Node *target, Graph::Check *visit, List<Node *> &result) {
    int len = 0;

    for(auto i = 0; i < size; i++){
        if(visit[i].data == target){
            visit[i].isVisited=true; break;
        }
    }

    result.append(target);
    for(auto i = target->undirectedList().begin(); i != nullptr; i = i->next){
        if(checkVisited(i->data, visit)) { continue; }
        len += 1 + _connected(i->data, visit, result);
    }

    return len;
}

string Graph::makeLexiStr(List<Node *> &target) {
    string tmp;
    string result;

    for(auto t = target.begin(); t != nullptr; t = t->next){ tmp += t->data->label(); }
    int length = tmp.length();

    for(int i = 0; i < length; i++){
        char min = tmp[i];
        for(int sub = i; sub < length; sub++){
            if(tmp[sub] < min){
                min = tmp[sub];
                T_swap<char>(tmp[i], tmp[sub]);
            }
        }

        result += min;
        if(i != length-1) { result += " "; }
    }

    return result;
}

int Graph::_numCycle(Graph::Node *start, Graph::Node *target, Check *visit, List<Node *> &check, int depth) {
    Check* current;
    int result = 0;
    for(int i = 0; i < size; i++){
        if(visit[i].data == target){
            current = &(visit[i]); break;
        }
    }

    if(depth > 0 && start == target) { return 1; }
    if(current->isVisited || check.isExist(target)) { return 0; }

    for(auto i = target->directedList().begin(); i != nullptr; i = i->next){
        current->isVisited = true;
        result += _numCycle(start, i->data, visit, check, depth + 1);
        current->isVisited = false;
    }

    return result;
}

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////


int Graph::addEdge(string nodeA, string nodeB) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    int result = 0;
    Node* targetA = getNodeByLabel(nodeA);
    Node* targetB = getNodeByLabel(nodeB);

    if(targetA == nullptr){
        targetA = genNode(nodeA);
        result = 1;
    }

    if(targetB == nullptr){
        targetB = genNode(nodeB);
        result = 1;
    }

    targetA->undirectLink(targetB);
    targetB->undirectLink(targetA);
    targetA->directLink(targetB);
    return result;

    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

string Graph::getConnectedComponent() {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    auto* visit = new Graph::Check[size];
    string result;
    int maxLen = 0;

    for(auto i = nodeList.begin(); i != nullptr; i = i->next){
        List<Node*> tmp;
        string tmpStr;
        initVisitArray(visit);
        int length = _connected(i->data, visit, tmp);

        tmpStr = makeLexiStr(tmp);
        if((length > maxLen) || (length == maxLen && tmpStr < result)){
            result = tmpStr;
            maxLen = length;
        }

    }


    return result;

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

int Graph::getCycleCount() {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    auto* visit = new Graph::Check[size];
    int result = 0;
    List<Node*> check;

    initVisitArray(visit);

    for(auto i = nodeList.begin(); i != nullptr; i = i->next){
        initVisitArray(visit);
        result += _numCycle(i->data, i->data, visit, check, 0);
        check.append(i->data);
    }

    return result;

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

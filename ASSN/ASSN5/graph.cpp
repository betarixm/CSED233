#include "graph.h"
#include <iostream>
#include <string>

using namespace std;


/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////


int Graph::addEdge(string nodeA, string nodeB) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    Node* targetA = getNodeByLabel(nodeA);
    Node* targetB = getNodeByLabel(nodeB);

    if(targetA == nullptr){
        targetA = genNode(nodeA);
    }

    if(targetB == nullptr){
        targetB = genNode(nodeB);
    }

    targetA->undirectLink(targetB);
    targetB->undirectLink(targetA);
    targetA->directLink(targetB);
    return 0;

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
        Graph::List<Node*> tmp;
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
    List<Node*> isChecked;

    for(auto i = nodeList.begin(); i != nullptr; i = i->next){
        if(isChecked.isExist(i->data)){
            continue;
        } else {
            initVisitArray(visit);
            result += _numCycle(i->data, i->data, visit,isChecked, 0);
        }

    }

    return result;

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

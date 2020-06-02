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

    targetA->link(targetB);
    targetB->link(targetA);

    return 0;

    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

string Graph::getConnectedComponent() {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    auto* isVisited = new Graph::Check[size];
    string result;
    int maxLen = 0;

    for(auto i = nodeList.begin(); i != nullptr; i = i->next){
        Graph::List<Node*> tmp;
        string tmpStr;
        initVisitArray(isVisited);
        int length = _connected(i->data, isVisited, tmp);
        if(length >= maxLen) {
            tmp.append(i->data);
            tmpStr = makeLexiStr(tmp);
            if((length > maxLen) || (length == maxLen && tmpStr < result)){
                result = tmpStr;
            }
        }

    }


    return result;

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

int Graph::getCycleCount() {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    return 0;

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

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
    try{
        stoi(str);
        return true;
    } catch( ... ){
        return false;
    }
}

void Graph::updateTopoRefCount(List<Node *> &v) {
    for(auto i = nodeList.begin(); i != nullptr; i = i->next){
        if(v.isExist(i->data)) { continue; }
        for(auto j = i->data->directedList().begin(); j != nullptr; j=j->next){
            j->data.first()->topoRefCount() += 1;
        }
    }
}

void Graph::copyDijkVector(Graph::DijkVector &src, Graph::DijkVector &dst) {
    for(auto i = src.first()->begin(); i != nullptr; i = i->next){
        dst.first()->append(i->data);
    }
    for(int i = 0; i < nodeList.size(); i++){
        dst.second()[i] = src.second()[i];
    }
}

Graph::DijkVector *Graph::initDijkVector() {
    auto v = new DijkVector(new CheckVector, new Dist[nodeList.size()]);
    for(int i = 0; i < nodeList.size(); i++){
        v->second()[i].first() = new PathVector;
        v->second()[i].second() = INF;
    }

    return v;
}

void Graph::dijkString(string origin, Graph::Node *target, Graph::Node *src, Graph::DijkVector &v, List<string> &result,
                       Index<Node *> &index) {
    if(target == src){
        if (!result.isExist(origin)){result.append(origin);}
        return;
    }

    PathVector* p = v.second()[index[target]].first();
    for(auto i = p->begin(); i != nullptr; i = i->next){
        string label = i->data->label() + " " + origin;
        dijkString(label, i->data, src, v, result, index);
    }
}

void
Graph::dijk(Graph::Node *target, Graph::Node *dst, long long int targetDist, Graph::DijkVector &v, Graph::DijkList &l,
            Index<Node *> &index) {
    auto k = initDijkVector();
    copyDijkVector(v, *k);

    CheckVector* check = k->first();
    DistArray distArray = k->second();

    check->append(target);

    for(auto fri = target->directedList().begin(); fri != nullptr; fri = fri->next){
        Dist* current = &(distArray[index[fri->data.first()]]);
        long long test = targetDist + fri->data.second();
        long long orin = current->second();

        if(test < orin){
            current->second() = test;
            current->first()->reset(), current->first()->append(target);
        } else if (test == orin) {
            if(!current->first()->isExist(target)) { current->first()->append(target); }
        }
    }

    if(check->size() == nodeList.size()){
        l.append(k); return;
    }

    long long min = INF;
    for(auto i = nodeList.begin(); i != nullptr; i = i->next){
        if(check->isExist(i->data)){ continue; }
        long long weight = k->second()[index[i->data]].second();
        if(weight < min){
            min = weight;
        }
    }

    for(auto i = nodeList.begin(); i != nullptr; i = i->next){
        if(check->isExist(i->data)){ continue;}
        if(k->second()[index[i->data]].second() == min){
            dijk(i->data, dst, min, *k, l, index);
        }
    }

}

bool Graph::checkPath(Graph::Node *src, Graph::Node *dst) {
    List<Node*> visit;
    pathDfs(src, visit);

    return visit.isExist(dst);
}

void Graph::pathDfs(Graph::Node *target, List<Node *> &visit) {
    if(visit.isExist(target)){ return; }
    visit.append(target);
    for(auto i = target->directedList().begin(); i != nullptr; i = i->next){
        pathDfs(i->data.first(), visit);
    }
}

void Graph::PRIM(ofstream &fout, Graph::Node *target, List<NodeWeight> &sorted, List<Node *> &visit, int &length) {
    visit.append(target);
    for(auto i = target->undirectedList().begin(); i != nullptr; i = i->next){
        if(visit.isExist(i->data.first())){ continue; }
        auto tmp = NodeWeight (NodePair (target, i->data.first()),i ->data.second());

        sorted.sortedPush(tmp, [](ListNode<NodeWeight>* n, NodeWeight cmp){
            Node* n_from = n->data.first().first(), * c_from = cmp.first().first();
            Node* n_to = n->data.first().second(), * c_to = cmp.first().second();
            int n_weight = n->data.second(), c_weight = cmp.second();
            auto next = n->next;

            return (n_weight == c_weight)?
                   (   (n_to->label() == c_to->label())?
                       ((*(n_from) < *(c_from)) && (next == nullptr || ((c_weight < n->next->data.second())))):
                       ((*(n_to) < *(c_to)) && (next == nullptr || ((c_weight < n->next->data.second()))))):
                   ((n_weight < c_weight) &&
                    (next == nullptr || (((c_weight == next->data.second())?((c_to->label() == next->data.first().second()->label())?((*(c_from) < *(next->data.first().first()))):(*(c_to) < *(next->data.first().second()))):(c_weight < n->next->data.second())))));
        });
    }

    for(auto i = sorted.begin(); i != nullptr; i = i->next){
        NodePair pair = i->data.first();
        int weight = i->data.second();
        if(visit.isExist(pair.second())){ continue; }
        fout << pair.first()->label() << " " << pair.second()->label() << " " << weight << endl;
        length += weight;
        PRIM(fout, pair.second(), sorted,visit, length);
    }
}

bool Graph::isDupWeight(Graph::Node *from, Graph::Node *to, List<NodeWeight> &weightList) {
    for(auto j = weightList.begin(); j != nullptr; j = j->next){
        NodeWeight tmp = j->data;
        if(tmp.first() == NodePair(to, from) || tmp.first() == NodePair(from, to)){ return true; }
    }
    return false;
}

void Graph::initWeightList(List<NodeWeight> &weightList) {
    for(auto i = nodeList.begin(); i != nullptr; i = i->next){
        Node* from = i->data;
        for(auto fre = from->undirectedList().begin(); fre != nullptr; fre = fre->next){
            Node* to = fre->data.first();
            int weight = fre->data.second();
            if(isDupWeight(from, to, weightList)) { continue; }
            NodePair p = (from->label() < to->label()) ? (NodePair(from, to)) : (NodePair(to, from));
            weightList.sortedPush(NodeWeight(p, weight), [](ListNode<NodeWeight>* n, NodeWeight cmp){
                Node* n_from = n->data.first().first(), * c_from = cmp.first().first();
                Node* n_to = n->data.first().second(), * c_to = cmp.first().second();
                int n_weight = n->data.second(), c_weight = cmp.second();

                return (n_weight == c_weight)
                       ?( (n_to->label() == c_to->label())
                          ? (*(n_from) < *(c_from) && (n->next == nullptr || ((c_weight < n->next->data.second()) || *c_from < *(n->next->data.first().first()))))
                            : (*(n_to) < *(c_to) && (n->next == nullptr || ((c_weight < n->next->data.second()) || *c_to < *(n->next->data.first().second()))))
                            )
                       :(n_weight < c_weight && (n->next == nullptr || (
                               (c_weight == n->next->data.second())?
                               (
                                       (c_to->label() == n->next->data.first().second()->label())?(c_from->label() <= n->next->data.first().first()->label()):(c_to->label() <= n->next->data.first().second()->label())
                               ):(c_weight < n->next->data.second()))));
            });
        }
    }
}

void Graph::kruskalDFS(Graph::Node *target, List<Node *> &visit) {
    if(visit.isExist(target)) { return; }
    visit.append(target);
    for(auto i = target->kruskal().begin(); i != nullptr; i = i->next){
        kruskalDFS(i->data, visit);
    }
}


bool Graph::Node::isLinked(Graph::Node *target, List<Pair<Node *, int>> &v) {
    for(auto i = v.begin(); i != nullptr; i=i->next){
        if(i->data.first() == target){
            return true;
        }
    }
    return false;
}

Graph::Node &Graph::Node::undirectLink(Graph::Node *target, int weight) {
    if(isLinked(target, _undirectedList)){ return *this; }
    _undirectedList.sortedPush(Pair<Node*, int>(target, weight), [](ListNode<Pair<Node*, int>>* n, Pair<Node*, int> cmp){
        return (*(n->data.first()) < *(cmp.first()) && (n->next == nullptr || (*cmp.first() < *(n->next->data.first()))));
    });
    return *this;
}

Graph::Node &Graph::Node::directLink(Graph::Node *target, int weight) {
    if(isLinked(target, _directedList)){ return *this; }
    _directedList.sortedPush(Pair<Node*, int>(target, weight), [](ListNode<Pair<Node*, int>>* n, Pair<Node*, int> cmp){
        return (*(n->data.first()) < *(cmp.first()) && (n->next == nullptr || (*cmp.first() < *(n->next->data.first()))));
    });
    return *this;
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

    List<Node*> result;

    while(true){
        bool isModified = false;

        initTopoRefCount();
        updateTopoRefCount(result);

        if([&](){for(auto i = nodeList.begin(); i != nullptr; i = i->next){
            if(result.isExist(i->data)) { continue;}
            if(i->data->topoRefCount() == 0){
                result.append(i->data);
                return true;
            }
        }
            return false;
        }()){ isModified = true; }

        if(!isModified) break;
    }

    if (result.size() == 0){
        return "error";
    } else {
        string resultStr;
        for(auto i = result.begin(); i != nullptr; i = i->next){
            resultStr += i->data->label() + " ";
        }
        resultStr.pop_back();
        return resultStr;
    }


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
    DijkVector* v = initDijkVector();

    v->second()[index[src]].first()->append(src);
    v->second()[index[src]].second() = 0;

    dijk(src, dst, 0, *v, l, index);

    for(auto i = l.begin(); i != nullptr; i = i->next){
        dijkString(dst->label() + " " + to_string(i->data->second()[index[dst]].second()), dst, src, *(i->data), resultStrList, index);
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
        fout << s << endl;
        length += weight;
    }

    for(auto i = nodeList.begin(); i != nullptr; i = i->next){
        i->data->kruskal().reset();
    }

    return length;

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}



#pragma once
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

/////////////////////////////////////////////////////////
///  TODO: Add Your Struct or Functions if required /////




template<typename T>
void T_swap(T& a, T&b){
    T tmp = a;
    a = b;
    b = tmp;
}

bool isInteger(const string& str);

template<typename T>
struct ListNode{
    T data;
    ListNode* next;
    ListNode(T _data, ListNode* _next): data(_data), next(_next) {};
};

template<typename T>
class List{
private:

protected:
    ListNode<T>* l_begin, *l_end;
    int l_size = 0;
public:


    List(): l_size(0), l_begin(nullptr), l_end(nullptr) {};
    List& append(T data){
        auto tmp = new ListNode<T>(data, nullptr);

        if(l_size == 0){
            l_begin = tmp;
        } else {
            l_end->next = tmp;
        }
        l_end = tmp;
        l_size++;
        return *this;
    }

    List& sortedPush(T data, bool (*test)(ListNode<T>*, T)){
        auto tmp = new ListNode<T>(data, nullptr);

        if(l_size == 0){
            l_begin = tmp;
            l_end = tmp;
        } else {
            ListNode<T>* i = l_begin;
            for(; i != nullptr; i = i->next){ if(test(i, data)){ break; } }

            if(i == nullptr){
                tmp->next = l_begin;
                l_begin = tmp;
            } else {
                tmp->next = i->next;
                i->next = tmp;

                if(tmp->next == nullptr) { l_end = tmp; }
            }

        }

        l_size++;
        return *this;
    }

    List& insert(ListNode<T>* target, T data){
        auto tmp = new ListNode<T>(data, nullptr);
        if(target == nullptr){
            tmp->next = l_begin;
            l_begin = tmp;
        } else {
            tmp->next = target->next;
            target->next = tmp;
            if(target == l_end){ l_end = tmp; }
        }
        l_size++;
        return *this;
    }

    ListNode<T>* begin() const { return l_begin; }
    ListNode<T>* end() const { return l_end; }

    bool isExist(T& target){
        for(ListNode<T>* i = l_begin; i != nullptr; i = i->next){
            if (i->data == target){
                return true;
            }
        }
        return false;
    }

    void reset(){
        for(ListNode<T>* i = l_begin, *k; i != nullptr; i = k){
            k = i->next;
            delete i;
        }
        l_size = 0;
    }


    int size() const { return l_size; }

    List operator=(List& target){
        target.reset();
        for(auto i = l_begin; i != nullptr; i = i->next){
            target.append(i->data);
        }
        return *this;
    }

};

template<typename X, typename Y>
class Pair{
private:
    X _first;
    Y _second;
public:
    Pair(X x, Y y): _first(x), _second(y) {};
    Pair(): _first(NULL), _second(NULL) {};
    X& first(){ return _first; }
    Y& second() { return _second; }

    Pair& operator=(Pair target){
        _first = target.first();
        _second = target.second();
        return *this;
    }

    bool operator<(const Pair<X,Y>& rhs){
        if(is_pointer<X>::value){
            return *(_first) < *(rhs._first);
        }
        return _first < rhs._first;
    }

    bool operator==(const Pair<X,Y> target){
        return target._first == _first && _second == target._second;
    }
};

template<typename T>
class Index{
private:
    T* data;
    int size;
    int counter = 0;
public:
    explicit Index(int _size): size(_size), data(new T[_size]) {};
    explicit Index(List<T> list): size(list.size()), data(new T[list.size()]){
        for(auto i = list.begin(); i != nullptr; i = i->next){
            push(i->data);
        }
    }
    void push(T _data){ if(counter < size){ data[counter++] = _data; } }

    T operator[](int idx){ return data[idx]; }

    int operator[](T idx){
        for(int i = 0; i < size; i++){ if (data[i] == idx){ return i; } }
        return -1;
    }
};


///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

class Graph{
public:
    Graph() { };
    ~Graph() { };

    int addDirectedEdge(string nodeA, string nodeB);
    int addDirectedEdge(string nodeA, string nodeB, int weight);
    int addUndirectedEdge(string nodeA, string nodeB);
    int addUndirectedEdge(string nodeA, string nodeB, int weight);

    string DFS();
    string getTopologicalSort();
    string getShortestPath(string source, string destination);
    string getAllShortestPaths();
    int primMST(ofstream &, string startNode);
    int kruskalMST(ofstream &);


private:
    /////////////////////////////////////////////////////////
    //////  TODO: Add private members if required ///////////
    const long long INF = (~(unsigned int)0 >> 1) + 1;

    class Node{
    private:
        string _label;

        List<Pair<Node*, int>> _undirectedList;
        List<Pair<Node*, int>> _directedList;
        List<Node*> _kruskal;
        int _topoRefCount = 0;
        bool isLinked(Node* target, List<Pair<Node*,int>>& v);

    public:
        explicit Node(const string& l) { _label = l; };
        string label() const { return _label; }
        int& topoRefCount (){ return _topoRefCount; };
        Node& undirectLink(Node* target, int weight);

        Node& directLink(Node* target, int weight);

        List<Pair<Node*, int>> undirectedList() const { return _undirectedList; }
        List<Pair<Node*, int>> directedList() const { return _directedList; }
        List<Node*>& kruskal() { return _kruskal; }
        bool operator< (const Node& rhs) const {
            if(isInteger(rhs.label()) && isInteger(label())){
                return stoi(label()) < stoi(rhs.label());
            } else {
                return label() < rhs.label();
            }
        }

    };

    struct Check{
        Node* data;
        bool isVisited;
    };

    List<Node*> nodeList;
    int size = 0;

    Node* getNodeByLabel(const string & label);

    Node* makeNode(const string & label);

    int initNode(Node*& nodeA, Node*& nodeB, const string& labelA, const string& labelB);

    void recurDFS(Node* target, List<Node*>& visit, List<Node*>& result);

    void initTopoRefCount(){
        for(auto i = nodeList.begin(); i != nullptr; i = i->next){ i->data->topoRefCount() = 0; }
    }

    void updateTopoRefCount(List<Node*>& v);

    string sort(string* tmp, int length, string sep);
    string makeLexiStr(List<Node *> &target, string sep);
    string makeLexiStr(List<string> &target, string sep);
    string makeNodeStr(List<Node *>& target, string sep);

    using CheckVector = List<Node*>;
    using PathVector = List<Node*>;
    using Dist = Pair<PathVector*, long long>;
    using DistArray = Dist*;
    using DijkVector = Pair<CheckVector*, DistArray>;
    using DijkList = List<DijkVector*>;

    void copyDijkVector(DijkVector& src, DijkVector& dst);

    DijkVector* initDijkVector();

    void dijkString(string origin, Node* target, Node* src, DijkVector& v, List<string>& result, Index<Node*>& index);

    void dijk(Node* target, Node* dst, long long targetDist, DijkVector& v, DijkList& l, Index<Node*>& index);

    bool checkPath(Node* src, Node* dst);

    void pathDfs(Node* target, List<Node*>& visit);

    using NodePair = Pair<Node*, Node*>;
    using NodeWeight = Pair<NodePair, int>;

    void PRIM(ofstream& fout, Node* target, List<NodeWeight>& sorted, List<Node*>& visit, int& length);

    bool isDupWeight(Node* from, Node* to, List<NodeWeight>& weightList);

    void initWeightList(List<NodeWeight>& weightList);

    void kruskalDFS(Node* target, List<Node*>& visit);
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};

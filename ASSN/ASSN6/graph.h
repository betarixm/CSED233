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


    int size() const { return l_size; }

};

template<typename X, typename Y>
class Pair{
private:
    X _first;
    Y _second;
public:
    Pair(const X x, const Y y): _first(x), _second(y) {};

    X first(){ return _first; }
    Y second() { return _second; }

    Pair operator=(Pair& target){
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

    class Node;


    class Node{
    private:
        string _label;

        List<Pair<Node*, int>> _undirectedList;
        List<Pair<Node*, int>> _directedList;


    public:
        explicit Node(const string& l) { _label = l; };
        string label() const { return _label; }

        Node& undirectLink(Node* target, int weight){
            _undirectedList.sortedPush(Pair<Node*, int>(target, weight), [](ListNode<Pair<Node*, int>>* n, Pair<Node*, int> cmp){
                return (*(n->data.first()) < *(cmp.first()) && (n->next == nullptr || (*cmp.first() < *(n->next->data.first()))));
            });
            return *this;
        }

        Node& directLink(Node* target, int weight){
            _directedList.sortedPush(Pair<Node*, int>(target, weight), [](ListNode<Pair<Node*, int>>* n, Pair<Node*, int> cmp){
                return (*(n->data.first()) < *(cmp.first()) && (n->next == nullptr || (*cmp.first() < *(n->next->data.first()))));
            });
            return *this;
        }

        List<Pair<Node*, int>> undirectedList() const { return _undirectedList; }
        List<Pair<Node*, int>> directedList() const { return _directedList; }
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

    void _DFS(Node* target, List<Node*>& visit, List<Node*>& result);

    void _TOPO(Node* target, List<Node*>& visit, List<Node*>& result){
        if(visit.isExist(target)) return;
        visit.append(target);

        for(auto i = target->directedList().begin(); i != nullptr; i = i->next){
            _TOPO(i->data.first(), visit, result);
        }

        result.insert(nullptr, target);
    }

    string sort(string* tmp, int length, string sep);
    string makeLexiStr(List<Node *> &target, string sep);
    string makeLexiStr(List<string> &target, string sep);
    string makeNodeStr(List<Node *>& target, string sep);

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};

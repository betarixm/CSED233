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

    bool TOPO(Node* target, List<Node*>& visit, List<Node*>& test, List<Node*>& result){
        bool isDone = true;
        test.sortedPush(target, [](ListNode<Node*>* n, Node* cmp){
            return (*(n->data) < *cmp && (n->next == nullptr || (*cmp < *(n->next->data))));
        });
        visit.append(target);
        result.append(target);

        for(auto i = target->directedList().begin(); i != nullptr; i = i->next){
            if(visit.isExist(i->data.first())) { return false; }
            test.sortedPush(i->data.first(), [](ListNode<Node*>* n, Node* cmp){
                return (*(n->data) < *cmp && (n->next == nullptr || (*cmp < *(n->next->data))));
            });
        }

        for(auto i = test.begin(); i != nullptr; i = i->next){
            if(result.isExist(i->data)){ continue; }
            isDone = TOPO(i->data, visit, test, result);
            break;
        }

        return isDone;
    }

    string sort(string* tmp, int length, string sep);
    string makeLexiStr(List<Node *> &target, string sep);
    string makeLexiStr(List<string> &target, string sep);
    string makeNodeStr(List<Node *>& target, string sep);

    using CheckVector = List<Node*>;
    using Dist = Pair<Node*, long long>;
    using DistArray = Dist*;
    using DijkVector = Pair<CheckVector*, DistArray>;
    using DijkList = List<DijkVector*>;
    DijkVector* initVector(){
        return new DijkVector(new CheckVector, new Dist[nodeList.size()]);
    }

    void copyDijkVector(DijkVector& src, DijkVector& dst){
        for(auto i = src.first()->begin(); i != nullptr; i = i->next){
            dst.first()->append(i->data);
        }
        for(int i = 0; i < nodeList.size(); i++){
            dst.second()[i] = src.second()[i];
        }
    }

    void dijk(Node* target, Node* dst, int d, DijkVector& v, DijkList& l, Index<Node*>& index){
        int targetDist = d;
        auto k = initVector();

        copyDijkVector(v, *k);
        k->first()->append(target);
        for(auto fre = target->directedList().begin(); fre != nullptr; fre = fre->next){
            if(k->first()->isExist(fre->data.first())) { continue; }
            int tmp = targetDist + fre->data.second();
            if(tmp < k->second()[index[fre->data.first()]].second()){
                k->second()[index[fre->data.first()]] = Dist(target, tmp);
            }
        }

        if(target == dst) {
            l.append(k);
            return;
        }

        Dist min = Dist(nullptr, INF);
        for(auto i = nodeList.begin(); i != nullptr; i = i->next){
            if(k->first()->isExist(i->data)) { continue; }
            if(k->second()[index[i->data]].second() < min.second()){
                min = k->second()[index[i->data]];
            }
        }

        for(auto i = nodeList.begin(); i != nullptr; i = i->next){
            if(k->first()->isExist(i->data)) { continue; }
            if(k->second()[index[i->data]].second() == min.second()){
                dijk(i->data, dst, min.second(),*k, l, index);
            }
        }
    }

    bool checkPath(Node* src, Node* dst){
        List<Node*> visit;
        pathDfs(src, visit);

        return visit.isExist(dst);
    }

    void pathDfs(Node* target, List<Node*>& visit){
        if(visit.isExist(target)){ return; }
        visit.append(target);
        for(auto i = target->directedList().begin(); i != nullptr; i = i->next){
            pathDfs(i->data.first(), visit);
        }
    }

    using NodePair = Pair<Node*, Node*>;
    using NodeWeight = Pair<NodePair, int>;

    void PRIM(ofstream& fout, Node* target, List<NodeWeight>& sorted, List<Node*>& visit, int& length){
        visit.append(target);
        for(auto i = target->undirectedList().begin(); i != nullptr; i = i->next){
            auto tmp = NodeWeight (NodePair (target, i->data.first()),i ->data.second());
            sorted.sortedPush(tmp, [](ListNode<NodeWeight>* n, NodeWeight cmp){
                Node* n_from = n->data.first().first(), * c_from = cmp.first().first();
                Node* n_to = n->data.first().second(), * c_to = cmp.first().second();
                int n_weight = n->data.second(), c_weight = cmp.second();

                return (n_weight == c_weight)
                       ?( (n_to->label() == c_to->label())
                          ? (*(n_from) < *(c_from) && (n->next == nullptr || ((c_weight < n->next->data.second()) || *c_from < *(n->next->data.first().first()))))
                          : (*(n_to) < *(c_to) && (n->next == nullptr || ((c_weight < n->next->data.second()) || *c_to < *(n->next->data.first().second()))))
                        )
                        :(n_weight < c_weight && (n->next == nullptr || (c_weight < n->next->data.second())));
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

    bool isDupWeight(Node* from, Node* to, List<NodeWeight>& weightList){
        for(auto j = weightList.begin(); j != nullptr; j = j->next){
            NodeWeight tmp = j->data;
            if(tmp.first() == NodePair(to, from) || tmp.first() == NodePair(from, to)){ return true; }
        }
        return false;
    }

    void initWeightList(List<NodeWeight>& weightList){
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
                           ?( (n_from->label() == c_from->label())
                              ? (*(n_to) < *(c_to) && (n->next == nullptr || ((c_weight < n->next->data.second()) || *c_to < *(n->next->data.first().second()))))
                              : (*(n_from) < *(c_from) && (n->next == nullptr || ((c_weight < n->next->data.second()) || *c_from < *(n->next->data.first().first())))))
                           :(n_weight < c_weight && (n->next == nullptr || (c_weight < n->next->data.second())));
                });
            }
        }
    }

    void kruskalDFS(Node* target, List<Node*>& visit){
        if(visit.isExist(target)) { return; }
        visit.append(target);
        for(auto i = target->kruskal().begin(); i != nullptr; i = i->next){
            kruskalDFS(i->data, visit);
        }
    }
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};

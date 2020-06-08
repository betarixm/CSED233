#pragma once
#include <string>

using namespace std;

/////////////////////////////////////////////////////////
///  TODO: Add Your Struct or Functions if required /////
template<typename T>
class List{
private:
    struct ListNode{
        T data;
        ListNode* next;
    };

    ListNode* l_begin, *l_end;
    int l_size = 0;
public:
    List(): l_size(0), l_begin(nullptr), l_end(nullptr) {};
    List& append(T data){
        auto* tmp = new ListNode;
        tmp->data = data;
        tmp->next = nullptr;

        if(l_size == 0){
            l_begin = tmp;
        } else {
            l_end->next = tmp;
        }
        l_end = tmp;
        l_size++;
        return *this;
    }

    List& push(T data){
        auto* tmp = new ListNode;
        tmp->data= data, tmp->next = l_begin;

        if(l_size == 0){
            l_end = tmp;
        }
        l_begin = tmp;
        l_size++;
        return *this;
    }

    List& insert(ListNode* target, T data){
        auto* tmp = new ListNode;
        tmp->data = data;
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

    ListNode* begin() const { return l_begin; }
    ListNode* end() const { return l_end; }

    bool isExist(T& target){
        for(ListNode* i = l_begin; i != nullptr; i = i->next){
            if (i->data == target){
                return true;
            }
        }
        return false;
    }

    int size() const { return l_size; }
};
///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

class Graph{
public:
    Graph() { };
    ~Graph() { };

    int addEdge(string nodeA, string nodeB);
    string getConnectedComponent();
    int getCycleCount();

private:
    /////////////////////////////////////////////////////////
    //////  TODO: Add private members if required ///////////



    class Node{
    private:
        string _label;
        List<Node*> _undirectedList;
        List<Node*> _directedList;
    public:
        explicit Node(const string& l) { _label = l; };
        string label() const { return _label; }

        Node& undirectLink(Node* target){
            _undirectedList.append(target);
            return *this;
        }

        Node& directLink(Node* target){
            _directedList.append(target);
            return *this;
        }
        List<Node*> undirectedList() const { return _undirectedList; }
        List<Node*> directedList() const { return _directedList; }
    };

    struct Check{
        Node* data;
        bool isVisited;
    };

    List<Node*> nodeList;
    int size = 0;

    Node* getNodeByLabel(const string& label);

    Node* genNode(const string& label);

    void initVisitArray(Check isVisited[]);

    bool checkVisited(Node* target, Check isVisited[]);

    int _connected(Node* target, Check visit[], List<Node*>& result);

    int _numCycle(Node* start, Node* target, Check visit[], List<Node*>& isChecked, int depth);

    string makeLexiStr(List<Node*>& target);

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};

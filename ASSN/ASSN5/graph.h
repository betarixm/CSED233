#pragma once
#include <string>

using namespace std;

/////////////////////////////////////////////////////////
///  TODO: Add Your Struct or Functions if required /////

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

    Node* getNodeByLabel(const string& label){
        for(auto i = nodeList.begin(); i != nullptr; i = i->next){
            if(i->data->label() == label){
                return i->data;
            }
        }
        return nullptr;
    }

    Node* genNode(const string& label){
        Node* tmp = new Node(label);
        nodeList.append(tmp);
        size++;
        return tmp;
    }

    void initVisitArray(Check isVisited[]){
        int counter = 0;
        for(auto i = nodeList.begin(); i != nullptr; i = i->next) {
            isVisited[counter++] = (Check) { i->data, false };
        }
    }

    bool checkVisited(Node* target, Check isVisited[]){
        for(int i = 0; i < size; i++){
            if(isVisited[i].data == target && isVisited[i].isVisited){ return true; }
        }
        return false;
    }

    int _connected(Node* target, Check visit[], List<Node*>& result) {
        int len = 0;

        for(auto i = 0; i < size; i++){
            if(visit[i].data == target){
                visit[i].isVisited=true; break;
            }
        }

        result.append(target);
        for(auto i = target->undirectedList().begin(); i != nullptr; i = i->next){
            if(checkVisited(i->data, visit)) { continue; }
            len = 1 + _connected(i->data, visit, result);
        }

        return len;
    }


    int _numCycle(Node* start, Node* target, Check visit[], List<Node*>& isChecked, int depth){
        Check* current;
        int result = 0;
        for(auto i = 0; i < size; i++){
            if(visit[i].data == target){
                current = &(visit[i]); break;
            }
        }

        if(depth > 0 && start == target){
            isChecked.append(start);
            return 1;
        }
        if(current->isVisited) { return 0; }
        current->isVisited = true;
        for(auto i = target->directedList().begin(); i != nullptr; i = i->next){
            result += _numCycle(start, i->data, visit, isChecked, depth + 1);
        }

        return result;
    }

    string makeLexiStr(List<Node*>& target){
        List<Node*> lexiList;
        string result;
        for(auto t = target.begin(); t != nullptr; t = t->next){
            if(lexiList.size() == 0 || t->data->label() < lexiList.begin()->data->label()){
                lexiList.push(t->data);
            } else {
                auto l = lexiList.begin();
                for(; l->next != nullptr; l = l->next){
                    if(l->next->data->label() >= t->data->label()){ break; }
                }
                lexiList.insert(l, t->data);
            }
        }

        for(auto i = lexiList.begin(); i != nullptr; i = i->next){
            result += i->data->label();
            if(i != lexiList.end()) { result += " "; }
        }

        return result;
    }

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};

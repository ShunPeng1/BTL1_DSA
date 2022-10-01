#include "ConcatStringList.h"

//ALL OF MY #DEFINE ARE FOR PERSONAL USE AND PREVENT PLAGIARISM TO SOME EXTENDS 

typedef long long ll;

#define INF 2147483647
#define INFLL 9223372036854775807
#define MOD1 1000000007
#define MOD9 998244353

#define FOR(i,a,n) for(ll i=a ; i<n ; i++)
#define FORR(i,n,a) for(ll i=a-1 ; i>=n ; i--)
#define FOREACH(x, c) for(auto &(x): (c) ) 

#define endl '\n'
#define ENDL cout<<'\n'
#define YES cout<<"YES"
#define NO cout<<"NO"

//typedef all the class because it is long af

typedef ConcatStringList CSL;
typedef CharALNode CALN;

typedef ConcatStringList::DeleteStringList DL;
typedef DelNode DN;

typedef ConcatStringList::ReferencesList RL;
typedef RefNode RN;

RL CSL::refList = RL();
DL CSL::delStrList = DL();
//struct Node
CALN::CharALNode(string s, CharALNode * _next){ 
    next = _next; 
    CharArrayList = s;
}

RN::RefNode(RefNode * _next, CharALNode * _original, int _nRef){ 
    next = _next; 
    original = _original;
    nReference = _nRef;
    isDeleted = false;
}

DN::DelNode(DelNode *_next, CALN* headCALN,  CALN* tailCALN, int length){
    next=_next;
    nChainRN = length;

    //array of RefNode to traverse in DeleteCALN
    chainRN = new RefNode*[length];
    for(int i = 0 ; i< length ; i++){
        chainRN[i] = CSL::refList.getRNPointer(headCALN);
        headCALN = headCALN->next;
    }
    if(headCALN!= tailCALN->next){
        throw logic_error("DelNode: Concat nNode struct size is wrong");
    }
}

DN::~DelNode(){
    delete [] chainRN;
}

CSL::ConcatStringList(){
    nChar = 0;
    nNode = 0;
    head = nullptr;
    tail = nullptr;
}

CSL::ConcatStringList(const char * s){
    int i = 0;
    string tp = "";
    while(s[i]!='\0'){
        tp+=s[i];
        i++;
    }

    CALN* tpCALN = new CALN(s,nullptr);
    head = tpCALN;
    tail = tpCALN;

    nChar = i;
    nNode = 1;
    
    //Reference
    refList.addFrontRefNode(tpCALN, 2);
    refList.sortRef();
    //
}

CSL::ConcatStringList(const CSL & tpCALN){
    this->head = tpCALN.head;
    this->tail = tpCALN.tail;
    this->nChar = tpCALN.nChar;
    this->nNode = tpCALN.nNode;
}

// ConcatStringList function
int CSL::length() const{
    return nChar;
}

char CSL::get(int index) const{
    if(index<0||index>=nChar){
        throw out_of_range("Index of string is invalid!");
    }

    int tpSize=0;
    CALN* roam = head;
    while(roam){
        if(index<tpSize+roam->CharArrayList.size()){
            return roam->CharArrayList[index-tpSize];
        }
        tpSize+= roam->CharArrayList.size();
        roam = roam->next;
    }
    return '\0';
}

int CSL::indexOf(char c) const{
    int tpSize=0;
    CALN* roam = head;
    while(roam!=nullptr){
        FOR(i,0,roam->CharArrayList.size()){
            if(c==roam->CharArrayList[i]) return tpSize+i;
        }
        tpSize+= roam->CharArrayList.size();
        roam = roam->next;
    }
    return -1;
}

string CSL::toString() const{
    string output ="";
    CALN* roam = head;
    while(roam!=tail->next){
        output+= roam->CharArrayList;
        roam = roam->next;
    }

    return output;
}

CSL CSL::concat(const CSL & otherS) const{
    
    tail->next = otherS.head;
    
    CSL nObj;
    nObj.head = head;
    nObj.tail = otherS.tail;
    nObj.nNode = nNode + otherS.nNode;
    nObj.nChar = nChar + otherS.nChar;
    
    //Reference List
    refList.increaseNumOfRefAt(head, 1);
    refList.increaseNumOfRefAt(otherS.tail, 1);
    refList.sortRef();
    //

    return nObj;
}

CSL CSL::subString(int from, int to) const{
    if(from <0 || to>nChar){
        throw out_of_range("Index of string is invalid");
    }

    if(from>to){
        throw logic_error("Invalid range");
    }
    
    CSL result;
    result.nChar = to-from;

    CALN* roam = head;
    int tpSize = 0;
    while(roam!=tail->next){
        
        string tpStr = "";
        FOR(i,0,roam->CharArrayList.size()){
            int currentPos = tpSize + i;
            if(currentPos>= from && currentPos<to){
                tpStr += roam->CharArrayList[i];
            }
        }
        if(tpStr.size()){
            CALN* tpCALN = new CALN(tpStr, nullptr);
            result.nNode++;
            
            //Reference Add
            refList.addFrontRefNode(tpCALN, 0);

            if(result.head == nullptr){
                result.head = tpCALN;
                result.tail = tpCALN;
            }
            else {
                result.tail->next = tpCALN;
                result.tail = result.tail->next;
            }

        }

        tpSize+= roam->CharArrayList.size();
        roam = roam->next;
    }

    //Reference increase
    refList.increaseNumOfRefAt(result.head, 1);
    refList.increaseNumOfRefAt(result.tail, 1);
    refList.sortRef();
    //
    return result;
}

CSL CSL::reverse() const{
    CSL result;
    result.nNode = nNode;
    result.nChar = nChar;

    CALN* roam = head;
    int tpSize = 0;
    while(roam!=tail->next){
        
        string tpStr = "";
        FORR(i,0,roam->CharArrayList.size()){
            tpStr += roam->CharArrayList[i];
        }

        if(tpStr.size()){
            CALN* tpCALN = new CharALNode(tpStr, nullptr);

            //Reference Add
            refList.addFrontRefNode(tpCALN, 0);

            if(result.tail == nullptr){
                result.head = tpCALN;
                result.tail = tpCALN;
            }
            else {
                tpCALN->next = result.head;
                result.head = tpCALN;
            }
        }

        tpSize+= roam->CharArrayList.size();
        roam = roam->next;
    }
    
    //Reference increase
    refList.increaseNumOfRefAt(result.head, 1);
    refList.increaseNumOfRefAt(result.tail, 1);
    refList.sortRef();
    //
    return result;
}

//Destructor section

CSL::~ConcatStringList(){
    refList.increaseNumOfRefAt(head, -1);
    refList.increaseNumOfRefAt(tail, -1);

    DN * tpDN = new DelNode(nullptr, head, tail, nNode);
    delStrList.addBackDelNode(tpDN);
    delStrList.loopToDeallocateNode();
    
    refList.sortRef();
    refList.DeleteIfAll0();
}



//References List Function

int RL::size() const{
    return nNodeRef;
}

int RL::refCountAt(int index) const{
    if(index<0||index>=nNodeRef){
        throw out_of_range("Index of references list is invalid!");
    }
    
    RN* roam = headRef;
    int tpSize = 0;
    while(roam!=nullptr){
        if(tpSize == index){
            return roam->nReference;
        }
        tpSize++;
        roam = roam->next;
    }
    
    return 0;
}

string RL::refCountsString() const{

    string res = "RefCounts[";
    RN* roam = headRef;
    
    while(roam!=nullptr){   
        res+= to_string(roam->nReference);
        roam = roam->next;
        if(roam!= nullptr) res+=',';
    }
    res+= "]";
    return res;
}


//Reference List Additional Function
void RL::printRefDebug(){
    RN* roam = headRef ;
    while(roam){
        cout<<roam->original->CharArrayList<<" "<<roam->nReference<<"\n | \n V \n";
        roam = roam->next;
    }

}

void RL::addFrontRefNode(CALN* tpCALN, int nRef){
    RN* tpNode = new RN(nullptr,tpCALN, nRef); 

    if(nNodeRef == 0){
        headRef = tpNode ;
        tailRef = tpNode ;
    }
    else{
        //Add back
        //tailRef->next = tpNode;
        //tailRef = tailRef->next; 

        //Add front
        tpNode->next = headRef;
        headRef = tpNode;
    }
    nNodeRef++;
    return ;
}

void RL::increaseNumOfRefAt(CALN* tpCALN, int value){
    RN* roam = refList.headRef;
    while (roam){
        if(roam->original == tpCALN){
            roam->nReference+= value;
            break;
        }
        roam = roam->next;
    }
}

RN * RL::getRNPointer(CALN * tpCALN){
    RN* roam = refList.headRef;
    while (roam){
        if(roam->original == tpCALN){
            return roam;
        }
        roam = roam->next;
    }
    //throw logic_error("No RefNode found BUG!");
    return nullptr;
}


void RL::sortRef(){
    //copy from https://www.javatpoint.com/program-to-sort-the-elements-of-the-singly-linked-list
    //Node currRN will point to head  
      


    if(headRef == nullptr) {  
        return;  
    }  

    FOR(i,0,refList.size()){
        RN *currRN = headRef, *nextRN = headRef->next, *prevRN = nullptr;
        while(nextRN != nullptr){
            if(compareRef(currRN, nextRN)){
                currRN->next = nextRN->next;
                nextRN->next = currRN;
                if(prevRN != nullptr) prevRN->next = nextRN;

                //Confusing bug
                if(headRef == currRN) headRef = nextRN;
                if(tailRef == nextRN) tailRef = currRN;
                
                RN* tpRN = currRN;
                currRN = nextRN;
                nextRN = tpRN;

            }
            prevRN = currRN;
            currRN = currRN->next;
            nextRN = nextRN->next;

            
        }
    }
}

bool RL::compareRef(RN* first, RN* second){
    if(second->nReference == 0){
        return false;
    }
    if(first->nReference == 0){
        return true;
    }
    if(first->nReference>second->nReference){
        return true;
    }
    return false;
}

void RL::DeleteIfAll0(){
    RN *roam = headRef;
    int sum = 0;
    while(roam){
        sum+= roam->nReference;
        roam=roam->next;
    }
    if(sum) return;

    roam = headRef;
    while (roam)
    {
        RN* tp = roam;
        roam = roam->next;
        delete tp; 
    }
    headRef = nullptr;
    tailRef = nullptr;
    nNodeRef = 0;
}

//Delete List Function
int DL::size() const{
    return nNodeDel;
}

string DL::totalRefCountsString() const{
    string res = "TotalRefCounts[";
    DN* roam = headDel;
    
    while(roam!=nullptr){   
        res+= to_string(sumHeadAndTailNumOfRef(roam));
        roam = roam->next;
        if(roam!= nullptr) res+=',';
    }
    res+= "]";
    return res;
}


//Delete List Additional Fuction
int DL::sumHeadAndTailNumOfRef(DN* tpDN) const{
    RN* headRN = tpDN->chainRN[0];
    RN* tailRN = tpDN->chainRN[tpDN->nChainRN-1];
    if(headRN == tailRN){
        return headRN->nReference;
    }
    return headRN->nReference + tailRN->nReference;
}

void DL::addBackDelNode(DN * &tpDN){
    if(headDel == nullptr && tailDel == nullptr){
        headDel = tpDN;
        tailDel = tpDN;
    }   
    else{
        tailDel->next = tpDN;
        tailDel = tpDN;
    }
    nNodeDel++;
}

void DL::loopToDeallocateNode(){
    //Copy from https://www.geeksforgeeks.org/delete-occurrences-given-key-linked-list/
    if(headDel == nullptr){
        return;
    }
    //remove front until unsatisfy
    while(headDel != nullptr && sumHeadAndTailNumOfRef(headDel) == 0){
        DN * tp = headDel;
        headDel = headDel->next;
        
        deleteCharALNode(tp);
        nNodeDel--;
        delete tp;
    }
    DN * curr  = headDel ,  *prev = nullptr;
    
    //remove the rest
    while (curr != nullptr) {
        if (sumHeadAndTailNumOfRef(curr) == 0) {
            DN *tp = curr;
            prev->next = curr->next;
            curr = curr->next;
        
            deleteCharALNode(tp);
            nNodeDel--;
            delete tp;
        }
        else{
            prev = curr;
            curr = curr->next;
        }
    }

    //assign tail
    if(headDel == nullptr){
        tailDel = nullptr;
        return ;
    }
    
    curr = headDel ;
    while(curr->next != nullptr){
        curr = curr->next;
    }
    tailDel = curr;
    
}


void DL::deleteCharALNode(DN * tpDN){
    
    FOR(i,0,tpDN->nChainRN){
        RN *tpRN = tpDN->chainRN[i];
        if(!tpRN->isDeleted){
            delete (tpRN->original);
            tpRN->isDeleted= true;
        }
    }
}
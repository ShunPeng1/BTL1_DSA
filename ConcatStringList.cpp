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
    nNode =1;
    
    //Reference
    refList.addFrontRefNode(tpCALN, 2);
    //
}

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

    return result;
}

//Destructor section

CSL::~ConcatStringList(){
    deleteNodeBycheckingRef();
    
}

void CSL::deleteNodeBycheckingRef(){
    refList.increaseNumOfRefAt(head, -1);
    refList.increaseNumOfRefAt(tail, -1);

    delStrList.addBackDelNode(
        new DelNode(nullptr, refList.getRNPointer(head) ,refList.getRNPointer(tail)));
    
    delStrList.loopToDeallocateNode();
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
    RN* tpNode = new RN(nullptr,tpCALN,nRef); 

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
    throw logic_error("No RefNode found BUG!");
}

void RL::sortRef(){
    return ;
    // pRN roam1 = headRef;
    // pRN roam2 = headRef;
    // FOR(i,0, refList.size()){
    //     FOR(j,0, refList.size()-1){
    //         if (roam1->data < roam2->data) {
    //             int tp = roam1->data;
    //             roam1->data = roam2->data;
    //             roam2->data = tp;

    //         }
    //         roam2 = roam2->next;
    //     }
    //     roam2 = headRef;
    //     roam1 = headRef->next;
    //     FOR(k,0, i){
    //         roam1 = roam1->next;
    //     }
    // }

}

bool RL::compareRef(RN* first, RN* second){
    return true;
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
    return tpDN->headRN->nReference + tpDN->tailRN->nReference;
}

void DL::addBackDelNode(DN * tpDN){
    if(headDel == nullptr && tailDel == nullptr){
        headDel = tpDN;
        tailDel = tpDN;
    }   
    else{
        tailDel->next = tpDN;
        tailDel = tpDN;
    }
}

void DL::loopToDeallocateNode(){
    //Copy from https://www.geeksforgeeks.org/delete-occurrences-given-key-linked-list/
    if(!headDel){
        return;
    }
    //remove front until unsatisfy
    while(headDel && sumHeadAndTailNumOfRef(headDel) == 0){
        DN * tp = headDel;
        headDel = headDel->next;
        
        deleteCharALNode(tp);
        delete tp;
    }
    DN * curr  = headDel ,  *prev = nullptr;
    
    //remove the rest
    while (curr) {
        if (sumHeadAndTailNumOfRef(curr) == 0) {
            DN *tp = curr;
            prev->next = curr->next;
            curr = curr->next;
        
            deleteCharALNode(tp);
            delete tp;
        }
        else{
            prev = curr;
            curr = curr->next;
        }
    }

    //assign tail
    curr = headDel ;
    while(curr->next){
        curr = curr->next;
    }
    tailDel = curr;
    
}


void DL::deleteCharALNode(DN * tpDN){
    CALN * roamHead = tpDN->headRN->original , * roamTail = tpDN->tailRN->original;
//roamtail next not null
    while(roamHead != roamTail->next){
        CALN * tp = roamHead;
        roamHead = roamHead->next;
        delete tp;
    }
}
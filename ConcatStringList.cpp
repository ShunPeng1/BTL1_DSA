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
typedef CharALNode * pCALN;

typedef ConcatStringList::DeleteStringList DL;
typedef DelNode DN;
typedef DelNode * pDN;

typedef ConcatStringList::ReferencesList RL;
typedef RefNode RN;
typedef RefNode * pRN;

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

    pCALN tpCALN = new CALN(s,nullptr);
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
    pCALN roam = head;
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
    pCALN roam = head;
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
    pCALN roam = head;
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
    refList.increaseNumberOfReferenceAt(head, 1);
    refList.increaseNumberOfReferenceAt(otherS.tail, 1);
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

    pCALN roam = head;
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
            pCALN tpCALN = new CALN(tpStr, nullptr);
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

    refList.increaseNumberOfReferenceAt(result.head, 1);
    refList.increaseNumberOfReferenceAt(result.tail, 1);

    return result;
}

CSL CSL::reverse() const{
    CSL result;
    result.nNode = nNode;
    result.nChar = nChar;

    pCALN roam = head;
    int tpSize = 0;
    while(roam!=tail->next){
        
        string tpStr = "";
        FORR(i,0,roam->CharArrayList.size()){
            tpStr += roam->CharArrayList[i];
        }

        if(tpStr.size()){
            pCALN tpCALN = new CharALNode(tpStr, nullptr);

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

    refList.increaseNumberOfReferenceAt(result.head, 1);
    refList.increaseNumberOfReferenceAt(result.tail, 1);

    return result;
}

//Destructor section

CSL::~ConcatStringList(){
    //deleteNodeBycheckingRef();
    
}

void CSL::deleteNodeBycheckingRef(){
    refList.increaseNumberOfReferenceAt(head, -1);
    refList.increaseNumberOfReferenceAt(tail, -1);


}

//References List Function

int RL::size() const{
    return nNodeRef;
}

int RL::refCountAt(int index) const{
    if(index<0||index>=nNodeRef){
        throw out_of_range("Index of references list is invalid!");
    }
    
    pRN roam = headRef;
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
    pRN roam = headRef;
    
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
    pRN roam = headRef ;
    while(roam){
        cout<<roam->original->CharArrayList<<" "<<roam->nReference<<"\n | \n V \n";
        roam = roam->next;
    }

}

void RL::addFrontRefNode(pCALN tpCALN, int nRef){
    pRN tpNode = new RN(nullptr,tpCALN,nRef); 

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

void RL::increaseNumberOfReferenceAt(pCALN tpCALN, int value){
    pRN roam = refList.headRef;
    while (roam){
        if(roam->original == tpCALN){
            roam->nReference+= value;
            break;
        }
        roam = roam->next;
    }
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

bool RL::compareRef(pRN first, pRN second){
    return true;
}


//Delete List Function
int DL::size() const{
    return nNodeDel;
}

string DL::totalRefCountsString() const{
    string res = "TotalRefCounts[";
    pDN roam = headDel;
    
    while(roam!=nullptr){   
        res+= to_string(roam->refNode->nReference);
        roam = roam->next;
        if(roam!= nullptr) res+=',';
    }
    res+= "]";
    return res;
}


//Delete List Additional Fuction
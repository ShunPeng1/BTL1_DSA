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

typedef CharALNode * pCALN;
typedef RefCharALNode * pRCALN;

ConcatStringList::ReferencesList ConcatStringList::refList = ConcatStringList::ReferencesList();
ConcatStringList::DeleteStringList ConcatStringList::delStrList = ConcatStringList::DeleteStringList();

ConcatStringList::ConcatStringList(){
    nChar = 0;
    nNode = 0;
    head = nullptr;
    tail = nullptr;
}

ConcatStringList::ConcatStringList(const char * s){
    int i = 0;
    string temp = "";
    while(s[i]!='\0'){
        temp+=s[i];
        i++;
    }

    pCALN tempCALN = new CharALNode(s,nullptr);
    head = tempCALN;
    tail = tempCALN;

    nChar = i;
    nNode =1;
    
    //Reference
    refList.addBackRefNode(tempCALN, 2);
    //
}

int ConcatStringList::length() const{
    return nChar;
}

char ConcatStringList::get(int index) const{
    if(index<0||index>=nChar){
        throw out_of_range("Index of string is invalid!");
    }

    int tempSize=0;
    pCALN roam = head;
    while(roam){
        if(index<tempSize+roam->CharArrayList.size()){
            return roam->CharArrayList[index-tempSize];
        }
        tempSize+= roam->CharArrayList.size();
        roam = roam->next;
    }
    return '\0';
}

int ConcatStringList::indexOf(char c) const{
    int tempSize=0;
    pCALN roam = head;
    while(roam!=nullptr){
        FOR(i,0,roam->CharArrayList.size()){
            if(c==roam->CharArrayList[i]) return tempSize+i;
        }
        tempSize+= roam->CharArrayList.size();
        roam = roam->next;
    }
    return -1;
}

string ConcatStringList::toString() const{
    string output ="";
    pCALN roam = head;
    while(roam!=tail->next){
        output+= roam->CharArrayList;
        roam = roam->next;
    }

    return output;
}

ConcatStringList ConcatStringList::concat(const ConcatStringList & otherS) const{
    
    tail->next = otherS.head;
    
    ConcatStringList nObj;
    nObj.head = head;
    nObj.tail = otherS.tail;
    nObj.nNode = nNode + otherS.nNode;
    nObj.nChar = nChar + otherS.nChar;
    
    //Reference 
    pCALN roam = nObj.head;
    while(roam->next){
        roam = roam->next;
    }

    refList.increaseNumberOfReferenceAt(nObj.head, 1);
    refList.increaseNumberOfReferenceAt(roam, 1);
    //

    return std::move(nObj);
}



ConcatStringList ConcatStringList::subString(int from, int to) const{
    if(from <0 || to>=nChar){
        throw out_of_range("Index of string is invalid");
    }

    if(from>to){
        throw logic_error("Invalid range");
    }
    
    ConcatStringList result;
    result.nChar = to-from;

    pCALN roam = head;
    int tempSize = 0;
    while(roam!=nullptr){
        
        string tempStr = "";
        FOR(i,0,roam->CharArrayList.size()){
            int currentPos = tempSize + i;
            if(currentPos>= from && currentPos<to){
                tempStr += roam->CharArrayList[i];
            }
        }
        if(tempStr.size()){
            pCALN tempCALN = new CharALNode(tempStr, nullptr);
            result.nNode++;
            
            //Reference Add
            refList.addBackRefNode(tempCALN, 0);
            
            if(result.head == nullptr){
                result.head = tempCALN;
                result.tail = tempCALN;
            }
            else {
                result.tail->next = tempCALN;
                result.tail = result.tail->next;
            }

        }

        tempSize+= roam->CharArrayList.size();
        roam = roam->next;
    }

    //Reference increase

    refList.increaseNumberOfReferenceAt(result.head, 1);
    refList.increaseNumberOfReferenceAt(result.tail, 1);

    return result;
}

ConcatStringList ConcatStringList::reverse() const{
    ConcatStringList result;
    result.nNode = nNode;
    result.nChar = nChar;

    pCALN roam = head;
    int tempSize = 0;
    while(roam!=nullptr){
        
        string tempStr = "";
        FORR(i,0,roam->CharArrayList.size()){
            tempStr += roam->CharArrayList[i];
        }

        if(tempStr.size()){
            pCALN tempCALN = new CharALNode(tempStr, nullptr);

            //Reference Add
            refList.addBackRefNode(tempCALN, 0);

            if(result.tail == nullptr){
                result.head = tempCALN;
                result.tail = tempCALN;
            }
            else {
                tempCALN->next = result.head;
                result.head = tempCALN;
            }
        }

        tempSize+= roam->CharArrayList.size();
        roam = roam->next;
    }
    
    //Reference increase

    refList.increaseNumberOfReferenceAt(result.head, 1);
    refList.increaseNumberOfReferenceAt(result.tail, 1);

    return result;
}

ConcatStringList::~ConcatStringList(){
    // pCALN roam = head;
    // while(roam!=nullptr){
    //     pCALN temp = roam->next;
    //     delete roam;
    //     roam = temp;
    // }
}

//References List Function

int ConcatStringList::ReferencesList::size() const{
    return nNodeRef;
}

int ConcatStringList::ReferencesList::refCountAt(int index) const{
    if(index<0||index>=nNodeRef){
        throw out_of_range("Index of references list is invalid!");
    }
    
    pRCALN roam = headRef;
    int tempSize = 0;
    while(roam!=nullptr){
        if(tempSize == index){
            return roam->nReference;
        }
        tempSize++;
        roam = roam->next;
    }
    
    return 0;
}

string ConcatStringList::ReferencesList::refCountsString() const{
    string res = "RefCounts[";
    pRCALN roam = headRef;
    
    while(roam!=nullptr){   
        res+= to_string(roam->nReference);
        roam = roam->next;
        if(roam!= nullptr) res+=',';
    }
    res+= "]";
    return res;
}


//Adding More Utility Functions
void ConcatStringList::ReferencesList::printRef(){
    pRCALN roam = headRef ;
    while(roam){
        cout<<roam->original->CharArrayList<<" "<<roam->nReference<<"\n | \n V \n";
        roam = roam->next;
    }

}

void ConcatStringList::ReferencesList::addBackRefNode(pCALN tempCALN, int nRef){
    pRCALN tempNode = new RefCharALNode(nullptr,tempCALN,nRef); 

    if(nNodeRef == 0){
        headRef = tempNode ;
        tailRef = tempNode ;
    }
    else{
        tailRef->next = tempNode;
        tailRef = tailRef->next; 
    }
    nNodeRef++;
}

void ConcatStringList::ReferencesList::increaseNumberOfReferenceAt(pCALN tempCALN, int value){
    pRCALN roam2 = refList.headRef;
    while (roam2){
        if(roam2->original == tempCALN){
            roam2->nReference+= value;
            break;
        }
        roam2 = roam2->next;
    }
}

void ConcatStringList::ReferencesList::sortRef(){
    return ;
    // pRCALN roam1 = headRef;
    // pRCALN roam2 = headRef;
    // FOR(i,0, refList.size()){
    //     FOR(j,0, refList.size()-1){
    //         if (roam1->data < roam2->data) {
    //             int temp = roam1->data;
    //             roam1->data = roam2->data;
    //             roam2->data = temp;

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

bool ConcatStringList::ReferencesList::compareRef(pRCALN first, pRCALN second){
    return true;
}
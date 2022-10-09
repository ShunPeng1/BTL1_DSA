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

ConcatStringList::ReferencesList ConcatStringList::refList = ConcatStringList::ReferencesList();
ConcatStringList::DeleteStringList ConcatStringList::delStrList = ConcatStringList::DeleteStringList();

//struct Node
CharALNode::CharALNode() {
    next = nullptr;
    CharArrayList = "";
}

CharALNode::CharALNode(string s, CharALNode* _next, RefNode *_referenceNode) {
    next = _next;
    CharArrayList = s;
    referenceNode = _referenceNode;
}

RefNode::RefNode(RefNode* _next, CharALNode* _original, int _nRef, bool _isHeadOrTail) {
    next = _next;
    original = _original;
    nReference = _nRef;
    isDeleted = false;
    isHeadOrTail = _isHeadOrTail;
}

DelNode::DelNode(DelNode* _next, CharALNode* headCALN, CharALNode* tailCALN, int length) {
    next = _next;
    nChainRN = length;

    //array of RefNode to traverse in DeleteCALN
    chainRN = new RefNode * [length];
    for (int i = 0; i < length; i++) {
        chainRN[i] = ConcatStringList::refList.getRNPointer(headCALN);
        headCALN = headCALN->next;
    }
}

DelNode::~DelNode() {
    delete[] chainRN;
}

ConcatStringList::ConcatStringList() {
    nChar = 0;
    nNode = 0;
    isConcated = false;
    isTemporary = false;
    head = nullptr;
    tail = nullptr;
}

ConcatStringList::ConcatStringList(const char* s) {
    int i = 0;
    string tp = "";
    while (s[i] != '\0') {
        tp += s[i];
        i++;
    }

    CharALNode* tpCALN = new CharALNode(s, nullptr, nullptr);
    head = tpCALN;
    tail = tpCALN;

    nChar = i;
    nNode = 1;
    isConcated = false;
    isTemporary = false;

    refList.addFrontRefNode(tpCALN, 2, true);
}

ConcatStringList::ConcatStringList(const ConcatStringList&& otherS) {
    this->head = nullptr;
    this->tail = nullptr;
    this->isConcated = false;
    this->isTemporary = false;
    this->nChar = otherS.nChar;
    this->nNode = otherS.nNode;

    if (otherS.isConcated) {//is return from concat so we shallow copy
        this->head = otherS.head;
        this->tail = otherS.tail;
        refList.increaseNumOfRefAt(this->head, 1, true);
        refList.increaseNumOfRefAt(this->tail, 1, true);

    }
    else {//is return from the reverse or substring so we deep copy
        CharALNode* roam = otherS.head;
        while (roam != otherS.tail->next) {
            CharALNode* tpCALN = new CharALNode();
            *tpCALN = *roam;
            refList.addFrontRefNode(tpCALN, 0, false);
            if (this->tail == nullptr) {
                this->head = tpCALN;
                this->tail = tpCALN;
            }
            else {
                this->tail->next = tpCALN;
                this->tail = this->tail->next;
            }
            roam = roam->next;
        }
        if (this->nNode == 1) {
            refList.increaseNumOfRefAt(this->head, 2, true);
            refList.nNodeRef += 1;
        }
        else {
            refList.increaseNumOfRefAt(this->head, 1, true);
            refList.increaseNumOfRefAt(this->tail, 1, true);
            refList.nNodeRef += 2;
        }

        //Delete tvalue otherS
        roam = otherS.head;
        while (roam) {
            CharALNode* tp = roam;
            roam = roam->next;
            delete tp;
        }
    }

}

// ConcatStringList function
int ConcatStringList::length() const {
    return nChar;
}

char ConcatStringList::get(int index) const {
    if (index < 0 || index >= nChar) {
        throw out_of_range("Index of string is invalid!");
    }

    int tpSize = 0;
    CharALNode* roam = head;
    while (roam) {
        if (index < tpSize + roam->CharArrayList.size()) {
            return roam->CharArrayList[index - tpSize];
        }
        tpSize += roam->CharArrayList.size();
        roam = roam->next;
    }
    return '\0';
}

int ConcatStringList::indexOf(char c) const {
    int tpSize = 0;
    CharALNode* roam = head;
    while (roam != tail->next) {
        FOR(i, 0, roam->CharArrayList.size()) {
            if (c == roam->CharArrayList[i]) return tpSize + i;
        }
        tpSize += roam->CharArrayList.size();
        roam = roam->next;
    }
    return -1;
}

string ConcatStringList::toString() const {
    string output = "";
    CharALNode* roam = head;
    while (roam != tail->next) {
        output += roam->CharArrayList;
        roam = roam->next;
    }

    return output;
}

ConcatStringList ConcatStringList::concat(const ConcatStringList& otherS) const {

    tail->next = otherS.head;

    ConcatStringList result;
    result.head = head;
    result.tail = otherS.tail;
    result.nNode = nNode + otherS.nNode;
    result.nChar = nChar + otherS.nChar;
    result.isConcated = true;
    result.isTemporary = true;

    return (ConcatStringList&&)result;
}

ConcatStringList ConcatStringList::subString(int from, int to) const {
    if (from <0 || to>nChar) {
        throw out_of_range("Index of string is invalid");
    }

    if (from >= to) {
        throw logic_error("Invalid range");
    }

    ConcatStringList result;
    result.nChar = to - from;

    CharALNode* roam = head;
    int tpSize = 0;
    while (roam != tail->next) {

        string tpStr = "";
        FOR(i, 0, roam->CharArrayList.size()) {
            int currentPos = tpSize + i;
            if (currentPos >= from && currentPos < to) {
                tpStr += roam->CharArrayList[i];
            }
        }
        if (tpStr.size() || (roam->CharArrayList.size() == 0 && tpSize >= from && tpSize <= to)) {
            CharALNode* tpCALN = new CharALNode(tpStr, nullptr, nullptr);
            result.nNode++;


            if (result.head == nullptr) {
                result.head = tpCALN;
                result.tail = tpCALN;
            }
            else {
                result.tail->next = tpCALN;
                result.tail = result.tail->next;
            }

        }

        tpSize += roam->CharArrayList.size();
        roam = roam->next;
    }

    result.isTemporary = true;

    return (ConcatStringList&&)result;
}

ConcatStringList ConcatStringList::reverse() const {
    ConcatStringList result;
    result.nNode = nNode;
    result.nChar = nChar;

    CharALNode* roam = head;
    int tpSize = 0;
    while (roam != tail->next) {

        string tpStr = "";
        FORR(i, 0, roam->CharArrayList.size()) {
            tpStr += roam->CharArrayList[i];
        }

        CharALNode* tpCALN = new CharALNode(tpStr, nullptr, nullptr);


        if (result.tail == nullptr) {
            result.head = tpCALN;
            result.tail = tpCALN;
        }
        else {
            tpCALN->next = result.head;
            result.head = tpCALN;
        }


        tpSize += roam->CharArrayList.size();
        roam = roam->next;
    }

    result.isTemporary = true;

    return (ConcatStringList&&)result;
}

//Destructor section
ConcatStringList::~ConcatStringList() {
    if (isTemporary) return;

    refList.increaseNumOfRefAt(head, -1, true);
    refList.increaseNumOfRefAt(tail, -1, true);

    DelNode* tpDN = new DelNode(nullptr, head, tail, nNode);
    delStrList.addBackDelNode(tpDN);
    delStrList.loopToDeallocateNode();

    refList.DeleteIfAll0();
    refList.mergeSort(&refList.headRef);
}


//References List Function

int ConcatStringList::ReferencesList::size() const {
    return nNodeRef;
}

int ConcatStringList::ReferencesList::refCountAt(int index) const {
    if (index < 0 || index >= nNodeRef) {
        throw out_of_range("Index of references list is invalid!");
    }

    refList.mergeSort(&refList.headRef);

    RefNode* roam = headRef;
    int tpSize = 0;
    while (roam != nullptr) {
        if (tpSize == index) {
            return roam->nReference;
        }
        tpSize++;
        roam = roam->next;
    }

    return 0;
}

string ConcatStringList::ReferencesList::refCountsString() const {
    refList.mergeSort(&refList.headRef);

    string res = "RefCounts[";
    RefNode* roam = headRef;

    while (roam != nullptr) {
        if (roam->isHeadOrTail) {
            res += to_string(roam->nReference);
        }

        roam = roam->next;

        if (roam != nullptr) if (roam->isHeadOrTail) res += ',';
    }
    res += "]";
    return res;
}


//Reference List Additional Function

void ConcatStringList::ReferencesList::addFrontRefNode(CharALNode* tpCALN, int nRef, bool isHeadOrTail) {
    RefNode* tpNode = new RefNode(nullptr, tpCALN, nRef, isHeadOrTail);
    tpCALN->referenceNode = tpNode;
    if (nNodeRef == 0) {
        headRef = tpNode;
        tailRef = tpNode;
    }
    else {
        //Add front
        tpNode->next = headRef;
        headRef = tpNode;
    }
    if (isHeadOrTail) nNodeRef++;
    return;
}


void ConcatStringList::ReferencesList::increaseNumOfRefAt(CharALNode* tpCALN, int value, bool changeIsHeadOrTail) {
    RefNode* roam = tpCALN->referenceNode;
    roam->nReference += value;
    roam->isHeadOrTail = changeIsHeadOrTail;
}

RefNode* ConcatStringList::ReferencesList::getRNPointer(CharALNode* tpCALN) {
    return tpCALN->referenceNode;
}


/* sorts the linked list by changing next pointers (not data) */
void  ConcatStringList::ReferencesList::mergeSort(RefNode** headRef)
{
    RefNode* head = *headRef;
    RefNode* front;
    RefNode* back;

    /* Base case -- length 0 or 1 */
    if ((head == nullptr) || (head->next == nullptr)) {
        return;
    }

    /* Split head into 'front' and 'back' sublists */
    frontBackSplit(head, &front, &back);

    /* Recursively sort the sublists */
    mergeSort(&front);
    mergeSort(&back);

    /* answer = merge the two sorted lists together */
    *headRef = sortedMerge(front, back);
}

/* See https:// www.geeksforgeeks.org/?p=3622 for details of this
function */
RefNode* ConcatStringList::ReferencesList::sortedMerge(RefNode* front, RefNode* back)
{
    RefNode* result = nullptr;

    /* Base cases */
    if (front == nullptr)
        return (back);
    else if (back == nullptr)
        return (front);

    /* Pick either front or b, and recur */
    if (!compareRef(front, back)) {
        result = front;
        result->next = sortedMerge(front->next, back);
    }
    else {
        result = back;
        result->next = sortedMerge(front, back->next);
    }
    return (result);
}

void  ConcatStringList::ReferencesList::frontBackSplit(RefNode* source,
    RefNode** front, RefNode** back)
{
    RefNode* fast;
    RefNode* slow;
    slow = source;
    fast = source->next;

    /* Advance 'fast' two nodes, and advance 'slow' one node */
    while (fast != nullptr) {
        fast = fast->next;
        if (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    /* 'slow' is before the midpoint in the list, so split it in two
    at that point. */
    *front = source;
    *back = slow->next;
    slow->next = nullptr;
}



bool ConcatStringList::ReferencesList::compareRef(RefNode* first, RefNode* second) {
  
    if (second->nReference == 0) {
        return false;
    }
    if (first->nReference == 0) {
        return true;
    }
    if (first->nReference > second->nReference) {
        return true;
    }
    return false;
}

void ConcatStringList::ReferencesList::DeleteIfAll0() {
    RefNode* roam = headRef;
    int sum = 0;
    while (roam) {
        sum += roam->nReference;
        roam = roam->next;
    }
    if (sum) return;

    roam = headRef;
    while (roam)
    {
        RefNode* tp = roam;
        roam = roam->next;
        delete tp;
    }
    headRef = nullptr;
    tailRef = nullptr;
    nNodeRef = 0;
}

//Delete List Function
int ConcatStringList::DeleteStringList::size() const {
    return nNodeDel;
}

string ConcatStringList::DeleteStringList::totalRefCountsString() const {
    string res = "TotalRefCounts[";
    DelNode* roam = headDel;

    while (roam != nullptr) {
        res += to_string(sumHeadAndTailNumOfRef(roam));
        roam = roam->next;
        if (roam != nullptr) res += ',';
    }
    res += "]";
    return res;
}


//Delete List Additional Fuction
int ConcatStringList::DeleteStringList::sumHeadAndTailNumOfRef(DelNode* tpDN) const {
    RefNode* headRN = tpDN->chainRN[0];
    RefNode* tailRN = tpDN->chainRN[tpDN->nChainRN - 1];
    if (!headRN || !tailRN) {
        return 0;
    }

    if (headRN == tailRN) {
        return headRN->nReference;
    }
    return headRN->nReference + tailRN->nReference;
}

void ConcatStringList::DeleteStringList::addBackDelNode(DelNode*& tpDN) {
    if (headDel == nullptr && tailDel == nullptr) {
        headDel = tpDN;
        tailDel = tpDN;
    }
    else {
        tailDel->next = tpDN;
        tailDel = tpDN;
    }
    nNodeDel++;
}

void ConcatStringList::DeleteStringList::loopToDeallocateNode() {
    //Copy from https://www.geeksforgeeks.org/delete-occurrences-given-key-linked-list/
    if (headDel == nullptr) {
        return;
    }
    //remove front until unsatisfy
    while (headDel != nullptr && sumHeadAndTailNumOfRef(headDel) == 0) {
        DelNode* tp = headDel;
        headDel = headDel->next;

        deleteCharALNode(tp);
        nNodeDel--;
        delete tp;
    }
    DelNode* curr = headDel, * prev = nullptr;

    //remove the rest
    while (curr != nullptr) {
        if (sumHeadAndTailNumOfRef(curr) == 0) {
            DelNode* tp = curr;
            if (prev != nullptr) prev->next = curr->next;
            curr = curr->next;

            deleteCharALNode(tp);
            nNodeDel--;
            delete tp;
        }
        else {
            prev = curr;
            curr = curr->next;
        }
    }

    tailDel = prev;

}


void ConcatStringList::DeleteStringList::deleteCharALNode(DelNode* tpDN) {

    FOR(i, 0, tpDN->nChainRN) {
        RefNode* tpRN = tpDN->chainRN[i];

        if (tpRN != nullptr) if (!tpRN->isDeleted) {
            delete (tpRN->original);
            tpRN->isDeleted = true;
        }
    }
}

#ifndef __CONCAT_STRING_LIST_H__
#define __CONCAT_STRING_LIST_H__

#include "main.h"


struct CharALNode {
    CharALNode* next;
    string CharArrayList;

    CharALNode(string s, CharALNode* _next);
};

struct RefNode {
    RefNode* next;
    CharALNode* original;
    int nReference;
    bool isDeleted;
    RefNode(RefNode* _next, CharALNode* _original, int _nRef);

};

struct DelNode {
    DelNode* next;
    RefNode** chainRN;
    int nChainRN;
    DelNode(DelNode* _next, CharALNode* headCALN, CharALNode* tailCALN, int length);
    ~DelNode();
};
class ConcatStringList {
private:
    CharALNode* head, * tail;
    int nNode = 0, nChar = 0;
    bool isAllocated;
public:
    class ReferencesList; // forward declaration
    class DeleteStringList; // forward declaration

    static ReferencesList refList;
    static DeleteStringList delStrList;

    bool isEmptyList() {
        return head == nullptr;
    }


    ConcatStringList();
    ConcatStringList(const char* s);
    int length() const;
    char get(int index) const;
    int indexOf(char c) const;
    std::string toString() const;
    ConcatStringList concat(const ConcatStringList& otherS) const;
    ConcatStringList subString(int from, int to) const;
    ConcatStringList reverse() const;
    void DeleteNode();
    ~ConcatStringList();


public:
    class ReferencesList {
        // TODO: may provide some attributes
        RefNode* headRef = nullptr, * tailRef = nullptr;
        int nNodeRef = 0;

        friend class ConcatStringList;
        friend class DeleteStringList;
    public:

        int size() const;
        int refCountAt(int index) const;
        std::string refCountsString() const;

        //Reference Additional Function
        void printRefDebug();
        void addFrontRefNode(CharALNode*, int);
        void increaseNumOfRefAt(CharALNode*, int);
        RefNode* getRNPointer(CharALNode*);
        void sortRef();
        bool compareRef(RefNode*, RefNode*);
        void DeleteIfAll0();
    };

    class DeleteStringList {
        // TODO: may provide some attributes
        DelNode* headDel = nullptr, * tailDel = nullptr;
        int nNodeDel = 0;

        friend class ConcatStringList;
        friend class ReferencesList;

    public:
        int size() const;
        std::string totalRefCountsString() const;

        //Delete Additional Function

        int sumHeadAndTailNumOfRef(DelNode*) const;
        void addBackDelNode(DelNode*&);
        void loopToDeallocateNode();
        void deleteCharALNode(DelNode*);
    };
};

#endif // __CONCAT_STRING_LIST_H__
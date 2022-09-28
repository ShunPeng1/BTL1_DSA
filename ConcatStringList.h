#ifndef __CONCAT_STRING_LIST_H__
#define __CONCAT_STRING_LIST_H__

#include "main.h"


struct CharALNode{
    CharALNode * next;
    string CharArrayList;
    CharALNode(string s, CharALNode * _next){ 
        next = _next; 
        CharArrayList = s;
    }
};

struct RefNode{
    RefNode * next;
    CharALNode * original;
    int nReference ;
    RefNode(RefNode * _next, CharALNode * _original, int _nRef){ 
        next = _next; 
        original = _original;
        nReference = _nRef;
    }
    
};

struct DelNode{
    DelNode * next;
    RefNode * headRN;
    RefNode * tailRN;

    DelNode(DelNode *_next, RefNode *_headRN, RefNode *_tailRN){
        next=_next;
        headRN = _headRN;
        tailRN = _tailRN;
    }
};

class ConcatStringList {
private:
    CharALNode *head, *tail;
    int nNode = 0, nChar = 0;

public:
    class ReferencesList; // forward declaration
    class DeleteStringList; // forward declaration

    static ReferencesList refList;
    static DeleteStringList delStrList;


    ConcatStringList();
    ConcatStringList(const char *s);
    int length() const;
    char get(int index) const;
    int indexOf(char c) const;
    std::string toString() const;
    ConcatStringList concat(const ConcatStringList & otherS) const;
    ConcatStringList subString(int from, int to) const;
    ConcatStringList reverse() const;
    void deleteNodeBycheckingRef();
    void DeleteNode();
    ~ConcatStringList();


public:
    class ReferencesList {
        // TODO: may provide some attributes
        RefNode *headRef =nullptr, *tailRef= nullptr;
        int nNodeRef = 0;

        friend class ConcatStringList;
        friend class DeleteStringList;
        public:
            
            int size() const;
            int refCountAt(int index) const;
            std::string refCountsString() const;

            //Reference Additional Function
            void printRefDebug();
            void addFrontRefNode(CharALNode* , int );
            void increaseNumOfRefAt(CharALNode *, int);
            RefNode * getRNPointer(CharALNode *);
            void sortRef();
            bool compareRef(RefNode *, RefNode *);
    };

    class DeleteStringList {
        // TODO: may provide some attributes
        DelNode *headDel =nullptr, *tailDel= nullptr;
        int nNodeDel = 0;

        friend class ConcatStringList;
        friend class ReferencesList;

        public:
            int size() const;
            std::string totalRefCountsString() const;

            //Delete Additional Function
            
            int sumHeadAndTailNumOfRef(DelNode *) const;
            void addBackDelNode(DelNode* );
            void loopToDeallocateNode();
            void deleteCharALNode(DelNode *);
    };
};


#endif // __CONCAT_STRING_LIST_H__
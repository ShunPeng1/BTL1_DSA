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
    CharALNode * headCALN;
    CharALNode * tailCALN;
    RefNode * refNode ;

    DelNode(DelNode *_next, CharALNode *_headCALN, CharALNode *_tailCALN, RefNode * _refNode){
        next=_next;
        headCALN = _headCALN;
        tailCALN = _tailCALN;
        refNode = _refNode;
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

            //RefNode * getHead();
            void printRefDebug();
            void addFrontRefNode(CharALNode* , int );
            void increaseNumberOfReferenceAt(CharALNode *, int);
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
    };
};


#endif // __CONCAT_STRING_LIST_H__
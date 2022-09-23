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

struct RefCharALNode{
    RefCharALNode * next;
    CharALNode * original;
    int nReference ;
    RefCharALNode(RefCharALNode * _next, CharALNode * _original, int _nRef){ 
        next = _next; 
        original = _original;
        nReference = _nRef;
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
    ~ConcatStringList();

public:
    //Function continue from above Function
    void ContinuingRef_ConcatStringList(CharALNode *);
    void ContinuingRef_concat(ConcatStringList &) const;
    void ContinuingRef_subString(CharALNode *) const;
    void ContinuingRef_reverse();

public:
    class ReferencesList {
        // TODO: may provide some attributes
        RefCharALNode *headRef =nullptr, *tailRef= nullptr;
        int nNodeRef = 0;

        friend class ConcatStringList;

        public:
            
            int size() const;
            int refCountAt(int index) const;
            std::string refCountsString() const;

            //RefCharALNode * getHead();
            void printRef();
            void addBackRefNode(CharALNode* , int );
            void increaseNumberOfReferenceAt(CharALNode *, int);
            void sortRef();
            bool compareRef(RefCharALNode *, RefCharALNode *);
    };

    class DeleteStringList {
        // TODO: may provide some attributes

        public:
            int size() const;
            std::string totalRefCountsString() const;
    };
};


#endif // __CONCAT_STRING_LIST_H__
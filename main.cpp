#include "ConcatStringList.h"

// void tc1() {
//     ConcatStringList s1("Hello,_world");
//     // test length
//     cout << "s1's length: " << s1.length() << endl;
//     // test get
//     cout << "char at index 2: " << s1.get(2) << endl;
//     try {
//         cout << "char at index 22: " << s1.get(22) << endl;
//     }
//     catch (out_of_range & ofr) {
//         cout << "Exception out_of_range: " << ofr.what() << endl;
//     }
//     // test indexOf
//     cout << "in s1, index of 'o': " << s1.indexOf('o') << endl;
//     cout << "in s1, index of 'a': " << s1.indexOf('a') << endl;
//     // test toString
//     cout << "s1 toString: " << s1.toString() << endl;
// }

void tc2() {
    ConcatStringList s1("Hello,");

    ConcatStringList s2("_this_is");
    ConcatStringList s3("_an_assignment");
    ConcatStringList s44("_new_string_");

    ConcatStringList s14 = s1.concat(s2);
    cout << "s14: " << s14.toString() << endl;
    cout<<"Current Ref \n"; ConcatStringList::refList.printRef();

    ConcatStringList s4 = s1.concat(s2).concat(s3);
    cout << "s4: " << s4.toString() << endl;
    cout<<"Current Ref \n"; ConcatStringList::refList.printRef();
    
    cout << "s1: " << s1.toString() << endl;
    cout << "s2: " << s2.toString() << endl;

    
    

    // ConcatStringList s11 = s1.reverse();
    // cout << "s11: " << s11.toString() << endl;
    // cout<<"Current Ref \n";
    // ConcatStringList::refList.printRef();

    // ConcatStringList s111 = s11.reverse();
    // cout << "s111: " << s111.toString() << endl;
    // cout<<"Current Ref \n";
    // ConcatStringList::refList.printRef();

    // ConcatStringList s1111 = s111.reverse();
    // cout << "s1111: " << s1111.toString() << endl;
    // ConcatStringList::refList.printRef();

    // ConcatStringList s100 = s1.concat(s11).concat(s111).concat(s1111);
    // ConcatStringList::refList.printRef();


    // cout << "s100: " << s100.toString() << endl;
    // ConcatStringList s110 = s100.subString(3,16);
    // cout << "s110: " << s110.toString() << endl;
    // cout << "s100: " << s100.toString() << endl;
    //ConcatStringList s5 = s1.concat(s2).reverse().subString(2, 4).concat(s44);
    //cout << "s5: " << s5.toString() << endl;


    // test reverse
   // ConcatStringList s7 = s4.reverse();
    //cout << "s7: " << s7.toString() << endl;
    //cout << "s4: " << s4.toString() << endl;
    
    //cout << "s1: " << s1.toString() << endl;

}

// void tc3() {
//     ConcatStringList * s1 = new ConcatStringList("Hello");
//     ConcatStringList * s2 = new ConcatStringList("_world");
//     ConcatStringList * s3 = new ConcatStringList(s1->concat(*s2));

//     cout << ConcatStringList::refList.refCountsString() << endl;
//     cout << ConcatStringList::delStrList.totalRefCountsString() << endl;

//     cout << "---After deleting s1---" << endl;
//     delete s1;
//     cout << ConcatStringList::refList.refCountsString() << endl;
//     cout << ConcatStringList::delStrList.totalRefCountsString() << endl;

//     cout << "---After deleting s3---" << endl;
//     delete s3;
//     cout << ConcatStringList::refList.refCountsString() << endl;
//     cout << ConcatStringList::delStrList.totalRefCountsString() << endl;

//     cout << "---After deleting s2---" << endl;
//     delete s2;
//     cout << ConcatStringList::refList.refCountsString() << endl;
//     cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
// }


int main() {
    tc2();
    return 0;
}
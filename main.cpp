#include "ConcatStringList.h"

void tc1() {
    ConcatStringList s1("Hello,_world");
    // test length
    cout << "s1's length: " << s1.length() << endl;
    // test get
    cout << "char at index 2: " << s1.get(2) << endl;
    try {
        cout << "char at index 22: " << s1.get(22) << endl;
    }
    catch (out_of_range & ofr) {
        cout << "Exception out_of_range: " << ofr.what() << endl;
    }
    // test indexOf
    cout << "in s1, index of 'o': " << s1.indexOf('o') << endl;
    cout << "in s1, index of 'a': " << s1.indexOf('a') << endl;
    // test toString
    cout << "s1 toString: " << s1.toString() << endl;
}

void tc2() {
    ConcatStringList s1("Hello,");
    ConcatStringList s2("_this_is");
    ConcatStringList s3("_an_assignment");

    // test concat
    ConcatStringList s4 = s1.concat(s2);
    cout << "s4: " << s4.toString() << endl;

    cout<< ConcatStringList::refList.refCountsString()<<endl;
    cout<< ConcatStringList::delStrList.totalRefCountsString()<<endl;
    ConcatStringList s5 = s1.concat(s2).concat(s3);
    cout << "s5: " << s5.toString() << endl;

    cout<< ConcatStringList::refList.refCountsString()<<endl;
    cout<< ConcatStringList::delStrList.totalRefCountsString()<<endl;
    // test subString
    ConcatStringList s6 = s5.subString(5, 15);
    cout << "s6: " << s6.toString() << endl;
    
    cout<< ConcatStringList::refList.refCountsString()<<endl;
    cout<< ConcatStringList::delStrList.totalRefCountsString()<<endl;
    // test reverse
    ConcatStringList s7 = s5.reverse();
    cout << "s7: " << s7.toString() << endl;
    
    cout<< ConcatStringList::refList.refCountsString()<<endl;
    cout<< ConcatStringList::delStrList.totalRefCountsString()<<endl;
}

void tc3() {
    ConcatStringList * s1 = new ConcatStringList("Hello");
    ConcatStringList * s2 = new ConcatStringList("_world");
    ConcatStringList * s3 = new ConcatStringList(s1->concat(*s2));

    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;

    cout << "---After deleting s1---" << endl;
    delete s1;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;

    cout << "---After deleting s3---" << endl;
    delete s3;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;

    cout << "---After deleting s2---" << endl;
    delete s2;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
}


void tc21() {
    
    ConcatStringList s1("Hello,");
    ConcatStringList s2("_this_is");
    ConcatStringList s3("_an_assignment");
    ConcatStringList s4 = s1.concat(s2);
    cout << "s4: " << s4.toString() << endl;
    cout<<"Current Ref \n"; ConcatStringList::refList.printRefDebug();
    cout<< ConcatStringList::refList.refCountsString()<<endl;
    cout<< ConcatStringList::delStrList.totalRefCountsString()<<endl;
    // ConcatStringList s5 = s1.concat(s2).concat(s3);
    // cout << "s5: " << s5.toString() << endl;
    // cout<<"Current Ref \n"; ConcatStringList::refList.printRefDebug();

    // cout << "s1: " << s1.toString() << endl;
    // cout << "s2: " << s2.toString() << endl;

    
    
}

void tc22() {
    ConcatStringList s1("Hello,");

    ConcatStringList s2("_this_is");
    ConcatStringList s3("_an_assignment");
    ConcatStringList s4("_new_string_");
    
    ConcatStringList s11 = s1.reverse();
    cout << "s11: " << s11.toString() << endl;
    cout<<"Current Ref 1\n";
    ConcatStringList::refList.printRefDebug();

    ConcatStringList s111 = s11.reverse();
    cout << "s111: " << s111.toString() << endl;
    cout<<"Current Ref 2\n";
    ConcatStringList::refList.printRefDebug();

    ConcatStringList s1111 = s111.reverse();
    cout << "s1111: " << s1111.toString() << endl;
    cout<<"Current Ref 3\n";
    ConcatStringList::refList.printRefDebug();

    // ConcatStringList s100 = s1.concat(s11).concat(s111).concat(s1111);
    // ConcatStringList::refList.printRefDebug();


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

void tc23() {
    ConcatStringList s1("Hello,");

    ConcatStringList s2("_this_is");
    ConcatStringList s3("_an_assignment");
    
    ConcatStringList s11 = s1.reverse();
    cout << "s11: " << s11.toString() << endl;
    cout<<"Current Ref 1\n";
    ConcatStringList::refList.printRefDebug();

    ConcatStringList s111 = s11.reverse();
    cout << "s111: " << s111.toString() << endl;
    cout<<"Current Ref 2\n";
    ConcatStringList::refList.printRefDebug();

    // ConcatStringList s110 = s111.subString(2,5);
    // cout << "s110: " << s110.toString() << endl;
    // cout << "s111: " << s111.toString() << endl;
    // cout<<"Current Ref 3\n";
    // ConcatStringList::refList.printRefDebug();

    
    ConcatStringList s100 = s111.subString(2,5).subString(1,2);
    cout << "s100: " << s100.toString() << endl;
    cout << "s111: " << s111.toString() << endl;
    cout<<"Current Ref 4\n";
    ConcatStringList::refList.printRefDebug();

}

void tc24() {
    ConcatStringList s1("Hello,");
    ConcatStringList s2("_this_is");
    ConcatStringList s3("_an_assignment");
    ConcatStringList s4("_which_no_one_like");

    ConcatStringList s11 = s1.reverse();
    cout << "s11: " << s11.toString() << endl;
    cout<<"Current Ref 1\n";
    ConcatStringList::refList.printRefDebug();

    ConcatStringList s111 = s11.reverse();
    cout << "s111: " << s111.toString() << endl;
    cout<<"Current Ref 2\n";
    ConcatStringList::refList.printRefDebug();
    
    ConcatStringList s100 = s111.subString(2,4);
    cout << "s100: " << s100.toString() << endl;
    
    
    ConcatStringList s5 = s1.concat(s2);
    cout << "s5: " << s5.toString() << endl;


    ConcatStringList s6 = s3.concat(s4).concat(s100);
    cout << "s6: " << s6.toString() << endl;

    cout<<"Current Ref 4\n";
    ConcatStringList::refList.printRefDebug();
    
    cout <<"refList.size() = " << ConcatStringList::refList.size() << endl;
    cout <<"refList.refCountAt(0) = "<< ConcatStringList::refList.refCountAt(0) << endl;
    cout <<"refList.refCountAt(1) = "<< ConcatStringList::refList.refCountAt(1) << endl;
    cout <<"refList.refCountAt(2) = "<< ConcatStringList::refList.refCountAt(2) << endl;
    cout <<"refList.refCountAt(3) = "<< ConcatStringList::refList.refCountAt(3) << endl;
    cout <<"refList.refCountAt(4) = "<< ConcatStringList::refList.refCountAt(4) << endl;
    cout <<"refList.refCountAt(5) = "<< ConcatStringList::refList.refCountAt(5) << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
}

void tc25() {
    ConcatStringList s1("Hello,");
    ConcatStringList s2("_this_is");
    ConcatStringList s3("_an_assignment");
    ConcatStringList s4("_which_no_one_like");
    
    ConcatStringList s100 = s1.subString(2,4);
    cout << "s100: " << s100.toString() << endl;
    cout<<"Current Ref 1\n";
    ConcatStringList::refList.printRefDebug();
    
    ConcatStringList s5 = s1.concat(s2);
    cout << "s5: " << s5.toString() << endl;
    cout<<"Current Ref 2\n";
    ConcatStringList::refList.printRefDebug();

    ConcatStringList s6 = s3.concat(s4).concat(s100);
    cout << "s6: " << s6.toString() << endl;
    cout<<"Current Ref 3\n";
    ConcatStringList::refList.printRefDebug();
    
    cout <<"refList.size() = " << ConcatStringList::refList.size() << endl;
    cout <<"refList.refCountAt(0) = "<< ConcatStringList::refList.refCountAt(0) << endl;
    cout <<"refList.refCountAt(1) = "<< ConcatStringList::refList.refCountAt(1) << endl;
    cout <<"refList.refCountAt(2) = "<< ConcatStringList::refList.refCountAt(2) << endl;
    cout <<"refList.refCountAt(3) = "<< ConcatStringList::refList.refCountAt(3) << endl;
    cout <<"refList.refCountAt(4) = "<< ConcatStringList::refList.refCountAt(4) << endl;
    cout <<"refList.refCountAt(5) = "<< ConcatStringList::refList.refCountAt(5) << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
}

void tc31() {
    ConcatStringList * s1 = new ConcatStringList("Hello,");
    ConcatStringList * s2 = new ConcatStringList("_this_is");
    ConcatStringList * s3 = new ConcatStringList(s1->concat(*s2));
    ConcatStringList * s4 = new ConcatStringList(s3->subString(0, 14));
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout << ConcatStringList::refList.size() << endl;
    cout << ConcatStringList::refList.refCountAt(0) << endl;
 
    delete s4;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    delete s3;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    delete s2;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    delete s1;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
}
 
void tc32() {
    ConcatStringList * s1 = new ConcatStringList("Hello,");
    ConcatStringList * s2 = new ConcatStringList("_this_is");
    ConcatStringList * s3 = new ConcatStringList("_an_assignment");
    ConcatStringList * s4 = new ConcatStringList(s1->concat(*s2));
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout << ConcatStringList::refList.size() << endl;
    cout << ConcatStringList::refList.refCountAt(0) << endl;
    cout << "---After deleting s2---" << endl;
    delete s2;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout << ConcatStringList::refList.size() << endl;
    cout << ConcatStringList::refList.refCountAt(0) << endl;
    cout << "---After deleting s4---" << endl;
    delete s4;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout << ConcatStringList::refList.size() << endl;
    cout << ConcatStringList::refList.refCountAt(0) << endl;
    
    cout << "---After deleting s1---" << endl;
    delete s1;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout << ConcatStringList::refList.size() << endl;
    cout << ConcatStringList::refList.refCountAt(0) << endl;
    cout << "---After deleting s3---" << endl;
    delete s3;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout << ConcatStringList::refList.size() << endl;
}
 
void tc33(){
    ConcatStringList * s1 = new ConcatStringList("Hello,");
    ConcatStringList * s2 = new ConcatStringList(s1->reverse());
 
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout << "---After deleting s2---" << endl;
    delete s2;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    
    cout << "---After deleting s1---" << endl;
    delete s1;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
}

void tc34() {
    ConcatStringList * s1 = new ConcatStringList("Hello");
    ConcatStringList * s2 = new ConcatStringList("_world");
    ConcatStringList * s4 = new ConcatStringList("_LOL");
    ConcatStringList * s3 = new ConcatStringList(s1->concat(*s2));

    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;

    
    cout << "---After deleting s3---" << endl;
    delete s3;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;

    cout << "---After deleting s4---" << endl;
    delete s4;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;

    cout << "---After deleting s2---" << endl;
    delete s2;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;

    cout << "---After deleting s1---" << endl;
    delete s1;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;

}
void tc35() {
    ConcatStringList * s1 = new ConcatStringList("Hello");
    ConcatStringList * s2 = new ConcatStringList("_world");
    ConcatStringList * s4 = new ConcatStringList("_LOL");

    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;

    
    cout << "---After deleting s4---" << endl;
    delete s4;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;

    cout << "---After deleting s2---" << endl;
    delete s2;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;

    cout << "---After deleting s1---" << endl;
    delete s1;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;

}

void tc36() {
    ConcatStringList * s1 = new ConcatStringList("Hello,");
    ConcatStringList * s2 = new ConcatStringList("_this_is");
    ConcatStringList * s3 = new ConcatStringList(s1->concat(*s2));
    ConcatStringList * s4 = new ConcatStringList(s3->reverse());

    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout << ConcatStringList::refList.size() << endl;
    cout << ConcatStringList::refList.refCountAt(0) << endl;
    delete s4;
    
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    delete s3;
    
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    delete s2;
    
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    delete s1;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
}

void tc37() {
    ConcatStringList * s1 = new ConcatStringList("Hello,");
    ConcatStringList * s2 = new ConcatStringList("_this_is");
    ConcatStringList * s3 = new ConcatStringList(s1->concat(*s2));
    ConcatStringList * s4 = new ConcatStringList(s3->reverse());
    ConcatStringList * s5 = new ConcatStringList(s4->subString(3,9));
    ConcatStringList * s6 = new ConcatStringList(s4->concat(*s5));

    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout <<"Ref size"<< ConcatStringList::refList.size() << endl;
    cout <<"Ref at 0"<< ConcatStringList::refList.refCountAt(0) << endl;
    cout <<"Del size "<< ConcatStringList::delStrList.size() << endl;

    cout<<"After Delete s6\n";
    delete s6;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout <<"Ref size"<< ConcatStringList::refList.size() << endl;
    cout <<"Ref at 0"<< ConcatStringList::refList.refCountAt(0) << endl;
    cout <<"Del size "<< ConcatStringList::delStrList.size() << endl;

    cout<<"After Delete s3\n";
    delete s3;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout <<"Ref size"<< ConcatStringList::refList.size() << endl;
    cout <<"Ref at 0"<< ConcatStringList::refList.refCountAt(0) << endl;
    cout <<"Del size "<< ConcatStringList::delStrList.size() << endl;

    cout<<"After Delete s1\n";
    delete s1;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout <<"Ref size"<< ConcatStringList::refList.size() << endl;
    cout <<"Ref at 0"<< ConcatStringList::refList.refCountAt(0) << endl;
    cout <<"Del size "<< ConcatStringList::delStrList.size() << endl;

    cout<<"After Delete s5\n";
    delete s5;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout <<"Ref size"<< ConcatStringList::refList.size() << endl;
    cout <<"Ref at 0"<< ConcatStringList::refList.refCountAt(0) << endl;
    cout <<"Del size "<< ConcatStringList::delStrList.size() << endl;

    cout<<"After Delete s2\n";
    delete s2;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout <<"Ref size"<< ConcatStringList::refList.size() << endl;
    cout <<"Ref at 0"<< ConcatStringList::refList.refCountAt(0) << endl;
    cout <<"Del size "<< ConcatStringList::delStrList.size() << endl;

    cout<<"After Delete s4\n";
    delete s4;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout <<"Ref size"<< ConcatStringList::refList.size() << endl;
    cout <<"Del size "<< ConcatStringList::delStrList.size() << endl;
}

void tc38() {
    ConcatStringList * s1 = new ConcatStringList("Hello,");
    ConcatStringList * s2 = new ConcatStringList(s1->reverse());

    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout <<"Ref size"<< ConcatStringList::refList.size() << endl;
    cout <<"Ref at 0"<< ConcatStringList::refList.refCountAt(0) << endl;
    cout <<"Del size "<< ConcatStringList::delStrList.size() << endl;

    cout<<"After Delete s2\n";
    delete s2;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout <<"Ref size"<< ConcatStringList::refList.size() << endl;
    cout <<"Ref at 0"<< ConcatStringList::refList.refCountAt(0) << endl;
    cout <<"Del size "<< ConcatStringList::delStrList.size() << endl;

    cout<<"After Delete s1\n";
    delete s1;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout <<"Ref size"<< ConcatStringList::refList.size() << endl;
    cout <<"Del size "<< ConcatStringList::delStrList.size() << endl;

}

int main() {
    cout<<"Checking testcase 38\n";
    tc2();
    //cout<<"Checking testcase 32\n";
    //tc32();
    // cout<<"Checking testcase 33\n";
    // tc33();
    // cout<<"Checking testcase 34\n";
    // tc34();
    // cout<<"Checking testcase 35\n";
    // tc35();
    // cout<<"Checking testcase 36\n";
    // tc36();
    //cout<<"Checking testcase 37\n";
    //tc37();
    return 0;
}
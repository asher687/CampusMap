#include <gtest/gtest.h>
#include "mymap.h"
#include "myrandom.h"
#include <iostream>
#include <sstream>

// Tests the main constructor
TEST(mymap, myMapConstructor) {
  // Constructs a default map, empty
  mymap<int,int> firstMap;
  // Will add nodes to the map and test size incrementation
	assert(firstMap.Size() == 0);
	firstMap.put(4,7);
	assert(firstMap.Size() == 1);
  firstMap.put(5,7);
	assert(firstMap.Size() == 2);
  firstMap.put(9,7);
	assert(firstMap.Size() == 3);
  firstMap.put(1,7);
	assert(firstMap.Size() == 4);
  firstMap.put(2,7);
	assert(firstMap.Size() == 5);
  //Test for value incrementation with equal node keys
  firstMap.put(4, 1);
  //cout << "Mymapsize: " << firstMap.Size() << endl;
  assert(firstMap.Size() == 5);

}

// Tests the main constructor of mymap with different types
TEST(mymap, myMap_double_Int_Constructor) {
  mymap<double,int> firstMap;
  // Will add nodes to the map and test size incrementation
	assert(firstMap.Size() == 0);
	firstMap.put(4.1,7);
	assert(firstMap.Size() == 1);
  firstMap.put(5.2,7);
	assert(firstMap.Size() == 2);
  firstMap.put(9.3,7);
	assert(firstMap.Size() == 3);
  firstMap.put(1.5,7);
	assert(firstMap.Size() == 4);
  firstMap.put(2.3,7);
	assert(firstMap.Size() == 5);
  //Test for value incrementation with equal node keys
  firstMap.put(4.1, 1);
  //cout << "Mymapsize: " << firstMap.Size() << endl;
  //cout << firstMap.toString() << endl;
  assert(firstMap.Size() == 5);

}

// given slides test: Makes a big tree and checks every
// signle node for correctness by comparing to regurlar map
TEST(mymap, Milestone1_Everything_Int_Int) {
    // test to compare with C++ map
    mymap<int, int> mapMine;
    map<int,int> mapSol;
    //int n = 1000000;  // # of elements inserted
    //int n = 5;
    // fill up BOTH maps
    for (int i = 1; i <= 10; i++) {
        int key = randomInteger(0,10);  // given
        int val = randomInteger(0,10);
        mapMine.put(key, val);
        mapSol[key] = val;
    }
    // 1. Assert sizes are equal
    EXPECT_EQ(mapMine.Size(), mapSol.size());
    // 2. String test (order is correct)
    stringstream solution("");
    // Fill string stream with mapSol
    for (auto e : mapSol) {
        solution << "key: " << e.first;
        solution << " value: " << e.second << endl;
     // 3. Test map contents
        EXPECT_TRUE(mapMine.contains(e.first));
        EXPECT_EQ(mapMine.get(e.first), e.second);
    }
    EXPECT_EQ(mapMine.toString(), solution.str());
   //cout << mapMine.toString() << endl;
}

TEST(mymap, Milestone1_Everything_Int_double) {
    // test to compare with C++ map
    mymap<int, double> mapMine;
    map<int,double> mapSol;
    int n = 100;  // # of elements inserted
    //int n = 5;
    // fill up BOTH maps
    for (int i = 1; i <= n; i++) {
        int key = randomInteger(0,n);  // given
        double val = randomInteger(0,n);
        mapMine.put(key, val);
        mapSol[key] = val;
    }
    // 1. Assert sizes are equal
    EXPECT_EQ(mapMine.Size(), mapSol.size());
    // 2. String test (order is correct)
    stringstream solution("");
    // Fill string stream with mapSol
    for (auto e : mapSol) {
        solution << "key: " << e.first;
        solution << " value: " << e.second << endl;
     // 3. Test map contents
        EXPECT_TRUE(mapMine.contains(e.first));
        EXPECT_EQ(mapMine.get(e.first), e.second);
    }
    EXPECT_EQ(mapMine.toString(), solution.str());
   //cout << mapMine.toString() << endl;
}

TEST(mymap, Milestone1_Everything_Int_String) {
    // test to compare with C++ map
    mymap<int, string> mapMine;
    map<int,string> mapSol;
    int n = 100;  // # of elements inserted
    //int n = 5;
    // fill up BOTH maps
    for (int i = 1; i <= n; i++) {
        int key = randomInteger(0,n);  // given
        //int val = randomInteger(0,10);
        string val = "Hello";
        mapMine.put(key, val);
        mapSol[key] = val;
    }
    // 1. Assert sizes are equal
    EXPECT_EQ(mapMine.Size(), mapSol.size());
    // 2. String test (order is correct)
    stringstream solution("");
    // Fill string stream with mapSol
    for (auto e : mapSol) {
        solution << "key: " << e.first;
        solution << " value: " << e.second << endl;
     // 3. Test map contents
        EXPECT_TRUE(mapMine.contains(e.first));
        EXPECT_EQ(mapMine.get(e.first), e.second);
    }
    EXPECT_EQ(mapMine.toString(), solution.str());
   //cout << mapMine.toString() << endl;
}

TEST(mymap, Milestone1_Everything_Int_Char) {
    // test to compare with C++ map
    mymap<int, char> mapMine;
    map<int, char> mapSol;
    int n = 100;  // # of elements inserted
    //int n = 5;
    // fill up BOTH maps
    for (int i = 1; i <= n; i++) {
        int key = randomInteger(0,n);  // given
        //int val = randomInteger(0,10);
        char val = '$';
        mapMine.put(key, val);
        mapSol[key] = val;
    }
    // 1. Assert sizes are equal
    EXPECT_EQ(mapMine.Size(), mapSol.size());
    // 2. String test (order is correct)
    stringstream solution("");
    // Fill string stream with mapSol
    for (auto e : mapSol) {
        solution << "key: " << e.first;
        solution << " value: " << e.second << endl;
     // 3. Test map contents
        EXPECT_TRUE(mapMine.contains(e.first));
        EXPECT_EQ(mapMine.get(e.first), e.second);
    }
    EXPECT_EQ(mapMine.toString(), solution.str());
   //cout << mapMine.toString() << endl;
}

TEST(mymap, Milestone1_Everything_Double_Int) {
    // test to compare with C++ map
    mymap<double, int> mapMine;
    map<double, int> mapSol;
    int n = 100;  // # of elements inserted
    //int n = 5;
    // fill up BOTH maps
    for (int i = 1; i <= n; i++) {
        double key = randomInteger(0,n);  // given
        int val = randomInteger(0,n);
        mapMine.put(key, val);
        mapSol[key] = val;
    }
    // 1. Assert sizes are equal
    EXPECT_EQ(mapMine.Size(), mapSol.size());
    // 2. String test (order is correct)
    stringstream solution("");
    // Fill string stream with mapSol
    for (auto e : mapSol) {
        solution << "key: " << e.first;
        solution << " value: " << e.second << endl;
     // 3. Test map contents
        EXPECT_TRUE(mapMine.contains(e.first));
        EXPECT_EQ(mapMine.get(e.first), e.second);
    }
    EXPECT_EQ(mapMine.toString(), solution.str());
   // cout << mapMine.toString() << endl;
}

TEST(mymap, Milestone1_Everything_Double_String) {
    // test to compare with C++ map
    mymap<double, string> mapMine;
    map<double, string> mapSol;
    int n = 100;  // # of elements inserted
    //int n = 5;
    // fill up BOTH maps
    for (int i = 1; i <= n; i++) {
        double key = randomInteger(0,n);  // given
        //int val = randomInteger(0,n);
        string val = "Hello";
        mapMine.put(key, val);
        mapSol[key] = val;
    }
    // 1. Assert sizes are equal
    EXPECT_EQ(mapMine.Size(), mapSol.size());
    // 2. String test (order is correct)
    stringstream solution("");
    // Fill string stream with mapSol
    for (auto e : mapSol) {
        solution << "key: " << e.first;
        solution << " value: " << e.second << endl;
     // 3. Test map contents
        EXPECT_TRUE(mapMine.contains(e.first));
        EXPECT_EQ(mapMine.get(e.first), e.second);
    }
    EXPECT_EQ(mapMine.toString(), solution.str());
   // cout << mapMine.toString() << endl;
}

TEST(mymap, Milestone1_Everything_Double_char) {
    // test to compare with C++ map
    mymap<double, char> mapMine;
    map<double, char> mapSol;
    int n = 100;  // # of elements inserted
    //int n = 5;
    // fill up BOTH maps
    for (int i = 1; i <= n; i++) {
        double key = randomInteger(0,n);  // given
        char val = '$';  //randomInteger(0,n);
        mapMine.put(key, val);
        mapSol[key] = val;
    }
    // 1. Assert sizes are equal
    EXPECT_EQ(mapMine.Size(), mapSol.size());
    // 2. String test (order is correct)
    stringstream solution("");
    // Fill string stream with mapSol
    for (auto e : mapSol) {
        solution << "key: " << e.first;
        solution << " value: " << e.second << endl;
     // 3. Test map contents
        EXPECT_TRUE(mapMine.contains(e.first));
        EXPECT_EQ(mapMine.get(e.first), e.second);
    }
    EXPECT_EQ(mapMine.toString(), solution.str());
   // cout << mapMine.toString() << endl;
}

TEST(mymap, operatorKeyAddition) {
mymap<string, int> testMe;
map<string, int> correct;
string astring;
string anotherstring;

string arr[26] = {"Apple", "Bannana", "Cat", "D", "E", "F", "G", "H", "I", "J", "K", "M", "N", "L", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
for (int i = 0; i < 26; i++) {

 //EXPECT_EQ(testMe[1], valueType);
 int r = randomInteger(0,26);

 testMe[arr[r]];

 astring = testMe.toString();
 anotherstring = testMe.checkBalance();


}
  cout << "In order " << endl;
  cout << astring << endl;
  cout << "Pre order" << endl;
  cout << anotherstring << endl;

}

TEST(mymap, Milestone1_Everything_char_char) {
    // test to compare with C++ map
    mymap<char, char> mapMine;
    map<char, char> mapSol;
    //int n = 1000000;  // # of elements inserted

    // fill up BOTH maps
    for (int i = 1; i <= 10; i++) {
        char key = randomInteger('A','z');  // given
        //cout << "Stroing key: " << key << endl;
        char val = '$';  //randomInteger(0,n);
        mapMine.put(key, val);
        mapSol[key] = val;
    }
    // 1. Assert sizes are equal
    EXPECT_EQ(mapMine.Size(), mapSol.size());
    // 2. String test (order is correct)
    stringstream solution("");
    // Fill string stream with mapSol
    for (auto e : mapSol) {
        solution << "key: " << e.first;
        solution << " value: " << e.second << endl;
     // 3. Test map contents
        EXPECT_TRUE(mapMine.contains(e.first));
        EXPECT_EQ(mapMine.get(e.first), e.second);
    }
    EXPECT_EQ(mapMine.toString(), solution.str());
    // cout << mapMine.toString() << endl;
}

TEST(mymap, Milestone1_Everything_char_double) {
    // test to compare with C++ map
    mymap<char, double> mapMine;
    map<char, double> mapSol;
    //int n = 1000000;  // # of elements inserted

    // fill up BOTH maps
    for (int i = 1; i <= 10; i++) {
        char key = randomInteger('A','z');  // given
        // cout << "Key: " << key << endl;
        double val = randomInteger(0,10);
        mapMine.put(key, val);
        mapSol[key] = val;
    }
    // 1. Assert sizes are equal
    EXPECT_EQ(mapMine.Size(), mapSol.size());
    // 2. String test (order is correct)
    stringstream solution("");
    // Fill string stream with mapSol
    for (auto e : mapSol) {
        solution << "key: " << e.first;
        solution << " value: " << e.second << endl;
     // 3. Test map contents
        EXPECT_TRUE(mapMine.contains(e.first));
        EXPECT_EQ(mapMine.get(e.first), e.second);
    }
    EXPECT_EQ(mapMine.toString(), solution.str());
    // cout << mapMine.toString() << endl;
}

TEST(mymap, Milestone1_Everything_char_string) {
    // test to compare with C++ map
    mymap<char, string> mapMine;
    map<char, string> mapSol;
    //int n = 1000000;  // # of elements inserted

    // fill up BOTH maps
    for (int i = 1; i <= 10; i++) {
        char key = randomInteger('A','z');  // given
        //cout << "Key: " << key << endl;
        string val = "Hello";  // randomInteger(0,10);
        mapMine.put(key, val);
        mapSol[key] = val;
    }
    // 1. Assert sizes are equal
    EXPECT_EQ(mapMine.Size(), mapSol.size());
    // 2. String test (order is correct)
    stringstream solution("");
    // Fill string stream with mapSol
    for (auto e : mapSol) {
        solution << "key: " << e.first;
        solution << " value: " << e.second << endl;
     // 3. Test map contents
        EXPECT_TRUE(mapMine.contains(e.first));
        EXPECT_EQ(mapMine.get(e.first), e.second);
    }
    EXPECT_EQ(mapMine.toString(), solution.str());
    // cout << mapMine.toString() << endl;
}

TEST(mymap, Milestone1_Everything_char_string_Manual) {
    // test to compare with C++ map
    mymap<char, string> mapMine;
    map<char, string> mapSol;
    // int n = 1000000;  // # of elements inserted

    // fill up BOTH maps
    char key = '&';
    string val = "Hello";
    mapMine.put(key, val);
    mapSol[key] = val;

    key++;
    val = "Hello";
    mapMine.put(key, val);
    mapSol[key] = val;

    key++;
    val = "Hello";
    mapMine.put(key, val);
    mapSol[key] = val;

    key++;
    val = "Hello";
    mapMine.put(key, val);
    mapSol[key] = val;

    key++;
    val = "Hello";
    mapMine.put(key, val);
    mapSol[key] = val;

    key++;
    val = "Hello";
    mapMine.put(key, val);
    mapSol[key] = val;

    key++;
    val = "Hello";
    mapMine.put(key, val);
    mapSol[key] = val;

    key++;
    val = "Hello";
    mapMine.put(key, val);
    mapSol[key] = val;

    string astring = mapMine.toString();
    cout << astring << endl;

    // 1. Assert sizes are equal
    EXPECT_EQ(mapMine.Size(), mapSol.size());
    // 2. String test (order is correct)
    stringstream solution("");
    // Fill string stream with mapSol
    for (auto e : mapSol) {
        solution << "key: " << e.first;
        solution << " value: " << e.second << endl;
     // 3. Test map contents
        EXPECT_TRUE(mapMine.contains(e.first));
        EXPECT_EQ(mapMine.get(e.first), e.second);
    }
    EXPECT_EQ(mapMine.toString(), solution.str());
    // cout << mapMine.toString() << endl;
}

TEST(mymap, Milestone1_Everything_string_string) {
    // test to compare with C++ map
    mymap<string, string> mapMine;
    map<string, string> mapSol;

    // fill up BOTH maps

        string key = "Hello";
        cout << "Key: " << key << endl;
        string val = "Hello";  // randomInteger(0,10);
        mapMine.put(key, val);
        mapSol[key] = val;

        key = "Bye";
        cout << "Key: " << key << endl;
        val = "Hello";  // randomInteger(0,10);
        mapMine.put(key, val);
        mapSol[key] = val;

        key = "Jay";
        cout << "Key: " << key << endl;
        val = "Hello";  // randomInteger(0,10);
        mapMine.put(key, val);
        mapSol[key] = val;

        key = "Fame";
        cout << "Key: " << key << endl;
        val = "Hello";  // randomInteger(0,10);
        mapMine.put(key, val);
        mapSol[key] = val;

        key = "Late";
        cout << "Key: " << key << endl;
        val = "Hello";  // randomInteger(0,10);
        mapMine.put(key, val);
        mapSol[key] = val;

        key = "Bake";
        cout << "Key: " << key << endl;
        val = "Hello";  // randomInteger(0,10);
        mapMine.put(key, val);
        mapSol[key] = val;

    // 1. Assert sizes are equal
    EXPECT_EQ(mapMine.Size(), mapSol.size());
    // 2. String test (order is correct)
    stringstream solution("");
    // Fill string stream with mapSol
    for (auto e : mapSol) {
        solution << "key: " << e.first;
        solution << " value: " << e.second << endl;
     // 3. Test map contents
        EXPECT_TRUE(mapMine.contains(e.first));
        EXPECT_EQ(mapMine.get(e.first), e.second);
    }
    EXPECT_EQ(mapMine.toString(), solution.str());
    // cout << mapMine.toString() << endl;
}

// Will populate a mympap and a regular map and
// use a for loop to test the iterator on my map
// by comparing it to a regular map
TEST(mymap, Iterator) {
   mymap<int, int> test;
   map<int, int> correct;
   int seed = 100;
   for(int i = 0; i < 10; i++) {
    // randomize key and val
    int k = randomInteger(0,seed);
    int v = randomInteger(0,seed);
    test.put(k, v);

   }
   stringstream ss;
   for (int key : test) {
      // it does work like this
      ss << "key: " << key <<
         " value: " << test[key]
         << endl;
   }
   // loop should be in order
   ASSERT_EQ(test.toString(),
      ss.str());
}

// Will populate a mymap, try clearing it, and then
// checking its size
TEST(mymap, clear) {
  mymap<int,int> m;

  for (int i=0;i<5;i++) {
    int x = randomInteger(0,10);
    m.put(x, x);
    EXPECT_NE(m.Size(), 0);
  }
  m.clear();
  ASSERT_EQ(m.Size(), 0);
}

// Populates a signle mymap
// and then copies it using a
// new and mymap that is in the process
// of being constructed
TEST(mymap, equalsConstructor) {
  mymap<int,int> m1;
  for (int b=0;b<5;b++) {
    int f = randomInteger(0,10);
    m1.put(f, f);
  }
  mymap<int,int> m2 = m1;

   ASSERT_EQ(m2.Size(), m1.Size());
   ASSERT_EQ(m2.toString(), m1.toString());
  // cout << "m2 size: " << m2.Size() << endl;
//   m2.clear();
//   m1.clear();
  }

TEST(mymap, equalsOperator) {
  mymap<int,int> m3;
  // cout << "Filling m3" << endl;
  for (int i=0;i<5;i++) {
    int x = randomInteger(0,10);
    m3.put(x, x);
  }

  mymap<int,int> m4;
  // cout << "Filling m4" << endl;
  for (int i=0;i<10;i++) {
    int x = randomInteger(0,10);
    m4.put(x, x);
  }

  // cout << "Setting m4 = m3" << endl;
  m4 = m3;     // main test

   ASSERT_EQ(m4.Size(), m3.Size());
   ASSERT_EQ(m4.toString(), m3.toString());
//   cout << "m3 size: " << m3.Size() << endl;
//   cout << "m4 size: " << m4.Size() << endl;
//   cout << m4.toString() << endl;

  }

// Populates a mymap and exits nicely

TEST(mymap, destructor) {
  mymap<int,int> m;
  for (int i=0;i<5;i++) {
    int x = randomInteger(0,10);
    m.put(x, x);
    EXPECT_NE(m.Size(), 0);
  }
}

// Populates a mymap and prints
// it out using a vector method
TEST(mymap, toVector) {
  mymap<int,int> m;
  for (int i=0;i<5;i++) {
    int x = randomInteger(0,10);
    m.put(x, x);
    EXPECT_NE(m.Size(), 0);
  }
  vector<pair<int,int>> vec = m.toVector();
}

// Provided by slides: populates a mymap
// and
TEST(mymap, checkBalance) {
  mymap<int,int> m;
  for (int i=0;i<5;i++) {
    int x = randomInteger(0,10);
    m.put(x, x);
    EXPECT_NE(m.Size(), 0);
  }
  m.checkBalance();
}

// Fills the tree with tree key values
TEST(mymap, testingProblematicNodes) {
  mymap<int,int> m;
  //m.put(2,2);
  m.put(1,1);
  m.put(2,2);
  m.put(3,3);
  m.put(4,4);
  m.put(5,5);
  m.put(6,6);
  m.put(7,2);
  m.put(8,1);
  m.put(9,5);
  m.put(10,3);
  m.put(11,4);

}

// provided by slides: populates a my map with 3 nodes
TEST(mymap, balancingCheck) {
  mymap<int,int> m;
  string s = "";
  for (int i=0;i<3;i++)
    m.put(i, i);
  s += "key: 1, nL: 1, nR: 1\n";
  s += "key: 0, nL: 0, nR: 0\n";
  s += "key: 2, nL: 0, nR: 0\n";
  ASSERT_EQ(m.checkBalance(), s);
}

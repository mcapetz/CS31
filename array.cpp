//
//  main.cpp
//  proj4
//
//  Created by Margaret Capetz on 10/29/21.
//

#include <iostream>
#include <string>

using namespace std;

int reduplicate(string a[], int n);
int locate(const string a[], int n, string target);
int locationOfMax(const string a[], int n);
int circleLeft(string a[], int n, int pos); //bonus
int enumerateRuns(const string a[], int n);
int flip(string a[], int n); //bonus
int locateDifference(const string a1[], int n1, const string a2[], int n2);
int subsequence(const string a1[], int n1, const string a2[], int n2);
int locateAny(const string a1[], int n1, const string a2[], int n2);
int separate(string a[], int n, string separator); //bonus
void print(string a[], int n);
void swap(string a[], int x, int y);


int main(int argc, const char * argv[]) {
    
    //reduplicate
    string stuff[6] = { "mahi", "bon", "cous", "", "tar", "mur" };
    assert(reduplicate(stuff, 6) == 6);
    assert(stuff[0] == "mahimahi" && stuff[1] == "bonbon" && stuff[2] == "couscous" && stuff[3] == "" && stuff[4] == "tartar" && stuff[5] == "murmur");
    assert(reduplicate(stuff, -6) == -1);
    assert(reduplicate(stuff, 0) == 0);
    
    //locate
    string a[6] = { "hello", "heLLo", "bonjour", "nihao", "hello", "gutentag"};
    assert(locate(a, 6, "hello") == 0);
    assert(locate(a, 6, "heLLo") == 1);
    assert(locate(a, 2, "nihao") == -1);
    assert(locate(a, 6, "henlo") == -1);
    assert(locate(a, 0, "hello") == -1);
    assert(locate(a, 6, "gutentag") == 5);
    assert(locate(a, -1, "gutentag") == -1);
    
    //location of max
    string b[6] = {"orange", "orange", "banana", "grape", "apple", "orange"};
    assert(locationOfMax(b, 6) == 0);
    assert(locationOfMax(b, -6) == -1);
    assert(locationOfMax(b, 0) == -1);
    string cc[4] = {"orange", "orange", "orange", "orange"};
    assert(locationOfMax(cc, 4) == 0);
    string dd[4] = {"", "", "", ""};
    assert(locationOfMax(dd, 4) == 0);
    
    //circleLeft
    string folks[5] = { "moana", "elsa", "ariel", "raya", "mulan" };
    assert(circleLeft(folks, 5, 0) == 0);
    assert(folks[0] == "elsa" && folks[1] == "ariel" && folks[2] == "raya" && folks[3] == "mulan" && folks[4] == "moana");
    string folks2[5] = { "moana", "elsa", "ariel", "raya", "mulan" };
    assert(circleLeft(folks2, 2, 0) == 0);
    assert(folks2[0] == "elsa" && folks2[1] == "moana" && folks2[2] == "ariel" && folks2[3] == "raya" && folks2[4] == "mulan");
    assert(circleLeft(folks, 4, 5) == -1);
    assert(circleLeft(folks, -4, 5) == -1);
    string folks3[5] = { "moana", "elsa", "ariel", "raya", "mulan" };
    assert(circleLeft(folks3, 5, 5) == -1);
    assert(circleLeft(folks3, 5, 4) == 4);
    assert(folks3[0] == "moana" && folks3[1] == "elsa" && folks3[2] == "ariel" && folks3[3] == "raya" && folks3[4] == "mulan");
    string folks4[5] = { "moana", "elsa", "ariel", "raya", "mulan" };
    assert(circleLeft(folks4, 5, 1) == 1);
    assert(folks4[0] == "moana" && folks4[1] == "ariel" && folks4[2] == "raya" && folks4[3] == "mulan" && folks4[4] == "elsa");

    //locate difference
    string roles[6] = { "merida", "raya", "", "belle", "moana", "elsa" };
    string group[5] = { "merida", "raya", "elsa", "", "belle" };
    string group2[5] = {"merida", "raya", "elsa", "", "belle" };
    assert(locateDifference(roles, 6, group, 5) == 2);
    assert(locateDifference(roles, 2, group, 1) == 1);
    assert(locateDifference(roles, 1, group, 0) == 0);
    assert(locateDifference(roles, 1, group, 1) == 1);
    assert(locateDifference(group, 5, group2, 5) == 5);
    
    //subsequence
    string names[10] = { "moana", "mulan", "raya", "tiana", "merida" };
    string names1[10] = { "mulan", "raya", "tiana" };
    assert(subsequence(names, 5, names1, 3) == 1);
    string names2[10] = { "moana", "tiana" };
    assert(subsequence(names, 4, names2, 2) == -1);
    assert(subsequence(names, 4, names2, 0) == 0);
    string names3[10] = {"moana", "tiana", "moana", "tiana", "moana", "tiana",};
    assert(subsequence(names3, 6, names2, 2) == 0);
    assert(subsequence(names3, 2, names2, 6) == -1);
    
    //enumerate runs
    string princesses[9] = { "belle", "merida", "raya", "raya", "tiana", "tiana", "tiana", "raya", "raya" };
    assert(enumerateRuns(princesses, 9) == 5);
    assert(enumerateRuns(names, 3) == 3);
    assert(enumerateRuns(names, 5) == 5);
    assert(enumerateRuns(princesses, -4) == -1);
    assert(enumerateRuns(dd, 4) == 1);
    assert(enumerateRuns(dd, 0) == 0);
    
    //flip
    string roles2[6] = { "merida", "raya", "", "belle", "moana", "elsa" };
    assert(flip(roles2, 0) == 0);
    assert(roles2[0] == "merida" && roles2[1] == "raya" && roles2[2] == "" && roles2[3] == "belle" && roles2[4] == "moana" && roles2[5] == "elsa");
    assert(flip(roles2, 1) == 1);
    assert(roles2[0] == "merida" && roles2[1] == "raya" && roles2[2] == "" && roles2[3] == "belle" && roles2[4] == "moana" && roles2[5] == "elsa");
    assert(flip(roles2, 6) == 6);
    assert(roles2[0] == "elsa" && roles2[1] == "moana" && roles2[2] == "belle" && roles2[3] == "" && roles2[4] == "raya" && roles2[5] == "merida");
    assert(flip(roles2, -4) == -1);
    string roles3[6] = { "merida", "raya", "", "belle", "moana", "elsa" };
    assert(flip(roles3, 4) == 4);
    assert(roles3[0] == "belle" && roles3[1] == "" && roles3[2] == "raya" && roles3[3] == "merida" && roles3[4] == "moana" && roles3[5] == "elsa");
    
    //locate any
    string namess[10] = { "moana", "mulan", "raya", "tiana", "merida", "moana" };
    string set1[10] = { "elsa", "merida", "tiana", "mulan" };
    string set3[10] = {"moana"};
    assert(locateAny(namess, 6, set1, 4) == 1);
    string set2[10] = { "belle", "ariel" };
    assert(locateAny(namess, 6, set2, 2) == -1);
    assert(locateAny(namess, -6, set2, 2) == -1);
    assert(locateAny(namess, 6, set2, -2) == -1);
    assert(locateAny(namess, 6, set3, 1) == 0);
    assert(locateAny(set2, 4, set3, 1) == -1);
    
    //proj spec test cases
    string h[7] = { "moana", "mulan", "ariel", "tiana", "", "belle", "elsa" };
    assert(locate(h, 7, "belle") == 5);
    assert(locate(h, 7, "ariel") == 2);
    assert(locate(h, 2, "ariel") == -1);
    assert(locationOfMax(h, 7) == 3);

    string g[4] = { "moana", "mulan", "belle", "raya" };
    assert(locateDifference(h, 4, g, 4) == 2);
    assert(circleLeft(g, 4, 1) == 1 && g[1] == "belle" && g[3] == "mulan");

    string c[4] = { "ma", "can", "tu", "do" };
    assert(reduplicate(c, 4) == 4 && c[0] == "mama" && c[3] == "dodo");

    string e[4] = { "ariel", "tiana", "", "belle" };
    assert(subsequence(h, 7, e, 4) == 2);

    string d[5] = { "mulan", "mulan", "mulan", "belle", "belle" };
    assert(enumerateRuns(d, 5) == 2);

    string f[3] = { "tiana", "ariel", "raya" };
    assert(locateAny(h, 7, f, 3) == 2);
    assert(flip(f, 3) == 3 && f[0] == "raya" && f[2] == "tiana");

    assert(separate(h, 7, "elsa") == 3);
    
    //separate
    string z[5] = {"d", "e", "a", "c", "b"};
    string h2[7] = { "moana", "mulan", "ariel", "tiana", "", "belle", "elsa" };
    string h3[6] = { "elsa", "ariel", "mulan", "belle", "tiana", "moana" };
    string empty[3] = {"", "", ""};
    assert(separate(z, 5, "c") == 2);
    //print(z, 5);
    assert(z[0] == "b" && z[1] == "a" && z[2] == "c" && z[3] == "e" && z[4] == "d");
    assert(separate(h3, 6, "merida") == 3);
    //print(h3, 6);
    assert(h3[0] == "elsa" && h3[1] == "ariel" && h3[2] == "belle" && h3[3] == "tiana" && h3[4] == "moana" && h3[5] == "mulan");
    assert(separate(h2, 7, "zelda") == 7);
    assert(separate(h2, 7, "azaelia") == 2);
    assert(separate(empty, 0, "z") == 0);
    assert(separate(empty, 2, "z") == 2);
    assert(separate(empty, -1, "z") == -1);
        
    cout << "All tests succeeded" << endl;
}

void print(string a[], int n) {
    for(int i = 0; i < n; i++){
        cout << a[i] << " ";
    }

    cout << endl;
}

void swap(string a[], int x, int y) {
    string temp1 = a[x];
    string temp2 = a[y];
    a[x] = temp2;
    a[y] = temp1;
}

int reduplicate(string a[], int n) {
    //bad argument
    if(n < 0) return -1;
    
    for(int i = 0; i < n; i++){
        a[i] += a[i];
    }
    
    return n;
}

int locate(const string a[], int n, string target) {
    //bad argument
    if(n < 0) return -1;
    
    for(int i = 0; i < n; i++){
        if(a[i] == target) {
            return i;
        }
    }
    
    return -1;
}


int locationOfMax(const string a[], int n) {
    //bad argument
    if(n <= 0) return -1;
    
    int x = 0;
    string temp = a[0];
    
    for(int i = 0; i < n; i++){
        if(a[i] != temp && a[i] > a[x]) {
            temp = a[i];
            x = i;
        }
    }
    
    return x;
    
}

int circleLeft(string a[], int n, int pos) {
    //bonus

    //bad argument
    if(n < 0 || pos >= n || pos < 0) return -1;
    
    string temp = a[pos];
    
    for(int i = pos; i < n - 1; i++){
        //cout << "i: " << i << a[i] << endl;
        a[i] = a[i+1];
    }
    
    a[n-1] = temp;
    
    //print(a, n);
    
    return pos;
}

int enumerateRuns(const string a[], int n) {
    //bad argument
    if(n < 0) return -1;
    
    //no elements --> no runs
    if(n == 0) return 0;
    
    int x = 1;
    
    for(int i = 1; i < n; i++){
        if(a[i] != a[i-1]) x++;
    }
    
    return x;
}

int flip(string a[], int n) {
    //bonus
    
    //bad argument
    if(n < 0) return -1;
    
    string front = "";
    string back = "";
    
    for(int i = 0; i < n / 2; i++){
//        front = a[i];
//        back = a[n - 1 - i];
//
//        a[i] = back;
//        a[n - 1 - i] = front;
        swap(a, i, n - 1 - i);
    }
    
    return n;
}

int locateDifference(const string a1[], int n1, const string a2[], int n2) {
    //bad argument
    if(n1 < 0 || n2 < 0) return -1;
    
    int min;
    
    if(n1 <= n2) min = n1;
    else min = n2;
    
    for(int i = 0; i < min; i++){
        if(a1[i] != a2[i]) return i;
    }
    
    return min;
}

int subsequence(const string a1[], int n1, const string a2[], int n2) {
    //bad argument
    if(n1 < 0 || n2 < 0 || n1 < n2) return -1;
    
    if(n2 == 0) return 0;
    
    int x = -1;
    bool found = true;
    
    for(int i = 0; i < n1; i++){
        found = true;
        if(a1[i] == a2[0]) {
            for(int j = 1; j < n2; j++){
                if(a1[i + j] != a2[j]) found = false;
            }
            if(found) {
                return i;
            }
        }
    }
    
    return x;
}

int locateAny(const string a1[], int n1, const string a2[], int n2) {
    //bad argument
    if(n1 < 0 || n2 < 0) return -1;
    
    int x = -1;
    
    for(int i = 0; i < n1; i++){
        for(int j = 0; j < n2; j++){
            if(a1[i] == a2[j]) return i;
        }
    }
    
    return x;
}

int separate(string a[], int n, string separator) {
    //bonus
    
    //bad argument
    if(n < 0) return -1;
    
    //i is the first index where the element is greater than separator
    //j is the first index where the element is not less than separator
    //check is the iterated var to check each index

    int i = n;
    int j = 0;
    int check = 0;
        

    while (check < i) {
        if (a[check] > separator) {
            //move to later position
            i--;
            swap(a, check, i);
        }
        else {
            if (a[check] < separator) {
                //move to a earlier position
                swap(a, check, j);
                j++;
            }
            //else a[check == separator
            check++;
        }
    }
        
    
    return j;
    
}

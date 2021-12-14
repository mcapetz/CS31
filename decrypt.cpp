//
//  main.cpp
//  proj50
//
//  Created by Margaret Capetz on 11/12/21.
//

#include <iostream>
#include <cctype>
#include <cstring>
#include <cassert>

using namespace std;

bool decrypt(const char ciphertext[], const char crib[]);
bool findCrib(const char ciphertext[], const char crib[], char key[]);
void simplify(char str[], int n);

void runtest(const char ciphertext[], const char crib[])
    {
        cout << "====== " << crib << endl;
        bool result = decrypt(ciphertext, crib);
        cout << "Return value: " << result << endl;
    }

    int main()
    {
        cout.setf(ios::boolalpha); // output bools as "true"/"false"
        
        runtest("kvbz 333***pqzzyfq 6783bz--zqxjqk", "secret"); //g31 test with punctuation
        runtest("kvbz 333***pqzzyfq 6783bz--zqxjjk", "secret"); //message not found
        runtest("", "secret"); //empty ciphertext
        runtest("kvbz 333***pqz", ""); //empty crib
        runtest("kvbz 333***pqz", "72389484@*&(#79987(*&@#$(*&"); //crib has no letters
        runtest("Hirdd ejsy zu drvtry od.\nO'z fodvtrry.\n", "my secret"); //msg found, newline at the end
        runtest("Hirdd ejsy zu drvtry od.\nO'z fodvtrry.\n", "shadow"); //msg not found, newline at end
        
        //the following test cases have different cribs that should behave the same
        runtest("F gspt fe! zyxZYXzyx--Abca abCa    bdefg## $$dsptrqtj6437 wvuWVUwvu\n\n8 9\n", "hush-hush until November 25, 2021"); //uppercase letters, punctuation in crib
        runtest("F gspt fe! zyxZYXzyx--Abca abCa    bdefg## $$dsptrqtj6437 wvuWVUwvu\n\n8 9\n", "   hush???hUSh---     --- until    NovemBER !!  "); //extra punctuation and spaces
        runtest("F gspt fe! zyxZYXzyx--Abca abCa    bdefg## $$dsptrqtj6437 wvuWVUwvu\n\n8 9\n", "hush hush until november"); //crib is already only lowercase letters, 1 space between words
        
        runtest("bwra wmwt\nqeirtk spst\n", "alan turing"); //crib split between new lines
        runtest("bwra wmwt qeirtk spst\n", "alan turing"); //crib not split between new lines
        
        runtest("Kpio't dmpbl-boe-ebhhfs opwfm", "s cloak"); //crib must be found in whole words
        runtest("Kpiost dmpbl-boe-ebhhfs opwfm", "s cloak"); //crib not found in whole words (crib matches partial word which is false)
        
        runtest("Rswjo qgx Tmeuo sgjsy jds vqgf vo jds vqzf xbby.\nUdbyjo iqcju cg wybgj cg jds esjqiqo zqy\nXbg'j rsj jds jsrrsy jycn jds ucrsgj qrqyt.\nZU 31 cu zdqrrsgecge!", "silent alarm"); //longer message, from spec
              
        
        //this test case is messing thigns up
        runtest("lskdjflksj832s87sdf8sd", "lksdfksdksdkfkdks saksdklsjfdsk lkjslksdfksdksdkfkdks saksdklsjfdsk lkjslksdfksdksdkfkdks saksdklsjfdsk lkjslksdfksdksdkfkdks saksdklsjfdsk lkjslksdfksdksdkfkdks saksdklsjfdsk lkjslksdfksdksdkfkdks saksdklsjfdsk lkjslksdfksdksdkfkdks saksdklsjfdsk lkjslksdfksdksdkfkdks saksdklsjfdsk lkjslksdfksdksdkfkdks saksdklsjfdsk lkjs"); //more than 90 crib letters
                
        runtest("ucrsgj qrqyt", "silent alarm"); //entire ciphertext can be decrypted
        
        
    }


void simplifyCrib(char str[]) {
    //cout << "str: " << str << endl;
    //cout << "len: " << strlen(str) << endl;
    
    bool isSimplified = false;
    
    while(!isSimplified) {
        int i = 0;
        //cout << "str: " << str << endl;

        while (i < 6555 && i < strlen(str)) {
            //cout << "i: " << i << endl;
            //cout << "n: " << n << endl;
            if(i < 6555 && !isalpha(str[i])) {
                //cout << "i got here" << endl;
                if(i < 6555 && isalpha(str[i+1])) {
                    //cout << "i got here2" << endl;
                    str[i] = ' ';
                    //cout << "str: " << str << endl;
                }
                
                else {
                    //not a letter --> remove
                    //cout << "remove" << endl;
                    //loop through and copy over chars to the left
                    for(int j = i; j < strlen(str) - 1; j++) {
                        str[j] = str[j+1];
                    }
                    //set last char to the zero byte to accomodate and shorten the length
                    str[strlen(str)-1] = '\0';
                    //cout << "str: " << str << endl;
                    
                    //reset i to check from beginning again?
                    
                }
            }
            i++;
            
        }
        //cout << "done with loop" << endl;
        //cout << "str: " << str << endl;
        
        isSimplified = true;
        
        for(int i = 0; i < strlen(str); i++) {
            //if not a blank and not an alphabet
            //cout << "str[i]: " << str[i] << endl;
            if(i < 6555 && !isalpha(str[i]) && !isblank(str[i])) {
                //cout << "not simplified" << endl;
                isSimplified = false;
            }
        }
        
    }
    
    //all to lower
    for(int i = 0; i < strlen(str); i++) {
        str[i] = tolower(str[i]);
    }
    
    //remove unecessary blanks
    
    //remove blanks at beginning
    int i = 0;
    while(isblank(str[i]) && i < strlen(str)) {
        for(int j = i; j < strlen(str) - 1; j++) {
            str[j] = str[j+1];
        }
        str[strlen(str)-1] = '\0';
        i++;
    }
    
    //remove blanks at the end
    while(strlen(str) > 0 && isblank(str[strlen(str)-1])) {
        str[strlen(str)-1] = '\0';
    }
    
    //remove blanks in the middle of two words
    i = 0;
    while(i < 6555 && i + 1 < strlen(str)) {
        if(i < 6555 && isblank(str[i]) && isblank(str[i + 1])) {
            //cout << "i got here, i: " << i << endl;
            //while the char and next char are blanks, remove the blank by copying over chars to the left then adjusting
            while(i < 6555 && isblank(str[i]) && isblank(str[i + 1])) {
                for(int j = i; j < strlen(str) - 1; j++) {
                    str[j] = str[j+1];
                }
                str[strlen(str)-1] = '\0';
            }
            i++;
        }
        i++;
        
    }
    
    //cout << "new str: " << str << endl;
    
}

void simplifyCipher(char str[]) {
    //n is the str length
    //cout << "str: " << str << endl;
    //cout << "len: " << strlen(str) << endl;
    
    bool isSimplified = false;
    
    while(!isSimplified) {
        int i = 0;
        //cout << "str: " << str << endl;
        //cout << "str len: " << strlen(str) << endl;

        while (i < 6555 && i < strlen(str)) {
            //cout << "i: " << i << endl;
            //cout << "n: " << n << endl;
            
            //if not a letter
            if(i < 6555 && !isalpha(str[i]) && str[i] != '\n') {
                //cout << "i got here" << endl;
                if(i < 6555 && isalpha(str[i+1])) {
                    //cout << "i got here2" << endl;
                    str[i] = ' ';
                    //cout << "str: " << str << endl;
                }
                
                else {
                    //not a letter --> remove
                    //cout << "remove" << endl;
                    for(int j = i; j < strlen(str) - 1; j++) {
                        str[j] = str[j+1];
                    }
                    str[strlen(str)-1] = '\0';
                    //cout << "str: " << str << endl;
                    
                }
            }
            
            i++;
            
        }
        //cout << "done with loop" << endl;
        //cout << "str: " << str << endl;
        
        isSimplified = true;
        
        for(int i = 0; i < strlen(str); i++) {
            //if not a blank and not an alphabet
            //cout << "str[i]: " << str[i] << endl;
            //for simplifyCipher, DO NOT REMOVE NEW LINE CHARS
            if(i < 6555 && !isalpha(str[i]) && !isblank(str[i]) && str[i] != '\n') {
                //cout << "not simplified" << endl;
                isSimplified = false;
            }
        }
        
    }
    
    //all to lower
    for(int i = 0; i < strlen(str); i++) {
        str[i] = tolower(str[i]);
    }
    
    //remove unecessary blanks
    
    //remove blanks at beginning
    int i = 0;
    while(i < 6555 && isblank(str[i]) && i < strlen(str)) {
        for(int j = i; j < strlen(str) - 1; j++) {
            str[j] = str[j+1];
        }
        str[strlen(str)-1] = '\0';
        i++;
    }
    
    //remove blanks at the end
    while(strlen(str) > 0 && isblank(str[strlen(str)-1])) {
        str[strlen(str)-1] = '\0';
    }
    
    //remove blanks in the middle of two words
    i = 0;
    while(i < 6555 && i + 1 < strlen(str)) {
        if(i < 6555 && isblank(str[i]) && isblank(str[i + 1])) {
            //cout << "i got here, i: " << i << endl;
            //while the char and next char are blanks, remove the blank by copying over chars to the left then adjusting
            while(i < 6555 && isblank(str[i]) && isblank(str[i + 1])) {
                for(int j = i; j < strlen(str) - 1; j++) {
                    str[j] = str[j+1];
                }
                str[strlen(str)-1] = '\0';
            }
            i++;
        }
        i++;
        
    }
    
    //cout << "new str: " << str << endl;
    
}

bool findCrib(const char ciphertext[], const char crib[], char key[]) {
    bool isMatch = true;
    //cout << "cipher: " << ciphertext << endl;
    //cout << "crib: " << crib << endl;
    //cout << "cipher len: " << strlen(ciphertext) << endl;
    //cout << "crib len: " << strlen(crib) << endl;
    
    int i = 0;
    int j = 0;
    
    while(i < 6555 && i < strlen(ciphertext)) {
        //cout << "i: " << i << endl;
        //cout << "j: " << j << endl;
        while(j < 6555 && j < strlen(crib) && isMatch == true) {
            //cout << "i: " << i << endl;
            //cout << "j: " << j << endl;
            //cout << "key: " << key << endl;
            
//            //if new message, reset
            if(i < 6555 && ciphertext[i] == '\n') {
                //cout << "***NEW MESSAGE*************" << endl;
                //reset
                //cout << "reset" << endl;
                j = 0;
                for(int i = 0; i < 26; i++) {
                    key[i] = '.';
                }
            }
            
            //if both are blank
            if(i < 6555 && j < 6555 && ciphertext[i] == ' ' && crib[j] == ' '){
                i++;
                j++;
            }
            
            if(i < 6555 && isalpha(ciphertext[i])) {
                //cout << "i got here" << endl;
                //cout << "ciphertext[i]: " << ciphertext[i] << endl;
                //cout << "key mapping: " << key[tolower(ciphertext[i]) - 'a'] << endl;
                
                //mapping at index matches, the char is consistent with the key mapping so far
                if(i < 6555 && key[ciphertext[i] - 'a'] == toupper(crib[j])) {
                    //cout << "mapping at index matches" << endl;
                    i++;
                    j++;
                }
                
                //crib char already in the key as is the char already exists at another index
                else if(j < 6555 && strchr(key, toupper(crib[j])) != nullptr) {
                    //cout << "crib char already in key" << endl;
                    isMatch = false;
                    //move i to top of word
                    //make sure i remains in range
                    while(i < 6555 && i < strlen(ciphertext) &&!isblank(ciphertext[i])) {
                        //cout << "i: " << i << endl;
                        i++;
                    }
                }
                
                //mapping at index already exists so there is not a match, must move to the top of the next word now
                else if(i < 6555 && key[tolower(ciphertext[i]) - 'a'] != '.') {
                    //cout << "mapping at index already exists" << endl;
                    isMatch = false;
                    //move i to top of word
                    //make sure i remains in range
                    while(i < 6555 && i < strlen(ciphertext) && !isblank(ciphertext[i])) {
                        i++;
                    }
                }
                
                else if(i < 6555) { //make sure i is in range to avoid out of bounds
                    //cout << "successful mapping" << endl;
                    //successful mapping can occur!
                    //to access the correct index of the key array (aligned with alphabet so it is 26 characters):
                    //use the difference is ASCII values for the chars (as the spec FAQ permits), as in 'a' - 'a' = 0, 'b' - 'a' = 1, 'z' - 'a' = 25
                    //these indices correspond with the alphabetical key array
                    //to lower because 'A' and 'a' have different char values
                    //to upper because the key should have uppcase letters
                    key[tolower(ciphertext[i]) - 'a'] = toupper(crib[j]);
                    i++;
                    j++;
                }
                
                //if j is gets to the last index of the crib, it has successfully passed through the mapping without errors --> a match is found & key is made!
                if(j < 6555 && j == strlen(crib)) {
                    //cout << "FOUND" << endl;
                    //cout << "key: " << key << endl;
                    return true;
                }
            }
            
            else {
                while(i < 6555 && !isalpha(ciphertext[i])) {
                    //while not a letter, increment
                    i++;
                }
                
                //reset
                //cout << "reset" << endl;
                j = 0;
                for(int i = 0; i < 26; i++) {
                    key[i] = '.';
                }
                isMatch = true;
            }
        }
        i++;
        
        //reset
        //cout << "reset" << endl;
        j = 0;
        for(int i = 0; i < 26; i++) {
            key[i] = '.';
        }
        isMatch = true;
        
    }
    //cout << "NOT FOUND";
    return false;
}

bool decrypt(const char ciphertext[], const char crib[]) {
    //cout << "cipher: " << ciphertext << endl;
    //cout << "crib: " << crib << endl;
    
    //special case: crib is empty
    if(strlen(crib) == 0) {
        return false;
    }
    
    //create empty cstring for key
    char key[27] = "..........................";
    
    //simplify
    //declare new CStrings because the parameters are const's and cannot be altered
    char cipher[6555];
    char scrib[6555];
    
    //copy over
    strcpy(cipher, ciphertext);
    strcpy(scrib, crib);
    
    //simplify is a void function, but the arrays are automatically pass by reference so they are altered
    simplifyCipher(cipher);
    simplifyCrib(scrib);
    
    //check crib after it has been simplified to scrib for special cases
    //special case: crib is just fluff
    if(strlen(scrib) > 90) {
        return false;
    }
    //special case: if crib is just junk
    if(strlen(scrib) == 0) {
        return false;
    }
    
    //if crib cannot be found, return false
    if(findCrib(cipher, scrib, key) == false) {
        //cout << "NO MATCH";
        return false;
    }
    
    //build new array with key
    char text[6555];
    strcpy(text, ciphertext);
    
    for(int i = 0; i < strlen(ciphertext); i++) {
        //is letter
        if(i < 6555 && isalpha(ciphertext[i])) {
            //there is a key code for it (as in the char at the key is not the default '.'
            if(i < 6555 && key[tolower(ciphertext[i]) - 'a'] != '.') {
            text[i] = key[tolower(ciphertext[i]) - 'a'];
            }
            //no key code, just make it lower case (uppercase letters denote decrypted chars)
            else if(i < 6555){
                text[i] = tolower(ciphertext[i]);
            }
        }
    }
    
    //cout << "text: " << text << endl;
    cout << text << endl;
    return true;
    
    
}


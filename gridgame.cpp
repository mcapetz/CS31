//
//  main.cpp
//  project3
//
//  Created by Margaret Capetz on 10/23/21.
//

#include <iostream>
#include <string>
#include <cctype>
#include "grid.h"
#include <cassert>

using namespace std;


bool hasCorrectForm(string plan) {
    for(int i = 0; i < plan.size(); i++){

        //cout << "checking: " << plan.at(i) << endl;

        //if turn letter is not valid then return false
        if(!isdigit(plan.at(i))){
            //cout << "i got here: " << plan.at(i) << endl;
            if(plan.at(i) != 'l' && plan.at(i) != 'L' && plan.at(i) != 'r' && plan.at(i) != 'R') return false;
        }
            
        //digit
        //1 digit
        else if(isdigit(plan.at(i))) {
            //prevent out of bounds: if at the end of the string then return false
            if(i == plan.size() - 1) return false;
            
            //2 digits
            if(isdigit(plan.at(i+1))) {
                
                //prevent out of bounds
                if(i == plan.size() - 2) return false;
                
                //3 digits --> return false
                else if(isdigit(plan.at(i+2))) return false;
                else {
                    i += 2;
                    continue;
                }
            }
        }
        
    }
    return true;
}

bool inBounds(int r, int c) {
    if((1 <= r && r <= getRows()) && (1 <= c && c <= getCols())) {
        //cout << "inbounds true" << endl;
        return true;
    }
    else {
        //cout << "inbounds false: " << r << "," << c << endl;
        return false;
    }
}

bool validInputs(int r, int c, char dir) {
    //coordinate out of bounds
    if(!inBounds(r,c)) return false;
    //coordinate is a wall (non-empty)
    if(isWall(r,c)) return false;
    //invalid direction
    if(dir != 'N' && dir != 'n' && dir != 'S' && dir != 's' && dir != 'W' && dir != 'w' && dir != 'E' && dir != 'e') return false;
    return true;
    
}


int determineSafeDistance(int r, int c, char dir, int maxSteps) {
    
    //HANDLE ERROR CASES
    
    //invalid inputs
    if(!validInputs(r, c, dir)) return -1;
    //negative maximum steps
    if(maxSteps < 0) return -1;
    
    int realMax;
    
    //HANDLE EDGE CASES
    //north edge
    if((dir == 'N' || dir == 'n') && (r == 1)) return 0;
    //south edge
    if((dir == 'S' || dir == 's') && (r == getRows())) return 0;
    //west edge
    if((dir == 'W' || dir == 'w') && (c == 1)) return 0;
    //east edge
    if((dir == 'E' || dir == 'e') && (c == getCols())) return 0;
       
    //OTHER CASES
    realMax = 0;

    //while the point is within bounds & not a wall
    while(inBounds(r,c) && !(isWall(r,c))){
        switch(dir) {
            //north
            case 'N':
            case 'n':
                r--;
                break;
            //south
            case 'S':
            case 's':
                r++;
                break;
            //west
            case 'W':
            case 'w':
                c--;
                break;
            //east
            case 'E':
            case 'e':
                c++;
                break;
        }
        realMax++;
    }
    
    //cout << "i got here" << endl;
           
    if(maxSteps < realMax - 1) {
        //cout << "i got here 2" << endl;
        return maxSteps;
    }
    else {
        //cout << "i got here 3" << endl;
        //cout << realMax << endl;
        return realMax - 1;
    }
}

char convertToDir(char& currentDir, char turnLetter) {
    
    //convert turn letter to NSEW direction
    if(turnLetter == 'L' || turnLetter == 'l') {
        //left
        switch(currentDir) {
            //north
            case 'N':
            case 'n':
                currentDir = 'W';
                break;
            //south
            case 'S':
            case 's':
                currentDir = 'E';
                break;
            //west
            case 'W':
            case 'w':
                currentDir = 'S';
                break;
            //east
            case 'E':
            case 'e':
                currentDir = 'N';
                break;
        }
    }
    else {
        //right
        switch(currentDir) {
            //north
            case 'N':
            case 'n':
                currentDir = 'E';
                break;
            //south
            case 'S':
            case 's':
                currentDir = 'W';
                break;
            //west
            case 'W':
            case 'w':
                currentDir = 'N';
                break;
            //east
            case 'E':
            case 'e':
                currentDir = 'S';
                break;
        }
        
    }
    
    return currentDir;
}


int obeyPlan(int sr, int sc, int er, int ec, char dir, string plan, int& nsteps) {
    
    
    
    //HANDLE ERRORS
    // If (sr,sc) or (er,ec) are not valid empty grid positions or if dir is not a direction letter or if the plan string is not a plan, the function returns 2 and leaves nsteps unchanged.
    //return 2: (sr,sc) or (er,ec) are invalid || dir invalid || plan invalid --> nsteps unchanged
    if(!(validInputs(sr, sc, dir) && validInputs(er, ec, dir) && hasCorrectForm(plan))) return 2;
    
    
    // The function must not assume that nsteps has any particular value at the time this function is entered.
    nsteps = 0;
    
    
    //ATTEMPT TO OBEY PLAN
    //set movable car coordinates
    int r = sr;
    int c = sc;
    
    //for loop to read plan --> partial plans
    string temp = "";
    char currentDir = dir;
    char turnLetter;
    int steps = 0;
    for(int i = 0; i < plan.size(); i++) {
        //cout << "int i: " << i << endl;
        //cout << "coordinate: (" << r << "," << c << ")" << endl;
        
        //cout << "nsteps: " << nsteps << endl;
        //cout << "safe steps: " << determineSafeDistance(r,c, currentDir, steps) << endl;
        
        if(!isdigit(plan.at(i))) {
            //not a digit, end of partial plan
            if(temp == "") steps = 0;
            else steps = stoi(temp);
            turnLetter = plan.at(i);
            //cout << "partial plan: " << steps << " " << turnLetter << endl;
            
            //increment steps as much as safe (regardless of plan can be obeyable)
            nsteps += determineSafeDistance(r,c, currentDir, steps);
                        
            //if partial plan matches determineSafeDistance() --> increment r,c and continue

            //failure, partial plan cannot be obeyed
            if(determineSafeDistance(r,c, currentDir, steps) != steps) {
                
                //cout << "i got here" << endl;
                //cout << "current dir " << currentDir << endl;
                
                return 3;
            }
            
            
    
            //success, partial plan can be obeyed
            else {
                //increment r,c
                switch(currentDir) {
                    //north
                    case 'N':
                    case 'n':
                        r -= steps;
                        break;
                    //south
                    case 'S':
                    case 's':
                        r += steps;
                        break;
                    //west
                    case 'W':
                    case 'w':
                        c -= steps;
                        break;
                    //east
                    case 'E':
                    case 'e':
                        c += steps;
                        break;
                }
            }
            
            //reset vars
            steps = 0;
            temp = "";
            convertToDir(currentDir, turnLetter);
            continue;
        }
        else {
            //digit, add to temp
            temp += plan.at(i);
          
        }
    }
    
    //if (er,ec) matches (r,c) return 0 to indicate success
    if(r == er && c == ec) return 0;
    //else return 1 to indicate no errors
    else return 1;
    
    
    
    
}

int main(int argc, const char * argv[]) {
    
    //hasCorrectForm() test cases
//    string plan;
//    cin >> plan;
    assert(hasCorrectForm("6L3R1R1X") == false);
    assert(hasCorrectForm("6X3R1R1X") == false);
    assert(hasCorrectForm("5rL00L0R09R7L") == true);
    assert(hasCorrectForm("42l") == true);
    assert(hasCorrectForm("") == true);
    assert(hasCorrectForm("L2") == false);
    assert(hasCorrectForm("1Rx2L ") == false);
    assert(hasCorrectForm("1R+2L ") == false);
    assert(hasCorrectForm("N144") == false);
    assert(hasCorrectForm("w2+n3") == false);
    assert(hasCorrectForm("444L") == false);
    assert(hasCorrectForm("LLL") == true);
    assert(hasCorrectForm("LXL") == false);


    
     cerr << "correct form test passed" << endl;
//
    
    setSize(5,8);
    setWall(1,4);
    setWall(2,2);
    setWall(3,2);
    setWall(4,8);
    setWall(5,5);
    draw(4,1, 1,8);
    
//    setSize(3,4);
//                setWall(1,4);
//                setWall(2,2);
//                setWall(3,2);
    
//    setSize(2,5);
//    setWall(2,2);
//    draw(2,5, 1,3);
    
    //determineSafeDistance() test cases
    //cerr << "safe distance function test" << endl;
//
    //true cases
//    assert(determineSafeDistance(1,1 ,'N', 1) == 0);
//    assert(determineSafeDistance(1,1, 'S', 4) == 2);
//    assert(determineSafeDistance(2,3, 'S', 4) == 1);
//    assert(determineSafeDistance(1,1, 'E', 4) == 2);
//
//    //invalid cases
//    assert(determineSafeDistance(1,4 ,'N', 1) == -1);
//    assert(determineSafeDistance(1,1, 'S', -4) == -1);
//    assert(determineSafeDistance(2,5, 'S', 4) == -1);
//    assert(determineSafeDistance(1,1, 'X', 4) == -1);
//
//    //edge cases
//    assert(determineSafeDistance(1,1 ,'N', 1) == 0);
//    assert(determineSafeDistance(3,1, 'W', 4) == 0);
//    assert(determineSafeDistance(2,4, 'E', 4) == 0);
//    assert(determineSafeDistance(3,1, 'S', 4) == 0);
//
    //cerr << "All tests succeeded" << endl;
    
    
    
    //obeyPlan() test cases
    cerr << "obeyPlan() test cases" << endl;
    int nsteps = -888;
//    cout << obeyPlan(2,5, 1,3, 'w', "2r1r", nsteps) << endl;
//    cout << "nsteps: " << nsteps << endl;
//    cout << obeyPlan(2,5, 1,3, 'w', "4r1r", nsteps) << endl;
//    cout << "nsteps: " << nsteps << endl;
    
//    assert(obeyPlan(2,5, 1,3, 'w', "2r1r", nsteps) == 0);
//    assert(nsteps == 3);
//    assert(obeyPlan(2,5, 1,3, 'w', "4r1r", nsteps) == 3);
//    assert(nsteps == 2);
    
    
    //assert(obeyPlan(2,5, 1,3, 'w', "2r1r", nsteps) == 3);
    //0
    assert(obeyPlan(3,1, 3,4, 'N', "2R2R2L1L", nsteps) == 0);
    assert(nsteps == 7);
    assert(obeyPlan(4,1, 1,8, 'E', "6L3R1R", nsteps) == 0);
    assert(nsteps == 10);
    //1
    assert(obeyPlan(4,1, 1,8, 'E', "6L3R", nsteps) == 1); //doesn't make it to end coordinate
    assert(nsteps == 9);
    assert(obeyPlan(4,1, 1,8, 'E', "6L3R1R1L", nsteps) == 1); //doesn't make it to end coordinate
    assert(nsteps == 11);
    //2
    nsteps = -888;
    assert(obeyPlan(4,1, 1,8, 'X', "6L3R1R", nsteps) == 2); //invalid direction
    assert(nsteps == -888);
    assert(obeyPlan(4,1, 1,8, ' ', "6L3R1R", nsteps) == 2); //invalid direction
    assert(nsteps == -888);
    assert(obeyPlan(4,1, 1,8, 'E', "6L3R1R1X", nsteps) == 2); //invalid plan
    assert(nsteps == -888);
    assert(obeyPlan(10,1, 1,8, 'E', "6L3R1R1L", nsteps) == 2); //invalid start coordinate
    assert(nsteps == -888);
    assert(obeyPlan(4,1, 1,10, 'E', "6L3R1R1L", nsteps) == 2); //invalid end coordinate
    assert(nsteps == -888);
    //3
    assert(obeyPlan(4,1, 1,8, 'E', "6L3R2R", nsteps) == 3); //car goes off grid
    assert(nsteps == 10);
    assert(obeyPlan(4,1, 1,8, 'E', "7L3R2R", nsteps) == 3); //car hits wall
    assert(nsteps == 6);
    
    //other
    assert(obeyPlan(4,1, 4,1, 'E', "", nsteps) == 0); //car doesn't move
    assert(nsteps == 0);
   

    cout << "all test cases succeeded" << endl;
    
    return 0;
}

//checklist for returns for obey plan
//    return 0; //success, cars ends up at (er,ec)
//    return 1; //success otherwise, car does not end up at (er,ec) but does not run into errors
//    return 2; //invalid starting inputs
//    return 3; //valid starting inputs, car couldn't make it to (er,ec) --> nsteps = max steps until error

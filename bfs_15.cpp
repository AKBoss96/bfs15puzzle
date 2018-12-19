	#include <iostream>
	#include <string>
	#include <vector>
	#include <map>
	#include<stack>
	#include <queue>
	#include <cstdlib>
	#include<chrono>

	using namespace std;
	using namespace std::chrono; //for time-related operations
	int expandCount = 0, blank_pos;

	const string goalState = "123456789ABCDEF0"; //the desired goal state

	struct State{       
		string order; //arrangement of tiles
		string moves; //set of directions to move in
	};

	bool checkGoalState(State a){ 				//testing for goal state
		return (a.order.compare(goalState)==0);
	}

	string performMove(string order, int x, int y){ //going from current state to next state
		string newState(order);
		string temp = newState.substr(x,1); 
		newState[x] = newState[y];
		newState[y] = temp[0];
		return newState;
	}

	State BreadthFirstSearch(State startState){
		queue<State> fringe; //next nodes to be expanded
		map<string,int> visited; //visited nodes
		fringe.push(startState); //push start state into queue
		while(fringe.size()>0){ 
			State curState = fringe.front(); //considers first fringe node as the current state
			fringe.pop(); //pop current state from queue
			expandCount += 1;
			visited[curState.order] = 1;
			vector<State> nextStates;
		blank_pos = curState.order.find("0"); //identifying the position of empty tile
		if(blank_pos > 3){ //condition for UP move
			State newState;
			newState.order = performMove(curState.order, blank_pos, blank_pos-4);
			newState.moves = curState.moves;
			newState.moves += 'U'; 
			nextStates.push_back(newState);
		}
		if (blank_pos < 12){ //condition for DOWN move
			State newState;
			newState.order = performMove(curState.order, blank_pos, blank_pos+4);
			newState.moves = curState.moves;
			newState.moves += 'D';
			nextStates.push_back(newState);
		}
		if (blank_pos%4 < 3){ //condition for RIGHT move
			State newState;
			newState.order = performMove(curState.order, blank_pos, blank_pos+1);
			newState.moves = curState.moves;
			newState.moves += 'R';
			nextStates.push_back(newState);		
		}
		if (blank_pos%4 > 0){ //condition for LEFT move
			State newState;
			newState.order = performMove(curState.order, blank_pos, blank_pos-1);
			newState.moves = curState.moves;
			newState.moves += 'L';
			nextStates.push_back(newState);		
		}
			for(int i = 0; i < nextStates.size(); i++){
				if (checkGoalState(nextStates[i])){ //checking whether child nodes contain the goal state
					return nextStates[i];
				}
				if (visited.find(nextStates[i].order) != visited.end()){
					continue;
				}
				fringe.push(nextStates[i]);
			}
		}
	}

	bool checkSolvable(State startState) //to check if a given input has a solution
	{
		int inv_count = 0; //to count the number of inversions
    	for (int i = 0; i < 15; i++) 
	    { 
	        for (int j = i + 1; j < 16; j++) 
	        { 
	        	//value of i < value of j, but value at position i is greater than that at position j
	            if (startState.order[j]!='0' && startState.order[i]!='0' && (startState.order[i] > startState.order[j])) 
	            	inv_count++; 
	        } 
	    }
	    
	    int row = 4 - (blank_pos/4); //identifying the row in which the empty tile is present
	    if (row & 1) 	//using bitwise to find polarity
	    	return !(inv_count & 1); 
	    else
	        return inv_count & 1; 
	} 


	int main(int argc, char* argv[]){ //main function
		State startState;
		startState.order = "";
		startState.order = argv[1]; //initial configuration is given as first command-line argument
        blank_pos = startState.order.find("0");
        
        if(!checkSolvable(startState)) 
		{
			cout << "Solution cannot be found" << endl; //unsolvable initial configuration
			return 1;
		}

		time_point<system_clock> startTime = system_clock::now(); //timestep before BFS starts
		State searchResult = BreadthFirstSearch(startState); //resulting state after BFS
		time_point<system_clock> endTime = system_clock::now(); //timestep after BFS returns 
		std::chrono::duration<double> runTime = endTime - startTime; //duration in seconds

		cout << "Moves: " << searchResult.moves << endl; //solution
		cout << "Number of nodes expanded: " << expandCount << endl; //metric for expansion of fringe
		cout << "Time taken: " << runTime.count()*1000 << " milliseconds" << endl; //duration in milliseconds
		cout << "Memory used: " << expandCount*(16+searchResult.moves.length()) << " bytes" << endl; //memory usage

		return 0;
	}

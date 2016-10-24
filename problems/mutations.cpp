/*
 * A gene string can be represented by an 8-character long string with, with choices from "A","C","G","T"
 * Suppose we need to investigate about a mutation from start to end, where one mutation is defined as 
 * ONE Single Character changed in the gene string.
 *
 * Also there is a given gene bank which records all the valid gene mutations. A gene must be in the bank to
 * make it a valid gene string. Now given 3 things, start, end and bank, your task is to determine what is the 
 * minimum number of mutations needed to mutate from "start" to "end". If there is no such mutation, then return
 * -1.
 *
 *  BFS Based : One mutate character and push it to key based on entry in dictionary. (Note, therafter this entry is removed)
 */
#include<iostream>
#include<string>
#include<vector>
#include<unordered_set>
#include<queue>

using namespace std;

void generate_mutations(string seq, unordered_set<string>& bank, queue<string>& bfsq) {

    char vchars[] = { 'A', 'C', 'T', 'G'};

    for (int i = 0; i < 8; i++) {
        auto str = seq;
        for (int j = 0; j < 4; j++) {
            str[i] = vchars[j];
            if (bank.find(str) != bank.end()) {
                bfsq.push(str);
                bank.erase(str);
            }  
        }
    }
}

int bfs(string seq, string end, unordered_set<string>& bank) {

    int level = 0;
    bool found = false;
    queue<string> p, q;

    p.push(seq);

    while (!found && (p.size() || q.size())) {

        while (!p.empty()) {
            auto next = p.front();
            if (next == end) {
                found = true;
                break;
            }
            p.pop();
            generate_mutations(next, bank, q);
        } 

        if (found)
           return level;

        level++;

        while (!q.empty()) {
            auto next = q.front();
            if (next == end) {
                found = true;
                break;
            }
            q.pop();
            generate_mutations(next, bank, p);
        } 

        if (found)
           return level;
      
        level++;
    }

    return -1;
}

int main(void) {
    unordered_set<string> bank1 = { "ACTGACTG", "ACTGACTA", "ACTGACCC", "ACTGAAAT"}; 
    string start1("ACTGAAAA");
    string end1("ACTGAAAT");
    cout << "Number of mutations : " << bfs(start1, end1, bank1) << endl;

    unordered_set<string> bank2 = { "AACCGGTA", "AACCGCTA", "AAACGGTA"};
    string start2("AACCGGTT");
    string end2("AAACGGTA");
    cout << "Number of mutations : " << bfs(start2, end2, bank2) << endl;

    unordered_set<string> bank3 = { "AAAACCCC", "AAACCCCC", "AACCCCCC"};
    string start3("AAAAACCC");
    string end3("AACCCCCC");
    cout << "Number of mutations : " << bfs(start3, end3, bank3) << endl;

    return 0;
}

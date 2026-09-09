#include<iostream>
#include<string>

using namespace std;
class SecurityEvent{
    protected:
    string SourceIP;
    int severnity;
    public:

    SecurityEvent(string SourceIP,int severnity){
        this->SourceIP = SourceIP;
        this->severnity = severnity;

    }

    virtual void display() = 0;
    virtual ~SecurityEvent() {}

};

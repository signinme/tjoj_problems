#include <iostream>
#include <stack>
#include <string.h>
using namespace std;

int postOrder[50];
typedef struct node{
 int c;
 bool flag;
}ElemType;
stack<ElemType> sta;
int main(){
 int n;
 char op[20];
 ElemType e;
 int c,cnt=0;
 cin>>n;
 for (int i=0;i<2*n;i++){
  cin>>op;
  if (strcmp(op,"push")==0){
   cin>>c;
   sta.push({c,0});
  }else if (strcmp(op,"pop")==0){
   e=sta.top() ;sta.pop();
   if (e.flag ==0){
    e.flag =1;
    sta.push(e);
   }else {
    //cout<<e.c<<" ";
    postOrder[cnt++]=e.c;
    if (!sta.empty()){
     e=sta.top();sta.pop();
     while (!sta.empty()&&e.flag ==1){
      //cout<<e.c;
      postOrder[cnt++]=e.c;
      e=sta.top() ;sta.pop();
     }
     if (e.flag==0 ){
      e.flag =1;
      sta.push(e); 
     }
     
    }
   }
  }
   
 }
 while (!sta.empty()) {
  e = sta.top();
  //cout << e.c;
  postOrder[cnt++]=e.c;
  sta.pop();
 }
 for (int j=0;j<cnt;j++){
  cout<<postOrder[j];
  if (j==cnt-1) cout<<endl;
  else cout<<" ";
 }
// system("pause");
} 

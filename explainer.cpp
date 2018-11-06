#include<iostream>
#include <string>
using namespace std;
#include <vector>
#include<cmath>
#include<list>
vector<double> V_d;
vector<string> V_s;
vector<string> V_f;
list<double> linshi_n;
list<string> linshi_s;
string run(string code){
double x1,x2;
int index,k=0;
string onstr(""),symbol,s,s2,s1;
vector<double> L_d;
vector<string> L_s;
vector<string> L_f;
if(code[0]==0x61){
			onstr="";
			k++;
			index=0;
			while(code[k]!=0x0a){
				if(code[k]==0x20){
					if(index==0){
						symbol=onstr;
						index=1;
					}
					else{
						if(symbol=="n"){
							L_d.push_back(stod(onstr));
						}
						else if(symbol=="s"){
							L_s.push_back(onstr);
						}
						else{
							index=stoi(onstr);
							if(symbol=="d"){
							L_d.push_back(V_d[index]);
							}
							else if(symbol=="t"){
							L_s.push_back(V_s[index]);
							}
							index=0;
						}
				}
			}
				else{
				onstr+=code[k];
			}
				k++;
			}
}
while(k<code.length()){
	if(code[k]!=0x20&&code[k]!=0x0a){
		onstr+=code[k];
	}
	else{
		if(onstr=="0"){
		onstr="";
		k++;
		while(code[k]!=0x20){
			onstr+=code[k];
			k++;
		}
		index=stoi(onstr);
		k++;
		onstr=code[k];
		if(onstr=="0"){
			cin>>*(V_d.begin()+index);
		}
		else if(onstr=="1"){
			cin>>onstr;
			*(V_s.begin()+index)=onstr;
		}
		k++;
	}
	else if(onstr=="1"){
		k++;
		onstr="";
		while(code[k]!=0x0a){
			onstr+=code[k];
			k++;
		}
		cout<<onstr<<"\n";
	}
	else if(onstr=="2"){
		k++;
		if(code[k]==0x30){
			onstr="";
			k++;
			while(code[k]!=0x0a){
				onstr+=code[k];
				k++;
			}
			V_d.push_back(stod(onstr));
		}
		else if(code[k]==0x31){
			onstr="";
			k+=2;
			while(code[k]!=0x0a){
				onstr+=code[k];
				k++;
			}
			V_s.push_back(onstr);
		}
	}
	else if(onstr=="3"){
			if(!linshi_n.empty()){
				cout<<linshi_n.back()<<"\n";
				linshi_n.clear();
			}
			else if(!linshi_s.empty()){
				cout<<linshi_s.back()<<"\n";
				linshi_s.clear();
			}
	}
	else if(onstr=="4"){
		k++;
		onstr="";
		while(code[k]!=0x20){
			onstr+=code[k];
			k++;
		}
		index=stoi(onstr);
		k++;
		if(code[k]==0x30){
			onstr="";
			k+=2;
			while(code[k]!=0x0a){
				onstr+=code[k];
				k++;
			}
			if(onstr=="r"){
				*(V_d.begin()+index)=linshi_n.back();
				linshi_n.clear();
			}
			else{
				*(V_d.begin()+index)=stod(onstr);
			}
		}
		else if(code[k]==0x31){
			k+=2;
			onstr="";
			while(code[k]!=0x0a){
				onstr+=code[k];
				k++;
			}
			if(onstr!="r"){
			*(V_s.begin()+index)=onstr;
			}
			else{
				*(V_s.begin()+index)=linshi_s.back();
				linshi_s.clear();
			}
		}
	}
	else if(onstr=="5"){
		onstr="";
		k++;
	while(k<code.length()){
		if(onstr=="\\0"){
			break;
		}
		else if(code[k]==0x20){
			if(0x30<=onstr[0]&&onstr[0]<=0x39){
				linshi_n.push_back(stod(onstr));
			}
			else if(onstr[0]==0x22){
				s="";
				index=1;
				while(index<onstr.length()){
					s+=onstr[index];
					index++;
				}
				linshi_s.push_back(s);
			}
			else if(onstr[0]==0x7e){
				s2=linshi_s.back();
				linshi_s.pop_back();
				s1=linshi_s.back();
				linshi_s.pop_back();
				linshi_s.push_back(s1+s2);
			}
			else if(onstr[0]==0x2a||onstr[0]==0x21||onstr[0]==0x2b||onstr[0]==0x2d||onstr[0]==0x2f||(0x3c<=onstr[0]&&onstr[0]<=0x3e)||onstr[0]==0x5e||onstr[0]==0x7c||onstr[0]==0x26){
				x2=linshi_n.back();
				linshi_n.pop_back();
				x1=linshi_n.back();
				linshi_n.pop_back();
				if(onstr=="+"){
					linshi_n.push_back(x1+x2);
				}
				else if(onstr=="-"){
					linshi_n.push_back(x1-x2);
				}
				else if(onstr=="*"){
					linshi_n.push_back(x1*x2);
				}
				else if(onstr=="/"){
					linshi_n.push_back(x1/x2);
				}
				else if(onstr==">"){
					linshi_n.push_back(x1>x2);
				}
				else if(onstr=="<"){
					linshi_n.push_back(x1<x2);
				}
				else if(onstr=="="){
					linshi_n.push_back(x1==x2);
				}
				else if(onstr=="!"){
					linshi_n.push_back(x1!=x2);
				}
				else if(onstr=="|"){
					linshi_n.push_back(x1||x2);
				}
				else if(onstr=="&"){
					linshi_n.push_back(x1&&x2);
				}
			}
			else{
				if(onstr=="d"){
					k++;
					onstr="";
					while(k<code.length()){
						if(code[k]==0x20||code[k]==0x0a){
							break;
						}
						onstr+=code[k];
						k++;
					}
					linshi_n.push_back(V_d[index]);
				}
				else if(onstr=="s"){
					k++;
					onstr="";
					while(k<code.length()){
						if(code[k]==0x20||code[k]==0x0a){
							break;
						}
						onstr+=code[k];
						k++;
					}
					index=stoi(onstr);
					linshi_s.push_back(V_s[index]);
				}
				if(onstr=="ld"){
					k++;
					onstr="";
					while(k<code.length()){
						if(code[k]==0x20||code[k]==0x0a){
							break;
						}
						onstr+=code[k];
						k++;
					}
					linshi_n.push_back(L_d[index]);
				}
				else if(onstr=="ls"){
					k++;
					onstr="";
					while(k<code.length()){
						if(code[k]==0x20||code[k]==0x0a){
							break;
						}
						onstr+=code[k];
						k++;
					}
					index=stoi(onstr);
					linshi_s.push_back(L_s[index]);
				}
			}
			onstr="";
		}
		else{
			onstr+=code[k];
		}
		k++;
	}
	}
	else if(onstr=="6"){
		k++;
		onstr="";
		string rep_code("");
		index=1;
		while(k<code.length()){
			if(code[k-1]==0x0a){
				if(code[k]==0x37){index--;}
				else if(code[k]==0x36){index++;}
			}
			if(index==0){break;}
			rep_code+=code[k];
			k++;
		}
		while(linshi_n.back()!=0){
			linshi_n.clear();
			run(rep_code);
		}
		linshi_n.clear();
}
	else if(onstr=="9"){
		if(linshi_n.back()==0){
			linshi_n.clear();
			k++;
			index=1;
			while(k<code.length()){
				if(code[k-1]==0x0a){
					if(code[k]==0x39){
						index++;
					}
					else if(code[k]==0x38){
						index--;
					}
				}
				if(index==0){
					break;
				}
				k++;
			}
	}
	}
	else if(onstr=="10"){
		k++;
		if(code[k]==0x30){
			onstr="";
			k++;
			while(code[k]!=0x0a){
				onstr+=code[k];
				k++;
			}
			L_d.push_back(stod(onstr));
		}
		else if(code[k]==0x31){
			onstr="";
			k+=2;
			while(code[k]!=0x0a){
				onstr+=code[k];
				k++;
			}
			L_s.push_back(onstr);
		}
	}
	else if(onstr=="11"){
		k++;
		onstr="";
		while(code[k]!=0x20){
			onstr+=code[k];
			k++;
		}
		index=stoi(onstr);
		k++;
		if(code[k]==0x30){
			onstr="";
			k+=2;
			while(code[k]!=0x0a){
				onstr+=code[k];
				k++;
			}
			if(onstr=="r"){
				*(L_d.begin()+index)=linshi_n.back();
				linshi_n.clear();
			}
			else{
				*(L_d.begin()+index)=stod(onstr);
			}
		}
		else if(code[k]==0x31){
			k+=2;
			onstr="";
			while(code[k]!=0x0a){
				onstr+=code[k];
				k++;
			}
			if(onstr!="r"){
			*(L_s.begin()+index)=onstr;
			}
			else{
				*(L_s.begin()+index)=linshi_s.back();
				linshi_s.clear();
			}
		}
	}
	else if(onstr=="b"){
		k++;
		index=1;
		onstr="";
		while(k<code.length()){
			if(code[k]==0x62){
				index+=1;
			}
			else if(code[k]==0x66){
				index-=1;
			}
			if(index==0){
				break;
			}
			onstr+=code[k];
			k++;
		}
		V_f.push_back(onstr);
		k++;
	}
	else if(onstr=="r"){
		k++;
		onstr="";
		while(code[k]!=0x20){
			onstr+=code[k];
			k++;
		}
		k++;
		if(code[k]==0x30){
			linshi_n.push_back(stod(onstr));
		}
		else if(code[k]==0x31){
			linshi_s.push_back(onstr);
		}
		k++;
	}
	onstr="";
}
	k++;
}
return "";
}
int main () {
cout<<fixed;
string p,sss;
{
cout<<"请输入打开的文件路径\n";
cin>>p;
FILE * pFile;
long lSize;
char * buffer;
size_t result;
pFile = fopen ( p.c_str() , "rb" );//希诺：C:\Users\Administrator\Desktop\test.txt
//我：/Users/boatbridge/Desktop/test.mfc
if (pFile==NULL) {fputs ("File error",stderr); exit (1);}
// obtain file size:
fseek (pFile , 0 , SEEK_END);
lSize = ftell (pFile);
rewind (pFile);
// allocate memory to contain the whole file:
buffer = (char*) malloc (sizeof(char)*lSize);
if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}
// copy the file into the buffer:
result = fread (buffer,1,lSize,pFile);
if (result != lSize) {fputs ("Reading error",stderr); exit (3);}
/* the whole file is now loaded in the memory buffer. */
// terminate
sss.assign(buffer,result);
fclose (pFile);
free (buffer);}
run(sss);
return 0;
}

#include<iostream>
#include<vector>
#include<map>
#include<list>
#include<iterator>
#include<fstream>
using namespace std;
int i,k,main_i=0,err=0,ori;
double x1,x2;
bool state=false,last_if_state=false,last_rep_state=false;
    string s_beh="",s,s1,s2,last_rep_con;
    list<char> stk;
    map<char,int> op;//利用map来实现运算符对应其优先级
   	string output(""),onstr(""),general("");
	list<double> linshi_n;
	list<string> linshi_s;
	map<string,int> M_s,M_f,M_d;//索引
	map<string,int> V_name;//类型
	vector<string> V_s;
	vector<double> V_d;
string getexp(string s_mid)
{
	op['(']=0;
    op[')']=0;
    op['+']=4;
    op['-']=4;
    op['*']=5;
    op['/']=5;
    op['<']=3;
    op['>']=3;
    op['=']=3;
    op['!']=3;
    op['~']=4;
    op['&']=2;
    op['|']=2;
	s_beh="";
	i=0;
    while(i<s_mid.length())
    {
        if(op.count(s_mid[i]))//判断该元素是否为运算符
        {
        	s_beh+=" ";
            if(s_mid[i]==')')//情况2
            {
                while(stk.back()!='(')
                {
                    s_beh+=stk.back();
                    s_beh+=" ";
                    stk.pop_back();
                }
                stk.pop_back();
            }
            else if(stk.empty()||s_mid[i]=='('||op[s_mid[i]]>op[stk.back()])//情况1、情况3
            {
                stk.push_back(s_mid[i]);
            }
            else if(op[s_mid[i]]<=op[stk.back()])//情况3
            {
                while(op[s_mid[i]]<=op[stk.back()]&&(!stk.empty()))
                {
                    s_beh+=stk.back();
                    s_beh+=" ";
                    stk.pop_back();
                    if(stk.empty()) break;
                }
                stk.push_back(s_mid[i]);
            }
        }
        else
        {
            s_beh+=s_mid[i];
        }
        i++;
        if(i==s_mid.length())//当中缀表达式输出完成，所有元素出栈
        {
            while(!stk.empty())
            {
            	s_beh+=" ";
                s_beh+=stk.back();
                stk.pop_back();
            }
            break;
        }
    }
    i=0;
    s_mid="";
    onstr="";
    while(i<s_beh.length()){
    	if(s_beh[i]==0x20){
    		if(onstr!=""){
    		s_mid+=onstr;
    		s_mid+=" ";
    		onstr="";
    		}
    	}
    	else{
    		onstr+=s_beh[i];
    	}
    	i++;
    }
    s_mid+=onstr;
    s_mid+=" \\0";
    return s_mid;
}
string replaceexp(string exp){
	onstr="";
	i=0;
	exp+=" ";
	s="";
	while(i<exp.length()){
		if(exp[i]==0x20){
			if(onstr[0]==0x5c){
				s+="\\0";
				break;
			}
			else if(onstr[0]<0x30||onstr[0]>0x39){
				if(M_d.find(onstr)!=M_d.end()&&!M_d.empty()){
					s+="d "+to_string(M_d[onstr])+" ";
				}
				else if(M_s.find(onstr)!=M_s.end()&&!M_s.empty()){
					s+="s "+to_string(M_s[onstr])+" ";
				}
				else{
					s+=onstr+" ";
				}
			}
			else{
				s+=onstr+" ";
			}
			onstr="";
		}
		else{
		onstr+=exp[i];
	}
		i++;
	}
	return s;
}
string getcode(string path){
FILE * pFile;
string sss;
long lSize;
char * buffer;
size_t result;
pFile = fopen ( path.c_str() , "rb" );//希诺：C:\Users\Administrator\Desktop\test.txt
//我：/Users/boatbridge/Desktop/test.mfs
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
free (buffer);
return sss;
}
void calculate(string exp){
	i=0;
	onstr="";
	state=false;
	exp+=" ";
	while(i<exp.length()){
		if(onstr=="\\0"){
			break;
		}
		else if(onstr=="true"){
			linshi_n.push_back(1);
		}
		else if(onstr=="false"){
			linshi_n.push_back(0);
		}
		else if(exp[i]==0x20){
			if(0x30<=onstr[0]&&onstr[0]<=0x39){
				linshi_n.push_back(stod(onstr));
			}
			else if(onstr[0]==0x22){
				s="",k=1;
				while(k<onstr.length()){
					s+=onstr[k];
					k++;
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
			else if(onstr[0]==0x2a||onstr[0]==0x21||onstr[0]==0x2b||onstr[0]==0x2d||onstr[0]==0x2f||(0x3c<=onstr[0]&&onstr[0]<=0x3e)||onstr[0]==0x5e||onstr[0]==0x7c||onstr=="≥"||onstr=="≤"){
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
			}
			else{
				state=true;
				if(M_d.find(onstr)!=M_d.end()){
					linshi_n.push_back(V_d[M_d[onstr]]);
				}
				else if(M_s.find(onstr)!=M_s.end()){
					linshi_s.push_back(V_s[M_s[onstr]]);
				}
				else{
					err++;
					cout<<main_i+1<<"：错误：变量<"<<onstr<<">未定义\n";
					return;
				}
			}
			onstr="";
		}
		else{
			onstr+=exp[i];
		}
		i++;
	}
	if(linshi_n.empty()==linshi_s.empty()){
		err++;
		cout<<main_i+1<<"：错误：不同的数据类型无法进行计算\n";
	}
}
string compiler(string text){
	i=0;
	onstr="";
	while(i<text.length()){
		if(text[i]!=0x0a){
			general+=text[i];
		}
		i++;
	}//处理换行
	i=0;
	general+=";";
	vector<string> code;
	while(i<general.length()){
		if(general[i]==0x3b){
			code.push_back(onstr+" ");
			onstr="";
		}
		else{
			onstr+=general[i];
		}
		i++;
	}
	int k=0;
	onstr="";
	while(main_i<code.size()){
		vector<string> oncode;
		while(k<code[main_i].length()){
			if(code[main_i][k]==0x20){
				oncode.push_back(onstr);
				onstr="";
			}
			else{
				onstr+=code[main_i][k];
			}
			k++;
		}
		if(oncode[0]=="def"){
			if(V_name.find(oncode[1])!=V_name.end()&&!V_name.empty()){
				cout<<main_i+1<<"：错误：变量<"<<oncode[1]<<">已定义\n";
				return "";
			}
			calculate(getexp(oncode[2]));
			if(err>0){
				return "";
			}
			if(!linshi_n.empty()){
				output+="2 0 "+to_string(linshi_n.back())+"\n";
				M_d[oncode[1]]=V_d.size();
				V_d.push_back(linshi_n.back());
				linshi_n.clear();
				V_name[oncode[1]]=0;
			}
			else if(!linshi_s.empty()){
				output+="2 1 "+linshi_s.back()+"\n";
				M_s[oncode[1]]=V_s.size();
				V_s.push_back(linshi_s.back());
				linshi_s.clear();
				V_name[oncode[1]]=1;
			}
		}
		else if(oncode[0]=="let"){
			if(V_name.find(oncode[1])==V_name.end()){
				cout<<main_i+1<<"：错误：变量<"<<oncode[1]<<">未定义\n";
			}
			calculate(getexp(oncode[2]));
			if(err>0){
				return "";
			}
			onstr=replaceexp(getexp(oncode[2]));
			if(!linshi_n.empty()){
				if(state==true){
					output+="5 "+onstr+"\n4 "+to_string(M_d[oncode[1]])+" 0 r\n";
				}
				else{
					output+="4 "+to_string(M_d[oncode[1]])+" 0 "+to_string(linshi_n.back())+"\n";
				}
				*(V_d.begin()+M_d[oncode[1]])=linshi_n.back();
				linshi_n.clear();
			}
			else if(!linshi_s.empty()){
				if(state==true){
					output+="5 "+onstr+"\n4 "+to_string(M_s[oncode[1]])+" 1 r\n";
				}
				else{
					output+="4 "+to_string(M_s[oncode[1]])+" 0 "+linshi_s.back()+"\n";
				}
				*(V_s.begin()+M_s[oncode[1]])=linshi_s.back();
				linshi_s.clear();
			}
		}
		else if(oncode[0]=="out"){
			calculate(getexp(oncode[2]));
			if(err>0){
				return "";
			}
			if(!linshi_s.empty()){
				onstr=linshi_s.back();
				linshi_s.clear();
			}
			else if(!linshi_n.empty()){
				onstr=to_string(linshi_n.back());
				linshi_n.clear();
			}
			if(oncode[1]=="console"){
				if(state==true){
					output+="5 "+replaceexp(getexp(oncode[2]))+"\n3\n";
				}
				else{
					output+="1 "+onstr+"\n";
				}
			}
			else{
				cout<<main_i+1<<"：错误：不支持输出目标<"<<oncode[1]<<">\n";
				return "";
			}
		}
		else if(oncode[0]=="if"){
			calculate(getexp(oncode[1]));
			if(err>0){
				return "";
			}
				ori=main_i;
				main_i++;
				while(main_i<code.size()){
					onstr="";
					i=0;
					k=1;
					while(code[main_i][i]!=0x20&&code[main_i][i]!=0x0a){
						onstr+=code[main_i][i];
						i++;
					}
					if(onstr=="endif"){
						k-=1;
					}
					else if(onstr=="if"){
						k+=1;
					}
					if(k==0){
						break;
					}
					main_i++;
				}
				if(k!=0){
					cout<<main_i+1<<"：错误：if与endif的个数不匹配\n";
					return "";
				}
				if(linshi_n.back()!=0){
					main_i=ori;
					if(state==true){
						last_if_state=true;
						output+="5 "+replaceexp(getexp(oncode[1]))+"\n9\n";
					}
				}
				else{
					if(state==true){
						main_i=ori;
						last_if_state=true;
						output+="5 "+replaceexp(getexp(oncode[1]))+"\n9\n";
					}
				}
		}
		else if(oncode[0]=="endif"){
			if(last_if_state==true){
				output+="8\n";
			}
			else{
				last_if_state=false;
			}
		}
		else if(oncode[0]=="endrep"){
			if(last_rep_state==true){
				output+="5 "+last_rep_con+"\n7\n";
			}
		}
		else if(oncode[0]=="rep"){
			calculate(getexp(oncode[1]));
			if(err>0){
				return "";
			}
				ori=main_i;
				main_i++;
				while(main_i<code.size()){
					onstr="";
					i=0;
					k=1;
					while(code[main_i][i]!=0x20&&code[main_i][i]!=0x0a){
						onstr+=code[main_i][i];
						i++;
					}
					if(onstr=="endrep"){
						k-=1;
					}
					else if(onstr=="rep"){
						k+=1;
					}
					if(k==0){
						break;
					}
					main_i++;
				}
				if(k!=0){
					cout<<main_i+1<<"：错误：rep与endrep的个数不匹配\n";
					return "";
				}
				if(linshi_n.back()!=0){
					main_i=ori;
					last_rep_con=replaceexp(getexp(oncode[1]));
					last_rep_state=true;
					if(state==true){
						output+="5 "+last_rep_con+"\n6\n";
					}
				}
		}
		else{
			cout<<main_i+1<<"：错误：未知的指令<"<<oncode[0]<<">\n";
			return "";
		}
		onstr="";
		k=0;
		main_i++;
	}
	return output;
}
void writeCode(string code,string outname){
    ofstream fout(outname);     //创建一个data.txt的文件
    fout<<code;
    fout.close();                  //关闭文件
    cout<<"编译成功！\n";
}
int main(){
	cout<<fixed;
	string p,name;
	cout<<"请输入打开的文件路径\n";
	cin>>p;
	cout<<"请输入输出文件路径(附带文件名)\n";
	cin>>name;
	writeCode(compiler(getcode(p)),name);
	return 0;
}

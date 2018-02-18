#include<bits/stdc++.h>
using namespace std;

string hex_to_bin(char a)
{
    switch(a)
    {
        case '0':return "0000";
        case '1':return "0001";
        case '2':return "0010";
        case '3':return "0011";
        case '4':return "0100";
        case '5':return "0101";
        case '6':return "0110";
        case '7':return "0111";
        case '8':return "1000";
        case '9':return "1001";
        case 'A':return "1010";
        case 'B':return "1011";
        case 'C':return "1100";
        case 'D':return "1101";
        case 'E':return "1110";
        case 'F':return "1111";
    }
}


map<string,string> bin_to_hex;

int pc1[]={57,49,41,33,25,17,9,1,58,50,42,34,26,18,10,2,59,51,43,35,27,19,11,3,60,52,44,36,63,55,47,39,31,23,15,7,62,54,46,38,30,22,14,6,61,53,45,37,29,21,13,5,28,20,12,4};

int pc2[]={14,17,11,24,1,5,3,28,15,6,21,10,23,19,12,4,26,8,16,7,27,20,13,2,41,52,31,37,47,55,30,40,51,45,33,48,44,49,39,56,34,53,46,42,50,36,29,32};

int l_shifts[16]={1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};

int ip[64]={58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,62,54,46,38,30,22,14,6,64,56,48,40,32,24,16,8,57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7};

int expp[48]={32,1,2,3,4,5,4,5,6,7,8,9,8,9,10,11,12,13,12,13,14,15,16,17,16,17,18,19,20,21,20,21,22,23,24,25,24,25,26,27,28,29,28,29,30,31,32,1};

int s1[4][16]={{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},{0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},{4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},{15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}};

int s2[4][16]={{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},{3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},{0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},{13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}};

int s3[4][16]={{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},{13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},{13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},{1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}};

int s4[4][16]={{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},{13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},{10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},{3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}};

int s5[4][16]={{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},{14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},{4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},{11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}};

int s6[4][16]={{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},{10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},{9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},{4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}};

int s7[4][16]={{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},{13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},{1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},{6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}};

int s8[4][16]={{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},{1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},{7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},{2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}};


int permute[]={16,7,20,21,29,12,28,17,1,15,23,26,5,18,31,10,2,8,24,14,32,27,3,9,19,13,30,6,22,11,4,25};


string left_shift_this(string key)
{
	char key_first=key[0];
	int siz=key.length();
	for(int i=1;i<siz;i++)
	{
		key[i-1]=key[i];
	}
	key[key.length()-1]=key_first;
	return key;
}


string b_box(string key,int val)
{
	int row= (key[5]-'0')+(key[0]-'0')*2;
	int column= (key[4]-'0')+(key[3]-'0')*2+(key[2]-'0')*4+(key[1]-'0')*8;

	

	int ans;
	switch(val)
	{
		case 1:{ans=s1[row][column];
			break;}
		case 2:{ans=s2[row][column];
			break;}
		case 3:{ans=s3[row][column];
			break;}
		case 4:{ans=s4[row][column];
			break;}
		case 5:{ans=s5[row][column];
			break;}
		case 6:{ans=s6[row][column];
			break;}
		case 7:{ans=s7[row][column];
			break;}
		case 8:{ans=s8[row][column];
			break;}
	}

	

	string bin_ans="";

	while(ans)
	{
		int y=ans%2;
		bin_ans+=('0'+y);
		ans/=2;
	}

	reverse(bin_ans.begin(),bin_ans.end());

	int zno=4-bin_ans.length();
	string zero_str="";
	for(int i=0;i<zno;i++)
	{
		zero_str+='0';
	}
	bin_ans=zero_str+bin_ans;
	return  bin_ans;
}

int main()
{
    string key,p_text;
    cin>>key>>p_text;
    

    bin_to_hex["0000"]="0";
    bin_to_hex["0001"]="1";
    bin_to_hex["0010"]="2";
    bin_to_hex["0011"]="3";
    bin_to_hex["0100"]="4";
    bin_to_hex["0101"]="5";
    bin_to_hex["0110"]="6";
    bin_to_hex["0111"]="7";
    bin_to_hex["1000"]="8";
    bin_to_hex["1001"]="9";
    bin_to_hex["1010"]="A";
    bin_to_hex["1011"]="B";
    bin_to_hex["1100"]="C";
    bin_to_hex["1101"]="D";
    bin_to_hex["1110"]="E";
    bin_to_hex["1111"]="F";
    
    
    string key_bin="",p_text_bin="";
    for(int i=0;i<64;i++)
    {
        key_bin+=hex_to_bin(key[i]);
        p_text_bin+=hex_to_bin(p_text[i]);
    }
    
    string key_after_pc1="";
    
    //cout<<key_bin.length()<<endl;
    
    for(int i=0;i<56;i++)
    {
        key_after_pc1+=key_bin[pc1[i]-1];
    }

    string c[17];
    string d[17];
    string fin_keys[17];

    
    c[0]=key_after_pc1.substr(0,28);
    d[0]=key_after_pc1.substr(28);
        

    for(int i=1;i<=16;i++)
    {
    	c[i]=c[i-1];
    	d[i]=d[i-1];
    	for(int j=0;j<l_shifts[i-1];j++)
    	{
    		c[i]=left_shift_this(c[i]);
    		d[i]=left_shift_this(d[i]);
    	}
    	string temp= c[i]+d[i];
    	for(int j=0;j<48;j++)
    	{
    		fin_keys[i]+=temp[pc2[j]-1];
    	}

    	for(int j=0;j<=44;j+=4)
    	{
    		cout<<bin_to_hex[fin_keys[i].substr(j,4)];
    	}   
    	cout<<endl;
    }
    
    string m_after_ip="";

    for(int i=0;i<64;i++)
    {
    	m_after_ip+=p_text_bin[ip[i]-1];
    }

    string l0=m_after_ip.substr(0,32);
    string r0=m_after_ip.substr(32);

   
    string l1=r0;
    string er0="";
    for(int i=0;i<48;i++)
    {
    	er0+=r0[expp[i]-1];
    }

    for(int i=0;i<48;i++)
    {
    	er0[i]=(char)('0'+ (er0[i]-'0')^(fin_keys[1][i]-'0') );
    }
     
    string e_b[9];
    int e_bct=1;
    for(int i=0;i<=42;i+=6)
    {
    	e_b[e_bct++]=er0.substr(i,6);
    }

    string f="";

    for(int i=1;i<=8;i++)
    {
    	//cout<<e_b[i]<<' '<<i<<' '<<b_box(e_b[i],i)<<endl;
    	f+=b_box(e_b[i],i);
    }

    string ff="";

    for(int i=0;i<32;i++)
    {
    	ff+=f[permute[i]-1];
    }

    string r1="";

    for(int i=0;i<32;i++)
    {
    	r1+=(char)('0'+(ff[i]-'0')^(l0[i]-'0'));
    }

    string final_output=l1+r1;

    
    for(int i=0;i<=60;i+=4)
  	{
  		cout<<bin_to_hex[final_output.substr(i,4)];
  	}
    return 0;
}
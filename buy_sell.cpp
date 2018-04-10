#include<bits/stdc++.h>
#define ff first
#define ss second
#define mp make_pair
#define pb push_back
using namespace std;

string active_user;
string next_hash="DEFAULT";  //valid for one order only
map<string,string> login_pwd;
vector<  pair< string , pair<int,float> > >buy_vec[15]; //stock id, buyer id,quantity ,price in that order
vector<  pair< string , pair<int,float> > >sell_vec[15];
vector< pair< pair<int, float >, pair<string,string> > > matched_vec[15];  // stock id- <qty price> <buyer seller>

string login();

#define uchar unsigned char
#define uint unsigned int
 
#define DBL_INT_ADD(a,b,c) if (a > 0xffffffff - (c)) ++b; a += c;
#define ROTLEFT(a,b) (((a) << (b)) | ((a) >> (32-(b))))
#define ROTRIGHT(a,b) (((a) >> (b)) | ((a) << (32-(b))))
 
#define CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define EP0(x) (ROTRIGHT(x,2) ^ ROTRIGHT(x,13) ^ ROTRIGHT(x,22))
#define EP1(x) (ROTRIGHT(x,6) ^ ROTRIGHT(x,11) ^ ROTRIGHT(x,25))
#define SIG0(x) (ROTRIGHT(x,7) ^ ROTRIGHT(x,18) ^ ((x) >> 3))
#define SIG1(x) (ROTRIGHT(x,17) ^ ROTRIGHT(x,19) ^ ((x) >> 10))
 
typedef struct {
	uchar data[64];
	uint datalen;
	uint bitlen[2];
	uint state[8];
} SHA256_CTX;
 
uint k[64] = {
	0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,
	0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,
	0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
	0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,
	0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,
	0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
	0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,
	0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
};
 
void SHA256Transform(SHA256_CTX *ctx, uchar data[])
{
	uint a, b, c, d, e, f, g, h, i, j, t1, t2, m[64];
 
	for (i = 0, j = 0; i < 16; ++i, j += 4)
		m[i] = (data[j] << 24) | (data[j + 1] << 16) | (data[j + 2] << 8) | (data[j + 3]);
	for (; i < 64; ++i)
		m[i] = SIG1(m[i - 2]) + m[i - 7] + SIG0(m[i - 15]) + m[i - 16];
 
	a = ctx->state[0];
	b = ctx->state[1];
	c = ctx->state[2];
	d = ctx->state[3];
	e = ctx->state[4];
	f = ctx->state[5];
	g = ctx->state[6];
	h = ctx->state[7];
 
	for (i = 0; i < 64; ++i) {
		t1 = h + EP1(e) + CH(e, f, g) + k[i] + m[i];
		t2 = EP0(a) + MAJ(a, b, c);
		h = g;
		g = f;
		f = e;
		e = d + t1;
		d = c;
		c = b;
		b = a;
		a = t1 + t2;
	}
 
	ctx->state[0] += a;
	ctx->state[1] += b;
	ctx->state[2] += c;
	ctx->state[3] += d;
	ctx->state[4] += e;
	ctx->state[5] += f;
	ctx->state[6] += g;
	ctx->state[7] += h;
}
 
void SHA256Init(SHA256_CTX *ctx)
{
	ctx->datalen = 0;
	ctx->bitlen[0] = 0;
	ctx->bitlen[1] = 0;
	ctx->state[0] = 0x6a09e667;
	ctx->state[1] = 0xbb67ae85;
	ctx->state[2] = 0x3c6ef372;
	ctx->state[3] = 0xa54ff53a;
	ctx->state[4] = 0x510e527f;
	ctx->state[5] = 0x9b05688c;
	ctx->state[6] = 0x1f83d9ab;
	ctx->state[7] = 0x5be0cd19;
}
 
void SHA256Update(SHA256_CTX *ctx, uchar data[], uint len)
{
	for (uint i = 0; i < len; ++i) {
		ctx->data[ctx->datalen] = data[i];
		ctx->datalen++;
		if (ctx->datalen == 64) {
			SHA256Transform(ctx, ctx->data);
			DBL_INT_ADD(ctx->bitlen[0], ctx->bitlen[1], 512);
			ctx->datalen = 0;
		}
	}
}
 
void SHA256Final(SHA256_CTX *ctx, uchar hash[])
{
	uint i = ctx->datalen;
 
	if (ctx->datalen < 56) {
		ctx->data[i++] = 0x80;
 
		while (i < 56)
			ctx->data[i++] = 0x00;
	}
	else {
		ctx->data[i++] = 0x80;
 
		while (i < 64)
			ctx->data[i++] = 0x00;
 
		SHA256Transform(ctx, ctx->data);
		memset(ctx->data, 0, 56);
	}
 
	DBL_INT_ADD(ctx->bitlen[0], ctx->bitlen[1], ctx->datalen * 8);
	ctx->data[63] = ctx->bitlen[0];
	ctx->data[62] = ctx->bitlen[0] >> 8;
	ctx->data[61] = ctx->bitlen[0] >> 16;
	ctx->data[60] = ctx->bitlen[0] >> 24;
	ctx->data[59] = ctx->bitlen[1];
	ctx->data[58] = ctx->bitlen[1] >> 8;
	ctx->data[57] = ctx->bitlen[1] >> 16;
	ctx->data[56] = ctx->bitlen[1] >> 24;
	SHA256Transform(ctx, ctx->data);
 
	for (i = 0; i < 4; ++i) {
		hash[i] = (ctx->state[0] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 4] = (ctx->state[1] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 8] = (ctx->state[2] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 12] = (ctx->state[3] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 16] = (ctx->state[4] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 20] = (ctx->state[5] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 24] = (ctx->state[6] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 28] = (ctx->state[7] >> (24 - i * 8)) & 0x000000ff;
	}
}
 
string SHA256(char* data) {
	int strLen = strlen(data);
	SHA256_CTX ctx;
	unsigned char hash[32];
	string hashStr = "";
 
	SHA256Init(&ctx);
	SHA256Update(&ctx, (unsigned char*)data, strLen);
	SHA256Final(&ctx, hash);
 
	char s[3];
	for (int i = 0; i < 32; i++) {
		sprintf(s, "%02x", hash[i]);
		hashStr += s;
	}
 
	return hashStr;
}

struct block  //fixing a limit of 10 transactions
{
	string transactions;
	struct block * next;
	struct block * prev;
	string prevhash;
};


struct block* getLatestBlock(struct block * genesisNode);

struct block * newBlock()
{
	struct block * temp= new block;	
	temp->transactions="DEFAULT";	
	temp->next=NULL;
	temp->prev=NULL;
	temp->prevhash="89DBF71048801678CA4ABFBAA3EA8F7C651AAE193357A3E23D68E21512CD07F5";
	return temp;
}

/*template<typename Out>
void split(const std::string &s, char delim, Out result) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}
*/

struct block* getLatestBlock(struct block * genesisNode)
{
	while(genesisNode->next!=NULL)
	{
		genesisNode=genesisNode->next;
	}
	return genesisNode;
}

/*int validTransaction(struct block * genesis,string transaction)
{
	vector<string> qpbs=split(transaction,' ');// stock-id qty price buyer seller
	/*
	for buyer, check if he has enough money
	for seller, check if he has stocks
	*/
/*
	float buyercash=0;
	int sellerstocks=0;

	string buyerstr=qpbs[3];
	string sellerstr=qpbs[4];
	int qty=stoi(qpbs[1]);
	int stockID=stoi(qpbs[0]);
	float price=stof(qpbs[2]);

	struct block * last=getLatestBlock(genesis); //last added block

	while(last!=genesis)
	{
		string transactionCheck=last->transactions;
		vector<string> splitTransactions=split(transactionCheck,':');

		for(int i=0;i<splitTransactions.size();i++)
		{
			vector<string> qpbs2=split(splitTransactions[i],' ');

			string buyerstr2=qpbs2[3];
			string sellerstr2=qpbs2[4];
			int qty2=stoi(qpbs2[1]);
			int stockID2=stoi(qpbs2[0]);
			float price2=stof(qpbs2[2]);

			if(stockID2==stockID && buyerstr2==sellerstr)
			{
				sellerstocks+=qty2;
			}

			if(sellerstr2==buyerstr)
			{
				buyercash+=qty2*price2;
			}

		}

		last=last->prev;
	}


	if(buyercash>=qty*price&&sellerstocks>=qty)
	{
		return 1;
	}
	else
	{
		return 0;
	}

}



int isValidBlock(struct block * toCheck,struct block * genesis)
{
	string transactionCheck=toCheck->transactions;
	vector<string> splitTransactions=split(transactionCheck,':');
	struct block * last=getLatestBlock(genesis);
	int flag=1;
	for(int i=0;i<splitTransactions.size();i++)
	{
		//vector<string> qpbs=split(splitTransactions[i],' ');// qty price buyer seller
		if(!validTransaction(genesis,splitTransactions[i]))
		{
			flag=0;
			break;
		}
	}

	int nn = last->transactions.length(); 
    char char_array[nn+1]; 
    strcpy(char_array,last->transactions.c_str()); 
    string hash=SHA256(char_array);
	
	if(toCheck->prevhash==hash  && flag==1)
	{
		return 1;
	}
}
*/

void addNewBlock(struct block * genesisNode)
{
	struct block * lastBlock=getLatestBlock(genesisNode);
	struct block * tempBlock=newBlock();
	
	string addToBlock="";
	for(int i=0;i<15;i++)
		{
				for(int j=0;j<matched_vec[i].size();j++)
				{
					pair< pair< int , float > , pair< string , string > > temp= matched_vec[i][j];
					//cout<<i<<' '<<temp.ff.ff<<' '<<temp.ff.ss<<' '<<temp.ss.ff<<temp.ss.ss<<endl;
					int qty=temp.ff.ff;
					float price=temp.ff.ss;
					string buyerstr=temp.ss.ff;
					string sellerstr=temp.ss.ss;
					string tempstr=to_string(i)+" "+to_string(qty)+" "+to_string(price)+" "+buyerstr+" "+sellerstr;
					addToBlock+=(tempstr+":");
				}
		}
	//cout<<addToBlock<<endl;
	tempBlock->transactions=addToBlock;	

    if(next_hash!="DEFAULT")
    {
    	tempBlock->prevhash=next_hash;
    }

    int nn = addToBlock.length(); 
    char char_array[nn+1]; 
    strcpy(char_array,addToBlock.c_str()); 
    next_hash=SHA256(char_array);

    //if(isValidBlock(tempBlock,genesisNode))
	//{
		cout<<"Block added"<<endl;
		lastBlock->next=tempBlock;
		tempBlock->prev=lastBlock;	
	//}
	/*else
	{
		cout<<"Block adding failed"<<endl;
	}*/


	for(int i=0;i<15;i++)
		{
			matched_vec[i].clear();
		}
}

void printChain(struct block * genesisNode)
{
	int ct=0;
	while(genesisNode->next!=NULL)
	{
		cout<<ct<<endl;
		ct++;
		genesisNode=genesisNode->next;

		string toprint=genesisNode->transactions;
		cout<<toprint<<endl;
	}
}

void register_page()
{
	cout<<"Enter user id"<<endl;
	string uid;
	cin>>uid;
	cout<<"Enter password"<<endl;
	string pwd,pwd2;
	cin>>pwd;
	cout<<"Re-enter password"<<endl;
	cin>>pwd2;
	if(pwd==pwd2)
	{
		cout<<"Done :)"<<endl;
		cout<<"you have logged in"<<endl;
		login_pwd[uid]=pwd;
		active_user=uid;
	}
	else
	{
		cout<<"Pwds do not match. Try again"<<endl;
		register_page();
	}
}

void buysell()
{
	while(1)
				{
					cout<<"Enter B for buy order, S for sell order, X to exit"<<endl;
					char ch;
					cin>>ch;
					if(ch=='X')
						break;
					else if(ch=='B')
					{
						int stockID;
						int quantity;
						float price;
						cout<<"Enter Stock ID"<<endl;
						cin>>stockID;
						cout<<"Enter Quantity"<<endl;
						cin>>quantity;
						cout<<"Enter Bid price"<<endl;
						cin>>price;
						buy_vec[stockID].pb(mp(active_user,mp(quantity,price)));						
					}
					else if(ch=='S')
					{
						int stockID;
						int quantity;
						float price;
						cout<<"Enter Stock ID"<<endl;
						cin>>stockID;
						cout<<"Enter Quantity"<<endl;
						cin>>quantity;
						cout<<"Enter Ask price"<<endl;
						cin>>price;

						sell_vec[stockID].pb(mp(active_user,mp(quantity,price)));	
					}
				}
}


void match()
{
	for(int i=0;i<15;i++)
		{
				for(int j=0;j<buy_vec[i].size();j++)
				{
					pair< string , pair<int,float> > buyer=buy_vec[i][j];
					//cout<<i<<' '<<buyer.ff<<' '<<buyer.ss.ff<<' '<<buyer.ss.ss<<endl;

						for(int k=0;k<sell_vec[i].size();k++)
					{
						pair< string , pair<int,float> > seller=sell_vec[i][k];
						//cout<<i<<' '<<seller.ff<<' '<<seller.ss.ff<<' '<<seller.ss.ss<<endl;

						if(seller.ss.ss<=buyer.ss.ss)
						{
							if(seller.ss.ff>buyer.ss.ff)
							{
								sell_vec[i][k]=mp(seller.ff,mp(seller.ss.ff-buyer.ss.ff,seller.ss.ss));
								buy_vec[i].erase(buy_vec[i].begin()+j);
								matched_vec[i].pb(mp(mp(buyer.ss.ff,seller.ss.ss),mp(buyer.ff,seller.ff)));
							}
							else if(seller.ss.ff<buyer.ss.ff)
							{
								buy_vec[i][j]=mp(buyer.ff,mp(buyer.ss.ff-seller.ss.ff,buyer.ss.ss));
								sell_vec[i].erase(sell_vec[i].begin()+k);
								matched_vec[i].pb(mp(mp(seller.ss.ff,seller.ss.ss),mp(buyer.ff,seller.ff)));
							}
							else
							{
								buy_vec[i].erase(buy_vec[i].begin()+j);
								sell_vec[i].erase(sell_vec[i].begin()+k);
								matched_vec[i].pb(mp(mp(seller.ss.ff,seller.ss.ss),mp(buyer.ff,seller.ff)));
							}	
							match();					
						}						
					}
				}
		}

}

void printOrderBook()
{
	cout<<"BUY orders till now"<<endl;
		for(int i=0;i<15;i++)
		{
			for(int j=0;j<buy_vec[i].size();j++)
				{
					pair< string , pair<int,float> > temp=buy_vec[i][j];
					cout<<i<<' '<<temp.ff<<' '<<temp.ss.ff<<' '<<temp.ss.ss<<endl;
				}
		}
		cout<<"SELL orders till now"<<endl;
		for(int i=0;i<15;i++)
		{
			for(int j=0;j<sell_vec[i].size();j++)
				{
					pair< string , pair<int,float> > temp=sell_vec[i][j];
					cout<<i<<' '<<temp.ff<<' '<<temp.ss.ff<<' '<<temp.ss.ss<<endl;
				}
		}
}


string login()
{
	cout<<"Enter user id"<<endl;
	string uid;
	cin>>uid;
	cout<<"Enter password"<<endl;
	string pwd;
	cin>>pwd;

  	if(login_pwd[uid]==pwd)
  {
  	cout<<"you have logged in"<<endl;
  	return uid;
  }
  else
  {
  	cout<<"Wrong Password"<<endl;
  	return login();
  }
}

int main()
{
	struct block * genesis=newBlock();
	while(1)
	{	
		cout<<"Enter 1 to register, 2 to login"<<endl;
		int c;
		cin>>c;
		switch(c)
		{
			case 1:{register_page();buysell();}
			break;
			case 2:
			{
				active_user=login();
				buysell();
			}
			break;
		}

		printOrderBook();	
		
		match();
		cout<<"Matched orders:"<<endl;

		int flag_matched=0;

		for(int i=0;i<15;i++)
		{
				for(int j=0;j<matched_vec[i].size();j++)
				{
					pair< pair< int , float > , pair< string , string > > temp= matched_vec[i][j];
					cout<<i<<' '<<temp.ff.ff<<' '<<temp.ff.ss<<' '<<temp.ss.ff<<temp.ss.ss<<endl;
					flag_matched=1;
				}
		}
		
		

		if(flag_matched==1)
		{			
			addNewBlock(genesis);
			flag_matched=0;			
			printChain(genesis);
		}

		printOrderBook();	


	}
	return 0;
}



#include<bits/stdc++.h>
#define ff first
#define ss second
#define mp make_pair
#define pb push_back
using namespace std;

string active_user;  //valid for one order only
map<string,string> login_pwd;
vector<  pair< string , pair<int,float> > >buy_vec[15]; //stock id, buyer id,quantity ,price in that order
vector<  pair< string , pair<int,float> > >sell_vec[15];
vector< pair< pair<int, float >, pair<string,string> > > matched_vec[15];  // stock id- <qty price> <buyer seller>

string login();

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
}

int main()
{
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
		for(int i=0;i<15;i++)
		{
				for(int j=0;j<matched_vec[i].size();j++)
				{
					pair< pair< int , float > , pair< string , string > > temp= matched_vec[i][j];
					cout<<i<<' '<<temp.ff.ff<<' '<<temp.ff.ss<<' '<<temp.ss.ff<<temp.ss.ss<<endl;
				}
		}
		
		printOrderBook();	


	}
	return 0;
}


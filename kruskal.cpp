#include <iostream>
#include <fstream>
#include <string>

using namespace std;

ifstream file;
ofstream write;

class Edge
{
public:
	int ID;
	int from;
	int to;
	double cost;
	bool usage;
	Edge();
	void operator=(const Edge&);
	~Edge();

private:

};

Edge::Edge()
{
	usage = false;
}
void Edge::operator=(const Edge& copied)
{
	ID=copied.ID;
	from=copied.from;
	to=copied.to;
	cost=copied.cost;
	usage=copied.usage;

}
Edge::~Edge()
{
}

void read_connections(Edge*,int);
void Kruskal(Edge*,int,int);
void sort(Edge*,int);
void printNetwork(Edge*,int);
void findTotalCost(Edge*,int);
int findCentralCity(int*,int,Edge*,int);
void costToHeadOffice(Edge*,int,int,int,int*);

int main(int argc, char *argv[])
{
	string output = argv[2];
	string input = argv[1];
	write.open("output.txt");
	file.open("input.txt");
	int city;
	int conn;
	file>>city>>conn;

	Edge *connection = new Edge[conn];
	read_connections(connection,conn);
	Kruskal(connection,conn,city);
	file.close();
	write.close();

	return 0;
}

void read_connections(Edge *connections, int conn)
{
	for(int i=0;i<conn;i++)
	{
		connections[i].ID=i;
		file>>connections[i].from>>connections[i].to>>connections[i].cost;
	}
}

void Kruskal(Edge *connection,int conn,int city)
{
	int *cities = new int[city];
	for(int i=0;i<city;i++) cities[i]=-1;
	sort(connection,conn);
	bool cont;
	for(int i=0;i<conn;i++)
	{
		cont=true;
		if (cities[connection[i].from]<0&&cities[connection[i].to]<0)
			{
				connection[i].usage=true;
				if(cities[connection[i].from]<cities[connection[i].to])
				{
					cities[connection[i].from]+=cities[connection[i].to];
					cities[connection[i].to]=connection[i].from;
				}
				else
				{
					cities[connection[i].to]+=cities[connection[i].from];
					cities[connection[i].from]=connection[i].to;
				}
			}
		
			else if(cities[connection[i].from]>0&&cities[connection[i].to]<0)
			{
				int j=cities[connection[i].from];
				while (cont)
				{
					if(cities[j]<0)	
					{
						connection[i].usage=true;
						cont =false;
						if(cities[j]<cities[connection[i].to])
						{
							cities[j]+=cities[connection[i].to];
							cities[connection[i].to]=j;
						}
						else if(cities[j]>cities[connection[i].to])
						{
							cities[connection[i].to]+=cities[j];
							cities[j]=connection[i].to;
						}
						else if(j==connection[i].to)
						{
							connection[i].usage=false;
						}

					}
					j=cities[j];
				}
				
			}
		else if(cities[connection[i].from]<0&&cities[connection[i].to]>0)
			{
				int j=cities[connection[i].to];
				while (cont)
				{
					if(cities[j]<0)	
					{
						cont =false;
						connection[i].usage=true;
						if(cities[j]<cities[connection[i].from])
						{
							cities[j]+=cities[connection[i].from];
							cities[connection[i].from]=j;
						}
						else if(cities[j]>cities[connection[i].from])
						{
							cities[connection[i].from]+=cities[j];
							cities[j]=connection[i].from;
						}
						else if(j==connection[i].from)
							connection[i].usage=false;
					}
					j=cities[j];
				}
				
			}
		else if(cities[connection[i].from]==cities[connection[i].to]);
		else 
		{
			int a=0;
			int k=connection[i].from;
			int j=connection[i].to;
			while(a<2)
			{
				if(cities[k]>=0)k=cities[k];
				if(cities[j]>=0)j=cities[j];
				if(cities[k]<0)	a++;
				if(cities[j]<0)	a++;

			}
			if(k!=j)
			{
				if(cities[k]<=cities[j])
				{
						cities[k] += cities[j];
						cities[j]=k;
				}
				else if(cities[j]<cities[k])
				{
					cities[j] += cities[k];
					cities[k]=j;
				}
				connection[i].usage=true;
			}
		}
		}
		
	printNetwork(connection,conn);
	findTotalCost(connection,conn);
	int central=findCentralCity(cities,city,connection,conn);

	
}

void sort(Edge *connections,int conn)
{
	Edge smaller;
	smaller.cost=10000;
	Edge *sorted = new Edge[conn+1];
	sorted[0].cost=0;
	for (int j=1;j<=conn;j++)
	{
		for(int i=0;i<conn;i++)
			if(smaller.cost>connections[i].cost&&connections[i].cost>sorted[j-1].cost) smaller=connections[i];

		sorted[j]=smaller;
		smaller.cost=10000;
	}
	for(int i=0; i<conn;i++) connections[i]=sorted[i+1];


}

void printNetwork(Edge *connection,int conn)
{
	for(int i=0;i<conn;i++)
	{
		if(connection[i].usage==true)
		{
			cout<<"("<<connection[i].from<<","<<connection[i].to<<")"<<endl;
			write<<"("<<connection[i].from<<","<<connection[i].to<<")"<<endl;
		}
	}
}

void findTotalCost(Edge *connection,int conn)
{
	double total_cost=0;

	for(int i=0;i<conn;i++)
	{
		if(connection[i].usage) total_cost+=connection[i].cost;
	}

	cout<<"The network total cost\t:\t"<<total_cost<<endl;
	write<<"The network total cost\t:\t"<<total_cost<<endl;
}

int findCentralCity(int *cities,int city, Edge *connection,int conn)
{
	for(int i=0;i<city;i++)
	{
		cities[i]=0;
	}
	for(int i=0;i<conn;i++)
	{
		if(connection[i].usage) 
		{
			cities[connection[i].to]++;
			cities[connection[i].from]++;
		}
	}
	int bigger = 0,a;
	for (int i = 0; i < city; i++)
	{
		if(cities[i]>bigger) bigger = cities[i];
	}
	for (int i = 0; i < city; i++)
	{
		if(cities[i]==bigger) 
		{
			cout<<"The central city\t:\t"<<i<<"th"<<endl;
			write<<"The central city\t:\t"<<i<<"th"<<endl;
			costToHeadOffice(connection,i,city,conn,cities);
			a=i;
		}
	}
	return a;
}

void costToHeadOffice(Edge* connection,int central,int city,int conn,int *cities)
{
	int delmin;
	double total=0;
	double *cost = new double[city];
	bool *used = new bool[city];
	int smallestCity;
	double smallest,smallest1=0.00000001;
	
	
	for(int i=0;i<city;i++)
	{
		delmin=i;
		for(int k=0;k<city;k++) if(k!=delmin){ cost[k]=0; used[k]=false;}
		cost[delmin]=0;
		smallest1=0.00000001;
		while(delmin!=central)
		{
			used[delmin]=true;
			smallest=1000000;
			for(int j=0;j<conn;j++)
			{
				if(connection[j].from==delmin&&(cost[connection[j].to]>=cost[connection[j].from]+connection[j].cost||cost[connection[j].to]==0))
				{
					cost[connection[j].to]=cost[connection[j].from]+connection[j].cost;
				}
				else if(connection[j].to==delmin&&(cost[connection[j].from]>=cost[connection[j].to]+connection[j].cost||cost[connection[j].from]==0))
				{
					cost[connection[j].from]=cost[connection[j].to]+connection[j].cost;
				}
			}
			for(int j=0;j<city;j++)
			{
				if(cost[j]>=smallest1&&cost[j]<smallest&&used[j]==false)
				{
					smallest=cost[j];
					smallestCity=j;
				}
			}
			delmin=smallestCity;
			smallest1=smallest;

		}

		total+=cost[central];
		
	}
	cout<<"The total cost of communication between the head office : "<<total<<endl;
	write<<"The total cost of communication between the head office : "<<total<<endl;

}
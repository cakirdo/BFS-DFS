1) 
Firstly, my program sorts connections ascending order according to cost of connections. After that, my program uses the Kruskal Algorithm to delete unnecessary edges to decrease total cost of network. After that it finds head office which has biggest connection number. And It finds the total cost of communication between the head office and all the other cities using Dijkstra Algorithm. 
 
I used Edge class to hold where edges from, where edges to, costs of edges and usage of edges. 
I have 7 methods: 
void read_connections(Edge*,int); is used to read connections using Edge class and copy to connection array. 
 
void Kruskal(Edge*,int,int); is used to implment Kruskal 
 
void sort(Edge*,int); sorts the connections ascending order according to cost of connections. 
 
void printNetwork(Edge*,int); prints using connections after Kruskal implemented. 
 
void findTotalCost(Edge*,int); finds total cost of network after implementation of Kruskal. 
 
int findCentralCity(int*,int,Edge*,int); finds central city according to using connection number of nodes 
 
void costToHeadOffice(Edge*,int,int,int,int*); 
finds total cost to ad office from each node. This is the part of Dijkstra implementation. 
 
 
(initialization) 
citynumber of node 
connnumber of edge 
connection[conn]the array holds edges 
cities[city]-1 
total0 
 
SORT connection[] ascending order       //n2 
FOR EACH from i=0 to i<conn i++       //n 
 İf (cities[ left side of edge]<0 AND cities[ right side of edge]<0)  //n  
  İf(cities[ left side of edge]< cities[ right side of edge])  //n 
   cities[left side of edge] +=cities[right side of edge]  //n 
   cities[right side of edge]=left side of edge    //n 
connection is used.      //n 
 
  else if(cities[ right side of edge]< cities[ left side of edge])  //n 
   cities[right side of edge] +=cities[left side of edge]  //n 
   cities[left side of edge]=right side of edge    //n 
connection is used.      //n 
 
 else if (cities[ left side of edge]>0 AND cities[ right side of edge]<0) //n 
  REPEAT until cities[left side of edge]<0    //n(n+1)    
	left side of edge= cities[left side of edge]   //n2   
  END REPEAT       //n2 
  if(cities[ left side of edge]< cities[ right side of edge])  //n  
	cities[left side of edge] +=cities[right side of edge]  //n 
	cities[right side of edge]=left side of edge    //n 
	connection is used.      //n 
 
  else if(cities[ right side of edge]< cities[ left side of edge])  //n 
   cities[right side of edge] +=cities[left side of edge]  //n 
   cities[left side of edge]=right side of edge    //n 
connection is used.      //n 
 
 else if (cities[ right side of edge]>0 AND cities[ left side of edge]<0) //n 
  REPEAT until cities[right side of edge]<0    //n(n+1)    
	right side of edge= cities[right side of edge]   //n2   
  END REPEAT       //n2 
  if(cities[ left side of edge]< cities[ right side of edge])  //n 
   cities[left side of edge] +=cities[right side of edge]  //n 
   cities[right side of edge]=left side of edge    //n 
	connection is used.      //n 
 
  else if(cities[ right side of edge]< cities[ left side of edge])  //n 
   cities[right side of edge] +=cities[left side of edge]  //n 
   cities[left side of edge]=right side of edge    //n 
	connection is used.      //n 
 
 
 else          //n 
  REPEAT until cities[right side of edge]<0    //n(n+1)    
	right side of edge= cities[right side of edge]   //n2   
  END REPEAT       //n2 
  REPEAT until cities[left side of edge]<0    //n(n+1)  
	left side of edge= cities[left side of edge]   //n2   
  END REPEAT       //n2 
  if(cities[ left side of edge]< cities[ right side of edge])  //n 
   cities[left side of edge] +=cities[right side of edge]  //n 
   cities[right side of edge]=left side of edge   //n 
   connection is used.      //n 
  else İf(cities[ right side of edge]< cities[ left side of edge])  //n 
   cities[right side of edge] +=cities[left side of edge]  //n 
   cities[left side of edge]=right side of edge   //n 
connection is used.      //n 
END FOR EACH         //n 
FOR EACH from i=0 to i<conn i++       //n+1 
İf( connection[i].usage)        //n 
Print connection[i]       //n 
END FOR EACH         //n 
FOR EACH from i=0 to i<conn i++       //n+1 
İf( connection[i].usage)        //n 
  total+=connection[i].cost      //n 
 END IF         //n 
END FOR EACH          //n 
print total // total cost of network       //1 
 
cities[]0          //1 
FOR EACH from i=0 to i<conn i++       //n+1 
 if(connection[i].usage)       //n 
  cities[left side of connection[i]]++     //n 
  cities[right side of connection[i]]++     //n 
 END IF         //n 
 central = the biggest cities[]       //n 
END FOR EACH         //n 
 print central // head office       //1 
 
 cost[city]         //1 
 used[city]false        //n 
 total 0         //1 
FOR EACH from i=0 to i< city i++       //n+1 
 Delmin=i         //n 
 Smallest = 1000000        //n 
REPEAT UNTIL central==delmin      //n(n+1)  
	Used[delmin]true       //n2  
	if(one side of edge == delmin)     //n2   
		Cost[other side]=cost[delmin]+cost[this edge]  //n2  
	END IF        //n2  
	Find (the city which has smallest cost AND unused city)  //n2 
	delmin = smallest city       //n2 
  END REPEAT        //n2 
Total += cost of central       //n 
END FOR EACH         //n 
Print total // total cost to head office       //1 
 
2) I show the complexity of each line on pseudo code. If we look the total complexity we have to add all lines complexities and the result is O(n2). 
 
Resulting network is an minimum spanning tree problem. I overcome this problem using Kruskal Algorithm. In this part there is an array and element number of array is node number. Each element is pair to a node. All elements of array equal to -1 initially. Firstly, edges are sorted ascendingly according to costs of edges. After that edges are taken in order. And array is checked according to nodes edge have. If two numbers on array is negative smaller one holds the total of two number and bigger one holds the other’s order number. 
0 1  2 3  4 5 6 7 
- - -1 - -2 - - - 
For example if node 2 and node 4 are connected with an edge. After operation node 2 holds 4. And node 4 holds -3. 
If one of the two numbers on array is negative and the other one is positive, program goes to positive numbers array area until find negative or equal number to array area which hold negative number. 
  
 0 1  2 3  4 5 6 7
-1 3 -1 4 -2 - - - 
If node 0 and node 1 are connected with an edge. Node 0 is compared to node 3 and than compared to node 4. After this operations node 0 holds 4 and node 4 holds -3. 
 
If both of two nodes holds positive number, program scans until to find negative numbers and does operations 
 0 1  2 3  4 5  6  7 
-1 3 -1 4 -2 4 -2 -1 
If we compare node 1 to node 5 we will reach node for both and we dont do anything. 
 
After these operations are applied, if two different array area which holds negative numbers are reached, this edge is on our network.  
This algorithm blocks the creation of cycles. 
 
In the total cost of your network problem, I just look for the edges which are used. And I take the sum of costs of used edges. 
 
The central city is the city which has the biggest number of connection. 
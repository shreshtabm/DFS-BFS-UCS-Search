
import java.util.*;
import java.io.*;

public class Breadth_First_Search 
{
	public int number_nodes;
	public String root, goal;
	public int edge[][] = new int [40][40];
	String [] g_nodes = new String[80]; 
	
	
	public Breadth_First_Search(int no_of_nodes, String src, String dst,int[][] graph_matrix, String[] nodes)
			
	{
		
		number_nodes = no_of_nodes;
		root 		 = src;
		goal		 = dst;
		edge 		 = graph_matrix;
		g_nodes 	 = nodes;
		
	}
	
	public void bfs() throws IOException
	{
		BufferedWriter bw = new BufferedWriter(new FileWriter(new File ("output.txt").getAbsolutePath()));
		
		System.out.println("In BFS");
		//Queue<String> queue = new LinkedList<String>();
		String element;
		List<String> visited = new ArrayList<String>();
		List<String> traversed = new ArrayList<String>();
		List<String> unvisit_chldrn = new ArrayList<String>();
		String [][] track_parent = new String[40][2];
		Stack<String> get_parent = new Stack<String>();
		int cost = 0;
		int m=0,p=0;
		int goal_fnd = 0;
		int distance_from_root = 0;
		
		PriorityQueue<Node> pqueue = new PriorityQueue<Node>(
				20, new Comparator<Node>()
				{
					public int compare(Node a, Node b)
					{
	                    if(a.cost > b.cost)
	                        return 1;
	                   else if (a.cost < b.cost)
	                        return -1;
	                   else
	                   {
	                	   if(a.element.compareTo(b.element) > 0)
		                        return 1;
		                   else		// (a.node.compareTo(b.node) < 0)
		                        return -1;
	                	   
	                   }
						
	                }
	            }
	        );
		
		System.out.println("Goal = " +goal);
		Node n = new Node(root,distance_from_root);
		pqueue.add(n);
		//System.out.println("Element added = " +root);
		visited.add(root);
		
		while(!pqueue.isEmpty())
		{
			
			//element = pqueue.remove();
			element = pqueue.poll().getnode();
			//System.out.println("Element removed = " +element);
			traversed.add(element);
			
			if(element.equals(goal))
			{
				goal_fnd = 1;
				break;
			}
			else
			{
				for(int j=1;j <= number_nodes;j++)
					if(g_nodes[j].equals(element))
						m = j;
				
				//Get all unvisited children
				for(int i=1;i<=number_nodes;i++)
				{
					if(edge[m][i] > 0)
					{
						if(!visited.contains(g_nodes[i]))
						{
							unvisit_chldrn.add(g_nodes[i]);
							
							//Add parent-child relation
							p++;
							track_parent[p][0] = g_nodes[m];
							track_parent[p][1] = g_nodes[i];
						}
					}	
				}
				
				//if(unvisit_chldrn.size() > 0)
				distance_from_root++;
				
				//Push all the nodes in alphabetical order
				
				//java.util.Collections.sort(unvisit_chldrn);
				for(int j=0; j < unvisit_chldrn.size() ; j++)
				{
					//Push & mark visited
					//pqueue.add(unvisit_chldrn.get(j));
					pqueue.add(new Node(unvisit_chldrn.get(j),distance_from_root));
					System.out.println("Element added = " +unvisit_chldrn.get(j));
					System.out.println("distance_from_root = " +distance_from_root);
					visited.add(unvisit_chldrn.get(j));
				}
				
				//Clear the unvisited list
				unvisit_chldrn.clear();
			}
		}
		
		if(goal_fnd == 1)
		{
			System.out.println("Goal reached");
			System.out.println("BFS traversal is");
			
			Iterator<String> i = traversed.iterator();
			if (i.hasNext()) 
			{
				//System.out.print(i.next());
				bw.write(i.next());
			    while (i.hasNext())
			    {
			      //System.out.print("-"+i.next());
			      bw.write("-"+i.next());
			    }
			 }
		}
		else
		{
			bw.write("NoPathAvailable");
		}
			
		
	
		//To find the optimal path and cost
		String child = goal;
		get_parent.push(goal);
		
		for( ; ; )
		{
			
			int f,g=0;
			for(f=1;f <= p;f++)
			{
				if(track_parent[f][1].equals(child))
				{
					g = f;
					
					cost = cost + getpathcost(track_parent[g][0],child);
					
					get_parent.push(track_parent[g][0]);
					child = track_parent[g][0];
					if (track_parent[g][0].equals(root))
					{
						
						bw.newLine();
						while(!get_parent.empty())
						{
							bw.write(get_parent.pop());
							if(!get_parent.empty())
							{
								bw.write('-');
							}
						}
						cost = cost + getpathcost(track_parent[g][0],child);
						bw.newLine();
						String data=Integer.toString(cost);
						bw.write(data);
						bw.newLine();
						bw.close();
						readoutputfileanddisplay();
						break;
					}
				}
			}	
		}			
		
	}
	
	public int getpathcost(String prnt,String child)
	{
		String u = prnt;
		String v = child;
		int m=0,n=0;
		
		for(int d=1;d<=number_nodes;d++)
			if(g_nodes[d].equals(u))
					m=d;
		
		for(int d=1;d<=number_nodes;d++)
			if(g_nodes[d].equals(v))
					n=d;
		
		return edge[m][n];
		
	}
	
	public void readoutputfileanddisplay() throws IOException
	{
		String str;
		BufferedReader br = new BufferedReader(new FileReader(new File ("output.txt").getAbsolutePath()));
		
		 while ((str = br.readLine()) != null)
		 {
			 System.out.println(str);
		 }
		 br.close();
	}
}
		
class Node
{
	public String element;
	public int cost;
	
	public Node(String element)
	{
		this.element = element;
	}
	
	public Node(String element, int cost)
	{
		this.element = element;
		this.cost = cost;
	}
	
	
	public String getnode()
	{
		return element;
	}
	
	public int getcost()
	{
		return cost;
	}
	
}
	

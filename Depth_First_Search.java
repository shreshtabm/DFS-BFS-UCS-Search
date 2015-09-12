
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.*;

public class Depth_First_Search 
{

	public int number_nodes;
	public String root, goal;
	public int edge[][] = new int [40][40];
	String [] g_nodes = new String[80]; 
	
	
	public Depth_First_Search(int no_of_nodes, String src, String dst,int[][] graph_matrix, String[] nodes)
			
	{
		
		number_nodes = no_of_nodes;
		root 		 = src;
		goal		 = dst;
		edge 		 = graph_matrix;
		g_nodes 	 = nodes;
		
	}
	
	public void dfs() throws IOException
	{
		BufferedWriter bw = new BufferedWriter(new FileWriter(new File ("output.txt").getAbsolutePath()));
		
		System.out.println("In DFS");
		
		Stack<String> stack = new Stack<String>();
		String element;
		List<String> visited = new ArrayList<String>();
		List<String> traversed = new ArrayList<String>();
		List<String> unvisit_chldrn = new ArrayList<String>();
		String [][] track_parent = new String[40][2];
		Stack<String> get_parent = new Stack<String>();
		int cost = 0;
		int m=0,p=0;
		int goal_fnd = 0;
		
		System.out.println("Goal = " +goal);
		stack.push(root);
		visited.add(root);
		
		while(!stack.isEmpty())
		{
			element = stack.pop();
			System.out.println("Popped Element = " +element);
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
						//if(!traversed.contains(g_nodes[i]))		//Only if stack elements are not req to be unique, if they have to be unique then check 'visited'
						{
							unvisit_chldrn.add(g_nodes[i]);
							
							//Add parent-child relation
							p++;
							track_parent[p][0] = g_nodes[m];
							track_parent[p][1] = g_nodes[i];
						}
					}	
				}
				
				//Push all the nodes in reverse alphabetical order
				
				java.util.Collections.sort(unvisit_chldrn);
				for(int j=(unvisit_chldrn.size() -1); j >= 0 ; j--)
				{
					//Push & mark visited
					stack.push(unvisit_chldrn.get(j));
					System.out.println("Element pushed = " +unvisit_chldrn.get(j));
					visited.add(unvisit_chldrn.get(j));
				}
				
				//Clear the unvisited list
				unvisit_chldrn.clear();
				
			}	
		}
		
		if(goal_fnd == 1)
		{
			System.out.println("Goal reached");
			System.out.println("DFS traversal is");
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
			//System.out.println("No Path Available");
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
						//cost = cost + getpathcost(track_parent[g][0],child);
						//System.out.println("Path Cost = " +cost);
						//System.out.println("Optimal Path: ");
						
						while(!get_parent.empty())
						{
							//System.out.print ( get_parent.pop());
	                        //System.out.print ( ',' );
							bw.write(get_parent.pop());
							if(!get_parent.empty())
							{
								//System.out.print ( '-' );
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
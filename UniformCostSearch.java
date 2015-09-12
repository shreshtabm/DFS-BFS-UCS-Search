import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.PriorityQueue;


public class UniformCostSearch 
{
	public int number_nodes;
	public String root, goal;
	public int edge[][] = new int [40][40];
	String [] g_nodes = new String[80]; 
	PriorityQueue<Node1> pqueue;
	
	public UniformCostSearch(int no_of_nodes, String src, String dst,int[][] graph_matrix, String[] nodes)
	{
		number_nodes = no_of_nodes;
		root 		 = src;
		goal		 = dst;
		edge 		 = graph_matrix;
		g_nodes 	 = nodes;
		pqueue= new PriorityQueue<Node1>(no_of_nodes,new Node1());
	}
	public void ucs() throws IOException
	{
		BufferedWriter bw = new BufferedWriter(new FileWriter(new File ("output.txt").getAbsolutePath()));
		
		System.out.println("In UCS");
		
		List<String> traversed = new ArrayList<String>();
		List<String> visited = new ArrayList<String>();
		int []least_distance = new int[40];
		String[] parentchild=new String[40];
		int goal_fnd = 0;
		
		for(int x=1;x<=number_nodes;x++)
		{
			for(int j=1;j<=number_nodes;j++)
			{
				if (x == j)
                {
					edge[x][j] = 0;
					continue;
                }
                if (edge[x][j] == 0)
                {
                	edge[x][j] = 1000;
                }
			}
		}
		
		for(int a=1;a<=number_nodes;a++)
			least_distance[a] = 10000;
		
		System.out.println("Goal = " +goal);
		Node1 n = new Node1(root,0);
		pqueue.add(n);
		least_distance[1]=0;
		 
		while(!pqueue.isEmpty())
		{
			Node1 nd = pqueue.remove();	
			traversed.add(nd.element);
			String popped=nd.element;
			int num=0;
		
			for(int i=1;i<=number_nodes;i++)
			{
				if(g_nodes[i].equals(popped))
					num=i;
			}
		
			if(popped.equals(goal))
			{
				goal_fnd = 1;
				break;
			}
			else
			{
				visited.add(popped);
				//System.out.println("Expansion "+traversed);
				for(int i=1;i<=number_nodes;i++)
				{ 
					if(!visited.contains(g_nodes[i]))
					{	
						if (edge[num][i] != 1000)
						{
							if (least_distance[i] > edge[num][i] + least_distance[num])
							{
								least_distance[i] = edge[num][i] + least_distance[num]; 	
								String parent=popped;
								parentchild[i] = parent;
							}		
							Node1 node = new Node1(g_nodes[i], least_distance[i]);
							if (pqueue.contains(node))
							{
								pqueue.remove(node);
							}
							pqueue.add(node);
						}
					}
				}
			}
		}
		
		if(goal_fnd == 1)
		{
			System.out.println("Goal reached");
			System.out.println("UCS traversal is "+traversed);
			/*for(int i=1;i<=number_nodes;i++)
			{
				System.out.println("Parent Of "+g_nodes[i]+" is "+parentchild[i]);
			}*/
			
			Iterator<String> it = traversed.iterator();
			if (it.hasNext()) 
			{
				//System.out.print(i.next());
				bw.write(it.next());
			    while (it.hasNext())
			    {
			      //System.out.print("-"+i.next());
			      bw.write("-"+it.next());
			    }
			 }
			
			int goal_number=0;
			for(int i=1;i<=number_nodes;i++)
			{
				if(g_nodes[i].equals(goal))
				{
					goal_number=i;
				}
			}
			int start=0;
		
			for(int i=1;i<=number_nodes;i++)
			{
				if(g_nodes[i].equals(root))
					start=i;
			}
			LinkedList<String> rev_path=new LinkedList<String>();
			int goal=goal_number;
			rev_path.add(g_nodes[goal_number]);
			String new_par=null;
			int found=0;
			while(found==0)
			{
				if(start==goal)
				{
					found=1;
					continue;
				}
				rev_path.add(parentchild[goal]);
				new_par=parentchild[goal];
				for(int i=1;i<=number_nodes;i++)
				{
					if(g_nodes[i].equals(new_par))
						goal=i;
				}	
			}
			LinkedList<String> path=new LinkedList<String>();
			Iterator<String> iterator = rev_path.descendingIterator();
			while(iterator.hasNext())
			{
				path.add(iterator.next());
			}
			System.out.println("Path is "+path);
			bw.newLine();
			Iterator<String> ip = path.iterator();
			if (ip.hasNext()) 
			{
				//System.out.print(i.next());
				bw.write(ip.next());
			    while (ip.hasNext())
			    {
			      //System.out.print("-"+i.next());
			      bw.write("-"+ip.next());
			    }
			 }
			System.out.println("Cost is :"+least_distance[goal_number]);
			bw.newLine();
			String data=Integer.toString(least_distance[goal_number]);
			bw.write(data);
			bw.newLine();
			bw.close();
		}
		else
		{
			System.out.println("NoPathAvailable");
		}
	}	
}

class Node1 implements Comparator<Node1> 
{

	public String element;
	public int distance;
	
	public Node1(String node) 
	{	
		this.element = node;
	}
	
	public Node1(String element,int distance)
	{
		this.element=element;
		this.distance=distance;
	}
	public Node1()
	{
		
	}

    public boolean equals(Object object)
    {
        if (object instanceof Node1)
        {
            Node1 n = (Node1) object;
            if (this.element == n.element)
            {
                return true;
            }
        }
        return false;
    }
	
    public int compare(Node1 a, Node1 b)
    {
		//Cost Comparison in the Queue
        if (a.distance < b.distance)
            return -1;
        else if (a.distance > b.distance)
            return 1;
        else
        {
        if (a.element.compareTo(b.element)<0)
            return -1;
        else 
            return 1;
        }
    }
	
}







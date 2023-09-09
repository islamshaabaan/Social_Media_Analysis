import matplotlib.pyplot as plt
import networkx as nx
import warnings
from matplotlib.cbook.deprecation import MatplotlibDeprecationWarning
warnings.filterwarnings("ignore", category=MatplotlibDeprecationWarning)

mylines = []
src=[]
des=[]
wt=[]
nums = []
node_sizes=[]
with open('input.txt', 'rt') as myfile:  # Open file input.txt for reading text
    for line in myfile:                   # For each line of text,
        mylines.append(line.rstrip('\n')) # add that line to the list.
    for i in range(len(mylines)):
        nums.append(mylines[i].split())

nums = [i for b in map(lambda x:[x] if not isinstance(x, list) else x, nums) for i in b] # unlist the list in nums list
for i in range(0, len(nums), 3):src.append(nums[i])
for i in range(0, len(nums), 3):des.append(nums[i+1])
for i in range(0, len(nums), 3):wt.append(nums[i+2])
wt = list(map(float, wt)) # convert weight from string to float
G = nx.Graph()
for i in range(len(mylines)):G.add_edge(src[i], des[i], weight=wt[i]) # Bulid the graph
pos = nx.spring_layout(G) #random Layout (position for nodes)
nx.draw_networkx_edges(G, pos, width=3) # draw edges
d= [val*300 for (node, val) in G.degree()] # get list of degree values from G.degree function
nx.draw_networkx_nodes(G, pos, node_color=d,node_size=d) # draw nodes
# labels
nx.draw_networkx_labels(G, pos, font_size=15, font_family='sans-serif')
labels = nx.get_edge_attributes(G,'weight')
nx.draw_networkx_edge_labels(G,pos,edge_labels=labels)
plt.axis('off')
plt.show()
#plt.savefig('output.png')

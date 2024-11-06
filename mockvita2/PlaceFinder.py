import math
from collections import defaultdict, deque

def connect(adjclist, device1, device2, distance, angle):
    # Calculate the x and y components of the distance
    x = distance * math.cos(math.radians(angle))
    y = distance * math.sin(math.radians(angle))
    adjclist[device1].append((device2, x, y))
    adjclist[device2].append((device1, -x, -y))  # Reverse the direction for undirected connection

def finddist(adjclist, start, target):
    # Perform BFS to find the shortest path and calculate the distance
    q = deque([(start, 0.0, 0.0)])  # (current node, x sum, y sum)
    vis = set([start])
    
    while q:
        curr, sumxval, sumyval = q.popleft()
        if curr == target:
            return math.sqrt(sumxval**2 + sumyval**2)  # Correct the formula for distance
        
        for adj, dx, dy in adjclist[curr]:
            if adj not in vis:
                vis.add(adj)
                q.append((adj, sumxval + dx, sumyval + dy))
    return -1  # Return -1 if no path exists

# Main input section
n = int(input().strip())  # Number of devices
devices = input().strip().split()  # List of device names

# Create the adjacency list for the connections
adjclist = defaultdict(list)

for _ in range(n):
    devid = int(input().strip())  # Device ID (1-indexed)
    conn = int(devices[devid - 1].split(':')[1])  # Extract number of connections
    for _ in range(conn):
        nid, dist, angle = map(int, input().strip().split())  # Neighbour ID, distance, and angle
        connect(adjclist, devid, nid, dist, angle)

# Start and end device IDs
start, end = map(int, input().strip().split())

# Find the distance using BFS
distance = finddist(adjclist, start, end)

# Output the result
if distance != -1:
    print(f"{distance:.2f}")
else:
    print("Path not found")

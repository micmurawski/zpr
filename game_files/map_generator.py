#temporary version of map generator
#to be improved

from graphics import *
from random import randint, normalvariate, random
from math import sin, cos

#variables defining how map will look like
map_x = 800
map_y = 500
points_nr = 90	
min_distance = 15
#first normal distribution with sigma = sigma1, after a points sigma = sigma2
sigma1 = 60
sigma2 = 50
a = 100
#
b= 5

def is_intersection (map_points, map_point):
	min_distance2 = min_distance * min_distance
	for p in map_points:
		distance  = (p.x_ - map_point.x_)*(p.x_ - map_point.x_)+(p.y_ - map_point.y_)*(p.y_ - map_point.y_)
		if distance<min_distance2:
			return True
	else:
		return False
		
def is_in_map (map_point):
	if map_point.x_+min_distance>map_x or map_point.y_+min_distance>map_y or map_point.x_<min_distance or map_point.y_<min_distance:
		return False
	else:
		return True
		
def link(x, map_point, map_points):
	temp  = list(map_points)
	temp.remove(map_point)
	points_near = []
# loop searches for the x nearest points
	for i in range(0, x):
		n = min(temp, key = lambda point: (map_point.x_ - point.x_)*(map_point.x_ - point.x_) + (map_point.y_ - point.y_)*(map_point.y_ - point.y_))
		points_near.append(n)
		temp.remove(n)
#checking if there are two connections and picking two closest and linking them to the point
	while len(map_point.connections_)<x:
		if points_near[0].id_nr_ not in map_point.connections_:
			map_point.connections_.append(points_near[0].id_nr_)
		if map_point.id_nr_ not in map_points[points_near[0].id_nr_].connections_:
			map_points[points_near[0].id_nr_].connections_.append(map_point.id_nr_)
		points_near.pop(0)
		
		
		
	

class MapPoint:
	def __init__(self, x, y, id_nr):
		self.x_ = x
		self.y_ = y
		self.id_nr_ = id_nr
		self.connections_ = []
	def __init__(self, id_nr, sigma):
		mu = 0
		r = abs(normalvariate(mu, sigma)*b)
		#print r
		fi = random() * 2 * 3.14
		#print fi
		self.x_ = abs(int(r * sin (fi)+map_x/2))
		self.y_ = abs(int(r * cos (fi)+map_y/2))
		self.id_nr_ = id_nr
		self.connections_ = []
	
map_points = []

sigma=sigma1
for i in range(0, points_nr-1):
	if i>a:
		sigma=sigma2
	#m = MapPoint(randint(0,map_x),randint(0,map_y),i)
	m = MapPoint(i, sigma)
	#print randint(0,map_x)
	while is_intersection(map_points, m) or not is_in_map(m):
		m = MapPoint(i, sigma)
	map_points.append(m)
	
for p in map_points:
	link(3, p, map_points)

for p in map_points:
	print p.connections_
	
win = GraphWin("kek", map_x, map_y)

for p in map_points:
	#print map_points[i].x_
	c = Circle(Point(p.x_, p.y_), 5)
	for connection in p.connections_:
		l = Line(Point(p.x_, p.y_), Point(map_points[connection].x_, map_points[connection].y_))
		l.draw(win)
	c.draw(win)




#c = Circle(Point(50, 50), 10)
#c.draw(win)
win.getMouse()
win.close()

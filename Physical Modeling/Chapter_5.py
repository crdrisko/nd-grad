#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created: Fri Jul 13 20:12:12 2018

Author: crdrisko

Description: Chapter 5 (More Python Constructions) 
                "A Student's Guide to Python for Physical Modeling"
                    - Jesse M. Kinder and Philip Nelson              
"""

import numpy as np
import matplotlib.pyplot as plt

#%% 5.1.1 - Defining functions in Python
def taxicab(pointA, pointB):
    """
    Taxicab metric for computing distance between points A and B.
        pointA = (x1, y1)
        pointB = (x2, y2)
    Returns |x2 - x1| + |y2 - y1|. Distances are measured in city blocks.
    """
    interval = abs(pointB[0] - pointA[0]) + abs(pointB[1] - pointA[1])
    return interval

fare_rate = 0.40
start = (1, 2)
stop = (4, 5)
trip_cost = taxicab(start, stop) * fare_rate

#%% Your Turn 5A
def resultant(pointA, pointB):
    """
    Function computing distance between points A and B as the crow flies.
        pointA = (x1, y1, z1)
        pointB = (x2, y2, z2)
    Returns sqrt((x1 + x2)^2 + (y1 + y2)^2 + (z1 + z2)^2). Distances are measured in city blocks.
    """
    magnitudeC = np.sqrt((pointA[0] + pointB[0])**2 + (pointA[1] + pointB[1])**2 + (pointA[2] + pointB[2])**2)
    return magnitudeC

fare_rate = 0.40
pointA = (1, 2, 3)
pointB = (4, 5, 6)
trip_cost = resultant(pointA, pointB) * fare_rate

#%% 5.1.3 - Arguments, keywords, and defaults
def distance(pointA, pointB = (0, 0), metric = 'taxi'):
    """
    Return distance in city blocks between points A and B. If metric is 'taxt' (or omitted), 
    use taxicab metric. Otherwise, use Euclidean distance.
        pointA = (x1, y1)
        pointB = (x2, y2)
    If pointB is omitted, use the origin.
    """
    if metric == 'taxi':
        interval = abs(pointB[0] - pointA[0])+ abs(pointB[1] - pointA[1])
    else:
        interval = np.sqrt( (pointB[0] - pointA[0])**2 + (pointB[1] - pointA[1])**2 )
    return interval

#%% 5.1.4 - Return values
def rotate_vector(vector, angle):
    """
    Rotate a two-dimensional vector through given angle.
        vector = (x, y)
        angle = rotation angle in radians (counterclockwise)
    Returns the image of a vector under rotation as a NumPy array.
    """
    rotation_matrix = np.array([[np.cos(angle), -np.sin(angle)],
                                [np.sin(angle), np.cos(angle)]])  
    return np.dot(rotation_matrix, vector)

vec = [1, 1]
theta = np.pi/2
r = rotate_vector(vec, theta)
x, y = rotate_vector(vec, theta)
_, z = rotate_vector(vec, theta)
first, *rest = rotate_vector(vec, theta)

#%% 5.1.5 - Fuctional programming
def running_average(x):
    """
    Return cumulative average of an array.
    """
    y = np.zeros(len(x))                    # Empty array to store result
    current_sum = 0.0                       # Running sum of elements of x
    for i in range(len(x)):
        current_sum += x[i]                 # Increment sum
        y[i] = current_sum / (i + 1.0)      # Update running average
    return y

#%% Your Turn 5B
from numpy.random import random as rng

num_steps = 500
x_step = rng(num_steps) > 0.5
y_step = rng(num_steps) > 0.5
x_step = 2 * x_step - 1
y_step = 2 * y_step - 1
x_position = np.cumsum(x_step)
y_position = np.cumsum(y_step)
plt.plot(x_position, y_position)
plt.axis('equal')

#%% 5.3 - Histograms and Bar Graphs
from numpy.random import random as rng

data = rng(100)
plt.hist(data)

counts, bin_edges, _ = plt.hist(data)

bin_size = bin_edges[1] - bin_edges[0]
new_widths = bin_size * counts/counts.max()
plt.bar(bin_edges[:-1], counts, width = new_widths, color = ['r','g','b'])

log2bins = np.logspace(-8, 0, num = 9, base = 2)
log2bins[0] = 0.0                   # Set first bin edge to zero instead of 1/256
plt.hist(data, bins = log2bins)

#%% 5.4 Contour Plots and Surfaces
from mpl_toolkits.mplot3d import Axes3D

x_vals = np.linspace(-3,3,21)
y_vals = np.linspace(0,10,11)
X, Y = np.meshgrid(x_vals, y_vals)
Z = np.cos(X) * np.sin(Y)

#plt.contour(X, Y, Z, 20)                                           # Normal
#cs = plt.contour(X, Y, Z, 10, linewidth = 3, colors = 'k')         # Labeled
#plt.clabel(cs, fontsize = 10)
plt.contourf(X, Y, Z, 20)                                           # Filled

ax = Axes3D( plt.figure() )                                         # Create 3D plotter attached to new figure
ax.plot_surface(X, Y, Z, rstride = 1, cstride = 1)                  # Generate 3D plot

#%% Your Turn 5D
from mpl_toolkits.mplot3d import Axes3D

x_vals = np.linspace(-1,1,10)
y_vals = np.linspace(-1,1,10)
X, Y = np.meshgrid(x_vals, y_vals)
Z = np.cos(X) * np.sin(Y)

ax = Axes3D( plt.figure() )
ax.plot_surface(X, Y, Z)

#%% 5.5.1 General real functions
import scipy.optimize as so
from scipy.optimize import fsolve

def f(x): return x**2 - 1
fsolve(f, 0.5)
fsolve(f, -0.5)
fsolve(f, [-0.5, 0.5])

def f(x): return np.sin(x)**10
fsolve(np.sin, 1)
fsolve(f, 1)




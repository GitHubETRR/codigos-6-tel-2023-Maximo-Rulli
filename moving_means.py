import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

df = pd.read_csv('students.csv')
del df['Unnamed: 0']

STUDENTS = len(df.index)

#Define same functions as in the jupyter notebook
def init_centers():
  return {'mu0':np.array([np.random.randint(0, 10), np.random.randint(0, 10)]), 'mu1': np.array([np.random.randint(0, 10), np.random.randint(0, 10)])}

def set_mu(X, mu, c):
  length = len(c)
  #For each student we assign a center, that'll be the closest one
  for i in range(length):
    c[i] = 'mu'+str(np.argmin(np.linalg.norm(X[i]-[i for i in mu.values()], axis=1)))
  return c

def move_mu(X, mu, c):
    #We define a mask to compute the avareage of the students marks and move the cluster center towards the mean
    for i in mu.keys():
        mask = np.array([j == i for j in c])
        mask = mask.reshape(150, 1)
        mean = np.sum(X*mask, axis=0)/np.sum(mask)
        mu[i] = mean
    return mu

#We run the whole animation 5 times with 5 different initializations
init = 0

#Get everything inside a forever loop to plot the progress visually
while init<5:
    #Initialize the students labels
    c = ['' for i in range(STUDENTS)]

    #Initialize cluster centers
    mu = init_centers()

    #Convert dataset to array and initialize variables for the centers
    X = df.to_numpy()
    c_new, c_act = c, []


    #Initialize plot
    fig, ax = plt.subplots(1, 1)
    ax.scatter(mu['mu0'][0], mu['mu0'][1], color='red', marker='x', label='Level A')
    ax.scatter(mu['mu1'][0], mu['mu1'][1], color='green', marker='x', label='Level B')
    ax.scatter(X[:,0], X[:,1], color='blue', marker='o')
    ax.set_xlabel('Mark 1')
    ax.set_ylabel('Mark 2')
    ax.legend()
    plt.show(block=False)

    #Make the animated plot show how the centers update and the students get labeled
    while(not(np.array_equal(c_new, c_act))):
        #Update values of labels and clusters
        c_act = np.copy(c_new)
        c_new = np.copy(set_mu(X, mu, c_new))
        mu = move_mu(X, mu, c_new)

        #Plot the data updated
        plt.pause(3)
        ax.clear()
        ax.set_xlabel('Mark 1')
        ax.set_ylabel('Mark 2')
        ax.scatter(mu['mu0'][0], mu['mu0'][1], color='red', marker='x')
        ax.scatter(mu['mu1'][0], mu['mu1'][1], color='green', marker='x')

        mask1 = np.array([j == 'mu0' for j in c_new]).reshape(150,)
        mask2 = np.array([j == 'mu1' for j in c_new]).reshape(150,)
        ax.scatter(X[:,0]*mask1, X[:,1]*mask1, color='red', marker='o', label='Level A')
        ax.scatter(X[:,0]*mask2, X[:,1]*mask2, color='green', marker='v', label='Level B')  
        ax.legend()
        plt.draw()
    init+=1
plt.pause(10000)

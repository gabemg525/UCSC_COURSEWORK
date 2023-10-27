"""*******************************************
	python code for project 1 in
	CSE 107 in 2022 winter, UC Santa Cruz,
			for Prof. Chen Qian.
**********************************************
	Student name:
	UCSC email: ___@ucsc.edu
"""

import numpy as np
import matplotlib.pyplot as plt
import simplerandom.iterators as sri

"""
Make a scatter plot of the distribution for these three RNG.
You'll generate num = 10,000 random number in range [0, num).
Make a single scatter plot using matplotlib with the x-axis being 
index of number and the y-axis being the number.

Hint(s):
    1. You'll call plt.scatter(...) for each rng. 
    Make sure your calls are of the form:
    'plt.scatter(x_vals, y_vals, c = 'b', s=2)' where c = 'b' indicates
    blue and s = 2 is to set the size of points. You may want to use
    "r", "g", and "b", a different color for each rng.
    2. Use plt.savefig(...).
"""

def distribution_random():
    num = 10000
    x_axis = list(range(0,num))
    y_axis = list()
    np.random.seed(1)
    for i in range(num):
        rand_num = np.random.random()*10000
        y_axis.append(rand_num)

    plt.scatter(x_axis, y_axis, s=0.1)
    plt.title("np.random")
    plt.xlabel("index")
    plt.ylabel("random number")
    plt.savefig("random.png")
    plt.show()
    

def distribution_KISS():
    num = 10000
    rng_kiss = sri.KISS(123958, 34987243, 3495825239, 2398172431)
    x_axis = list(range(0,num))
    y_axis = list()
    for i in range(num):
        rand_num = next(rng_kiss)/42949.67296
        y_axis.append(rand_num)

    plt.scatter(x_axis, y_axis, s=0.1)
    plt.title("sri.KISS")
    plt.xlabel("index")
    plt.ylabel("random number")
    plt.savefig("sriKISS.png")
    plt.show()
    


def distribution_SHR3():
    num = 10000
    rng_shr3 = sri.SHR3(3360276411)
    x_axis = list(range(0,num))
    y_axis = list()
    for i in range(num):
        rand_num = next(rng_shr3)/429496.7296
        y_axis.append(rand_num)

    plt.scatter(x_axis, y_axis, s=0.1)
    plt.title("sri.SHR3")
    plt.xlabel("index")
    plt.ylabel("random number")
    plt.savefig("sriSHR3.png")
    plt.show()
    

def pingpong(n:int=21, p:float=0.3, ntrials:int=5000, seed:int=0):
    """
    Write code to simulate a ping pong game to n points,
    where the probability of you winning a single point is p.
    You must win by 2; for example, if the score is 21 - 20, 
    the game isn't over yet. Simulate ntrials # of games.
    :param n: The number of points to play to.
    :param p: The probability of YOU winning a single point.
    :param ntrials: The number of trials to simulate.
    :return: returns the probability YOU win the overall game.
    You can ONLY use the function np.random.random() to generate randomness; 
    this function generates a random float from the interval [0, 1).
    """

    def sim_one_game():
        #     """
        #     This is a nested function only accessible by parent sim_prob,
        #     which we're in now. You may want to implement this function!
        #     """
        pass # TODO: Your code here (10-20 lines)
        p1_points,p2_points,p1_p2_diff = 0,0,0
        while((p1_p2_diff<2 and p1_p2_diff>-2) or (p1_points<n and p2_points<n)):
            rand_num = np.random.random()
            if rand_num > p:
                p2_points+=1
                p1_p2_diff-=1
            else:
                p1_points+=1
                p1_p2_diff+=1
            #print("score: " + str(p1_points) + " - " + str(p2_points))
            #print("diff: " + str(p1_p2_diff))
        if(p1_points>p2_points):
            return True
        else:
            return False
    total_p1_wins = 0
    np.random.seed(seed)
    for i in range(ntrials):
        if sim_one_game() == True:
            total_p1_wins+=1

    #print("total wins: " + str(total_p1_wins) + " ntrials: " +str(ntrials))
    return total_p1_wins/ntrials


def plot_output():
    """
    Make a single plot using matplotlib with the x-axis being p
    for different values of p in {0, 0.04, 0.08,...,0.96, 1.0} 
    and the y-axis being the probability of winning the overall game 
    (use your previous function). Plot 3 "curves" in different colors, 
    one for each n in {3,11,21}.
    You can code up your solution here. Make sure to label your axes
    and title your plot appropriately, as well as include a 
    legend!
    Hint(s):
    1. You'll call plt.plot(...) 3 times total, one for each
    n. Make sure your calls are of the form:
    'plt.plot(x_vals, y_vals, "-b", label="n=11")' where "-b" indicates
    blue and "n=11" is to say these set of points is for n=11. You may 
    want to use "-r", "-g", and "-b", a different color for each n.
    2. Use plt.legend(loc="upper left").
    3. Use plt.savefig(...).
    :return: Nothing. Just save the plot you made!
    """
    
    pass # TODO: Your code here (10-20 lines)
    x_axis = range(0,100,4)
    y_axis1,y_axis2,y_axis3,x_ax = [],[],[],[]
    for p in x_axis:
        y_axis1.append(pingpong(3,p/100,5000,5))
    for p in x_axis:
        y_axis2.append(pingpong(11,p/100,5000,5))
    for p in x_axis:
        y_axis3.append(pingpong(21,p/100,5000,5))
    for p in x_axis:
        x_ax.append(p/100)
    plt.plot(x_ax, y_axis1, '-o')
    plt.plot(x_ax, y_axis2, '-o')
    plt.plot(x_ax, y_axis3, '-o')
    plt.title("Ping Pong")
    plt.xlabel("P(win point)")
    plt.ylabel("P(win game)")
    plt.legend(['n=3','n=11','n=21'])
    plt.show()


if __name__ == '__main__':
    # You can test out things here. Feel free to write anything below.
    distribution_random()
    distribution_KISS()
    distribution_SHR3()
    plot_output()
    

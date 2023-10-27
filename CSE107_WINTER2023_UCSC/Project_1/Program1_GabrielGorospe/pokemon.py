# =============================================================
# You may define helper functions, but DO NOT MODIFY
# the parameters or names of the provided functions.

# Do NOT add any import statements.
# =============================================================

import numpy as np
import simplerandom.iterators as sri

"""
The data for this problem is provided in pokemon.txt and follows the
following format.
Col 1: pokemon_id: A unique identifier for the Pokemon.
Col 2: is_legendary: A 1 if the Pokemon is legendary, and 0 otherwise.
Col 3: height: The height of the Pokemon in meters.
Col 4: weight: The weight of the Pokemon in kilograms.
Col 5: encounter_prob: The probability of encountering this Pokemon 
in the wild grass. Note the sum of this entire column is 1, since when
you make an encounter, exactly one of these Pokemon appears.
Col 6: catch_prob: Once you have encountered a Pokemon, the probability 
you catch it. (Ignore any mechanics of the actual game if you've played 
a Pokemon game in the past.)
"""

def part_a(filename:str='data/pokemon.txt'):
    """
    Compute the proportion of Pokemon that are legendary, the average
    height, the average weight, the average encounter_prob, and average 
    catch_prob. 
    :param filename: The path to the csv as described in the pset.
    :return: A numpy array of length 5 with these 5 quantities.
    Hint(s):
    1. Use np.genfromtxt(...) to load the file. Do NOT hardcode 
    'data/pokemon.txt' as the parameter as we may use other hidden
    files to test your function.
    2. Use np.mean(...) with its axis parameter to compute means in one line.
    """
    
    pass # TODO: Your code here (<= 3 lines)

    data = np.genfromtxt(filename,delimiter=" ")
    return [data[:,1].mean(),data[:,2].mean(),data[:,3].mean(),data[:,4].mean(),data[:,5].mean()]

def part_b(filename:str='data/pokemon.txt'):
    """
    Compute the proportion of Pokemon that are legendary, the average
    height, the average weight, the average encounter_prob, and average 
    catch_prob OF ONLY those Pokemon STRICTLY heavier than the median weight. 
    :param filename: The path to the csv as described in the pset.
    :return: A numpy array of length 5 with these 5 quantities.
    Hint(s):
    1. Use np.median(...) to compute medians along an axis.
    2. Use np.where(...) to select only certain rows.
    """
    pass # TODO: Your code here (<= 5 lines)
    
    data = np.genfromtxt(filename,delimiter=" ")
    rows = np.where(data[:,3]>np.median(data[:,3]))
    return [data[rows,1].mean(),data[rows,2].mean(),data[rows,3].mean(),data[rows,4].mean(),data[rows,5].mean()]
    

def part_c(filename:str='data/pokemon.txt', ntrials:int=5000):
    """
    Suppose you are walking around the wild grass, and you wonder: how
    many encounters do you expect to make until you ENCOUNTER each Pokemon 
    (at least) once? 
    :param filename: The path to the csv as described in the pset.
    :param ntrials: How many simulations to run.
    :return: The (simulated) average number of ENCOUNTERS you expect to 
    make, until you ENCOUNTER each Pokemon (at least) once.
    Hint(s):
    1. You only need to use one of the columns for this part!
    2. You may want to use np.random.choice(...) with the parameter a
    being np.arange(...) and the parameter p being the data column!
    """
    
    def sim_one():
        """
        This is a nested function only accessible by parent 'part_c',
        which we're in now. You may want to implement this function!
        """
        enc, total = 0,0

        enc_p = np.genfromtxt(filename,delimiter=" ")[:,4]
        I = np.arange(len(enc_p))
        pokedex = [False]*len(enc_p)
        while(total<len(enc_p)):
            found = np.random.choice(I,size=500,p=enc_p)
            for f in found:
                if pokedex[f]==False:
                    pokedex[f]=True
                    total+=1
                    if(total>=len(enc_p)):
                        return enc
                enc+=1
        return enc
        pass
    pass # TODO: Your code here (10-20 lines)
    
    encounters=0
    np.random.seed(1)
    for i in range(ntrials):
        # x=sim_one(id,e)
        # print(x)
        encounters+=sim_one()
    return encounters/ntrials
        



def part_d(filename:str='data/pokemon.txt', ntrials:int=5000):
    """
    Suppose you are walking around the wild grass, and you wonder: how
    many encounters do you expect to make until you CATCH each Pokemon 
    (at least) once? 
    :param filename: The path to the csv as described in the pset.
    :param ntrials: How many simulations to run.
    :return: The (simulated) average number of ENCOUNTERS you expect to 
    make, until you CATCH each Pokemon (at least) once.
    Hint(s):
    1. You only need to use two of the columns for this part!
    2. You may want to use np.random.choice(...) with the parameter a
    being np.arange(...) and the parameter p being the data column!
    3. You may want to use np.random.rand(...).
    """
    data = np.genfromtxt(filename)[:, -2:]
    n_pokemon = data.shape[0]
    
    def sim_one():
        """
        This is a nested function only accessible by parent 'part_d',
        which we're in now. You may want to implement this function!
        """
        enc, total = 0,0
        enc_p = np.genfromtxt(filename,delimiter=" ")[:,4]
        c_prob = np.genfromtxt(filename,delimiter=" ")[:,5]
        I = np.arange(len(enc_p))
        pokedex = [False]*len(enc_p)
        while(total<len(enc_p)):
            found = np.random.choice(I,size=2000,p=enc_p)
            for f in found:
                if pokedex[f]==False and c_prob[f]>np.random.rand():
                    pokedex[f]=True
                    total+=1
                    if(total>=len(enc_p)):
                        return enc
                enc+=1
        return enc
        pass
    pass # TODO: Your code here (10-20 lines)
    encounters=0
    np.random.seed(1)
    for i in range(ntrials):
        encounters+=sim_one()
    return encounters/ntrials

if __name__ == '__main__':
    # You can test out things here. Feel free to write anything below.
    print(part_a())
    print(part_b())
    print(part_c())
    print(part_d())

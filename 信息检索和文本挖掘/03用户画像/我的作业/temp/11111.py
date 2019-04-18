import numpy as np
import math
from datascience import *
data =Table.read_table('99999.csv')

data = data.relabeled(0,'s1').relabeled(1,'s2').relabeled(2,'s3').relabeled(3,'s4').relabeled(4,'s5').relabeled(5,'class').with_column('index', np.arange(len(data.column(0)))+1)
num_data = data.num_rows
num_train = int(num_data * 0.8)
num_test = num_data - num_train
train_data = data.take(np.arange(num_train))
test_data = data.take(np.arange(num_train, num_data)) 

def distance(test_row, train_rows):
    counts_matrix = np.asmatrix(train_rows.columns).transpose()
    diff = np.tile(np.array(test_row), [counts_matrix.shape[0], 1]) - counts_matrix
    np.random.seed(0) # For tie breaking purposes
    distances = np.squeeze(np.asarray(np.sqrt(np.square(diff).sum(1))))
    eps = np.random.uniform(size=distances.shape)*1e-10 #Noise for tie break
    distances = distances + eps
    return distances

def classify(test_row, train_rows, train_classes, k):
    distances = distance(test_row, train_rows)
    genre_and_distances = Table().with_columns('Class', train_classes, 'Distance', distances).sort(1)
    return genre_and_distances.take(np.arange(k)).group(0).sort(1, descending=True).column(0).item(0)


classify(test_data.row(0), train_data, train_data.column('class'), 5)

def classify_one_argument(row): 
    return classify(row, train_data, train_data.column('class'), 5) #k=5, and can be changed to any number

test_guesses = test_data.select('index', 'class').with_column('Prediction', test_data.apply(classify_one_argument), 'True or False', test_data.column('class')==test_data.apply(classify_one_argument))
proportion_correct = test_guesses.where('True or False', True).num_rows / test_guesses.num_rows
print(proportion_correct)
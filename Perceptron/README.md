# Perceptron Implementation
## Input
The input consists of 5 parts:
- Line 1: the dimensionality d of the dataset. For example, a dimensionality of 2 means that there are 2 inputs.
- Line 2: the size of the training set m.
- Line 3: the size of the test set n.
- Line 4 to line 4 + m: the list of m training examples. Each training example consists d comma-separated inputs and 1 output.
- Line 4 + m + 1 until end of file: the list of n test examples. Each test example consists of d comma-separated inputs only (no output).

## Output
- If linearly separable: For each of the n test examples, the output of the perceptron algorithm which you first trained on the training set. All outputs must be given on a separate line.
- If not linearly separable: a single line no solution found

# ID3 Implementation Decision Trees

## Input
ARFF Format. There are already in the folder.

## Output
Output consists of the hierarchical tree, one node per line. A node is either an internal node (a node with one or more children), or a leaf node.
These nodes should be shown in your output as follows:
- A leaf node is an ANSWER node, and should be shown in your output as: ANSWER: [output]. This is saying that the result of following the path gives the answer output (for example yes, no, maybe).
- An internal node is a decision node: [attribute]: [value]. For example: outlook: sunny. This means that the attribute outlook is set to sunny.
- All nodes need to be indented with 2 * depth spaces. So the decision nodes at root level are indented with 0 spaces, and a leaf node at depth 10 with 20 spaces.
- Decision nodes need to be ordered based on the occurrence of their value in the ARFF file. For example, if the attribute outlook appears in the ARFF file as @attribute outlook {sunny, overcast, rainy}, then the decision nodes for that attribute should appear in the order sunny, overcast and rainy.
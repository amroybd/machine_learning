# What does the converted table mean?
- Node number: The root node is 0 and then as we go down the associate node number increase
- Input feature index: We have 8 inputs as features. This index number is telling which feature is being used by the corresponding node
- Value to compare: This value is compared with the feature value
- Next node if true: Tells which node is next if the above comparison is true
- Next node if false: Tells which node is next if the above comparison is false
- is leaf: Tells you the current node is a leaf node or not
- Output: Tells you the output of the node. You will notice that some output is -1. That's because only leaf nodes have the outcomes of a given input. Other nodes 
- do not have any outcomes.
- If any cell has -1 that means that cell does not have any use to make predictions. For example Node number 3 is a leaf node. So here we are not comparing any feature
value with "Value to compare". So Input feature index is -1 here but the output has a value of 1 which is our desired outcome of the tree.

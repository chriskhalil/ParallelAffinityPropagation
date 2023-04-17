#Sparse Affinity Propagation (C++/CUDA)

Implementation of the affinitypropagation a clustering.An algorithm that identifies exemplars among data points and forms clusters of data points around these exemplars.
It operates by simultaneously considering all data point as potential exemplars and exchanging messages between data points until a good set of exemplars and clusters emerges.

Optimized for sparse similarity matrix.

<b>data point</b> (a.k.a. training case): One item of data; affinity propagation clusters data points

<b>exemplar</b>: A data point that is nicely representative of itself and some other data points.

<b>similarity</b>: The similarity of data point i to data point j, called s(i,j), is the suitability of point j to serve as the exemplar for data point i. If the data are real-valued, a common choice for similarity is negative Euclidean distance: s(i,j) = -(x(i)-x(j))(x(i)-x(j)). Affinity propagation can be applied using more general notions of similarity, and the similarities may be positive or negative. In fact, the output of the algorithm is unchanged if the similarities are scaled and/or offset by a constant (as long as the preferences are scaled and/or offset by the same constant).

<b>preference</b>: The preference of point i, called p(i) or s(i,i), is the a priori suitability of point i to serve as an exemplar. Preferences can be set to a global (shared) value, or customized for particular data points. High values of the preferences will cause affinity propagation to find many exemplars (clusters), while low values will lead to a small number of exemplars (clusters). A good initial choice for the preference is the minimum similarity or the median similarity.

<b>availability</b>: Messages sent from candidate exemplars (data points) to potential cluster members (data points), indicating how appropriate that candidate would be as an exemplar.

<b>responsibility</b>: Messages sent from cluster members (data points) to candidate exemplars (data points), indicating how well-suited the data point would be as a member of the candidate exemplar's cluster.

<b>net similarity</b>: A score of how appropriate the exemplars are for explaining the data. This is the objective function that affinity propagation tries to maximize.

</b>belief propagation</b>: An iterative algorithm (used in affinity propagation) for searching over and scoring configurations of variables in a graphical model. It is also referred to as the "sum-product algorithm". When it is applied to a graph with cycles, it is often referred to as "loopy belief propagation".

<b>sum-product and max-product algorithms</b>: Whereas the sum-product algorithm combines evidence by adding probabilities (scores), the max-product algorithm combines evidence by taking the largest probability (score).

<b>iteration</b>: In affinity propagation, a single iteration involves computing all responsibility messages based on the current availability messages, the input similarities and the input preferences, and then computing all availability messages based on the responsibility messages, which were just updated.

<b>damping / dampfact</b>: Computing responsibilities and availabilities according to simple update rules will often lead to oscillations caused by "overshooting" the solution, so the responsibility and availability messages are "damped" like this:

msgnew = (dampfact)(msgold) + (1-dampfact)(msgnew)

<b>clustering</b>: An unsupervised machine learning task that involves partitioning data into groups of similar data points.

<b>cluster</b>: One of the data point groups arising from clustering.

<b>convits and maxits</b>: Affinity propagation iteratively computes responsibilities and availabilities. The algorithm terminates if decisions for the exemplars and the cluster boundaries are unchanged for convits iterations, or if maxits iterations are reached.

Expected output from toyDataSet
2 2 2 2 2 2 6 6 6 6 2 6 2 6 6 19 19 19 19 19 19 2 19 19 6

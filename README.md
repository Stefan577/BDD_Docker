## Requirements
Python Version 3.11

## Overview
It's just a mesh together from BDDSampler (https://github.com/davidfa71/BDDSampler), Extended Logic (https://github.com/davidfa71/Extending-Logic) and dimagic(https://doi.org/10.5281/zenodo.12707100) with Docker to quickly generate BDDs from dimacs. 
BDDSampler, Extended Logic and dimagic are not from me. You can create BDDs in the dddmp Format and Sample them (random with replacement).

## Example
The 2 main functions are ``` convert_dimacs_to_bdd(dimacs_path, output_path) ```and ``` sample_bdd(num_samples, bdd_path) ```
```python
import os
from dimacs2BDD import *

num_of_samples = 10

dimacs_path = "/your/local/path/to/dimacs/system.dimacs"
bdd_path = "/your/local/path/to/bdd/system.dddmp"
# Create BDD if needed
if not os.path.exists(bdd_path):
  print(f"No BDD found ({bdd_path}), creating BDD")
  convert_dimacs_to_bdd(dimacs_path, os.path.dirname(bdd_path))
# Sampling
configurations = sample_bdd(num_of_samples, bdd_path)
# configurations looks like this: [[opt4, opt1, root, opt8],[opt2, opt4, root],...]
#if you have a list of features e.g: [root, opt1, opt2, opt3, opt4,...] use following code to get a binary array of configs:
features = [root, opt1, opt2, opt3, opt4,...]
num_configurations = len(configurations)
num_features = len(features)
binary_array = np.zeros((num_configurations, num_features), dtype=int)
        for i, config in enumerate(configurations):
            for feature in config:
                if feature in features:
                    feature_index = features.index(feature)
                    binary_array[i, feature_index] = 1

#if you only want unique_configurtions use
unique_configuations = np.unique(binary_array, axis=0)
```

# LCPA-BWT
Computing the Longest Common Prefix Array Based on the Burrows-Wheeler Transform.

http://www.fer.unizg.hr/predmet/bio/

# Installation
1. Clone this project to your local repository. This can be done using the following instruction:

    ```sh
    git clone https://github.com/mrlovre/LCPA-BWT
    ```

2. Compilation: position yourself inside the cloned repository, and compile the code using the supplied makefile:

    ```sh
    cd LCPA_BWT/Release
    make
    ```

# Usage
```sh
./Release/LCPA-BWT [< input_file] [> output_file]
```

# Generating test data
```sh
# clean the 'expected' folder
rm expected/*

# generate expected outputs using the baseline algorithm
for input in $(ls data); do ./Prefixes < data/$input > expected/$input; done
```

# Testing
```sh
# clean the out folder
rm out/*

# redirect each sample from data folder to stdin and stdout to out folder
for input in $(ls data); do ./Release/LCPA-BWT < data/$input > out/$input; done

# diff on each pair of expected values and values obtained using the LCPA-BWT algorithm
# this should produce no output if both files in each pair are the same
for input in $(ls data); do diff out/$input expected/$input; done
```

# LCPA-BWT
Computing the longest common prefix array based on the Burrows-Wheeler transform.

http://www.fer.unizg.hr/predmet/bio/

# Installation
1) Clone this project to your local repository.
	This can be done using the following instruction.
  ```sh
  	git clone https://github.com/mrlovre/LCPA-BWT
  ```
2) Compilation.
   Position yourself inside the cloned repository and compile the code.
   ```sh
  	cd LCPA_BWT/Release
  	make
  ```
3) Usage:
  ```sh
  	./LCPA-BWT < input_file
  ```
4) Test:
	```sh
	for input in $(ls data); do 
			./Release/LCPA-BWT < data/$input > out/$input; 
	done

	for input in $(ls data); do 
		diff out/$input expected/$input; 
	done
	```

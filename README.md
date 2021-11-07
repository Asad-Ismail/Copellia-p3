# Copellia-p3
Based on https://github.com/rzhang2285/Coppelia

# Updates
1) Updated Copellia scripts to support python 3.x instead of 2.x
2) Fixed klee-uclibc certificates issues
3) A Dockerfile which build all the requirements of python, llvm, clang, minisat, stp, verliator, klee-uclibc, klee andother useful tools to run the tool

# RUN
1) Build docker using "docker build -t $name_of_container ."
2) Run container in interactive mode "docker run -it --rm $name_of_container bash"
3) Test the one step using run using cd ../one_cycle && tb_cpu.sh
4) Test multistep cd script && ./multi.py

# TO DO
1) Update to support recent version of klee and llvm



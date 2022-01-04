# Copellia-p3
## [![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](https://github.com/Asad-Ismail/Copellia-p3/issues) [![Hits](https://hits.seeyoufarm.com/api/count/incr/badge.svg?url=https%3A%2F%2Fgithub.com%2FAsad-Ismail%2FCopellia-p3&count_bg=%2379C83D&title_bg=%23555555&icon=&icon_color=%23E7E7E7&title=hits&edge_flat=false)](https://hits.seeyoufarm.com)

Based on https://github.com/rzhang2285/Coppelia

## Updates
1) Updated Copellia scripts to support python 3.x instead of 2.x
2) Fixed klee-uclibc dependencies certificates 
3) A Dockerfile which build all the requirements of python, llvm, clang, minisat, stp, verliator, klee-uclibc, klee and other useful tools to run the tool

## RUN
1) Build docker using "docker build -t $name_of_container ."
2) Run container in interactive mode "docker run -it --rm $name_of_container bash"
3) Test the one step using run using cd ../one_cycle && tb_cpu.sh
4) Test multistep cd script && ./multi.py

## TO DO
1) Update to support recent version of klee and llvm



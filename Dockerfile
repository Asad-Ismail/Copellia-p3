FROM ubuntu:14.04

ENV DEBIAN_FRONTEND=noninteractive 

RUN apt-get update && apt-get install -y --no-install-recommends \
		ca-certificates \
		curl \
		wget \
       	build-essential \
        	libopenblas-dev \
        	nginx
        	

        	

RUN apt-get install -y git

RUN  apt-get install -y build-essential curl bison flex bc libcap-dev git cmake libboost-all-dev libncurses5-dev python-minimal python-pip unzip
# for terminal
RUN echo  "export CPLUS_INCLUDE_PATH=/usr/include/x86_64-linux-gnu" >> ~/.bashrc
RUN echo "export CPLUS_INCLUDE_PATH=/usr/include/x86_64-linux-gnu" >> ~/.bashrc

RUN apt-get install -y libtcmalloc-minimal4 libgoogle-perftools-dev

RUN apt-get install -y software-properties-common

RUN add-apt-repository ppa:nilarimogard/webupd8
RUN apt-get update
RUN apt-get install -y launchpad-getkeys

RUN echo "deb http://apt.llvm.org/trusty/ llvm-toolchain-trusty main" >> /etc/apt/sources.list 
RUN wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key|sudo apt-key add -
RUN echo "deb-src http://apt.llvm.org/trusty/ llvm-toolchain-trusty main" >> /etc/apt/sources.list
RUN wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key|sudo apt-key add -

#RUN launchpad-getkeys
RUN apt-get update

#RUN sudo apt-get install -y clang-3.4 llvm-3.4 llvm-3.4-dev 

#RUN sudo ln -sf /usr/bin/llvm-config-3.4 /usr/bin/llvm-config


RUN mkdir llvm
WORKDIR llvm

RUN wget --no-check-certificate http://llvm.org/releases/3.4/llvm-3.4.src.tar.gz
RUN wget --no-check-certificate http://llvm.org/releases/3.4/compiler-rt-3.4.src.tar.gz
RUN wget --no-check-certificate https://releases.llvm.org/3.4/clang-3.4.src.tar.gz
RUN wget --no-check-certificate https://releases.llvm.org/3.4/clang-tools-extra-3.4.src.tar.gz

RUN tar zxvf ./llvm-3.4.src.tar.gz
RUN tar zxvf ./clang-3.4.src.tar.gz
RUN tar zxvf ./compiler-rt-3.4.src.tar.gz
RUN tar zxvf ./clang-tools-extra-3.4.src.tar.gz

RUN mv clang-3.4 clang
RUN mv clang llvm-3.4/tools/
RUN mv compiler-rt-3.4 compiler-rt
RUN mv compiler-rt llvm-3.4/projects/
RUN mv clang-tools-extra-3.4  clang-tools-extra
RUN mv clang-tools-extra llvm-3.4/tools/clang/tools 

RUN mkdir build
WORKDIR build

RUN ../llvm-3.4/configure --enable-shared --enable-targets=host-only

RUN make -j 3
RUN echo $?
RUN apt-get install -y groff
RUN make install


WORKDIR ../

RUN git clone https://github.com/stp/minisat.git
WORKDIR minisat
RUN mkdir build
WORKDIR build
RUN cmake -DSTATICCOMPILE=ON -DCMAKE_INSTALL_PREFIX=/usr/ ../
RUN sudo make install
WORKDIR ../../
RUN git clone https://github.com/stp/stp.git
WORKDIR stp
RUN git checkout tags/2.1.2
RUN mkdir build
WORKDIR build

RUN cmake -DBUILD_SHARED_LIBS:BOOL=OFF -DENABLE_PYTHON_INTERFACE:BOOL=OFF ..
RUN make
RUN sudo make install
WORKDIR ../../
RUN ulimit -s unlimited

RUN apt-get install -y vim

# GET gtests
RUN curl -OL https://src.fedoraproject.org/repo/pkgs/gtest/gtest-1.7.0.zip/2d6ec8ccdf5c46b05ba54a9fd1d130d7/gtest-1.7.0.zip  
RUN unzip gtest-1.7.0.zip  
WORKDIR gtest-1.7.0  
RUN cmake .  
RUN make  
WORKDIR ..



ENV PYTHON_VERSION=3.6
ENV LANG=C.UTF-8 LC_ALL=C.UTF-8
ENV PATH /opt/conda/bin:$PATH

RUN wget --quiet https://repo.anaconda.com/miniconda/Miniconda3-4.5.12-Linux-x86_64.sh -O ~/miniconda.sh && \
    /bin/bash ~/miniconda.sh -b -p /opt/conda && \
    rm ~/miniconda.sh 
   
   
ENV PYTHONUNBUFFERED=TRUE
ENV PYTHONDONTWRITEBYTECODE=TRUE

RUN pip install wllvm

#RUN git clone https://github.com/klee/klee-uclibc.git  
#WORKDIR klee-uclibc  
#RUN ./configure --make-llvm-lib  
#RUN make -j2  
#WORKDIR .. 

RUN apt-get install -y autoconf bison build-essential libssl-dev libyaml-dev libreadline6 libreadline6-dev zlib1g zlib1g-dev

#RUN git clone https://github.com/klee/klee.git
#WORKDIR klee
#RUN git checkout v1.3.0
#RUN ./configure --with-stp=../stp/build/ --with-uclibc=full-path-to-klee-uclibc --enable-posix-runtime
#RUN make
#RUN make install
#WORKDIR ..

# build verilator
RUN git clone http://git.veripool.org/git/verilator
WORKDIR verilator
RUN git checkout v3.900
RUN autoconf
RUN ./configure
RUN make
RUN make install
WORKDIR ..

COPY Coppelia Coppelia
COPY klee-uclibc klee-uclibc

# build klee-uclibc
WORKDIR klee-uclibc  
RUN ./configure --make-llvm-lib  
RUN make -j2  
WORKDIR .. 

# build klee
WORKDIR Coppelia/klee
RUN ./configure --with-stp=/llvm/stp/build --with-uclibc=/llvm/klee-uclibc --enable-posix-runtime
RUN make
RUN make install
WORKDIR ../../


RUN mv /usr/local/share/verilator/include/verilated.mk /usr/local/share/verilator/include/verilated.mk.bak
RUN cp Coppelia/verilator/verilated.mk /usr/local/share/verilator/include
RUN export LLVM_COMPILER=clang
# for terminal
RUN echo "export LLVM_COMPILER=clang" >> ~/.bashrc
#fix symbolic link
RUN ln -s /usr/local/lib/libkleeRuntest.so /usr/local/lib/libkleeRuntest.so.1.0
RUN sudo ldconfig
WORKDIR Coppelia/script
#RUN ./multi.py




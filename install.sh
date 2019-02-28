#!/bin/bash

which python >> /dev/null || (echo "You need to have python installed first, you can use 'brew install python' for instance." || exit 0)
# pip install
which pip >> /dev/null
if [ $? == 1 ]; then
    curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py
    python get-pip.py --user
    rm get-pip.py
	echo -e "\033[0;31mIn order to finish the install script you need to add the path to the pip binary to your PATH env variable.\033[0m"
    exit 0;
fi

# GLAD install
which glad >> /dev/null || pip install glad --user
if [[ ! -d "./libs/srcs/glad" && ! -d "./libs/includes/glad" && ! -d "./libs/includes/KHR" ]]; then
    glad --api gl=4.1 --profile=core --generator=c --out-path=tmp-glad
    mkdir -p ./libs/srcs/glad
    mv tmp-glad/src/glad.c ./libs/srcs/glad/glad.cpp
    mkdir -p ./libs/includes/glad
    mv tmp-glad/include/glad/glad.h ./libs/includes/glad
    mkdir -p ./libs/includes/KHR
    mv tmp-glad/include/KHR/khrplatform.h ./libs/includes/KHR
    rm -rf tmp-glad
fi

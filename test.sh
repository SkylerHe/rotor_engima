#!/bin/bash

#
#
#  Test Script.  Used for testing the solution.  
#
#  DO NOT MODIFY THIS FILE.
#


export CFLAGS="-Wall -Wextra -Wno-unused"

red=''
green=''
nc=''

base=$(dirname $0)


function tobase(){
    cd $(dirname $0)
}

function utest( ){
    ret=0
    if [ "$1" == "$2" ]
    then
	echo -ne "$green pass $nc"
    else
	echo -ne "$red FAIL $nc"
        ret=1
    fi
    echo -ne "\t\t "
    echo "$3"
    return $ret
}

function utest_ne( ){
    ret=0
    if [ "$1" != "$2" ]
    then
	echo -ne "$green pass $nc"
    else
	echo -ne "$red FAIL $nc"
        ret=1
    fi

    echo -ne "\t\t "
    echo "$3"
    return $ret
}

function utest_nz( ){
    ret=0
    if [ ! -z "$1" ]
    then
	echo -ne "$green pass $nc" 
    else
	echo -ne "$red FAIL $nc"
        ret=1
    fi
    echo -ne "\t\t "
    echo "$2"
    return $ret
}

function utest_z( ){
    ret=0
    if [ -z "$1" ]
    then
	echo -ne "$green pass $nc" 
    else
	echo -ne "$red FAIL $nc"
        ret=1
    fi
    echo -ne "\t\t "
    echo "$2"
    return $ret

}



function dodiff(){
    if [ "$1" == "1" ]
    then
        echo
        echo -e "\t\t\t --------- DIFF ---------"
        echo -e "your output \t\t\t\t\t\t\t expected output"
        echo -e "----------- \t\t\t\t\t\t\t ---------------"
        echo "$2" > res
        echo "$3" > expect
        diff -y res expect
        rm -f res expect
        echo
    fi
}


function test_enigma( ){
    rm -f comms
    cmd="g++ -Wall usage.cpp comms.cpp Enigma.cpp Rotor.cpp -o comms 2>&1"
    res=$(eval $cmd)
    utest_z "$res" "Compiles without warnings or errors ($cmd)"

    if [ ! -z "$res" ]
    then
	echo
	echo "--- ERRORS --- "
	echo "$res"
	echo
    fi


    echo
    echo "- encryption"
    echo
    
    cmd="echo AAA | ./comms 1 2 3 \"###\" encrypt"
    res=$(eval $cmd)
    expect="NDU"
    utest "$res" "$expect" "Simple encryption ($cmd)"
    dodiff "$?" "$res" "$expect"


    cmd="echo -n DO#YOUR#BEST#AND#KEEP#ON#KEEPIN#ON | ./comms 3 1 2 \"SAT\" encrypt"
    res=$(eval $cmd)
    expect="ACAAFAEOZFWKBQKPXZOGIKXTNPEBDXWQCZ"
    utest "$res" "$expect" "Medium encryption ($cmd)"
    dodiff "$?" "$res" "$expect"

    cmd="echo -n THE#NATIONAL#ANIMAL#OF#SCOTLAND#IS#THE#UNICORN | ./comms 5 2 4 \"EST\" encrypt"
    res=$(eval $cmd)
    expect="CSHIAWDFGDCOE#EZKJHRWAZDDCBCILON#PKUJEXEXSHINZ"
    utest "$res" "$expect" "Medium encryption 2 ($cmd)"
    dodiff "$?" "$res" "$expect"



    cmd="echo \"ONCE#UPON#A#MIDNIGHT#DREARY#WHILE#I#PONDERED#WEAK#AND#WEARY#OVER#MANY#A#QUAINT#AND#CURIOUS#VOLUME#OF#FORGOTTEN#LORE#WHILE#I#NODDED#NEARLY#NAPPING#SUDDENLY#THERE#CAME#A#TAPPING#AS#OF#SOME#ONE#GENTLY#RAPPING#RAPPING#AT#MY#CHAMBER#DOOR#TIS#SOME#VISITOR#I#MUTTERED#TAPPING#AT#MY#CHAMBER#DOOR#ONLY#THIS#AND#NOTHING#MORE\" | ./comms 5 1 3 \"POE\" encrypt"
    res=$(eval $cmd)
    expect="OEXPDPUSICJHFQMMKAKQQQCLRXXWV#UUWKDPQOEJPLUTYXDJNXDXBGHOU##XGZSOWUSLYVB#RALNUDDKDKPCQRCI#GIVHROQYMWKGPFIV#K#CMGKFIRFEJDDFUNZJYDTZYCNIOUSLITEODLSRBECGWBLUNKPOFBKZMXDL#GEJAK#HONYEQSBQMPLPXLVLIXRCMWKDAYXGWDKJURQ#PXDCNUHJHGDRHPWJTPXXWLOWAEDFIEIQERPOUVPS#TECFODEAJINSJTIQXWGNCCA#XKAIPCMIQQPEHPZPYROTSMLPWPUZJYIHBIHSQRUC"
    utest "$res" "$expect" "Large encryption ($cmd)"
    dodiff "$?" "$res" "$expect"

    echo
    echo "- decryption"
    echo
    

    cmd="echo NDU | ./comms 1 2 3 \"###\" decrypt"
    res=$(eval $cmd)
    expect="AAA"
    utest "$res" "$expect" "Simple decryption ($cmd)"
    dodiff "$?" "$res" "$expect"


    cmd="echo -n ACAAFAEOZFWKBQKPXZOGIKXTNPEBDXWQCZ | ./comms 3 1 2 \"SAT\" decrypt"
    res=$(eval $cmd)
    expect="DO#YOUR#BEST#AND#KEEP#ON#KEEPIN#ON"
    utest "$res" "$expect" "Medium decryption 1 ($cmd)"
    dodiff "$?" "$res" "$expect"



    cmd="echo -n CSHIAWDFGDCOE#EZKJHRWAZDDCBCILON#PKUJEXEXSHINZ | ./comms 5 2 4 \"EST\" decrypt"
    res=$(eval $cmd)
    expect="THE#NATIONAL#ANIMAL#OF#SCOTLAND#IS#THE#UNICORN"
    utest "$res" "$expect" "Medium decryption 2 ($cmd)"
    dodiff "$?" "$res" "$expect"




    cmd="echo \"OEXPDPUSICJHFQMMKAKQQQCLRXXWV#UUWKDPQOEJPLUTYXDJNXDXBGHOU##XGZSOWUSLYVB#RALNUDDKDKPCQRCI#GIVHROQYMWKGPFIV#K#CMGKFIRFEJDDFUNZJYDTZYCNIOUSLITEODLSRBECGWBLUNKPOFBKZMXDL#GEJAK#HONYEQSBQMPLPXLVLIXRCMWKDAYXGWDKJURQ#PXDCNUHJHGDRHPWJTPXXWLOWAEDFIEIQERPOUVPS#TECFODEAJINSJTIQXWGNCCA#XKAIPCMIQQPEHPZPYROTSMLPWPUZJYIHBIHSQRUC\" | ./comms 5 1 3 \"POE\" decrypt"
    res=$(eval $cmd)
    expect="ONCE#UPON#A#MIDNIGHT#DREARY#WHILE#I#PONDERED#WEAK#AND#WEARY#OVER#MANY#A#QUAINT#AND#CURIOUS#VOLUME#OF#FORGOTTEN#LORE#WHILE#I#NODDED#NEARLY#NAPPING#SUDDENLY#THERE#CAME#A#TAPPING#AS#OF#SOME#ONE#GENTLY#RAPPING#RAPPING#AT#MY#CHAMBER#DOOR#TIS#SOME#VISITOR#I#MUTTERED#TAPPING#AT#MY#CHAMBER#DOOR#ONLY#THIS#AND#NOTHING#MORE"
    utest "$res" "$expect" "Large Decryption ($cmd)"
    dodiff "$?" "$res" "$expect"

    
    
}


if [ ! -z $1 ]
then
    cd $1
else
    cd $(dirname $0)
fi

echo

test_enigma
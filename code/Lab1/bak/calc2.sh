#!/bin/bash
findr=`find . -name result.txt`
if [ -z "$findr" ]
then
	touch result.txt
fi	
read -p ">>" pa1 math pa2

while [[ $pa1 != "EXIT" ]] ; do
	
	if [ -z $pa1 ]
	then
		continue
	fi
	
#	if [ -z $math ]
#	then
#		echo "SYNTAX ERROR"	
#	fi
#	echo $pa1
	if [ $pa1 == "ANS" ]
	then 
		lastLine=`tail -1 result.txt`;
		equalChar=`expr index "$lastLine" =`;
		lastRes=`expr $equalChar + 1`;
		pa1=${lastLine:$lastRes};
	fi

	if [[ $pa1 -eq "HIST" ]]
	then
		tail -5 result.txt
		read -p ">>" pa1 math pa2
		continue
	fi
	case $math in
		%)
		if [ $pa2 == 0 ]
		then
			echo "MATH ERROR"
		else
			res=`echo "scale=0; $pa1 / $pa2" | bc`
		fi
		;;

		/)
		if [ $pa2 == 0 ]
		then
			echo "MATH ERROR"
		else
			res=`echo "scale=2; $pa1 / $pa2" | bc`
		fi
		;;
		
		\*)res=`echo "$pa1 * $pa2" | bc`
		;;

		-)res=`echo "$pa1 - $pa2" | bc`
		;;

		+)res=`echo "$pa1 + $pa2" | bc`
		;;

		*)echo "SYNTAX ERROR"
		read -p ">>" pa1 math pa2
		continue		
		;;
	esac
	echo $res
	if [[ $math == "*" ]]
	then
		echo "$pa1 "*" $pa2 = $res" >> result.txt
	else 
		echo "$pa1 $math $pa2 = $res" >> result.txt
	fi
	read -p ">>" pa1 math pa2
done

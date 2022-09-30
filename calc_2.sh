# ! /bin/bash
# file calculator

# Create save file if not present

FILE=calc_data.txt

if test -f "$FILE"; then
    echo "ANS exists."
	# Clean HIST data but keep ANS
	sed -i '2,$d' $FILE
	else
	# Create local save file
	echo "ANS not exist"
	echo 0 > calc_data.txt
fi

checkIfANS(){
	# Check if ANS is used with operators
	if [[ $a == "ANS" ||  $a == "ans" ]]
	then
		a=$ANS
		flag1=1
	fi
	if [[ $c == "ANS" ||  $c == "ans" ]]
	then
		c=$ANS
		flag2=1
	fi
}

SavenUpdate(){
	# Save the ANS
	sed -i "1s/.*/$res/" $FILE
	# Save to HIST
	if [[ $flag1 == 1 ]]
	then
		a="ANS"
	fi
	if [[ $flag2 == 1 ]]
	then
		c="ANS"
	fi
	echo "$a $b $c = $res" >> $FILE
	#Update counter and flags
	(( count += 1 ))
	flag1=0;
	flag2=0;
	if [[ $count -ge 6 ]]
	then
		#Delete the 2 second line
		sed -i '2d' $FILE
		count=6
	fi
}

# Take user Input
read -p ">> "  a b c

count=0
ANS=$(head -n 1 $FILE)
flag1=0
flag2=0

while [[ $a != "EXIT" && $a != "exit" ]] ; do
	# Switch Case to perform
	# calculator operations
		if [[ -z "$b" ]]
		then
			case $a in
			ANS|ans)
				res=$(head -n 1 $FILE)
			;;
			HIST|hist) 
				res=`tail +2 $FILE`
			;;
			*)
				res="SYNTAX ERROR"
			esac
		else
			ANS=`head -n 1 $FILE`
			checkIfANS a c flag1 flag2
			case $b in
			+)
				res=`echo $a + $c | bc`
				# Save and Update
				SavenUpdate res $FILE a b c
			;;
			-)
				res=`echo $a - $c | bc`
				# Save and Update
				SavenUpdate res $FILE a b c
			;;
			/)
				if [[ $c -le 0 ]]
				then
					res="MATH ERROR"
				else
					res=`echo "scale=2; $a / $c" | bc`
					# Save and Update
					SavenUpdate res $FILE a b c
				fi
			;;
			%)
				if [[ $c -le 0 ]]
				then
					res="MATH ERROR"
				else
					res=`echo "scale=0; $a / $c" | bc`
					# Save and Update
					SavenUpdate res $FILE a b c
				fi
			;;
			x)
				res=`echo $a \* $c | bc`
				#Save and Update
				SavenUpdate res $FILE a b c
			;;
			*)
				res="SYNTAX ERROR"
			esac
		fi
	# Show result
	echo "$res"
	read -p ">> " a b c
done

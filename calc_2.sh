# ! /bin/bash

# read input file
read -p ">> " num1 operator num2

# check and create log file
FILE=~/temp.log
CreateLogFile()
{
    if [[ ! -f "$FILE" ]]; then
        touch $FILE
        chmod -R 755 $FILE
        echo 0 > $FILE
    else
        sed -i '2,$d' $FILE
    fi
}
CreateLogFile $FILE

CheckAnsVar(){
    if [[ $num1 == "ANS" || $num1 == "ans" ]]; then
        num1=$ANS
        flag1=1
    fi

    if [[ $num2 == "ANS" || $num2 == "ans" ]]; then
        num2=$ANS
        flag2=1
    fi
}

WriteToFile(){
    sed -i "1s/.*/$result/" $FILE
    if [[ $flag1 == 1 ]]; then
        num1="ANS"
    fi

    if [[ $flag2 == 1 ]]; then
        num2="ANS"
    fi

    echo "$num1 $operator $num2 = $result" >> $FILE
    flag1=0;
    flag2=0;
    (( count += 1 ))

    if [[ $count -ge 6 ]]; then
        sed -i '2d' $FILE
        count=6
    fi
}

ANS=$(head -n 1 $FILE)
flag1=0
flag2=0
count=0

# process
while [[ $num1 != "EXIT" ]] ; do
    if [[ -z $num1 ]]; then
        echo "SYNTAX ERROR"

    elif [[ -z "$operator" ]]; then
        case $num1 in
        ANS)
            result=$(head -n 1 $FILE)
        ;;
        HIST) 
            result=`tail +2 $FILE`
        ;;
        *)
            result="SYNTAX ERROR"
        esac
    else
        ANS=`head -n 1 $FILE`
        CheckAnsVar num1 num2 flag1 flag2
        case $operator in
        \+|+)
            result=`echo $num1 + $num2 | bc`
            WriteToFile result $FILE num1 operator num2
        ;;
        \-|-)
            result=`echo $num1 - $num2 | bc`            
            WriteToFile result $FILE num1 operator num2
        ;;
        \*|x)
            result=`echo $num1 \* $num2 | bc`
            WriteToFile result $FILE num1 operator num2
        ;;
        \/|/)
            if [[ $num2 -le 0 ]]; then
                echo "MATH ERROR"
            else
                result=`echo "scale=2; $num1 / $num2" | bc`
                WriteToFile result $FILE num1 operator num2
            fi
        ;;
        \%|%)
            if [[ $num2 -le 0 ]]; then
                echo "MATH ERROR"
            else
                result=`echo "scale=0; $num1 / $num2" | bc`
                WriteToFile result $FILE num1 operator num2
            fi
        ;;
        *)
            echo "SYNTAX ERROR"
        esac
    fi
    echo "$result"
    read -p ">> " num1 operator num2
done

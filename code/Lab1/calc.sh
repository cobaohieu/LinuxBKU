#! /bin/bash

# Read input file
read -p ">> " num1 operator num2

# Check and create temp file
FILE=~/tmp.log
CreateHistFile()
{
    if [[ ! -f "$FILE" ]]; then
        touch $FILE
        chmod -R 755 $FILE
    fi
}
CreateHistFile $FILE
FILE2=~/ans.log
CreateAnsFile()
{
    if [[ ! -f "$FILE2" ]]; then
        touch $FILE2
        chmod -R 755 $FILE2
        echo 0 > ans.log
    fi
}
CreateAnsFile $FILE2

temp="0"

# Process calculator
while [[ $num1 != "EXIT" && $num1 != "exit" ]]; do
    if [[ -z $num1 ]]; then
        echo "SYNTAX ERROR"
    elif [[ ! -z $num1 ]]; then
        if [[ -z $operator ]] && [[ -z $num2 ]]; then
            case $num1 in 
                "HIST"|"hist")
                    tail -5 $FILE
                ;;
                "ANS"|"ans")
                    tail -n -1 $FILE > $FILE2
                    awk -v FPAT=':[^|]*' '{print $5}' $FILE2
                    tail -n -1 $FILE2
                ;;
                *)
                    echo "SYNTAX ERROR"
                ;;
            esac
        else
            ANS=`tail -n -1 $FILE2`
            ans=$ANS
            if [[ $num1 == "ANS" ]]; then
                num1=$ANS
            fi
            case $operator in
                \+|+)
                    result=`echo "$num1 + $num2" | bc`
                    echo "Result: $result"
                    echo "$num1 $operator $num2 = $result" >> $FILE
                    ANS=`echo $result > $FILE2`
                ;;
                \-|-)
                    result=`echo "$num1 - $num2" | bc`
                    echo "Result: $result"
                    echo "$num1 $operator $num2 = $result" >> $FILE
                    ANS=`echo $result > $FILE2`
                ;;
                \*|x)
                    result=`echo "$num1 * $num2" | bc`
                    echo "Result: $result"
                    echo "$num1 $operator $num2 = $result" >> $FILE
                    ANS=`echo $result > $FILE2`
                ;;
                \/|/)
                    if [[ $num2 -le 0 ]]; then
                        echo "MATH ERROR"
                    else
                        result=`echo "scale=2; $num1 / $num2" | bc`
                    fi
                    echo "Result: $result"
                    echo "$num1 $operator $num2 = $result" >> $FILE
                    ANS=`echo $result > $FILE2`
                ;;
                \%|%)
                    result=`echo "scale=0; $num1 / $num2" | bc`
                    echo "Result: $result"
                    echo "$num1 $operator $num2 = $result" >> $FILE
                    ANS=`echo $result > $FILE2`
                ;;
                *)
                    echo "SYNTAX ERROR"
                ;;
            esac
            ANS=`echo $result > $FILE2`
        fi
    else
        echo "SYNTAX ERROR"
    fi
    temp=`echo $result > $FILE2`
    read -p ">> " num1 operator num2
done
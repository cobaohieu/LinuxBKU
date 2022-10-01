#! /bin/bash

# read input file
read -p ">> " num1 operator num2

# check and create temp file
FILE=~/tmp.log
create_file()
{
    if [[ ! -f "$FILE" ]]; then
        touch $FILE
        chmod -R 755 $FILE
    fi
}
create_file $FILE
FILE2=~/ans.log
create_file()
{
    if [[ ! -f "$FILE2" ]]; then
        touch $FILE2
        chmod -R 755 $FILE2
        echo 0 > ans.log
    # else
    #     tail -n -1 $FILE > $FILE2
    #     awk -v FPAT=':[^|]*' '{print $5}' $FILE2
    fi
}
create_file $FILE2
temp="0"
# process
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
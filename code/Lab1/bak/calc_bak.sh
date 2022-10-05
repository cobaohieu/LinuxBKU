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
    else
        tail -n -1 $FILE > $FILE2
        awk -v FPAT=':[^|]*' '{print $5}' $FILE2
    fi
}
create_file $FILE2

checkANS()
{
    # Check if ANS is used with operators
    if [[ $num1 == "ANS" ||  $num1 == "ans" ]]
    then
        num1=$ANS
        flag1=1
    fi
    if [[ $num2 == "ANS" ||  $c == "ans" ]]; then
        num2=$ANS
        flag2=1
    fi
}

SavenUpdate(){
    # Save the ANS
    sed -i "1s/.*/$res/" $FILE2
    # Save to HIST
    if [[ $flag1 == 1 ]]
    then
        num1="ANS"
    fi
    if [[ $flag2 == 1 ]]
    then
        num2="ANS"
    fi
    echo "$num1 $operator $num2 = $result" >> $FILE
    #Update counter and flags
    (( count += 1 ))
    flag1=0;
    flag2=0;
}

ANS=$(tail -n -1 $FILE)
flag1=0
flag2=0

# process
while [[ $num1 != "EXIT" && $num1 != "exit" ]]; do
    if [[ -z $num1 ]]; then
        echo "SYNTAX ERROR"
    elif [[ ! -z $num1 ]]; then
        if [[ -z $operator ]] && [[ -z $num2 ]]; then
            case $num1 in 
                HIST|hist)
                    tail -5 $FILE
                ;;
                '')
                    echo 'ERROR: SYNTAX ERROR'
                ;;
                # [+-]0)
                #     echo 'ERROR: zero should not be signed'
                # ;;
                ANS|ans)
                    tail -n -1 $FILE2
                    # awk -v FPAT=':[^|]*' '{print $5}' $FILE2
                    # result=`cat $FILE2`
                ;;
                *)
                    echo "SYNTAX ERROR"
                ;;
            esac
        else
            # ANS=`awk -v FPAT=':[^|]*' '{print $5}' $FILE2`
            # ANS=`cat $FILE2`
            checkANS num1 num2 flag1 flag2
            # ans=$ANS
            # echo $ans
            case $operator in
                \+|+)
                    result=`echo "$num1 + $num2" | bc`
                    echo "Result: $result"
                    SavenUpdate  result $FILE $FILE2 $num1 $operator $num2
                    # echo "$num1 $operator $num2 = $result" >> $FILE
                    # echo "$result" > $FILE2
                ;;
                \-|-)
                    result=`echo "$num1 - $num2" | bc`
                    echo "Result: $result"
                    SavenUpdate  result $FILE $FILE2 $num1 $operator $num2
                    # echo "$num1 $operator $num2 = $result" >> $FILE
                    # echo "$result" > $FILE2
                ;;
                \*|x)
                    result=`echo "$num1 * $num2" | bc`
                    echo "Result: $result"
                    SavenUpdate  result $FILE $FILE2 $num1 $operator $num2
                    # echo "$num1 $operator $num2 = $result" >> $FILE
                    # echo "$result" > $FILE2
                ;;
                \/|/)
                    if [[ $num2 -le 0 ]]; then
                        echo "MATH ERROR"
                    else
                        result=`echo "scale=2; $num1 / $num2" | bc`
                    fi
                    echo "Result: $result"
                    SavenUpdate  result $FILE $FILE2 $num1 $operator $num2
                    # echo "$num1 $operator $num2 = $result" >> $FILE
                    # echo "$result" > $FILE2
                ;;
                \%|%)
                    result=`echo "scale=0; $num1 / $num2" | bc`
                    echo "Result: $result"
                    SavenUpdate  result $FILE $FILE2 $num1 $operator $num2
                    # echo "$num1 $operator $num2 = $result" >> $FILE
                    # echo "$result" >> $FILE2
                ;;
                *)
                    echo "SYNTAX ERROR"
                ;;
            esac
            # awk -v FPAT=':[^|]*' '{print $5}' $FILE2
        fi
    else
        echo "SYNTAX ERROR"
    fi

    # echo "$result" >> $FILE2
    # tail -n 1 $FILE > $FILE2
    # awk -v FPAT=':[^|]*' '{print $5}' $FILE2
    read -p ">> " num1 operator num2
done
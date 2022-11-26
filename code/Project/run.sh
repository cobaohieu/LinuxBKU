#!/bin/bash

main() {

    #TODO: Implement menu - https://linuxize.com/post/bash-select/
    while true; do

        options=('Install device' 'View info' 'Write a string device' 'Write empty string 2 device' 'View dmesg' 'Clean device' 'Quit')

        echo "Enter your choice below: "
        select opt in "${options[@]}"
        do
            case $opt in
                "Install device"|"1")
                    make
                    sudo make install
                    sudo insmod mychardev.ko
                    break
                    ;;
                "View info"|"2")
                    modinfo mychardev.ko
                    cat /dev/mychardev
                    break
                    ;;
                "Write a string device"|"3")
                    read -p "Please type some string: " input
                    echo "$input" > /dev/mychardev-1
                    break
                    ;;
                "Write empty string 2 device"|"4")
                    echo "" > /dev/mychardev-1
                    break
                    ;;
                "View dmesg"|"5")
                    sudo dmesg
                    # sudo dmesg | tail
                    break
                    ;;
                "Clean device"|"6")
                    make clean
                    sudo make uninstall
                    sudo rmmod mychardev
                    break
                    ;;
                "Quit"|"7")
                    break 2 ;;
                *) echo "invalid option $REPLY";;
            esac
        done
    done
}

echo "Auto setup script device..."
main
echo "Done."

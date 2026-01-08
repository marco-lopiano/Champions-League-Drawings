min=1
max=99999999

if [ "$1" = "" ]; then
    ./main 
else
    for i in $(seq 0 $(($1 - 1)));
    do
        seed=$(($RANDOM%($max-$min+1)+$min))
        ./main $seed
    done
fi
# A simple script that runs in a command ("_comm_") in parallel.
# The command runs "cpus" simultateus times, while he total times the command runs is (cpus * N_batches + R_batches)



#Usage:
# paralllel_run.sh  command cpus N_N_batches R_batches

#Example:
# If you want to run "math -script Test.wl" 11 times in 4 cores, you run  
# paralllel_run.sh  "./a.out" 4 2 3

# the fourth is optional, and you can choose the name of the tmp files to write the result 

if [ "$#" -lt "4" ]
then
    echo "Number of parameters passed must be 4 or 5."
    echo "Usage:
            paralllel_run.sh command parallel N_baches R_baches "
    exit
fi


_comm_="$1"
cpus=$2
N_batches=$3
R_batches=$4

#N_batches must be larger than 1 
if [ "$N_batches" -lt 1 ]
then
    N_batches=1
fi




res_file=$5
if [ -z "$5" ] 
then
    res_file="/tmp/_tmp_par"

else
    touch $5"-1"  2>/tmp/err && rm $5"-1" || res_file="/tmp/_tmp_par-" 
fi
res_file=$res_file"_$$"
#the temporary file is res_file_$BASHPID_process_numer


#run the first batch:
total_ran=0
for i in $(seq 1 1 $cpus )
do      
    total_ran=$((total_ran+1))
    $_comm_ > $res_file"_$i" &
    pid[$i]=$!
done

#Keep launching new porcesses to continuue running "cpus" simultaneously
while true
do
    running=0 

    #check if a process is finnished  
    for i in $(seq 1 1 $cpus )
    do 
        if ps -p ${pid[i]} > /dev/null
        then
            running=$((running +  1))
        else
            #if its finnished, print the result and delete the tmp file (if result file exists)
            if test -f $res_file"_$i" 
            then 
                echo `cat $res_file"_$i"` 
                rm $res_file"_$i"
            fi

            #if the total number of runs (cpus*N_batches) is not finnished, and process $i is finnished, run a new on.
            if [ "$total_ran" -lt "$((cpus * N_batches + R_batches))" ]
            then

                total_ran=$((total_ran+1))
                $_comm_ > $res_file"_$i" &
                pid[$i]=$!
                running=$((running +  1))
            fi
        fi
    done
    
    
    # echo  "currently running: $running"
    
    #exit when 
    if [ "$running" = "0" ]
    then
        echo "finnished all $total_ran runs!!" 
        exit
    fi



done 




#!/usr/bin/env bash
BASE="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
cd "$BASE" || exit

BIN="./bin/pick-it-sales"
TESTDIR="./tests"
CASES="$TESTDIR/cases"
RESULTS="$TESTDIR/results"

year=$(date +'%Y')
month=$(date +'%m')
day=$(date +'%d')



compare_output() {
    local expected="$1"
    local result="$2"

    # fix newlines in the output file.
    sed -i -e 's/ERROR:/ERROR-/g; s/: /: \n/g; s/ERROR-/ERROR: /g' "$result"
    # sed -i '$a\' "$result"

    #compare them.
    results=$(diff --suppress-common-lines -y -Z -T -t "$expected" "$result")
    # results=$(cmp "$expected" "$result")
    echo "$results" >> "$SUMMARYFILE"

    if [ -z "$results" ]
    then
        # echo -e "$current_test\t\tPassed!"
        printf "%-25s \033[32m%s\033[0m\n" "$current_test" "PASSED!"
    else
        # echo -e "$current_test\t\tFailed!"
        printf "%-25s \033[31m%s\033[0m\n" "$current_test" "FAILED!"
    fi
    # echo -e "\n\nRESULTS:\n$results"
    # echo "Ran test"
}

run_test_case() {
    local filepath fullfilename filename testdir
    filepath="$1"
    fullfilename=$(basename -- "$filepath") || true
    # local extension="${fullfilename##*.}" || true
    filename="${fullfilename%.*}"
    testdir=$(dirname "$filepath")

    if [ ! -d "$resultdir/$casename" ]; then
        mkdir -p "$resultdir/$casename"
    fi


    (sed -e '$a\' "$filepath" | "$BIN") > "$resultdir/$casename/$filename.output"
    # (cat "$filepath" | "$BIN") >"$resultdir/$casename/$filename.output"
    # echo "before error"

    compare_output "$testdir/$filename.termout" "$resultdir/$casename/$filename.output"
}

parse_case() {
    # case=$(basename -- $1)
    local case="$1"
    # echo $case

    for file in $case/*.input; do
        current_test=$(basename $file)
        
        echo -e "--------------------------------------------------------------------------------------------------------------------------------" >> "$SUMMARYFILE"
        echo -e "\t\t\t\t\t\tStarting Test: $current_test" >> "$SUMMARYFILE"
        echo -e "--------------------------------------------------------------------------------------------------------------------------------" >> "$SUMMARYFILE"
        run_test_case "$file"
    done

    # wait
}

parse_cases_dir () {
    for casedir in $CASES/*/; do
        casedir=${casedir%*/}
        casename=$(basename $casedir)

        echo -e "\nStarting New Test Case Set: $casename" >> "$SUMMARYFILE"
        parse_case "$casedir"
        echo -e "--------------------------------------------------------------------------------------------------------------------------------\n\n" >> "$SUMMARYFILE"
    done

    # wait
}

create_results_dir () {
    # echo "$RESULTS/$year/$month-$day/"
    # get run count
    runnumber=$(ls -dl "$RESULTS/$year/$month-$day/run-"* 2>/dev/null | grep run- | wc -l)
    # runnumber=$(($runnumber+1))
    # echo $runnumber
    
    
    mkdir -p "$RESULTS/$year/$month-$day/run-$runnumber"

    # Set resultdir and SUMMARYFILE variables to make life easier for me later
    resultdir="$RESULTS/$year/$month-$day/run-$runnumber"
    SUMMARYFILE="$resultdir/summary.txt"

    # Remove the summary file if it exists (shouldn't), ignore errors if it cant remove (pipe to null).
    rm      "$SUMMARYFILE" 2>/dev/null
    # Create empty summary file
    touch   "$SUMMARYFILE"
}

main () {
    create_results_dir 

    parse_cases_dir
    # parse_case "./tests/cases/01-login"
}

start=$(date +%s.%N)
main
end=$(date +%s.%N)
elapsed=$(echo "$end-$start" | bc)
printf "Tests completed in %.03f seconds\n" $elapsed
# echo "Tests completed in: " $elapsed 

# parse_cases_dir 
# ( "$BIN < ")
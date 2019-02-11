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

# ls -la
# as="./test2"
# ("$BIN") <"$as" 

compare_output() {
    local expected="$1"
    local result="$2"

    # fix newlines in the output file.
    sed -i -e 's/ERROR:/ERROR-/g; s/: /: \n/g; s/ERROR-/ERROR: /g' "$result"

    #compare them.
    results=$(diff --suppress-common-lines -y -q -Z "$expected" "$result")
    # results=$(cmp "$expected" "$result")

    echo "RESULTS: $results"
}

run_test_case() {
    local filepath="$1"
    local fullfilename=$(basename -- "$filepath")
    local extension="${fullfilename##*.}"
    local filename="${fullfilename%.*}"
    local testdir=$(dirname $filepath)

    if [ ! -d "$resultdir/$casename" ]; then
        mkdir -p "$resultdir/$casename"
    fi


    (sed -e '$a\' "$filepath" | "$BIN") >"$resultdir/$casename/$filename.output"
    # echo "before error"

    compare_output "$testdir/$filename.termout" "$resultdir/$casename/$filename.output"
}

parse_case() {
    # case=$(basename -- $1)
    local case="$1"
    # echo $case

    for file in $case/*.input; do
        run_test_case "$file"
    done

    # wait
}

parse_cases_dir () {
    for casedir in $CASES/*/; do
        casedir=${casedir%*/}
        casename=$(basename $casedir)
        echo $casedir
        parse_case "$casedir"
    done

    # wait
}

create_results_dir () {
    # echo "$RESULTS/$year/$month-$day/"
    # get run count
    runnumber=$(ls -l "$RESULTS/$year/$month-$day/run-"* 2>/dev/null | grep run- | wc -l)
    # runnumber=$(($runnumber+1))
    # echo $runnumber
    
    mkdir -p "$RESULTS/$year/$month-$day/run-$runnumber"

    resultdir="$RESULTS/$year/$month-$day/run-$runnumber"

    # echo "RESRSET" $resultdir
    # mkdir -p
    
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
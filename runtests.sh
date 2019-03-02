#!/usr/bin/env bash

#Ensure the script starts executing from it's own base directory.
BASE="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
cd "$BASE" || exit  #cd to script base dir

# Declare global variables
BIN="./bin/pick-it-sales"
RES="./bin/CurrentUserAccounts.txt ./bin/AvailableTickets.txt"
TESTDIR="./tests"
CASES="$TESTDIR/cases"
RESULTS="$TESTDIR/results"
SUMMARYFILE=""
CASENAME=""

#Get date variables
YEAR=$(date +'%Y')
MONTH=$(date +'%m')
DAY=$(date +'%d')


# Compare the output of our results after executing them.
compare_output() {
    # Get passed variables
    local expected="$1"
    local result="$2"
    local testname="$3"

    # fix newlines in the output file.
    sed -i -e 's/ERROR:/ERROR-/g; s/: /: \n/g; s/ERROR-/ERROR:/g' "$result"

    #compare them.
    results=$(diff --suppress-common-lines -y -Z -T -t "$expected" "$result")

    # Write results to file. (echoing it to fix newlines)
    echo "$results" >> "$SUMMARYFILE"

    # if results have content, that means the test failed, notify.
    if [ -z "$results" ]
    then
        printf "%-20s \033[32m%s\033[0m\n" "$testname" "PASSED!"
    else
        printf "%-20s \033[31m%s\033[0m\n" "$testname" "FAILED!"
    fi
}

# Run each test case
run_test_case() {
    # declare local variables
    local filepath fullfilename filename testdir

    filepath="$1"                                   # full path of the test input file (E.G "./tests/cases/01-login/Login-01.input")
    fullfilename=$(basename -- "$filepath")         # Full file name of the input file, including extension (E.G "Login-01.input")
    # local extension="${fullfilename##*.}" || true
    filename="${fullfilename%.*}"                   # Just the name of the test, no extension (E.G "Login-01")
    testdir=$(dirname "$filepath")                  # The directory the test is contained in  (E.G "./tests/cases/01-login")

    # Check if the results directory for this test case exists, if not, create it.
    if [ ! -d "$RESULTDIR/$CASENAME" ]; then
        mkdir -p "$RESULTDIR/$CASENAME"
    fi

    # Notify of which test we're running.
    { echo -e "--------------------------------------------------------------------------------------------------------------------------------";
    echo -e "\t\t\t\t\t\tStarting Test: $filename" >> "$SUMMARYFILE";
    echo -e "--------------------------------------------------------------------------------------------------------------------------------"; } >> "$SUMMARYFILE"

    
    # Add a new line to the end of the test file
    # then pipe the newly edited file into the program
    # capture the output and redirect it to the results directory
    (sed -e '$a\' "$filepath" | "$BIN" $RES test.trn) > "$RESULTDIR/$CASENAME/$filename.output"

    # After having executed the test, run the compare function
    compare_output "$testdir/$filename.termout" "$RESULTDIR/$CASENAME/$filename.output" "$filename"
}

parse_case() {
    local case="$1"
    local file

    # Loop over all tests
    for file in "$case"/*.input; do
        run_test_case "$file"
    done
}

parse_cases_dir () {
    # Loop over each case directory
    local casedir
    for casedir in $CASES/*/; do
        casedir="${casedir%*/}"
        CASENAME=$(basename "$casedir")

        echo -e "\nStarting New Test Case Set: $CASENAME" >> "$SUMMARYFILE"
        printf "\n\033[33m%s %+18s\033[0m\n" "Starting:" "cases/$CASENAME"
        parse_case "$casedir"
        echo -e "--------------------------------------------------------------------------------------------------------------------------------\n\n" >> "$SUMMARYFILE"
    done
}

create_results_dir () {
    # get run count
    local runnumber
    runnumber=$(ls -dl "$RESULTS/$YEAR/$MONTH-$DAY/run-"* 2>/dev/null | grep -c run- )
    runnumber=$(printf "%03i" $((runnumber+1)) )
    
    mkdir -p "$RESULTS/$YEAR/$MONTH-$DAY/run-$runnumber"

    # Set RESULTDIR and SUMMARYFILE variables to make life easier for me later
    RESULTDIR="$RESULTS/$YEAR/$MONTH-$DAY/run-$runnumber"
    SUMMARYFILE="$RESULTDIR/summary.txt"

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
printf "Tests completed in %.03f seconds\n" "$elapsed"
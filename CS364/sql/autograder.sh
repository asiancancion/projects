#!/bin/bash

set -u  # raise error for uninitialized variables


if which colordiff > /dev/null; then
  # redefine `diff` as `colordiff` (if available)
  diff() {
    command colordiff "$@"
  }
fi


errors=0


for i in $(seq --equal-width 1 25); do
  database='LargeCo'
  if [ $i -le 5 ]; then
    database='ConstructCo'
  fi

  TAIL=$(git rev-list HEAD -- src/$i.sql | tail -n 1)
  if git diff --exit-code --quiet $TAIL..HEAD -- src/$i.sql; then
    echo "$i not attempted, not bothering to execute query"
    ((errors++))  # increment number of errors
  else
    # setup (e.g., inserting data into tables)
    if [ -f "test/$i-pre.sql" ]; then
      psql --dbname="$database" --file="test/$i-pre.sql" --quiet
    fi

    psql --dbname="$database" --file="src/$i.sql" --output="/tmp/$i.out"

    # tear down (e.g., queries used to test non-SELECT statements)
    if [ -f "test/$i-post.sql" ]; then
      psql --dbname="$database" --file="test/$i-post.sql" --output="/tmp/$i.out"
    fi

    echo "Comparing output for $i..."
    diff --ignore-space-change --strip-trailing-cr --unified \
        "test/$i.out" "/tmp/$i.out" || ((errors++))
  fi
done

echo
echo "$errors errors encountered."
[ $errors = 0 ]  # exit with non-zero status if there were any errors
